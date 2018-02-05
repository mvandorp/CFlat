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

#include <utility>

using namespace CFlat;

/* Private constants */
static const uintsize DefaultBufferSize = 4096;

/**************************************/
/* Public function definitions        */
/**************************************/

StreamReader::StreamReader(StreamReader &&reader) :
    _stream(nullptr),
    _buffer(nullptr),
    _bufferPosition(0),
    _bufferLength(0)
{
    std::swap(_stream, reader._stream);
    std::swap(_buffer, reader._buffer);
    std::swap(_bufferPosition, reader._bufferPosition);
    std::swap(_bufferLength, reader._bufferLength);
}

StreamReader::StreamReader(unique_ptr<Stream> &&stream) :
    _stream(std::move(stream)),
    _buffer(new byte[DefaultBufferSize]),
    _bufferPosition(0),
    _bufferLength(0)
{
    Validate_NotNull(stream);
    Validate_IsTrue(stream->CanRead(), NotSupportedException(String::Wrap("The stream does not support reading.")));
}

StreamReader::StreamReader(const String &path) :
    _stream(new FileStream(path, FileMode::Open, FileAccess::Read)),
    _buffer(new byte[DefaultBufferSize]),
    _bufferPosition(0),
    _bufferLength(0)
{
}

StreamReader::StreamReader(const char *path) : StreamReader(String(path))
{
}

StreamReader::~StreamReader()
{
}

StreamReader &StreamReader::operator=(StreamReader &&reader)
{
    if (this != std::addressof(reader)) {
        std::swap(_stream, reader._stream);
        std::swap(_buffer, reader._buffer);
        std::swap(_bufferPosition, reader._bufferPosition);
        std::swap(_bufferLength, reader._bufferLength);
    }

    return *this;
}

int StreamReader::Peek() const
{
    if (_bufferPosition == _bufferLength) {
        if (this->ReadInternalBuffer() == 0) return -1;
    }

    return _buffer[_bufferPosition];
}

int StreamReader::Read()
{
    if (_bufferPosition == _bufferLength) {
        if (this->ReadInternalBuffer() == 0) return -1;
    }

    return _buffer[_bufferPosition++];
}

uintsize StreamReader::Read(char *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(buffer);

    if (count == 0) return 0;

    uintsize totalRead = 0;
    uintsize bytesRead = 0;

    // The number of bytes remaining in the internal buffer.
    uintsize remaining = _bufferLength - _bufferPosition;

    // Read from the internal buffer.
    if (remaining > 0) {
        remaining = UIntSize::Min(remaining, count);

        Memory::Copy(_buffer.Get(), _bufferPosition, reinterpret_cast<byte*>(buffer), offset, remaining);

        // Advance the position within the internal buffer.
        _bufferPosition += remaining;

        totalRead += remaining;
        offset += remaining;
        count -= remaining;
    }

    if (count == 0) return totalRead;

    // Read the stream directly into the user buffer.
    while ((bytesRead = _stream->Read(reinterpret_cast<byte*>(buffer), offset, count)) != 0) {
        totalRead += bytesRead;
        offset += bytesRead;
        count -= bytesRead;
    }

    return totalRead;
}

uintsize StreamReader::ReadInternalBuffer() const
{
    _bufferPosition = 0;
    _bufferLength = _stream->Read(_buffer.Get(), 0, DefaultBufferSize);

    return _bufferLength;
}
