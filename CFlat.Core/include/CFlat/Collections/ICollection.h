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

//! @file ICollection.h

#ifndef CFLAT_CORE_COLLECTIONS_ICOLLECTION_H
#define CFLAT_CORE_COLLECTIONS_ICOLLECTION_H

#include "CFlat/Collections/IReadOnlyCollection.h"
#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
struct IEnumerator;

/* Macros */
/// <summary>
/// Initializer for an <see cref="ICollection"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define ICollection_Initializer(vtable) { IReadOnlyCollection_Initializer(vtable) }

/// <summary>
/// Initializer for a const <see cref="ICollection"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define ICollection_const_Initializer(vtable) { IReadOnlyCollection_const_Initializer(vtable) }

/// <summary>
/// Initializer for an <see cref="ICollectionVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="getEnumerator">An <see cref="IEnumerable_GetEnumeratorFunc"/>.</param>
/// <param name="getCount">An <see cref="IReadOnlyCollection_GetCountFunc"/>.</param>
/// <param name="add">An <see cref="ICollection_AddFunc"/>.</param>
/// <param name="clear">An <see cref="ICollection_ClearFunc"/>.</param>
/// <param name="contains">An <see cref="IReadOnlyCollection_ContainsFunc"/>.</param>
/// <param name="copyTo">An <see cref="IReadOnlyCollection_CopyToFunc"/>.</param>
/// <param name="remove">An <see cref="ICollection_RemoveFunc"/>.</param>
#define ICollectionVTable_Initializer(      \
    destructor,                             \
    getEnumerator,                          \
    getCount,                               \
    add,                                    \
    clear,                                  \
    contains,                               \
    copyTo,                                 \
    remove)                                 \
{                                           \
    IReadOnlyCollectionVTable_Initializer(  \
        destructor,                         \
        getEnumerator,                      \
        getCount,                           \
        contains,                           \
        copyTo),                            \
    add,                                    \
    clear,                                  \
    remove                                  \
}

/* Types */
/// <summary>
/// Base class for a collection of elements.
/// </summary>
typedef struct ICollection {
    /// <summary>
    /// The base class of <see cref="ICollection"/>.
    /// </summary>
    IReadOnlyCollection Base;
} ICollection;

/// <summary>
/// A function that adds an item to an <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <param name="item">The item to add.</param>
typedef void (*ICollection_AddFunc)(ICollection *collection, void *item);

/// <summary>
/// A function that removes all elements from an <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
typedef void (*ICollection_ClearFunc)(ICollection *collection);

/// <summary>
/// A function that removes the first occurance of the given item from an <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <param name="item">The item to remove.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="item"/> was successfully removed; otherwise, <see cref="false"/>.
/// </returns>
typedef bool (*ICollection_RemoveFunc)(ICollection *collection, const void *item);

/// <summary>
/// A virtual method table for the <see cref="ICollection"/> class.
/// </summary>
typedef struct ICollectionVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="ICollection"/>.
    /// </summary>
    IReadOnlyCollectionVTable Base;

    /// <summary>
    /// A function that adds an item to an <see cref="ICollection"/>.
    /// </summary>
    ICollection_AddFunc Add;

    /// <summary>
    /// A function that removes all elements from an <see cref="ICollection"/>.
    /// </summary>
    ICollection_ClearFunc Clear;

    /// <summary>
    /// A function that removes the first occurance of the given item from an <see cref="ICollection"/>.
    /// </summary>
    ICollection_RemoveFunc Remove;
} ICollectionVTable;

/* Functions */
/// <summary>
/// Initializes an <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an uninitialized <see cref="ICollection"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="collection"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void ICollection_Constructor(
    ICollection *collection,
    const ICollectionVTable *vtable);

/// <summary>
/// Adds an item to an <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <param name="item">The item to add.</param>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
void ICollection_Add(ICollection *collection, void *item);

/// <summary>
/// Removes all elements from an <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
void ICollection_Clear(ICollection *collection);

/// <summary>
/// Removes the first occurance of the given item from an <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <param name="item">The item to remove.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="item"/> was successfully removed; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
bool ICollection_Remove(ICollection *collection, const void *item);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through an <see cref="ICollection"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
struct IEnumerator *ICollection_GetEnumerator(const ICollection *collection);

/* IReadOnlyCollection */
/// <summary>
/// Gets the number of elements in an <see cref="ICollection"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <returns>The number of elements in the <see cref="ICollection"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
uintsize ICollection_GetCount(const ICollection *collection);

/// <summary>
/// Determines whether an <see cref="ICollection"/> contains the given value.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
bool ICollection_Contains(const ICollection *collection, const void *item);

/// <summary>
/// Copies the elements of an <see cref="ICollection"/> to the given array.
/// </summary>
/// <param name="collection">Pointer to an <see cref="ICollection"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="ICollection"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="collection"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
void ICollection_CopyTo(const ICollection *collection, void *destination);

#endif
