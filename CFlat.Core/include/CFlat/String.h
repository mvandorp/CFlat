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

//! @file String.h

#ifndef CFLAT_CORE_STRING_H
#define CFLAT_CORE_STRING_H

#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/VarArgs.h"

/* Forward declarations */
struct IEnumerable;

/* Macros */
/// <summary>
/// Evaluates to the size of the given string literal.
/// </summary>
/// <remarks>
///     <paramref name="value"/> must be an actual string literal. Passing <see cref="null"/> will yield an incorrect
///     result.
/// </remarks>
/// <param name="value">A string literal.</param>
#define __CFLAT_STRING_LITERAL_LENGTH(value) (sizeof(value) - 1)

/// <summary>
/// Initializer for a <see cref="String"/> that initializes the value to the given value string literal.
/// </summary>
/// <param name="value">A string literal.</param>
#define String_Initializer(value)                                                   \
{                                                                                   \
    IEnumerable_const_Initializer((const ObjectVTable*)&String_VTableNoDestructor), \
    __CFLAT_STRING_LITERAL_LENGTH(value),                                           \
    value                                                                           \
}

/* Constants */
/// <summary>
/// The virtual method table for the <see cref="String"/> class.
/// </summary>
extern const IEnumerableVTable String_VTable;

/// <summary>
/// The virtual method table for the <see cref="String"/> class, without a destructor set so that the internal
/// null-terminated string is not automatically destroyed.
/// </summary>
extern const IEnumerableVTable String_VTableNoDestructor;

/* Types */
/// <summary>
/// Represents text as an immutable string of characters.
/// </summary>
typedef struct String {
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
} String;

/// <summary>
/// Specifies how a string should be split.
/// </summary>
typedef enum StringSplitOptions {
    /// <summary>
    /// Specifies nothing.
    /// </summary>
    StringSplitOptions_None = 0,
    /// <summary>
    /// Specifies that empty entries are not included in the return value.
    /// </summary>
    StringSplitOptions_RemoveEmptyEntries = 1 << 0
} StringSplitOptions;

/* Constants */
/// <summary>
/// Represents an empty string.
/// </summary>
extern String * const String_Empty;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="String"/> to the value represented by the given null-terminated string.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="String"/> should be managed with retain() and release().
/// </remarks>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <returns>A pointer to the newly allocated string.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_New(const char *value);

/// <summary>
/// Allocates and initializes a new <see cref="String"/> to the value represented by the given null-terminated string,
/// starting position and length.
/// </summary>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <param name="startIndex">The starting position within <paramref name="value"/>.</param>
/// <param name="length">The number of character within <paramref name="value"/> to use.</param>
/// <returns>A pointer to the newly allocated string.</returns>
/// <exception cref="::ArgumentException">
///     <paramref name="value"/> is <see cref="null"/> and <paramref name="length"/> is greater than 0.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/> <b>-or-</b>
///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="str"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_New_Substring(const char *value, uintsize startIndex, uintsize length);

/// <summary>
/// Initializes a <see cref="String"/> to the value represented by the given null-terminated string.
/// </summary>
/// <param name="str">Pointer to an uninitialized <see cref="String"/>.</param>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void String_Constructor(String *str, const char *value);

/// <summary>
/// Initializes a <see cref="String"/> to the value represented by the given null-terminated string, starting position
/// and length.
/// </summary>
/// <param name="str">Pointer to an uninitialized <see cref="String"/>.</param>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <param name="startIndex">The starting position within <paramref name="value"/>.</param>
/// <param name="length">The number of character within <paramref name="value"/> to use.</param>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/></exception>
/// <exception cref="::ArgumentException">
///     <paramref name="value"/> is <see cref="null"/> and <paramref name="length"/> is greater than 0.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/> <b>-or-</b>
///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="str"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void String_Constructor_Substring(String *str, const char *value, uintsize startIndex, uintsize length);

/// <summary>
/// Destroys a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
void String_Destructor(String *str);

/// <summary>
/// Gets the character at the given index of a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="index">A position within the string.</param>
/// <returns>The character at the given index of the given <see cref="String"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the length of <paramref name="str"/>.
/// </exception>
char String_GetCharAt(const String *str, uintsize index);

