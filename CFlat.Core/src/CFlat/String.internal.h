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

#ifndef CFLAT_CORE_STRING_INTERNAL_H
#define CFLAT_CORE_STRING_INTERNAL_H

#ifndef CFLAT_CORE_STRING_H
 #error String.internal.h should not be included directly.
#endif

#include "CFlat.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Language/Integer.h"

/* Macros */
/// <summary>
/// Evaluates to the size of the given string literal.
/// </summary>
/// <remarks>
///     <paramref name="value"/> must be an actual string literal. Passing <see cref="null"/> will yield an incorrect
///     result.
/// </remarks>
/// <param name="value">A string literal.</param>
#define CFLAT_STRING_LITERAL_LENGTH(value) (sizeof(value) - 1)

/// <summary>
/// Initializer for a <see cref="String"/> that initializes the value to the given value string literal.
/// </summary>
/// <param name="value">A string literal.</param>
#define CFLAT_STRING_LITERAL(value)                                                 \
{                                                                                   \
    IEnumerable_const_Initializer((const ObjectVTable*)&String_VTableNoDestructor), \
    CFLAT_STRING_LITERAL_LENGTH(value),                                             \
    value                                                                           \
}

/* Types */
/// <summary>
/// Represents text as an immutable string of characters.
/// </summary>
struct String {
    /// <summary>
    /// The base class of the string.
    /// </summary>
    const IEnumerable Base;
    /// <summary>
    /// The length of the string.
    /// </summary>
    const uintsize Length;
    /// <summary>
    /// Pointer to the null-terminated string that represents the value of the string.
    /// </summary>
    const char * const Value;
};

/* Constants */
/// <summary>
/// The virtual method table for the <see cref="String"/> class.
/// </summary>
internal extern const IEnumerableVTable String_VTable;

/// <summary>
/// The virtual method table for the <see cref="String"/> class, without a destructor set so that the internal
/// null-terminated string is not automatically destroyed.
/// </summary>
internal extern const IEnumerableVTable String_VTableNoDestructor;

/* Functions */
/// <summary>
/// Returns a pointer to a <see cref="String"/> wrapper for given null-terminated string.
/// </summary>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <param name="bufer">
///     Pointer to a buffer capable of storing a <see cref="String"/>, this value cannot be <see cref="null"/>.
/// </param>
/// <returns>
///     A pointer to a <see cref="String"/> wrapper for the given null-terminated string, or <see cref="null"/> if
///     <paramref name="value"/> is <see cref="null"/>.
/// </returns>
internal struct String *String_WrapCString(const char *value, struct String *buffer);

#endif
