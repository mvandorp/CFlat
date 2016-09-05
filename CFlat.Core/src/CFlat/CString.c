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
#include "CFlat/StringBuilder.h"
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
    Validate_NotNull(str);

    uintsize length = 0;

    while (*str) {
        length++;
        str++;
    }

    return length;
}

public int CString_Compare(const char *str1, const char *str2)
{
    return CString_Compare_IgnoreCase(str1, str2, false);
}

public int CString_Compare_IgnoreCase(const char *str1, const char *str2, bool ignoreCase)
{
    if (str1 == str2) return 0;
    if (str1 == null) return -1;
    if (str2 == null) return 1;

    return CString_CompareSubstrings_IgnoreCase(
        str1, 0,
        str2, 0,
        uintsize_Max(CString_Length(str1), CString_Length(str2)),
        ignoreCase);
}

public int CString_CompareSubstrings(
    const char *str1, uintsize startIndex1,
    const char *str2, uintsize startIndex2,
    uintsize length)
{
    return CString_CompareSubstrings_IgnoreCase(str1, startIndex1, str2, startIndex2, length, false);
}

public int CString_CompareSubstrings_IgnoreCase(
    const char *str1, uintsize startIndex1,
    const char *str2, uintsize startIndex2,
    uintsize length,
    bool ignoreCase)
{
    Validate_Argument(length == 0 || str1 != null, "String cannot be null if length is greater than zero.", "str1");
    Validate_Argument(length == 0 || str2 != null, "String cannot be null if length is greater than zero.", "str2");
    Validate_ArgumentRange(str1 == null || startIndex1 <= CString_Length(str1),
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex1");
    Validate_ArgumentRange(str2 == null || startIndex2 <= CString_Length(str2),
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex2");

    if (length == 0) return 0;

    const char *cstr1 = str1;
    const char *cstr2 = str2;

    for (uintsize i = 0; i < length; i++) {
        int c1 = ignoreCase ? char_ToLower(cstr1[i]) : cstr1[i];
        int c2 = ignoreCase ? char_ToLower(cstr2[i]) : cstr2[i];
        int diff = c1 - c2;

        if (diff) return diff;

        if (c1 == '\0') break;
    }

    return 0;
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

public char *CString_Copy(const char *str)
{
    Validate_NotNull(str);

    // Add one to the length to account for the terminating null character.
    uintsize length = CString_Length(str) + 1;

    char *copy = Memory_Allocate(length);

    Memory_Copy(str, copy, length);

    return copy;
}

public void CString_CopyTo(
    const char *source,
    uintsize sourceIndex,
    char *destination,
    uintsize destinationIndex,
    uintsize count)
{
    Validate_NotNull(source);
    Validate_NotNull(destination);
    Validate_ArgumentRange(sourceIndex <= CString_Length(source),
        "Index cannot be greater than the the size of the string/array/collection.", "sourceIndex");
    Validate_ArgumentRange(sourceIndex + count <= CString_Length(source),
        "Count must refer to a location within the string/array/collection.", "count");

    Memory_Copy(&source[sourceIndex], &destination[destinationIndex], count);
}

public bool CString_EndsWith(const char *str, char value)
{
    Validate_NotNull(str);

    uintsize length = CString_Length(str);

    return length > 0 && str[length - 1] == value;
}

public bool CString_EndsWithCString(const char *str, const char *value)
{
    return CString_EndsWithCString_IgnoreCase(str, value, false);
}

public bool CString_EndsWithCString_IgnoreCase(const char *str, const char *value, bool ignoreCase)
{
    String buffer;

    return CString_EndsWithString_IgnoreCase(str, String_WrapCString(value, &buffer), ignoreCase);
}

public bool CString_EndsWithString(const char *str, const String *value)
{
    return CString_EndsWithString_IgnoreCase(str, value, false);
}

public bool CString_EndsWithString_IgnoreCase(const char *str, const String *value, bool ignoreCase)
{
    Validate_NotNull(str);
    Validate_NotNull(value);

    if (value->Length == 0) return true;
    if (value->Length > CString_Length(str)) return false;

    // Indices are within bounds because of the early-out above.
    const char *cstr1 = &str[CString_Length(str) - 1];
    const char *cstr2 = &value->Value[value->Length - 1];

    // Iterate through all of the search string's characters, or until we find two inequal characters.
    for (uintsize length = value->Length; length-- > 0; cstr1--, cstr2--) {
        if ((!ignoreCase && *cstr1 != *cstr2) || (ignoreCase && char_ToLower(*cstr1) != char_ToLower(*cstr2))) {
            return false;
        }
    }

    // Reached the end of the search string, all the characters must've matched.
    return true;
}

public bool CString_Equals(const char *str1, const char *str2)
{
    return CString_Equals_IgnoreCase(str1, str2, false);
}

public bool CString_Equals_IgnoreCase(const char *str1, const char *str2, bool ignoreCase)
{
    if (str1 == str2) {
        return true;
    }
    else if (str1 == null || str2 == null) {
        return false;
    }

    // Iterate through all of the string's characters, or until we find two inequal characters.
    for (; *str1; str1++, str2++) {
        if ((!ignoreCase && *str1 != *str2) || (ignoreCase && char_ToLower(*str1) != char_ToLower(*str2))) {
            return false;
        }
    }

    // We reached the end of the string. If we also reached the end of the second string, the strings compare equal.
    return *str1 == *str2;
}

public int CString_GetHashCode(const char *str)
{
    Validate_NotNull(str);

    // DJB2 hash
    int hash = 5381;

    char c;
    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) ^ c;
    }

    return hash;
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
    for (uintsize i = startIndex; *str; i++, str++) {
        if (*str == value) {
            return i;
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

public bool CString_IsNullOrEmpty(const char *str)
{
    return str == null || str[0] == '\0';
}

public bool CString_IsNullOrWhiteSpace(const char *str)
{
    if (str == null) return true;

    char c;
    while ((c = *str++) != '\0') {
        if (!char_IsWhiteSpace(c)) return false;
    }

    return true;
}

public uintsize CString_LastIndexOf(const char *str, char value)
{
    Validate_NotNull(str);

    uintsize lastIndex = InvalidIndex;

    // Iterate through all characters.
    for (uintsize i = 0; *str; i++, str++) {
        // If we find the search value, remember the index.
        if (*str == value) {
            lastIndex = i;
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

public char *CString_Remove(const char *str, uintsize startIndex)
{
    return CString_CSubstring_WithLength(str, 0, startIndex);
}

public char *CString_Remove_Substring(const char *str, uintsize startIndex, uintsize count)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= CString_Length(str),
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(startIndex + count <= CString_Length(str),
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize endIndex = startIndex + count;

    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, CString_Length(str) - count);

    StringBuilder_AppendBuffer(&sb, str, 0, startIndex);
    StringBuilder_AppendBuffer(&sb, str, endIndex, CString_Length(str) - endIndex);

    return StringBuilder_DeleteAndToCString(&sb);
}

public char *CString_Replace(const char *str, char oldValue, char newValue)
{
    Validate_NotNull(str);

    StringBuilder sb;
    StringBuilder_Constructor_WithInitialCStringValue(&sb, str);

    StringBuilder_Replace(&sb, oldValue, newValue);

    return StringBuilder_DeleteAndToCString(&sb);
}

public char *CString_ReplaceCString(const char *str, const char *oldValue, const char *newValue)
{
    Validate_NotNull(str);

    StringBuilder sb;
    StringBuilder_Constructor_WithInitialCStringValue(&sb, str);

    try {
        StringBuilder_ReplaceCString(&sb, oldValue, newValue);
    }
    catch (Exception) {
        release(&sb);

        throw;
    }
    endtry;

    return StringBuilder_DeleteAndToCString(&sb);
}

public char *CString_ReplaceString(const char *str, const String *oldValue, const String *newValue)
{
    Validate_NotNull(str);

    StringBuilder sb;
    StringBuilder_Constructor_WithInitialCStringValue(&sb, str);

    try {
        StringBuilder_ReplaceString(&sb, oldValue, newValue);
    }
    catch (Exception) {
        release(&sb);

        throw;
    }
    endtry;

    return StringBuilder_DeleteAndToCString(&sb);
}

public bool CString_StartsWith(const char *str, char value)
{
    Validate_NotNull(str);

    return *str == value;
}

public bool CString_StartsWithCString(const char *str, const char *value)
{
    return CString_StartsWithCString_IgnoreCase(str, value, false);
}

public bool CString_StartsWithCString_IgnoreCase(const char *str, const char *value, bool ignoreCase)
{
    Validate_NotNull(str);
    Validate_NotNull(value);

    // Iterate through all of the search string's characters, or until we find two inequal characters.
    for (; *value; str++, value++) {
        if ((!ignoreCase && *str != *value) || (ignoreCase && char_ToLower(*str) != char_ToLower(*value))) {
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

public bool CString_StartsWithString_IgnoreCase(const char *str, const String *value, bool ignoreCase)
{
    return CString_StartsWithCString_IgnoreCase(str, String_GetCString(value), ignoreCase);
}

public char *CString_CSubstring(const char *str, uintsize startIndex)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= CString_Length(str),
        "Index was out of range. Must be less than the length of the string.", "startIndex");

    return CString_Copy(&str[startIndex]);
}

public char *CString_CSubstring_WithLength(const char *str, uintsize startIndex, uintsize length)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= CString_Length(str),
        "Index was out of range. Must be less than the length of the string.", "startIndex");
    Validate_ArgumentRange(startIndex + length <= CString_Length(str),
        "Index and count must refer to a location within the string.", "count");

    // Add one to the length to account for the terminating null character.
    char *substring = Memory_Allocate(length + 1);

    // Ensure that the string has a terminating null character.
    substring[length] = '\0';

    Memory_Copy(&str[startIndex], substring, length);

    return substring;
}

public String *CString_Substring(const char *str, uintsize startIndex)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= CString_Length(str),
        "Index was out of range. Must be less than the length of the string.", "startIndex");

    return String_New(&str[startIndex]);
}

public String *CString_Substring_WithLength(const char *str, uintsize startIndex, uintsize length)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= CString_Length(str),
        "Index was out of range. Must be less than the length of the string.", "startIndex");
    Validate_ArgumentRange(startIndex + length <= CString_Length(str),
        "Index and count must refer to a location within the string.", "count");

    return String_New_Substring(str, startIndex, length);
}

public String *CString_ToString(const char *str)
{
    Validate_NotNull(str);

    return String_New(str);
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
