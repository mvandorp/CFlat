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

#include "CFlat/String.h"

#include "CFlat.h"
#include "CFlat/const_cast.h"
#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/StringEnumerator.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/IList.h"
#include "CFlat/Collections/ObjectList.h"

/* Private constants */
/// <summary>
/// Represents an empty string.
/// </summary>
private const String Empty = String_Initializer("");

/* Public constants */
/// <summary>
/// Represents an empty string.
/// </summary>
public const String * const String_Empty = &Empty;

/// <summary>
/// The virtual method table for the <see cref="String"/> class.
/// </summary>
public const IEnumerableVTable String_VTable = IEnumerableVTable_Initializer(
    (DestructorFunc)String_Destructor,
    (IEnumerable_GetEnumeratorFunc)String_GetEnumerator);

/// <summary>
/// The virtual method table for the <see cref="String"/> class, without a destructor set so that the internal
/// null-terminated string is not automatically destroyed.
/// </summary>
public const IEnumerableVTable String_VTableNoDestructor = IEnumerableVTable_Initializer(
    null,
    (IEnumerable_GetEnumeratorFunc)String_GetEnumerator);

/**************************************/
/* Private functions                  */
/**************************************/

private String *Trim(const String *str, const char *trimChars, int mode);
private String *TrimWhiteSpace(const String *str, int mode);

/**************************************/
/* Public function definitions        */
/**************************************/

