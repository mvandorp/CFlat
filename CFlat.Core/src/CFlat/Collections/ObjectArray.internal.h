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

#ifndef CFLAT_CORE_COLLECTIONS_OBJECTARRAY_INTERNAL_H
#define CFLAT_CORE_COLLECTIONS_OBJECTARRAY_INTERNAL_H

#ifndef CFLAT_CORE_COLLECTIONS_OBJECTARRAY_H
 #error ObjectArray.internal.h should not be included directly.
#endif

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"
#include "CFlat/Collections/PointerArray.h"

/* Types */
struct ObjectArray {
    PointerArray Base;
};

/* Functions */
/// <summary>
/// Initializes an <see cref="ObjectArray"/>.
/// </summary>
/// <param name="array">Pointer to an uninitialized <see cref="ObjectArray"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <param name="source">The source array.</param>
/// <param name="length">The number of elements in the array.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer <b>-or-</b>.
///     <paramref name="source"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void ObjectArray_Constructor_Full(
    ObjectArray *array,
    const IReadOnlyListVTable *vtable,
    void **source,
    uintsize length);

#endif
