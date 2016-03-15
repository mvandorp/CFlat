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

#include "CFlat/Collections/ListEnumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/List.h"

/* Types */
typedef struct ListEnumerator {
    IEnumerator Base;
    const List *List;
    void *Current;
    int Index;
    uintsize Version;
} ListEnumerator;

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(ListEnumerator *enumerator, const List *list);
private void Destructor(ListEnumerator *enumerator);
private void *GetCurrent(const ListEnumerator *enumerator);
private bool MoveNext(ListEnumerator *enumerator);
private void Reset(ListEnumerator *enumerator);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="ListEnumerator"/> class.
/// </summary>
private const IEnumeratorVTable VTable = IEnumeratorVTable_Initializer(
    (DestructorFunc)Destructor,
    (IEnumerator_GetCurrentFunc)GetCurrent,
    (IEnumerator_MoveNextFunc)MoveNext,
    (IEnumerator_ResetFunc)Reset);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerator *ListEnumerator_New(const List *list)
{
    Validate_NotNull(list);

    ListEnumerator *enumerator = Memory_Allocate(sizeof(ListEnumerator));

    try {
        Constructor(enumerator, list);

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

private void Constructor(ListEnumerator *enumerator, const List *list)
{
    Validate_NotNull(enumerator);
    Validate_NotNull(list);

    IEnumerator_Constructor((IEnumerator*)enumerator, &VTable);

    enumerator->List = Object_Aquire(list);
    enumerator->Index = 0;
    enumerator->Current = null;
    enumerator->Version = List_GetVersion(list);
}

private void Destructor(ListEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    Object_Release(((ListEnumerator*)enumerator)->List);
}

private void *GetCurrent(const ListEnumerator *enumerator)
{
    Validate_NotNull(enumerator);
    Validate_State(
        enumerator->Version == List_GetVersion(enumerator->List),
        "Collection was modified; enumeration operation may not execute.");
    Validate_State(
        enumerator->Index > 0 &&
        enumerator->Index <= List_GetCount(enumerator->List),
        "Enumeration has either not started or has already finished.");

    return enumerator->Current;
}

private bool MoveNext(ListEnumerator *enumerator)
{
    Validate_NotNull(enumerator);
    Validate_State(
        enumerator->Version == List_GetVersion(enumerator->List),
        "Collection was modified; enumeration operation may not execute.");

    if (enumerator->Index < List_GetCount(enumerator->List)) {
        enumerator->Current = List_GetItemRef(enumerator->List, enumerator->Index);
        enumerator->Index++;

        return true;
    }
    else {
        enumerator->Current = null;
        enumerator->Index = List_GetCount(enumerator->List) + 1;

        return false;
    }
}

private void Reset(ListEnumerator *enumerator)
{
    Validate_NotNull(enumerator);
    Validate_State(
        enumerator->Version == List_GetVersion(enumerator->List),
        "Collection was modified; enumeration operation may not execute.");

    enumerator->Index = 0;
    enumerator->Current = null;
}
