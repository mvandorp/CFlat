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

//! @file Array.h

#ifndef CFLAT_CORE_COLLECTIONS_ARRAY_H
#define CFLAT_CORE_COLLECTIONS_ARRAY_H

#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
struct IEnumerator;

/* Types */
/// <summary>
/// Represents a dynamically sized array of objects. Implements <see cref="IReadOnlyList"/>.
/// </summary>
typedef struct Array Array;

/* Functions */
/// <summary>
/// Allocates and initializes an <see cref="Array"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="Array"/> should be managed with retain() and release().
/// </remarks>
/// <param name="source">The source array.</param>
/// <param name="length">The number of elements in the array.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="equals">
///     An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
/// </param>
/// <returns>A pointer to the newly allocated <see cref="Array"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="source"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException"><paramref name="elementSize"/> is 0.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
Array *Array_New(void *source, uintsize length, uintsize elementSize, EqualityPredicate equals);

/// <summary>
/// Initializes an <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an uninitialized <see cref="Array"/>.</param>
/// <param name="source">The source array.</param>
/// <param name="length">The number of elements in the array.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="equals">
///     An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="source"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException"><paramref name="elementSize"/> is 0.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Array_Constructor(Array *array, void *source, uintsize length, uintsize elementSize, EqualityPredicate equals);

/// <summary>
/// Destroys an <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
void Array_Destructor(Array *array);

/// <summary>
/// Gets the size in bytes of each element in an <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <returns>The size in bytes of each element in the <see cref="Array"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
uintsize Array_GetElementSize(const Array *array);

/// <summary>
/// Gets the number of elements in an <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <returns>The number of elements in the <see cref="Array"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
uintsize Array_GetLength(const Array *array);

/// <summary>
/// Replaces the item at the given index of an <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index, must be an lvalue.</param>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
/// </exception>
#define Array_SetItem(array, index, item) Array_SetItemRef(array, index, &item)

/// <summary>
/// Replaces the item at the given index of an <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="item"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
/// </exception>
void Array_SetItemRef(Array *array, uintsize index, const void *item);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through an <see cref="Array"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
struct IEnumerator *Array_GetEnumerator(const Array *array);

/* IReadOnlyCollection */
/// <summary>
/// Determines whether an <see cref="Array"/> contains the given value.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <param name="item">The item to find, must be an lvalue.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// </exception>
#define Array_Contains(array, item) Array_ContainsRef(array, &item)

/// <summary>
/// Determines whether an <see cref="Array"/> contains the given value.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="item"/> is <see cref="null"/>.
/// </exception>
bool Array_ContainsRef(const Array *array, const void *item);

/// <summary>
/// Copies the elements of an <see cref="Array"/> to the given array.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <param name="destination">
///     The array that is the destination of the elements copied from the <see cref="Array"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
void Array_CopyTo(const Array *array, void *destination);

/* IReadOnlyList */
/// <summary>
/// Gets the item at the given index of an <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <param name="type">The type of the element.</param>
/// <returns>The item at the given index of the <see cref="Array"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
/// </exception>
#define Array_GetItem(array, index, type) (*(type*)Array_GetItemRef(array, index))

/// <summary>
/// Gets the item at the given index of an <see cref="Array"/>.
/// </summary>
/// <remarks>
///     The returned pointer shall no longer be dereferenced after the first call to a function that modifies
///     <paramref name="array"/>.
/// </remarks>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="Array"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException">
///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
/// </exception>
void *Array_GetItemRef(const Array *array, uintsize index);

/// <summary>
/// Determines the index of the given item in an <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <param name="item">The item to find, must be an lvalue.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise <see cref="InvalidIndex"/>.</returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="item"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::InvalidOperationException">
///     <paramref name="array"/> does not have an equality predicate set.
/// </exception>
#define Array_IndexOf(array, item) Array_IndexOfRef(array, &item)

/// <summary>
/// Determines the index of the given item in an <see cref="Array"/>.
/// </summary>
/// <param name="array">Pointer to an <see cref="Array"/>.</param>
/// <param name="item">The item to find.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise <see cref="InvalidIndex"/>.</returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="item"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::InvalidOperationException">
///     <paramref name="array"/> does not have an equality predicate set.
/// </exception>
uintsize Array_IndexOfRef(const Array *array, const void *item);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/Collections/Array.internal.h"
#endif

#endif
