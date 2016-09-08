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

#include "CFlat/Collections/ICollection.h"

#include "CFlat.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const ICollectionVTable *GetVTable(const ICollection *collection);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructors */
public void ICollection_Constructor(
    ICollection *collection,
    const ICollectionVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetCount);
    Validate_NotNull(vtable->IsReadOnly);
    Validate_NotNull(vtable->Add);
    Validate_NotNull(vtable->Clear);
    Validate_NotNull(vtable->Contains);
    Validate_NotNull(vtable->CopyTo);
    Validate_NotNull(vtable->Remove);

    IEnumerable_Constructor((IEnumerable*)collection, (const IEnumerableVTable*)vtable);
}

/* IEnumerable */
public IEnumerator *ICollection_GetEnumerator(const ICollection *collection)
{
    return IEnumerable_GetEnumerator((const IEnumerable*)collection);
}

/* Properties */
public int ICollection_GetCount(const ICollection *collection)
{
    return GetVTable(collection)->GetCount(collection);
}

public bool ICollection_IsReadOnly(const ICollection *collection)
{
    return GetVTable(collection)->IsReadOnly(collection);
}

/* Methods */
public void ICollection_Add(ICollection *collection, void *item)
{
    GetVTable(collection)->Add(collection, item);
}

public void ICollection_Clear(ICollection *collection)
{
    GetVTable(collection)->Clear(collection);
}

public bool ICollection_Contains(const ICollection *collection, const void *item)
{
    return GetVTable(collection)->Contains(collection, item);
}

public void ICollection_CopyTo(const ICollection *collection, void *destination)
{
    GetVTable(collection)->CopyTo(collection, destination);
}

public bool ICollection_Remove(ICollection *collection, const void *item)
{
    return GetVTable(collection)->Remove(collection, item);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of an <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
private const ICollectionVTable *GetVTable(const ICollection *collection)
{
    Validate_NotNull(collection);

    return (const ICollectionVTable*)((const Object*)collection)->VTable;
}
