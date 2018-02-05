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

#include "CFlat/Collections/Enumerable.Empty.Enumerator.h"

#include "CFlat.h"
#include "CFlat/ExceptionType.h"

using namespace CFlat;

/**************************************/
/* Private function definitions       */
/**************************************/

template <typename T>
Enumerable::EmptyEnumerable<T>::Enumerator::Enumerator()
{
}

template <typename T>
T Enumerable::EmptyEnumerable<T>::Enumerator::GetCurrent() const
{
    throw InvalidOperationException(String::Wrap("Enumeration has either not started or has already finished."));

    return T{};
}

template <typename T>
bool Enumerable::EmptyEnumerable<T>::Enumerator::MoveNext()
{
    return false;
}

template <typename T>
void Enumerable::EmptyEnumerable<T>::Enumerator::Reset()
{
}
