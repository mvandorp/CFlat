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

//! @file IReadOnlyList.h

#ifndef CFLAT_CORE_COLLECTIONS_IREADONLYLIST_H
#define CFLAT_CORE_COLLECTIONS_IREADONLYLIST_H

#include "CFlat/Collections/ICollection.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
struct IEnumerator;

/* Macros */
/// <summary>
/// Initializer for an <see cref="IReadOnlyList"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define IIReadOnlyList_Initializer(vtable) { IReadOnlyCollection_Initializer(vtable) }

/// <summary>
/// Initializer for a const <see cref="IReadOnlyList"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define IIReadOnlyList_const_Initializer(vtable) { IReadOnlyCollection_const_Initializer(vtable) }

/// <summary>
/// Initializer for an <see cref="IReadOnlyListVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="getEnumerator">An <see cref="IEnumerable_GetEnumeratorFunc"/>.</param>
/// <param name="getCount">An <see cref="IReadOnlyCollection_GetCountFunc"/>.</param>
/// <param name="contains">An <see cref="IReadOnlyCollection_ContainsFunc"/>.</param>
/// <param name="copyTo">An <see cref="IReadOnlyCollection_CopyToFunc"/>.</param>
/// <param name="getItem">An <see cref="IReadOnlyList_GetItemFunc"/>.</param>
/// <param name="indexOf">An <see cref="IReadOnlyList_IndexOfFunc"/>.</param>
#define IReadOnlyListVTable_Initializer(                                \
    destructor,                                                         \
    getEnumerator,                                                      \
    getCount,                                                           \
    contains,                                                           \
    copyTo,                                                             \
    getItem,                                                            \
    indexOf)                                                            \
{                                                                       \
    ICollectionVTable_Initializer(                                      \
        destructor,                                                     \
        getEnumerator,                                                  \
        getCount,                                                       \
        (ICollection_AddFunc)__CFLAT_IREADONLYLIST_Add,                 \
        (ICollection_ClearFunc)__CFLAT_IREADONLYLIST_Clear,             \
        contains,                                                       \
        copyTo,                                                         \
        (ICollection_RemoveFunc)__CFLAT_IREADONLYLIST_Remove),          \
    getItem,                                                            \
    indexOf                                                             \
}

/// <summary>
/// Initializer for an <see cref="IReadOnlyListVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="getEnumerator">An <see cref="IEnumerable_GetEnumeratorFunc"/>.</param>
/// <param name="getCount">An <see cref="IReadOnlyCollection_GetCountFunc"/>.</param>
/// <param name="add">An <see cref="ICollection_AddFunc"/>.</param>
/// <param name="clear">An <see cref="ICollection_ClearFunc"/>.</param>
/// <param name="contains">An <see cref="IReadOnlyCollection_ContainsFunc"/>.</param>
/// <param name="copyTo">An <see cref="IReadOnlyCollection_CopyToFunc"/>.</param>
/// <param name="remove">An <see cref="ICollection_RemoveFunc"/>.</param>
/// <param name="getItem">An <see cref="IReadOnlyList_GetItemFunc"/>.</param>
/// <param name="indexOf">An <see cref="IReadOnlyList_IndexOfFunc"/>.</param>
#define IReadOnlyListVTable_ICollection_Initializer(                    \
    destructor,                                                         \
    getEnumerator,                                                      \
    getCount,                                                           \
    add,                                                                \
    clear,                                                              \
    contains,                                                           \
    copyTo,                                                             \
    remove,                                                             \
    getItem,                                                            \
    indexOf)                                                            \
{                                                                       \
    ICollectionVTable_Initializer(                                      \
        destructor,                                                     \
        getEnumerator,                                                  \
        getCount,                                                       \
        add,                                                            \
        clear,                                                          \
        contains,                                                       \
        copyTo,                                                         \
        remove),                                                        \
    getItem,                                                            \
    indexOf                                                             \
}

/* Types */
/// <summary>
/// Base class for a list of elements.
/// </summary>
typedef struct IReadOnlyList {
    /// <summary>
    /// The base class of <see cref="IReadOnlyList"/>.
    /// </summary>
    ICollection Base;
} IReadOnlyList;

