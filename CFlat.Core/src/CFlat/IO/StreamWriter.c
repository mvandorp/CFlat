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

#include "CFlat/IO/StreamWriter.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/FileStream.h"
#include "CFlat/IO/Stream.h"
#include "CFlat/IO/TextWriter.h"

/* Types */
struct StreamWriter {
    TextWriter Base;
    Stream *Stream;
};

/**************************************/
/* Private functions                  */
/**************************************/

private void StreamWriter_Constructor(StreamWriter *writer, Stream *stream);
private void StreamWriter_Destructor(StreamWriter *writer);

private override void StreamWriter_Flush(StreamWriter *writer);
private override String *StreamWriter_ToString(const StreamWriter *writer);
private override void StreamWriter_WriteBuffer(
    StreamWriter *writer,
    const char *buffer,
    uintsize offset,
    uintsize count);

/* Private constants */
/// <summary>
/// The default string representation of a <see cref="StreamWriter"/>.
/// </summary>
private String ClassName = String_Initializer("StreamWriter");

/// <summary>
/// The virtual method table for the <see cref="ConsoleStream"/> class.
/// </summary>
private const TextWriterVTable VTable = TextWriterVTable_Initializer(
    (DestructorFunc)StreamWriter_Destructor,
    (TextWriter_FlushFunc)StreamWriter_Flush,
    (TextWriter_ToStringFunc)StreamWriter_ToString,
    (TextWriter_WriteBufferFunc)StreamWriter_WriteBuffer);

/**************************************/
/* Public function definitions        */
/**************************************/

public TextWriter *StreamWriter_New(Stream *stream)
{
    StreamWriter *writer = Memory_Allocate(sizeof(StreamWriter));

    try {
        StreamWriter_Constructor(writer, stream);

        Object_SetDeallocator(writer, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(writer);
        throw;
    }
    endtry;

    return (TextWriter*)writer;
}

public TextWriter *StreamWriter_New_FromFile(const String *path, bool append)
{
    TextWriter *writer = null;
    Stream *stream = FileStream_New_WithAccess(path, append ? FileMode_Append : FileMode_Create, FileAccess_Write);

    try {
        writer = StreamWriter_New(stream);
    }
    finally {
        release(stream);
    }
    endtry;

    return writer;
}

public TextWriter *StreamWriter_New_FromFile_CString(const char *path, bool append)
{
    TextWriter *writer = null;
    Stream *stream = FileStream_New_WithAccess_CString(
        path,
        append ? FileMode_Append : FileMode_Create,
        FileAccess_Write);

    try {
        writer = StreamWriter_New(stream);
    }
    finally {
        release(stream);
    }
    endtry;

    return writer;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void StreamWriter_Constructor(StreamWriter *writer, Stream *stream)
{
    Validate_NotNull(stream);
    Validate_IsTrue(Stream_CanWrite(stream), NotSupportedException, "The stream does not support writing.");

    TextWriter_Constructor((TextWriter*)writer, &VTable);

    writer->Stream = retain(stream);
}

private void StreamWriter_Destructor(StreamWriter *writer)
{
    Validate_NotNull(writer);

    release(writer->Stream);
}

private override void StreamWriter_Flush(StreamWriter *writer)
{
    Validate_NotNull(writer);

    Stream_Flush(writer->Stream);
}

private override String *StreamWriter_ToString(const StreamWriter *writer)
{
    Validate_NotNull(writer);

    return &ClassName;
}

private override void StreamWriter_WriteBuffer(
    StreamWriter *writer,
    const char *buffer,
    uintsize offset,
    uintsize count)
{
    Validate_NotNull(writer);
    Validate_NotNull(buffer);

    Stream_Write(writer->Stream, (const byte*)buffer, offset, count);
}
