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

//! @file Enumerable.h

#ifndef CFLAT_CORE_COLLECTIONS_ENUMERABLE_H
#define CFLAT_CORE_COLLECTIONS_ENUMERABLE_H

#include "CFlat/Object.h"
#include "CFlat/Language/Functions.h"

/* Forward declarations */
struct IEnumerable;

/* Functions */
/// <summary>
/// Determines whether all elements of an <see cref="IEnumerable"/> satisfy a given predicate.
/// </summary>
/// <param name="enumerable">Pointer to an <see cref="IEnumerable"/>.</param>
/// <param name="predicate">A <see cref="Predicate"/> to test each element for a condition.</param>
/// <returns>
///     <see cref="true"/> if all elements of <paramref name="enumerable"/> satisfy <paramref name="predicate"/>;
///     otherwise <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="enumerable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="predicate"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
bool Enumerable_All(const struct IEnumerable *enumerable, Predicate predicate);

/// <summary>
/// Determines whether any element of an <see cref="IEnumerable"/> satisfies a given predicate.
/// </summary>
/// <param name="enumerable">Pointer to an <see cref="IEnumerable"/>.</param>
/// <param name="predicate">A <see cref="Predicate"/> to test each element for a condition.</param>
/// <returns>
///     <see cref="true"/> if any element of <paramref name="enumerable"/> satisfies <paramref name="predicate"/>;
///     otherwise <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="enumerable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="predicate"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
bool Enumerable_Any(const struct IEnumerable *enumerable, Predicate predicate);

/// <summary>
/// Determines the number of elements in an <see cref="IEnumerable"/>.
/// </summary>
/// <param name="enumerable">Pointer to an <see cref="IEnumerable"/>.</param>
/// <returns>The number of elements in the <see cref="IEnumerable"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="enumerable"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
uintsize Enumerable_Count(const struct IEnumerable *enumerable);

/// <summary>
/// Returns an empty <see cref="IEnumerable"/>.
/// </summary>
/// <returns>An empty <see cref="IEnumerable"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IEnumerable *Enumerable_Empty(void);

/// <summary>
/// Returns an <see cref="IEnumerable"/> containing a single pointer.
/// </summary>
/// <param name="item">The pointer contained in the <see cref="IEnumerable"/>.</param>
/// <param name="itemDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when <paramref name="item"/> needs to be destroyed, or
///     <see cref="null"/> if <paramref name="item"/> should not automatically be destroyed.
/// </param>
/// <returns>An <see cref="IEnumerable"/> containing a single pointer.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IEnumerable *Enumerable_FromSinglePointer(void *item, DestructorFunc itemDestructor);

/// <summary>
/// Returns an <see cref="IEnumerable"/> containing a single <see cref="Object"/>.
/// </summary>
/// <param name="item">The <see cref="Object"/> contained in the <see cref="IEnumerable"/>.</param>
/// <returns>An <see cref="IEnumerable"/> containing a single <see cref="Object"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IEnumerable *Enumerable_FromSingleObject(Object *item);

/// <summary>
/// Concatenates two sequences.
/// </summary>
/// <param name="first">The first sequence to concatenate.</param>
/// <param name="second">The second sequence to concatenate.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the concatenated elements of the two input sequences.</returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="first"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="second"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IEnumerable *Enumerable_Concat(const struct IEnumerable *first, const struct IEnumerable *second);

/// <summary>
/// Concatenates the given sequences.
/// </summary>
/// <param name="enumerables">An array of sequences to concatenate.</param>
/// <param name="count">The number of sequences to concatenate.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the concatenated elements of the input sequences.</returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="count"/> is greater than 0 and <paramref name="enumerables"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentException">
///     <paramref name="count"/> is greater than 0 and <paramref name="enumerables"/> contains a <see cref="null"/>
///     pointer.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IEnumerable *Enumerable_ConcatArray(const struct IEnumerable * const *enumerables, uintsize count);

/// <summary>
/// Concatenates the sequences contained in the given <see cref="IEnumerable"/>.
/// </summary>
/// <param name="enumerables">An <see cref="IEnumerable"/> containing the sequences to concatenate.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the concatenated elements of the input sequences.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="enumerables"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentException">
///     <paramref name="enumerables"/> contains a <see cref="null"/> pointer.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct IEnumerable *Enumerable_ConcatEnumerable(const struct IEnumerable *enumerables);

#endif
