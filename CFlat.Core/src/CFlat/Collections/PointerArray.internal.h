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

#ifndef CFLAT_CORE_COLLECTIONS_POINTERARRAY_INTERNAL_H
#define CFLAT_CORE_COLLECTIONS_POINTERARRAY_INTERNAL_H

#ifndef CFLAT_CORE_COLLECTIONS_POINTERARRAY_H
 #error PointerArray.internal.h should not be included directly.
#endif

#include "CFlat/Object.h"
#include "CFlat/Collections/Array.h"
#include "CFlat/Language/Keywords.h"

/* Types */
struct PointerArray {
    Array Base;
    DestructorFunc ElementDestructor;
};

/* Functions */
/// <summary>
/// Initializes an <see cref="PointerArray"/>.
/// </summary>
/// <param name="array">Pointer to an uninitialized <see cref="PointerArray"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <param name="source">The source array.</param>
/// <param name="length">The number of elements in the array.</param>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer <b>-or-</b>.
///     <paramref name="source"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void PointerArray_Constructor_Full(
    PointerArray *array,
    const IReadOnlyListVTable *vtable,
    void **source,
    uintsize length,
    DestructorFunc elementDestructor);

#endif
