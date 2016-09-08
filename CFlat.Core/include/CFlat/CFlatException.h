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

//! @file CFlatException.h

#ifndef CFLAT_CORE_CFLATEXCEPTION_H
#define CFLAT_CORE_CFLATEXCEPTION_H

#include "CFlat/ExceptionType.h"
#include "CFlat/Language/Bool.h"

/* Forward declarations */
struct String;

/* Types */
/// <summary>
/// Holds information about the exception that occured.
/// </summary>
typedef struct CFlatException CFlatException;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="CFlatException"/>.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
/// <param name="type">The type of exception thrown.</param>
/// <param name="message">
///     Pointer to a null-terminated string that describes the exception, or <see cref="null"/> to use the default
///     exception message.
/// </param>
/// <param name="file">The file in which the exception occured.</param>
/// <param name="line">The line at which the exception occured.</param>
/// <param name="innerException">
///     Optional pointer to an <see cref="CFlatException"/> that caused the current exception.
/// </param>
CFlatException *Exception_New(
    ExceptionType type,
    const struct String *message,
    const char *file,
    int line,
    CFlatException *innerException);

/// <summary>
/// Allocates and initializes a new <see cref="CFlatException"/>.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
/// <param name="type">The type of exception thrown.</param>
/// <param name="message">
///     Pointer to a null-terminated string that describes the exception, or <see cref="null"/> to use the default
///     exception message.
/// </param>
/// <param name="file">The file in which the exception occured.</param>
/// <param name="line">The line at which the exception occured.</param>
/// <param name="innerException">
///     Optional pointer to a <see cref="CFlatException"/> that caused the current exception.
/// </param>
CFlatException *Exception_New_CString(
    ExceptionType type,
    const char *userMessage,
    const char *file,
    int line,
    CFlatException *innerException);

/// <summary>
/// Initializes a <see cref="CFlatException"/>.
/// </summary>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
/// <param name="ex">Pointer to a <see cref="CFlatException"/>.</param>
/// <param name="type">The type of exception thrown.</param>
/// <param name="message">
///     Pointer to a null-terminated string that describes the exception, or <see cref="null"/> to use the default
///     exception message.
/// </param>
/// <param name="file">The file in which the exception occured.</param>
/// <param name="line">The line at which the exception occured.</param>
/// <param name="innerException">
///     Optional pointer to an <see cref="CFlatException"/> that caused the current exception.
/// </param>
void Exception_Constructor(
    CFlatException *ex,
    ExceptionType type,
    const struct String *message,
    const char *file,
    int line,
    CFlatException *innerException);

/// <summary>
/// Destroys a <see cref="CFlatException"/>.
/// </summary>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
/// <param name="ex">Pointer to a <see cref="CFlatException"/>.</param>
void Exception_Destructor(CFlatException *ex);

/// <summary>
/// Determines whether a <see cref="CFlatException"/> is of the given type.
/// </summary>
/// <param name="ex">Pointer to a <see cref="CFlatException"/>.</param>
/// <param name="type">The exception type to compare with.</param>
/// <returns><see cref="true"/> if the exception is of the given type; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
bool Exception_IsInstanceOf(const CFlatException *ex, ExceptionType type);

/// <summary>
/// Gets the <see cref="CFlatException"/> that caused the given <see cref="CFlatException"/>.
/// </summary>
/// <param name="ex">Pointer to a <see cref="CFlatException"/>.</param>
/// <returns>
///     A pointer to the <see cref="CFlatException"/> that caused the given <see cref="CFlatException"/>, or
///     <see cref="null"/> if no inner exception was specified.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
CFlatException *Exception_GetInnerException(const CFlatException *ex);

/// <summary>
/// Gets the message describing a given <see cref="CFlatException"/>.
/// </summary>
/// <param name="ex">Pointer to a <see cref="CFlatException"/>.</param>
/// <returns>The message describing the given <see cref="CFlatException"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
const struct String *Exception_GetMessage(const CFlatException *ex);

/// <summary>
/// Gets the name of a <see cref="CFlatException"/>.
/// </summary>
/// <param name="ex">Pointer to a <see cref="CFlatException"/>.</param>
/// <returns>The name of the <see cref="CFlatException"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
const struct String *Exception_GetName(const CFlatException *ex);

/// <summary>
/// Gets the <see cref="ExceptionType"/> of a <see cref="CFlatException"/>.
/// </summary>
/// <param name="ex">Pointer to a <see cref="CFlatException"/>.</param>
/// <returns>The <see cref="ExceptionType"/> of the <see cref="CFlatException"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
ExceptionType Exception_GetType(const CFlatException *ex);

/// <summary>
/// Gets the path of the file in which the specified <see cref="CFlatException"/> was raised.
/// </summary>
/// <param name="ex">Pointer to a <see cref="CFlatException"/>.</param>
/// <returns>The path of the file in which <paramref name="ex"/> was raised.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
const char *Exception_GetFile(const CFlatException *ex);

/// <summary>
/// Gets the line number at which the specified <see cref="CFlatException"/> was raised.
/// </summary>
/// <param name="ex">Pointer to a <see cref="CFlatException"/>.</param>
/// <returns>The line number where <paramref name="ex"/> was raised.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="ex"/> is <see cref="null"/>.</exception>
int Exception_GetLine(const CFlatException *ex);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/CFlatException.internal.h"
#endif

#endif
