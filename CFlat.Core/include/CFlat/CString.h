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
 * @file CString.h
 */

#ifndef CFLAT_CORE_CSTRING_H
#define CFLAT_CORE_CSTRING_H

#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
typedef struct String String;

/* Functions */
/// <summary>
/// Gets the length of a null-terminated string.
///
/// The length does not include the terminating null character.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <returns>The length of the string.</returns>
uintsize CString_Length(const char *str);

/// <summary>
/// Returns a pointer to a new null-terminated string that is a copy of the given string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <returns>
/// On success, returns the pointer to the copy of the string.
///
/// On failure, returns <see cref="null"/>.
/// </returns>
char *CString_Copy(const char *str);

/// <summary>
/// Determines whether the two given strings have the same value.
/// </summary>
/// <param name="str">Pointer to the first string, or <see cref="null"/>.</param>
/// <param name="value">Pointer to the second string, or <see cref="null"/>.</param>
/// <returns>
/// <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
/// otherwise <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are <see cref="null"/>,
/// the method returns <see cref="true"/>.
/// </returns>
bool CString_Equals(const char *str1, const char *str2);

/// <summary>
/// Returns the index of the first occurance of the specified character in the given string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The character to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOf(const char *str, char value);

/// <summary>
/// Returns the index of the first occurance of the specified character in the given string.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOf_Offset(const char *str, char value, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of the specified character in the given string.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOf_Substring(const char *str, char value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the first occurance of any of the specified character in the given string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">A null-terminated array of characters containing one or more characters to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOfAny(const char *str, const char *anyOf);

/// <summary>
/// Returns the index of the first occurance of any of the specified character in the given string.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOfAny_Offset(const char *str, const char *anyOf, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of any of the specified character in the given string.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOfAny_Substring(const char *str, const char *anyOf, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOfCString(const char *str, const char *value);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given string.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOfCString_Offset(const char *str, const char *value, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given string.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOfCString_Substring(const char *str, const char *value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOfString(const char *str, const String *value);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given string.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOfString_Offset(const char *str, const String *value, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given string.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_IndexOfString_Substring(const char *str, const String *value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the last occurance of the specified character in the given string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The character to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOf(const char *str, char value);

/// <summary>
/// Returns the index of the last occurance of the specified character in the given string.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOf_Offset(const char *str, char value, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of the specified character in the given string.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOf_Substring(const char *str, char value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the last occurance of any of the specified character in the given string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">A null-terminated array of characters containing one or more characters to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOfAny(const char *str, const char *anyOf);

/// <summary>
/// Returns the index of the last occurance of any of the specified character in the given string.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOfAny_Offset(const char *str, const char *anyOf, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of any of the specified character in the given string.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOfAny_Substring(const char *str, const char *anyOf, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOfCString(const char *str, const char *value);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given string.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOfCString_Offset(const char *str, const char *value, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given string.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOfCString_Substring(const char *str, const char *value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOfString(const char *str, const String *value);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given string.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOfString_Offset(const char *str, const String *value, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given string.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a null-terminated string.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize CString_LastIndexOfString_Substring(
    const char *str,
    const String *value,
    uintsize startIndex,
    uintsize count);

#endif
