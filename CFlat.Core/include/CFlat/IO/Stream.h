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

//! @file Stream.h

#ifndef CFLAT_CORE_IO_STREAM_H
#define CFLAT_CORE_IO_STREAM_H

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Pointers.h"

#include "CFlat/IO/SeekOrigin.h"

namespace CFlat {
    /// <summary>
    /// Base class for objects that can read and/or write sequences of bytes.
    /// </summary>
    class Stream {
    private:
        class NullStream;

    public:
        virtual ~Stream();

        /// <summary>
        /// Represents a <see cref="Stream"/> with no backing store.
        /// </summary>
        static unique_ptr<Stream, NoOpDeleter<Stream>> Null();

        /// <summary>
        /// Determines whether a <see cref="Stream"/> supports reading.
        /// </summary>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <returns>
        ///     <see cref="true"/> if the stream supports reading; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        virtual bool CanRead() const = 0;

        /// <summary>
        /// Determines whether a <see cref="Stream"/> supports seeking.
        /// </summary>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <returns>
        ///     <see cref="true"/> if the stream supports seeking; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        virtual bool CanSeek() const = 0;

        /// <summary>
        /// Determines whether a <see cref="Stream"/> supports writing.
        /// </summary>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <returns>
        ///     <see cref="true"/> if the stream supports writing; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        virtual bool CanWrite() const = 0;

        /// <summary>
        /// Gets the length of a <see cref="Stream"/> in bytes.
        /// </summary>
        /// <remarks>
        ///     The stream must support seeking for this function to work. Use CanSeek() to determine whether seeking
        ///     is supported.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <returns>The length of the stream in bytes.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        /// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
        virtual intfsize GetLength() const = 0;

        /// <summary>
        /// Sets the length of a <see cref="Stream"/> in bytes.
        /// </summary>
        /// <remarks>
        ///     If the given value is less than the current length of the stream, the stream is truncated. If the given value is
        ///     larger than the current length of the stream, the stream is expanded. The contents of the expanded section of
        ///     the stream are undefined.
        ///
        ///     The stream must support both writing and seeking for this function to work. Use CanWrite() and
        ///     CanSeek() to determine whether writing and seeking are supported.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <param name="length">The desired length of the stream in bytes.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        /// <exception cref="::NotSupportedException">
        ///     <paramref name="stream"/> does not support both writing and seeking.
        /// </exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual void SetLength(intfsize length) = 0;

        /// <summary>
        /// Gets the position within a <see cref="Stream"/>.
        /// </summary>
        /// <remarks>
        ///     The stream must support seeking for this function to work. Use CanSeek() to determine whether seeking
        ///     is supported.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <returns>The position within the stream.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        /// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual intfsize GetPosition() const = 0;

        /// <summary>
        /// Sets the position within a <see cref="Stream"/>.
        /// </summary>
        /// <remarks>
        ///     The stream must support seeking for this function to work. Use CanSeek() to determine whether seeking
        ///     is supported.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <param name="position">The desired position within the stream.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        /// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual void SetPosition(intfsize position) = 0;

        /// <summary>
        /// Reads the bytes from a <see cref="Stream"/> and writes them to another <see cref="Stream"/>.
        /// </summary>
        /// <remarks>
        ///     Copying begins at the current position in the stream and does not reset the position after the copy operation
        ///     is completed.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <param name="destination">
        ///     Pointer to a <see cref="Stream"/> to which the contents of <paramref name="stream"/> should be copied.
        /// </param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="stream"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="destination"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::NotSupportedException">
        ///     <paramref name="stream"/> does not support reading <b>-or-</b>
        ///     <paramref name="destination"/> does not support writing.
        /// </exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        void CopyTo(Stream &destination);

