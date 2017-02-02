/*
 * Copyright (C) 2015 Martijn van Dorp
 *
 * This file is part of CFlat.Core.
 *
 * CFlat.Core is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFlat.Core is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CFlat/Language/Exceptions.h"

#include "CFlat.h"
#include "CFlat/Console.h"
#include "CFlat/Environment.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/TextWriter.h"

/* Types */
typedef struct __CFLAT_EXCEPTION_STATE ExceptionState;

/* Public variables */
public jmp_buf __CFLAT_EXCEPTION_BUFFER;

/* Private variables */
/// <summary>
/// A handle to the exception that is currently being handled, or <see cref="null"/> if there is no exception right now.
/// </summary>
private CFlatException *CurrentException = null;

/// <summary>
/// Indicates whether the current exception has already been handled by a catch clause.
/// </summary>
private bool ExceptionHandled = true;

/// <summary>
/// Indicates whether or not the first chance exception handler should be invoked when an exception occurs.
/// </summary>
/// <remarks>
///     This is used to disable first chance exception handling when calling a first chance exception handler to prevent
///     calling the exception handler recursively should an exception occur inside the exception handler.
/// </remarks>
private bool InvokeFirstChanceHandler = true;

/// <summary>
/// The size of the exception state stack. A stack size greater than zero indicates that the program is currently inside
/// a try block.
/// </summary>
private int StackSize = 0;

/**************************************/
/* Private functions                  */
/**************************************/

private void PushJumpBuffer(jmp_buf stack);
private void PopJumpBuffer(jmp_buf stack);
private void RestoreJumpBuffer(ExceptionState *state);
private void PrintUnhandledException(const CFlatException *ex);
private void UnhandledException(void);
private bool IsInsideTryBlock(void);

/**************************************/
/* Public function definitions        */
/**************************************/

public void __CFLAT_EXCEPTION_BEGINTRY(ExceptionState *state)
{
    assert(state != null);

    PushJumpBuffer(state->JumpStack);

    // Set the flag to indicate that this try-catch has not yet popped the previous jump buffer off the stack.
    state->ShouldPopStack = true;

    // Store the exception state.
    state->PreviousException = CurrentException;
    state->PreviousExceptionHandled = ExceptionHandled;

    // Reset the exception state.
    CurrentException = null;
    ExceptionHandled = true;
}

public bool __CFLAT_EXCEPTION_CATCH(ExceptionState *state, ExceptionType ex)
{
    assert(state != null);

    RestoreJumpBuffer(state);

    // Test whether the raised exception matches the given exception type.
    if (Exception_IsInstanceOf(state->Exception, ex)) {
        // If so, clear the exception flag.
        ExceptionHandled = true;

        // Return true to indicate that exception should be handled.
        return true;
    }
    else {
        // Return false to indicate that exception should not be handled.
        return false;
    }
}

public void __CFLAT_EXCEPTION_FINALLY(ExceptionState *state)
{
    RestoreJumpBuffer(state);
}

public void __CFLAT_EXCEPTION_ENDTRY(ExceptionState *state)
{
    RestoreJumpBuffer(state);

    if (!ExceptionHandled) {
        // If the exception flag is still set at this point, throw the exception.
        release(state->PreviousException);

        __CFLAT_EXCEPTION_THROW();
    }
    else {
        // If there was an exception but it was handled, clean up the exception.
        release(CurrentException);

        CurrentException = state->PreviousException;
        ExceptionHandled = state->PreviousExceptionHandled;
    }
}

public void __CFLAT_EXCEPTION_THROW(void)
{
    Validate_State(CurrentException != null,
        "A throw statement with no arguments is not allowed outside of a catch clause.");

    CFlatException *exception = CurrentException;

    // Reset the exception state.
    CurrentException = null;
    ExceptionHandled = true;

    // Invoke the exception handlers.
    if (InvokeFirstChanceHandler) {
        InvokeFirstChanceHandler = false;

        try {
            Environment_OnFirstChanceException(exception);
        }
        catch_ex(Exception, ex) {
            // If an exception occurs in the exception handler, overwrite the original exception and propagate the
            // exception.
            release(exception);

            throw_ex(ex);
        }
        endtry;

        InvokeFirstChanceHandler = true;
    }

    // Restore the exception state.
    CurrentException = exception;
    ExceptionHandled = false;

    // Test whether the exception occured within a try block.
    if (IsInsideTryBlock()) {
        // If so, jump to the corresponding catch/finally blocks.
        longjmp(__CFLAT_EXCEPTION_BUFFER, true);
    }
    else {
        // Otherwise, print an exception message and abort the program.
        UnhandledException();
    }
}

