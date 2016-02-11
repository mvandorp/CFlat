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
    if (str1 == str2) {
        return true;
    }
    else if (str1 == null || str2 == null) {
        return false;
    }

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

uintsize CString_IndexOf(const char *str, char value)
{
    Validate_NotNull(str);

    uintsize index = 0;

    // Iterate through all characters.
    while (*str) {
        // If we find the search value, return the index.
        if (*str == value) {
            return index;
        }

        // Move to the next character.
        str++;
        index++;
    }

    return InvalidIndex;
}

uintsize CString_IndexOf_Offset(const char *str, char value, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOf_Offset(strWrapper, value, startIndex);
}

uintsize CString_IndexOf_Substring(const char *str, char value, uintsize startIndex, uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOf_Substring(strWrapper, value, startIndex, count);
}

uintsize CString_IndexOfAny(const char *str, const char *anyOf)
{
    Validate_NotNull(str);
    Validate_NotNull(anyOf);

    uintsize index = 0;

    // Iterate through all characters.
    while (*str) {
        // If we find the search value, return the index.
        if (CString_IndexOf(anyOf, *str) != InvalidIndex) {
            return index;
        }

        // Move to the next character.
        str++;
        index++;
    }

    return InvalidIndex;
}

uintsize CString_IndexOfAny_Offset(const char *str, const char *anyOf, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOfAny_Offset(strWrapper, anyOf, startIndex);
}

uintsize CString_IndexOfAny_Substring(const char *str, const char *anyOf, uintsize startIndex, uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOfAny_Substring(strWrapper, anyOf, startIndex, count);
}

uintsize CString_IndexOfCString(const char *str, const char *value)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOfCString(strWrapper, value);
}

uintsize CString_IndexOfCString_Offset(const char *str, const char *value, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOfCString_Offset(strWrapper, value, startIndex);
}

uintsize CString_IndexOfCString_Substring(const char *str, const char *value, uintsize startIndex, uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOfCString_Substring(strWrapper, value, startIndex, count);
}

uintsize CString_IndexOfString(const char *str, const String *value)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOfString(strWrapper, value);
}

uintsize CString_IndexOfString_Offset(const char *str, const String *value, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOfString_Offset(strWrapper, value, startIndex);
}

uintsize CString_IndexOfString_Substring(const char *str, const String *value, uintsize startIndex, uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_IndexOfString_Substring(strWrapper, value, startIndex, count);
}

uintsize CString_LastIndexOf(const char *str, char value)
{
    Validate_NotNull(str);

    uintsize index = 0;
    uintsize lastIndex = InvalidIndex;

    // Iterate through all characters.
    while (*str) {
        // If we find the search value, remember the index.
        if (*str == value) {
            lastIndex = index;
        }

        // Move to the next character.
        str++;
        index++;
    }

    return lastIndex;
}

uintsize CString_LastIndexOf_Offset(const char *str, char value, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOf_Offset(strWrapper, value, startIndex);
}

uintsize CString_LastIndexOf_Substring(const char *str, char value, uintsize startIndex, uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOf_Substring(strWrapper, value, startIndex, count);
}

uintsize CString_LastIndexOfAny(const char *str, const char *anyOf)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfAny(strWrapper, anyOf);
}

uintsize CString_LastIndexOfAny_Offset(const char *str, const char *anyOf, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfAny_Offset(strWrapper, anyOf, startIndex);
}

uintsize CString_LastIndexOfAny_Substring(const char *str, const char *anyOf, uintsize startIndex, uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfAny_Substring(strWrapper, anyOf, startIndex, count);
}

uintsize CString_LastIndexOfCString(const char *str, const char *value)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfCString(strWrapper, value);
}

uintsize CString_LastIndexOfCString_Offset(const char *str, const char *value, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfCString_Offset(strWrapper, value, startIndex);
}

uintsize CString_LastIndexOfCString_Substring(const char *str, const char *value, uintsize startIndex, uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfCString_Substring(strWrapper, value, startIndex, count);
}

uintsize CString_LastIndexOfString(const char *str, const String *value)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfString(strWrapper, value);
}

uintsize CString_LastIndexOfString_Offset(const char *str, const String *value, uintsize startIndex)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfString_Offset(strWrapper, value, startIndex);
}

uintsize CString_LastIndexOfString_Substring(const char *str, const String *value, uintsize startIndex, uintsize count)
{
    String strBuffer;
    String *strWrapper = String_WrapCString(str, &strBuffer);

    return String_LastIndexOfString_Substring(strWrapper, value, startIndex, count);
}
