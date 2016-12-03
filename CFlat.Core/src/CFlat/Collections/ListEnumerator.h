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

#ifndef CFLAT_CORE_COLLECTIONS_LISTENUMERATOR_H
#define CFLAT_CORE_COLLECTIONS_LISTENUMERATOR_H

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"

/* Forward declarations */
struct IReadOnlyList;
struct IEnumerator;

/* Types */
/// <summary>
/// A function that returns the version of an <see cref="IReadOnlyList"/>. The version changes after every mutation to
/// the list.
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <returns>The version of the <see cref="IReadOnlyList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
typedef uintsize (*ListEnumerator_GetVersionFunc)(const struct IReadOnlyList *list);

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="IEnumerator"/> that can iterate over the given
/// <see cref="IReadOnlyList"/>.
///
/// The lifetime of the <see cref="IEnumerator"/> should be managed with retain() and release().
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="IEnumerator"/>.</returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="getVersion"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal struct IEnumerator *ListEnumerator_New(
    const struct IReadOnlyList *list,
    ListEnumerator_GetVersionFunc getVersion);

#endif
