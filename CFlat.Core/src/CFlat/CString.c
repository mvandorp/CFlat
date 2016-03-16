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
#include "CFlat/String.h"
#include "CFlat/Validate.h"

/**************************************/
/* Private functions                  */
/**************************************/

private void ValidateStartIndex(const char *str, uintsize startIndex);
private void ValidatePositionIsWithinString(const char *str);

/**************************************/
/* Public function definitions        */
/**************************************/

public uintsize CString_Length(const char *str)
{
    return CString_IndexOf(str, '\0');
}

public char *CString_Copy(const char *str)
{
    Validate_NotNull(str);

    // Add one to the length to account for the terminating null character.
    uintsize length = CString_Length(str) + 1;

    char *copy = Memory_Allocate(length);

    Memory_Copy(str, copy, length);

    return copy;
}

public bool CString_Contains(const char *str, char value)
{
    return CString_IndexOf(str, value) != InvalidIndex;
}

public bool CString_ContainsCString(const char *str, const char *value)
{
    return CString_IndexOfCString(str, value) != InvalidIndex;
}

public bool CString_ContainsString(const char *str, const String *value)
{
    return CString_IndexOfString(str, value) != InvalidIndex;
}

public bool CString_Equals(const char *str1, const char *str2)
{
    if (str1 == str2) {
        return true;
    }
    else if (str1 == null || str2 == null) {
        return false;
    }

    // Iterate through all of the string's characters, or until we find two inequal characters.
    for (; *str1; str1++, str2++) {
        if (*str1 != *str2) {
            return false;
        }
    }

    // We reached the end of the string. If we also reached the end of the second string, the strings compare equal.
    return *str1 == *str2;
}

public uintsize CString_IndexOf(const char *str, char value)
{
    return CString_IndexOf_Offset(str, value, 0);
}

public uintsize CString_IndexOf_Offset(const char *str, char value, uintsize startIndex)
{
    Validate_NotNull(str);
    ValidateStartIndex(str, startIndex);

    // Iterate through the remaining characters.
    for (uintsize i = startIndex; true; i++, str++) {
        if (*str == value) {
            return i;
        }

        // Check for the null character after the comparison to allow searching for the terminating null character.
        if (*str == '\0') {
            break;
        }
    }

    // The character was not found.
    return InvalidIndex;
}

public uintsize CString_IndexOf_Substring(const char *str, char value, uintsize startIndex, uintsize count)
{
    Validate_NotNull(str);
    ValidateStartIndex(str, startIndex);

    uintsize end = startIndex + count;

    // Iterate through the next given number of characters.
    for (uintsize i = startIndex; i < end; i++, str++) {
        if (*str == value) {
            return i;
        }

        // Validate the position after the comparison to allow searching for the terminating null character.
        ValidatePositionIsWithinString(str);
    }

    // The character was not found.
    return InvalidIndex;
}

public uintsize CString_IndexOfAny(const char *str, const char *anyOf)
{
    return CString_IndexOfAny_Offset(str, anyOf, 0);
}

public uintsize CString_IndexOfAny_Offset(const char *str, const char *anyOf, uintsize startIndex)
{
    Validate_NotNull(str);
    Validate_NotNull(anyOf);
    ValidateStartIndex(str, startIndex);

    // Iterate through the remaining characters.
    for (uintsize i = startIndex; *str; i++, str++) {
        if (CString_Contains(anyOf, *str)) {
            return i;
        }
    }

    // None of the characters were not found.
    return InvalidIndex;
}

public uintsize CString_IndexOfAny_Substring(const char *str, const char *anyOf, uintsize startIndex, uintsize count)
{
    Validate_NotNull(str);
    Validate_NotNull(anyOf);
    ValidateStartIndex(str, startIndex);

    uintsize end = startIndex + count;

    // Iterate through the next given number of characters.
    for (uintsize i = startIndex; i < end; i++, str++) {
        ValidatePositionIsWithinString(str);

        if (CString_Contains(anyOf, *str)) {
            return i;
        }
    }

    // None of the characters were not found.
    return InvalidIndex;
}

public uintsize CString_IndexOfCString(const char *str, const char *value)
{
    return CString_IndexOfCString_Offset(str, value, 0);
}

public uintsize CString_IndexOfCString_Offset(const char *str, const char *value, uintsize startIndex)
{
    Validate_NotNull(str);
    Validate_NotNull(value);
    ValidateStartIndex(str, startIndex);

    // If we are searching for an empty string, report it at the starting index.
    if (*value == '\0') {
        return startIndex;
    }

    // Iterate through the remaining characters.
    for (uintsize i = startIndex; *str; i++, str++) {
        if (CString_StartsWithCString(str, value)) {
            return i;
        }
    }

    // The string was not found.
    return InvalidIndex;
}

