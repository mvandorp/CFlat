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

#include "CFlat/Collections/ObjectList.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private bool IsReadOnly(const ObjectList *list);
private void ReleaseElement(void *obj);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="ObjectList"/> class.
/// </summary>
private const IListVTable VTable = IListVTable_Initializer(
    (DestructorFunc)ObjectList_Destructor,
    (IEnumerable_GetEnumeratorFunc)ObjectList_GetEnumerator,
    (ICollection_GetCountFunc)ObjectList_GetCount,
    (ICollection_IsReadOnlyFunc)IsReadOnly,
    (ICollection_AddFunc)ObjectList_Add,
    (ICollection_ClearFunc)ObjectList_Clear,
    (ICollection_ContainsFunc)ObjectList_Contains,
    (ICollection_CopyToFunc)ObjectList_CopyTo,
    (ICollection_RemoveFunc)ObjectList_Remove,
    (IList_GetItemFunc)ObjectList_GetItem,
    (IList_SetItemFunc)ObjectList_SetItem,
    (IList_IndexOfFunc)ObjectList_IndexOf,
    (IList_InsertFunc)ObjectList_Insert,
    (IList_RemoveAtFunc)ObjectList_RemoveAt);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public ObjectList *ObjectList_New(void)
{
    return ObjectList_New_WithCapacity(0);
}

public ObjectList *ObjectList_New_WithCapacity(int capacity)
{
    ObjectList *list = Memory_Allocate(sizeof(ObjectList));

    try {
        ObjectList_Constructor_WithCapacity(list, capacity);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

public ObjectList *ObjectList_New_FromEnumerable(const IEnumerable *collection)
{
    ObjectList *list = Memory_Allocate(sizeof(ObjectList));

    try {
        ObjectList_Constructor_FromEnumerable(list, collection);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

public ObjectList *ObjectList_New_FromCollection(const ICollection *collection)
{
    ObjectList *list = Memory_Allocate(sizeof(ObjectList));

    try {
        ObjectList_Constructor_FromCollection(list, collection);

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
public void ObjectList_Constructor(ObjectList *list)
{
    ObjectList_Constructor_WithCapacity(list, 0);
}

public void ObjectList_Constructor_WithCapacity(ObjectList *list, int capacity)
{
    ObjectList_Constructor_Full(list, &VTable, capacity);
}

public void ObjectList_Constructor_FromEnumerable(
    ObjectList *list,
    const IEnumerable *collection)
{
    Validate_NotNull(collection);

    ObjectList_Constructor(list);
    ObjectList_AddRange(list, collection);
}

public void ObjectList_Constructor_FromCollection(
    ObjectList *list,
    const ICollection *collection)
{
    Validate_NotNull(collection);

    ObjectList_Constructor_WithCapacity(list, ICollection_GetCount(collection));
    ObjectList_AddRange(list, (const IEnumerable*)collection);
}

/* Destructor */
public void ObjectList_Destructor(ObjectList *list)
{
    PointerList_Destructor((PointerList*)list);
}

/* Properties */
public int ObjectList_GetCapacity(const ObjectList *list)
{
    return PointerList_GetCapacity((const PointerList*)list);
}

public void ObjectList_SetCapacity(ObjectList *list, int capacity)
{
    PointerList_SetCapacity((PointerList*)list, capacity);
}

/* Methods */
public void ObjectList_AddRange(ObjectList *list, const IEnumerable *collection)
{
    ObjectList_InsertRange(list, ObjectList_GetCount(list), collection);
}

public void ObjectList_InsertRange(ObjectList *list, int index, const IEnumerable *collection)
{
    Validate_NotNull(list);
    Validate_NotNull(collection);
    Validate_ArgumentRange(
        index >= 0 && index <= ObjectList_GetCount(list),
        "Index must be within the bounds of the List.", "index");

    IEnumerator *enumerator = IEnumerable_GetEnumerator(collection);

    try {
        int i = index;

        while (IEnumerator_MoveNext(enumerator)) {
            ObjectList_Insert(list, i++, IEnumerator_GetCurrent(enumerator));
        }
    }
    finally {
        release(enumerator);
    }
    endtry;
}

public void ObjectList_RemoveRange(ObjectList *list, int index, int count)
{
    PointerList_RemoveRange((PointerList*)list, index, count);
}

public void *ObjectList_ToArray(const ObjectList *list)
{
    void *array = PointerList_ToArray((const PointerList*)list);

    IEnumerator *enumerator = ObjectList_GetEnumerator(list);

    try {
        while (IEnumerator_MoveNext(enumerator)) {
            retain(IEnumerator_GetCurrent(enumerator));
        }
    }
    finally {
        release(enumerator);
    }
    endtry;

    return array;
}

public void ObjectList_TrimExcess(ObjectList *list)
{
    PointerList_TrimExcess((PointerList*)list);
}

/* IEnumerable */
public IEnumerator *ObjectList_GetEnumerator(const ObjectList *list)
{
    return PointerList_GetEnumerator((const PointerList*)list);
}

/* ICollection */
public int ObjectList_GetCount(const ObjectList *list)
{
    return PointerList_GetCount((const PointerList*)list);
}

public void ObjectList_Add(ObjectList *list, void *item)
{
    PointerList_Add((PointerList*)list, item);
    retain(item);
}

public void ObjectList_Clear(ObjectList *list)
{
    PointerList_Clear((PointerList*)list);
}

public bool ObjectList_Contains(const ObjectList *list, const void *item)
{
    return PointerList_Contains((const PointerList*)list, item);
}

public void ObjectList_CopyTo(const ObjectList *list, void *destination)
{
    PointerList_CopyTo((const PointerList*)list, destination);

    IEnumerator *enumerator = ObjectList_GetEnumerator(list);

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

public bool ObjectList_Remove(ObjectList *list, const void *item)
{
    return PointerList_Remove((PointerList*)list, item);
}

/* IList */
public void *ObjectList_GetItem(const ObjectList *list, int index)
{
    return PointerList_GetItem((const PointerList*)list, index);
}

public void ObjectList_SetItem(ObjectList *list, int index, const void *item)
{
    if (ObjectList_GetItem(list, index) == item) {
        return;
    }

    PointerList_SetItem((PointerList*)list, index, item);
    retain_const(item);
}

public int ObjectList_IndexOf(const ObjectList *list, const void *item)
{
    return PointerList_IndexOf((const PointerList*)list, item);
}

public void ObjectList_Insert(ObjectList *list, int index, void *item)
{
    PointerList_Insert((PointerList*)list, index, item);
    retain(item);
}

public void ObjectList_RemoveAt(ObjectList *list, int index)
{
    PointerList_RemoveAt((PointerList*)list, index);
}

/**************************************/
/* Internal function definitions      */
/**************************************/
internal void ObjectList_Constructor_Full(
    ObjectList *list,
    const IListVTable *vtable,
    int capacity)
{
    PointerList_Constructor_Full((PointerList*)list, vtable, ReleaseElement, capacity);
}

internal uintsize ObjectList_GetVersion(const ObjectList *list)
{
    return PointerList_GetVersion((const PointerList*)list);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private bool IsReadOnly(const ObjectList *list)
{
    Validate_NotNull(list);

    return false;
}

private void ReleaseElement(void *obj)
{
    release(obj);
}
