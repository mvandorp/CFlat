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

#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/VarArgs.h"

/* Types */
/// <summary>
/// Represents text as an immutable string of characters.
/// </summary>
typedef struct String String;

/* Constants */
/// <summary>
/// Represents an empty string.
/// </summary>
extern const String * const String_Empty;

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
/// Initializes a <see cref="String"/> to the value represented by the given null-terminated string.
/// </summary>
/// <param name="str">Pointer to an uninitialized <see cref="String"/>.</param>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void String_Constructor(String *str, const char *value);

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
/// Determines whether two given strings have the same value.
/// </summary>
/// <param name="str1">Pointer to the first  <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second  <see cref="String"/>, or <see cref="null"/>.</param>
/// <returns>
///     <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
///     otherwise, <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are
///     <see cref="null"/>, the method returns <see cref="true"/>.
/// </returns>
bool String_Equals(const String *str1, const String *str2);

/// <summary>
/// Determines whether two given strings have the same value.
/// </summary>
/// <param name="str1">Pointer to the first  <see cref="String"/>, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second  <see cref="String"/>, or <see cref="null"/>.</param>
/// <returns>
///     <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
///     otherwise, <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are
///     <see cref="null"/>, the method returns <see cref="true"/>.
/// </returns>
bool String_EqualsCString(const String *str1, const char *str2);

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
String *String_FormatCStringV(const char *format, VarArgs args);

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
String *String_FormatStringV(const String *format, VarArgs args);

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
/// Converts the value of a <see cref="String"/> to a null-terminated string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>
///     A pointer to a null-terminated string with the same value as the <see cref="String"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
char *String_ToCString(const String *str);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/String.internal.h"
#endif

#endif
