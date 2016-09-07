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

#include "CFlat/IO/StreamReader.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/FileStream.h"
#include "CFlat/IO/Stream.h"
#include "CFlat/IO/TextReader.h"

/* Types */
struct StreamReader {
    TextReader Base;
    Stream *Stream;
    byte *Buffer;
    uintsize BufferPosition;
    uintsize BufferLength;
};

/**************************************/
/* Private functions                  */
/**************************************/

private void StreamReader_Constructor(StreamReader *reader, Stream *stream);

private void StreamReader_Destructor(StreamReader *reader);

private override int StreamReader_Peek(StreamReader *reader);

private override int StreamReader_Read(StreamReader *reader);

private override uintsize StreamReader_ReadBuffer(StreamReader *reader, char *buffer, uintsize offset, uintsize count);

private uintsize ReadInternalBuffer(StreamReader *reader);

/* Private constants */
private uintsize DefaultBufferSize = 4096;

/// <summary>
/// The virtual method table for the <see cref="ConsoleStream"/> class.
/// </summary>
private const TextReaderVTable VTable = TextReaderVTable_Initializer(
    (DestructorFunc)StreamReader_Destructor,
    (TextReader_PeekFunc)StreamReader_Peek,
    (TextReader_ReadFunc)StreamReader_Read,
    (TextReader_ReadBufferFunc)StreamReader_ReadBuffer);

/**************************************/
/* Public function definitions        */
/**************************************/

public TextReader *StreamReader_New(Stream *stream)
{
    StreamReader *reader = Memory_Allocate(sizeof(StreamReader));

    try {
        StreamReader_Constructor(reader, stream);

        Object_SetDeallocator(reader, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(reader);
        throw;
    }
    endtry;

    return (TextReader*)reader;
}

public TextReader *StreamReader_New_FromFile(const char *path)
{
    TextReader *reader = null;
    Stream *stream = FileStream_New(path, FileMode_Open);

    try {
        reader = StreamReader_New(stream);
    }
    finally {
        release(stream);
    }
    endtry;

    return reader;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void StreamReader_Constructor(StreamReader *reader, Stream *stream)
{
    Validate_NotNull(stream);
    Validate_IsTrue(Stream_CanRead(stream), NotSupportedException, "The stream does not support reading.");

    TextReader_Constructor((TextReader*)reader, &VTable);

    reader->Buffer = Memory_Allocate(DefaultBufferSize);
    reader->Stream = retain(stream);
    reader->BufferPosition = 0;
    reader->BufferLength = 0;
}

private void StreamReader_Destructor(StreamReader *reader)
{
    Validate_NotNull(reader);

    Memory_Deallocate(reader->Buffer);

    release(reader->Stream);
}

private override int StreamReader_Peek(StreamReader *reader)
{
    Validate_NotNull(reader);

    if (reader->BufferPosition == reader->BufferLength) {
        if (ReadInternalBuffer(reader) == 0) return -1;
    }

    return reader->Buffer[reader->BufferPosition];
}

private override int StreamReader_Read(StreamReader *reader)
{
    Validate_NotNull(reader);

    if (reader->BufferPosition == reader->BufferLength) {
        if (ReadInternalBuffer(reader) == 0) return -1;
    }

    return reader->Buffer[reader->BufferPosition++];
}

private override uintsize StreamReader_ReadBuffer(StreamReader *reader, char *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(reader);
    Validate_NotNull(buffer);

    if (count == 0) return 0;

    uintsize totalRead = 0;
    uintsize bytesRead = 0;

    // The number of bytes remaining in the internal buffer.
    uintsize remaining = reader->BufferLength - reader->BufferPosition;

    // Read from the internal buffer.
    if (remaining > 0) {
        remaining = uintsize_Min(remaining, count);

        Memory_CopyOffset(reader->Buffer, reader->BufferPosition, buffer, offset, remaining);

        // Advance the position within the internal buffer.
        reader->BufferPosition += remaining;

        totalRead += remaining;
        offset += remaining;
        count -= remaining;
    }

    if (count == 0) return totalRead;

    // Read the stream directly into the user buffer.
    while ((bytesRead = Stream_Read(reader->Stream, (byte*)buffer, offset, count)) != 0) {
        totalRead += bytesRead;
        offset += bytesRead;
        count -= bytesRead;
    }

    return totalRead;
}

private uintsize ReadInternalBuffer(StreamReader *reader)
{
    assert(reader != null);

    reader->BufferPosition = 0;
    reader->BufferLength = Stream_Read(reader->Stream, reader->Buffer, 0, DefaultBufferSize);

    return reader->BufferLength;
}
