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

#include "CFlat/Console.ConsoleStream.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"

using namespace CFlat;

/**************************************/
/* Public function definitions        */
/**************************************/

ConsoleStream::ConsoleStream(int *file, FileAccess::Enum fileAccess)
{
    Validate_NotNull(file);
    FileAccess::Validate(fileAccess);

    _file = file;
    _access = fileAccess;
}

ConsoleStream::~ConsoleStream()
{
    if (this->CanWrite()) {
        try {
            this->Flush();
        }
        catch (const Exception &ex) {
            (void)ex;
        }
    }
}

bool ConsoleStream::CanRead() const
{
    return FileAccess::HasFlag(_access, FileAccess::Read);
}

bool ConsoleStream::CanSeek() const
{
    return false;
}

bool ConsoleStream::CanWrite() const
{
    return FileAccess::HasFlag(_access, FileAccess::Write);
}

intfsize ConsoleStream::GetLength() const
{
    this->ValidateSeekSupported();

    return 0;
}

void ConsoleStream::SetLength(intfsize length)
{
    this->ValidateSeekSupported();

    (void)length;
}

intfsize ConsoleStream::GetPosition() const
{
    this->ValidateSeekSupported();

    return 0;
}

void ConsoleStream::SetPosition(intfsize position)
{
    this->ValidateSeekSupported();

    (void)position;
}

void ConsoleStream::Flush()
{
    if (this->CanWrite()) {
        //fflush(_file);

        if (0) {//std::ferror(_file)) {
            throw IOException(String::Wrap("Failed to flush the stream."));
        }
    }
}

uintsize ConsoleStream::Read(byte *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(buffer);
    this->ValidateReadSupported();

    // Skip to the offset.
    buffer = &buffer[offset];

    uintsize bytesRead = 0;

    while (bytesRead < count) {
        int ch = 0;//td::fgetc(_file);

        if (ch == 0) break;//EOF) break;

        buffer[bytesRead++] = (byte)ch;

        if (ch == '\n') break;
    }

    if (0) {//ferror(_file)) {
        throw IOException(String::Wrap("Failed to read from the stream."));
    }

    return bytesRead;
}

intfsize ConsoleStream::Seek(intfsize offset, SeekOrigin::Enum origin)
{
    this->ValidateSeekSupported();

    (void)offset;
    (void)origin;

    return 0;
}

void ConsoleStream::Write(const byte *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(buffer);
    this->ValidateWriteSupported();

    if (count == 0) return;

    //std::fwrite(&buffer[offset], 1, count, _file);

    if (0) {//ferror(_file)) {
        throw IOException(String::Wrap("Failed to write to the stream."));
    }
}

void ConsoleStream::ValidateReadSupported() const
{
    if (!this->CanRead()) {
        throw NotSupportedException(String::Wrap("The stream does not support reading."));
    }
}

void ConsoleStream::ValidateSeekSupported() const
{
    if (!this->CanSeek()) {
        throw NotSupportedException(String::Wrap("The stream does not support seeking."));
    }
}

void ConsoleStream::ValidateWriteSupported() const
{
    if (!this->CanWrite()) {
        throw NotSupportedException(String::Wrap("The stream does not support writing."));
    }
}
