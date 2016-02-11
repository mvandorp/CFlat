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
 * @file String.h
 */

#ifndef CFLAT_CORE_STRING_H
#define CFLAT_CORE_STRING_H

#include "CFlat/Language/Integer.h"

/// <summary>
/// Represents text as an immutable string of characters.
/// </summary>
typedef struct String String;

/// <summary>
/// Allocates and initializes a new <see cref="String"/> to the value represented by the given null-terminated string.
///
/// The lifetime of the <see cref="String"/> should be managed with Object_Aquire(), Object_Release() and
/// Object_Delete().
/// </summary>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <returns>Pointer to the newly allocated string.</returns>
String *String_New(const char *value);

/// <summary>
/// Initializes the given <see cref="String"/> to the value represented by the given null-terminated string.
/// </summary>
/// <param name="str">Pointer to an uninitialized <see cref="String"/>.</param>
/// <param name="value">Pointer to a null-terminated string.</param>
void String_Constructor(String *str, const char *value);

/// <summary>
/// Destroys the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
void String_Destructor(void *str);

/// <summary>
/// Gets the length of the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>The length of the string.</returns>
uintsize String_GetLength(const String *str);

/// <summary>
/// Gets the pointer to the null-terminated string representing the value of the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>A pointer to the null-terminated string representing the value of the string.</returns>
const char *String_GetCString(const String *str);

/// <summary>
/// Gets the character at the given index of the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="index">A position within the string.</param>
/// <returns>The character at the given index of the given <see cref="String"/>.</returns>
char String_GetCharAt(const String *str, uintsize index);

/// <summary>
/// Converts the value of the given <see cref="String"/> to a null-terminated string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>
/// A pointer to a null-terminated string with the same value as the given <see cref="String"/>.
/// </returns>
char *String_ToCString(const String *str);

/// <summary>
/// Returns a pointer to a new <see cref="String"/> that is formatted according to the given format string, with each
/// format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <returns>A pointer to a new <see cref="String"/> that is formatted according to the given format string.</returns>
String *String_FormatCString(const char *format, ...);

/// <summary>
/// Returns a pointer to a new <see cref="String"/> that is formatted according to the given format string, with each
/// format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <returns>A pointer to a new <see cref="String"/> that is formatted according to the given format string.</returns>
String *String_FormatString(const String *format, ...);

/// <summary>
/// Returns a pointer to the empty string.
/// </summary>
/// <returns>A pointer to the empty string.</returns>
const String *String_Empty(void);

#endif
