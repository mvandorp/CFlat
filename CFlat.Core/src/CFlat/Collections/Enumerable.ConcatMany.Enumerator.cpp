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

#include "CFlat/Collections/Enumerable.ConcatMany.Enumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/Enumerable.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/ObjectList.h"

/* Types */
typedef struct ConcatManyEnumerator {
    IEnumerator Base;
    IEnumerable *Enumerators;
    IEnumerator *EnumeratorsEnumerator;
    IEnumerator *Current;
} ConcatManyEnumerator;

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(ConcatManyEnumerator *enumerator, const IEnumerable *enumerables);
private void Destructor(ConcatManyEnumerator *enumerator);
private void *GetCurrent(const ConcatManyEnumerator *enumerator);
private bool MoveNext(ConcatManyEnumerator *enumerator);
private void Reset(ConcatManyEnumerator *enumerator);
private IEnumerable *GetEnumerators(const IEnumerable *enumerables);
private bool NextEnumerator(ConcatManyEnumerator *enumerator);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="ConcatManyEnumerator"/> class.
/// </summary>
private const IEnumeratorVTable VTable = IEnumeratorVTable_Initializer(
    (DestructorFunc)Destructor,
    (IEnumerator_GetCurrentFunc)GetCurrent,
    (IEnumerator_MoveNextFunc)MoveNext,
    (IEnumerator_ResetFunc)Reset);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerator *ConcatManyEnumerator_New(const IEnumerable *enumerables)
{
    ConcatManyEnumerator *enumerator = Memory_Allocate(sizeof(ConcatManyEnumerator));

    try {
        Constructor(enumerator, enumerables);

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

private void Constructor(ConcatManyEnumerator *enumerator, const IEnumerable *enumerables)
{
    assert(enumerator != null);
    assert(enumerables != null);
    assert(Enumerable_All(enumerables, Predicate_IsNotNull));

    IEnumerator_Constructor((IEnumerator*)enumerator, &VTable);

    enumerator->Enumerators = GetEnumerators(enumerables);
    enumerator->EnumeratorsEnumerator = IEnumerable_GetEnumerator(enumerator->Enumerators);
    enumerator->Current = null;
}

private void Destructor(ConcatManyEnumerator *enumerator)
{
    assert(enumerator != null);

    release(enumerator->EnumeratorsEnumerator);
    release(enumerator->Enumerators);
}

/// <summary>
/// Returns a list containing the enumerators to the given enumerables.
/// </summary>
private IEnumerable *GetEnumerators(const IEnumerable *enumerables)
{
    assert(enumerables != null);

    // Create a new list to hold the enumerators.
    IList *enumerators = (IList*)ObjectList_New();

    // Iterate through all enumerables.
    IEnumerator *enumerablesEnumerator = IEnumerable_GetEnumerator(enumerables);

    try {
        while (IEnumerator_MoveNext(enumerablesEnumerator)) {
            // Get the enumerator of the enumerable and add it to the list of enumerators.
            IEnumerable *currentEnumerable = IEnumerator_GetCurrent(enumerablesEnumerator);
            IEnumerator *currentEnumerableEnumerator = IEnumerable_GetEnumerator(currentEnumerable);

            try {
                IList_Add(enumerators, currentEnumerableEnumerator);
            }
            finally {
                release(currentEnumerableEnumerator);
            }
            endtry;
        }
    }
    catch (Exception) {
        release(enumerators);
        release(enumerablesEnumerator);
        throw;
    }
    finally {
        release(enumerablesEnumerator);
    }
    endtry;

    return (IEnumerable*)enumerators;
}

/// <summary>
/// Attempts to move to the next internal enumerator.
/// Returns true if successful; otherwise sets the current enumerator to null and returns false.
/// </summary>
private bool NextEnumerator(ConcatManyEnumerator *enumerator)
{
    assert(enumerator != null);

    if (IEnumerator_MoveNext(enumerator->EnumeratorsEnumerator)) {
        enumerator->Current = IEnumerator_GetCurrent(enumerator->EnumeratorsEnumerator);

        return true;
    }
    else {
        enumerator->Current = null;

        return false;
    }
}

/* IEnumerator */
private void *GetCurrent(const ConcatManyEnumerator *enumerator)
{
    Validate_NotNull(enumerator);
    Validate_State(enumerator->Current != null, "Enumeration has either not started or has already finished.");

    // Return the current element of the current enumerator.
    return IEnumerator_GetCurrent(enumerator->Current);
}

private bool MoveNext(ConcatManyEnumerator *enumerator)
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

private void Reset(ConcatManyEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    // Iterate through all enumerators.
    IEnumerator_Reset(enumerator->EnumeratorsEnumerator);

    while (IEnumerator_MoveNext(enumerator->EnumeratorsEnumerator)) {
        // Reset the enumerator.
        IEnumerator_Reset(IEnumerator_GetCurrent(enumerator->EnumeratorsEnumerator));
    }

    // Move to the first enumerator.
    IEnumerator_Reset(enumerator->EnumeratorsEnumerator);

    enumerator->Current = null;
}