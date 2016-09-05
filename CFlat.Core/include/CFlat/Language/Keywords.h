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

//! @file Keywords.h

#ifndef CFLAT_CORE_LANGUAGE_KEYWORDS_H
#define CFLAT_CORE_LANGUAGE_KEYWORDS_H

/// <summary>
/// Indicates that a function or variable is public and uses external linkage.
/// </summary>
#define public

/// <summary>
/// Indicates that a function or variable is internal and uses external linkage.
/// </summary>
#define internal

/// <summary>
/// Indicates that a function or variable is private and uses internal linkage.
/// </summary>
#define private static

/// <summary>
/// Indicates that a function is abstract.
/// </summary>
#define abstract

/// <summary>
/// Indicates that a function is virtual.
/// </summary>
#define virtual

/// <summary>
/// Indicates that a function overrides an abstract or virtual base function.
/// </summary>
#define override

#include "CFlat/Language/Bool.h"

/* Object.c */
/// <summary>
/// Increments the reference count of an <see cref="Object"/>.
/// </summary>
/// <remarks>
///     If <paramref name="obj"/> is <see cref="null"/>, the function does nothing.
///
///     The behaviour is undefined if <paramref name="obj"/> has already been deleted as the result of a call to
///     release().
/// </remarks>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <returns><paramref name="obj"/>.</returns>
/// <seealso cref="release()"/>
void *retain(void *obj);

/// <summary>
/// Increments the reference count of an <see cref="Object"/>.
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <returns><paramref name="obj"/>.</returns>
/// <seealso cref="retain()"/>
const void *retain_const(const void *obj);

/// <summary>
/// Decrements the reference count of an <see cref="Object"/>.
/// </summary>
/// <remarks>
///     If <paramref name="obj"/> is <see cref="null"/>, the function does nothing and returns <see cref="false"/>.
///
///     If the reference count reaches zero, the object is deleted by first calling the destructor of the object, and
///     then deallocating the memory reserved for the object.
///
///     The behaviour is undefined if <paramref name="obj"/> has already been deleted as the result of a previous call
///     to release().
/// </remarks>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <returns>
///     <see cref="true"/> if the reference count reached zero and <paramref name="obj"/> was deleted;
///     otherwise, <see cref="false"/>.
/// </returns>
/// <seealso cref="retain()"/>
bool release(const void *obj);

#endif
