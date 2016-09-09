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

//! @file IEnumerable.h

#ifndef CFLAT_CORE_COLLECTIONS_IENUMERABLE_H
#define CFLAT_CORE_COLLECTIONS_IENUMERABLE_H

#include "CFlat/Object.h"

/* Forward declarations */
struct IEnumerator;

/* Macros */
/// <summary>
/// Initializer for an <see cref="IEnumerable"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define IEnumerable_Initializer(vtable) { Object_Initializer(vtable)

/// <summary>
/// Initializer for a const <see cref="IEnumerable"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define IEnumerable_const_Initializer(vtable) { Object_const_Initializer(vtable) }

/// <summary>
/// Initializer for an <see cref="IEnumerableVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="getEnumerator">An <see cref="IEnumerable_GetEnumeratorFunc"/>.</param>
#define IEnumerableVTable_Initializer(destructor, getEnumerator) { ObjectVTable_Initializer(destructor), getEnumerator }

/* Types */
/// <summary>
/// Base class that exposes an enumerator, which supports a simple iteration over a collection of elements.
/// </summary>
typedef struct IEnumerable {
    /// <summary>
    /// The base class of <see cref="IEnumerable"/>.
    /// </summary>
    Object Base;
} IEnumerable;

/// <summary>
/// A function that returns a pointer to an <see cref="IEnumerator"/> that iterates through an
/// <see cref="IEnumerable"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/>.</param>
typedef struct IEnumerator *(*IEnumerable_GetEnumeratorFunc)(const IEnumerable *collection);

/// <summary>
/// A virtual method table for the <see cref="IEnumerable"/> class.
/// </summary>
typedef struct IEnumerableVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="IEnumerable"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that returns a pointer to an <see cref="IEnumerator"/> that iterates through an
    /// <see cref="IEnumerable"/>.
    /// </summary>
    IEnumerable_GetEnumeratorFunc GetEnumerator;
} IEnumerableVTable;

/* Functions */
/// <summary>
/// Initializes an <see cref="IEnumerable"/>.
/// </summary>
/// <param name="collection">Pointer to an uninitialized <see cref="IEnumerable"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="collection"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void IEnumerable_Constructor(IEnumerable *collection, const IEnumerableVTable *vtable);

/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through an <see cref="IEnumerable"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through the <see cref="IEnumerable"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
struct IEnumerator *IEnumerable_GetEnumerator(const IEnumerable *collection);

#endif
