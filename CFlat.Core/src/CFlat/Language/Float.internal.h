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

#ifndef CFLAT_CORE_LANGUAGE_FLOAT_INTERNAL_H
#define CFLAT_CORE_LANGUAGE_FLOAT_INTERNAL_H

#ifndef CFLAT_CORE_LANGUAGE_FLOAT_H
 #error Float.internal.h should not be included directly.
#endif

#include "CFlat/Language/Keywords.h"

/* Types */
struct String;
struct StringBuilder;

/* Functions */
/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void float_ToStringBuffered(struct StringBuilder *sb, float value, const struct String *format);

#endif
