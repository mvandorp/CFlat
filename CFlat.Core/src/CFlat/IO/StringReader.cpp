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

#include "CFlat/IO/StringReader.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

#include <utility>

using namespace CFlat;

/**************************************/
/* Public function definitions        */
/**************************************/

StringReader::StringReader(String str) : _value(std::move(str))
{
}

int StringReader::Peek() const
{
    return this->Peek(0);
}

int StringReader::Peek(uintsize offset) const
{
    if (UIntSize::CheckedAddition(_position, offset) >= _value.GetLength()) {
        return -1;
    }
    else {
        return _value[_position + offset];
    }
}

int StringReader::Read()
{
    if (_position >= _value.GetLength()) {
        return -1;
    }
    else {
        return _value[_position++];
    }
}

uintsize StringReader::Read(char *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(buffer);

    if (count == 0) return 0;

    // The number of characters read.
    uintsize charactersRead = 0;

    // The number of characters remaining.
    uintsize remaining = _value.GetLength() - _position;

    if (remaining > 0) {
        charactersRead = UIntSize::Min(remaining, count);

        Memory::Copy(_value.GetCString(), _position, buffer, offset, charactersRead);

        _position += charactersRead;
    }

    return charactersRead;
}

void StringReader::Skip(uintsize amount)
{
    uintsize length = _value.GetLength();

    if (UIntSize::CheckedAddition(_position, amount) >= length) {
        _position = length;
    }
    else {
        _position += amount;
    }
}
