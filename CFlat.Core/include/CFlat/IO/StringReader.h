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

//! @file StringReader.h

#ifndef CFLAT_CORE_IO_STRINGREADER_H
#define CFLAT_CORE_IO_STRINGREADER_H

#include "CFlat/Language/Integer.h"

#include "CFlat/String.h"

#include "CFlat/IO/TextReader.h"

namespace CFlat {
    /// <summary>
    /// Implements a reader that reads from a string of characters.
    /// </summary>
    class StringReader : public TextReader {
    private:
        String _value;
        uintsize _position;

    public:
        /// <summary>
        /// Initializes a <see cref="StringReader"/> so that reads from the given <see cref="String"/>.
        /// </summary>
        /// <param name="str">Pointer to a string.</param>
        StringReader(String str);

        /// <summary>
        /// Returns the next available character of a <see cref="StringReader"/>.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
        /// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        int Peek() const override;

        /// <summary>
        /// Returns the character at the given offset of a <see cref="StringReader"/>.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
        /// <param name="offset">The offset at which to peek.</param>
        /// <returns>
        ///     An integer representing the character at the given offset, or -1 if no more characters are available.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        int Peek(uintsize offset) const;

        /// <summary>
        /// Reads the next available character from the input string of a <see cref="StringReader"/> and advances the character
        /// position to the next character.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
        /// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        int Read() override;

        /// <summary>
        /// Reads a given maximum number of characters from the input string of a <see cref="StringReader"/> and advances the
        /// character position by the number of characters read.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
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
        /// </exception>>
        uintsize Read(char *buffer, uintsize offset, uintsize count) override;

        /// <summary>
        /// Advances the position of a <see cref="StringReader"/> by the given number of characters.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
        /// <param name="amount">The number of characters to skip.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        void Skip(uintsize amount);
    };
}

#endif