/// <summary>
/// Gets the pointer to the null-terminated string representing the value of a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>The pointer to the null-terminated string representing the value of the <see cref="String"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
const char *String_GetCString(const String *str);

/// <summary>
/// Gets the length of a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>The length of the <see cref="String"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
uintsize String_GetLength(const String *str);

/// <summary>
/// Compares two given strings and returns an integer that indicates their relative position in the sort order.
/// </summary>
/// <param name="str1">Pointer to the first <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second <see cref="String"/>, or <see cref="null"/>.</param>
/// <returns>
///     Less than zero if <paramref name="str1"/> precedes <paramref name="str2"/> in the sort order;
///     Zero if <paramref name="str1"/> occurs in the same position as <paramref name="str2"/> in the sort order;
///     Greater than zero if <paramref name="str1"/> follows <paramref name="str2"/> in the sort order.
/// </returns>
int String_Compare(const String *str1, const String *str2);

/// <summary>
/// Compares two given strings, ignoring or honoring their case, and returns an integer that indicates their relative
/// position in the sort order.
/// </summary>
/// <param name="str1">Pointer to the first <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="ignoreCase">
///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
/// </param>
/// <returns>
///     Less than zero if <paramref name="str1"/> precedes <paramref name="str2"/> in the sort order;
///     Zero if <paramref name="str1"/> occurs in the same position as <paramref name="str2"/> in the sort order;
///     Greater than zero if <paramref name="str1"/> follows <paramref name="str2"/> in the sort order.
/// </returns>
int String_Compare_IgnoreCase(const String *str1, const String *str2, bool ignoreCase);

/// <summary>
/// Compares substrings of two given strings and returns an integer that indicates their relative position in the sort
/// order.
/// </summary>
/// <param name="str1">Pointer to the first <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="startIndex1">The position of the substring within <paramref name="str1"/>.</param>
/// <param name="str2">Pointer to the second <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="startIndex2">The position of the substring within <paramref name="str2"/>.</param>
/// <param name="length">The maximum number of characters in the substrings to compare.</param>
/// <returns>
///     Less than zero if <paramref name="str1"/> precedes <paramref name="str2"/> in the sort order;
///     Zero if <paramref name="str1"/> occurs in the same position as <paramref name="str2"/> in the sort order;
///     Greater than zero if <paramref name="str1"/> follows <paramref name="str2"/> in the sort order.
/// </returns>
/// <exception cref="ArgumentException">
///     <paramref name="length"/> is greater than zero and <paramref name="str1"/> or <paramref name="str2"/> is
///     <see cref="null"/>.
/// </exception>
/// <exception cref="ArgumentOutOfRangeException">
///     <paramref name="startIndex1"/> is greater than the size of <paramref name="str1"/> <b>-or-</b>
///     <paramref name="startIndex2"/> is greater than the size of <paramref name="str2"/>.
/// </exception>
int String_CompareSubstrings(
    const String *str1,
    uintsize startIndex1,
    const String *str2,
    uintsize startIndex2,
    uintsize length);

/// <summary>
/// Compares substrings of two given strings, ignoring or honoring their case, and returns an integer that indicates
/// their relative position in the sort order.
/// </summary>
/// <param name="str1">Pointer to the first <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="startIndex1">The position of the substring within <paramref name="str1"/>.</param>
/// <param name="str2">Pointer to the second <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="startIndex2">The position of the substring within <paramref name="str2"/>.</param>
/// <param name="length">The maximum number of characters in the substrings to compare.</param>
/// <param name="ignoreCase">
///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
/// </param>
/// <returns>
///     Less than zero if <paramref name="str1"/> precedes <paramref name="str2"/> in the sort order;
///     Zero if <paramref name="str1"/> occurs in the same position as <paramref name="str2"/> in the sort order;
///     Greater than zero if <paramref name="str1"/> follows <paramref name="str2"/> in the sort order.
/// </returns>
/// <exception cref="ArgumentException">
///     <paramref name="length"/> is greater than zero and <paramref name="str1"/> or <paramref name="str2"/> is
///     <see cref="null"/>.
/// </exception>
/// <exception cref="ArgumentOutOfRangeException">
///     <paramref name="startIndex1"/> is greater than the size of <paramref name="str1"/> <b>-or-</b>
///     <paramref name="startIndex2"/> is greater than the size of <paramref name="str2"/>.
/// </exception>
int String_CompareSubstrings_IgnoreCase(
    const String *str1,
    uintsize startIndex1,
    const String *str2,
    uintsize startIndex2,
    uintsize length,
    bool ignoreCase);

