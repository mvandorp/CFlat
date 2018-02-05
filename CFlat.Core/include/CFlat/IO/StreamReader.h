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

//! @file StreamReader.h

#ifndef CFLAT_CORE_IO_STREAMREADER_H
#define CFLAT_CORE_IO_STREAMREADER_H

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Pointers.h"

#include "CFlat/IO/TextReader.h"

namespace CFlat {
    /* Forward declarations */
    class Stream;
    class String;

    /* Types */
    /// <summary>
    /// Implements a <see cref="TextReader"/> for reading characters from a <see cref="Stream"/>.
    /// </summary>
    class StreamReader : public TextReader {
    private:
        unique_ptr<Stream> _stream;
        mutable unique_ptr<byte[]> _buffer;
        mutable uintsize _bufferPosition;
        mutable uintsize _bufferLength;

        uintsize ReadInternalBuffer() const;

    public:
        StreamReader() = delete;

        StreamReader(const StreamReader &reader) = delete;

        StreamReader(StreamReader &&reader);

        /// <summary>
        /// Allocates and initializes a new <see cref="StreamReader"/>.
        /// </summary>
        /// <remarks>
        ///     The lifetime of the <see cref="StreamReader"/> should be managed with retain() and release().
        /// </remarks>
        /// <param name="stream">Pointer to the <see cref="Stream"/> to read from.</param>
        /// <returns>A pointer to the newly allocated stream reader.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        StreamReader(unique_ptr<Stream> &&stream);

        /// <summary>
        /// Allocates and initializes a new <see cref="StreamReader"/> for the specified file.
        /// </summary>
        /// <remarks>
        ///     The lifetime of the <see cref="StreamWriter"/> should be managed with retain() and release().
        /// </remarks>
        /// <param name="path">The file path to read from.</param>
        /// <returns>A pointer to the newly allocated stream reader.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="path"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        StreamReader(const String &path);

        /// <summary>
        /// Allocates and initializes a new <see cref="StreamReader"/> for the specified file.
        /// </summary>
        /// <remarks>
        ///     The lifetime of the <see cref="StreamWriter"/> should be managed with retain() and release().
        /// </remarks>
        /// <param name="path">The file path to read from.</param>
        /// <returns>A pointer to the newly allocated stream reader.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="path"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        StreamReader(const char *path);

        virtual ~StreamReader();

        StreamReader &operator=(const StreamReader &reader) = delete;

        StreamReader &operator=(StreamReader &&reader);

        /// <summary>
        /// Returns the next available character of a <see cref="TextReader"/>.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
        /// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        int Peek() const override;

        /// <summary>
        /// Reads the next available character from the input source of a <see cref="TextReader"/> and advances the character
        /// position to the next character.
        /// </summary>
        /// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
        /// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        int Read() override;

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
        virtual uintsize Read(char *buffer, uintsize offset, uintsize count) override;
    };
}

#endif
