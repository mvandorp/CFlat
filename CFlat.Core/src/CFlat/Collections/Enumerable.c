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
#include "CFlat/Collections/Enumerable.ConcatMany.h"
#include "CFlat/Collections/Enumerable.ConcatTwo.h"
#include "CFlat/Collections/Enumerable.Empty.h"
#include "CFlat/Collections/Enumerable.SinglePointer.h"
#include "CFlat/Collections/Enumerable.SingleObject.h"

#include "CFlat.h"
#include "CFlat/const_cast.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/ObjectArray.h"

/**************************************/
/* Public function definitions        */
/**************************************/

public bool Enumerable_All(const IEnumerable *enumerable, Predicate predicate)
{
    Validate_NotNull(enumerable);
    Validate_NotNull(predicate);

    bool result = true;
    IEnumerator *enumerator = IEnumerable_GetEnumerator(enumerable);

    try {
        while (IEnumerator_MoveNext(enumerator)) {
            if (!predicate(IEnumerator_GetCurrent(enumerator))) {
                result = false;
                break;
            }
        }
    }
    finally {
        release(enumerator);
    }
    endtry;

    return result;
}

public bool Enumerable_Any(const IEnumerable *enumerable, Predicate predicate)
{
    Validate_NotNull(enumerable);
    Validate_NotNull(predicate);

    bool result = false;
    IEnumerator *enumerator = IEnumerable_GetEnumerator(enumerable);

    try {
        while (IEnumerator_MoveNext(enumerator)) {
            if (predicate(IEnumerator_GetCurrent(enumerator))) {
                result = true;
                break;
            }
        }
    }
    finally {
        release(enumerator);
    }
    endtry;

    return result;
}

public uintsize Enumerable_Count(const IEnumerable *enumerable)
{
    Validate_NotNull(enumerable);

    uintsize count = 0;

    IEnumerator *enumerator = IEnumerable_GetEnumerator(enumerable);

    try {
        while (IEnumerator_MoveNext(enumerator)) {
            count++;
        }
    }
    finally {
        release(enumerator);
    }
    endtry;

    return count;
}

public IEnumerable *Enumerable_Empty(void)
{
    return Empty_New();
}

public IEnumerable *Enumerable_FromSinglePointer(void *item, DestructorFunc itemDestructor)
{
    return SinglePointer_New(item, itemDestructor);
}

public IEnumerable *Enumerable_FromSingleObject(Object *item)
{
    return SingleObjectEnumerable_New(item);
}

public IEnumerable *Enumerable_Concat(const IEnumerable *first, const IEnumerable *second)
{
    Validate_NotNull(first);
    Validate_NotNull(second);

    return ConcatTwo_New(first, second);
}

public IEnumerable *Enumerable_ConcatArray(const IEnumerable * const *enumerables, uintsize count)
{
    Validate_Argument(count == 0 || enumerables != null,
        "Collection cannot be null if count is greater than zero.", "enumerables");

    IEnumerable *result = null;
    IEnumerable *array = (IEnumerable*)ObjectArray_New(const_cast(enumerables), count);

    try {
        result = Enumerable_ConcatEnumerable(array);
    }
    finally {
        release(array);
    }
    endtry;

    return result;
}

public IEnumerable *Enumerable_ConcatEnumerable(const IEnumerable *enumerables)
{
    Validate_NotNull(enumerables);
    Validate_Argument(Enumerable_All(enumerables, Predicate_IsNotNull),
        "Collection cannot contain a null pointer.", "enumerables");

    return ConcatMany_New(enumerables);
}
