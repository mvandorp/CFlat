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

//! @file IList.h

#ifndef CFLAT_CORE_COLLECTIONS_ILIST_H
#define CFLAT_CORE_COLLECTIONS_ILIST_H

#include "CFlat/Collections/ICollection.h"
#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
struct IEnumerator;

/* Macros */
/// <summary>
/// Initializer for an <see cref="IListVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="getEnumerator">An <see cref="IEnumerable_GetEnumeratorFunc"/>.</param>
/// <param name="getCount">An <see cref="ICollection_GetCountFunc"/>.</param>
/// <param name="isReadOnly">An <see cref="ICollection_IsReadOnlyFunc"/>.</param>
/// <param name="add">An <see cref="ICollection_AddFunc"/>.</param>
/// <param name="clear">An <see cref="ICollection_ClearFunc"/>.</param>
/// <param name="contains">An <see cref="ICollection_ContainsFunc"/>.</param>
/// <param name="copyTo">An <see cref="ICollection_CopyToFunc"/>.</param>
/// <param name="remove">An <see cref="ICollection_RemoveFunc"/>.</param>
/// <param name="getItem">An <see cref="IList_GetItemFunc"/>.</param>
/// <param name="setItem">An <see cref="IList_SetItemFunc"/>.</param>
/// <param name="indexOf">An <see cref="IList_IndexOfFunc"/>.</param>
/// <param name="insert">An <see cref="IList_InsertFunc"/>.</param>
/// <param name="removeAt">An <see cref="IList_RemoveAtFunc"/>.</param>
#define IListVTable_Initializer(                                \
    destructor,                                                 \
    getEnumerator,                                              \
    getCount,                                                   \
    isReadOnly,                                                 \
    add,                                                        \
    clear,                                                      \
    contains,                                                   \
    copyTo,                                                     \
    remove,                                                     \
    getItem,                                                    \
    setItem,                                                    \
    indexOf,                                                    \
    insert,                                                     \
    removeAt)                                                   \
{                                                               \
    ICollectionVTable_Initializer(                              \
        destructor,                                             \
        getEnumerator,                                          \
        getCount,                                               \
        isReadOnly,                                             \
        add,                                                    \
        clear,                                                  \
        contains,                                               \
        copyTo,                                                 \
        remove),                                                \
    getItem,                                                    \
    setItem,                                                    \
    indexOf,                                                    \
    insert,                                                     \
    removeAt                                                    \
}

/* Types */
/// <summary>
/// Base class for a list of elements.
/// </summary>
typedef struct IList {
    /// <summary>
    /// The base class of <see cref="IList"/>.
    /// </summary>
    ICollection Base;
} IList;

/// <summary>
/// A function that returns the item at the given index of an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="IList"/>.</returns>
typedef void *(*IList_GetItemFunc)(const IList *list, int index);

/// <summary>
/// A function that replaces the item at the given index of an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index.</param>
typedef void (*IList_SetItemFunc)(IList *list, int index, const void *item);

/// <summary>
/// A function that determines the index of the given item in an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise -1.</returns>
typedef int (*IList_IndexOfFunc)(const IList *list, const void *item);

/// <summary>
/// A function that inserts an item into an <see cref="IList"/> at the given index.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="index">The index at which <paramref name="item"/> should be inserted.</param>
/// <param name="item">The item to insert.</param>
typedef void (*IList_InsertFunc)(IList *list, int index, const void *item);

/// <summary>
/// A function that removes the element at the given index of an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="index">The index of the element to remove.</param>
typedef void (*IList_RemoveAtFunc)(IList *list, int index);

/// <summary>
/// A virtual method table for the <see cref="IList"/> class.
/// </summary>
typedef struct IListVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="IList"/>.
    /// </summary>
    ICollectionVTable Base;

    /// <summary>
    /// A function that returns the item at the given index of an <see cref="IList"/>.
    /// </summary>
    IList_GetItemFunc GetItem;

    /// <summary>
    /// A function that replaces the item at the given index of an <see cref="IList"/>.
    /// </summary>
    IList_SetItemFunc SetItem;

    /// <summary>
    /// A function that determines the index of the given item in an <see cref="IList"/>.
    /// </summary>
    IList_IndexOfFunc IndexOf;

    /// <summary>
    /// A function that inserts an item into an <see cref="IList"/> at the given index.
    /// </summary>
    IList_InsertFunc Insert;

    /// <summary>
    /// A function that removes the element at the given index of an <see cref="IList"/>.
    /// </summary>
    IList_RemoveAtFunc RemoveAt;
} IListVTable;

/* Functions */
/// <summary>
/// Initializes an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="IList"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void IList_Constructor(
    IList *list,
    const IListVTable *vtable);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through an <see cref="IList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
struct IEnumerator *IList_GetEnumerator(const IList *list);

/* ICollection */
/// <summary>
/// Gets the number of elements in an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <returns>The number of elements in the <see cref="IList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
int IList_GetCount(const IList *list);

/// <summary>
/// Gets whether or not an <see cref="IList"/> is read-only.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <returns>
///     <see cref="true"/> if the <see cref="IList"/> is read-only; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
bool IList_IsReadOnly(const IList *list);

/// <summary>
/// Adds an item to an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="item">The item to add.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
void IList_Add(IList *list, const void *item);

/// <summary>
/// Removes all elements from an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
void IList_Clear(IList *list);

/// <summary>
/// Determines whether an <see cref="IList"/> contains the given value.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
bool IList_Contains(const IList *list, const void *item);

/// <summary>
/// Copies the elements of an <see cref="IList"/> to the given array.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="IList"/>.
/// </param>
/// <param name="destinationSize">The size in bytes of the array.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentException">
///     The number of elements in the list is greater than the number of elements that the destination array can
///     contain.
/// </exception>
void IList_CopyTo(const IList *list, void *destination, uintsize destinationSize);

/// <summary>
/// Removes the first occurance of the given item from an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="item">The item to remove.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="item"/> was successfully removed; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
bool IList_Remove(IList *list, const void *item);

/* IList */
/// <summary>
/// Gets the item at the given index of an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="IList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void *IList_GetItem(const IList *list, int index);

/// <summary>
/// Replaces the item at the given index of an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void IList_SetItem(IList *list, int index, const void *item);

/// <summary>
/// Determines the index of the given item in an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise -1.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
int IList_IndexOf(const IList *list, const void *item);

/// <summary>
/// Inserts an item into an <see cref="IList"/> at the given index.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="index">The index at which <paramref name="item"/> should be inserted.</param>
/// <param name="item">The item to insert.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is greater than the number of elements in <paramref name="list"/>.
/// </exception>
void IList_Insert(IList *list, int index, const void *item);

/// <summary>
/// Removes the element at the given index of an <see cref="IList"/>.
/// </summary>
/// <param name="list">Pointer to an <see cref="IList"/>.</param>
/// <param name="index">The index of the element to remove.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void IList_RemoveAt(IList *list, int index);

#endif
