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

#include "CFlat/String.Enumerator.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

#include <utility>

using namespace CFlat;

/**************************************/
/* Public function definitions        */
/**************************************/

String::Enumerator::Enumerator(String str) :
    _string(std::move(str)),
    _current('\0'),
    _index(0)
{
}

String::Enumerator::~Enumerator()
{
}

const char &String::Enumerator::GetCurrent() const
{
    Validate_State(
        _index > 0 &&
        _index <= _string.GetLength(),
        "Enumeration has either not started or has already finished.");

    return _current;
}

bool String::Enumerator::MoveNext()
{
    if (_index < _string.GetLength()) {
        _current = _string[_index];
        _index++;

        return true;
    }
    else {
        _current = '\0';
        _index = UIntSize::CheckedAddition(_string.GetLength(), 1);

        return false;
    }
}

void String::Enumerator::Reset()
{
    _index = 0;
    _current = '\0';
}
