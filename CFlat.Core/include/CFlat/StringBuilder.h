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

//! @file StringBuilder.h

#ifndef CFLAT_CORE_STRINGBUILDER_H
#define CFLAT_CORE_STRINGBUILDER_H

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/VarArgs.h"

/* Forward declarations */
struct String;

/* Types */
/// <summary>
/// Represents a mutable string of characters.
/// </summary>
typedef struct StringBuilder StringBuilder;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire() and Object_Release().
/// </remarks>
/// <returns>A pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
StringBuilder *StringBuilder_New(void);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> with the given capacity.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire() and Object_Release().
/// </remarks>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
StringBuilder *StringBuilder_New_WithCapacity(uintsize capacity);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> with the given initial value.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire() and Object_Release().
/// </remarks>
/// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
/// <returns>A pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
StringBuilder *StringBuilder_New_WithInitialCStringValue(const char *value);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> with the given initial value and capacity.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire() and Object_Release().
/// </remarks>
/// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
StringBuilder *StringBuilder_New_WithInitialCStringValueAndCapacity(const char *value, uintsize capacity);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> with the given initial value.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire() and Object_Release().
/// </remarks>
/// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
/// <returns>A pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
StringBuilder *StringBuilder_New_WithInitialStringValue(const struct String *value);

/// <summary>
/// Allocates and initializes a new <see cref="StringBuilder"/> with the given initial value and capacity.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StringBuilder"/> should be managed with Object_Aquire() and Object_Release().
/// </remarks>
/// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="StringBuilder"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
StringBuilder *StringBuilder_New_WithInitialStringValueAndCapacity(const struct String *value, uintsize capacity);

/// <summary>
/// Initializes a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_Constructor(StringBuilder *sb);

/// <summary>
/// Initializes a <see cref="StringBuilder"/> with the given capacity.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_Constructor_WithCapacity(StringBuilder *sb, uintsize capacity);

/// <summary>
/// Initializes a <see cref="StringBuilder"/> with the given initial value.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_Constructor_WithInitialCStringValue(StringBuilder *sb, const char *value);

/// <summary>
/// Initializes a <see cref="StringBuilder"/> with the given initial value and capacity.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_Constructor_WithInitialCStringValueAndCapacity(
    StringBuilder *sb,
    const char *value,
    uintsize capacity);

/// <summary>
/// Initializes a <see cref="StringBuilder"/> with the given initial value.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_Constructor_WithInitialStringValue(StringBuilder *sb, const struct String *value);

/// <summary>
/// Initializes a <see cref="StringBuilder"/> with the given initial value and capacity.
/// </summary>
/// <param name="sb">Pointer to an uninitialized <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
/// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_Constructor_WithInitialStringValueAndCapacity(
    StringBuilder *sb,
    const struct String *value,
    uintsize capacity);

/// <summary>
/// Destroys a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
void StringBuilder_Destructor(StringBuilder *sb);

/// <summary>
/// Gets the length of a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>The length of the <see cref="StringBuilder"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
uintsize StringBuilder_GetLength(const StringBuilder *sb);

/// <summary>
/// Gets the capacity of a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>The capacity of the <see cref="StringBuilder"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
uintsize StringBuilder_GetCapacity(const StringBuilder *sb);

/// <summary>
/// Sets the capacity of a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="capacity">The new capacity of the <see cref="StringBuilder"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="capacity"/> is less than the length of <paramref name="sb"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_SetCapacity(StringBuilder *sb, uintsize capacity);

/// <summary>
/// Appends the given character to a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">The character to append.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_Append(StringBuilder *sb, char value);

/// <summary>
/// Appends the given string to a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to the string to append.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_AppendCString(StringBuilder *sb, const char *value);

/// <summary>
/// Appends the given string to a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to the string to append.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_AppendString(StringBuilder *sb, const struct String *value);

/// <summary>
/// Appends a string that is formatted according to the given format string, to a <see cref="StringBuilder"/>.
/// Each format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_AppendFormatCString(StringBuilder *sb, const char *format, ...);

/// <summary>
/// Appends a string that is formatted according to the given format string, to a <see cref="StringBuilder"/>.
/// Each format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_AppendFormatCStringV(StringBuilder *sb, const char *format, VarArgs args);

/// <summary>
/// Appends a string that is formatted according to the given format string, to a <see cref="StringBuilder"/>.
/// Each format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_AppendFormatString(StringBuilder *sb, const struct String *format, ...);

/// <summary>
/// Appends a string that is formatted according to the given format string, to a <see cref="StringBuilder"/>.
/// Each format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_AppendFormatStringV(StringBuilder *sb, const struct String *format, VarArgs args);

/// <summary>
/// Appends a new line to a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_AppendLine(StringBuilder *sb);

/// <summary>
/// Appends the given string followed by a new line to a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to the string to append.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_AppendLineCString(StringBuilder *sb, const char *value);

/// <summary>
/// Appends the given string followed by a new line to a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="value">Pointer to the string to append.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_AppendLineString(StringBuilder *sb, const struct String *value);

/// <summary>
/// Removes all characters from the specified <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
void StringBuilder_Clear(StringBuilder *sb);

/// <summary>
/// Deletes a <see cref="StringBuilder"/> and returns its value as a <see cref="String"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>
///     A pointer to a <see cref="String"/> with the same value as the <see cref="StringBuilder"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::InvalidOperationException">There are still references to <paramref name="sb"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct String *StringBuilder_DeleteAndToString(StringBuilder *sb);

/// <summary>
/// Deletes a <see cref="StringBuilder"/> and returns its value as a null-terminated string.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>
///     A pointer to a null-terminated string with the same value as the <see cref="StringBuilder"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::InvalidOperationException">There are still references to <paramref name="sb"/>.</exception>
char *StringBuilder_DeleteAndToCString(StringBuilder *sb);

/// <summary>
/// Inserts the given character into a <see cref="StringBuilder"/> at the given index.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="index">The position where to insert <paramref name="value"/>.</param>
/// <param name="value">The character to insert.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is greater than the length of <paramref name="sb"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_Insert(StringBuilder *sb, uintsize index, char value);

/// <summary>
/// Inserts the given string into a <see cref="StringBuilder"/> at the given index.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="index">The position where to insert <paramref name="value"/>.</param>
/// <param name="value">Pointer to the string to insert.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is greater than the length of <paramref name="sb"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_InsertCString(StringBuilder *sb, uintsize index, const char *value);

/// <summary>
/// Inserts the given string into a <see cref="StringBuilder"/> at the given index.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="index">The position where to insert <paramref name="value"/>.</param>
/// <param name="value">Pointer to the string to insert.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is greater than the length of <paramref name="sb"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void StringBuilder_InsertString(StringBuilder *sb, uintsize index, const struct String *value);

/// <summary>
/// Removes the given range of characters from a <see cref="StringBuilder"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="startIndex">The position where to start removing characters.</param>
/// <param name="count">The number of characters to remove.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="sb"/>.
/// </exception>
void StringBuilder_Remove(StringBuilder *sb, uintsize startIndex, uintsize count);

/// <summary>
/// Converts the value of a <see cref="StringBuilder"/> to a <see cref="String"/>.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>
///     A pointer to a <see cref="String"/> with the same value as the <see cref="StringBuilder"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct String *StringBuilder_ToString(const StringBuilder *sb);

/// <summary>
/// Converts the value of a <see cref="StringBuilder"/> to a null-terminated string.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>
///     A pointer to a null-terminated string with the same value as the <see cref="StringBuilder"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
char *StringBuilder_ToCString(const StringBuilder *sb);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/StringBuilder.internal.h"
#endif

#endif
