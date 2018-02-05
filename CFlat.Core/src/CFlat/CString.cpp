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

using namespace CFlat;

/* Public constants */
/// <summary>
/// Represents an empty string.
/// </summary>
const char * const CString::Empty = "";

/**************************************/
/* Private functions                  */
/**************************************/

static void ValidateStartIndex(const char *str, uintsize startIndex);

/**************************************/
/* Public function definitions        */
/**************************************/

uintsize CString::Length(const char *str)
{
    Validate_NotNull(str);

    uintsize length = 0;

    while (*str) {
        length++;
        str++;
    }

    return length;
}

int CString::Compare(const char *str1, const char *str2)
{
    return CString::Compare(str1, str2, false);
}

int CString::Compare(const char *str1, const char *str2, bool ignoreCase)
{
    if (str1 == str2) return 0;
    if (str1 == nullptr) return -1;
    if (str2 == nullptr) return 1;

    return CString::Compare(
        str1, 0,
        str2, 0,
        UIntSize::Max(CString::Length(str1), CString::Length(str2)),
        ignoreCase);
}

int CString::Compare(
    const char *str1, uintsize startIndex1,
    const char *str2, uintsize startIndex2,
    uintsize length)
{
    return CString::Compare(str1, startIndex1, str2, startIndex2, length, false);
}

