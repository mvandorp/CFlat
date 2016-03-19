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
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"

/* Private constants */
/// <summary>
/// The default buffer capacity to use when copying a stream.
/// </summary>
private const uintsize DefaultBufferSize = 81920;

 /**************************************/
/* Private functions                  */
/**************************************/

private const StreamVTable *GetVTable(const Stream *stream);

/**************************************/
/* Public function definitions        */
/**************************************/

public void Stream_Constructor(Stream *stream, const StreamVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->CanRead);
    Validate_NotNull(vtable->CanSeek);
    Validate_NotNull(vtable->CanWrite);
    Validate_NotNull(vtable->GetLength);
    Validate_NotNull(vtable->SetLength);
    Validate_NotNull(vtable->GetPosition);
    Validate_NotNull(vtable->Flush);
    Validate_NotNull(vtable->Seek);
    Validate_NotNull(vtable->Read);
    Validate_NotNull(vtable->Write);

    Object_Constructor((Object*)stream, (const ObjectVTable*)vtable);
}

public abstract bool Stream_CanRead(const Stream *stream)
{
    return GetVTable(stream)->CanRead(stream);
}

public abstract bool Stream_CanSeek(const Stream *stream)
{
    return GetVTable(stream)->CanSeek(stream);
}

public abstract bool Stream_CanWrite(const Stream *stream)
{
    return GetVTable(stream)->CanWrite(stream);
}

public abstract long Stream_GetLength(const Stream *stream)
{
    return GetVTable(stream)->GetLength(stream);
}

public abstract void Stream_SetLength(Stream *stream, long length)
{
    GetVTable(stream)->SetLength(stream, length);
}

public abstract long Stream_GetPosition(const Stream *stream)
{
    return GetVTable(stream)->GetPosition(stream);
}

public abstract void Stream_SetPosition(Stream *stream, long position)
{
    GetVTable(stream)->SetPosition(stream, position);
}

public void Stream_CopyTo(Stream *stream, Stream *destination)
{
    Stream_CopyTo_WithBufferSize(stream, destination, DefaultBufferSize);
}

public void Stream_CopyTo_WithBufferSize(Stream *stream, Stream *destination, uintsize bufferSize)
{
    Validate_NotNull(stream);
    Validate_NotNull(destination);
    Validate_IsTrue(Stream_CanWrite(stream), NotSupportedException, "The source stream does not support reading.");
    Validate_IsTrue(
        Stream_CanWrite(destination),
        NotSupportedException,
        "The destination stream does not support writing.");
    Validate_IsTrue(bufferSize > 0, ArgumentOutOfRangeException, "Buffer size cannot be zero.");

    byte *buffer = Memory_Allocate(bufferSize);

    try {
        uintsize bytesRead;

        while ((bytesRead = Stream_Read(stream, buffer, 0, bufferSize)) != 0) {
            Stream_Write(destination, buffer, 0, bytesRead);
        }
    }
    finally {
        Memory_Deallocate(buffer);
    }
    endtry;
}

public abstract void Stream_Flush(Stream *stream)
{
    GetVTable(stream)->Flush(stream);
}

public abstract long Stream_Seek(Stream *stream, long offset, SeekOrigin origin)
{
    return GetVTable(stream)->Seek(stream, offset, origin);
}

public abstract uintsize Stream_Read(Stream *stream, byte *buffer, uintsize offset, uintsize count)
{
    return GetVTable(stream)->Read(stream, buffer, offset, count);
}

public int Stream_ReadByte(Stream *stream)
{
    byte buffer[1];

    if (Stream_Read(stream, buffer, 0, 1) == 0) {
        return -1;
    }

    return buffer[0];
}

public abstract void Stream_Write(Stream *stream, const byte *buffer, uintsize offset, uintsize count)
{
    GetVTable(stream)->Write(stream, buffer, offset, count);
}

public void Stream_WriteByte(Stream *stream, byte value)
{
    byte buffer[1];
    buffer[0] = value;

    Stream_Write(stream, buffer, 0, 1);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of a <see cref="Stream"/>.
/// </summary>
/// <param name="stream">Pointer to a <see cref="Stream"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
private const StreamVTable *GetVTable(const Stream *stream)
{
    Validate_NotNull(stream);

    return (const StreamVTable*)((const Object*)stream)->VTable;
}
