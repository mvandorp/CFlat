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

//! @file CString.h

#ifndef CFLAT_CORE_CSTRING_H
#define CFLAT_CORE_CSTRING_H

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Pointers.h"

#include "CFlat/String.h"

namespace CFlat {
    class CString {
    public:
        /* Static class */
        CString() = delete;

        /* Constants */
        /// <summary>
        /// Represents an empty string.
        /// </summary>
        static const char * const Empty;

        /* Functions */
        /// <summary>
        /// Gets the length of a null-terminated string.
        ///
        /// The length does not include the terminating null character.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <returns>The length of the string.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        static uintsize Length(const char *str);

        /// <summary>
        /// Compares two given strings and returns an integer that indicates their relative position in the sort order.
        /// </summary>
        /// <param name="str1">Pointer to the first string, or <see cref="null"/>.</param>
        /// <param name="str2">Pointer to the second string, or <see cref="null"/>.</param>
        /// <returns>
        ///     Less than zero if <paramref name="str1"/> precedes <paramref name="str2"/> in the sort order;
        ///     Zero if <paramref name="str1"/> occurs in the same position as <paramref name="str2"/> in the sort order;
        ///     Greater than zero if <paramref name="str1"/> follows <paramref name="str2"/> in the sort order.
        /// </returns>
        static int Compare(const char *str1, const char *str2);

        /// <summary>
        /// Compares two given strings, ignoring or honoring their case, and returns an integer that indicates their relative
        /// position in the sort order.
        /// </summary>
        /// <param name="str1">Pointer to the first string, or <see cref="null"/>.</param>
        /// <param name="str2">Pointer to the second string, or <see cref="null"/>.</param>
        /// <param name="ignoreCase">
        ///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
        /// </param>
        /// <returns>
        ///     Less than zero if <paramref name="str1"/> precedes <paramref name="str2"/> in the sort order;
        ///     Zero if <paramref name="str1"/> occurs in the same position as <paramref name="str2"/> in the sort order;
        ///     Greater than zero if <paramref name="str1"/> follows <paramref name="str2"/> in the sort order.
        /// </returns>
        static int Compare(const char *str1, const char *str2, bool ignoreCase);

        /// <summary>
        /// Compares substrings of two given strings and returns an integer that indicates their relative position in the sort
        /// order.
        /// </summary>
        /// <param name="str1">Pointer to the first string, or <see cref="null"/>.</param>
        /// <param name="startIndex1">The position of the substring within <paramref name="str1"/>.</param>
        /// <param name="str2">Pointer to the second string, or <see cref="null"/>.</param>
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
        static int Compare(
            const char *str1,
            uintsize startIndex1,
            const char *str2,
            uintsize startIndex2,
            uintsize length);

        /// <summary>
        /// Compares substrings of two given strings, ignoring or honoring their case, and returns an integer that indicates
        /// their relative position in the sort order.
        /// </summary>
        /// <param name="str1">Pointer to the first string, or <see cref="null"/>.</param>
        /// <param name="startIndex1">The position of the substring within <paramref name="str1"/>.</param>
        /// <param name="str2">Pointer to the second string, or <see cref="null"/>.</param>
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
        static int Compare(
            const char *str1,
            uintsize startIndex1,
            const char *str2,
            uintsize startIndex2,
            uintsize length,
            bool ignoreCase);

        /// <summary>
        /// Determines whether a null-terminated string contains the specified character.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The character to seek.</param>
        /// <returns>
        ///     <see cref="true"/> if the string contains <paramref name="value"/>; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        static bool Contains(const char *str, char value);

        /// <summary>
        /// Determines whether a null-terminated string contains the specified string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     <see cref="true"/> if the string contains <paramref name="value"/>; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static bool Contains(const char *str, const char *value);

        /// <summary>
        /// Determines whether a null-terminated string contains the specified string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     <see cref="true"/> if the string contains <paramref name="value"/>; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static bool Contains(const char *str, const String &value);

        /// <summary>
        /// Returns a copy of a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <returns>A pointer to the copy of the string.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static unique_ptr<char[]> Copy(const char *str);

        /// <summary>
        /// Copies a number of characters at the given position of a null-terminated string to the given array.
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
        static void CopyTo(
            const char *source,
            uintsize sourceIndex,
            char *destination,
            uintsize destinationIndex,
            uintsize count);

        /// <summary>
        /// Determines whether a null-terminated string ends with the specified character.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The character to seek.</param>
        /// <returns>
        ///     <see cref="true"/> if the string ends with <paramref name="value"/>; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        static bool EndsWith(const char *str, char value);

        /// <summary>
        /// Determines whether a null-terminated string ends with the specified string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     <see cref="true"/> if the string ends with <paramref name="value"/>; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static bool EndsWith(const char *str, const char *value);

