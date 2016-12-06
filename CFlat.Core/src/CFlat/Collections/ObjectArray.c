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

#include "CFlat/Collections/ObjectArray.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private void ReleaseElement(void *obj);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="ObjectArray"/> class.
/// </summary>
private const IReadOnlyListVTable VTable = IReadOnlyListVTable_Initializer(
    (DestructorFunc)ObjectArray_Destructor,
    (IEnumerable_GetEnumeratorFunc)ObjectArray_GetEnumerator,
    (IReadOnlyCollection_GetCountFunc)ObjectArray_GetLength,
    (IReadOnlyCollection_ContainsFunc)ObjectArray_Contains,
    (IReadOnlyCollection_CopyToFunc)ObjectArray_CopyTo,
    (IReadOnlyList_GetItemFunc)ObjectArray_GetItem,
    (IReadOnlyList_IndexOfFunc)ObjectArray_IndexOf);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public ObjectArray *ObjectArray_New(void **source, uintsize length)
{
    ObjectArray *array = Memory_Allocate(sizeof(ObjectArray));

    try {
        ObjectArray_Constructor(array, source, length);

        Object_SetDeallocator(array, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(array);
        throw;
    }
    endtry;

    return array;
}

/* Constructors */
public void ObjectArray_Constructor(
    ObjectArray *array,
    void **source,
    uintsize length)
{
    ObjectArray_Constructor_Full(array, &VTable, source, length);
}

/* Destructor */
public void ObjectArray_Destructor(ObjectArray *array)
{
    PointerArray_Destructor((PointerArray*)array);
}

/* Properties */
public uintsize ObjectArray_GetLength(const ObjectArray *array)
{
    return PointerArray_GetLength((const PointerArray*)array);
}

/* Methods */
public void ObjectArray_SetItem(ObjectArray *array, uintsize index, const void *item)
{
    if (ObjectArray_GetItem(array, index) == item) {
        return;
    }

    PointerArray_SetItem((PointerArray*)array, index, item);
    retain_const(item);
}

/* IEnumerable */
public IEnumerator *ObjectArray_GetEnumerator(const ObjectArray *array)
{
    return PointerArray_GetEnumerator((const PointerArray*)array);
}

/* IReeadOnlyCollection */
public bool ObjectArray_Contains(const ObjectArray *array, const void *item)
{
    return PointerArray_Contains((const PointerArray*)array, item);
}

public void ObjectArray_CopyTo(const ObjectArray *array, void *destination)
{
    PointerArray_CopyTo((const PointerArray*)array, destination);

    IEnumerator *enumerator = ObjectArray_GetEnumerator(array);

    try {
        while (IEnumerator_MoveNext(enumerator)) {
            retain(IEnumerator_GetCurrent(enumerator));
        }
    }
    finally {
        release(enumerator);
    }
    endtry;
}

/* IReadOnlyList */
public void *ObjectArray_GetItem(const ObjectArray *array, uintsize index)
{
    return PointerArray_GetItem((const PointerArray*)array, index);
}

public uintsize ObjectArray_IndexOf(const ObjectArray *array, const void *item)
{
    return PointerArray_IndexOf((const PointerArray*)array, item);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void ObjectArray_Constructor_Full(
    ObjectArray *array,
    const IReadOnlyListVTable *vtable,
    void **source,
    uintsize length)
{
    PointerArray_Constructor_Full((PointerArray*)array, vtable, source, length, ReleaseElement);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void ReleaseElement(void *obj)
{
    release(obj);
}
