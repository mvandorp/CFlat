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

#ifndef CFLAT_CORE_COLLECTIONS_ENUMERABLE_CONCATMANY_H
#define CFLAT_CORE_COLLECTIONS_ENUMERABLE_CONCATMANY_H

/* Forward declarations */
struct IEnumerable;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="IEnumerable"/> exposing an enumerator which supports iteration over the
/// elements of every <see cref="IEnumerable"/> in <paramref name="enumerables"/> as if they were concatenated.
///
/// The lifetime of the <see cref="IEnumerable"/> should be managed with retain() and release().
/// </summary>
/// <param name="enumerables">
///     A collection of <see cref="IEnumerable"/>s that implements <see cref="IEnumerable"/>.
/// </param>
/// <returns>A pointer to the newly allocated <see cref="IEnumerable"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal struct IEnumerable *ConcatMany_New(const struct IEnumerable *enumerables);

#endif
