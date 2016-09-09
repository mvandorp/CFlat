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

//! @file IEnumerator.h

#ifndef CFLAT_CORE_COLLECTIONS_IENUMERATOR_H
#define CFLAT_CORE_COLLECTIONS_IENUMERATOR_H

#include "CFlat/Object.h"
#include "CFlat/Language/Bool.h"

/* Macros */
/// <summary>
/// Initializer for an <see cref="IEnumerator"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define IEnumerator_Initializer(vtable) { Object_Initializer(vtable)

/// <summary>
/// Initializer for a const <see cref="IEnumerator"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define IEnumerator_const_Initializer(vtable) { Object_const_Initializer(vtable) }

/// <summary>
/// Initializer for an <see cref="IEnumertorVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="getCurrent">An <see cref="IEnumerator_GetCurrentFunc"/>.</param>
/// <param name="moveNext">An <see cref="IEnumerator_MoveNextFunc"/>.</param>
/// <param name="reset">An <see cref="IEnumerator_ResetFunc"/>.</param>
#define IEnumeratorVTable_Initializer(destructor, getCurrent, moveNext, reset)  \
{                                                                               \
    ObjectVTable_Initializer(destructor),                                       \
    getCurrent,                                                                 \
    moveNext,                                                                   \
    reset                                                                       \
}

/* Types */
/// <summary>
/// Supports a simple iteration over a collection of elements.
/// </summary>
typedef struct IEnumerator {
    /// <summary>
    /// The base class of <see cref="IEnumerator"/>.
    /// </summary>
    Object Base;
} IEnumerator;

/// <summary>
/// A function that returns the element at the current position in the collection of an <see cref="IEnumerator"/>.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>
///     A pointer to the element at the current position in the collection of the <see cref="IEnumerator"/>.
/// </returns>
typedef void *(*IEnumerator_GetCurrentFunc)(const IEnumerator *enumerator);

/// <summary>
/// A function that moves an <see cref="IEnumerator"/> to the next element in the collection.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>
///     <see cref="true"/> if the enumerator was successfully advanced to the next element;
///     <see cref="false"/> if the enumerator passed the end of the collection.
/// </returns>
typedef bool(*IEnumerator_MoveNextFunc)(IEnumerator *enumerator);

/// <summary>
/// A function that resets an <see cref="IEnumerator"/> to its initial position, which is before the first element in
/// the collection.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
typedef void(*IEnumerator_ResetFunc)(IEnumerator *enumerator);

/// <summary>
/// A virtual method table for the <see cref="IEnumerator"/> class.
/// </summary>
typedef struct IEnumeratorVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="IEnumerator"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that returns the element at the current position in the collection of an <see cref="IEnumerator"/>.
    /// </summary>
    IEnumerator_GetCurrentFunc GetCurrent;

    /// <summary>
    /// A function that moves an <see cref="IEnumerator"/> to the next element in the collection
    /// </summary>
    IEnumerator_MoveNextFunc MoveNext;

    /// <summary>
    /// A function that resets a given <see cref="IEnumerator"/> to its initial position, which is before the first
    /// element in the collection.
    /// </summary>
    IEnumerator_ResetFunc Reset;
} IEnumeratorVTable;

/* Functions */
/// <summary>
/// Initializes an <see cref="IEnumerator"/>.
/// </summary>
/// <param name="enumerator">Pointer to an uninitialized <see cref="IEnumerator"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="enumerator"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void IEnumerator_Constructor(
    IEnumerator *enumerator,
    const IEnumeratorVTable *vtable);

/// <summary>
/// Returns the element at the current position in the collection of an <see cref="IEnumerator"/>.
/// </summary>
/// <remarks>
///     If the collection contains value types, the returned pointer shall no longer be dereferenced after the first
///     call to a function that modifies the collection.
/// </remarks>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>A pointer to the current element.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="enumerator"/> is <see cref="null"/>.</exception>
/// <exception cref="::InvalidOperationException">
///     The collection was modified during enumeration <b>-or-</b>
///     The enumeration has either not started or has already finished.
/// </exception>
void *IEnumerator_GetCurrent(const IEnumerator *enumerator);

/// <summary>
/// Moves an <see cref="IEnumerator"/> to the next element in the collection
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>
///     <see cref="true"/> if the enumerator was successfully advanced to the next element;
///     <see cref="false"/> if the enumerator passed the end of the collection.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="enumerator"/> is <see cref="null"/>.</exception>
/// <exception cref="::InvalidOperationException">The collection was modified during enumeration.</exception>
bool IEnumerator_MoveNext(IEnumerator *enumerator);

/// <summary>
/// Resets an <see cref="IEnumerator"/> to its initial position, which is before the first element in the
/// collection.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="enumerator"/> is <see cref="null"/>.</exception>
/// <exception cref="::InvalidOperationException">The collection was modified during enumeration.</exception>
void IEnumerator_Reset(IEnumerator *enumerator);

#endif