        /// <summary>
        /// Determines whether a null-terminated string ends with the specified string, ignoring or honoring case.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static bool EndsWith(const char *str, const char *value, bool ignoreCase);

        /// <summary>
        /// Determines whether a null-terminated string ends with the specified string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     <see cref="true"/> if the string ends with <paramref name="value"/>; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static bool EndsWith(const char *str, const String &value);

        /// <summary>
        /// Determines whether a null-terminated string ends with the specified string, ignoring or honoring case.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static bool EndsWith(const char *str, const String &value, bool ignoreCase);

        /// <summary>
        /// Determines whether the two given strings have the same value.
        /// </summary>
        /// <param name="str1">Pointer to the first string, or <see cref="null"/>.</param>
        /// <param name="str2">Pointer to the second string, or <see cref="null"/>.</param>
        /// <returns>
        ///     <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
        ///     otherwise, <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are
        ///     <see cref="null"/>, the method returns <see cref="true"/>.
        /// </returns>
        static bool Equals(const char *str1, const char *str2);

        /// <summary>
        /// Determines whether two given strings have the same value, ignoring or honoring their case.
        /// </summary>
        /// <param name="str1">Pointer to the first string, or <see cref="null"/>.</param>
        /// <param name="str2">Pointer to the second string, or <see cref="null"/>.</param>
        /// <param name="ignoreCase">
        ///     <see cref="true"/> to ignore case during the comparison; otherwise <see cref="false"/>.
        /// </param>
        /// <returns>
        ///     <see cref="true"/> if the value of <paramref name="str1"/> is the same as the value of <paramref name="str2"/>;
        ///     otherwise, <see cref="false"/>. If both <paramref name="str1"/> and <paramref name="str2"/> are
        ///     <see cref="null"/>, the method returns <see cref="true"/>.
        /// </returns>
        static bool Equals(const char *str1, const char *str2, bool ignoreCase);

        /// <summary>
        /// Returns the hash code for a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <returns>A 32-bit signed integer hash code.</returns>
        /// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        static int GetHashCode(const char *str);

        /// <summary>
        /// Returns the index of the first occurance of the specified character in a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The character to seek.</param>
        /// <returns>
        ///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        static uintsize IndexOf(const char *str, char value);

        /// <summary>
        /// Returns the index of the first occurance of the specified character in a null-terminated string.
        /// The search starts at a given character position.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The character to seek.</param>
        /// <param name="startIndex">The search starting position.</param>
        /// <returns>
        ///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
        /// </exception>
        static uintsize IndexOf(const char *str, char value, uintsize startIndex);

        /// <summary>
        /// Returns the index of the first occurance of the specified character in a null-terminated string.
        /// The search starts at a given character position and examims a given number of character positions.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize IndexOf(const char *str, char value, uintsize startIndex, uintsize count);

        /// <summary>
        /// Returns the index of the first occurance of the specified string in a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static uintsize IndexOf(const char *str, const char *value);

        /// <summary>
        /// Returns the index of the first occurance of the specified string in a null-terminated string.
        /// The search starts at a given character position.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize IndexOf(const char *str, const char *value, uintsize startIndex);

        /// <summary>
        /// Returns the index of the first occurance of the specified string in a null-terminated string.
        /// The search starts at a given character position and examims a given number of character positions.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize IndexOf(const char *str, const char *value, uintsize startIndex, uintsize count);

        /// <summary>
        /// Returns the index of the first occurance of the specified string in a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static uintsize IndexOf(const char *str, const String &value);

        /// <summary>
        /// Returns the index of the first occurance of the specified string in a null-terminated string.
        /// The search starts at a given character position.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize IndexOf(const char *str, const String &value, uintsize startIndex);

        /// <summary>
        /// Returns the index of the first occurance of the specified string in a null-terminated string.
        /// The search starts at a given character position and examims a given number of character positions.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize IndexOf(
            const char *str,
            const String &value,
            uintsize startIndex,
            uintsize count);

        /// <summary>
        /// Returns the index of the first occurance of any of the specified character in a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
        /// <returns>
        ///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="anyOf"/> is <see cref="null"/>.
        /// </exception>
        static uintsize IndexOfAny(const char *str, const char *anyOf);

        /// <summary>
        /// Returns the index of the first occurance of any of the specified character in a null-terminated string.
        /// The search starts at a given character position.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize IndexOfAny(const char *str, const char *anyOf, uintsize startIndex);

        /// <summary>
        /// Returns the index of the first occurance of any of the specified character in a null-terminated string.
        /// The search starts at a given character position and examims a given number of character positions.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize IndexOfAny(const char *str, const char *anyOf, uintsize startIndex, uintsize count);

