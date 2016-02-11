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
 * @file StringBuilder.h
 */

#ifndef CFLAT_CORE_STRINGBUILDER_H
#define CFLAT_CORE_STRINGBUILDER_H

#include "CFlat/Language/Integer.h"

typedef struct String String;

/// <summary>
/// Represents a mutable string of characters.
/// </summary>
typedef struct StringBuilder StringBuilder;

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/>.
///
/// The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire(), Object_Release() and
/// Object_Delete().
/// </summary>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
StringBuilder *StringBuilder_New(void);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> using the given capacity.
///
/// The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire(), Object_Release() and
/// Object_Delete().
/// </summary>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
StringBuilder *StringBuilder_New_WithCapacity(uintsize capacity);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> using the given initial value.
///
/// The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire(), Object_Release() and
/// Object_Delete().
/// </summary>
/// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
StringBuilder *StringBuilder_New_WithInitialCStringValue(const char *value);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> using the given initial value and capacity.
///
/// The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire(), Object_Release() and
/// Object_Delete().
/// </summary>
/// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
StringBuilder *StringBuilder_New_WithInitialCStringValueAndCapacity(const char *value, uintsize capacity);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> using the given initial value.
///
/// The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire(), Object_Release() and
/// Object_Delete().
/// </summary>
/// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
StringBuilder *StringBuilder_New_WithInitialStringValue(const String *value);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> using the given initial value and capacity.
///
/// The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire(), Object_Release() and
/// Object_Delete().
/// </summary>
/// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
StringBuilder *StringBuilder_New_WithInitialStringValueAndCapacity(const String *value, uintsize capacity);

/// <summary>
/// Initializes the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
void StringBuilder_Constructor(StringBuilder *sb);

/// <summary>
/// Initializes the given <see cref="StringBuilder"/> using the given capacity.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
void StringBuilder_Constructor_WithCapacity(StringBuilder *sb, uintsize capacity);

/// <summary>
/// Initializes the given <see cref="StringBuilder"/> using the given initial value.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
void StringBuilder_Constructor_WithInitialCStringValue(StringBuilder *sb, const char *value);

/// <summary>
/// Initializes the given <see cref="StringBuilder"/> using the given initial value and capacity.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
void StringBuilder_Constructor_WithInitialCStringValueAndCapacity(
    StringBuilder *sb,
    const char *value,
    uintsize capacity);

/// <summary>
/// Initializes the given <see cref="StringBuilder"/> using the given initial value.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
void StringBuilder_Constructor_WithInitialStringValue(StringBuilder *sb, const String *value);

/// <summary>
/// Initializes the given <see cref="StringBuilder"/> using the given initial value and capacity.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <returns>Pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
void StringBuilder_Constructor_WithInitialStringValueAndCapacity(
    StringBuilder *sb,
    const String *value,
    uintsize capacity);

/// <summary>
/// Destroys the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
void StringBuilder_Destructor(void *sb);

/// <summary>
/// Gets the length of the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>The length of the <see cref="StringBuilder"/>.</returns>
uintsize StringBuilder_GetLength(const StringBuilder *sb);

/// <summary>
/// Gets the capacity of the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>The capacity of the <see cref="StringBuilder"/>.</returns>
uintsize StringBuilder_GetCapacity(const StringBuilder *sb);

/// <summary>
/// Sets the capacity of the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="capacity">The new capacity of the <see cref="StringBuilder"/>.</param>
void StringBuilder_SetCapacity(StringBuilder *sb, uintsize capacity);

/// <summary>
/// Converts the value of the given <see cref="StringBuilder"/> to a <see cref="String"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>
/// A pointer to a <see cref="String"/> with the same value as the given <see cref="StringBuilder"/>.
/// </returns>
String *StringBuilder_ToString(const StringBuilder *sb);

/// <summary>
/// Converts the value of the given <see cref="StringBuilder"/> to a null-terminated string.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>
/// A pointer to a null-terminated string with the same value as the given <see cref="StringBuilder"/>.
/// </returns>
char *StringBuilder_ToCString(const StringBuilder *sb);

/// <summary>
/// Appends the given character to the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">The character to append.</param>
void StringBuilder_Append(StringBuilder *sb, char value);

/// <summary>
/// Appends the given string to the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to the string to append.</param>
void StringBuilder_AppendCString(StringBuilder *sb, const char *value);

/// <summary>
/// Appends the given string to the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to the string to append.</param>
void StringBuilder_AppendString(StringBuilder *sb, const String *value);

/// <summary>
/// Appends a string that is formatted according to the given format string, to the given <see cref="StringBuilder"/>.
/// Each format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
void StringBuilder_AppendFormatCString(StringBuilder *sb, const char *format, ...);

/// <summary>
/// Appends a string that is formatted according to the given format string, to the given <see cref="StringBuilder"/>.
/// Each format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
void StringBuilder_AppendFormatString(StringBuilder *sb, const String *format, ...);

/// <summary>
/// Appends a new line to the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
void StringBuilder_AppendLine(StringBuilder *sb);

/// <summary>
/// Appends the given string followed by a new line to the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to the string to append.</param>
void StringBuilder_AppendLineCString(StringBuilder *sb, const char *value);

/// <summary>
/// Appends the given string followed by a new line to the given <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to the string to append.</param>
void StringBuilder_AppendLineString(StringBuilder *sb, const String *value);

#endif
