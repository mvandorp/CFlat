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

#include "CFlat/Collections/Enumerable.h"
//#include "CFlat/Collections/Enumerable.ConcatMany.h"
//#include "CFlat/Collections/Enumerable.ConcatTwo.h"
#include "CFlat/Collections/Enumerable.Empty.h"
//#include "CFlat/Collections/Enumerable.SinglePointer.h"
//#include "CFlat/Collections/Enumerable.SingleObject.h"

#include "CFlat.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

using namespace CFlat;

/**************************************/
/* Public function definitions        */
/**************************************/

template <typename T>
unique_ptr<IEnumerable<T>> Enumerable::Yield(const T &item)
{
    return SingleObjectEnumerable::New(item);
}

template <typename T>
unique_ptr<IEnumerable<T>> Enumerable::Concat(const IEnumerable<T> &first, const IEnumerable<T> &second)
{
    Validate_NotNull(first);
    Validate_NotNull(second);

    return ConcatTwo_New(first, second);
}

template <typename T>
unique_ptr<IEnumerable<T>> Enumerable::Concat(const IEnumerable<T> *enumerables[], uintsize count)
{
    Validate_Argument(count == 0 || enumerables != null,
        "Collection cannot be null if count is greater than zero.", "enumerables");

    Array<const IEnumerable<T>&> arr = ObjectArray_New(enumerables, count);

    return Enumerable::ConcatEnumerable(array);
}

template <typename T>
unique_ptr<IEnumerable<T>> Enumerable::Concat(const IEnumerable<const IEnumerable<T>*> &enumerables)
{
    Validate_NotNull(enumerables);
    Validate_Argument(Enumerable::All(enumerables, Predicate::IsNotNull),
        "Collection cannot contain a null pointer.", "enumerables");

    return ConcatMany_New(enumerables);
}