/// <summary>
/// Concatenates two given strings.
/// </summary>
/// <param name="str1">The first string to concatenate.</param>
/// <param name="str2">The second string to concatenate.</param>
/// <returns>A pointer to a new <see cref="String"/> that is the concatenation of the given strings.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Concat(const String *str1, const String *str2);

/// <summary>
/// Concatenates three given strings.
/// </summary>
/// <param name="str1">The first string to concatenate.</param>
/// <param name="str2">The second string to concatenate.</param>
/// <param name="str3">The third string to concatenate.</param>
/// <returns>A pointer to a new <see cref="String"/> that is the concatenation of the given strings.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Concat3(const String *str1, const String *str2, const String *str3);

/// <summary>
/// Concatenates four given strings.
/// </summary>
/// <param name="str1">The first string to concatenate.</param>
/// <param name="str2">The second string to concatenate.</param>
/// <param name="str3">The third string to concatenate.</param>
/// <param name="str4">The fourth string to concatenate.</param>
/// <returns>A pointer to a new <see cref="String"/> that is the concatenation of the given strings.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Concat4(const String *str1, const String *str2, const String *str3, const String *str4);

/// <summary>
/// Concatenates the strings in the given array.
/// </summary>
/// <param name="strings">An array of strings to concatenate.</param>
/// <param name="count">The number of strings in <pararef name="strings"/>.</param>
/// <returns>A pointer to a new <see cref="String"/> that is the concatenation of the given strings.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="strings"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_ConcatArray(const String * const *strings, uintsize count);

/// <summary>
/// Concatenates the strings in the given <see cref="IEnumerable"/>.
/// </summary>
/// <param name="strings">A collection of strings that implements <see cref="IEnumerable"/>.</param>
/// <returns>A pointer to a new <see cref="String"/> that is the concatenation of the given strings.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="strings"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_ConcatEnumerable(const struct IEnumerable *strings);

/// <summary>
/// Determines whether a <see cref="String"/> contains the specified character.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <returns>
///     <see cref="true"/> if the string contains <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
bool String_Contains(const String *str, char value);

/// <summary>
/// Determines whether a <see cref="String"/> contains the specified string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     <see cref="true"/> if the string contains <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_ContainsCString(const String *str, const char *value);

/// <summary>
/// Determines whether a <see cref="String"/> contains the specified string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     <see cref="true"/> if the string contains <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_ContainsString(const String *str, const String *value);

/// <summary>
/// Creates a new <see cref="String"/> with the same value as the given string.
/// </summary>
/// <param name="str">The string to copy.</param>
/// <returns>A pointer to a new <see cref="String"/> with the same value as <paramref name="str"/>.</returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Copy(const String *str);

/// <summary>
/// Copies a number of characters at the given position of a <see cref="String"/> to the given array.
/// </summary>
/// <param name="source">The string to copy.</param>
/// <param name="sourceIndex">The index of the first character in <paramref name="source"/> to copy.</param>
/// <param name="destination">An array to which the characters should be copied.</param>
/// <param name="destinationIndex">The index in <paramref name="destination"/> at which copying begins.</param>
/// <param name="count">The number of characters to copy.</param>
/// <exception cref="ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="ArgumentOutOfRangeException">
///     <paramref name="sourceIndex"/> does not identify a position in <paramref name="source"/> <b>-or-</b>
///     <paramref name="count"/> is greater than the length of the substring from <paramref name="sourceIndex"/> to
///     the end of <paramref name="source"/>.
/// </exception>
void String_CopyTo(
    const String *source,
    uintsize sourceIndex,
    char *destination,
    uintsize destinationIndex,
    uintsize count);

