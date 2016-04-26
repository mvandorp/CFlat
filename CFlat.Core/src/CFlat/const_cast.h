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

#ifndef CFLAT_CORE_CONST_CAST_H
#define CFLAT_CORE_CONST_CAST_H

#include "CFlat/Language/Keywords.h"

/* Functions */
/// <summary>
/// Casts away the const qualifier of the given pointer.
/// </summary>
/// <param name="ptr">A constant pointer.</param>
/// <returns><paramref name="ptr"/> without the const qualifier.</returns>
internal void *const_cast(const void *ptr);

#endif
