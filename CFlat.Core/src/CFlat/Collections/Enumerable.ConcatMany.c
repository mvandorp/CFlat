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

#include "CFlat/Collections/Enumerable.ConcatMany.h"
#include "CFlat/Collections/Enumerable.ConcatMany.Enumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/Enumerable.h"
#include "CFlat/Collections/IEnumerable.h"

/* Types */
typedef struct ConcatMany {
    IEnumerable Base;
    const IEnumerable *Enumerables;
} ConcatMany;

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(ConcatMany *enumerable, const IEnumerable *enumerables);
private void Destructor(ConcatMany *enumerable);
private void *GetEnumerator(const ConcatMany *enumerable);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="ConcatMany"/> class.
/// </summary>
private const IEnumerableVTable VTable = IEnumerableVTable_Initializer(
    (DestructorFunc)Destructor,
    (IEnumerable_GetEnumeratorFunc)GetEnumerator);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerable *ConcatMany_New(const IEnumerable *enumerables)
{
    ConcatMany *enumerable = Memory_Allocate(sizeof(ConcatMany));

    try {
        Constructor(enumerable, enumerables);

        Object_SetDeallocator(enumerable, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(enumerable);
        throw;
    }
    endtry;

    return (IEnumerable*)enumerable;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void Constructor(ConcatMany *enumerable, const IEnumerable *enumerables)
{
    assert(enumerable != null);
    assert(enumerables != null);
    assert(Enumerable_All(enumerables, Predicate_IsNotNull));

    IEnumerable_Constructor((IEnumerable*)enumerable, &VTable);

    enumerable->Enumerables = retain_const(enumerables);
}

private void Destructor(ConcatMany *enumerable)
{
    assert(enumerable != null);

    release(enumerable->Enumerables);
}

/* IEnumerable */
private void *GetEnumerator(const ConcatMany *enumerable)
{
    Validate_NotNull(enumerable);

    return ConcatManyEnumerator_New(enumerable->Enumerables);
}