/// <summary>
/// Determines whether a <see cref="String"/> ends with the specified character.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <returns>
///     <see cref="true"/> if the string ends with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
bool String_EndsWith(const String *str, char value);

/// <summary>
/// Determines whether a <see cref="String"/> ends with the specified string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     <see cref="true"/> if the string ends with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_EndsWithCString(const String *str, const char *value);

/// <summary>
/// Determines whether a <see cref="String"/> ends with the specified string, ignoring or honoring case.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="ignoreCase">
///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
/// </param>
/// <returns>
///     <see cref="true"/> if the string ends with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_EndsWithCString_IgnoreCase(const String *str, const char *value, bool ignoreCase);

/// <summary>
/// Determines whether a <see cref="String"/> ends with the specified string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     <see cref="true"/> if the string ends with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_EndsWithString(const String *str, const String *value);

/// <summary>
/// Determines whether a <see cref="String"/> ends with the specified string, ignoring or honoring case.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="ignoreCase">
///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
/// </param>
/// <returns>
///     <see cref="true"/> if the string ends with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_EndsWithString_IgnoreCase(const String *str, const String *value, bool ignoreCase);

/// <summary>
/// Determines whether two given strings have the same value.
/// </summary>
/// <param name="str1">Pointer to the first <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second <see cref="String"/>, or <see cref="null"/>.</param>
/// <returns>
///     <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
///     otherwise, <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are
///     <see cref="null"/>, the method returns <see cref="true"/>.
/// </returns>
bool String_Equals(const String *str1, const String *str2);

/// <summary>
/// Determines whether two given strings have the same value, ignoring or honoring their case.
/// </summary>
/// <param name="str1">Pointer to the first <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="ignoreCase">
///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
/// </param>
/// <returns>
///     <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
///     otherwise, <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are
///     <see cref="null"/>, the method returns <see cref="true"/>.
/// </returns>
bool String_Equals_IgnoreCase(const String *str1, const String *str2, bool ignoreCase);

/// <summary>
/// Determines whether two given strings have the same value.
/// </summary>
/// <param name="str1">Pointer to the first <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second <see cref="String"/>, or <see cref="null"/>.</param>
/// <returns>
///     <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
///     otherwise, <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are
///     <see cref="null"/>, the method returns <see cref="true"/>.
/// </returns>
bool String_EqualsCString(const String *str1, const char *str2);

/// <summary>
/// Determines whether two given strings have the same value, ignoring or honoring their case.
/// </summary>
/// <param name="str1">Pointer to the first <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="ignoreCase">
///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
/// </param>
/// <returns>
///     <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
///     otherwise, <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are
///     <see cref="null"/>, the method returns <see cref="true"/>.
/// </returns>
bool String_EqualsCString_IgnoreCase(const String *str1, const char *str2, bool ignoreCase);

/// <summary>
/// Returns a pointer to a new <see cref="String"/> that is formatted according to the given format string, with each
/// format specifier replaced by a string representation of the corresponding argument.
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <returns>A pointer to a new <see cref="String"/> that is formatted according to the given format string.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_FormatCString(const char *format, ...);

/// <summary>
/// Returns a pointer to a new <see cref="String"/> that is formatted according to the given format string, with each
/// format specifier replaced by a string representation of the corresponding argument.
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <returns>A pointer to a new <see cref="String"/> that is formatted according to the given format string.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_FormatCStringV(const char *format, VarArgsList args);

/// <summary>
/// Returns a pointer to a new <see cref="String"/> that is formatted according to the given format string, with each
/// format specifier replaced by a string representation of the corresponding argument.
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <returns>A pointer to a new <see cref="String"/> that is formatted according to the given format string.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_FormatString(const String *format, ...);

/// <summary>
/// Returns a pointer to a new <see cref="String"/> that is formatted according to the given format string, with each
/// format specifier replaced by a string representation of the corresponding argument.
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <returns>A pointer to a new <see cref="String"/> that is formatted according to the given format string.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_FormatStringV(const String *format, VarArgsList args);

