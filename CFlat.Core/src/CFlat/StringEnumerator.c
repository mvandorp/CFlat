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

#include "CFlat/StringEnumerator.h"

#include "CFlat.h"
#include "CFlat/const_cast.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/* Types */
typedef struct StringEnumerator {
    IEnumerator Base;
    const String *String;
    char Current;
    uintsize Index;
} StringEnumerator;

/**************************************/
/* Private functions                  */
/**************************************/

private void Constructor(StringEnumerator *enumerator, const String *str);
private void Destructor(StringEnumerator *enumerator);
private void *GetCurrent(const StringEnumerator *enumerator);
private bool MoveNext(StringEnumerator *enumerator);
private void Reset(StringEnumerator *enumerator);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="StringEnumerator"/> class.
/// </summary>
private const IEnumeratorVTable VTable = IEnumeratorVTable_Initializer(
    (DestructorFunc)Destructor,
    (IEnumerator_GetCurrentFunc)GetCurrent,
    (IEnumerator_MoveNextFunc)MoveNext,
    (IEnumerator_ResetFunc)Reset);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerator *StringEnumerator_New(const String *str)
{
    StringEnumerator *enumerator = Memory_Allocate(sizeof(StringEnumerator));

    try {
        Constructor(enumerator, str);

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

private void Constructor(StringEnumerator *enumerator, const String *str)
{
    Validate_NotNull(enumerator);
    Validate_NotNull(str);

    IEnumerator_Constructor((IEnumerator*)enumerator, &VTable);

    enumerator->String = retain_const(str);
    enumerator->Index = 0;
    enumerator->Current = '\0';
}

private void Destructor(StringEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    release(((StringEnumerator*)enumerator)->String);
}

private void *GetCurrent(const StringEnumerator *enumerator)
{
    Validate_NotNull(enumerator);
    Validate_State(
        enumerator->Index > 0 &&
        enumerator->Index <= String_GetLength(enumerator->String),
        "Enumeration has either not started or has already finished.");

    // BUG: Current could be modified.
    return const_cast(&enumerator->Current);
}

private bool MoveNext(StringEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    if (enumerator->Index < String_GetLength(enumerator->String)) {
        enumerator->Current = String_GetCharAt(enumerator->String, enumerator->Index);
        enumerator->Index++;

        return true;
    }
    else {
        enumerator->Current = '\0';
        enumerator->Index = uintsize_CheckedAddition(String_GetLength(enumerator->String), 1);

        return false;
    }
}

private void Reset(StringEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    enumerator->Index = 0;
    enumerator->Current = '\0';
}
