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

#include "CFlat/Collections/Enumerable.SinglePointer.h"
#include "CFlat/Collections/Enumerable.SinglePointer.Enumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/* Types */
typedef struct SinglePointerEnumerator {
    IEnumerator Base;
    const SinglePointer *Enumerable;
    int Index;
} SinglePointerEnumerator;

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(SinglePointerEnumerator *enumerator, const SinglePointer *enumerable);
private void Destructor(SinglePointerEnumerator *enumerator);
private void *GetCurrent(const SinglePointerEnumerator *enumerator);
private bool MoveNext(SinglePointerEnumerator *enumerator);
private void Reset(SinglePointerEnumerator *enumerator);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="SinglePointerEnumerator"/> class.
/// </summary>
private const IEnumeratorVTable VTable = IEnumeratorVTable_Initializer(
    (DestructorFunc)Destructor,
    (IEnumerator_GetCurrentFunc)GetCurrent,
    (IEnumerator_MoveNextFunc)MoveNext,
    (IEnumerator_ResetFunc)Reset);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerator *SinglePointerEnumerator_New(const SinglePointer *enumerable)
{
    SinglePointerEnumerator *enumerator = Memory_Allocate(sizeof(SinglePointerEnumerator));

    try {
        Constructor(enumerator, enumerable);

        Object_SetDeallocator(enumerator, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(enumerator);
        throw;
    }
    endtry;

    return (IEnumerator*)enumerator;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void Constructor(SinglePointerEnumerator *enumerator, const SinglePointer *enumerable)
{
    assert(enumerator != null);
    assert(enumerable != null);

    IEnumerator_Constructor((IEnumerator*)enumerator, &VTable);

    enumerator->Enumerable = retain_const(enumerable);
    enumerator->Index = 0;
}

private void Destructor(SinglePointerEnumerator *enumerator)
{
    assert(enumerator != null);

    release(enumerator->Enumerable);
}

/* IEnumerator */
private void *GetCurrent(const SinglePointerEnumerator *enumerator)
{
    Validate_NotNull(enumerator);
    Validate_State(
        enumerator->Index > 0 &&
        enumerator->Index <= 1,
        "Enumeration has either not started or has already finished.");

    return SinglePointer_GetItem(enumerator->Enumerable);
}

private bool MoveNext(SinglePointerEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    if (enumerator->Index < 1) {
        enumerator->Index++;

        return true;
    }
    else {
        enumerator->Index = 2;

        return false;
    }
}

private void Reset(SinglePointerEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    enumerator->Index = 0;
}
