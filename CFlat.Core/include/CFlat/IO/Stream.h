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

#include "CFlat/Object.h"
#include "CFlat/IO/SeekOrigin.h"
#include "CFlat/Language/Bool.h"

/* Macros */
/// <summary>
/// Initializer for an <see cref="StreamVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>, or <see cref="null"/>.</param>
/// <param name="canRead">A <see cref="Stream_CanReadFunc"/>.</param>
/// <param name="canSeek">A <see cref="Stream_CanSeekFunc"/>.</param>
/// <param name="canWrite">A <see cref="Stream_CanWriteFunc"/>.</param>
/// <param name="getLength">A <see cref="Stream_GetLengthFunc"/>.</param>
/// <param name="setLength">A <see cref="Stream_SetLengthFunc"/>.</param>
/// <param name="getPosition">A <see cref="Stream_GetPositionFunc"/>.</param>
/// <param name="setPosition">A <see cref="Stream_SetPositionFunc"/>.</param>
/// <param name="flush">A <see cref="Stream_FlushFunc"/>.</param>
/// <param name="read">A <see cref="Stream_ReadFunc"/>.</param>
/// <param name="seek">A <see cref="Stream_SeekFunc"/>.</param>
/// <param name="write">A <see cref="Stream_WriteFunc"/>.</param>
#define StreamVTable_Initializer(               \
    destructor,                                 \
    canRead,                                    \
    canSeek,                                    \
    canWrite,                                   \
    getLength,                                  \
    setLength,                                  \
    getPosition,                                \
    setPosition,                                \
    flush,                                      \
    read,                                       \
    seek,                                       \
    write)                                      \
{                                               \
    ObjectVTable_Initializer(destructor),       \
    canRead,                                    \
    canSeek,                                    \
    canWrite,                                   \
    getLength,                                  \
    setLength,                                  \
    getPosition,                                \
    setPosition,                                \
    flush,                                      \
    read,                                       \
    seek,                                       \
    write                                       \
}

/* Types */
/// <summary>
/// Base class for objects that can read and/or write sequences of bytes.
/// </summary>
typedef struct Stream {
    /// <summary>
    /// The base class of <see cref="Stream"/>.
    /// </summary>
    Object Base;
} Stream;

/// <summary>
/// A function that determines whether a <see cref="Stream"/> supports reading.
/// </summary>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>
///     <see cref="true"/> if the stream supports reading; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
typedef bool (*Stream_CanReadFunc)(const Stream *stream);

/// <summary>
/// A function that determines whether a <see cref="Stream"/> supports seeking.
/// </summary>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>
///     <see cref="true"/> if the stream supports seeking; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
typedef bool (*Stream_CanSeekFunc)(const Stream *stream);

/// <summary>
/// A function that determines whether a <see cref="Stream"/> supports writing.
/// </summary>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>
///     <see cref="true"/> if the stream supports writing; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
typedef bool (*Stream_CanWriteFunc)(const Stream *stream);

/// <summary>
/// A function that returns the length of a <see cref="Stream"/> in bytes.
/// </summary>
/// <remarks>
///     The stream must support seeking for this function to work. Use Stream_CanSeek() to determine whether seeking
///     is supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>The length of the stream in bytes.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
typedef long (*Stream_GetLengthFunc)(const Stream *stream);

/// <summary>
/// A function that sets the length of a <see cref="Stream"/> in bytes.
/// </summary>
/// <remarks>
///     If the given value is less than the current length of the stream, the stream is truncated. If the given value is
///     larger than the current length of the stream, the stream is expanded. The contents of the expanded section of
///     the stream are undefined.
///
///     The stream must support both writing and seeking for this function to work. Use Stream_CanWrite() and
///     Stream_CanSeek() to determine whether writing and seeking are supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <param name="length">The desired length of the stream in bytes.</param>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException">
///     <paramref name="stream"/> does not support both writing and seeking.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
typedef void (*Stream_SetLengthFunc)(Stream *stream, long length);

/// <summary>
/// A function that returns the length of a <see cref="Stream"/> in bytes.
/// </summary>
/// <remarks>
///     The stream must support seeking for this function to work. Use Stream_CanSeek() to determine whether seeking
///     is supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>The length of the stream in bytes.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
typedef long (*Stream_GetPositionFunc)(const Stream *stream);

