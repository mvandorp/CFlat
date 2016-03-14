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

#ifndef CFLAT_CORE_COLLECTIONS_LISTENUMERATOR_H
#define CFLAT_CORE_COLLECTIONS_LISTENUMERATOR_H

#include "CFlat/Language/Keywords.h"

/* Forward declarations */
typedef struct List List;
typedef struct IEnumerator IEnumerator;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="IEnumerator"/> that can iterate over the given <see cref="List"/>.
///
/// The lifetime of the <see cref="IEnumerator"/> should be managed with Object_Aquire() and Object_Release().
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="IEnumerator"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal IEnumerator *ListEnumerator_New(const List *list);

#endif
