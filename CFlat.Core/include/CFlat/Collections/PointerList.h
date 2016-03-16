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

//! @file PointerList.h

#ifndef CFLAT_CORE_COLLECTIONS_POINTERLIST_H
#define CFLAT_CORE_COLLECTIONS_POINTERLIST_H

#include "CFlat/Object.h"
#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
struct ICollection;
struct IEnumerable;
struct IEnumerator;

/* Macros */
/// <summary>
/// The maximum number of elements a <see cref="PointerList"/> can hold.
/// </summary>
#define PointerList_MaxCapacity List_MaxCapacity

/* Types */
/// <summary>
/// Represents a dynamically sized list of pointers. Implements <see cref="IList"/>.
/// </summary>
typedef struct PointerList PointerList;

/* Functions */
/// <summary>
/// Allocates and initializes a <see cref="PointerList"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="PointerList"/> should be managed with retain() and release().
/// </remarks>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <returns>A pointer to the newly allocated <see cref="PointerList"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
PointerList *PointerList_New(DestructorFunc elementDestructor);

/// <summary>
/// Allocates and initializes a <see cref="PointerList"/> with the given capacity.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="PointerList"/> should be managed with retain() and release().
/// </remarks>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <param name="capacity">The initial capacity of the <see cref="PointerList"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="PointerList"/>.</returns>
/// <exception cref="::ArgumentOutOfRangeException"><paramref name="capacity"/> is less than 0.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
PointerList *PointerList_New_WithCapacity(DestructorFunc elementDestructor, int capacity);

/// <summary>
/// Allocates and initializes a <see cref="PointerList"/> that contains the elements copied from the given collection.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="PointerList"/> should be managed with retain() and release().
/// </remarks>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/> whose elements are copied.</param>
/// <returns>A pointer to the newly allocated <see cref="PointerList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
PointerList *PointerList_New_FromEnumerable(DestructorFunc elementDestructor, const struct IEnumerable *collection);

/// <summary>
/// Allocates and initializes a <see cref="PointerList"/> that contains the elements copied from the given collection.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="PointerList"/> should be managed with retain() and release().
/// </remarks>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <param name="collection">Pointer to an <see cref="ICollection"/> whose elements are copied.</param>
/// <returns>A pointer to the newly allocated <see cref="PointerList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
PointerList *PointerList_New_FromCollection(DestructorFunc elementDestructor, const struct ICollection *collection);

/// <summary>
/// Initializes a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="PointerList"/>.</param>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerList_Constructor(PointerList *list, DestructorFunc elementDestructor);

/// <summary>
/// Initializes a <see cref="PointerList"/> with the given capacity.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="PointerList"/>.</param>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <param name="capacity">The initial capacity of the <see cref="PointerList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException"><paramref name="capacity"/> is less than 0.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerList_Constructor_WithCapacity(PointerList *list, DestructorFunc elementDestructor, int capacity);

/// <summary>
/// Initializes a <see cref="PointerList"/> that contains the elements copied from the given collection.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="PointerList"/>.</param>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/> whose elements are copied.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="collection"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerList_Constructor_FromEnumerable(
    PointerList *list,
    DestructorFunc elementDestructor,
    const struct IEnumerable *collection);

/// <summary>
/// Initializes a <see cref="PointerList"/> that contains the elements copied from the given collection.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="PointerList"/>.</param>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <param name="collection">Pointer to an <see cref="ICollection"/> whose elements are copied.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="collection"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerList_Constructor_FromCollection(
    PointerList *list,
    DestructorFunc elementDestructor,
    const struct ICollection *collection);

/// <summary>
/// Destroys a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
void PointerList_Destructor(PointerList *list);

/// <summary>
/// Gets the capacity of a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <returns>The capacity of the <see cref="PointerList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
int PointerList_GetCapacity(const PointerList *list);

/// <summary>
/// Sets the capacity of a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="capacity">The new capacity of the <see cref="PointerList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="capacity"/> is less than the number of elements in <paramref name="list"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerList_SetCapacity(PointerList *list, int capacity);

/// <summary>
/// Adds the elements of the given collection to the end of a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="collection">
///     Pointer to an <see cref="IEnumerable"/> whose elements should be added to the end of the
///     <see cref="PointerList"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="collection"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerList_AddRange(PointerList *list, const struct IEnumerable *collection);

/// <summary>
/// Inserts the elements of the given collection into a <see cref="PointerList"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="index">The position where the new elements should be inserted.</param>
/// <param name="collection">
///     Pointer to an <see cref="IEnumerable"/> whose elements should be inserted into the <see cref="PointerList"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="collection"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerList_InsertRange(PointerList *list, int index, const struct IEnumerable *collection);

/// <summary>
/// Removes the given range of elements from the a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="index">The position where to start removing elements.</param>
/// <param name="count">The number of elements to remove.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="count"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> and <paramref name="count"/> do not denote a valid range of elements in
///     <paramref name="list"/>.
/// </exception>
void PointerList_RemoveRange(PointerList *list, int index, int count);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through a <see cref="PointerList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
struct IEnumerator *PointerList_GetEnumerator(const PointerList *list);

/* ICollection */
/// <summary>
/// Gets the number of elements in a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <returns>The number of elements in the <see cref="PointerList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
int PointerList_GetCount(const PointerList *list);

/// <summary>
/// Adds an item to a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="item">The item to add.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerList_Add(PointerList *list, void *item);

/// <summary>
/// Removes all elements from a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
void PointerList_Clear(PointerList *list);

/// <summary>
/// Determines whether a <see cref="PointerList"/> contains the given value.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
bool PointerList_Contains(const PointerList *list, const void *item);

/// <summary>
/// Copies the elements of a <see cref="PointerList"/> to the given array.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="PointerList"/>.
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
void PointerList_CopyTo(const PointerList *list, void *destination, uintsize destinationSize);

/// <summary>
/// Removes the first occurance of the given item from a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="item">The item to remove.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="item"/> was successfully removed; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
bool PointerList_Remove(PointerList *list, const void *item);

/* IList */
/// <summary>
/// Gets the item at the given index of a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="PointerList"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void *PointerList_GetItem(const PointerList *list, int index);

/// <summary>
/// Replaces the item at the given index of a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void PointerList_SetItem(PointerList *list, int index, const void *item);

/// <summary>
/// Determines the index of the given item in a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise -1.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
int PointerList_IndexOf(const PointerList *list, const void *item);

/// <summary>
/// Inserts an item into a <see cref="PointerList"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="index">The index at which <paramref name="item"/> should be inserted.</param>
/// <param name="item">The item to insert.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is greater than the number of elements in <paramref name="list"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerList_Insert(PointerList *list, int index, void *item);

/// <summary>
/// Removes the element at the given index of a <see cref="PointerList"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="PointerList"/>.</param>
/// <param name="index">The index of the element to remove.</param>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is less than 0 <b>-or-</b>
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
/// </exception>
void PointerList_RemoveAt(PointerList *list, int index);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/Collections/PointerList.internal.h"
#endif

#endif
