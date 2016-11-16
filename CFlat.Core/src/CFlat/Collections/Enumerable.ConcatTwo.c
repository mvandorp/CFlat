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

#include "CFlat/Collections/Enumerable.ConcatTwo.h"
#include "CFlat/Collections/Enumerable.ConcatTwo.Enumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"

/* Types */
typedef struct ConcatTwo {
    IEnumerable Base;
    const IEnumerable *First;
    const IEnumerable *Second;
} ConcatTwo;

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(ConcatTwo *enumerable, const IEnumerable *first, const IEnumerable *second);
private void Destructor(ConcatTwo *enumerable);
private void *GetEnumerator(const ConcatTwo *enumerable);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="ConcatTwo"/> class.
/// </summary>
private const IEnumerableVTable VTable = IEnumerableVTable_Initializer(
    (DestructorFunc)Destructor,
    (IEnumerable_GetEnumeratorFunc)GetEnumerator);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerable *ConcatTwo_New(const IEnumerable *first, const IEnumerable *second)
{
    ConcatTwo *enumerable = Memory_Allocate(sizeof(ConcatTwo));

    try {
        Constructor(enumerable, first, second);

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

private void Constructor(ConcatTwo *enumerable, const IEnumerable *first, const IEnumerable *second)
{
    assert(enumerable != null);
    assert(first != null);
    assert(second != null);

    IEnumerable_Constructor((IEnumerable*)enumerable, &VTable);

    enumerable->First = retain_const(first);
    enumerable->Second = retain_const(second);
}

private void Destructor(ConcatTwo *enumerable)
{
    assert(enumerable != null);

    release(enumerable->First);
    release(enumerable->Second);
}

/* IEnumerable */
private void *GetEnumerator(const ConcatTwo *enumerable)
{
    Validate_NotNull(enumerable);

    return ConcatTwoEnumerator_New(enumerable->First, enumerable->Second);
}
