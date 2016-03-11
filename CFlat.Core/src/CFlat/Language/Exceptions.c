#include "CFlat/Language/Exceptions.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

#include <stdio.h>
#include <stdlib.h>

/* Aliases for the 'hidden / obfuscated' symbols */
#define BeginTry            __CFLAT_EXCEPTION_BEGINTRY
#define Catch               __CFLAT_EXCEPTION_CATCH
#define Finally             __CFLAT_EXCEPTION_FINALLY
#define EndTry              __CFLAT_EXCEPTION_ENDTRY
#define Throw               __CFLAT_EXCEPTION_THROW
#define ThrowAgain          __CFLAT_EXCEPTION_THROW_AGAIN
#define ThrowNew            __CFLAT_EXCEPTION_THROW_NEW
#define JumpBuffer          __CFLAT_EXCEPTION_BUFFER

typedef struct __CFLAT_EXCEPTION_STATE ExceptionState;
typedef struct __CFLAT_EXCEPTION CFlatException;

/* Public variables */
public jmp_buf JumpBuffer;

/* Private variables */
private ExceptionHandle CurrentException = null;
private bool ExceptionHandled = true;
private int StackSize = 0;

/* Private function declarations */
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
private const ObjectVTable Exception_VTable = ObjectVTable_Initializer((Destructor)Exception_Destructor);

/**************************************/
/* Public function definitions        */
/**************************************/

public void BeginTry(ExceptionState *state)
{
    assert(state != null);

    PushJumpBuffer(state->JumpStack);

    // Set the flag to indicate that this try-catch has not yet popped the previous jump buffer off the stack.
    state->ShouldPopStack = true;

    // Clear the exception flag.
    ExceptionHandled = true;
}

public bool Catch(ExceptionState *state, ExceptionType ex)
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

public void Finally(ExceptionState *state)
{
    RestoreJumpBuffer(state);
}

public void EndTry(ExceptionState *state)
{
    RestoreJumpBuffer(state);

    // If the exception flag is still set at this point, throw the exception.
    if (!ExceptionHandled) {
        Throw();
    }

    // If there was an exception but it was handled, clean up the exception.
    if (CurrentException != null) {
        Object_Release(CurrentException);

        CurrentException = null;
    }
}

public void ThrowAgain(const ExceptionHandle ex)
{
    Validate_NotNull(ex);

    // Set exception information.
    CurrentException = ex;

    // Throw an exception with the set information.
    Throw();
}

public void ThrowNew(ExceptionType type, const char *message, const char *file, int line)
{
    assert(file != null);
    assert(line > 0);

    // Set exception information.
    CurrentException = Exception_New(type, String_New(message), file, line);

    // Throw an exception with the set information.
    Throw();
}

public void Throw(void)
{
    Validate_State(CurrentException != null,
        "A throw statement with no arguments is not allowed outside of a catch clause.");

    // Set the exception flag.
    ExceptionHandled = false;

    // Test whether the exception occured within a try block.
    if (IsInsideTryBlock()) {
        // If so, jump to the corresponding catch/finally blocks.
        longjmp(JumpBuffer, true);
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
/// Allocates and initializes a new CFlatException and returns a ExceptionHandle.
/// </summary>
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
/// Initializes the CFlatException referenced by the given ExceptionHandle.
/// </summary>
private void Exception_Constructor(
    ExceptionHandle ex,
    ExceptionType type,
    const String *userMessage,
    const char *file,
    int line)
{
    Object_Constructor(ex, &Exception_VTable);

    ex->Type = type;
    ex->UserMessage = userMessage;
    ex->File = file;
    ex->Line = line;
}

/// <summary>
/// Destroys the CFlatException referenced by the given ExceptionHandle.
/// </summary>
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
    Memory_Copy(JumpBuffer, stack, sizeof(jmp_buf));

    StackSize++;
}

/// <summary>
/// Sets the jump buffer to the buffer on top of the stack and pops it off the stack.
/// </summary>
private void PopJumpBuffer(jmp_buf stack)
{
    Memory_Copy(stack, JumpBuffer, sizeof(jmp_buf));

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
/// Prints an exception message based on the given exception type and message, and then aborts the program.
/// </summary>
private void UnhandledException(void)
{
    assert(CurrentException != null);

    String *message = GenerateExceptionText(CurrentException);

    fprintf(stderr, "%s", String_GetCString(message));

    Object_Release(message);
    Object_Release(CurrentException);

    abort();
}

/// <summary>
/// Tests whether the program is currently inside a try block.
/// </summary>
/// <returns><see cref="true"/> if the program is inside a try block; otherwise <see cref="false"/>.</returns>
private bool IsInsideTryBlock(void)
{
    // If we are inside a try block, the stack size must be greater than zero.
    return StackSize > 0;
}
