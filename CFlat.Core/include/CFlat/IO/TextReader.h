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

//! @file TextReader.h

#ifndef CFLAT_CORE_IO_TEXTREADER_H
#define CFLAT_CORE_IO_TEXTREADER_H

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Pointers.h"
#include "CFlat/Language/VarArgs.h"

namespace CFlat {
    class String;

    /// <summary>
    /// Base class for objects that can read sequences of characters.
    /// </summary>
    class TextReader {
    private:
        class NullReader;

    public:
        virtual ~TextReader();

        /// <summary>
        /// A <see cref="TextReader"/> with no backing store.
        /// </summary>
        static unique_ptr<TextReader, NoOpDeleter<TextReader>> Null();

        /// <summary>
        /// Returns the next available character of a <see cref="TextReader"/>.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
        /// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual int Peek() const = 0;

        /// <summary>
        /// Reads the next available character from the input source of a <see cref="TextReader"/> and advances the character
        /// position to the next character.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
        /// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual int Read() = 0;

        /// <summary>
        /// Reads a given maximum number of characters from the input source of a <see cref="TextReader"/> and advances the
        /// character position by the number of characters read.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
        /// <param name="buffer">The array to which the characters should be read.</param>
        /// <param name="offset">
        ///     The offset in <paramref name="buffer"/> at which to begin storing characters read from
        ///     <paramref name="reader"/>.
        /// </param>
        /// <param name="count">The maximum number of characters to read.</param>
        /// <returns>
        ///     The total number of characters read into the buffer. This can be less than the number of bytes requested if
        ///     that many characters are currently not available, or zero if all characters have been read.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="reader"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="buffer"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual uintsize Read(char *buffer, uintsize offset, uintsize count) = 0;

        /// <summary>
        /// Reads a line of characters from the input source of a <see cref="TextReader"/> and returns the data as a
        /// <see cref="String"/>.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
        /// <returns>
        ///     A pointer to a <see cref="String"/> containing the next line of the reader, or <see cref="null"/> if all
        ///     characters have been read.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        String ReadLine();

        /// <summary>
        /// Reads all characters from the input source of a <see cref="TextReader"/> and returns the data as a
        /// <see cref="String"/>.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
        /// <returns>
        ///     A pointer to a <see cref="String"/> containing all remaining characters of the reader, or <see cref="null"/>
        ///     if all characters have been read.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        String ReadToEnd();
    };
}

#endif
