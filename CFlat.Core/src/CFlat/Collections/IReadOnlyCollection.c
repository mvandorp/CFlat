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

#include "CFlat/Collections/IReadOnlyCollection.h"

#include "CFlat.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const IReadOnlyCollectionVTable *GetVTable(const IReadOnlyCollection *collection);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructors */
public void IReadOnlyCollection_Constructor(
    IReadOnlyCollection *collection,
    const IReadOnlyCollectionVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetCount);
    Validate_NotNull(vtable->Contains);
    Validate_NotNull(vtable->CopyTo);

    IEnumerable_Constructor((IEnumerable*)collection, (const IEnumerableVTable*)vtable);
}

/* Properties */
public uintsize IReadOnlyCollection_GetCount(const IReadOnlyCollection *collection)
{
    return GetVTable(collection)->GetCount(collection);
}

/* Methods */
public bool IReadOnlyCollection_Contains(const IReadOnlyCollection *collection, const void *item)
{
    return GetVTable(collection)->Contains(collection, item);
}

public void IReadOnlyCollection_CopyTo(const IReadOnlyCollection *collection, void *destination)
{
    GetVTable(collection)->CopyTo(collection, destination);
}

/* IEnumerable */
public IEnumerator *IReadOnlyCollection_GetEnumerator(const IReadOnlyCollection *collection)
{
    return IEnumerable_GetEnumerator((const IEnumerable*)collection);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of an <see cref="IReadOnlyCollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IReadOnlyCollection"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
private const IReadOnlyCollectionVTable *GetVTable(const IReadOnlyCollection *collection)
{
    Validate_NotNull(collection);

    return (const IReadOnlyCollectionVTable*)((const Object*)collection)->VTable;
}