        /// <summary>
        /// Reads the bytes from a <see cref="Stream"/> and writes them to another <see cref="Stream"/>, using the given buffer
        /// size.
        /// </summary>
        /// <remarks>
        ///     Copying begins at the current position in the stream and does not reset the position after the copy operation
        ///     is completed.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <param name="destination">
        ///     Pointer to a <see cref="Stream"/> to which the contents of <paramref name="stream"/> should be copied.
        /// </param>
        /// <param name="bufferSize">The size of the buffer.</param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="stream"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="destination"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::ArgumentOutOfRangeException"><paramref name="bufferSize"/> is zero.</exception>
        /// <exception cref="::NotSupportedException">
        ///     <paramref name="stream"/> does not support reading <b>-or-</b>
        ///     <paramref name="destination"/> does not support writing.
        /// </exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        void CopyTo(Stream &destination, uintsize bufferSize);

        /// <summary>
        /// Writes any unwritten data in the output buffer of a <see cref="Stream"/> to the underlying device.
        /// </summary>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual void Flush() = 0;

        /// <summary>
        /// Reads a sequence of bytes from a <see cref="Stream"/> and advances the position of the stream by the number of bytes
        /// read.
        /// </summary>
        /// <remarks>
        ///     Use CanRead() to determine whether reading is supported.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <param name="buffer">The array to which the bytes should be read.</param>
        /// <param name="offset">
        ///     The offset in <paramref name="buffer"/> at which to begin storing bytes read from <paramref name="stream"/>.
        /// </param>
        /// <param name="count">The maximum number of bytes to read.</param>
        /// <returns>
        ///     The total number of bytes read into the buffer. This can be less than the number of bytes requested if that many
        ///     bytes are currently not available, or zero if the end of the stream has been reached.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="stream"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="buffer"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support reading.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual uintsize Read(byte *buffer, uintsize offset, uintsize count) = 0;

        /// <summary>
        /// Reads a byte from a <see cref="Stream"/> and advances the position of the stream by one byte, or returns -1 if the
        /// end of the stream has been reached.
        /// </summary>
        /// <remarks>
        ///     Use CanRead() to determine whether reading is supported.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <returns>The byte read promoted to an <see cref="int"/>, or -1 if the end of the stream has been reached.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        /// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support reading.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual int ReadByte();

        /// <summary>
        /// Sets the position within a <see cref="Stream"/>.
        /// </summary>
        /// <remarks>
        ///     Use CanSeek() to determine whether seeking is supported.
        ///
        ///     Seeking to any location beyond the length of the stream is not supported.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <param name="offset">The offset in bytes relative to <paramref name="origin"/>.</param>
        /// <param name="origin">
        ///     A <see cref="SeekOrigin"/> value that is used as a reference point for <paramref name="offset"/>.
        /// </param>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        /// <exception cref="::ArgumentException"><paramref name="origin"/> is not a valid <see cref="SeekOrigin"/>.</exception>
        /// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual intfsize Seek(intfsize offset, SeekOrigin::Enum origin) = 0;

        /// <summary>
        /// Writes a sequence of bytes to a <see cref="Stream"/> and advances the position of the stream by the number of bytes
        /// written.
        /// </summary>
        /// <remarks>
        ///     Use CanWrite() to determine whether writing is supported.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <param name="buffer">The array from which the bytes should be copied.</param>
        /// <param name="offset">
        ///     The offset in <paramref name="buffer"/> at which to begin copying bytes to <paramref name="stream"/>.
        /// </param>
        /// <param name="count">The number of bytes to write.</param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="stream"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="buffer"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support writing.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual void Write(const byte *buffer, uintsize offset, uintsize count) = 0;

        /// <summary>
        /// Writes a byte to a <see cref="Stream"/> and advances the position of the stream by one byte.
        /// </summary>
        /// <remarks>
        ///     Use CanWrite() to determine whether writing is supported.
        /// </remarks>
        /// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
        /// <param name="value">The byte to write to <paramref name="stream"/>.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
        /// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support writing.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual void WriteByte(byte value);
    };
}

#endif
