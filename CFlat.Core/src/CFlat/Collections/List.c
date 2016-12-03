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

#include "CFlat/Collections/List.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/ICollection.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/IList.h"
#include "CFlat/Collections/ListEnumerator.h"

/* Private constants */
/// <summary>
/// The default capacity for a list that is not empty.
/// </summary>
private const uintsize DefaultCapacity = 4;

/**************************************/
/* Private functions                  */
/**************************************/

private void EnsureCapacity(List *list, uintsize capacity);
private bool IsReadOnly(const List *list);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="List"/> class.
/// </summary>
private const IListVTable VTable = IListVTable_Initializer(
    (DestructorFunc)List_Destructor,
    (IEnumerable_GetEnumeratorFunc)List_GetEnumerator,
    (IReadOnlyCollection_GetCountFunc)List_GetCount,
    (ICollection_IsReadOnlyFunc)IsReadOnly,
    (ICollection_AddFunc)List_AddRef,
    (ICollection_ClearFunc)List_Clear,
    (IReadOnlyCollection_ContainsFunc)List_ContainsRef,
    (IReadOnlyCollection_CopyToFunc)List_CopyTo,
    (ICollection_RemoveFunc)List_RemoveRef,
    (IReadOnlyList_GetItemFunc)List_GetItemRef,
    (IList_SetItemFunc)List_SetItemRef,
    (IReadOnlyList_IndexOfFunc)List_IndexOfRef,
    (IList_InsertFunc)List_InsertRef,
    (IList_RemoveAtFunc)List_RemoveAt);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public List *List_New(uintsize elementSize, EqualityPredicate equals)
{
    return List_New_WithCapacity(elementSize, equals, 0);
}

