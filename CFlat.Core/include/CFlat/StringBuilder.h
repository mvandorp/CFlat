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
#include "CFlat/Language/Pointers.h"
#include "CFlat/Language/VarArgs.h"

namespace CFlat {
    /* Forward declarations */
    class String;

    /* Types */
    /// <summary>
    /// Represents a mutable string of characters.
    /// </summary>
    class StringBuilder {
    private:
        mutable unique_ptr<char[]> _buffer;
        mutable uintsize _capacity;
        uintsize _length;

        void EnsureBufferIsString() const;
        void EnsureCapacity(uintsize minCapacity) const;

    public:
        /// <summary>
        /// Initializes a <see cref="StringBuilder"/>.
        /// </summary>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        StringBuilder();

        StringBuilder(const StringBuilder &sb);

        StringBuilder(StringBuilder &&sb);

        /// <summary>
        /// Initializes a <see cref="StringBuilder"/> with the given capacity.
        /// </summary>
        /// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        StringBuilder(uintsize capacity);

        /// <summary>
        /// Initializes a <see cref="StringBuilder"/> with the given initial value.
        /// </summary>
        /// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        StringBuilder(const char *value);

        /// <summary>
        /// Initializes a <see cref="StringBuilder"/> with the given initial value and capacity.
        /// </summary>
        /// <param name="value">Pointer to a null-terminated string used as the initial value.</param>
        /// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        StringBuilder(const char *value, uintsize capacity);

        /// <summary>
        /// Initializes a <see cref="StringBuilder"/> with the given initial value.
        /// </summary>
        /// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        StringBuilder(const String &value);

        /// <summary>
        /// Initializes a <see cref="StringBuilder"/> with the given initial value and capacity.
        /// </summary>
        /// <param name="value">Pointer to a <see cref="String"/> used as the initial value.</param>
        /// <param name="capacity">The initial capacity of the <see cref="StringBuilder"/>.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        StringBuilder(const String &value, uintsize capacity);

        StringBuilder &operator=(const StringBuilder &sb);

        StringBuilder &operator=(StringBuilder &&sb);

        static String ToString(const StringBuilder &sb);

        static String ToString(StringBuilder &&sb);

        static unique_ptr<char[]> ToCString(const StringBuilder &sb);

        static unique_ptr<char[]> ToCString(StringBuilder &&sb);

        char *GetData() const;

        /// <summary>
        /// Gets the length of a <see cref="StringBuilder"/>.
        /// </summary>
        /// <returns>The length of the <see cref="StringBuilder"/>.</returns>
        uintsize GetLength() const;

        /// <summary>
        /// Gets the capacity of a <see cref="StringBuilder"/>.
        /// </summary>
        /// <returns>The capacity of the <see cref="StringBuilder"/>.</returns>
        uintsize GetCapacity() const;

        /// <summary>
        /// Sets the capacity of a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="capacity">The new capacity of the <see cref="StringBuilder"/>.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="capacity"/> is less than the length of <paramref name="sb"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void SetCapacity(uintsize capacity) const;

        /// <summary>
        /// Appends the given character to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The character to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(char value);

        /// <summary>
        /// Appends the contents of the given buffer to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="buffer">An array of characters.</param>
        /// <param name="offset">The starting position in <paramref name="buffer"/>.</param>
        /// <param name="count">The number of characters to append.</param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="buffer"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(const char *buffer, uintsize offset, uintsize count);

        /// <summary>
        /// Appends the given string to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">Pointer to the string to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(const char *value);

        /// <summary>
        /// Appends the given string to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">Pointer to the string to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(const String &value);

        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(int value);

        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(intmax value);

#ifdef CFLAT_INTPTR
        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        //void Append(intptr value);
#endif

        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        //void Append(intfsize value);

        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(uint value);

        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(uintmax value);

#ifdef CFLAT_UINTPTR
        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        //void Append(uintptr value);
#endif

        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        //void Append(uintsize value);

        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(float value);

        /// <summary>
        /// Appends the string representation of the given number to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">The value to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Append(double value);

        /// <summary>
        /// Appends a string that is formatted according to the given format string, to a <see cref="StringBuilder"/>.
        /// Each format specifier replaced with a string representation of the corresponding argument.
        /// </summary>
        /// <param name="format">Pointer to a format string.</param>
        /// <param name="...">Objects to format according to the format specifiers in the format string.</param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="format"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void AppendFormat(const char *format, ...);

        /// <summary>
        /// Appends a string that is formatted according to the given format string, to a <see cref="StringBuilder"/>.
        /// Each format specifier replaced with a string representation of the corresponding argument.
        /// </summary>
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
        void AppendFormatVA(const char *format, VarArgsList args);

        /// <summary>
        /// Appends a string that is formatted according to the given format string, to a <see cref="StringBuilder"/>.
        /// Each format specifier replaced with a string representation of the corresponding argument.
        /// </summary>
        /// <param name="format">Pointer to a format string.</param>
        /// <param name="...">Objects to format according to the format specifiers in the format string.</param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="format"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void AppendFormat(String format, ...);

