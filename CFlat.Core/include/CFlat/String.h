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
/// Gets the character at the given index of the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="index">A position within the string.</param>
/// <returns>The character at the given index of the given <see cref="String"/>.</returns>
char String_GetCharAt(const String *str, uintsize index);

/// <summary>
/// Gets the pointer to the null-terminated string representing the value of the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>A pointer to the null-terminated string representing the value of the string.</returns>
const char *String_GetCString(const String *str);

/// <summary>
/// Gets the length of the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>The length of the string.</returns>
uintsize String_GetLength(const String *str);

/// <summary>
/// Determines whether the two given strings have the same value.
/// </summary>
/// <param name="str1">Pointer to the first string, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second string, or <see cref="null"/>.</param>
/// <returns>
/// <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
/// otherwise <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are <see cref="null"/>,
/// the method returns <see cref="true"/>.
/// </returns>
bool String_Equals(const String *str1, const String *str2);

/// <summary>
/// Determines whether the two given strings have the same value.
/// </summary>
/// <param name="str1">Pointer to the first string, or <see cref="null"/>.</param>
/// <param name="str2">Pointer to the second string, or <see cref="null"/>.</param>
/// <returns>
/// <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
/// otherwise <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are <see cref="null"/>,
/// the method returns <see cref="true"/>.
/// </returns>
bool String_EqualsCString(const String *str1, const char *str2);

/// <summary>
/// Returns a pointer to a new <see cref="String"/> that is formatted according to the given format string, with each
/// format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
/// A variable argument list containing the objects to format according to the format specifiers in the format string.
/// </param>
/// <returns>A pointer to a new <see cref="String"/> that is formatted according to the given format string.</returns>
String *String_Format(const String *format, VarArgs args);

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
/// Returns the index of the first occurance of the specified character in the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOf(const String *str, char value);

/// <summary>
/// Returns the index of the first occurance of the specified character in the given <see cref="String"/>.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOf_Offset(const String *str, char value, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of the specified character in the given <see cref="String"/>.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOf_Substring(const String *str, char value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the first occurance of any of the specified character in the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOfAny(const String *str, const char *anyOf);

/// <summary>
/// Returns the index of the first occurance of any of the specified character in the given <see cref="String"/>.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOfAny_Offset(const String *str, const char *anyOf, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of any of the specified character in the given <see cref="String"/>.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOfAny_Substring(const String *str, const char *anyOf, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOfCString(const String *str, const char *value);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given <see cref="String"/>.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOfCString_Offset(const String *str, const char *value, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given <see cref="String"/>.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOfCString_Substring(const String *str, const char *value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOfString(const String *str, const String *value);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given <see cref="String"/>.
/// The search starts at a given character position.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOfString_Offset(const String *str, const String *value, uintsize startIndex);

/// <summary>
/// Returns the index of the first occurance of the specified string in the given <see cref="String"/>.
/// The search starts at a given character position and examims a given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_IndexOfString_Substring(const String *str, const String *value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the last occurance of the specified character in the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOf(const String *str, char value);

/// <summary>
/// Returns the index of the last occurance of the specified character in the given <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOf_Offset(const String *str, char value, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of the specified character in the given <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The character to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOf_Substring(const String *str, char value, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the last occurance of any of the specified character in the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOfAny(const String *str, const char *anyOf);

/// <summary>
/// Returns the index of the last occurance of any of the specified character in the given <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOfAny_Offset(const String *str, const char *anyOf, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of any of the specified character in the given <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOfAny_Substring(const String *str, const char *anyOf, uintsize startIndex, uintsize count);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOfCString(const String *str, const char *value);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOfCString_Offset(const String *str, const char *value, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOfCString_Substring(
    const String *str,
    const char *value,
    uintsize startIndex,
    uintsize count);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOfString(const String *str, const String *value);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOfString_Offset(const String *str, const String *value, uintsize startIndex);

/// <summary>
/// Returns the index of the last occurance of the specified string in the given <see cref="String"/>.
/// The search starts at a given character position and proceeds backward toward the beginning of the string for a
/// given number of character positions.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <param name="value">The string to seek.</param>
/// <param name="startIndex">The search starting position.</param>
/// <param name="count">The number of character positions to examine.</param>
/// <returns>
/// The index of <paramref name="value"/> if that character is found, otherwise <see cref="InvalidIndex"/>.
/// </returns>
uintsize String_LastIndexOfString_Substring(
    const String *str,
    const String *value,
    uintsize startIndex,
    uintsize count);

/// <summary>
/// Converts the value of the given <see cref="String"/> to a null-terminated string.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>
/// A pointer to a null-terminated string with the same value as the given <see cref="String"/>.
/// </returns>
char *String_ToCString(const String *str);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/String.internal.h"
#endif

#endif
