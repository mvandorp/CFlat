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

/**
 * @file IEnumerator.h
 */

#ifndef CFLAT_CORE_COLLECTIONS_IENUMERATOR_H
#define CFLAT_CORE_COLLECTIONS_IENUMERATOR_H

#include "CFlat/Object.h"
#include "CFlat/Language/Bool.h"

/* Macros */
/// <summary>
/// Initializer for an <see cref="IEnumertorVTable"/>.
/// </summary>
/// <param name="destructor">
/// A <see cref="DestructorFunc"/> that is called when the object needs to be destroyed, or <see cref="null"/> if the
/// object should not automatically be destroyed.
/// </param>
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
/// A function that returns the current element for a given <see cref="IEnumerator"/>.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>A pointer to the current element.</returns>
typedef void *(*IEnumerator_GetCurrentFunc)(const IEnumerator *enumerator);

/// <summary>
/// A function that moves a given <see cref="IEnumerator"/> to the next element.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>
/// <see cref="true"/> if the enumerator was successfully advanced to the next element;
/// <see cref="false"/> if the enumerator passed the end of the collection.
/// </returns>
typedef bool(*IEnumerator_MoveNextFunc)(IEnumerator *enumerator);

/// <summary>
/// A function that resets a given <see cref="IEnumerator"/> to its initial position, which is before the first
/// element in the collection.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
typedef void(*IEnumerator_ResetFunc)(IEnumerator *enumerator);

/// <summary>
/// A virtual method table for the <see cref="IEnumerator"/> class.
/// </summary>
typedef struct IEnumeratorVTable {
    /// <summary>
    /// The base class of <see cref="IEnumeratorVTable"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that returns the current element for a given <see cref="IEnumerator"/>.
    /// </summary>
    IEnumerator_GetCurrentFunc GetCurrent;

    /// <summary>
    /// A function that moves a given <see cref="IEnumerator"/> to the next element.
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
/// Initializes the given <see cref="IEnumerator"/>.
/// </summary>
/// <param name="enumerator">Pointer to an uninitialized <see cref="IEnumerator"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
void IEnumerator_Constructor(
    IEnumerator *enumerator,
    const IEnumeratorVTable *vtable);

/// <summary>
/// Returns the current element for the given <see cref="IEnumerator"/>.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>A pointer to the current element.</returns>
void *IEnumerator_GetCurrent(const IEnumerator *enumerator);

/// <summary>
/// Moves the given <see cref="IEnumerator"/> to the next element.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>
/// <see cref="true"/> if the enumerator was successfully advanced to the next element;
/// <see cref="false"/> if the enumerator passed the end of the collection.
/// </returns>
bool IEnumerator_MoveNext(IEnumerator *enumerator);

/// <summary>
/// Resets the given <see cref="IEnumerator"/> to its initial position, which is before the first element in the
/// collection.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
void IEnumerator_Reset(IEnumerator *enumerator);

#endif