/// <summary>
/// Returns the hash code for a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>A 32-bit signed integer hash code.</returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
int String_GetHashCode(const String *str);

/// <summary>
/// Returns the index of the first occurance of the specified character in a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
uintsize String_IndexOf(const String *str, char value);

/// <summary>
/// Returns the index of the first occurance of the specified character in a <see cref="String"/>.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
/// </exception>
uintsize String_IndexOf_Offset(const String *str, char value, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of the specified character in a <see cref="String"/>.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/> <b>-or-</b>
///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="str"/>.
/// </exception>
uintsize String_IndexOf_Substring(const String *str, char value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the first occurance of any of the specified character in a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="anyOf"/> is <see cref="null"/>.
/// </exception>
uintsize String_IndexOfAny(const String *str, const char *anyOf);

/// <summary>
/// Returns the index of the first occurance of any of the specified character in a <see cref="String"/>.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="anyOf"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
/// </exception>
uintsize String_IndexOfAny_Offset(const String *str, const char *anyOf, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of any of the specified character in a <see cref="String"/>.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="anyOf"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/> <b>-or-</b>
///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="str"/>.
/// </exception>
uintsize String_IndexOfAny_Substring(const String *str, const char *anyOf, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the first occurance of the specified string in a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
uintsize String_IndexOfCString(const String *str, const char *value);

/// <summary>
/// Returns the index of the first occurance of the specified string in a <see cref="String"/>.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
/// </exception>
uintsize String_IndexOfCString_Offset(const String *str, const char *value, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of the specified string in a <see cref="String"/>.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/> <b>-or-</b>
///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="str"/>.
/// </exception>
uintsize String_IndexOfCString_Substring(const String *str, const char *value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the first occurance of the specified string in a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
uintsize String_IndexOfString(const String *str, const String *value);

/// <summary>
/// Returns the index of the first occurance of the specified string in a <see cref="String"/>.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
/// </exception>
uintsize String_IndexOfString_Offset(const String *str, const String *value, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of the specified string in a <see cref="String"/>.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/> <b>-or-</b>
///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="str"/>.
/// </exception>
uintsize String_IndexOfString_Substring(const String *str, const String *value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns a new <see cref="String"/> in which the given string is inserted at the given index in
/// <paramref name="str"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="startIndex">The index at which to insert <paramref name="value"/>.</param>
/// <param name="value">The string to insert.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but with <paramref name="value"/>
///     inserted at position <paramref name="startIndex"/>.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Insert(const String *str, uintsize startIndex, const String *value);

/// <summary>
/// Determines whether a <see cref="String"/> is <see cref="null"/> or empty.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="str"/> is <see cref="null"/> or empty; otherwise, <see cref="false"/>.
/// </returns>
bool String_IsNullOrEmpty(const String *str);

/// <summary>
/// Determines whether a <see cref="String"/> is <see cref="null"/>, empty, or consists only of white-space characters.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="str"/> is <see cref="null"/>, empty, or consists only of white-space
///     characters; otherwise, <see cref="false"/>.
/// </returns>
bool String_IsNullOrWhiteSpace(const String *str);

/// <summary>
/// Concatenates the strings in the given array, using the given separator between each string.
/// </summary>
/// <param name="separator">The string to use as a separator.</param>
/// <param name="strings">An array of strings to concatenate.</param>
/// <param name="count">The number of strings in <pararef name="strings"/>.</param>
/// <returns>A pointer to a new <see cref="String"/> that is the concatenation of the given strings.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="strings"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Join(const String *separator, const String * const *strings, uintsize count);

/// <summary>
/// Concatenates the strings in the given <see cref="IEnumerable"/>, using the given separator between each string.
/// </summary>
/// <param name="separator">The string to use as a separator.</param>
/// <param name="strings">A collection of strings that implements <see cref="IEnumerable"/>.</param>
/// <returns>A pointer to a new <see cref="String"/> that is the concatenation of the given strings.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="strings"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_JoinEnumerable(const String *separator, const struct IEnumerable *strings);

/// <summary>
/// Returns the index of the last occurance of the specified character in a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
uintsize String_LastIndexOf(const String *str, char value);

/// <summary>
/// Returns the index of the last occurance of the specified character in a <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> is greater than or equal to the length
///     of <paramref name="str"/>.
/// </exception>
uintsize String_LastIndexOf_Offset(const String *str, char value, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of the specified character in a <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> is greater than or equal to the length
///     of <paramref name="str"/> <b>-or-</b>
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> - <paramref name="count"/> + 1 is less
///     than 0.
/// </exception>
uintsize String_LastIndexOf_Substring(const String *str, char value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the last occurance of any of the specified character in a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="anyOf"/> is <see cref="null"/>.
/// </exception>
uintsize String_LastIndexOfAny(const String *str, const char *anyOf);

/// <summary>
/// Returns the index of the last occurance of any of the specified character in a <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="anyOf"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> is greater than or equal to the length
///     of <paramref name="str"/>.
/// </exception>
uintsize String_LastIndexOfAny_Offset(const String *str, const char *anyOf, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of any of the specified character in a <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="anyOf"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> is greater than or equal to the length
///     of <paramref name="str"/> <b>-or-</b>
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> - <paramref name="count"/> + 1 is less
///     than 0.
/// </exception>
uintsize String_LastIndexOfAny_Substring(const String *str, const char *anyOf, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the last occurance of the specified string in a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
uintsize String_LastIndexOfCString(const String *str, const char *value);

/// <summary>
/// Returns the index of the last occurance of the specified string in a <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> is greater than or equal to the length
///     of <paramref name="str"/>.
/// </exception>
uintsize String_LastIndexOfCString_Offset(const String *str, const char *value, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of the specified string in a <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> is greater than or equal to the length
///     of <paramref name="str"/> <b>-or-</b>
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> - <paramref name="count"/> + 1 is less
///     than 0.
/// </exception>
uintsize String_LastIndexOfCString_Substring(
    const String *str,
    const char *value,
    uintsize startIndex,
    uintsize count);

/// <summary>
/// Returns the index of the last occurance of the specified string in a <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
uintsize String_LastIndexOfString(const String *str, const String *value);

/// <summary>
/// Returns the index of the last occurance of the specified string in a <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> is greater than or equal to the length
///     of <paramref name="str"/>.
/// </exception>
uintsize String_LastIndexOfString_Offset(const String *str, const String *value, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of the specified string in a <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> is greater than or equal to the length
///     of <paramref name="str"/> <b>-or-</b>
///     <paramref name="str"/> is not empty, and <paramref name="startIndex"/> - <paramref name="count"/> + 1 is less
///     than 0.
/// </exception>
uintsize String_LastIndexOfString_Substring(
    const String *str,
    const String *value,
    uintsize startIndex,
    uintsize count);

/// <summary>
/// Returns a new <see cref="String"/> that right-aligns the characters in <paramref name="str"/> by padding them on the
/// left with a specified character, for a specified total length.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="totalWidth">The desired number of characters in the resulting string.</param>
/// <param name="paddingChar">The padding character.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but right-aligned and padded on
///     the left with as many <paramref name="paddingChar"/> as needed to create a length of
///     <paramref name="totalWidth"/>. However, if <paramref name="totalWidth"/> is less than or equal to the length of
///     <paramref name="str"/>, the method returns <paramref name="str"/>.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_PadLeft(const String *str, uintsize totalWidth, char paddingChar);

/// <summary>
/// Returns a new <see cref="String"/> that left-aligns the characters in <paramref name="str"/> by padding them on the
/// right with a specified character, for a specified total length.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="totalWidth">The desired number of characters in the resulting string.</param>
/// <param name="paddingChar">The padding character.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but left-aligned and padded on
///     the right with as many <paramref name="paddingChar"/> as needed to create a length of
///     <paramref name="totalWidth"/>. However, if <paramref name="totalWidth"/> is less than or equal to the length of
///     <paramref name="str"/>, the method returns <paramref name="str"/>.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_PadRight(const String *str, uintsize totalWidth, char paddingChar);

/// <summary>
/// Returns a new <see cref="String"/> in which all the characters in <paramref name="str"/>, beginning at a specified
/// position and continuing through the last position, have been deleted.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="startIndex">The position where to begin deleting characters.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but with the specified characters
///     removed.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Remove(const String *str, uintsize startIndex);

/// <summary>
/// Returns a new <see cref="String"/> in which a specified number of characters in <paramref name="str"/>, beginning at
/// a specified position, have been deleted.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="startIndex">The position where to begin deleting characters.</param>
/// <param name="count">The number of characters to delete.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but with the specified characters
///     removed.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="str"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Remove_Substring(const String *str, uintsize startIndex, uintsize count);

/// <summary>
/// Returns a new <see cref="String"/> in which all occurrences of a specified character in <paramref name="str"/> are
/// replaced with another specified character.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="oldChar">The character to be replaced.</param>
/// <param name="newChar">The character to replace all occurrences of <paramref name="oldChar"/>.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but with all occurrences of
///     <paramref name="oldChar"/> replaced by <paramref name="newChar"/>.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Replace(const String *str, char oldValue, char newValue);

/// <summary>
/// Returns a new <see cref="String"/> in which all occurrences of a specified string in <paramref name="str"/> are
/// replaced with another specified string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="oldValue">The string to be replaced.</param>
/// <param name="newValue">The string to replace all occurrences of <paramref name="newValue"/>.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but with all occurrences of
///     <paramref name="oldChar"/> replaced by <paramref name="newChar"/>.
/// </returns>
/// <exception cref="ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="oldValue"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="ArgumentException">
///     <paramref name="oldValue"/> is the empty string ("").
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_ReplaceCString(const String *str, const char *oldValue, const char *newValue);

/// <summary>
/// Returns a new <see cref="String"/> in which all occurrences of a specified string in <paramref name="str"/> are
/// replaced with another specified string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="oldValue">The string to be replaced.</param>
/// <param name="newValue">The string to replace all occurrences of <paramref name="newValue"/>.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but with all occurrences of
///     <paramref name="oldChar"/> replaced by <paramref name="newChar"/>.
/// </returns>
/// <exception cref="ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="oldValue"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentException">
///     <paramref name="oldValue"/> is the empty string ("").
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_ReplaceString(const String *str, const String *oldValue, const String *newValue);

/// <summary>
/// Splits a string into substrings delimited by any of the given separator characters.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="separators">
///     A null-terminated array of characters that delimit the substrings in <paramref name="str"/>.
/// </param>
/// <returns>
///     An <see cref="IList"/> containing the substrings resulting from splitting <paramref name="str"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IList *String_Split(const String *str, const char *separators);

/// <summary>
/// Splits a string into a maximum number of substrings delimited by any of the given separator characters.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="separators">
///     A null-terminated array of characters that delimit the substrings in <paramref name="str"/>.
/// </param>
/// <param name="count">The maximum number of substrings to return.</param>
/// <returns>
///     An <see cref="IList"/> containing the substrings resulting from splitting <paramref name="str"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IList *String_Split_AtMost(const String *str, const char *separators, uintsize count);

/// <summary>
/// Splits a string into substrings delimited by any of the given separator characters.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="separators">
///     A null-terminated array of characters that delimit the substrings in <paramref name="str"/>.
/// </param>
/// <param name="options">A <see cref="StringSplitOptions"/> value that determines how to split the string.</param>
/// <returns>
///     An <see cref="IList"/> containing the substrings resulting from splitting <paramref name="str"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IList *String_Split_WithOptions(const String *str, const char *separators, StringSplitOptions options);

/// <summary>
/// Splits a string into a maximum number of substrings delimited by any of the given separator characters.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="separators">
///     A null-terminated array of characters that delimit the substrings in <paramref name="str"/>.
/// </param>
/// <param name="count">The maximum number of substrings to return.</param>
/// <param name="options">A <see cref="StringSplitOptions"/> value that determines how to split the string.</param>
/// <returns>
///     An <see cref="IList"/> containing the substrings resulting from splitting <paramref name="str"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IList *String_Split_AtMost_WithOptions(
    const String *str,
    const char *separators,
    uintsize count,
    StringSplitOptions options);

/// <summary>
/// Determines whether a <see cref="String"/> starts with the specified character.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <returns>
///     <see cref="true"/> if the string starts with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
bool String_StartsWith(const String *str, char value);

/// <summary>
/// Determines whether a <see cref="String"/> starts with the specified string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     <see cref="true"/> if the string starts with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_StartsWithCString(const String *str, const char *value);

/// <summary>
/// Determines whether a <see cref="String"/> starts with the specified string, ignoring or honoring their case.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="ignoreCase">
///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
/// </param>
/// <returns>
///     <see cref="true"/> if the string starts with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_StartsWithCString_IgnoreCase(const String *str, const char *value, bool ignoreCase);

/// <summary>
/// Determines whether a <see cref="String"/> starts with the specified string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
///     <see cref="true"/> if the string starts with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_StartsWithString(const String *str, const String *value);

/// <summary>
/// Determines whether a <see cref="String"/> starts with the specified string, ignoring or honoring their case.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="ignoreCase">
///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
/// </param>
/// <returns>
///     <see cref="true"/> if the string starts with <paramref name="value"/>; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="value"/> is <see cref="null"/>.
/// </exception>
bool String_StartsWithString_IgnoreCase(const String *str, const String *value, bool ignoreCase);

/// <summary>
/// Returns a substring of a given <see cref="String"/>. The substring starts at a specified position and continues to
/// the end of the string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="startIndex">The starting position of the substring.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> that is equivalent to the specified substring of <paramref name="str"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Substring(const String *str, uintsize startIndex);

/// <summary>
/// Returns a substring of a given <see cref="String"/>. The substring starts at a specified position and has a
/// specified length.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="startIndex">The starting position of the substring.</param>
/// <param name="length">The length of the substring.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> that is equivalent to the specified substring of <paramref name="str"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="startIndex"/> + <paramref name="length"/> is greater than the length of <paramref name="str"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Substring_WithLength(const String *str, uintsize startIndex, uintsize length);

/// <summary>
/// Converts the value of a <see cref="String"/> to a null-terminated string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>
///     A pointer to a null-terminated string with the same value as the <see cref="String"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
char *String_ToCString(const String *str);

/// <summary>
/// Returns a copy of a given <see cref="String"/> converted to lowercase.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/> but in lowercase.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_ToLower(const String *str);

/// <summary>
/// Returns a copy of a given <see cref="String"/> converted to uppercase.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/> but in uppercase.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_ToUpper(const String *str);

/// <summary>
/// Returns a new <see cref="String"/> in which all leading and trailing occurrences of the specified characters from
/// <paramref name="str"/> are removed.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="trimChars">Null-terminated array of characters to remove, or <see cref="null"/>.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but with all leading and trailing
///     occurrences of the specified characters removed. If <paramref name="trimChars"/> is <see cref="null"/> or an
///     empty array, white-space characters are removed instead.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_Trim(const String *str, const char *trimChars);

/// <summary>
/// Returns a new <see cref="String"/> in which all trailing occurrences of the specified characters from
/// <paramref name="str"/> are removed.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="trimChars">Null-terminated array of characters to remove, or <see cref="null"/>.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but with all trailing occurrences
///     of the specified characters removed. If <paramref name="trimChars"/> is <see cref="null"/> or an
///     empty array, white-space characters are removed instead.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_TrimEnd(const String *str, const char *trimChars);

/// <summary>
/// Returns a new <see cref="String"/> in which all leading occurrences of the specified characters from
/// <paramref name="str"/> are removed.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="trimChars">Null-terminated array of characters to remove, or <see cref="null"/>.</param>
/// <returns>
///     A pointer to a new <see cref="String"/> equivalent to <paramref name="str"/>, but with all leading occurrences
///     of the specified characters removed. If <paramref name="trimChars"/> is <see cref="null"/> or an
///     empty array, white-space characters are removed instead.
/// </returns>
/// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *String_TrimStart(const String *str, const char *trimChars);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the characters of the given
/// <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through the characters of a <see cref="String"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
struct IEnumerator *String_GetEnumerator(const String *str);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/String.internal.h"
#endif

#endif