/// <summary>
/// A function that sets the length of a <see cref="Stream"/> in bytes.
/// </summary>
/// <remarks>
///     If the given value is less than the current length of the stream, the stream is truncated. If the given value is
///     larger than the current length of the stream, the stream is expanded. The contents of the expanded section of
///     the stream are undefined.
///
///     The stream must support both writing and seeking for this function to work. Use Stream_CanWrite() and
///     Stream_CanSeek() to determine whether writing and seeking are supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <param name="length">The desired length of the stream in bytes.</param>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException">
///     <paramref name="stream"/> does not support both writing and seeking.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
typedef void (*Stream_SetPositionFunc)(Stream *stream, long position);

/// <summary>
/// A function that writes any unwritten data in the output buffer of a <see cref="Stream"/> to the underlying device.
/// </summary>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
typedef void (*Stream_FlushFunc)(Stream *stream);

/// <summary>
/// A function that reads a sequence of bytes from a <see cref="Stream"/> and advances the position of the stream by the
/// number of bytes read.
/// </summary>
/// <remarks>
///     Use Stream_CanRead() to determine whether reading is supported.
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
typedef uintsize (*Stream_ReadFunc)(Stream *stream, byte *buffer, uintsize offset, uintsize count);

/// <summary>
/// A function that sets the position within a <see cref="Stream"/>.
/// </summary>
/// <remarks>
///     Use Stream_CanSeek() to determine whether seeking is supported.
///
///     Seeking to any location beyond the length of the stream is not supported.
/// </remarks>
/// <param name="offset">The offset in bytes relative to <paramref name="origin"/>.</param>
/// <param name="origin">
///     A <see cref="SeekOrigin"/> value that is used as a reference point for <paramref name="offset"/>.
/// </param>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
typedef long (*Stream_SeekFunc)(Stream *stream, long offset, SeekOrigin origin);

/// <summary>
/// A function that writes a sequence of bytes to a <see cref="Stream"/> and advances the position of the stream by the
/// number of bytes written.
/// </summary>
/// <remarks>
///     Use Stream_CanWrite() to determine whether writing is supported.
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
typedef void (*Stream_WriteFunc)(Stream *stream, const byte *buffer, uintsize offset, uintsize count);

/// <summary>
/// A virtual method table for the <see cref="Stream"/> class.
/// </summary>
typedef struct StreamVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="Stream"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that determines whether a <see cref="Stream"/> supports reading.
    /// </summary>
    Stream_CanReadFunc CanRead;

    /// <summary>
    /// A function that determines whether a <see cref="Stream"/> supports seeking.
    /// </summary>
    Stream_CanSeekFunc CanSeek;

    /// <summary>
    /// A function that determines whether a <see cref="Stream"/> supports writing.
    /// </summary>
    Stream_CanWriteFunc CanWrite;

    /// <summary>
    /// A function that returns the length of a <see cref="Stream"/> in bytes.
    /// </summary>
    Stream_GetLengthFunc GetLength;

    /// <summary>
    /// A function that sets the length of a <see cref="Stream"/> in bytes.
    /// </summary>
    Stream_SetLengthFunc SetLength;

    /// <summary>
    /// A function that returns the length of a <see cref="Stream"/> in bytes.
    /// </summary>
    Stream_GetPositionFunc GetPosition;

    /// <summary>
    /// A function that sets the length of a <see cref="Stream"/> in bytes.
    /// </summary>
    Stream_SetPositionFunc SetPosition;

    /// <summary>
    /// A function that writes any unwritten data in the output buffer of a <see cref="Stream"/> to the underlying
    /// device.
    /// </summary>
    Stream_FlushFunc Flush;

    /// <summary>
    /// A function that reads a sequence of bytes from a <see cref="Stream"/> and advances the position of the stream by
    /// the number of bytes read.
    /// </summary>
    Stream_ReadFunc Read;

    /// <summary>
    /// A function that sets the position within a <see cref="Stream"/>.
    /// </summary>
    Stream_SeekFunc Seek;

    /// <summary>
    /// A function that writes a sequence of bytes to a <see cref="Stream"/> and advances the position of the stream by
    /// the number of bytes written.
    /// </summary>
    Stream_WriteFunc Write;
} StreamVTable;

/* Constants */
/// <summary>
/// Represents a <see cref="Stream"/> with no backing store.
/// </summary>
extern Stream * const Stream_Null;

/* Functions */
/// <summary>
/// Initializes a <see cref="Stream"/>.
/// </summary>
/// <param name="stream">Pointer to an uninitialized <see cref="Stream"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="stream"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void Stream_Constructor(Stream *stream, const StreamVTable *vtable);

