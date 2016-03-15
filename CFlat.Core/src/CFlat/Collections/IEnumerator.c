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

#include "CFlat/Collections/IEnumerator.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const IEnumeratorVTable *GetVTable(const IEnumerator *enumerator);

/**************************************/
/* Public function definitions        */
/**************************************/

public void IEnumerator_Constructor(
    IEnumerator *enumerator,
    const IEnumeratorVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetCurrent);
    Validate_NotNull(vtable->MoveNext);
    Validate_NotNull(vtable->Reset);

    Object_Constructor(enumerator, (const ObjectVTable*)vtable);
}

public void *IEnumerator_GetCurrent(const IEnumerator *enumerator)
{
    return GetVTable(enumerator)->GetCurrent(enumerator);
}

public bool IEnumerator_MoveNext(IEnumerator *enumerator)
{
    return GetVTable(enumerator)->MoveNext(enumerator);
}

public void IEnumerator_Reset(IEnumerator *enumerator)
{
    GetVTable(enumerator)->Reset(enumerator);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of an <see cref="IEnumerator"/>.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="enumerator"/> is <see cref="null"/>.</exception>
private const IEnumeratorVTable *GetVTable(const IEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    return (const IEnumeratorVTable*)((const Object*)enumerator)->VTable;
}
