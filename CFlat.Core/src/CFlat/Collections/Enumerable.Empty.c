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

#include "CFlat/Collections/Enumerable.Empty.h"
#include "CFlat/Collections/Enumerable.Empty.Enumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerable.h"

/* Types */
typedef IEnumerable Empty;

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(Empty *enumerable);
private void *GetEnumerator(const Empty *enumerable);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="Empty"/> class.
/// </summary>
private const IEnumerableVTable VTable = IEnumerableVTable_Initializer(
    (DestructorFunc)null,
    (IEnumerable_GetEnumeratorFunc)GetEnumerator);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerable *Empty_New(void)
{
    Empty *enumerable = Memory_Allocate(sizeof(Empty));

    try {
        Constructor(enumerable);

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

private void Constructor(Empty *enumerable)
{
    assert(enumerable != null);

    IEnumerable_Constructor((IEnumerable*)enumerable, &VTable);
}

/* IEnumerable */
private void *GetEnumerator(const Empty *enumerable)
{
    Validate_NotNull(enumerable);

    return EmptyEnumerator_New();
}
