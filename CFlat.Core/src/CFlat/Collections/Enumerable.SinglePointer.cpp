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
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"

/* Types */
struct SinglePointer {
    IEnumerable Base;
    DestructorFunc ElementDestructor;
    void *Item;
};

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(SinglePointer *enumerable , void *item, DestructorFunc elementDestructor);
private void Destructor(SinglePointer *enumerable);
private IEnumerator *GetEnumerator(const SinglePointer *enumerable);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="SinglePointer"/> class.
/// </summary>
private const IEnumerableVTable VTable = IEnumerableVTable_Initializer(
    (DestructorFunc)Destructor,
    (IEnumerable_GetEnumeratorFunc)GetEnumerator);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerable *SinglePointer_New(void *item, DestructorFunc itemDestructor)
{
    SinglePointer *enumerable = Memory_Allocate(sizeof(SinglePointer));

    try {
        Constructor(enumerable, item, itemDestructor);

        Object_SetDeallocator(enumerable, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(enumerable);

        if (itemDestructor != null && item != null) {
            itemDestructor(item);
        }

        throw;
    }
    endtry;

    return (IEnumerable*)enumerable;
}

internal void *SinglePointer_GetItem(const SinglePointer *enumerable)
{
    assert(enumerable != null);

    return enumerable->Item;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void Constructor(SinglePointer *enumerable, void *item, DestructorFunc elementDestructor)
{
    assert(enumerable != null);

    IEnumerable_Constructor((IEnumerable*)enumerable, &VTable);

    enumerable->ElementDestructor = elementDestructor;
    enumerable->Item = item;
}

private void Destructor(SinglePointer *enumerable)
{
    assert(enumerable != null);

    if (enumerable->ElementDestructor != null && enumerable->Item != null) {
        enumerable->ElementDestructor(enumerable->Item);
    }
}

/* IEnumerable */
private IEnumerator *GetEnumerator(const SinglePointer *enumerable)
{
    Validate_NotNull(enumerable);

    return SinglePointerEnumerator_New(enumerable);
}