int CString::Compare(
    const char *str1, uintsize startIndex1,
    const char *str2, uintsize startIndex2,
    uintsize length,
    bool ignoreCase)
{
    Validate_Argument(length == 0 || str1 != nullptr, "String cannot be null if length is greater than zero.", "str1");
    Validate_Argument(length == 0 || str2 != nullptr, "String cannot be null if length is greater than zero.", "str2");
    Validate_ArgumentRange(str1 == nullptr || startIndex1 <= CString::Length(str1),
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex1");
    Validate_ArgumentRange(str2 == nullptr || startIndex2 <= CString::Length(str2),
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex2");

    if (length == 0) return 0;

    const char *cstr1 = str1;
    const char *cstr2 = str2;

    for (uintsize i = 0; i < length; i++) {
        int c1 = ignoreCase ? Char::ToLower(cstr1[i]) : cstr1[i];
        int c2 = ignoreCase ? Char::ToLower(cstr2[i]) : cstr2[i];
        int diff = c1 - c2;

        if (diff) return diff;

        if (c1 == '\0') break;
    }

    return 0;
}

bool CString::Contains(const char *str, char value)
{
    return CString::IndexOf(str, value) != InvalidIndex;
}

bool CString::Contains(const char *str, const char *value)
{
    return CString::IndexOf(str, value) != InvalidIndex;
}

bool CString::Contains(const char *str, const String &value)
{
    return CString::IndexOf(str, value) != InvalidIndex;
}

unique_ptr<char[]> CString::Copy(const char *str)
{
    Validate_NotNull(str);

    // Add one to the length to account for the terminating null character.
    uintsize length = UIntSize::CheckedAddition(CString::Length(str), 1);

    unique_ptr<char[]> copy = unique_ptr<char[]>(new char[length]);

    Memory::Copy(str, copy.Get(), length);

    return copy;
}

void CString::CopyTo(
    const char *source,
    uintsize sourceIndex,
    char *destination,
    uintsize destinationIndex,
    uintsize count)
{
    Validate_NotNull(source);
    Validate_NotNull(destination);

    uintsize sourceLength = CString::Length(source);

    Validate_ArgumentRange(sourceIndex <= sourceLength,
        "Index cannot be greater than the the size of the string/array/collection.", "sourceIndex");
    Validate_ArgumentRange(count <= sourceLength - sourceIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    Memory::Copy(&source[sourceIndex], &destination[destinationIndex], count);
}

bool CString::EndsWith(const char *str, char value)
{
    Validate_NotNull(str);

    uintsize length = CString::Length(str);

    return length > 0 && str[length - 1] == value;
}

bool CString::EndsWith(const char *str, const char *value)
{
    return CString::EndsWith(str, value, false);
}

bool CString::EndsWith(const char *str, const char *value, bool ignoreCase)
{
    Validate_NotNull(value);

    return CString::EndsWith(str, String::Wrap(value), ignoreCase);
}

bool CString::EndsWith(const char *str, const String &value)
{
    return CString::EndsWith(str, value, false);
}

bool CString::EndsWith(const char *str, const String &value, bool ignoreCase)
{
    Validate_NotNull(str);

    if (value.GetLength() == 0) return true;
    if (value.GetLength() > CString::Length(str)) return false;

    // Indices are within bounds because of the early-out above.
    const char *cstr1 = &str[CString::Length(str) - 1];
    const char *cstr2 = &value.GetCString()[value.GetLength() - 1];

    // Iterate through all of the search string's characters, or until we find two inequal characters.
    for (uintsize length = value.GetLength(); length-- > 0; cstr1--, cstr2--) {
        if ((!ignoreCase && *cstr1 != *cstr2) || (ignoreCase && Char::ToLower(*cstr1) != Char::ToLower(*cstr2))) {
            return false;
        }
    }

    // Reached the end of the search string, all the characters must've matched.
    return true;
}

bool CString::Equals(const char *str1, const char *str2)
{
    return CString::Equals(str1, str2, false);
}

bool CString::Equals(const char *str1, const char *str2, bool ignoreCase)
{
    if (str1 == str2) {
        return true;
    }
    else if (str1 == nullptr || str2 == nullptr) {
        return false;
    }

    // Iterate through all of the string's characters, or until we find two inequal characters.
    for (; *str1; str1++, str2++) {
        if ((!ignoreCase && *str1 != *str2) || (ignoreCase && Char::ToLower(*str1) != Char::ToLower(*str2))) {
            return false;
        }
    }

    // We reached the end of the string. If we also reached the end of the second string, the strings compare equal.
    return *str1 == *str2;
}

int CString::GetHashCode(const char *str)
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

uintsize CString::IndexOf(const char *str, char value)
{
    return CString::IndexOf(str, value, 0);
}

uintsize CString::IndexOf(const char *str, char value, uintsize startIndex)
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

uintsize CString::IndexOf(const char *str, char value, uintsize startIndex, uintsize count)
{
    uintsize length = CString::Length(str);

    Validate_ArgumentRange(startIndex <= length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize end = startIndex + count;

    // Iterate through the next given number of characters.
    for (uintsize i = startIndex; i < end; i++, str++) {
        if (*str == value) {
            return i;
        }
    }

    // The character was not found.
    return InvalidIndex;
}

uintsize CString::IndexOf(const char *str, const char *value)
{
    return CString::IndexOf(str, value, 0);
}

uintsize CString::IndexOf(const char *str, const char *value, uintsize startIndex)
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
        if (CString::StartsWith(str, value)) {
            return i;
        }
    }

    // The string was not found.
    return InvalidIndex;
}

uintsize CString::IndexOf(
    const char *str,
    const char *value,
    uintsize startIndex,
    uintsize count)
{
    uintsize length = CString::Length(str);

    Validate_NotNull(value);
    Validate_ArgumentRange(startIndex <= length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    // If we are searching for an empty string, report it at the starting index.
    if (*value == '\0') {
        return startIndex;
    }

    uintsize end = startIndex + count;

    // Iterate through the next given number of characters.
    for (uintsize i = startIndex; i < end; i++, str++) {
        if (CString::StartsWith(str, value)) {
            return i;
        }
    }

    // The string was not found.
    return InvalidIndex;
}

uintsize CString::IndexOf(const char *str, const String &value)
{
    return CString::IndexOf(str, value.GetCString());
}

uintsize CString::IndexOf(const char *str, const String &value, uintsize startIndex)
{
    return CString::IndexOf(str, value.GetCString(), startIndex);
}

uintsize CString::IndexOf(
    const char *str,
    const String &value,
    uintsize startIndex,
    uintsize count)
{
    return CString::IndexOf(str, value.GetCString(), startIndex, count);
}

uintsize CString::IndexOfAny(const char *str, const char *anyOf)
{
    return CString::IndexOfAny(str, anyOf, 0);
}

uintsize CString::IndexOfAny(const char *str, const char *anyOf, uintsize startIndex)
{
    Validate_NotNull(str);
    Validate_NotNull(anyOf);
    ValidateStartIndex(str, startIndex);

    // Iterate through the remaining characters.
    for (uintsize i = startIndex; *str; i++, str++) {
        if (CString::Contains(anyOf, *str)) {
            return i;
        }
    }

    // None of the characters were not found.
    return InvalidIndex;
}

uintsize CString::IndexOfAny(const char *str, const char *anyOf, uintsize startIndex, uintsize count)
{
    uintsize length = CString::Length(str);

    Validate_NotNull(anyOf);
    Validate_ArgumentRange(startIndex <= length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize end = startIndex + count;

    // Iterate through the next given number of characters.
    for (uintsize i = startIndex; i < end; i++, str++) {
        if (CString::Contains(anyOf, *str)) {
            return i;
        }
    }

    // None of the characters were not found.
    return InvalidIndex;
}

bool CString::IsNullOrEmpty(const char *str)
{
    return str == nullptr || str[0] == '\0';
}

bool CString::IsNullOrWhiteSpace(const char *str)
{
    if (str == nullptr) return true;

    char c;
    while ((c = *str++) != '\0') {
        if (!Char::IsWhiteSpace(c)) return false;
    }

    return true;
}

uintsize CString::LastIndexOf(const char *str, char value)
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

uintsize CString::LastIndexOf(const char *str, char value, uintsize startIndex)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOf(value, startIndex);
}

uintsize CString::LastIndexOf(const char *str, char value, uintsize startIndex, uintsize count)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOf(value, startIndex, count);
}

uintsize CString::LastIndexOf(const char *str, const char *value)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOf(value);
}

uintsize CString::LastIndexOf(const char *str, const char *value, uintsize startIndex)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOf(value, startIndex);
}

uintsize CString::LastIndexOf(
    const char *str,
    const char *value,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOf(value, startIndex, count);
}

uintsize CString::LastIndexOf(const char *str, const String &value)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOf(value);
}

