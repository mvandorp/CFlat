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

#include "CFlat/Collections/Enumerable.Empty.Enumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/* Types */
typedef IEnumerator EmptyEnumerator;

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(EmptyEnumerator *enumerator);
private void *GetCurrent(const EmptyEnumerator *enumerator);
private bool MoveNext(EmptyEnumerator *enumerator);
private void Reset(EmptyEnumerator *enumerator);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="EmptyEnumerator"/> class.
/// </summary>
private const IEnumeratorVTable VTable = IEnumeratorVTable_Initializer(
    (DestructorFunc)null,
    (IEnumerator_GetCurrentFunc)GetCurrent,
    (IEnumerator_MoveNextFunc)MoveNext,
    (IEnumerator_ResetFunc)Reset);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerator *EmptyEnumerator_New(void)
{
    EmptyEnumerator *enumerator = Memory_Allocate(sizeof(EmptyEnumerator));

    try {
        Constructor(enumerator);

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

private void Constructor(EmptyEnumerator *enumerator)
{
    assert(enumerator != null);

    IEnumerator_Constructor((IEnumerator*)enumerator, &VTable);
}

/* IEnumerator */
private void *GetCurrent(const EmptyEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    throw_new(InvalidOperationException, "Enumeration has either not started or has already finished.");

    return null;
}

private bool MoveNext(EmptyEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    return false;
}

private void Reset(EmptyEnumerator *enumerator)
{
    Validate_NotNull(enumerator);
}
