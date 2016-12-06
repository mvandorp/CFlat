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

#include "CFlat/Collections/PointerArray.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private bool PointerEquals(const void **x, const void **y);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="PointerArray"/> class.
/// </summary>
private const IReadOnlyListVTable VTable = IReadOnlyListVTable_Initializer(
    (DestructorFunc)PointerArray_Destructor,
    (IEnumerable_GetEnumeratorFunc)PointerArray_GetEnumerator,
    (IReadOnlyCollection_GetCountFunc)PointerArray_GetLength,
    (IReadOnlyCollection_ContainsFunc)PointerArray_Contains,
    (IReadOnlyCollection_CopyToFunc)PointerArray_CopyTo,
    (IReadOnlyList_GetItemFunc)PointerArray_GetItem,
    (IReadOnlyList_IndexOfFunc)PointerArray_IndexOf);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public PointerArray *PointerArray_New(void **source, uintsize length, DestructorFunc elementDestructor)
{
    PointerArray *array = Memory_Allocate(sizeof(PointerArray));

    try {
        PointerArray_Constructor(array, source, length, elementDestructor);

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
public void PointerArray_Constructor(
    PointerArray *array,
    void **source,
    uintsize length,
    DestructorFunc elementDestructor)
{
    PointerArray_Constructor_Full(array, &VTable, source, length, elementDestructor);
}

/* Destructor */
public void PointerArray_Destructor(PointerArray *array)
{
    Validate_NotNull(array);

    // Clear the contents of the array, so that all pointers are destroyed.
    if (array->ElementDestructor != null) {
        uintsize length = PointerArray_GetLength(array);

        for (uintsize i = 0; i < length; i++) {
            PointerArray_SetItem(array, i, null);
        }
    }

    Array_Destructor((Array*)array);
}

/* Properties */
public uintsize PointerArray_GetLength(const PointerArray *array)
{
    return Array_GetLength((const Array*)array);
}

/* Methods */
public void PointerArray_SetItem(PointerArray *array, uintsize index, const void *item)
{
    Validate_NotNull(array);

    if (array->ElementDestructor != null) {
        void *oldItem = PointerArray_GetItem(array, index);

        if (oldItem == item) {
            return;
        }
        else if (oldItem != null) {
            array->ElementDestructor(oldItem);
        }
    }

    Array_SetItem((Array*)array, index, item);
}

/* IEnumerable */
public IEnumerator *PointerArray_GetEnumerator(const PointerArray *array)
{
    return Array_GetEnumerator((const Array*)array);
}

/* IReeadOnlyCollection */
public bool PointerArray_Contains(const PointerArray *array, const void *item)
{
    return Array_Contains((const Array*)array, item);
}

public void PointerArray_CopyTo(const PointerArray *array, void *destination)
{
    Array_CopyTo((const Array*)array, destination);
}

/* IReadOnlyList */
public void *PointerArray_GetItem(const PointerArray *array, uintsize index)
{
    return Array_GetItem((const Array*)array, index, void*);
}

public uintsize PointerArray_IndexOf(const PointerArray *array, const void *item)
{
    return Array_IndexOf((const Array*)array, item);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void PointerArray_Constructor_Full(
    PointerArray *array,
    const IReadOnlyListVTable *vtable,
    void **source,
    uintsize length,
    DestructorFunc elementDestructor)
{
    Array_Constructor_Full((Array*)array, vtable, source, length, sizeof(void*), (EqualityPredicate)PointerEquals);

    array->ElementDestructor = elementDestructor;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private bool PointerEquals(const void **x, const void **y)
{
    return *x == *y;
}