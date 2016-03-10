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

/* Types */
/// <summary>
/// A function that returns an <see cref="IEnumerator"/> for a given <see cref="IEnumerable"/>.
/// </summary>
/// <param name="enumerable">The <see cref="IEnumerable"/> for which to return an <see cref="IEnumerator"/>.</param>
typedef IEnumerator *(*IEnumerable_GetEnumeratorCallback)(const void *enumerable);

/// <summary>
/// Exposes the enumerator, which supports a simple iteration over a collection of elements.
/// </summary>
typedef struct IEnumerable {
    /// <summary>
    /// The base class of the <see cref="IEnumerable"/>.
    /// </summary>
    Object Base;

    /// <summary>
    /// A function that returns an <see cref="IEnumerator"/> for this <see cref="IEnumerable"/>.
    /// </summary>
    IEnumerable_GetEnumeratorCallback GetEnumerator;
} IEnumerable;

/* Functions */
/// <summary>
/// Initializes the given <see cref="IEnumerable"/>.
/// </summary>
/// <param name="enumerable">Pointer to an uninitialized <see cref="IEnumerable"/>.</param>
/// <param name="destructor">
///     Pointer to a <see cref="Destructor"/> to call when the object needs to be destroyed, or <see cref="null"/> if
///     <paramref name="enumerable"/> should not automatically be destroyed.
/// </param>
/// <param name="getEnumerator">
///     Pointer to a <see cref="IEnumerable_GetEnumeratorCallback"/> that returns an <see cref="IEnumerator"/> for a
///     given <see cref="IEnumerable"/>.
/// </param>
void IEnumerable_Constructor(void *enumerable, Destructor destructor, IEnumerable_GetEnumeratorCallback getEnumerator);

/// <summary>
/// Returns an <see cref="IEnumerator"/> that iterates through the given <see cref="IEnumerable"/>.
/// </summary>
/// <param name="enumerable">Pointer to a <see cref="IEnumerable"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through the given <see cref="IEnumerable"/>.</returns>
IEnumerator *IEnumerable_GetEnumerator(const void *enumerable);

#endif
