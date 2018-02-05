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

#include "CFlat/Collections/Enumerable.ConcatTwo.Enumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"

/* Types */
typedef struct ConcatTwoEnumerator {
    IEnumerator Base;
    IEnumerator *Enumerators[2];
    IEnumerator *Current;
    int Index;
} ConcatTwoEnumerator;

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(ConcatTwoEnumerator *enumerator, const IEnumerable *first, const IEnumerable *second);
private void Destructor(ConcatTwoEnumerator *enumerator);
private bool NextEnumerator(ConcatTwoEnumerator *enumerator);
private void *GetCurrent(const ConcatTwoEnumerator *enumerator);
private bool MoveNext(ConcatTwoEnumerator *enumerator);
private void Reset(ConcatTwoEnumerator *enumerator);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="ConcatTwoEnumerator"/> class.
/// </summary>
private const IEnumeratorVTable VTable = IEnumeratorVTable_Initializer(
    (DestructorFunc)Destructor,
    (IEnumerator_GetCurrentFunc)GetCurrent,
    (IEnumerator_MoveNextFunc)MoveNext,
    (IEnumerator_ResetFunc)Reset);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerator *ConcatTwoEnumerator_New(const IEnumerable *first, const IEnumerable *second)
{
    ConcatTwoEnumerator *enumerator = Memory_Allocate(sizeof(ConcatTwoEnumerator));

    try {
        Constructor(enumerator, first, second);

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

private void Constructor(ConcatTwoEnumerator *enumerator, const IEnumerable *first, const IEnumerable *second)
{
    assert(enumerator != null);
    assert(first != null);
    assert(second != null);

    IEnumerator_Constructor((IEnumerator*)enumerator, &VTable);

    enumerator->Enumerators[0] = IEnumerable_GetEnumerator(first);
    enumerator->Enumerators[1] = IEnumerable_GetEnumerator(second);
    enumerator->Current = null;
    enumerator->Index = 0;
}

private void Destructor(ConcatTwoEnumerator *enumerator)
{
    assert(enumerator != null);

    release(enumerator->Enumerators[0]);
    release(enumerator->Enumerators[1]);
}

/// <summary>
/// Attempts to move to the next internal enumerator.
/// Returns true if successful; otherwise sets the current enumerator to null and returns false.
/// </summary>
private bool NextEnumerator(ConcatTwoEnumerator *enumerator)
{
    assert(enumerator != null);

    if (enumerator->Index < 2) {
        enumerator->Current = enumerator->Enumerators[enumerator->Index];
        enumerator->Index++;

        return true;
    }
    else {
        enumerator->Current = null;
        enumerator->Index = 3;

        return false;
    }
}

/* IEnumerator */
private void *GetCurrent(const ConcatTwoEnumerator *enumerator)
{
    Validate_NotNull(enumerator);
    Validate_State(
        enumerator->Index > 0 &&
        enumerator->Index <= 2,
        "Enumeration has either not started or has already finished.");

    // Return the current element of the current enumerator.
    return IEnumerator_GetCurrent(enumerator->Current);
}

private bool MoveNext(ConcatTwoEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    // If there is no current enumerator, move to the first one, or return false if we reached past the last enumerator.
    if (enumerator->Current == null) {
        if (!NextEnumerator(enumerator)) return false;
    }

    // Move to the next element of the current enumerator, or move to the next enumerator if we reached past the end of
    // the current one.
    return IEnumerator_MoveNext(enumerator->Current) || (NextEnumerator(enumerator), MoveNext(enumerator));
}

    private void Reset(ConcatTwoEnumerator *enumerator)
    {
        Validate_NotNull(enumerator);

        // Reset all enumerators.
        IEnumerator_Reset(enumerator->Enumerators[0]);
        IEnumerator_Reset(enumerator->Enumerators[1]);

        // Move to the first enumerator.
        enumerator->Current = null;
        enumerator->Index = 0;
    }