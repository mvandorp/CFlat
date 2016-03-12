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

#include "CFlat/Collections/IList.h"
#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"

/* Types */
struct List {
    IList Base;
    int Capacity;
    int Count;
    uintsize ElementSize;
    uintsize Version;
    byte *Array;
    EqualityPredicate Equals;
};

 /* Functions */
/// <summary>
/// Initializes a <see cref="List"/> with the given capacity.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="equals">
/// An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
/// </param>
/// <param name="capacity">The initial capacity of the <see cref="List"/>.</param>
internal void List_Constructor_Full(
    List *list,
    const IListVTable *vtable,
    uintsize elementSize,
    EqualityPredicate equals,
    int capacity);

/// <summary>
/// Gets the version of a <see cref="List"/>. The version changes after every mutation to the list.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>The version of the <see cref="List"/>.</returns>
internal uintsize List_GetVersion(const List *list);

#endif