public uintsize CString_IndexOfCString_Substring(
    const char *str,
    const char *value,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);
    Validate_NotNull(value);
    ValidateStartIndex(str, startIndex);

    // If we are searching for an empty string, report it at the starting index.
    if (*value == '\0') {
        return startIndex;
    }

    uintsize end = startIndex + count;

    // Iterate through the next given number of characters.
    for (uintsize i = startIndex; i < end; i++, str++) {
        ValidatePositionIsWithinString(str);

        if (CString_StartsWithCString(str, value)) {
            return i;
        }
    }

    // The string was not found.
    return InvalidIndex;
}

public uintsize CString_IndexOfString(const char *str, const String *value)
{
    return CString_IndexOfCString(str, String_GetCString(value));
}

public uintsize CString_IndexOfString_Offset(const char *str, const String *value, uintsize startIndex)
{
    return CString_IndexOfCString_Offset(str, String_GetCString(value), startIndex);
}

public uintsize CString_IndexOfString_Substring(
    const char *str,
    const String *value,
    uintsize startIndex,
    uintsize count)
{
    return CString_IndexOfCString_Substring(str, String_GetCString(value), startIndex, count);
}

public uintsize CString_LastIndexOf(const char *str, char value)
{
    Validate_NotNull(str);

    uintsize lastIndex = InvalidIndex;

    // Iterate through all characters.
    for (uintsize i = 0; true; i++, str++) {
        // If we find the search value, remember the index.
        if (*str == value) {
            lastIndex = i;
        }

        // Check for the null character after the comparison to allow searching for the terminating null character.
        if (*str == '\0') {
            break;
        }
    }

    // Return the index of the last character that was found.
    return lastIndex;
}

public uintsize CString_LastIndexOf_Offset(const char *str, char value, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOf_Offset(strWrapper, value, startIndex);
}

public uintsize CString_LastIndexOf_Substring(const char *str, char value, uintsize startIndex, uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOf_Substring(strWrapper, value, startIndex, count);
}

public uintsize CString_LastIndexOfAny(const char *str, const char *anyOf)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfAny(strWrapper, anyOf);
}

public uintsize CString_LastIndexOfAny_Offset(const char *str, const char *anyOf, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfAny_Offset(strWrapper, anyOf, startIndex);
}

public uintsize CString_LastIndexOfAny_Substring(
    const char *str,
    const char *anyOf,
    uintsize startIndex,
    uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfAny_Substring(strWrapper, anyOf, startIndex, count);
}

public uintsize CString_LastIndexOfCString(const char *str, const char *value)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfCString(strWrapper, value);
}

public uintsize CString_LastIndexOfCString_Offset(const char *str, const char *value, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfCString_Offset(strWrapper, value, startIndex);
}

public uintsize CString_LastIndexOfCString_Substring(
    const char *str,
    const char *value,
    uintsize startIndex,
    uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfCString_Substring(strWrapper, value, startIndex, count);
}

public uintsize CString_LastIndexOfString(const char *str, const String *value)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfString(strWrapper, value);
}

public uintsize CString_LastIndexOfString_Offset(const char *str, const String *value, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfString_Offset(strWrapper, value, startIndex);
}

public uintsize CString_LastIndexOfString_Substring(
    const char *str,
    const String *value,
    uintsize startIndex,
    uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfString_Substring(strWrapper, value, startIndex, count);
}

public bool CString_StartsWithCString(const char *str, const char *value)
{
    Validate_NotNull(str);
    Validate_NotNull(value);

    // Iterate through all of the search string's characters, or until we find two inequal characters.
    for (; *value; str++, value++) {
        if (*str != *value) {
            return false;
        }
    }

    // Reached the end of the search string, all the characters must've matched.
    return true;
}

public bool CString_StartsWithString(const char *str, const String *value)
{
    return CString_StartsWithCString(str, String_GetCString(value));
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void ValidateStartIndex(const char *str, uintsize startIndex)
{
    assert(str != null);

    // Move to the start index.
    for (uintsize i = 0; i < startIndex; i++, str++) {
        if (*str == 0) {
            // The end of the string was reached before the given start index, throw an exception.
            throw_new(
                ArgumentOutOfRangeException,
                "Index was out of range. Must be less than the length of the string.");
        }
    }
}

private void ValidatePositionIsWithinString(const char *str)
{
    assert(str != null);

    if (*str == '\0') {
        // The end of the string was reached before we checked the given number of characters, throw an exception.
        throw_new(ArgumentOutOfRangeException,
            "Count must be positive and count must refer to a location within the string.");
    }
}
