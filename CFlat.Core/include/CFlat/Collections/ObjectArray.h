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

//! @file ObjectArray.h

#ifndef CFLAT_CORE_COLLECTIONS_OBJECTARRAY_H
#define CFLAT_CORE_COLLECTIONS_OBJECTARRAY_H

#include "CFlat/Language/Integer.h"

/* Forward declarations */
struct IEnumerator;

/* Types */
/// <summary>
/// Represents a dynamically sized array of objects. Implements <see cref="IReadOnlyList"/>.
/// </summary>
typedef struct ObjectArray ObjectArray;

/* Functions */
/// <summary>
/// Allocates and initializes an <see cref="ObjectArray"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="ObjectArray"/> should be managed with retain() and release().
/// </remarks>
/// <param name="source">The source array.</param>
/// <param name="length">The number of elements in the array.</param>
/// <returns>A pointer to the newly allocated <see cref="ObjectArray"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="source"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
ObjectArray *ObjectArray_New(void **source, uintsize length);

/// <summary>
/// Initializes an <see cref="ObjectArray"/>.
/// </summary>
/// <param name="array">Pointer to an uninitialized <see cref="ObjectArray"/>.</param>
/// <param name="source">The source array.</param>
/// <param name="length">The number of elements in the array.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="source"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void ObjectArray_Constructor(ObjectArray *array, void **source, uintsize length);

/// <summary>
/// Destroys an <see cref="ObjectArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="ObjectArray"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
void ObjectArray_Destructor(ObjectArray *array);

/// <summary>
/// Gets the number of elements in an <see cref="ObjectArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="ObjectArray"/>.</param>
/// <returns>The number of elements in the <see cref="ObjectArray"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
uintsize ObjectArray_GetLength(const ObjectArray *array);

/// <summary>
/// Replaces the item at the given index of an <see cref="ObjectArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="ObjectArray"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index.</param>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
/// </exception>
void ObjectArray_SetItem(ObjectArray *array, uintsize index, const void *item);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="ObjectArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="ObjectArray"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through an <see cref="ObjectArray"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
struct IEnumerator *ObjectArray_GetEnumerator(const ObjectArray *array);

/* IReadOnlyCollection */
/// <summary>
/// Determines whether an <see cref="ObjectArray"/> contains the given value.
/// </summary>
/// <param name="array">Pointer to an <see cref="ObjectArray"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
bool ObjectArray_Contains(const ObjectArray *array, const void *item);

/// <summary>
/// Copies the elements of an <see cref="ObjectArray"/> to the given array.
/// </summary>
/// <param name="array">Pointer to an <see cref="ObjectArray"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="ObjectArray"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
void ObjectArray_CopyTo(const ObjectArray *array, void *destination);

/* IReadOnlyList */
/// <summary>
/// Gets the item at the given index of an <see cref="ObjectArray"/>.
/// </summary>
/// <remarks>
///     The returned pointer shall no longer be dereferenced after the first call to a function that modifies
///     <paramref name="array"/>.
/// </remarks>
/// <param name="array">Pointer to an <see cref="ObjectArray"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="ObjectArray"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
/// </exception>
void *ObjectArray_GetItem(const ObjectArray *array, uintsize index);

/// <summary>
/// Determines the index of the given item in an <see cref="ObjectArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="ObjectArray"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise <see cref="InvalidIndex"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// <exception cref="::InvalidOperationException">
///     <paramref name="array"/> does not have an equality predicate set.
/// </exception>
uintsize ObjectArray_IndexOf(const ObjectArray *array, const void *item);

#ifdef CFLAT_CORE_INTERNAL
#include "CFlat/Collections/ObjectArray.internal.h"
#endif

#endif
