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

#ifndef CFLAT_CORE_COLLECTIONS_ENUMERABLE_SINGLEPOINTER_H
#define CFLAT_CORE_COLLECTIONS_ENUMERABLE_SINGLEPOINTER_H

#include "CFlat/Object.h"
#include "CFlat/Language/Keywords.h"

/* Forward declarations */
struct IEnumerable;

/* Types */
/// <summary>
/// Implements an <see cref="IEnumerable"/> exposing an enumerator which supports iteration over a single pointer as if
/// it were part of a collection.
/// </summary>
typedef struct SinglePointer SinglePointer;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="IEnumerable"/> exposing an enumerator which supports iteration over a
/// single pointer as if it were part of a collection.
///
/// The lifetime of the <see cref="IEnumerable"/> should be managed with retain() and release().
/// </summary>
/// <param name="item">The single element of the <see cref="IEnumerable"/>.</param>
/// <param name="itemDestructor">
///     A <see cref="DestructorFunc"/> that is called when <paramref name="item"/> needs to be destroyed, or
///     <see cref="null"/> if <paramref name="item"/> should not automatically be destroyed.</param>
/// <returns>A pointer to the newly allocated <see cref="IEnumerable"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal struct IEnumerable *SinglePointer_New(void *item, DestructorFunc itemDestructor);

/// <summary>
/// Gets the single element contained in the given <see cref="SinglePointer"/>.
/// </summary>
/// <param name="enumerable">Pointer to an <see cref="IEnumerable"/>.</param>
/// <returns>The single element contained in the given <see cref="SinglePointer"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="enumerable"/> is <see cref="null"/>.</exception>
internal void *SinglePointer_GetItem(const SinglePointer *enumerable);

#endif
