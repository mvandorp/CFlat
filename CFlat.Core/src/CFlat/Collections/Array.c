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

#include "CFlat/Collections/Array.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/ListEnumerator.h"

 /**************************************/
 /* Private functions                  */
 /**************************************/

private uintsize GetVersion(const IReadOnlyList *list);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="Array"/> class.
/// </summary>
private const IReadOnlyListVTable VTable = IReadOnlyListVTable_Initializer(
    (DestructorFunc)Array_Destructor,
    (IEnumerable_GetEnumeratorFunc)Array_GetEnumerator,
    (IReadOnlyCollection_GetCountFunc)Array_GetLength,
    (IReadOnlyCollection_ContainsFunc)Array_ContainsRef,
    (IReadOnlyCollection_CopyToFunc)Array_CopyTo,
    (IReadOnlyList_GetItemFunc)Array_GetItemRef,
    (IReadOnlyList_IndexOfFunc)Array_IndexOfRef);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public Array *Array_New(void *source, uintsize length, uintsize elementSize, EqualityPredicate equals)
{
    Array *array = Memory_Allocate(sizeof(Array));

    try {
        Array_Constructor(array, source, length, elementSize, equals);

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
public void Array_Constructor(
    Array *array,
    void *source,
    uintsize length,
    uintsize elementSize,
    EqualityPredicate equals)
{
    Array_Constructor_Full(array, &VTable, source, length, elementSize, equals);
}

/* Destructor */
public void Array_Destructor(Array *array)
{
    Validate_NotNull(array);

    Memory_Deallocate(array->Array);
}

/* Properties */
public uintsize Array_GetElementSize(const Array *array)
{
    Validate_NotNull(array);

    return array->ElementSize;
}

public uintsize Array_GetLength(const Array *array)
{
    Validate_NotNull(array);

    return array->Length;
}

/* Methods */
public void Array_SetItemRef(Array *array, uintsize index, const void *item)
{
    Validate_NotNull(array);
    Validate_NotNull(item);

    Memory_Copy(item, Array_GetItemRef(array, index), array->ElementSize);;
}

/* IEnumerable */
public IEnumerator *Array_GetEnumerator(const Array *array)
{
    return ListEnumerator_New((const IReadOnlyList*)array, (ListEnumerator_GetVersionFunc)GetVersion);
}

/* IReeadOnlyCollection */
public bool Array_ContainsRef(const Array *array, const void *item)
{
    return Array_IndexOfRef(array, item) != InvalidIndex;
}

public void Array_CopyTo(const Array *array, void *destination)
{
    Validate_NotNull(array);
    Validate_NotNull(destination);

    Memory_Copy(array->Array, destination, array->Length * array->ElementSize);
}

/* IReadOnlyList */
public void *Array_GetItemRef(const Array *array, uintsize index)
{
    Validate_NotNull(array);
    Validate_ArgumentRange(index <= array->Length,
        "Index must be within the bounds of the Array.", "index");

    return &array->Array[index * array->ElementSize];
}

public uintsize Array_IndexOfRef(const Array *array, const void *item)
{
    Validate_NotNull(array);
    Validate_NotNull(item);

    if (array->Equals == null) {
        throw_new(
            InvalidOperationException,
            "Cannot find the index of an element because an equality predicate is not set.");
    }

    byte *source = array->Array;
    uintsize size = array->ElementSize;
    uintsize count = array->Length;

    for (uintsize i = 0; i < count; i++) {
        if (array->Equals(&source[i * size], item)) {
            return i;
        }
    }

    return InvalidIndex;
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void Array_Constructor_Full(
    Array *array,
    const IReadOnlyListVTable *vtable,
    void *source,
    uintsize length,
    uintsize elementSize,
    EqualityPredicate equals)
{
    Validate_NotNull(source);
    Validate_ArgumentRange(elementSize > 0, "Element size cannot be zero.", "elementSize");

    IReadOnlyList_Constructor((IReadOnlyList*)array, vtable);

    array->Array = source;
    array->Length = length;
    array->ElementSize = elementSize;
    array->Equals = equals;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private uintsize GetVersion(const IReadOnlyList *list)
{
    Validate_NotNull(list);

    return 0;
}