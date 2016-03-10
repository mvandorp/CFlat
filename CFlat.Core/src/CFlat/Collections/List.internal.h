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

#ifndef CFLAT_CORE_COLLECTIONS_LIST_INTERNAL_H
#define CFLAT_CORE_COLLECTIONS_LIST_INTERNAL_H

#include "CFlat/Object.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"

/* Forward declarations */
typedef struct List List;

/* Types */
struct List {
    IEnumerable Base;
    int Capacity;
    int Count;
    int ElementSize;
    int Version;
    byte *Array;
};

 /* Functions */
/// <summary>
/// Initializes the given <see cref="List"/> using the given capacity.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="destructor">
///     Pointer to a <see cref="Destructor"/> to call when the object needs to be destroyed, or <see cref="null"/> if
///     <paramref name="list"/> should not automatically be destroyed.
/// </param>
/// <param name="getEnumerator">
///     Pointer to a <see cref="IEnumerable_GetEnumeratorCallback"/> that returns an <see cref="IEnumerator"/> for a
///     given <see cref="List"/>.
/// </param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="capacity">The initial capacity of the <see cref="List"/>.</param>
internal void List_Constructor_Full(
    List *list,
    Destructor destructor,
    IEnumerable_GetEnumeratorCallback getEnumerator,
    uintsize elementSize,
    int capacity);

/// <summary>
/// Gets the version of the given <see cref="List"/>. This value changes after every mutation to the list.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>The version of the given <see cref="List"/>.</returns>
internal uintsize List_GetVersion(const List *list);

#endif
