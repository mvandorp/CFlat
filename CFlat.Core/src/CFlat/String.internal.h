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

#ifndef CFLAT_CORE_STRING_INTERNAL_H
#define CFLAT_CORE_STRING_INTERNAL_H

#ifndef CFLAT_CORE_STRING_H
 #error String.internal.h should not be included directly.
#endif

/* Forward declarations */
struct String;

/* Functions */
/// <summary>
/// Returns a pointer to a <see cref="String"/> wrapper for given null-terminated string.
/// </summary>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <param name="bufer">
///     Pointer to a buffer capable of storing a <see cref="String"/>, this value cannot be <see cref="null"/>.
/// </param>
/// <returns>
///     A pointer to a <see cref="String"/> wrapper for the given null-terminated string, or <see cref="null"/> if
///     <paramref name="value"/> is <see cref="null"/>.
/// </returns>
internal struct String *String_WrapCString(const char *value, struct String *buffer);

#endif
