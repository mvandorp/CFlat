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
 * @file CString.h
 */

#ifndef CFLAT_CORE_CSTRING_H
#define CFLAT_CORE_CSTRING_H

#include "CFlat/Language/Integer.h"

/// <summary>
/// Gets the length of a null-terminated string.
///
/// The length does not include the terminating null character.
/// </summary>
/// <param name="str">A null-terminated string.</param>
/// <returns>The length of the string.</returns>
uintsize CString_Length(const char *str);

/// <summary>
/// Returns a pointer to a new null-terminated string that is a copy of the given string.
/// </summary>
/// <param name="str">A null-terminated string.</param>
/// <returns>
/// On success, returns the pointer to the copy of the string.
///
/// On failure, returns <see cref="null"/>.
/// </returns>
char *CString_Copy(const char *str);

#endif
