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

#ifndef CFLAT_CORE_COLLECTIONS_POINTERLIST_INTERNAL_H
#define CFLAT_CORE_COLLECTIONS_POINTERLIST_INTERNAL_H

#ifndef CFLAT_CORE_COLLECTIONS_POINTERLIST_H
 #error PointerList.internal.h should not be included directly.
#endif

#include "CFlat/Object.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/List.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"

/* Types */
struct PointerList {
    List Base;
    DestructorFunc ElementDestructor;
};

 /* Functions */
/// <summary>
/// Initializes a <see cref="PointerList"/> with the given capacity.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <param name="capacity">The initial capacity of the <see cref="List"/>.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void PointerList_Constructor_Full(
    PointerList *list,
    const IListVTable *vtable,
    DestructorFunc elementDestructor,
    uintsize capacity);

/// <summary>
/// Gets the version of a <see cref="PointerList"/>. The version changes after every mutation to the list.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <returns>The version of the <see cref="PointerList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
internal uintsize PointerList_GetVersion(const PointerList *list);

#endif