public void __CFLAT_EXCEPTION_THROW_AGAIN(CFlatException *ex)
{
    Validate_NotNull(ex);

    // Set exception information.
    CurrentException = ex;

    // Throw an exception with the set information.
    __CFLAT_EXCEPTION_THROW();
}

public void __CFLAT_EXCEPTION_THROW_NEW(
    ExceptionType type,
    const char *message,
    const char *file,
    int line,
    CFlatException *innerException)
{
    assert(file != null);
    assert(line > 0);

    __CFLAT_EXCEPTION_THROW_AGAIN(Exception_New(type, String_New(message), file, line, innerException));
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Pushes the current jump buffer onto the stack to support nested try-catch statements.
/// </summary>
private void PushJumpBuffer(jmp_buf stack)
{
    Memory_Copy(__CFLAT_EXCEPTION_BUFFER, stack, sizeof(jmp_buf));

    StackSize++;
}

/// <summary>
/// Sets the jump buffer to the buffer on top of the stack and pops it off the stack.
/// </summary>
private void PopJumpBuffer(jmp_buf stack)
{
    Memory_Copy(stack, __CFLAT_EXCEPTION_BUFFER, sizeof(jmp_buf));

    StackSize--;
}

/// <summary>
/// Restores the jump buffer to that of the parent try scope, if any.
/// </summary>
private void RestoreJumpBuffer(ExceptionState *state)
{
    assert(state != null);

    // If it hasn't happened already, restore the previous jump buffer by popping it off the stack.
    if (state->ShouldPopStack) {
        PopJumpBuffer(state->JumpStack);

        // Copy the current exception into state.
        state->Exception = CurrentException;

        // Clear the flag that indicates that the jump buffer should be popped off the stack.
        state->ShouldPopStack = false;
    }
}

/// <summary>
/// Prints the error message for a given unhandled exception.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private void PrintUnhandledException(const CFlatException *ex)
{
    assert(ex != null);

    const String *name = retain_const(ExceptionType_GetName(ex->Type));
    const String *message = retain_const(Exception_GetMessage(ex));

    try {
        if (message == null || String_GetLength(message) == 0) {
            TextWriter_WriteFormat_CString(Console_GetError(),
                "An unhandled exception of type '{string}' occurred" Environment_NewLine_CString
                "   at {cstring}:{int}" Environment_NewLine_CString,
                name,
                ex->File,
                ex->Line);
        }
        else {
            TextWriter_WriteFormat_CString(Console_GetError(),
                "An unhandled exception of type '{string}' occurred" Environment_NewLine_CString
                "   at {cstring}:{int}" Environment_NewLine_CString
                Environment_NewLine_CString
                "Additional information: {string}" Environment_NewLine_CString,
                name,
                ex->File,
                ex->Line,
                message);
        }
    }
    finally {
        release(name);
        release(message);
    }
    endtry;
}

/// <summary>
/// Prints a message based on the current exception, and then aborts the program.
/// </summary>
private void UnhandledException(void)
{
    assert(CurrentException != null);

    CFlatException *exception = CurrentException;

    // Reset the exception state.
    CurrentException = null;
    ExceptionHandled = true;

    // Invoke the exception handlers.
    try {
        InvokeFirstChanceHandler = true;

        Environment_OnUnhandledException(exception);
    }
    catch_ex (Exception, ex) {
        // If an exception occurs in the exception handler, overwrite the original exception.
        release(exception);

        exception = retain(ex);
    }
    finally {
        InvokeFirstChanceHandler = false;
    }
    endtry;

    // Print the unhandled exception message.
    try {
        PrintUnhandledException(exception);
    }
    catch (Exception) {
        // If an exception occurs, just give up and call Environment_FailFast().
    }
    endtry;

    release(exception);

    Environment_FailFast();
}

/// <summary>
/// Determines whether the program is currently inside a try block.
/// </summary>
/// <returns><see cref="true"/> if the program is inside a try block; otherwise, <see cref="false"/>.</returns>
private bool IsInsideTryBlock(void)
{
    // If we are inside a try block, the stack size must be greater than zero.
    return StackSize > 0;
}
