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

//! @file ObjectList.h

#ifndef CFLAT_CORE_COLLECTIONS_OBJECTLIST_H
#define CFLAT_CORE_COLLECTIONS_OBJECTLIST_H

#include "CFlat/Object.h"
#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
struct ICollection;
struct IEnumerable;
struct IEnumerator;

/* Macros */
/// <summary>
/// The maximum number of elements a <see cref="ObjectList"/> can hold.
/// </summary>
#define ObjectList_MaxCapacity PointerList_MaxCapacity

/* Types */
/// <summary>
/// Represents a dynamically sized list of <see cref="Object"/>s. Implements <see cref="IList"/>.
/// </summary>
typedef struct ObjectList ObjectList;

/* Functions */
/// <summary>
/// Allocates and initializes a <see cref="ObjectList"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="ObjectList"/> should be managed with retain() and release().
/// </remarks>
/// <returns>A pointer to the newly allocated <see cref="ObjectList"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
ObjectList *ObjectList_New(void);

/// <summary>
/// Allocates and initializes a <see cref="ObjectList"/> with the given capacity.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="ObjectList"/> should be managed with retain() and release().
/// </remarks>
/// <param name="capacity">The initial capacity of the <see cref="ObjectList"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="ObjectList"/>.</returns>
/// <exception cref="::ArgumentOutOfRangeException"><paramref name="capacity"/> is less than 0.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
ObjectList *ObjectList_New_WithCapacity(int capacity);

/// <summary>
/// Allocates and initializes a <see cref="ObjectList"/> that contains the elements copied from the given collection.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="ObjectList"/> should be managed with retain() and release().
/// </remarks>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/> whose elements are copied.</param>
/// <returns>A pointer to the newly allocated <see cref="ObjectList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
ObjectList *ObjectList_New_FromEnumerable(const struct IEnumerable *collection);

/// <summary>
/// Allocates and initializes a <see cref="ObjectList"/> that contains the elements copied from the given collection.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="ObjectList"/> should be managed with retain() and release().
/// </remarks>
/// <param name="collection">Pointer to an <see cref="ICollection"/> whose elements are copied.</param>
/// <returns>A pointer to the newly allocated <see cref="ObjectList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
ObjectList *ObjectList_New_FromCollection(const struct ICollection *collection);

/// <summary>
/// Initializes a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="ObjectList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectList_Constructor(ObjectList *list);

/// <summary>
/// Initializes a <see cref="ObjectList"/> with the given capacity.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="ObjectList"/>.</param>
/// <param name="capacity">The initial capacity of the <see cref="ObjectList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException"><paramref name="capacity"/> is less than 0.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectList_Constructor_WithCapacity(ObjectList *list, int capacity);

/// <summary>
/// Initializes a <see cref="ObjectList"/> that contains the elements copied from the given collection.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="ObjectList"/>.</param>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/> whose elements are copied.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="collection"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectList_Constructor_FromEnumerable(
    ObjectList *list,
    const struct IEnumerable *collection);

/// <summary>
/// Initializes a <see cref="ObjectList"/> that contains the elements copied from the given collection.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="ObjectList"/>.</param>
/// <param name="collection">Pointer to an <see cref="ICollection"/> whose elements are copied.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="collection"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectList_Constructor_FromCollection(
    ObjectList *list,
    const struct ICollection *collection);

/// <summary>
/// Destroys a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
void ObjectList_Destructor(ObjectList *list);

/// <summary>
/// Gets the capacity of a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <returns>The capacity of the <see cref="ObjectList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
int ObjectList_GetCapacity(const ObjectList *list);

/// <summary>
/// Sets the capacity of a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="capacity">The new capacity of the <see cref="ObjectList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="capacity"/> is less than the number of elements in <paramref name="list"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectList_SetCapacity(ObjectList *list, int capacity);

/// <summary>
/// Adds the elements of the given collection to the end of a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="collection">
///     Pointer to an <see cref="IEnumerable"/> whose elements should be added to the end of the
///     <see cref="ObjectList"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="collection"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectList_AddRange(ObjectList *list, const struct IEnumerable *collection);

/// <summary>
/// Inserts the elements of the given collection into a <see cref="ObjectList"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="index">The position where the new elements should be inserted.</param>
/// <param name="collection">
///     Pointer to an <see cref="IEnumerable"/> whose elements should be inserted into the <see cref="ObjectList"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="collection"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectList_InsertRange(ObjectList *list, int index, const struct IEnumerable *collection);

/// <summary>
/// Removes the given range of elements from the a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="index">The position where to start removing elements.</param>
/// <param name="count">The number of elements to remove.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="count"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> and <paramref name="count"/> do not denote a valid range of elements in
///     <paramref name="list"/>.
/// </exception>
void ObjectList_RemoveRange(ObjectList *list, int index, int count);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through a <see cref="ObjectList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
struct IEnumerator *ObjectList_GetEnumerator(const ObjectList *list);

/* ICollection */
/// <summary>
/// Gets the number of elements in a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <returns>The number of elements in the <see cref="ObjectList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
int ObjectList_GetCount(const ObjectList *list);

/// <summary>
/// Adds an item to a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="item">The item to add.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectList_Add(ObjectList *list, void *item);

/// <summary>
/// Removes all elements from a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
void ObjectList_Clear(ObjectList *list);

/// <summary>
/// Determines whether a <see cref="ObjectList"/> contains the given value.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
bool ObjectList_Contains(const ObjectList *list, const void *item);

/// <summary>
/// Copies the elements of a <see cref="ObjectList"/> to the given array.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="ObjectList"/>.
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
void ObjectList_CopyTo(const ObjectList *list, void *destination, uintsize destinationSize);

/// <summary>
/// Removes the first occurance of the given item from a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="item">The item to remove.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="item"/> was successfully removed; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
bool ObjectList_Remove(ObjectList *list, const void *item);

/* IList */
/// <summary>
/// Gets the item at the given index of a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="ObjectList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void *ObjectList_GetItem(const ObjectList *list, int index);

/// <summary>
/// Replaces the item at the given index of a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void ObjectList_SetItem(ObjectList *list, int index, const void *item);

/// <summary>
/// Determines the index of the given item in a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise -1.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
int ObjectList_IndexOf(const ObjectList *list, const void *item);

/// <summary>
/// Inserts an item into a <see cref="ObjectList"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="index">The index at which <paramref name="item"/> should be inserted.</param>
/// <param name="item">The item to insert.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is greater than the number of elements in <paramref name="list"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectList_Insert(ObjectList *list, int index, void *item);

/// <summary>
/// Removes the element at the given index of a <see cref="ObjectList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="ObjectList"/>.</param>
/// <param name="index">The index of the element to remove.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void ObjectList_RemoveAt(ObjectList *list, int index);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/Collections/ObjectList.internal.h"
#endif

#endif