public String *String_New(const char *value)
{
    String *str = Memory_Allocate(sizeof(String));

    try {
        String_Constructor(str, value);

        Object_SetDeallocator(str, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(str);
        throw;
    }
    endtry;

    return str;
}

public String *String_New_Substring(const char *value, uintsize startIndex, uintsize length)
{
    String *str = Memory_Allocate(sizeof(String));

    try {
        String_Constructor_Substring(str, value, startIndex, length);

        Object_SetDeallocator(str, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(str);
        throw;
    }
    endtry;

    return str;
}

public void String_Constructor(String *str, const char *value)
{
    Validate_NotNull(str);

    Object_Constructor(str, (const ObjectVTable*)&String_VTable);

    if (value == null) {
        *(uintsize*)const_cast(&str->Length) = 0;
        *(const char**)const_cast(&str->Value) = CString_Empty;
    }
    else {
        *(uintsize*)const_cast(&str->Length) = CString_Length(value);
        *(const char**)const_cast(&str->Value) = CString_Copy(value);
    }
}

public void String_Constructor_Substring(String *str, const char *value, uintsize startIndex, uintsize length)
{
    Validate_NotNull(str);

    Object_Constructor(str, (const ObjectVTable*)&String_VTable);

    if (length == 0) {
        *(uintsize*)const_cast(&str->Length) = 0;
        *(const char**)const_cast(&str->Value) = CString_Empty;
    }
    else {
        Validate_NotNull(value);

        *(uintsize*)const_cast(&str->Length) = length;
        *(const char**)const_cast(&str->Value) = CString_CSubstring_WithLength(value, startIndex, length);
    }
}

public void String_Destructor(String *str)
{
    Validate_NotNull(str);

    // Prevent freeing the empty string constant.
    if (str == String_Empty || str->Value == CString_Empty)
        return;

    Memory_Deallocate(str->Value);
}

public char String_GetCharAt(const String *str, uintsize index)
{
    Validate_NotNull(str);
    Validate_Argument(index < str->Length,
        "Index must be less than the size of the string/array/collection.", "index");

    return str->Value[index];
}

public const char *String_GetCString(const String *str)
{
    Validate_NotNull(str);

    return str->Value;
}

public uintsize String_GetLength(const String *str)
{
    Validate_NotNull(str);

    return str->Length;
}

public int String_Compare(const String *str1, const String *str2)
{
    return String_Compare_IgnoreCase(str1, str2, false);
}

public int String_Compare_IgnoreCase(const String *str1, const String *str2, bool ignoreCase)
{
    if (str1 == str2) return 0;
    if (str1 == null) return -1;
    if (str2 == null) return 1;

    return String_CompareSubstrings_IgnoreCase(
        str1, 0,
        str2, 0,
        uintsize_Max(str1->Length, str2->Length),
        ignoreCase);
}

public int String_CompareSubstrings(
    const String *str1, uintsize startIndex1,
    const String *str2, uintsize startIndex2,
    uintsize length)
{
    return String_CompareSubstrings_IgnoreCase(str1, startIndex1, str2, startIndex2, length, false);
}

public int String_CompareSubstrings_IgnoreCase(
    const String *str1, uintsize startIndex1,
    const String *str2, uintsize startIndex2,
    uintsize length,
    bool ignoreCase)
{
    Validate_Argument(length == 0 || str1 != null, "String cannot be null if length is greater than zero.", "str1");
    Validate_Argument(length == 0 || str2 != null, "String cannot be null if length is greater than zero.", "str2");
    Validate_ArgumentRange(str1 == null || startIndex1 <= str1->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex1");
    Validate_ArgumentRange(str2 == null || startIndex2 <= str2->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex2");

    if (length == 0) return 0;

    const char *cstr1 = str1->Value;
    const char *cstr2 = str2->Value;

    for (uintsize i = 0; i < length; i++) {
        int c1 = ignoreCase ? char_ToLower(cstr1[i]) : cstr1[i];
        int c2 = ignoreCase ? char_ToLower(cstr2[i]) : cstr2[i];
        int diff = c1 - c2;

        if (diff) return diff;

        if (c1 == '\0') break;
    }

    return 0;
}

public String *String_Concat(const String *str1, const String *str2)
{
    const String *strings[2];
    strings[0] = str1;
    strings[1] = str2;

    return String_ConcatArray(strings, 2);
}

public String *String_Concat3(const String *str1, const String *str2, const String *str3)
{
    const String *strings[3];
    strings[0] = str1;
    strings[1] = str2;
    strings[2] = str3;

    return String_ConcatArray(strings, 3);
}

public String *String_Concat4(const String *str1, const String *str2, const String *str3, const String *str4)
{
    const String *strings[4];
    strings[0] = str1;
    strings[1] = str2;
    strings[2] = str3;
    strings[3] = str4;

    return String_ConcatArray(strings, 4);
}

public String *String_ConcatArray(const String * const *strings, uintsize count)
{
    Validate_NotNull(strings);

    uintsize capacity = 0;

    // Calculate the total length of the resulting string.
    for (uintsize i = 0; i < count; i++) {
        if (strings[i] == null) continue;

        capacity += strings[i]->Length;
    }

    String*result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, capacity);

    try {
        // Concatenate the strings.
        for (uintsize i = 0; i < count; i++) {
            if (strings[i] == null) continue;

            StringBuilder_AppendString(&sb, strings[i]);
        }

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *String_ConcatEnumerable(const IEnumerable *strings)
{
    Validate_NotNull(strings);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor(&sb);

    try {
        IEnumerator *enumerator = IEnumerable_GetEnumerator(strings);

        try {
            while (IEnumerator_MoveNext(enumerator)) {
                StringBuilder_AppendString(&sb, (const String*)IEnumerator_GetCurrent(enumerator));
            }
        }
        finally {
            release(enumerator);
        }
        endtry;

        result = StringBuilder_DeleteAndToString(&sb);;
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public bool String_Contains(const String *str, char value)
{
    return String_IndexOf(str, value) != InvalidIndex;
}

public bool String_ContainsCString(const String *str, const char *value)
{
    return String_IndexOfCString(str, value) != InvalidIndex;
}

public bool String_ContainsString(const String *str, const String *value)
{
    return String_IndexOfString(str, value) != InvalidIndex;
}

public String *String_Copy(const String *str)
{
    Validate_NotNull(str);

    return String_New(String_GetCString(str));
}

public void String_CopyTo(
    const String *source,
    uintsize sourceIndex,
    char *destination,
    uintsize destinationIndex,
    uintsize count)
{
    Validate_NotNull(source);
    Validate_NotNull(destination);
    Validate_ArgumentRange(sourceIndex <= source->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "sourceIndex");
    Validate_ArgumentRange(count <= source->Length - sourceIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    Memory_Copy(&source->Value[sourceIndex], &destination[destinationIndex], count);
}

public bool String_EndsWith(const String *str, char value)
{
    Validate_NotNull(str);

    return str->Length > 0 && str->Value[str->Length - 1] == value;
}

public bool String_EndsWithCString(const String *str, const char *value)
{
    return String_EndsWithCString_IgnoreCase(str, value, false);
}

public bool String_EndsWithCString_IgnoreCase(const String *str, const char *value, bool ignoreCase)
{
    String buffer;

    return String_EndsWithString_IgnoreCase(str, String_WrapCString(value, &buffer), ignoreCase);
}

public bool String_EndsWithString(const String *str, const String *value)
{
    return String_EndsWithString_IgnoreCase(str, value, false);
}

public bool String_EndsWithString_IgnoreCase(const String *str, const String *value, bool ignoreCase)
{
    Validate_NotNull(str);
    Validate_NotNull(value);

    if (value->Length == 0) return true;
    if (value->Length > str->Length) return false;

    // Indices are within bounds because of the early-out above.
    const char *cstr1 = &str->Value[str->Length - 1];
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

public bool String_Equals(const String *str1, const String *str2)
{
    return String_Equals_IgnoreCase(str1, str2, false);
}

public bool String_Equals_IgnoreCase(const String *str1, const String *str2, bool ignoreCase)
{
    return
        str1 == str2 || (
        str1 != null &&
        str2 != null &&
        str1->Length == str2->Length &&
        CString_Equals_IgnoreCase(str1->Value, str2->Value, ignoreCase));
}

public bool String_EqualsCString(const String *str1, const char *str2)
{
    return String_EqualsCString_IgnoreCase(str1, str2, false);
}

public bool String_EqualsCString_IgnoreCase(const String *str1, const char *str2, bool ignoreCase)
{
    return
        (str1 == null && str2 == null) || (
        str1 != null &&
        str2 != null &&
        CString_Equals_IgnoreCase(str1->Value, str2, ignoreCase));
}

public String *String_FormatCString(const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    String *result = String_FormatCStringV(format, args);

    VarArgs_End(args);

    return result;
}

public String *String_FormatCStringV(const char *format, VarArgsList args)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return String_FormatStringV(str, args);
}

public String *String_FormatString(const String *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    String *result = String_FormatStringV(format, args);

    VarArgs_End(args);

    return result;
}

public String *String_FormatStringV(const String *format, VarArgsList args)
{
    Validate_NotNull(format);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor(&sb);

    try {
        StringBuilder_AppendFormatStringV(&sb, format, args);

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public int String_GetHashCode(const String *str)
{
    Validate_NotNull(str);

    return CString_GetHashCode(str->Value);
}

public uintsize String_IndexOf(const String *str, char value)
{
    return String_IndexOf_Substring(str, value, 0, String_GetLength(str));
}

public uintsize String_IndexOf_Offset(const String *str, char value, uintsize startIndex)
{
    return String_IndexOf_Substring(str, value, startIndex, String_GetLength(str) - startIndex);
}

public uintsize String_IndexOf_Substring(const String *str, char value, uintsize startIndex, uintsize count)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= str->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= str->Length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize end = startIndex + count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex; i < end; i++) {
        if (str->Value[i] == value) {
            return i;
        }
    }

    return InvalidIndex;
}

public uintsize String_IndexOfAny(const String *str, const char *anyOf)
{
    return String_IndexOfAny_Substring(str, anyOf, 0, String_GetLength(str));
}

public uintsize String_IndexOfAny_Offset(const String *str, const char *anyOf, uintsize startIndex)
{
    return String_IndexOfAny_Substring(str, anyOf, startIndex, String_GetLength(str) - startIndex);
}

public uintsize String_IndexOfAny_Substring(const String *str, const char *anyOf, uintsize startIndex, uintsize count)
{
    Validate_NotNull(str);
    Validate_NotNull(anyOf);
    Validate_ArgumentRange(startIndex <= str->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= str->Length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize end = startIndex + count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex; i < end; i++) {
        if (CString_IndexOf(anyOf, str->Value[i]) != InvalidIndex) {
            return i;
        }
    }

    return InvalidIndex;
}

public uintsize String_IndexOfCString(const String *str, const char *value)
{
    return String_IndexOfCString_Substring(str, value, 0, String_GetLength(str));
}

public uintsize String_IndexOfCString_Offset(const String *str, const char *value, uintsize startIndex)
{
    return String_IndexOfCString_Substring(str, value, startIndex, String_GetLength(str) - startIndex);
}

public uintsize String_IndexOfCString_Substring(
    const String *str,
    const char *value,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);
    Validate_NotNull(value);
    Validate_ArgumentRange(startIndex <= str->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= str->Length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    // If we are searching for an empty string, report it at the starting index.
    if (*value == '\0') {
        return startIndex;
    }

    uintsize end = startIndex + count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex; i < end; i++) {
        if (CString_StartsWithCString(&str->Value[i], value)) {
            return i;
        }
    }

    return InvalidIndex;
}

public uintsize String_IndexOfString(const String *str, const String *value)
{
    return String_IndexOfCString(str, String_GetCString(value));
}

public uintsize String_IndexOfString_Offset(const String *str, const String *value, uintsize startIndex)
{
    return String_IndexOfCString_Offset(str, String_GetCString(value), startIndex);
}

public uintsize String_IndexOfString_Substring(
    const String *str,
    const String *value,
    uintsize startIndex,
    uintsize count)
{
    return String_IndexOfCString_Substring(str, String_GetCString(value), startIndex, count);
}

public String *String_Insert(const String *str, uintsize startIndex, const String *value)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= str->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");

    if (value == null || value->Length == 0) return const_cast(retain_const(str));

    uintsize capacity = uintsize_CheckedAddition(str->Length, value->Length);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, capacity);

    try {
        StringBuilder_AppendString(&sb, str);
        StringBuilder_InsertString(&sb, startIndex, value);

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public bool String_IsNullOrEmpty(const String *str)
{
    return str == null || str->Length == 0;
}

public bool String_IsNullOrWhiteSpace(const String *str)
{
    if (str == null) return true;

    const char *cstr = str->Value;

    char c;
    while ((c = *cstr++) != '\0') {
        if (!char_IsWhiteSpace(c)) return false;
    }

    return true;
}

public String *String_Join(const String *separator, const String * const *strings, uintsize count)
{
    Validate_NotNull(strings);

    if (count == 0 || (count == 1 && strings[0] == null)) return const_cast(String_Empty);
    if (count == 1) return const_cast(retain_const(strings[0]));

    uintsize capacity = 0;

    // Calculate the total length of the resulting string.
    if (separator != null) {
        capacity = uintsize_CheckedMultiplication(count - 1, separator->Length);
    }

    for (uintsize i = 0; i < count; i++) {
        if (strings[i] == null) continue;

        capacity = uintsize_CheckedAddition(capacity, strings[i]->Length);
    }

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, capacity);

    // Join the strings.
    try {
        for (uintsize i = 0; i < count - 1; i++) {
            if (strings[i] == null) continue;

            StringBuilder_AppendString(&sb, strings[i]);
            StringBuilder_AppendString(&sb, separator);
        }

        StringBuilder_AppendString(&sb, strings[count - 1]);

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *String_JoinEnumerable(const String *separator, const IEnumerable *strings)
{
    Validate_NotNull(strings);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor(&sb);

    try {
        IEnumerator *enumerator = IEnumerable_GetEnumerator(strings);

        try {
            bool first = true;

            while (IEnumerator_MoveNext(enumerator)) {
                if (!first) StringBuilder_AppendString(&sb, separator);

                StringBuilder_AppendString(&sb, (const String*)IEnumerator_GetCurrent(enumerator));

                if (first) first = false;
            }
        }
        finally {
            release(enumerator);
        }
        endtry;

        result = StringBuilder_DeleteAndToString(&sb);;
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public uintsize String_LastIndexOf(const String *str, char value)
{
    return String_LastIndexOf_Substring(str, value, String_GetLength(str) - 1, String_GetLength(str));
}

public uintsize String_LastIndexOf_Offset(const String *str, char value, uintsize startIndex)
{
    return String_LastIndexOf_Substring(str, value, startIndex, uintsize_CheckedAddition(startIndex, 1));
}

public uintsize String_LastIndexOf_Substring(const String *str, char value, uintsize startIndex, uintsize count)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex < str->Length || str->Length == 0,
        "Index must be less than the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(startIndex + 1 >= count || str->Length == 0,
        "Count must refer to a location within the string/array/collection.", "count");

    // If the string is empty, return InvalidIndex.
    if (str->Length == 0) {
        return InvalidIndex;
    }

    uintsize end = startIndex + 1 - count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex + 1; i-- > end; ) {
        if (str->Value[i] == value) {
            return i;
        }
    }

    return InvalidIndex;
}

public uintsize String_LastIndexOfAny(const String *str, const char *anyOf)
{
    Validate_NotNull(str);

    if (str->Length == 0) {
        return InvalidIndex;
    }
    else {
        return String_LastIndexOfAny_Substring(str, anyOf, str->Length - 1, str->Length);
    }
}

public uintsize String_LastIndexOfAny_Offset(const String *str, const char *anyOf, uintsize startIndex)
{
    return String_LastIndexOfAny_Substring(str, anyOf, startIndex, uintsize_CheckedAddition(startIndex, 1));
}

public uintsize String_LastIndexOfAny_Substring(
    const String *str,
    const char *anyOf,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex < str->Length || str->Length == 0,
        "Index must be less than the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(startIndex + 1 >= count || str->Length == 0,
        "Count must refer to a location within the string/array/collection.", "count");

    // If the string is empty, return InvalidIndex.
    if (str->Length == 0) {
        return InvalidIndex;
    }

    uintsize end = startIndex + 1 - count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex + 1; i-- > end; ) {
        if (CString_IndexOf(anyOf, str->Value[i]) != InvalidIndex) {
            return i;
        }
    }

    return InvalidIndex;
}

public uintsize String_LastIndexOfCString(const String *str, const char *value)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_LastIndexOfString(str, valueWrapper);
}

public uintsize String_LastIndexOfCString_Offset(const String *str, const char *value, uintsize startIndex)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_LastIndexOfString_Offset(str, valueWrapper, startIndex);
}

public uintsize String_LastIndexOfCString_Substring(
    const String *str,
    const char *value,
    uintsize startIndex,
    uintsize count)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_LastIndexOfString_Substring(str, valueWrapper, startIndex, count);
}

public uintsize String_LastIndexOfString(const String *str, const String *value)
{
    Validate_NotNull(str);
    Validate_NotNull(value);

    if (str->Length == 0) {
        if (value->Length == 0) {
            return 0;
        }
        else {
            return InvalidIndex;
        }
    }
    else {
        return String_LastIndexOfString_Substring(str, value, str->Length - 1, str->Length);
    }
}

public uintsize String_LastIndexOfString_Offset(const String *str, const String *value, uintsize startIndex)
{
    return String_LastIndexOfString_Substring(str, value, startIndex, uintsize_CheckedAddition(startIndex, 1));
}

public uintsize String_LastIndexOfString_Substring(
    const String *str,
    const String *value,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);
    Validate_NotNull(value);
    Validate_ArgumentRange(startIndex < str->Length || str->Length == 0,
        "Index must be less than the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(startIndex + 1 >= count || str->Length == 0,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize length = value->Length;
    uintsize end = startIndex + 1 - count;

    // If we are searching for an empty string, report it at the starting index.
    if (length == 0) {
        return startIndex;
    }

    // If there aren't enough characters in front of start index, return InvalidIndex.
    if (startIndex + 1 < length) {
        return InvalidIndex;
    }

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex + 1 - length; i-- > end; ) {
        if (CString_StartsWithCString(&str->Value[i], value->Value)) {
            return i;
        }
    }

    return InvalidIndex;
}

public String *String_PadLeft(const String *str, uintsize totalWidth, char paddingChar)
{
    Validate_NotNull(str);

    if (totalWidth <= str->Length) return const_cast(retain_const(str));

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, totalWidth);

    try {
        for (uintsize i = str->Length; i < totalWidth; i++) {
            StringBuilder_Append(&sb, paddingChar);
        }

        StringBuilder_AppendString(&sb, str);

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *String_PadRight(const String *str, uintsize totalWidth, char paddingChar)
{
    Validate_NotNull(str);

    if (totalWidth <= str->Length) return const_cast(retain_const(str));

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, totalWidth);

    try {
        StringBuilder_AppendString(&sb, str);

        for (uintsize i = str->Length; i < totalWidth; i++) {
            StringBuilder_Append(&sb, paddingChar);
        }

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *String_Remove(const String *str, uintsize startIndex)
{
    return String_Substring_WithLength(str, 0, startIndex);
}

public String *String_Remove_Substring(const String *str, uintsize startIndex, uintsize count)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= str->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= str->Length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize endIndex = startIndex + count;

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, str->Length - count);

    try {
        StringBuilder_AppendBuffer(&sb, str->Value, 0, startIndex);
        StringBuilder_AppendBuffer(&sb, str->Value, endIndex, str->Length - endIndex);

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *String_Replace(const String *str, char oldValue, char newValue)
{
    Validate_NotNull(str);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithInitialStringValue(&sb, str);

    try {
        StringBuilder_Replace(&sb, oldValue, newValue);

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *String_ReplaceCString(const String *str, const char *oldValue, const char *newValue)
{
    Validate_NotNull(str);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithInitialStringValue(&sb, str);

    try {
        StringBuilder_ReplaceCString(&sb, oldValue, newValue);

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *String_ReplaceString(const String *str, const String *oldValue, const String *newValue)
{
    Validate_NotNull(str);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithInitialStringValue(&sb, str);

    try {
        StringBuilder_ReplaceString(&sb, oldValue, newValue);

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public IList *String_Split(const String *str, const char *separators)
{
    return String_Split_AtMost_WithOptions(str, separators, int_MaxValue, StringSplitOptions_None);
}

public IList *String_Split_AtMost(const String *str, const char *separators, uintsize count)
{
    return String_Split_AtMost_WithOptions(str, separators, count, StringSplitOptions_None);
}

public IList *String_Split_WithOptions(
    const String *str,
    const char *separators,
    StringSplitOptions options)
{
    return String_Split_AtMost_WithOptions(str, separators, int_MaxValue, options);
}

public IList *String_Split_AtMost_WithOptions(
    const String *str,
    const char *separators,
    uintsize count,
    StringSplitOptions options)
{
    Validate_NotNull(str);
    Validate_NotNull(separators);

    IList *list = (IList*)ObjectList_New();

    try {
        uintsize i;
        uintsize offset = 0;

        for (i = 1; i <= count; i++) {
            uintsize separatorIndex;

            if (i == count) {
                separatorIndex = String_GetLength(str);
            }
            else {
                separatorIndex = String_IndexOfAny_Offset(str, separators, offset);

                if (separatorIndex == InvalidIndex) {
                    break;
                }
            }

            if (separatorIndex == offset) {
                if ((options & StringSplitOptions_RemoveEmptyEntries) == 0) {
                    IList_Add(list, const_cast(String_Empty));
                }
            }
            else {
                String *sub = String_Substring_WithLength(str, offset, separatorIndex - offset);

                try {
                    IList_Add(list, sub);
                }
                finally {
                    release(sub);
                }
                endtry;
            }

            offset = separatorIndex + 1;
        }

        if (i <= count) {
            if (offset == String_GetLength(str)) {
                if ((options & StringSplitOptions_RemoveEmptyEntries) == 0) {
                    IList_Add(list, const_cast(String_Empty));
                }
            }
            else if (offset < String_GetLength(str)) {
                String *sub = String_Substring_WithLength(str, offset, String_GetLength(str) - offset);

                try {
                    IList_Add(list, sub);
                }
                finally {
                    release(sub);
                }
                endtry;
            }
        }
    }
    catch (Exception) {
        release(list);
        throw;
    }
    endtry;

    return list;
}

public bool String_StartsWith(const String *str, char value)
{
    return CString_StartsWith(String_GetCString(str), value);
}

public bool String_StartsWithCString(const String *str, const char *value)
{
    return CString_StartsWithCString(String_GetCString(str), value);
}

public bool String_StartsWithCString_IgnoreCase(const String *str, const char *value, bool ignoreCase)
{
    return CString_StartsWithCString_IgnoreCase(String_GetCString(str), value, ignoreCase);
}

public bool String_StartsWithString(const String *str, const String *value)
{
    return String_StartsWithString_IgnoreCase(str, value, false);
}

public bool String_StartsWithString_IgnoreCase(const String *str, const String *value, bool ignoreCase)
{
    Validate_NotNull(str);
    Validate_NotNull(value);

    if (value->Length == 0) return true;
    if (value->Length > str->Length) return false;

    return CString_StartsWithCString_IgnoreCase(str->Value, value->Value, ignoreCase);
}

public String *String_Substring(const String *str, uintsize startIndex)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= str->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");

    return String_Substring_WithLength(str, startIndex, str->Length - startIndex);
}

public String *String_Substring_WithLength(const String *str, uintsize startIndex, uintsize length)
{
    Validate_NotNull(str);
    Validate_ArgumentRange(startIndex <= str->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(length <= str->Length - startIndex,
        "StartIndex and length must refer to a location within the string.", "length");

    if (length == 0) return const_cast(String_Empty);

    if (startIndex == 0 && length == str->Length) return const_cast(retain_const(str));

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, length);

    try {
        StringBuilder_AppendBuffer(&sb, str->Value, startIndex, length);

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public char *String_ToCString(const String *str)
{
    Validate_NotNull(str);

    return CString_Copy(str->Value);
}

public String *String_ToLower(const String *str)
{
    Validate_NotNull(str);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, str->Length);

    try {
        for (uintsize i = 0; i < str->Length; i++) {
            StringBuilder_Append(&sb, (char)char_ToLower(str->Value[i]));
        }

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *String_ToUpper(const String *str)
{
    Validate_NotNull(str);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor_WithCapacity(&sb, str->Length);

    try {
        for (uintsize i = 0; i < str->Length; i++) {
            StringBuilder_Append(&sb, (char)char_ToUpper(str->Value[i]));
        }

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *String_Trim(const String *str, const char *trimChars)
{
    Validate_NotNull(str);

    if (CString_IsNullOrEmpty(trimChars)) {
        return TrimWhiteSpace(str, 2);
    }

    return Trim(str, trimChars, 2);
}

public String *String_TrimEnd(const String *str, const char *trimChars)
{
    Validate_NotNull(str);

    if (CString_IsNullOrEmpty(trimChars)) {
        return TrimWhiteSpace(str, 1);
    }

    return Trim(str, trimChars, 1);
}

public String *String_TrimStart(const String *str, const char *trimChars)
{
    Validate_NotNull(str);

    if (CString_IsNullOrEmpty(trimChars)) {
        return TrimWhiteSpace(str, 0);
    }

    return Trim(str, trimChars, 0);
}

/* IEnumerable */
public IEnumerator *String_GetEnumerator(const String *str)
{
    return StringEnumerator_New(str);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal String *String_WrapCString(const char *value, String *buffer)
{
    assert(buffer != null);

    if (value == null) {
        // If the string is null, return a null pointer.
        return null;
    }
    else {
        // Otherwise, initialize the buffer.

        // Do not set the destructor to prevent the value from being deallocated.
        Object_Constructor(buffer, (const ObjectVTable*)&String_VTableNoDestructor);

        *(uintsize*)const_cast(&buffer->Length) = CString_Length(value);
        *(const char**)const_cast(&buffer->Value) = value;

        return buffer;
    }
}

/**************************************/
/* Private function definitions       */
/**************************************/

private String *Trim(const String *str, const char *trimChars, int mode)
{
    assert(str != null);
    assert(trimChars != null);

    uintsize length = str->Length;
    uintsize start = 0;
    uintsize end = length;

    if (mode != 1) {
        while (start < length && CString_Contains(trimChars, str->Value[start])) {
            start++;
        }
    }

    if (mode != 0) {
        while (end > start && CString_Contains(trimChars, str->Value[end - 1])) {
            end--;
        }
    }

    return String_Substring_WithLength(str, start, end - start);
}

private String *TrimWhiteSpace(const String *str, int mode)
{
    assert(str != null);

    uintsize length = str->Length;
    uintsize start = 0;
    uintsize end = length;

    if (mode != 1) {
        while (start < length && char_IsWhiteSpace(str->Value[start])) {
            start++;
        }
    }

    if (mode != 0) {
        while (end > start && char_IsWhiteSpace(str->Value[end - 1])) {
            end--;
        }
    }

    return String_Substring_WithLength(str, start, end - start);
}