public List *List_New_WithCapacity(uintsize elementSize, EqualityPredicate equals, uintsize capacity)
{
    List *list = Memory_Allocate(sizeof(List));

    try {
        List_Constructor_WithCapacity(list, elementSize, equals, capacity);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

public List *List_New_FromEnumerable(uintsize elementSize, EqualityPredicate equals, const IEnumerable *collection)
{
    List *list = Memory_Allocate(sizeof(List));

    try {
        List_Constructor_FromEnumerable(list, elementSize, equals, collection);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

public List *List_New_FromCollection(uintsize elementSize, EqualityPredicate equals, const ICollection *collection)
{
    List *list = Memory_Allocate(sizeof(List));

    try {
        List_Constructor_FromCollection(list, elementSize, equals, collection);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

/* Constructors */
public void List_Constructor(List *list, uintsize elementSize, EqualityPredicate equals)
{
    List_Constructor_WithCapacity(list, elementSize, equals, 0);
}

public void List_Constructor_WithCapacity(List *list, uintsize elementSize, EqualityPredicate equals, uintsize capacity)
{
    List_Constructor_Full(list, &VTable, elementSize, equals, capacity);
}

public void List_Constructor_FromEnumerable(
    List *list,
    uintsize elementSize,
    EqualityPredicate equals,
    const IEnumerable *collection)
{
    Validate_NotNull(collection);

    List_Constructor(list, elementSize, equals);
    List_AddRange(list, collection);
}

public void List_Constructor_FromCollection(
    List *list,
    uintsize elementSize,
    EqualityPredicate equals,
    const ICollection *collection)
{
    Validate_NotNull(collection);

    List_Constructor_WithCapacity(list, elementSize, equals, ICollection_GetCount(collection));
    List_AddRange(list, (const IEnumerable*)collection);
}

/* Destructor */
public void List_Destructor(List *list)
{
    Validate_NotNull(list);

    Memory_Deallocate(list->Array);
}

/* Properties */
public uintsize List_GetCapacity(const List *list)
{
    Validate_NotNull(list);

    return list->Capacity;
}

public void List_SetCapacity(List *list, uintsize capacity)
{
    Validate_NotNull(list);
    Validate_ArgumentRange(capacity >= list->Count,
        "Capacity cannot be smaller than the current length.", "capacity");
    Validate_ArgumentRange(capacity != InvalidIndex,
        "Capacity cannot be equal to the value of InvalidIndex.", "capacity");

    if (capacity != list->Capacity) {
        list->Array = Memory_Reallocate(list->Array, uintsize_CheckedMultiplication(capacity, list->ElementSize));
        list->Capacity = capacity;
    }
}

public uintsize List_GetElementSize(const List *list)
{
    Validate_NotNull(list);

    return list->ElementSize;
}

/* Methods */
public void List_AddRange(List *list, const IEnumerable *collection)
{
    Validate_NotNull(list);
    Validate_NotNull(collection);

    List_InsertRange(list, list->Count, collection);
}

public void List_InsertRange(List *list, uintsize index, const IEnumerable *collection)
{
    Validate_NotNull(list);
    Validate_NotNull(collection);
    Validate_ArgumentRange(index <= list->Count,
        "Index must be within the bounds of the List.", "index");

    IEnumerator *enumerator = IEnumerable_GetEnumerator(collection);

    try {
        uintsize i = index;

        while (IEnumerator_MoveNext(enumerator)) {
            List_InsertRef(list, i++, IEnumerator_GetCurrent(enumerator));
        }
    }
    finally {
        release(enumerator);
    }
    endtry;
}

public void List_RemoveRange(List *list, uintsize index, uintsize count)
{
    Validate_NotNull(list);
    Validate_ArgumentRange(index <= list->Count,
        "Index cannot be greater than the size of the string/array/collection.", "index");
    Validate_ArgumentRange(count <= list->Count - index,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize size = list->ElementSize;

    // Copy the contents of the buffer backward after index forward by length bytes.
    Memory_CopyOffset(
        list->Array, (index + count) * size,
        list->Array, count * size,
        (list->Count - (index + count)) * size);

    list->Count -= count;
    list->Version++;
}

public void *List_ToArray(const List *list)
{
    Validate_NotNull(list);

    uintsize size = list->ElementSize * list->Count;

    void *copy = Memory_Allocate(size);

    Memory_Copy(list->Array, copy, size);

    return copy;
}

public void List_TrimExcess(List *list)
{
    Validate_NotNull(list);

    if (list->Count < (list->Capacity * 9) / 10) {
        List_SetCapacity(list, list->Count);
    }
}

/* IEnumerable */
public IEnumerator *List_GetEnumerator(const List *list)
{
    return ListEnumerator_New((const IReadOnlyList*)list, (ListEnumerator_GetVersionFunc)List_GetVersion);
}

/* ICollection */
public uintsize List_GetCount(const List *list)
{
    Validate_NotNull(list);

    return list->Count;
}

public void List_AddRef(List *list, const void *item)
{
    Validate_NotNull(list);
    Validate_NotNull(item);

    List_InsertRef(list, list->Count, item);
}

public void List_Clear(List *list)
{
    Validate_NotNull(list);

    list->Count = 0;
    list->Version++;
}

public bool List_ContainsRef(const List *list, const void *item)
{
    return List_IndexOfRef(list, item) != InvalidIndex;
}

public void List_CopyTo(const List *list, void *destination)
{
    Validate_NotNull(list);
    Validate_NotNull(destination);

    Memory_Copy(list->Array, destination, list->Count * list->ElementSize);
}

public bool List_RemoveRef(List *list, const void *item)
{
    uintsize index = List_IndexOfRef(list, item);

    if (index != InvalidIndex) {
        List_RemoveAt(list, index);
    }

    return index != InvalidIndex;
}

/* IList */
public void *List_GetItemRef(const List *list, uintsize index)
{
    Validate_NotNull(list);
    Validate_ArgumentRange(index <= list->Count,
        "Index must be within the bounds of the List.", "index");

    return &list->Array[index * list->ElementSize];
}

public void List_SetItemRef(List *list, uintsize index, const void *item)
{
    Validate_NotNull(list);
    Validate_NotNull(item);

    Memory_Copy(item, List_GetItemRef(list, index), list->ElementSize);

    list->Version++;
}

public uintsize List_IndexOfRef(const List *list, const void *item)
{
    Validate_NotNull(list);
    Validate_NotNull(item);

    if (list->Equals == null) {
        throw_new(
            InvalidOperationException,
            "Cannot find the index of an element because an equality predicate is not set.");
    }

    byte *array = list->Array;
    uintsize size = list->ElementSize;
    uintsize count = list->Count;

    for (uintsize i = 0; i < count; i++) {
        if (list->Equals(&array[i * size], item)) {
            return i;
        }
    }

    return InvalidIndex;
}

public void List_InsertRef(List *list, uintsize index, const void *item)
{
    Validate_NotNull(list);
    Validate_NotNull(item);
    Validate_ArgumentRange(index <= list->Count,
        "Index must be within the bounds of the List.", "index");

    EnsureCapacity(list, uintsize_CheckedAddition(list->Count, 1));

    byte *array = list->Array;
    uintsize size = list->ElementSize;
    uintsize i = index;
    uintsize length = list->Count;

    if (i < length) {
        // Move the contents of the array after index forward by 1 index.
        Memory_Copy(
            &array[i * size],
            &array[(i + 1) * size],
            (length - i) * size);
    }

    // Insert the item.
    Memory_Copy(item, &array[i * size], size);

    list->Count++;
    list->Version++;
}

public void List_RemoveAt(List *list, uintsize index)
{
    List_RemoveRange(list, index, 1);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void List_Constructor_Full(
    List *list,
    const IListVTable *vtable,
    uintsize elementSize,
    EqualityPredicate equals,
    uintsize capacity)
{
    Validate_ArgumentRange(elementSize > 0, "Element size cannot be zero.", "elementSize");
    Validate_ArgumentRange(capacity != InvalidIndex,
        "Capacity cannot be equal to the value of InvalidIndex.", "capacity");

    IList_Constructor((IList*)list, vtable);

    list->Equals = equals;
    list->Array = null;
    list->Capacity = 0;
    list->Count = 0;
    list->ElementSize = elementSize;
    list->Version = 0;

    List_SetCapacity(list, capacity);
}

internal uintsize List_GetVersion(const List *list)
{
    Validate_NotNull(list);

    return list->Version;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void EnsureCapacity(List *list, uintsize minCapacity)
{
    assert(list != null);

    if (list->Capacity < minCapacity) {
        uintsize capacity;
        capacity = uintsize_Min(list->Count * 2, InvalidIndex - 1);
        capacity = uintsize_Max(capacity, minCapacity);
        capacity = uintsize_Max(capacity, DefaultCapacity);

        List_SetCapacity(list, capacity);
    }
}

private bool IsReadOnly(const List *list)
{
    Validate_NotNull(list);

    return false;
}
