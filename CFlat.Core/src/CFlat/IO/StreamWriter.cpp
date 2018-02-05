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

#include <utility>

using namespace CFlat;

/**************************************/
/* Public function definitions        */
/**************************************/

StreamWriter::StreamWriter(StreamWriter &&writer) :
    _autoFlush(false),
    _stream(nullptr)
{
    std::swap(_stream, writer._stream);
    std::swap(_autoFlush, writer._autoFlush);
}

StreamWriter::StreamWriter(unique_ptr<Stream> stream)
{
    Validate_NotNull(stream);
    Validate_IsTrue(stream->CanWrite(), NotSupportedException(String::Wrap("The stream does not support writing.")));

    _stream = std::move(stream);
}

StreamWriter::StreamWriter(const String &path, bool append)
{
    _stream = unique_ptr<Stream>(new FileStream(path, append ? FileMode::Append : FileMode::Create, FileAccess::Write));
}

StreamWriter::StreamWriter(const char *path, bool append)
{
    _stream = unique_ptr<Stream>(new FileStream(path, append ? FileMode::Append : FileMode::Create, FileAccess::Write));
}

StreamWriter::~StreamWriter()
{
}

StreamWriter &StreamWriter::operator=(StreamWriter &&writer)
{
    if (this != std::addressof(writer)) {
        std::swap(_stream, writer._stream);
        std::swap(_autoFlush, writer._autoFlush);
    }

    return *this;
}

bool StreamWriter::GetAutoFlush() const
{
    return _autoFlush;
}

void StreamWriter::SetAutoFlush(bool autoFlush)
{
    _autoFlush = autoFlush;
}

void StreamWriter::Flush()
{
    _stream->Flush();
}

void StreamWriter::Write(const char *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(buffer);

    _stream->Write(reinterpret_cast<const byte*>(buffer), offset, count);

    if (_autoFlush) {
        this->Flush();
    }
}
