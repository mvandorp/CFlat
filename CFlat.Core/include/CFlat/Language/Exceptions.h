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

//! @file Exceptions.h

#ifndef CFLAT_CORE_LANGUAGE_EXCEPTIONS_H
#define CFLAT_CORE_LANGUAGE_EXCEPTIONS_H

#include "CFlat/ExceptionType.h"
#include "CFlat/Object.h"
#include "CFlat/Language/Bool.h"

#include <setjmp.h>

/* Forward declarations */
typedef struct String String;

/* Macros */
/// <summary>
/// Marks the beginning of the try block.
/// </summary>
/// <remarks>This macro is intended for internal use only.</remarks>
#define __CFLAT_EXCEPTION_TRY() setjmp(__CFLAT_EXCEPTION_BUFFER)

/// <summary>
/// Begins a try block.
/// </summary>
#define try                                                                         \
{                                                                                   \
    struct __CFLAT_EXCEPTION_STATE __CFLAT_EXCEPTION_STATE;                         \
    __CFLAT_EXCEPTION_BEGINTRY(&__CFLAT_EXCEPTION_STATE);                           \
    if (!__CFLAT_EXCEPTION_TRY()) {

/// <summary>
/// Begins a catch block.
/// </summary>
#define catch(toCatch)                                                              \
    }                                                                               \
    else if (__CFLAT_EXCEPTION_CATCH(&__CFLAT_EXCEPTION_STATE, toCatch)) {

/// <summary>
/// Begins a catch block.
/// </summary>
#define catch_ex(toCatch, var)                                                      \
        catch(toCatch)                                                              \
        ExceptionHandle var = __CFLAT_EXCEPTION_STATE.Exception;

/// <summary>
/// Begins a finally block.
/// </summary>
#define finally                                                                     \
    }                                                                               \
    __CFLAT_EXCEPTION_FINALLY(&__CFLAT_EXCEPTION_STATE);                            \
    {

/// <summary>
/// Indicates the end of a try-catch-finally block.
/// </summary>
#define endtry                                                                      \
    }                                                                               \
    __CFLAT_EXCEPTION_ENDTRY(&__CFLAT_EXCEPTION_STATE);                             \
}

/// <summary>
/// Re-throws an exception that was caught earlier.
/// </summary>
/// <param name="exceptionHandle">The <see cref="ExceptionHandle"/> of the exception to throw.</param>
/// <exception cref="::ArgumentNullException"><paramref name="exceptionHandle"/> is <see cref="null"/>.</exception>
#define throw_again(exceptionHandle) __CFLAT_EXCEPTION_THROW_AGAIN(exceptionHandle)

/// <summary>
/// Throws an exception of the given type.
/// </summary>
/// <param name="exception">The type of exception thrown.</param>
/// <param name="message">
///     Pointer to a null-terminated string that describes the exception, or <see cref="null"/> to use the default
///     exception message.
/// </param>
#define throw_new(exception, message) __CFLAT_EXCEPTION_THROW_NEW(exception, message, __FILE__, __LINE__)

/// <summary>
/// Re-throws the last exception that occured.
/// </summary>
/// <exception cref="::InvalidOperationException"><see cref="throw"/> was used outside of a catch clause.</exception>
#define throw __CFLAT_EXCEPTION_THROW()

/* Types */
/// <summary>
/// Represents an abstraction for an exception, so that information about an exception can be obtained through its
/// handle.
/// </summary>
typedef struct __CFLAT_EXCEPTION *ExceptionHandle;

/// <summary>
/// Holds information about the exception that occured.
/// </summary>
/// <remarks>This struct is intended for internal use only.</remarks>
struct __CFLAT_EXCEPTION {
    /// <summary>
    /// The base class of the exception.
    /// </summary>
    Object Base;
    /// <summary>
    /// Pointer to a string supplied by the user that describes the exception that occured.
    /// </summary>
    const String *UserMessage;
    /// <summary>
    /// Pointer to a string representing the file where the exception occured.
    /// </summary>
    const char *File;
    /// <summary>
    /// The line number within the source file at which the exception occured.
    /// </summary>
    int Line;
    /// <summary>
    /// The exception type.
    /// </summary>
    ExceptionType Type;
};

/// <summary>
/// Holds state information required for exception handling.
/// </summary>
/// <remarks>This struct is intended for internal use only.</remarks>
struct __CFLAT_EXCEPTION_STATE {
    /// <summary>
    /// The jump buffer of the parent try scope, if any.
    /// </summary>
    jmp_buf JumpStack;
    /// <summary>
    /// Indicates whether or not the previous jump buffer still needs to be popped off the stack.
    /// </summary>
    /// <remarks>
    ///     The jump buffer should be popped off the stack directly after a <c>try</c> block. This is achieved through
    ///     popping it at the first <c>catch</c> or <c>finally</c> clause following the <c>try</c> block.
    ///     <see cref="ShouldPopStack"/> keeps track of whether the jump buffer still needs to be popped off the stack
    ///     so that only the first <c>catch</c> or <c>finally</c> clause causes the jump buffer to be popped off the
    ///     stack.
    /// </remarks>
    bool ShouldPopStack;
    /// <summary>
    /// The exception that occured.
    /// </summary>
    ExceptionHandle Exception;
};