/// <summary>
/// Determines whether a <see cref="Stream"/> supports reading.
/// </summary>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>
///     <see cref="true"/> if the stream supports reading; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
abstract bool Stream_CanRead(const Stream *stream);

/// <summary>
/// Determines whether a <see cref="Stream"/> supports seeking.
/// </summary>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>
///     <see cref="true"/> if the stream supports seeking; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
abstract bool Stream_CanSeek(const Stream *stream);

/// <summary>
/// Determines whether a <see cref="Stream"/> supports writing.
/// </summary>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>
///     <see cref="true"/> if the stream supports writing; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
abstract bool Stream_CanWrite(const Stream *stream);

/// <summary>
/// Gets the length of a <see cref="Stream"/> in bytes.
/// </summary>
/// <remarks>
///     The stream must support seeking for this function to work. Use Stream_CanSeek() to determine whether seeking
///     is supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>The length of the stream in bytes.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
abstract long Stream_GetLength(const Stream *stream);

/// <summary>
/// Sets the length of a <see cref="Stream"/> in bytes.
/// </summary>
/// <remarks>
///     If the given value is less than the current length of the stream, the stream is truncated. If the given value is
///     larger than the current length of the stream, the stream is expanded. The contents of the expanded section of
///     the stream are undefined.
///
///     The stream must support both writing and seeking for this function to work. Use Stream_CanWrite() and
///     Stream_CanSeek() to determine whether writing and seeking are supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <param name="length">The desired length of the stream in bytes.</param>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException">
///     <paramref name="stream"/> does not support both writing and seeking.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
abstract void Stream_SetLength(Stream *stream, long length);

/// <summary>
/// Gets the position within a <see cref="Stream"/>.
/// </summary>
/// <remarks>
///     The stream must support seeking for this function to work. Use Stream_CanSeek() to determine whether seeking
///     is supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>The position within the stream.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
abstract long Stream_GetPosition(const Stream *stream);

/// <summary>
/// Sets the position within a <see cref="Stream"/>.
/// </summary>
/// <remarks>
///     The stream must support seeking for this function to work. Use Stream_CanSeek() to determine whether seeking
///     is supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <param name="position">The desired position within the stream.</param>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support seeking.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
abstract void Stream_SetPosition(Stream *stream, long position);

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
void Stream_CopyTo(Stream *stream, Stream *destination);

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
void Stream_CopyTo_WithBufferSize(Stream *stream, Stream *destination, uintsize bufferSize);

/// <summary>
/// Writes any unwritten data in the output buffer of a <see cref="Stream"/> to the underlying device.
/// </summary>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
abstract void Stream_Flush(Stream *stream);

/// <summary>
/// Reads a sequence of bytes from a <see cref="Stream"/> and advances the position of the stream by the number of bytes
/// read.
/// </summary>
/// <remarks>
///     Use Stream_CanRead() to determine whether reading is supported.
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
abstract uintsize Stream_Read(Stream *stream, byte *buffer, uintsize offset, uintsize count);

/// <summary>
/// Reads a byte from a <see cref="Stream"/> and advances the position of the stream by one byte, or returns -1 if the
/// end of the stream has been reached.
/// </summary>
/// <remarks>
///     Use Stream_CanRead() to determine whether reading is supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <returns>The byte read promoted to an <see cref="int"/>, or -1 if the end of the stream has been reached.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support reading.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
int Stream_ReadByte(Stream *stream);

/// <summary>
/// Sets the position within a <see cref="Stream"/>.
/// </summary>
/// <remarks>
///     Use Stream_CanSeek() to determine whether seeking is supported.
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
abstract long Stream_Seek(Stream *stream, long offset, SeekOrigin origin);

/// <summary>
/// Writes a sequence of bytes to a <see cref="Stream"/> and advances the position of the stream by the number of bytes
/// written.
/// </summary>
/// <remarks>
///     Use Stream_CanWrite() to determine whether writing is supported.
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
abstract void Stream_Write(Stream *stream, const byte *buffer, uintsize offset, uintsize count);

/// <summary>
/// Writes a byte to a <see cref="Stream"/> and advances the position of the stream by one byte.
/// </summary>
/// <remarks>
///     Use Stream_CanWrite() to determine whether writing is supported.
/// </remarks>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <param name="value">The byte to write to <paramref name="stream"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::NotSupportedException"><paramref name="stream"/> does not support writing.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void Stream_WriteByte(Stream *stream, byte value);

#endif
