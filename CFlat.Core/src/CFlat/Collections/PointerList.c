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

#include "CFlat/Collections/PointerList.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private bool PointerEquals(const void **x, const void **y);
private bool IsReadOnly(const PointerList *list);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="PointerList"/> class.
/// </summary>
private const IListVTable VTable = IListVTable_Initializer(
    (DestructorFunc)PointerList_Destructor,
    (IEnumerable_GetEnumeratorFunc)PointerList_GetEnumerator,
    (ICollection_GetCountFunc)PointerList_GetCount,
    (ICollection_IsReadOnlyFunc)IsReadOnly,
    (ICollection_AddFunc)PointerList_Add,
    (ICollection_ClearFunc)PointerList_Clear,
    (ICollection_ContainsFunc)PointerList_Contains,
    (ICollection_CopyToFunc)PointerList_CopyTo,
    (ICollection_RemoveFunc)PointerList_Remove,
    (IList_GetItemFunc)PointerList_GetItem,
    (IList_SetItemFunc)PointerList_SetItem,
    (IList_IndexOfFunc)PointerList_IndexOf,
    (IList_InsertFunc)PointerList_Insert,
    (IList_RemoveAtFunc)PointerList_RemoveAt);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public PointerList *PointerList_New(DestructorFunc elementDestructor)
{
    return PointerList_New_WithCapacity(elementDestructor, 0);
}

public PointerList *PointerList_New_WithCapacity(DestructorFunc elementDestructor, int capacity)
{
    PointerList *list = Memory_Allocate(sizeof(PointerList));

    try {
        PointerList_Constructor_WithCapacity(list, elementDestructor, capacity);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

public PointerList *PointerList_New_FromEnumerable(DestructorFunc elementDestructor, const IEnumerable *collection)
{
    PointerList *list = Memory_Allocate(sizeof(PointerList));

    try {
        PointerList_Constructor_FromEnumerable(list, elementDestructor, collection);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

public PointerList *PointerList_New_FromCollection(DestructorFunc elementDestructor, const ICollection *collection)
{
    PointerList *list = Memory_Allocate(sizeof(PointerList));

    try {
        PointerList_Constructor_FromCollection(list, elementDestructor, collection);

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
public void PointerList_Constructor(PointerList *list, DestructorFunc elementDestructor)
{
    PointerList_Constructor_WithCapacity(list, elementDestructor, 0);
}

public void PointerList_Constructor_WithCapacity(PointerList *list, DestructorFunc elementDestructor, int capacity)
{
    PointerList_Constructor_Full(list, &VTable, elementDestructor, capacity);
}

public void PointerList_Constructor_FromEnumerable(
    PointerList *list,
    DestructorFunc elementDestructor,
    const IEnumerable *collection)
{
    Validate_NotNull(collection);

    PointerList_Constructor(list, elementDestructor);
    PointerList_AddRange(list, collection);
}

public void PointerList_Constructor_FromCollection(
    PointerList *list,
    DestructorFunc elementDestructor,
    const ICollection *collection)
{
    Validate_NotNull(collection);

    PointerList_Constructor_WithCapacity(list, elementDestructor, ICollection_GetCount(collection));
    PointerList_AddRange(list, (const IEnumerable*)collection);
}

/* Destructor */
public void PointerList_Destructor(PointerList *list)
{
    PointerList_Clear(list);

    List_Destructor((List*)list);
}

/* Properties */
public int PointerList_GetCapacity(const PointerList *list)
{
    return List_GetCapacity((const List*)list);
}

public void PointerList_SetCapacity(PointerList *list, int capacity)
{
    List_SetCapacity((List*)list, capacity);
}

/* Methods */
public void PointerList_AddRange(PointerList *list, const IEnumerable *collection)
{
    List_AddRange((List*)list, collection);
}

public void PointerList_InsertRange(PointerList *list, int index, const IEnumerable *collection)
{
    List_InsertRange((List*)list, index, collection);
}

public void PointerList_RemoveRange(PointerList *list, int index, int count)
{
    Validate_NotNull(list);
    Validate_IsTrue(index >= 0, ArgumentOutOfRangeException, "Index cannot be negative.");
    Validate_IsTrue(count >= 0, ArgumentOutOfRangeException, "Count cannot be negative.");
    Validate_IsTrue(
        index + count >= PointerList_GetCount(list),
        ArgumentOutOfRangeException,
        "Index and count were out of bounds for the list or count is greater than the number of elements from index to "
        "the end of the list.");

    if (list->ElementDestructor != null) {
        for (int i = index; i < index + count; i++) {
            PointerList_SetItem(list, i, null);
        }
    }

    List_RemoveRange((List*)list, index, count);
}

/* IEnumerable */
public IEnumerator *PointerList_GetEnumerator(const PointerList *list)
{
    return List_GetEnumerator((const List*)list);
}

/* ICollection */
public int PointerList_GetCount(const PointerList *list)
{
    return List_GetCount((const List*)list);
}

public void PointerList_Add(PointerList *list, void *item)
{
    List_Add((List*)list, item);
}

public void PointerList_Clear(PointerList *list)
{
    Validate_NotNull(list);

    if (list->ElementDestructor != null) {
        int count = PointerList_GetCount(list);

        for (int i = 0; i < count; i++) {
            PointerList_SetItem(list, i, null);
        }
    }

    List_Clear((List*)list);
}

public bool PointerList_Contains(const PointerList *list, const void *item)
{
    return List_Contains((const List*)list, item);
}

public void PointerList_CopyTo(const PointerList *list, void *destination, uintsize destinationSize)
{
    List_CopyTo((const List*)list, destination, destinationSize);
}

public bool PointerList_Remove(PointerList *list, const void *item)
{
    int index = PointerList_IndexOf(list, item);

    if (index >= 0) {
        PointerList_RemoveAt(list, index);
    }

    return index >= 0;
}

/* IList */
public void *PointerList_GetItem(const PointerList *list, int index)
{
    return List_GetItem((const List*)list, index, void*);
}

public void PointerList_SetItem(PointerList *list, int index, const void *item)
{
    Validate_NotNull(list);

    if (list->ElementDestructor != null) {
        void *oldItem = PointerList_GetItem(list, index);

        if (oldItem == item) {
            return;
        }
        else if (oldItem != null) {
            list->ElementDestructor(oldItem);
        }
    }

    List_SetItem((List*)list, index, item);
}

public int PointerList_IndexOf(const PointerList *list, const void *item)
{
    return List_IndexOf((const List*)list, item);
}

public void PointerList_Insert(PointerList *list, int index, void *item)
{
    List_Insert((List*)list, index, item);
}

public void PointerList_RemoveAt(PointerList *list, int index)
{
    Validate_NotNull(list);

    if (list->ElementDestructor != null) {
        void *item = PointerList_GetItem(list, index);

        if (item != null) {
            list->ElementDestructor(item);
        }
    }

    List_RemoveAt((List*)list, index);
}

/**************************************/
/* Internal function definitions      */
/**************************************/
internal void PointerList_Constructor_Full(
    PointerList *list,
    const IListVTable *vtable,
    DestructorFunc elementDestructor,
    int capacity)
{
    List_Constructor_Full((List*)list, vtable, sizeof(void*), (EqualityPredicate)PointerEquals, capacity);

    list->ElementDestructor = elementDestructor;;
}

internal uintsize PointerList_GetVersion(const PointerList *list)
{
    return List_GetVersion((const List*)list);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private bool PointerEquals(const void **x, const void **y)
{
    return *x == *y;
}

private bool IsReadOnly(const PointerList *list)
{
    Validate_NotNull(list);

    return false;
}
