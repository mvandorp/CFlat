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

#include "CFlat/Collections/IEnumerable.h"

#include "CFlat.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const IEnumerableVTable *GetVTable(const IEnumerable *collection);

/**************************************/
/* Public function definitions        */
/**************************************/

public void IEnumerable_Constructor(
    IEnumerable *collection,
    const IEnumerableVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetEnumerator);

    Object_Constructor(collection, (const ObjectVTable*)vtable);
}

public IEnumerator *IEnumerable_GetEnumerator(const IEnumerable *collection)
{
    return GetVTable(collection)->GetEnumerator(collection);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of an <see cref="IEnumerable"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
private const IEnumerableVTable *GetVTable(const IEnumerable *collection)
{
    Validate_NotNull(collection);

    return (const IEnumerableVTable*)((const Object*)collection)->VTable;
}
