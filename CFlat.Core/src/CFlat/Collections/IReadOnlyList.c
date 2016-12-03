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

#include "CFlat/Collections/IReadOnlyList.h"

#include "CFlat.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const IReadOnlyListVTable *GetVTable(const IReadOnlyList *list);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructors */
public void IReadOnlyList_Constructor(
    IReadOnlyList *list,
    const IReadOnlyListVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetItem);
    Validate_NotNull(vtable->IndexOf);

    ICollection_Constructor((ICollection*)list, (const ICollectionVTable*)vtable);
}

/* Methods */
public void *IReadOnlyList_GetItem(const IReadOnlyList *list, uintsize index)
{
    return GetVTable(list)->GetItem(list, index);
}

public uintsize IReadOnlyList_IndexOf(const IReadOnlyList *list, const void *item)
{
    return GetVTable(list)->IndexOf(list, item);
}

public bool __CFLAT_IREADONLYLIST_IsReadOnly(const IReadOnlyList *list)
{
    (void)list;

    throw_new(NotSupportedException, null);

    return true;
}

public void __CFLAT_IREADONLYLIST_Add(IReadOnlyList *list, void *item)
{
    (void)list;
    (void)item;

    throw_new(NotSupportedException, null);
}

public void __CFLAT_IREADONLYLIST_Clear(IReadOnlyList *list)
{
    (void)list;

    throw_new(NotSupportedException, null);
}

public bool __CFLAT_IREADONLYLIST_Remove(IReadOnlyList *list, const void *item)
{
    (void)list;
    (void)item;

    throw_new(NotSupportedException, null);

    return false;
}

/* IEnumerable */
public IEnumerator *IReadOnlyList_GetEnumerator(const IReadOnlyList *list)
{
    return IEnumerable_GetEnumerator((const IEnumerable*)list);
}

/* IReadOnlyCollection */
public uintsize IReadOnlyList_GetCount(const IReadOnlyList *list)
{
    return IReadOnlyCollection_GetCount((const IReadOnlyCollection*)list);
}

public bool IReadOnlyList_Contains(const IReadOnlyList *list, const void *item)
{
    return IReadOnlyCollection_Contains((const IReadOnlyCollection*)list, item);
}

public void IReadOnlyList_CopyTo(const IReadOnlyList *list, void *destination)
{
    IReadOnlyCollection_Contains((const IReadOnlyCollection*)list, destination);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of an <see cref="IReadOnlyList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
private const IReadOnlyListVTable *GetVTable(const IReadOnlyList *list)
{
    Validate_NotNull(list);

    return (const IReadOnlyListVTable*)((const Object*)list)->VTable;
}