/// <summary>
/// A function that returns the item at the given index of an <see cref="IReadOnlyList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="IReadOnlyList"/>.</returns>
typedef void *(*IReadOnlyList_GetItemFunc)(const IReadOnlyList *list, uintsize index);

/// <summary>
/// A function that determines the index of the given item in an <see cref="IReadOnlyList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise <see cref="InvalidIndex"/>.</returns>
typedef uintsize (*IReadOnlyList_IndexOfFunc)(const IReadOnlyList *list, const void *item);

/// <summary>
/// A virtual method table for the <see cref="IReadOnlyList"/> class.
/// </summary>
typedef struct IReadOnlyListVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="IReadOnlyList"/>.
    /// </summary>
    ICollectionVTable Base;

    /// <summary>
    /// A function that returns the item at the given index of an <see cref="IReadOnlyList"/>.
    /// </summary>
    IReadOnlyList_GetItemFunc GetItem;

    /// <summary>
    /// A function that determines the index of the given item in an <see cref="IReadOnlyList"/>.
    /// </summary>
    IReadOnlyList_IndexOfFunc IndexOf;
} IReadOnlyListVTable;

/* Functions */
/// <summary>
/// Initializes an <see cref="IReadOnlyList"/>.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="IReadOnlyList"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void IReadOnlyList_Constructor(
    IReadOnlyList *list,
    const IReadOnlyListVTable *vtable);
/// <summary>
/// Gets the item at the given index of an <see cref="IReadOnlyList"/>.
/// </summary>
/// <remarks>
///     If <paramref name="list"/> contains value types, the returned pointer shall no longer be dereferenced after the
///     first call to a function that modifies <paramref name="list"/>.
/// </remarks>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="IList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void *IReadOnlyList_GetItem(const IReadOnlyList *list, uintsize index);

/// <summary>
/// Determines the index of the given item in an <see cref="IReadOnlyList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise <see cref="InvalidIndex"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
uintsize IReadOnlyList_IndexOf(const IReadOnlyList *list, const void *item);

/// <summary>
/// Throws a <see cref="NotSupportedException"/>.
/// </summary>
/// <exception cref="::NotSupportedException">When this method is called.</exception>
bool __CFLAT_IREADONLYLIST_IsReadOnly(const IReadOnlyList *list);

/// <summary>
/// Throws a <see cref="NotSupportedException"/>.
/// </summary>
/// <exception cref="::NotSupportedException">When this method is called.</exception>
void __CFLAT_IREADONLYLIST_Add(IReadOnlyList *list, void *item);

/// <summary>
/// Throws a <see cref="NotSupportedException"/>.
/// </summary>
/// <exception cref="::NotSupportedException">When this method is called.</exception>
void __CFLAT_IREADONLYLIST_Clear(IReadOnlyList *list);

/// <summary>
/// Throws a <see cref="NotSupportedException"/>.
/// </summary>
/// <exception cref="::NotSupportedException">When this method is called.</exception>
bool __CFLAT_IREADONLYLIST_Remove(IReadOnlyList *list, const void *item);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="IReadOnlyList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through an <see cref="IReadOnlyList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
struct IEnumerator *IReadOnlyList_GetEnumerator(const IReadOnlyList *list);

/* IReadOnlyCollection */
/// <summary>
/// Gets the number of elements in an <see cref="IReadOnlyList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <returns>The number of elements in the <see cref="IReadOnlyList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
uintsize IReadOnlyList_GetCount(const IReadOnlyList *list);

/// <summary>
/// Determines whether an <see cref="IReadOnlyList"/> contains the given value.
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
bool IReadOnlyList_Contains(const IReadOnlyList *list, const void *item);

/// <summary>
/// Copies the elements of an <see cref="IReadOnlyList"/> to the given array.
/// </summary>
/// <param name="list">Pointer to an <see cref="IReadOnlyList"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="IReadOnlyList"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
void IReadOnlyList_CopyTo(const IReadOnlyList *list, void *destination);

#endif
