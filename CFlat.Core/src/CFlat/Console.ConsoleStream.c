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

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/FileAccess.h"
#include "CFlat/IO/Stream.h"

#include <stdio.h>

/* Types */
typedef struct ConsoleStream {
    Stream Base;
    FILE *File;
    FileAccess Access;
} ConsoleStream;

/**************************************/
/* Internal functions                 */
/**************************************/

internal Stream *ConsoleStream_New(FILE *file, FileAccess fileAccess);

/**************************************/
/* Private functions                  */
/**************************************/

private void ConsoleStream_Constructor(ConsoleStream *stream, FILE *file, FileAccess fileAccess);
private void ConsoleStream_Destructor(ConsoleStream *stream);

private override bool ConsoleStream_CanRead(const ConsoleStream *stream);
private override bool ConsoleStream_CanSeek(const ConsoleStream *stream);
private override bool ConsoleStream_CanWrite(const ConsoleStream *stream);

private override long ConsoleStream_GetLength(const ConsoleStream *stream);
private override void ConsoleStream_SetLength(ConsoleStream *stream, long length);

private override long ConsoleStream_GetPosition(const ConsoleStream *stream);
private override void ConsoleStream_SetPosition(ConsoleStream *stream, long position);

private override void ConsoleStream_Flush(ConsoleStream *stream);
private override uintsize ConsoleStream_Read(ConsoleStream *stream, byte *buffer, uintsize offset, uintsize count);
private override long ConsoleStream_Seek(ConsoleStream *stream, long offset, SeekOrigin origin);
private override void ConsoleStream_Write(ConsoleStream *stream, const byte *buffer, uintsize offset, uintsize count);

private void ValidateReadSupported(const ConsoleStream *stream);
private void ValidateSeekSupported(const ConsoleStream *stream);
private void ValidateWriteSupported(const ConsoleStream *stream);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="ConsoleStream"/> class.
/// </summary>
private const StreamVTable VTable = StreamVTable_Initializer(
    (DestructorFunc)ConsoleStream_Destructor,
    (Stream_CanReadFunc)ConsoleStream_CanRead,
    (Stream_CanSeekFunc)ConsoleStream_CanSeek,
    (Stream_CanWriteFunc)ConsoleStream_CanWrite,
    (Stream_GetLengthFunc)ConsoleStream_GetLength,
    (Stream_SetLengthFunc)ConsoleStream_SetLength,
    (Stream_GetPositionFunc)ConsoleStream_GetPosition,
    (Stream_SetPositionFunc)ConsoleStream_SetPosition,
    (Stream_FlushFunc)ConsoleStream_Flush,
    (Stream_ReadFunc)ConsoleStream_Read,
    (Stream_SeekFunc)ConsoleStream_Seek,
    (Stream_WriteFunc)ConsoleStream_Write);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal Stream *ConsoleStream_New(FILE *file, FileAccess fileAccess)
{
    ConsoleStream *stream = Memory_Allocate(sizeof(ConsoleStream));

    try {
        ConsoleStream_Constructor(stream, file, fileAccess);

        Object_SetDeallocator(stream, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(stream);
        throw;
    }
    endtry;

    return (Stream*)stream;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void ConsoleStream_Constructor(ConsoleStream *stream, FILE *file, FileAccess fileAccess)
{
    Validate_NotNull(file);
    FileAccess_Validate(fileAccess);

    Stream_Constructor((Stream*)stream, &VTable);

    stream->File = file;
    stream->Access = fileAccess;
}

private void ConsoleStream_Destructor(ConsoleStream *stream)
{
    if (ConsoleStream_CanWrite(stream)) {
        try {
            ConsoleStream_Flush(stream);
        }
        catch (Exception);
        endtry;
    }
}

private override bool ConsoleStream_CanRead(const ConsoleStream *stream)
{
    Validate_NotNull(stream);

    return (stream->Access & FileAccess_Read) == FileAccess_Read;
}

private override bool ConsoleStream_CanSeek(const ConsoleStream *stream)
{
    Validate_NotNull(stream);

    return false;
}

private override bool ConsoleStream_CanWrite(const ConsoleStream *stream)
{
    Validate_NotNull(stream);

    return (stream->Access & FileAccess_Write) == FileAccess_Write;
}

private override long ConsoleStream_GetLength(const ConsoleStream *stream)
{
    ValidateSeekSupported(stream);

    return 0;
}

private override void ConsoleStream_SetLength(ConsoleStream *stream, long length)
{
    ValidateSeekSupported(stream);

    (void)length;
}

private override long ConsoleStream_GetPosition(const ConsoleStream *stream)
{
    ValidateSeekSupported(stream);

    return 0;
}

private override void ConsoleStream_SetPosition(ConsoleStream *stream, long position)
{
    ValidateSeekSupported(stream);

    (void)position;
}

private override void ConsoleStream_Flush(ConsoleStream *stream)
{
    Validate_NotNull(stream);

    if (ConsoleStream_CanWrite(stream)) {
        fflush(stream->File);

        if (ferror(stream->File)) {
            throw_new(IOException, "Failed to flush the stream.");
        }
    }
}

private override uintsize ConsoleStream_Read(ConsoleStream *stream, byte *buffer, uintsize offset, uintsize count)
{
    ValidateReadSupported(stream);
    Validate_NotNull(buffer);

    uintsize bytesRead = 0;

    while (bytesRead < count) {
        int ch = fgetc(stream->File);

        if (ch == EOF) break;

        buffer[offset + bytesRead++] = (byte)ch;

        if (ch == '\n') break;
    }

    if (ferror(stream->File)) {
        throw_new(IOException, "Failed to read from the stream.");
    }

    return bytesRead;
}

private override long ConsoleStream_Seek(ConsoleStream *stream, long offset, SeekOrigin origin)
{
    ValidateSeekSupported(stream);

    (void)offset;
    (void)origin;

    return 0;
}

private override void ConsoleStream_Write(ConsoleStream *stream, const byte *buffer, uintsize offset, uintsize count)
{
    ValidateWriteSupported(stream);
    Validate_NotNull(buffer);

    if (count == 0) return;

    fwrite(&buffer[offset], 1, count, stream->File);

    if (ferror(stream->File)) {
        throw_new(IOException, "Failed to write to the stream.");
    }
}

private void ValidateReadSupported(const ConsoleStream *stream)
{
    if (!ConsoleStream_CanRead(stream)) {
        throw_new(NotSupportedException, "The stream does not support reading.");
    }
}

private void ValidateSeekSupported(const ConsoleStream *stream)
{
    if (!ConsoleStream_CanSeek(stream)) {
        throw_new(NotSupportedException, "The stream does not support seeking.");
    }
}

private void ValidateWriteSupported(const ConsoleStream *stream)
{
    if (!ConsoleStream_CanWrite(stream)) {
        throw_new(NotSupportedException, "The stream does not support writing.");
    }
}
