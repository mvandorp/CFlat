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

#include "CFlat/IO/Stream.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

/* Macros */
/// <summary>
/// Initializer for a <see cref="Stream"/> with no backing store.
/// </summary>
#define NullStream_Initializer() { CFLAT_CONST_OBJECT_INITIALIZER((const ObjectVTable*)&NullStream_VTable) }

/**************************************/
/* Private functions                  */
/**************************************/

private override bool NullStream_CanRead(const Stream *stream);
private override bool NullStream_CanSeek(const Stream *stream);
private override bool NullStream_CanWrite(const Stream *stream);

private override intfsize NullStream_GetLength(const Stream *stream);
private override void NullStream_SetLength(Stream *stream, intfsize length);

private override intfsize NullStream_GetPosition(const Stream *stream);
private override void NullStream_SetPosition(Stream *stream, intfsize position);

private override void NullStream_Flush(Stream *stream);
private override uintsize NullStream_Read(Stream *stream, byte *buffer, uintsize offset, uintsize count);
private override intfsize NullStream_Seek(Stream *stream, intfsize offset, SeekOrigin origin);
private override void NullStream_Write(Stream *stream, const byte *buffer, uintsize offset, uintsize count);

/* Private constants */
/// <summary>
/// The virtual method table for a <see cref="Stream"/> with no backing store.
/// </summary>
private const StreamVTable NullStream_VTable = StreamVTable_Initializer(
    null,
    NullStream_CanRead,
    NullStream_CanSeek,
    NullStream_CanWrite,
    NullStream_GetLength,
    NullStream_SetLength,
    NullStream_GetPosition,
    NullStream_SetPosition,
    NullStream_Flush,
    NullStream_Read,
    NullStream_Seek,
    NullStream_Write);

/// <summary>
/// A <see cref="Stream"/> with no backing store.
/// </summary>
private Stream Null = NullStream_Initializer();

/* Public constants */
/// <summary>
/// A <see cref="Stream"/> with no backing store.
/// </summary>
public Stream * const Stream_Null = &Null;

/**************************************/
/* Private function definitions       */
/**************************************/

private override bool NullStream_CanRead(const Stream *stream)
{
    Validate_NotNull(stream);

    return true;
}

private override bool NullStream_CanSeek(const Stream *stream)
{
    Validate_NotNull(stream);

    return true;
}

private override bool NullStream_CanWrite(const Stream *stream)
{
    Validate_NotNull(stream);

    return true;
}

private override intfsize NullStream_GetLength(const Stream *stream)
{
    Validate_NotNull(stream);

    return 0;
}

private override void NullStream_SetLength(Stream *stream, intfsize length)
{
    Validate_NotNull(stream);

    (void)length;
}

private override intfsize NullStream_GetPosition(const Stream *stream)
{
    Validate_NotNull(stream);

    return 0;
}

private override void NullStream_SetPosition(Stream *stream, intfsize position)
{
    Validate_NotNull(stream);

    (void)position;
}

private override void NullStream_Flush(Stream *stream)
{
    Validate_NotNull(stream);
}

private override uintsize NullStream_Read(Stream *stream, byte *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(stream);
    Validate_NotNull(buffer);

    (void)offset;
    (void)count;

    return 0;
}

private override intfsize NullStream_Seek(Stream *stream, intfsize offset, SeekOrigin origin)
{
    Validate_NotNull(stream);

    (void)offset;
    (void)origin;

    return 0;
}

private override void NullStream_Write(Stream *stream, const byte *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(stream);
    Validate_NotNull(buffer);

    (void)offset;
    (void)count;
}