uintsize CString::LastIndexOf(const char *str, const String &value, uintsize startIndex)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOf(value, startIndex);
}

uintsize CString::LastIndexOf(
    const char *str,
    const String &value,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOf(value, startIndex, count);
}

uintsize CString::LastIndexOfAny(const char *str, const char *anyOf)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOfAny(anyOf);
}

uintsize CString::LastIndexOfAny(const char *str, const char *anyOf, uintsize startIndex)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOfAny(anyOf, startIndex);
}

uintsize CString::LastIndexOfAny(
    const char *str,
    const char *anyOf,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);

    return String::Wrap(str).LastIndexOfAny(anyOf, startIndex, count);
}

unique_ptr<char[]> CString::Remove(const char *str, uintsize startIndex)
{
    return CString::CSubstring(str, 0, startIndex);
}

unique_ptr<char[]> CString::Remove(const char *str, uintsize startIndex, uintsize count)
{
    uintsize length = CString::Length(str);

    Validate_ArgumentRange(startIndex <= length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize endIndex = startIndex + count;

    StringBuilder sb = StringBuilder(length - count);
    sb.Append(str, 0, startIndex);
    sb.Append(str, endIndex, length - endIndex);

    return StringBuilder::ToCString(sb);
}

unique_ptr<char[]> CString::Replace(const char *str, char oldValue, char newValue)
{
    Validate_NotNull(str);

    StringBuilder sb = StringBuilder(str);
    sb.Replace(oldValue, newValue);

    return StringBuilder::ToCString(sb);
}

unique_ptr<char[]> CString::Replace(const char *str, const char *oldValue, const char *newValue)
{
    Validate_NotNull(str);

    StringBuilder sb = StringBuilder(str);
    sb.Replace(oldValue, newValue);

    return StringBuilder::ToCString(sb);
}

unique_ptr<char[]> CString::Replace(const char *str, const String &oldValue, const String &newValue)
{
    Validate_NotNull(str);

    StringBuilder sb = StringBuilder(str);
    sb.Replace(oldValue, newValue);

    return StringBuilder::ToCString(sb);
}

bool CString::StartsWith(const char *str, char value)
{
    Validate_NotNull(str);

    return *str == value;
}

bool CString::StartsWith(const char *str, const char *value)
{
    return CString::StartsWith(str, value, false);
}

bool CString::StartsWith(const char *str, const char *value, bool ignoreCase)
{
    Validate_NotNull(str);
    Validate_NotNull(value);

    // Iterate through all of the search string's characters, or until we find two inequal characters.
    for (; *value; str++, value++) {
        if ((!ignoreCase && *str != *value) || (ignoreCase && Char::ToLower(*str) != Char::ToLower(*value))) {
            return false;
        }
    }

    // Reached the end of the search string, all the characters must've matched.
    return true;
}

bool CString::StartsWith(const char *str, const String &value)
{
    return CString::StartsWith(str, value.GetCString());
}

bool CString::StartsWith(const char *str, const String &value, bool ignoreCase)
{
    return CString::StartsWith(str, value.GetCString(), ignoreCase);
}

unique_ptr<char[]> CString::CSubstring(const char *str, uintsize startIndex)
{
    Validate_NotNull(str);
    ValidateStartIndex(str, startIndex);

    return CString::Copy(&str[startIndex]);
}

unique_ptr<char[]> CString::CSubstring(const char *str, uintsize startIndex, uintsize length)
{
    uintsize strLength = CString::Length(str);

    Validate_ArgumentRange(startIndex <= strLength,
        "Index was out of range. Must be less than the length of the string.", "startIndex");
    Validate_ArgumentRange(length <= strLength - startIndex,
        "Index and count must refer to a location within the string.", "count");

    // Add one to the length to account for the terminating null character.
    unique_ptr<char[]> substring = unique_ptr<char[]>(new char[UIntSize::CheckedAddition(length, 1)]);

    // Ensure that the string has a terminating null character.
    substring[length] = '\0';

    Memory::Copy(&str[startIndex], substring.Get(), length);

    return substring;
}

String CString::Substring(const char *str, uintsize startIndex)
{
    Validate_NotNull(str);
    ValidateStartIndex(str, startIndex);

    return String(&str[startIndex]);
}

String CString::Substring(const char *str, uintsize startIndex, uintsize length)
{
    uintsize strLength = CString::Length(str);

    Validate_ArgumentRange(startIndex <= strLength,
        "Index was out of range. Must be less than the length of the string.", "startIndex");
    Validate_ArgumentRange(length <= strLength - startIndex,
        "Index and count must refer to a location within the string.", "count");

    return String(str, startIndex, length);
}

String CString::ToString(const char *str)
{
    Validate_NotNull(str);

    return String(str);
}

/**************************************/
/* Private function definitions       */
/**************************************/

void ValidateStartIndex(const char *str, uintsize startIndex)
{
    assert(str != nullptr);

    // Move to the start index.
    for (uintsize i = 0; i < startIndex; i++, str++) {
        // Throws when the end of the string was reached before the given start index.
        Validate_ArgumentRange(*str != 0,
            "Index was out of range. Must be less than the length of the string.", "startIndex");
    }
}
