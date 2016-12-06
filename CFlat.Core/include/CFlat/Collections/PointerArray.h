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

//! @file PointerArray.h

#ifndef CFLAT_CORE_COLLECTIONS_POINTERARRAY_H
#define CFLAT_CORE_COLLECTIONS_POINTERARRAY_H

#include "CFlat/Object.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
struct IEnumerator;

/* Types */
/// <summary>
/// Represents a dynamically sized array of objects. Implements <see cref="IReadOnlyList"/>.
/// </summary>
typedef struct PointerArray PointerArray;

/* Functions */
/// <summary>
/// Allocates and initializes an <see cref="PointerArray"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="PointerArray"/> should be managed with retain() and release().
/// </remarks>
/// <param name="source">The source array.</param>
/// <param name="length">The number of elements in the array.</param>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <returns>A pointer to the newly allocated <see cref="PointerArray"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="source"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
PointerArray *PointerArray_New(void **source, uintsize length, DestructorFunc elementDestructor);

/// <summary>
/// Initializes an <see cref="PointerArray"/>.
/// </summary>
/// <param name="array">Pointer to an uninitialized <see cref="PointerArray"/>.</param>
/// <param name="source">The source array.</param>
/// <param name="length">The number of elements in the array.</param>
/// <param name="elementDestructor">
///     Pointer to a <see cref="DestructorFunc"/> to call when an element needs to be destroyed, or <see cref="null"/>
///     if elements should not automatically be destroyed.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="source"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void PointerArray_Constructor(PointerArray *array, void **source, uintsize length, DestructorFunc elementDestructor);

/// <summary>
/// Destroys an <see cref="PointerArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="PointerArray"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
void PointerArray_Destructor(PointerArray *array);

/// <summary>
/// Gets the number of elements in an <see cref="PointerArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="PointerArray"/>.</param>
/// <returns>The number of elements in the <see cref="PointerArray"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
uintsize PointerArray_GetLength(const PointerArray *array);

/// <summary>
/// Replaces the item at the given index of an <see cref="PointerArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="PointerArray"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index.</param>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
/// </exception>
void PointerArray_SetItem(PointerArray *array, uintsize index, const void *item);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="PointerArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="PointerArray"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through an <see cref="PointerArray"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
struct IEnumerator *PointerArray_GetEnumerator(const PointerArray *array);

/* IReadOnlyCollection */
/// <summary>
/// Determines whether an <see cref="PointerArray"/> contains the given value.
/// </summary>
/// <param name="array">Pointer to an <see cref="PointerArray"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
bool PointerArray_Contains(const PointerArray *array, const void *item);

/// <summary>
/// Copies the elements of an <see cref="PointerArray"/> to the given array.
/// </summary>
/// <param name="array">Pointer to an <see cref="PointerArray"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="PointerArray"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
void PointerArray_CopyTo(const PointerArray *array, void *destination);

/* IReadOnlyList */
/// <summary>
/// Gets the item at the given index of an <see cref="PointerArray"/>.
/// </summary>
/// <remarks>
///     The returned pointer shall no longer be dereferenced after the first call to a function that modifies
///     <paramref name="array"/>.
/// </remarks>
/// <param name="array">Pointer to an <see cref="PointerArray"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="PointerArray"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
/// </exception>
void *PointerArray_GetItem(const PointerArray *array, uintsize index);

/// <summary>
/// Determines the index of the given item in an <see cref="PointerArray"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="PointerArray"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise <see cref="InvalidIndex"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// <exception cref="::InvalidOperationException">
///     <paramref name="array"/> does not have an equality predicate set.
/// </exception>
uintsize PointerArray_IndexOf(const PointerArray *array, const void *item);

#ifdef CFLAT_CORE_INTERNAL
#include "CFlat/Collections/PointerArray.internal.h"
#endif

#endif
