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
#include "CFlat/IO/Stream.NullStream.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"

using namespace CFlat;

/* Private constants */
/// <summary>
/// The default buffer capacity to use when copying a stream.
/// </summary>
static const uintsize DefaultBufferSize = 81920;

/**************************************/
/* Public function definitions        */
/**************************************/

Stream::~Stream()
{
}

unique_ptr<Stream, NoOpDeleter<Stream>> Stream::Null()
{
    static NullStream instance = NullStream();

    return unique_ptr<Stream, NoOpDeleter<Stream>>(&instance);
}

void Stream::CopyTo(Stream &destination)
{
    this->CopyTo(destination, DefaultBufferSize);
}

void Stream::CopyTo(Stream &destination, uintsize bufferSize)
{
    Validate_IsTrue(this->CanWrite(), NotSupportedException(String::Wrap("The source stream does not support reading.")));
    Validate_IsTrue(destination.CanWrite(), NotSupportedException(String::Wrap("The destination stream does not support writing.")));
    Validate_ArgumentRange(bufferSize > 0, "Buffer size cannot be zero.", "bufferSize");

    unique_ptr<byte[]> buffer = unique_ptr<byte[]>(new byte[bufferSize]);

    uintsize bytesRead;

    while ((bytesRead = this->Read(buffer.Get(), 0, bufferSize)) != 0) {
        destination.Write(buffer.Get(), 0, bytesRead);
    }
}

int Stream::ReadByte()
{
    byte buffer[1];

    if (this->Read(buffer, 0, 1) == 0) {
        return -1;
    }

    return buffer[0];
}

void Stream::WriteByte(byte value)
{
    this->Write(&value, 0, 1);
}
