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

//! @file IReadOnlyCollection.h

#ifndef CFLAT_CORE_COLLECTIONS_IREADONLYCOLLECTION_H
#define CFLAT_CORE_COLLECTIONS_IREADONLYCOLLECTION_H

#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
struct IEnumerator;

/* Macros */
/// <summary>
/// Initializer for an <see cref="IReadOnlyCollection"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define IReadOnlyCollection_Initializer(vtable) { IEnumerable_Initializer(vtable) }

/// <summary>
/// Initializer for a const <see cref="IReadOnlyCollection"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define IReadOnlyCollection_const_Initializer(vtable) { IEnumerable_const_Initializer(vtable) }

/// <summary>
/// Initializer for an <see cref="IReadOnlyCollectionVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="getEnumerator">An <see cref="IEnumerable_GetEnumeratorFunc"/>.</param>
/// <param name="getCount">An <see cref="IReadOnlyCollection_GetCountFunc"/>.</param>
/// <param name="contains">An <see cref="IReadOnlyCollection_ContainsFunc"/>.</param>
/// <param name="copyTo">An <see cref="IReadOnlyCollection_CopyToFunc"/>.</param>
#define IReadOnlyCollectionVTable_Initializer(                  \
    destructor,                                                 \
    getEnumerator,                                              \
    getCount,                                                   \
    contains,                                                   \
    copyTo)                                                     \
{                                                               \
    IEnumerableVTable_Initializer(destructor, getEnumerator),   \
    getCount,                                                   \
    contains,                                                   \
    copyTo,                                                     \
}

/* Types */
/// <summary>
/// Base class for a collection of elements.
/// </summary>
typedef struct IReadOnlyCollection {
    /// <summary>
    /// The base class of <see cref="IReadOnlyCollection"/>.
    /// </summary>
    IEnumerable Base;
} IReadOnlyCollection;

/// <summary>
/// A function that returns the number of elements in an <see cref="IReadOnlyCollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IReadOnlyCollection"/>.</param>
/// <returns>The number of elements in the <see cref="IReadOnlyCollection"/>.</returns>
typedef uintsize (*IReadOnlyCollection_GetCountFunc)(const IReadOnlyCollection *collection);

/// <summary>
/// A function that determines whether an <see cref="IReadOnlyCollection"/> contains the given value.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IReadOnlyCollection"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
typedef bool (*IReadOnlyCollection_ContainsFunc)(const IReadOnlyCollection *collection, const void *item);

/// <summary>
/// A function that copies the elements of an <see cref="IReadOnlyCollection"/> to the given array.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IReadOnlyCollection"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="IReadOnlyCollection"/>.
/// </param>
typedef void (*IReadOnlyCollection_CopyToFunc)(const IReadOnlyCollection *collection, void *destination);

/// <summary>
/// A virtual method table for the <see cref="IReadOnlyCollection"/> class.
/// </summary>
typedef struct IReadOnlyCollectionVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="IReadOnlyCollection"/>.
    /// </summary>
    IEnumerableVTable Base;

    /// <summary>
    /// A function that returns the number of elements in an <see cref="IReadOnlyCollection"/>.
    /// </summary>
    IReadOnlyCollection_GetCountFunc GetCount;

    /// <summary>
    /// A function that determines whether an <see cref="IReadOnlyCollection"/> contains the given value.
    /// </summary>
    IReadOnlyCollection_ContainsFunc Contains;

    /// <summary>
    /// A function that copies the elements of an <see cref="IReadOnlyCollection"/> to the given array.
    /// </summary>
    IReadOnlyCollection_CopyToFunc CopyTo;
} IReadOnlyCollectionVTable;

/* Functions */
/// <summary>
/// Initializes an <see cref="IReadOnlyCollection"/>.
/// </summary>
/// <param name="collection">Pointer to an uninitialized <see cref="IReadOnlyCollection"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="collection"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void IReadOnlyCollection_Constructor(
    IReadOnlyCollection *collection,
    const IReadOnlyCollectionVTable *vtable);

/// <summary>
/// Gets the number of elements in an <see cref="IReadOnlyCollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IReadOnlyCollection"/>.</param>
/// <returns>The number of elements in the <see cref="IReadOnlyCollection"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
uintsize IReadOnlyCollection_GetCount(const IReadOnlyCollection *collection);

/// <summary>
/// Determines whether an <see cref="IReadOnlyCollection"/> contains the given value.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IReadOnlyCollection"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
bool IReadOnlyCollection_Contains(const IReadOnlyCollection *collection, const void *item);

/// <summary>
/// Copies the elements of an <see cref="IReadOnlyCollection"/> to the given array.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IReadOnlyCollection"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="IReadOnlyCollection"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="collection"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
void IReadOnlyCollection_CopyTo(const IReadOnlyCollection *collection, void *destination);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="IReadOnlyCollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IReadOnlyCollection"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through an <see cref="IReadOnlyCollection"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
struct IEnumerator *IReadOnlyCollection_GetEnumerator(const IReadOnlyCollection *collection);

#endif
