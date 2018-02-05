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

#include "CFlat/IO/TextReader.h"
#include "CFlat/IO/TextReader.NullTextReader.h"

#include "CFlat.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"

#include <utility>

using namespace CFlat;

/* Private constants */
/// <summary>
/// The default buffer capacity to use when reading.
/// </summary>
static const uintsize DefaultBufferSize = 4096;

/**************************************/
/* Public function definitions        */
/**************************************/

TextReader::~TextReader()
{
}

unique_ptr<TextReader, NoOpDeleter<TextReader>> TextReader::Null()
{
    static NullReader instance = NullReader();

    return unique_ptr<TextReader, NoOpDeleter<TextReader>>(&instance);
}

String TextReader::ReadLine()
{
    // If we reached the end of the stream, return null.
    if (this->Peek() == -1) return String::Empty;

    StringBuilder sb = StringBuilder();

    while (true) {
        int ch = this->Read();

        // Deal with CR+LF line endings.
        if (ch == '\r' && this->Peek() == '\n') {
            this->Read();
            break;
        }

        if (ch == -1 || ch == '\r' || ch == '\n') break;

        sb.Append((char)ch);
    }

    return StringBuilder::ToString(std::move(sb));
}

String TextReader::ReadToEnd()
{
    unique_ptr<char> buffer = unique_ptr<char>(new char[DefaultBufferSize]);

    StringBuilder sb = StringBuilder();
    uintsize bytesRead;

    while ((bytesRead = this->Read(buffer.Get(), 0, DefaultBufferSize)) != 0) {
        sb.Append(buffer.Get(), 0, bytesRead);
    }

    return StringBuilder::ToString(std::move(sb));
}
