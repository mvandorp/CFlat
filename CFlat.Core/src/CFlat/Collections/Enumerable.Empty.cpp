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

#include "CFlat/Collections/Enumerable.Empty.h"
#include "CFlat/Collections/Enumerable.Empty.Enumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/Enumerable.h"
#include "CFlat/Collections/IEnumerable.h"

using namespace CFlat;

/**************************************/
/* Public function definitions       */
/**************************************/

template <typename T>
Enumerable::EmptyEnumerable<T>::EmptyEnumerable()
{
}

/* IEnumerable */
template <typename T>
unique_ptr<IEnumerator<T>> Enumerable::EmptyEnumerable<T>::GetEnumerator() const
{
    Validate_NotNull(enumerable);

    return EmptyEnumerator_New();
}