/* Variables */
/// <summary>
/// The jump buffer for the current try scope so that longjmp can be used to jump there.
/// </summary>
/// <remarks>This variable is intended for internal use only.</remarks>
extern jmp_buf __CFLAT_EXCEPTION_BUFFER;

/* Functions */
/// <summary>
/// Determines whether the exception pointed to by the given <see cref="ExceptionHandle"/> is of the given type.
/// </summary>
/// <param name="ex">The <see cref="ExceptionHandle"/> of the exception.</param>
/// <param name="type">The exception type to compare with.</param>
/// <returns><see cref="true"/> if the exception is of the given type; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="exceptionHandle"/> is <see cref="null"/>.</exception>
bool Exception_IsInstanceOf(const ExceptionHandle ex, ExceptionType type);

/// <summary>
/// Gets the message describing the exception pointed to by the given <see cref="ExceptionHandle"/>.
/// </summary>
/// <param name="ex">The <see cref="ExceptionHandle"/> of the exception.</param>
/// <returns>The message describing the exception pointed to by the given <see cref="ExceptionHandle"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="exceptionHandle"/> is <see cref="null"/>.</exception>
const String *Exception_GetMessage(const ExceptionHandle ex);

/// <summary>
/// Gets the name of the exception pointed to by the given <see cref="ExceptionHandle"/>.
/// </summary>
/// <param name="ex">The <see cref="ExceptionHandle"/> of the exception.</param>
/// <returns>The name of the exception pointed to by the given <see cref="ExceptionHandle"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="exceptionHandle"/> is <see cref="null"/>.</exception>
const String *Exception_GetName(const ExceptionHandle ex);

/// <summary>
/// Gets the <see cref="ExceptionType"/> of the exception pointed to by the given <see cref="ExceptionHandle"/>.
/// </summary>
/// <param name="ex">The <see cref="ExceptionHandle"/> of the exception.</param>
/// <returns>
///     The <see cref="ExceptionType"/> of the exception pointed to by the given <see cref="ExceptionHandle"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="exceptionHandle"/> is <see cref="null"/>.</exception>
ExceptionType Exception_GetType(const ExceptionHandle ex);

/* 'Hidden / obfuscated' functions */
/// <summary>
/// Prepares the given <see cref="__CFLAT_EXCEPTION_STATE"/>.
/// </summary>
/// <remarks>This function is intended for internal use only.</remarks>
/// <param name="state">Pointer to a <see cref="__CFLAT_EXCEPTION_STATE"/>.</param>
void __CFLAT_EXCEPTION_BEGINTRY(struct __CFLAT_EXCEPTION_STATE *state);

/// <summary>
/// Catches the exception if it matches the given exception type and returns whether the exception should be caught.
/// </summary>
/// <remarks>This function is intended for internal use only.</remarks>
/// <param name="state">Pointer to a <see cref="__CFLAT_EXCEPTION_STATE"/>.</param>
/// <param name="exception">The type of exception to catch.</param>
/// <returns><see cref="true"/> if the exception should be handled; otherwise, <see cref="false"/>.</returns>
bool __CFLAT_EXCEPTION_CATCH(struct __CFLAT_EXCEPTION_STATE *state, ExceptionType exception);

/// <summary>
/// Marks the beginning of the finally block.
/// </summary>
/// <remarks>This function is intended for internal use only.</remarks>
/// <param name="state">Pointer to a <see cref="__CFLAT_EXCEPTION_STATE"/>.</param>
void __CFLAT_EXCEPTION_FINALLY(struct __CFLAT_EXCEPTION_STATE *state);

/// <summary>
/// Ends a try-catch-finally block. If there is an unhandled exception at this point it will be passed to the parent
/// try scope if there is any, otherwise an exception message is printed and the program is aborted.
/// </summary>
/// <remarks>This function is intended for internal use only.</remarks>
/// <param name="state">Pointer to a <see cref="__CFLAT_EXCEPTION_STATE"/>.</param>
void __CFLAT_EXCEPTION_ENDTRY(struct __CFLAT_EXCEPTION_STATE *state);

/// <summary>
/// Re-throws an exception that was caught earlier.
/// </summary>
/// <remarks>This function is intended for internal use only.</remarks>
/// <param name="ex">The <see cref="ExceptionHandle"/> of the exception to throw.</param>
void __CFLAT_EXCEPTION_THROW_AGAIN(const ExceptionHandle ex);

/// <summary>
/// Throws an exception of the given type.
/// </summary>
/// <remarks>This function is intended for internal use only.</remarks>
/// <param name="type">The type of exception thrown.</param>
/// <param name="message">
///     Pointer to a string that describes the exception, or <see cref="null"/> to use the default exception message.
/// </param>
/// <param name="file">Pointer to a string that contains the filename where the exception occured.</param>
/// <param name="line">The line number where the exception occured.</param>
void __CFLAT_EXCEPTION_THROW_NEW(ExceptionType type, const char *message, const char *file, int line);

/// <summary>
/// Re-throws the last exception that occured.
/// </summary>
/// <remarks>This function is intended for internal use only.</remarks>
void __CFLAT_EXCEPTION_THROW(void);

#endif