        /// <summary>
        /// Determines whether a null-terminated string is <see cref="null"/> or empty.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <returns>
        ///     <see cref="true"/> if <paramref name="str"/> is <see cref="null"/> or empty; otherwise, <see cref="false"/>.
        /// </returns>
        static bool IsNullOrEmpty(const char *str);

        /// <summary>
        /// Determines whether a null-terminated string is <see cref="null"/>, empty, or consists only of white-space
        /// characters.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <returns>
        ///     <see cref="true"/> if <paramref name="str"/> is <see cref="null"/>, empty, or consists only of white-space
        ///     characters; otherwise, <see cref="false"/>.
        /// </returns>
        static bool IsNullOrWhiteSpace(const char *str);

        /// <summary>
        /// Returns the index of the last occurance of the specified character in a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The character to seek.</param>
        /// <returns>
        ///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        static uintsize LastIndexOf(const char *str, char value);

        /// <summary>
        /// Returns the index of the last occurance of the specified character in a null-terminated string.
        /// The search starts at a given character position and proceeds backward toward the beginning of the string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize LastIndexOf(const char *str, char value, uintsize startIndex);

        /// <summary>
        /// Returns the index of the last occurance of the specified character in a null-terminated string.
        /// The search starts at a given character position and proceeds backward toward the beginning of the string for a
        /// given number of character positions.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize LastIndexOf(const char *str, char value, uintsize startIndex, uintsize count);

        /// <summary>
        /// Returns the index of the last occurance of the specified string in a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static uintsize LastIndexOf(const char *str, const char *value);

        /// <summary>
        /// Returns the index of the last occurance of the specified string in a null-terminated string.
        /// The search starts at a given character position and proceeds backward toward the beginning of the string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize LastIndexOf(const char *str, const char *value, uintsize startIndex);

        /// <summary>
        /// Returns the index of the last occurance of the specified string in a null-terminated string.
        /// The search starts at a given character position and proceeds backward toward the beginning of the string for a
        /// given number of character positions.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize LastIndexOf(const char *str, const char *value, uintsize startIndex, uintsize count);

        /// <summary>
        /// Returns the index of the last occurance of the specified string in a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static uintsize LastIndexOf(const char *str, const String &value);

        /// <summary>
        /// Returns the index of the last occurance of the specified string in a null-terminated string.
        /// The search starts at a given character position and proceeds backward toward the beginning of the string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize LastIndexOf(const char *str, const String &value, uintsize startIndex);

