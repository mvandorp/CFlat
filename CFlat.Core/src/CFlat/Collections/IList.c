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

#include "CFlat/Collections/IList.h"

#include "CFlat.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const IListVTable *GetVTable(const IList *list);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructors */
public void IList_Constructor(
    IList *list,
    const IListVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetItem);
    Validate_NotNull(vtable->SetItem);
    Validate_NotNull(vtable->IndexOf);
    Validate_NotNull(vtable->Insert);
    Validate_NotNull(vtable->RemoveAt);

    ICollection_Constructor((ICollection*)list, (const ICollectionVTable*)vtable);
}

/* IEnumerable */
public IEnumerator *IList_GetEnumerator(const IList *list)
{
    return IEnumerable_GetEnumerator((const IEnumerable*)list);
}

/* ICollection */
public int IList_GetCount(const IList *list)
{
    return ICollection_GetCount((const ICollection*)list);
}

public bool IList_IsReadOnly(const IList *list)
{
    return ICollection_IsReadOnly((const ICollection*)list);
}

public void IList_Add(IList *list, const void *item)
{
    ICollection_Add((ICollection*)list, item);
}

public void IList_Clear(IList *list)
{
    ICollection_Clear((ICollection*)list);
}

public bool IList_Contains(const IList *list, const void *item)
{
    return ICollection_Contains((const ICollection*)list, item);
}

public void IList_CopyTo(const IList *list, void *destination, uintsize destinationSize)
{
    ICollection_CopyTo((const ICollection*)list, destination, destinationSize);
}

public bool IList_Remove(IList *list, const void *item)
{
    return ICollection_Remove((ICollection*)list, item);
}

/* IList */
public void *IList_GetItem(const IList *list, int index)
{
    return GetVTable(list)->GetItem(list, index);
}

public void IList_SetItem(IList *list, int index, const void *value)
{
    GetVTable(list)->SetItem(list, index, value);
}

public int IList_IndexOf(const IList *list, const void *item)
{
    return GetVTable(list)->IndexOf(list, item);
}

public void IList_Insert(IList *list, int index, const void *value)
{
    GetVTable(list)->Insert(list, index, value);
}

public void IList_RemoveAt(IList *list, int index)
{
    GetVTable(list)->RemoveAt(list, index);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
private const IListVTable *GetVTable(const IList *list)
{
    Validate_NotNull(list);

    return (const IListVTable*)((const Object*)list)->VTable;
}
