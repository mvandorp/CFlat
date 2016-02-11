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
#include "CFlat/Validate.h"

uintsize CString_Length(const char *str)
{
    Validate_NotNull(str);

    const char *start = str;

    // Walk to the end of the string, indicated by a terminating null character.
    while (*str) {
        str++;
    }

    // The length is equal to the difference between the start and end of the string.
    return str - start;
}

char *CString_Copy(const char *str)
{
    Validate_NotNull(str);

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

bool CString_Equals(const char *str1, const char *str2)
{
    assert(str1 != null);
    assert(str2 != null);

    // Walk to the end of the string, indicated by a terminating null character.
    while (*str1) {
        // If a character is not equal to the corresponding character of the second string, the strings are not equal.
        // If the second string is shorter than the first, this check will fail when the terminating null-character of
        // the second string is reached.
        if (*str1 != *str2) {
            return false;
        }

        str1++;
        str2++;
    }

    // We reached the end of the string. If we also reached the end of the second string, the strings compare equal.
    return *str1 == *str2;
}
