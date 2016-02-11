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

#include "CFlat/CString.h"

#include "CFlat.h"
#include "CFlat/Memory.h"

uintsize CString_Length(const char *str)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    const char *start = str;

    // Walk to the end of the string, indicated by a terminating null character.
    while (*str != '\0') {
        str++;
    }

    // The length is equal to the difference between the start and end of the string.
    return str - start;
}

char *CString_Copy(const char *str)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    // Add one to the length to account for the terminating null character.
    uintsize length = CString_Length(str) + 1;

    // Allocate memory for the copy.
    char *start = Memory_Allocate(length);
    char *copy = start;

    // If the allocation failed, return null.
    if (start == null) {
        return null;
    }

    // Copy all bytes in the string, including the terminating null character.
    while (length-- > 0) {
        *copy++ = *str++;
    }

    return start;
}
