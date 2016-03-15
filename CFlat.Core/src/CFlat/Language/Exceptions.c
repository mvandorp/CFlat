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
#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

#include <stdio.h>
#include <stdlib.h>

/* Types */
typedef struct __CFLAT_EXCEPTION_STATE ExceptionState;
typedef struct __CFLAT_EXCEPTION CFlatException;

/* Public variables */
public jmp_buf __CFLAT_EXCEPTION_BUFFER;

/* Private variables */
/// <summary>
/// A handle to the exception that is currently being handled, or <see cref="null"/> if there is no exception right now.
/// </summary>
private ExceptionHandle CurrentException = null;

/// <summary>
/// Indicates whether the current exception has already been handled by a catch clause.
/// </summary>
private bool ExceptionHandled = true;

/// <summary>
/// The size of the exception state stack. A stack size greater than zero indicates that the program is currently inside
/// a try block.
/// </summary>
private int StackSize = 0;

/**************************************/
/* Private functions                  */
/**************************************/

private ExceptionHandle Exception_New(ExceptionType type, const String *userMessage, const char *file, int line);
private void Exception_Constructor(
    ExceptionHandle ex,
    ExceptionType type,
    const String *userMessage,
    const char *file,
    int line);
private void Exception_Destructor(ExceptionHandle ex);

private void PushJumpBuffer(jmp_buf stack);
private void PopJumpBuffer(jmp_buf stack);
private void RestoreJumpBuffer(ExceptionState *state);
private String *GenerateExceptionText(const ExceptionHandle ex);
private void UnhandledException(void);
private bool IsInsideTryBlock(void);

/* Private constants */
private const ObjectVTable Exception_VTable = ObjectVTable_Initializer((DestructorFunc)Exception_Destructor);

/**************************************/
/* Public function definitions        */
/**************************************/

public void __CFLAT_EXCEPTION_BEGINTRY(ExceptionState *state)
{
    assert(state != null);

    PushJumpBuffer(state->JumpStack);

    // Set the flag to indicate that this try-catch has not yet popped the previous jump buffer off the stack.
    state->ShouldPopStack = true;

    // Clear the exception flag.
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

    // If the exception flag is still set at this point, throw the exception.
    if (!ExceptionHandled) {
        __CFLAT_EXCEPTION_THROW();
    }

    // If there was an exception but it was handled, clean up the exception.
    if (CurrentException != null) {
        Object_Release(CurrentException);

        CurrentException = null;
    }
}

public void __CFLAT_EXCEPTION_THROW_AGAIN(const ExceptionHandle ex)
{
    Validate_NotNull(ex);

    // Set exception information.
    CurrentException = ex;

    // Throw an exception with the set information.
    __CFLAT_EXCEPTION_THROW();
}

public void __CFLAT_EXCEPTION_THROW_NEW(ExceptionType type, const char *message, const char *file, int line)
{
    assert(file != null);
    assert(line > 0);

    // Set exception information.
    CurrentException = Exception_New(type, String_New(message), file, line);

    // Throw an exception with the set information.
    __CFLAT_EXCEPTION_THROW();
}

public void __CFLAT_EXCEPTION_THROW(void)
{
    Validate_State(CurrentException != null,
        "A throw statement with no arguments is not allowed outside of a catch clause.");

    // Set the exception flag.
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

public bool Exception_IsInstanceOf(const ExceptionHandle ex, ExceptionType type)
{
    Validate_NotNull(ex);

    return ExceptionType_IsAssignableFrom(type, ex->Type);
}

public const String *Exception_GetMessage(const ExceptionHandle ex)
{
    Validate_NotNull(ex);

    if (ex->UserMessage == null) {
        return ExceptionType_GetDefaultMessage(ex->Type);
    }
    else {
        return Object_Aquire(ex->UserMessage);
    }
}

public const String *Exception_GetName(const ExceptionHandle ex)
{
    return ExceptionType_GetName(Exception_GetType(ex));
}

public ExceptionType Exception_GetType(const ExceptionHandle ex)
{
    Validate_NotNull(ex);

    return ex->Type;
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Allocates and initializes a new <see cref="CFlatException"/> and returns its <see cref="ExceptionHandle"/>.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private ExceptionHandle Exception_New(ExceptionType type, const String *userMessage, const char *file, int line)
{
    ExceptionHandle ex = Memory_Allocate(sizeof(CFlatException));

    try {
        Exception_Constructor(ex, type, userMessage, file, line);

        Object_SetDeallocator(ex, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(ex);
        throw;
    }
    endtry;

    return ex;
}

/// <summary>
/// Initializes the <see cref="CFlatException"/> referenced by the given <see cref="ExceptionHandle"/>.
/// </summary>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
private void Exception_Constructor(
    ExceptionHandle ex,
    ExceptionType type,
    const String *userMessage,
    const char *file,
    int line)
{
    assert(ex != null);
    assert(file != null);
    assert(line > 0);

    Object_Constructor(ex, &Exception_VTable);

    ex->Type = type;
    ex->UserMessage = userMessage;
    ex->File = file;
    ex->Line = line;
}

/// <summary>
/// Destroys the <see cref="CFlatException"/> referenced by the given <see cref="ExceptionHandle"/>.
/// </summary>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
private void Exception_Destructor(ExceptionHandle ex)
{
    Validate_NotNull(ex);

    Object_Release(ex->UserMessage);
}

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
/// Generates the error text for a given exception.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private String *GenerateExceptionText(const ExceptionHandle ex)
{
    assert(ex != null);

    const String *name = ExceptionType_GetName(ex->Type);
    const String *message = Exception_GetMessage(ex);
    String *result;

    if (message == null || String_GetLength(message) == 0) {
        result = String_FormatCString(
            "An unhandled exception of type '{string}' occurred\n   at {cstring}:{int}\n",
            name,
            ex->File,
            ex->Line);
    }
    else {
        result = String_FormatCString(
            "An unhandled exception of type '{string}' occurred\n   at {cstring}:{int}\n\n"
            "Additional information: {string}\n",
            name,
            ex->File,
            ex->Line,
            message);
    }

    Object_Release(name);
    Object_Release(message);

    return result;
}

/// <summary>
/// Prints a message based on the current exception, and then aborts the program.
/// </summary>
private void UnhandledException(void)
{
    assert(CurrentException != null);

    try {
        String *message = GenerateExceptionText(CurrentException);

        fprintf(stderr, "%s", String_GetCString(message));

        Object_Release(message);
    }
    catch (Exception);
    endtry;

    Object_Release(CurrentException);
    abort();
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
