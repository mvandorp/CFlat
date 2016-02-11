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

/**
 * @file ExceptionType.h
 */

#ifndef CFLAT_CORE_EXCEPTIONTYPE_H
#define CFLAT_CORE_EXCEPTIONTYPE_H

#include "CFlat/Language/Boolean.h"

typedef struct String String;

/* Macros */
#define CFLAT_EXCEPTIONTYPE_BASE_BITS 4
#define CFLAT_EXCEPTIONTYPE_BASE_VALUE(value) (1 << ((value) - 1))
#define CFLAT_EXCEPTIONTYPE_VALUE(value) ((value) << CFLAT_EXCEPTIONTYPE_BASE_BITS)

/* Types */
/// <summary>
/// Specifies the type of an exception.
/// </summary>
typedef enum ExceptionType {
    /// <summary>
    /// Base class for all exceptions.
    /// </summary>
    Exception = CFLAT_EXCEPTIONTYPE_BASE_VALUE(1),

    /// <summary>
    /// Base class for all runtime-generated errors.
    /// </summary>
    SystemException = CFLAT_EXCEPTIONTYPE_BASE_VALUE(2) | Exception,

    /// <summary>
    /// Base class for all argument exceptions.
    /// </summary>
    ArgumentException = CFLAT_EXCEPTIONTYPE_BASE_VALUE(3) | SystemException,

    /// <summary>
    /// Base class for all I/O exceptions.
    /// </summary>
    IOException = CFLAT_EXCEPTIONTYPE_BASE_VALUE(4) | SystemException,

    /// <summary>
    /// Thrown by the runtime only when an array is indexed improperly.
    /// </summary>
    IndexOutOfRangeException = CFLAT_EXCEPTIONTYPE_VALUE(1) | SystemException,

    /// <summary>
    /// Thrown by the runtime only when a null object is referenced.
    /// </summary>
    NullReferenceException = CFLAT_EXCEPTIONTYPE_VALUE(2) | SystemException,

    /// <summary>
    /// Thrown by the runtime only when invalid memory is accessed.
    /// </summary>
    AccessViolationException = CFLAT_EXCEPTIONTYPE_VALUE(3) | SystemException,

    /// <summary>
    /// Thrown by methods when in an invalid state.
    /// </summary>
    InvalidOperationException = CFLAT_EXCEPTIONTYPE_VALUE(4) | SystemException,

    /// <summary>
    /// Thrown by methods that do not allow an argument to be null.
    /// </summary>
    ArgumentNullException = CFLAT_EXCEPTIONTYPE_VALUE(5) | ArgumentException,

    /// <summary>
    /// Thrown by methods that verify that arguments are in a given range.
    /// </summary>
    ArgumentOutOfRangeException = CFLAT_EXCEPTIONTYPE_VALUE(6) | ArgumentException,

    /// <summary>
    /// Thrown by methods when there is not enough memory to complete a certain operation
    /// </summary>
    OutOfMemoryException = CFLAT_EXCEPTIONTYPE_VALUE(7) | SystemException,

    /// <summary>
    /// Thrown by methods when an attempt to access a file that does not exist on disk fails.
    /// </summary>
    FileNotFoundException = CFLAT_EXCEPTIONTYPE_VALUE(8) | IOException,

    /// <summary>
    /// Throw by methods when the format of an argument is invalid, or when a composite format string is not well
    /// formed.
    /// </summary>
    FormatException = CFLAT_EXCEPTIONTYPE_VALUE(9) | SystemException,
} ExceptionType;

#undef CFLAT_EXCEPTIONTYPE_BASE_BITS
#undef CFLAT_EXCEPTIONTYPE_BASE_VALUE
#undef CFLAT_EXCEPTIONTYPE_VALUE

/* Functions */
/// <summary>
/// Checks whether an instance of the second type can be assigned to an instance of the first type.
/// </summary>
/// <param name="type1">A type.</param>
/// <param name="type2">The type to compare with.</param>
/// <returns>
/// <see cref="true"/> if one of the following coniditions is true:
/// <list type="bullet">
///     <item>
///         <description><paramref name="type2"/> and <paramref name="type1"/> represent the same type.</description>
///     </item>
///     <item>
///         <description>
///             <paramref name="type2"/> is derived either directly or indirectly from <paramref name="type1"/>.
///         </description>
///     </item>
/// </list>
/// otherwise <see cref="false"/>.
/// </returns>
bool ExceptionType_IsAssignableFrom(ExceptionType type1, ExceptionType type2);

/// <summary>
/// Gets a pointer to a <see cref="String"/> representing the name of the given exception type.
/// </summary>
/// <param name="type">The type of which to get the name.</param>
/// <returns>A pointer to a <see cref="String"/> representing the name of the given exception type.</returns>
const String *ExceptionType_GetName(ExceptionType type);

/// <summary>
/// Gets a pointer to a <see cref="String"/> describing an exception of the given type.
/// </summary>
/// <param name="type">The type for which to get the default message.</param>
/// <returns>A pointer to a <see cref="String"/> describing an exception of the given type.</returns>
const String *ExceptionType_GetDefaultMessage(ExceptionType type);

#endif
