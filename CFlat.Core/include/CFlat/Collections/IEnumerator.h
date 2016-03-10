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

/* Types */
/// <summary>
/// A function that returns the current element for a given <see cref="IEnumerator"/>.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>A pointer to the current element.</returns>
typedef void *(*IEnumerator_GetCurrentCallback)(const void *enumerator);

/// <summary>
/// A function that moves a given <see cref="IEnumerator"/> to the next element.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>
///     <see cref="true"/> if the enumerator was successfully advanced to the next element;
///     <see cref="false"/> if the enumerator passed the end of the collection.
/// </returns>
typedef bool(*IEnumerator_MoveNextCallback)(void *enumerator);

/// <summary>
/// A function that resets a given <see cref="IEnumerator"/> to its initial position, which is before the first
/// element in the collection.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
typedef void(*IEnumerator_ResetCallback)(void *enumerator);

/// <summary>
/// Supports a simple iteration over a collection of elements.
/// </summary>
typedef struct IEnumerator {
    /// <summary>
    /// The base class of the <see cref="IEnumerator"/>.
    /// </summary>
    Object Base;

    /// <summary>
    /// A function that returns the current element for a given <see cref="IEnumerator"/>.
    /// </summary>
    IEnumerator_GetCurrentCallback GetCurrent;

    /// <summary>
    /// A function that moves a given <see cref="IEnumerator"/> to the next element.
    /// </summary>
    IEnumerator_MoveNextCallback MoveNext;

    /// <summary>
    /// A function that resets a given <see cref="IEnumerator"/> to its initial position, which is before the first
    /// element in the collection.
    /// </summary>
    IEnumerator_ResetCallback Reset;
} IEnumerator;

/* Functions */
/// <summary>
/// Initializes the given <see cref="IEnumerator"/>.
/// </summary>
/// <param name="enumerator">Pointer to an uninitialized <see cref="IEnumerator"/>.</param>
/// <param name="destructor">
///     Pointer to a <see cref="Destructor"/> to call when the object needs to be destroyed, or <see cref="null"/> if
///     <paramref name="enumerator"/> should not automatically be destroyed.
/// </param>
/// <param name="getCurrent">
///     An <see cref="IEnumerator_GetCurrentCallback"/> that returns the current element for a given
///     <see cref="IEnumerator"/>.
/// </param>
/// <param name="moveNext">
///     An <see cref="IEnumerator_MoveNextCallback"/> that that moves a given <see cref="IEnumerator"/> to the next
///     element.
/// </param>
/// <param name="reset">
///     An <see cref="IEnumerator_ResetCallback"/> that resets a given <see cref="IEnumerator"/> to its initial
///     position, which is before the first element in the collection.
/// </param>
void IEnumerator_Constructor(
    void *enumerator,
    Destructor destructor,
    IEnumerator_GetCurrentCallback getCurrent,
    IEnumerator_MoveNextCallback moveNext,
    IEnumerator_ResetCallback reset);

/// <summary>
/// Returns the current element for the given <see cref="IEnumerator"/>.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>A pointer to the current element.</returns>
void *IEnumerator_GetCurrent(const void *enumerator);

/// <summary>
/// Moves the given <see cref="IEnumerator"/> to the next element.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
/// <returns>
///     <see cref="true"/> if the enumerator was successfully advanced to the next element;
///     <see cref="false"/> if the enumerator passed the end of the collection.
/// </returns>
bool IEnumerator_MoveNext(void *enumerator);

/// <summary>
/// Resets the given <see cref="IEnumerator"/> to its initial position, which is before the first element in the
/// collection.
/// </summary>
/// <param name="enumerator">Pointer to an <see cref="IEnumerator"/>.</param>
void IEnumerator_Reset(void *enumerator);

#endif
