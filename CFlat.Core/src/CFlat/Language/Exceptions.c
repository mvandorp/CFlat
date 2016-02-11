#include "CFlat/Language/Exceptions.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/String-private.h"
#include "CFlat/StringHelper.h"
#include "CFlat/Validate.h"

#include <stdio.h>
#include <stdlib.h>

/* Aliases for the 'hidden / obfuscated' symbols */
#define BeginTry            __CFLAT_EXCEPTION_BEGINTRY
#define Catch               __CFLAT_EXCEPTION_CATCH
#define Finally             __CFLAT_EXCEPTION_FINALLY
#define EndTry              __CFLAT_EXCEPTION_ENDTRY
#define ThrowAgain          __CFLAT_EXCEPTION_THROW_AGAIN
#define ThrowNew            __CFLAT_EXCEPTION_THROW_NEW
#define Throw               __CFLAT_EXCEPTION_THROW
#define Exception_GetHandle __CFLAT_EXCEPTION_HANDLE
#define jumpBuffer          __CFLAT_EXCEPTION_BUFFER

typedef struct __CFLAT_EXCEPTION_STATE ExceptionState;
typedef struct __CFLAT_EXCEPTION CFlatException;

/* Extern Variables */
jmp_buf jumpBuffer;

/* Static Variables */
static CFlatException exception;
static bool exceptionHandled = true;
static int stackSize = 0;

/* Static functions */
static void PushJumpBuffer(jmp_buf stack);
static void PopJumpBuffer(jmp_buf stack);
static void RestoreJumpBuffer(ExceptionState *state);
static void UnhandledException(const ExceptionHandle ex);
static bool IsInsideTryBlock(void);

/**************************************/
/* Extern function definitions        */
/**************************************/

void BeginTry(ExceptionState *state)
{
    assert(state != null);

    PushJumpBuffer(state->JumpStack);

    // Set the flag to indicate that this try-catch has not yet popped the previous jump buffer off the stack.
    state->ShouldPopStack = true;

    // Clear the exception flag.
    exceptionHandled = true;
}

bool Catch(ExceptionState *state, ExceptionType ex)
{
    assert(state != null);

    RestoreJumpBuffer(state);

    // Test whether the raised exception matches the given exception type.
    if (Exception_IsInstanceOf(Exception_GetHandle(state), ex)) {
        // If so, clear the exception flag.
        exceptionHandled = true;

        // Return true to indicate that exception should be handled.
        return true;
    }
    else {
        // Return false to indicate that exception should not be handled.
        return false;
    }
}

void Finally(ExceptionState *state)
{
    RestoreJumpBuffer(state);
}

void EndTry(ExceptionState *state)
{
    RestoreJumpBuffer(state);

    // If the exception flag is still set at this point, throw the exception.
    if (!exceptionHandled) {
        Throw();
    }
}

void ThrowAgain(const ExceptionHandle ex)
{
    Validate_NotNull(ex);

    ThrowNew(ex->Type, ex->UserMessage, ex->File, ex->Line);
}

void ThrowNew(ExceptionType type, const char *message, const char *file, int line)
{
    assert(file != null);
    assert(line > 0);

    // Set exception information.
    exception.Type = type;
    exception.UserMessage = message;
    exception.File = file;
    exception.Line = line;

    // Throw an exception with the set information.
    Throw();
}

void Throw(void)
{
    // Set the exception flag.
    exceptionHandled = false;

    // Test whether the exception occured within a try block.
    if (IsInsideTryBlock()) {
        // If so, jump to the corresponding catch/finally blocks.
        longjmp(jumpBuffer, true);
    }
    else {
        // Otherwise, print an exception message and abort the program.
        UnhandledException(&exception);
    }
}

bool Exception_IsInstanceOf(const ExceptionHandle ex, ExceptionType type)
{
    Validate_NotNull(ex);

    return ExceptionType_IsAssignableFrom(type, ex->Type);
}

String *Exception_GetMessage(const ExceptionHandle ex)
{
    Validate_NotNull(ex);

    String *name = ExceptionType_GetName(ex->Type);
    String *message = ExceptionType_GetExceptionMessage(ex->Type, ex->UserMessage);
    String *result;

    if (message == null || String_GetLength(message) == 0) {
        // TODO: Print line where exception occured
        result = String_FormatCString(
            "An unhandled exception of type '%#s' occurred\n   at %s:line\n",
            name,
            ex->File/*,
            ex->Line*/);
    }
    else {
        // TODO: Print line where exception occured
        result = String_FormatCString(
            "An unhandled exception of type '%#s' occurred\n   at %s:line\n\nAdditional information: %#s\n",
            name,
            ex->File,
            /*ex->Line,*/
            message);
    }

    Object_Release(name);
    Object_Release(message);

    return result;
}

ExceptionType Exception_GetType(const ExceptionHandle ex)
{
    Validate_NotNull(ex);

    return ex->Type;
}

const char *Exception_GetUserMessage(const ExceptionHandle ex)
{
    Validate_NotNull(ex);

    return ex->UserMessage;
}

/**************************************/
/* Static function definitions        */
/**************************************/

/// <summary>
/// Pushes the current jump buffer onto the stack to support nested try-catch statements.
/// </summary>
static void PushJumpBuffer(jmp_buf stack)
{
    Memory_Copy(jumpBuffer, stack, sizeof(jmp_buf));

    stackSize++;
}

/// <summary>
/// Sets the jump buffer to the buffer on top of the stack and pops it off the stack.
/// </summary>
static void PopJumpBuffer(jmp_buf stack)
{
    Memory_Copy(stack, jumpBuffer, sizeof(jmp_buf));

    stackSize--;
}

/// <summary>
/// Restores the jump buffer to that of the parent try scope, if any.
/// </summary>
static void RestoreJumpBuffer(ExceptionState *state)
{
    assert(state != null);

    // If it hasn't happened already, restore the previous jump buffer by popping it off the stack.
    if (state->ShouldPopStack) {
        PopJumpBuffer(state->JumpStack);

        // Copy the current exception into state.
        state->Exception = exception;

        // Clear the flag that indicates that the jump buffer should be popped off the stack.
        state->ShouldPopStack = false;
    }
}

/// <summary>
/// Prints an exception message based on the given exception type and message, and then aborts the program.
/// </summary>
/// <param name="ex">The type of exception thrown.</param>
/// <param name="msg">Pointer to a string that describes the error, or <see cref="null"/>.</param>
/// <param name="file">Pointer to a string that contains the filename where the exception occured.</param>
/// <param name="line">The line number where the exception occured.</param>
static void UnhandledException(const ExceptionHandle ex)
{
    assert(ex != null);

    String *message = Exception_GetMessage(ex);

    fprintf(stderr, "%s", String_GetCString(message));

    Object_Release(message);

    abort();
}

/// <summary>
/// Tests whether the program is currently inside a try block.
/// </summary>
/// <returns><see cref="true"/> if the program is inside a try block; otherwise <see cref="false"/>.</returns>
static bool IsInsideTryBlock(void)
{
    // If we are inside a try block, the stack size must be greater than zero.
    return stackSize > 0;
}