        /// <summary>
        /// Appends a string that is formatted according to the given format string, to a <see cref="StringBuilder"/>.
        /// Each format specifier replaced with a string representation of the corresponding argument.
        /// </summary>
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
        void AppendFormatVA(const String &format, VarArgsList args);

        /// <summary>
        /// Appends a new line to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void AppendLine();

        /// <summary>
        /// Appends the given string followed by a new line to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">Pointer to the string to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void AppendLine(const char *value);

        /// <summary>
        /// Appends the given string followed by a new line to a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="value">Pointer to the string to append.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void AppendLine(const String &value);

        /// <summary>
        /// Removes all characters from the specified <see cref="StringBuilder"/>.
        /// </summary>
        void Clear();

        /// <summary>
        /// Inserts the given character into a <see cref="StringBuilder"/> at the given index.
        /// </summary>
        /// <param name="index">The position in <paramref name="sb"/> where insertion begins.</param>
        /// <param name="value">The character to insert.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is greater than the length of <paramref name="sb"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Insert(uintsize index, char value);

        /// <summary>
        /// Inserts the contents of the given buffer into a <see cref="StringBuilder"/> at the given index.
        /// </summary>
        /// <param name="index">The position in <paramref name="sb"/> where insertion begins.</param>
        /// <param name="buffer">An array of characters.</param>
        /// <param name="offset">The starting position in <paramref name="buffer"/>.</param>
        /// <param name="count">The number of characters to insert.</param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="buffer"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is greater than the length of <paramref name="sb"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Insert(uintsize index, const char *buffer, uintsize offset, uintsize count);

        /// <summary>
        /// Inserts the given string into a <see cref="StringBuilder"/> at the given index.
        /// </summary>
        /// <param name="index">The position in <paramref name="sb"/> where insertion begins.</param>
        /// <param name="value">Pointer to the string to insert.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is greater than the length of <paramref name="sb"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Insert(uintsize index, const char *value);

        /// <summary>
        /// Inserts the given string into a <see cref="StringBuilder"/> at the given index.
        /// </summary>
        /// <param name="index">The position in <paramref name="sb"/> where insertion begins.</param>
        /// <param name="value">Pointer to the string to insert.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is greater than the length of <paramref name="sb"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Insert(uintsize index, const String &value);

        /// <summary>
        /// Removes the given range of characters from a <see cref="StringBuilder"/>.
        /// </summary>
        /// <param name="startIndex">The position where to start removing characters.</param>
        /// <param name="count">The number of characters to remove.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="startIndex"/> + <paramref name="count"/> is greater than the length of <paramref name="sb"/>.
        /// </exception>
        void Remove(uintsize startIndex, uintsize count);

        /// <summary>
        /// Replaces all occurrences of a specified character in a <see cref="StringBuilder"/> with another specified character.
        /// </summary>
        /// <param name="oldChar">The character to be replaced.</param>
        /// <param name="newChar">The character to replace all occurrences of <paramref name="oldChar"/>.</param>
        /// <exception cref="ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        void Replace(char oldValue, char newValue);

        /// <summary>
        /// Replaces all occurrences of a specified string in a <see cref="StringBuilder"/> with another specified string.
        /// </summary>
        /// <param name="oldValue">The string to be replaced.</param>
        /// <param name="newValue">The string to replace all occurrences of <paramref name="newValue"/>.</param>
        /// <exception cref="ArgumentNullException">
        ///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="oldValue"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="ArgumentException">
        ///     <paramref name="oldValue"/> is the empty string ("").
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Replace(const char *oldValue, const char *newValue);

        /// <summary>
        /// Replaces all occurrences of a specified string in a <see cref="StringBuilder"/> with another specified string.
        /// </summary>
        /// <param name="oldValue">The string to be replaced.</param>
        /// <param name="newValue">The string to replace all occurrences of <paramref name="newValue"/>.</param>
        /// <exception cref="ArgumentNullException">
        ///     <paramref name="sb"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="oldValue"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="ArgumentException">
        ///     <paramref name="oldValue"/> is the empty string ("").
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void Replace(const String &oldValue, const String &newValue);

        /// <summary>
        /// Converts the value of a <see cref="StringBuilder"/> to a <see cref="String"/>.
        /// </summary>
        /// <returns>
        ///     A pointer to a <see cref="String"/> with the same value as the <see cref="StringBuilder"/>.
        /// </returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        String ToString() const;

        /// <summary>
        /// Converts the value of a <see cref="StringBuilder"/> to a null-terminated string.
        /// </summary>
        /// <returns>
        ///     A pointer to a null-terminated string with the same value as the <see cref="StringBuilder"/>.
        /// </returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        unique_ptr<char[]> ToCString() const;
    };
}

#endif
