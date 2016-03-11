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

/**
 * @file IEnumerable.h
 */

#ifndef CFLAT_CORE_COLLECTIONS_IENUMERABLE_H
#define CFLAT_CORE_COLLECTIONS_IENUMERABLE_H

#include "CFlat/Object.h"

/* Forward declarations */
typedef struct IEnumerator IEnumerator;

/* Macros */
/// <summary>
/// Initializer for an <see cref="IEnumerableVTable"/>.
/// </summary>
/// <param name="destructor">
/// A <see cref="Destructor"/> that is called when the object needs to be destroyed, or <see cref="null"/> if the
/// object should not automatically be destroyed.
/// </param>
/// <param name="getEnumerator">A <see cref="IEnumerable_GetEnumeratorCallback"/>.</param>
#define IEnumerableVTable_Initializer(destructor, getEnumerator) { ObjectVTable_Initializer(destructor), getEnumerator }

/* Types */
/// <summary>
/// Exposes the enumerator, which supports a simple iteration over a collection of elements.
/// </summary>
typedef struct IEnumerable {
    /// <summary>
    /// The base class of <see cref="IEnumerable"/>.
    /// </summary>
    Object Base;
} IEnumerable;

/// <summary>
/// A function that returns an <see cref="IEnumerator"/> for a given <see cref="IEnumerable"/>.
/// </summary>
/// <param name="enumerable">Pointer to an <see cref="IEnumerable"/>.</param>
typedef IEnumerator *(*IEnumerable_GetEnumeratorCallback)(const IEnumerable *enumerable);

/// <summary>
/// A virtual method table for the <see cref="IEnumerable"/> class.
/// </summary>
typedef struct IEnumerableVTable {
    /// <summary>
    /// The base class of <see cref="IEnumerableVTable"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that returns an <see cref="IEnumerator"/> for this <see cref="IEnumerable"/>.
    /// </summary>
    IEnumerable_GetEnumeratorCallback GetEnumerator;
} IEnumerableVTable;

/* Functions */
/// <summary>
/// Initializes the given <see cref="IEnumerable"/>.
/// </summary>
/// <param name="enumerable">Pointer to an uninitialized <see cref="IEnumerable"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
void IEnumerable_Constructor(IEnumerable *enumerable, const IEnumerableVTable *vtable);

/// <summary>
/// Returns an <see cref="IEnumerator"/> that iterates through the given <see cref="IEnumerable"/>.
/// </summary>
/// <param name="enumerable">Pointer to a <see cref="IEnumerable"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through the given <see cref="IEnumerable"/>.</returns>
IEnumerator *IEnumerable_GetEnumerator(const IEnumerable *enumerable);

#endif