        /// <summary>
        /// Returns the index of the last occurance of the specified string in a null-terminated string.
        /// The search starts at a given character position and proceeds backward toward the beginning of the string for a
        /// given number of character positions.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize LastIndexOf(
            const char *str,
            const String &value,
            uintsize startIndex,
            uintsize count);

        /// <summary>
        /// Returns the index of the last occurance of any of the specified character in a null-terminated string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="anyOf">A null-terminated array of characters containing one or more characters to seek.</param>
        /// <returns>
        ///     The index of <paramref name="value"/> if that character is found, or <see cref="InvalidIndex"/> if it is not.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="anyOf"/> is <see cref="null"/>.
        /// </exception>
        static uintsize LastIndexOfAny(const char *str, const char *anyOf);

        /// <summary>
        /// Returns the index of the last occurance of any of the specified character in a null-terminated string.
        /// The search starts at a given character position and proceeds backward toward the beginning of the string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize LastIndexOfAny(const char *str, const char *anyOf, uintsize startIndex);

        /// <summary>
        /// Returns the index of the last occurance of any of the specified character in a null-terminated string.
        /// The search starts at a given character position and proceeds backward toward the beginning of the string for a
        /// given number of character positions.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static uintsize LastIndexOfAny(const char *str, const char *anyOf, uintsize startIndex, uintsize count);

        /// <summary>
        /// Returns a new null-terminated string in which all the characters in <paramref name="str"/>, beginning at a specified
        /// position and continuing through the last position, have been deleted.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="startIndex">The position where to begin deleting characters.</param>
        /// <returns>
        ///     A pointer to a new null-terminated string equivalent to <paramref name="str"/>, but with the specified
        ///     characters removed.
        /// </returns>
        /// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="ArgumentOutOfRangeException">
        ///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static unique_ptr<char[]> Remove(const char *str, uintsize startIndex);

        /// <summary>
        /// Returns a new null-terminated string in which a specified number of characters in <paramref name="str"/>, beginning
        /// at a specified position, have been deleted.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="startIndex">The position where to begin deleting characters.</param>
        /// <param name="count">The number of characters to delete.</param>
        /// <returns>
        ///     A pointer to a new null-terminated string equivalent to <paramref name="str"/>, but with the specified
        ///     characters removed.
        /// </returns>
        /// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="ArgumentOutOfRangeException">
        ///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="str"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static unique_ptr<char[]> Remove(const char *str, uintsize startIndex, uintsize count);

        /// <summary>
        /// Returns a new null-terminated string in which all occurrences of a specified character in <paramref name="str"/> are
        /// replaced with another specified character.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="oldChar">The character to be replaced.</param>
        /// <param name="newChar">The character to replace all occurrences of <paramref name="oldChar"/>.</param>
        /// <returns>
        ///     A pointer to a new null-terminated string equivalent to <paramref name="str"/>, but with all occurrences of
        ///     <paramref name="oldChar"/> replaced by <paramref name="newChar"/>.
        /// </returns>
        /// <exception cref="ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static unique_ptr<char[]> Replace(const char *str, char oldValue, char newValue);

        /// <summary>
        /// Returns a new null-terminated string in which all occurrences of a specified string in <paramref name="str"/> are
        /// replaced with another specified string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="oldValue">The string to be replaced.</param>
        /// <param name="newValue">The string to replace all occurrences of <paramref name="newValue"/>.</param>
        /// <returns>
        ///     A pointer to a new null-terminated string equivalent to <paramref name="str"/>, but with all occurrences of
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
        static unique_ptr<char[]> Replace(const char *str, const char *oldValue, const char *newValue);

        /// <summary>
        /// Returns a new null-terminated string in which all occurrences of a specified string in <paramref name="str"/> are
        /// replaced with another specified string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="oldValue">The string to be replaced.</param>
        /// <param name="newValue">The string to replace all occurrences of <paramref name="newValue"/>.</param>
        /// <returns>
        ///     A pointer to a new null-terminated string equivalent to <paramref name="str"/>, but with all occurrences of
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
        static unique_ptr<char[]> Replace(const char *str, const String &oldValue, const String &newValue);

        /// <summary>
        /// Determines whether a null-terminated string starts with the character.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The character to seek.</param>
        /// <returns>
        ///     <see cref="true"/> if the string starts with <paramref name="value"/>; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        static bool StartsWith(const char *str, char value);

        /// <summary>
        /// Determines whether a null-terminated string starts with the specified string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     <see cref="true"/> if the string starts with <paramref name="value"/>; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static bool StartsWith(const char *str, const char *value);

        /// <summary>
        /// Determines whether a null-terminated string starts with the specified string, ignoring or honoring their case.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static bool StartsWith(const char *str, const char *value, bool ignoreCase);

        /// <summary>
        /// Determines whether a null-terminated string starts with the specified string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="value">The string to seek.</param>
        /// <returns>
        ///     <see cref="true"/> if the string starts with <paramref name="value"/>; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="str"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="value"/> is <see cref="null"/>.
        /// </exception>
        static bool StartsWith(const char *str, const String &value);

        /// <summary>
        /// Determines whether a null-terminated string starts with the specified string, ignoring or honoring their case.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static bool StartsWith(const char *str, const String &value, bool ignoreCase);

        /// <summary>
        /// Returns a substring of a given null-terminated string. The substring starts at a specified position and continues to
        /// the end of the string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="startIndex">The starting position of the substring.</param>
        /// <returns>
        ///     A pointer to a new null-terminated string that is equivalent to the specified substring of
        ///     <paramref name="str"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static unique_ptr<char[]> CSubstring(const char *str, uintsize startIndex);

        /// <summary>
        /// Returns a substring of a given null-terminated string. The substring starts at a specified position and has a
        /// specified length.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="startIndex">The starting position of the substring.</param>
        /// <param name="length">The length of the substring.</param>
        /// <returns>
        ///     A pointer to a new null-terminated string that is equivalent to the specified substring of
        ///     <paramref name="str"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="startIndex"/> + <paramref name="length"/> is greater than the length of <paramref name="str"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static unique_ptr<char[]> CSubstring(const char *str, uintsize startIndex, uintsize length);

        /// <summary>
        /// Returns a substring of a given null-terminated string. The substring starts at a specified position and continues to
        /// the end of the string.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <param name="startIndex">The starting position of the substring.</param>
        /// <returns>
        ///     A pointer to a new <see cref="String"/> that is equivalent to the specified substring of <paramref name="str"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="startIndex"/> is greater than the length of <paramref name="str"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String Substring(const char *str, uintsize startIndex);

        /// <summary>
        /// Returns a substring of a given null-terminated string. The substring starts at a specified position and has a
        /// specified length.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
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
        static String Substring(const char *str, uintsize startIndex, uintsize length);

        /// <summary>
        /// Converts the value of a null-terminated string to a <see cref="String"/>.
        /// </summary>
        /// <param name="str">Pointer to a null-terminated string.</param>
        /// <returns>
        ///     A pointer to a <see cref="String"/> with the same value as the null-terminated string.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(const char *str);
    };
}

#endif
