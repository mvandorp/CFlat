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
#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"

/* Private constants */
private const String Empty = CFLAT_STRING_LITERAL("");

/* Public constants */
public const String * const String_Empty = &Empty;

/* Internal constants */
internal const ObjectVTable String_VTable = ObjectVTable_Initializer((Destructor)String_Destructor);

internal const ObjectVTable String_VTableNoDestructor = ObjectVTable_Initializer(null);

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

public void String_Constructor(String *str, const char *value)
{
    Validate_NotNull(str);

    Object_Constructor(str, &String_VTable);

    if (value == null) {
        str->Length = 0;
        str->Value = "";
    }
    else {
        str->Length = CString_Length(value);
        str->Value = CString_Copy(value);
    }
}

public void String_Destructor(String *str)
{
    Validate_NotNull(str);

    Memory_Deallocate((void*)str->Value);
}

public char String_GetCharAt(const String *str, uintsize index)
{
    Validate_NotNull(str);
    Validate_IsTrue(index < str->Length, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");

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

public bool String_Equals(const String *str1, const String *str2)
{
    return str1 == str2 || (
        str1 != null &&
        str2 != null &&
        String_GetLength(str1) == String_GetLength(str2) &&
        CString_Equals(String_GetCString(str1), String_GetCString(str2)));
}

public bool String_EqualsCString(const String *str1, const char *str2)
{
    return (str1 == null && str2 == null) || (
        str1 != null &&
        str2 != null &&
        CString_Equals(String_GetCString(str1), str2));
}

public String *String_FormatCString(const char *format, ...)
{
    VarArgs args;
    VarArgs_Start(args, format);

    String *result = String_FormatCStringV(format, args);

    VarArgs_End(args);

    return result;
}

public String *String_FormatCStringV(const char *format, VarArgs args)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return String_FormatStringV(str, args);
}

public String *String_FormatString(const String *format, ...)
{
    VarArgs args;
    VarArgs_Start(args, format);

    String *result = String_FormatStringV(format, args);

    VarArgs_End(args);

    return result;
}

public String *String_FormatStringV(const String *format, VarArgs args)
{
    Validate_NotNull(format);

    StringBuilder sb;
    StringBuilder_Constructor(&sb);

    StringBuilder_AppendFormatStringV(&sb, format, args);

    return StringBuilder_DeleteAndToString(&sb);
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
    Validate_IsTrue(startIndex <= str->Length, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");
    Validate_IsTrue(startIndex + count <= str->Length, ArgumentOutOfRangeException,
        "Count must be positive and count must refer to a location within the string.");

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
    Validate_IsTrue(startIndex <= str->Length, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");
    Validate_IsTrue(startIndex + count <= str->Length, ArgumentOutOfRangeException,
        "Count must be positive and count must refer to a location within the string.");

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
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_IndexOfString(str, valueWrapper);
}

public uintsize String_IndexOfCString_Offset(const String *str, const char *value, uintsize startIndex)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_IndexOfString_Offset(str, valueWrapper, startIndex);
}

public uintsize String_IndexOfCString_Substring(
    const String *str,
    const char *value,
    uintsize startIndex,
    uintsize count)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_IndexOfString_Substring(str, valueWrapper, startIndex, count);
}

public uintsize String_IndexOfString(const String *str, const String *value)
{
    return String_IndexOfString_Substring(str, value, 0, String_GetLength(str));
}

public uintsize String_IndexOfString_Offset(const String *str, const String *value, uintsize startIndex)
{
    return String_IndexOfString_Substring(str, value, startIndex, String_GetLength(str) - startIndex);
}

public uintsize String_IndexOfString_Substring(
    const String *str,
    const String *value,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);
    Validate_NotNull(value);
    Validate_IsTrue(startIndex <= str->Length, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");
    Validate_IsTrue(startIndex + count <= str->Length, ArgumentOutOfRangeException,
        "Count must be positive and count must refer to a location within the string.");

    uintsize length = value->Length;
    uintsize end = startIndex + count;

    // If we are searching for an empty string, report it at the starting index.
    if (length == 0) {
        return startIndex;
    }

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex; i + length <= end; i++) {
        const char *str1 = &str->Value[i];
        const char *str2 = value->Value;

        bool found = true;

        // Iterate through all of the search string's characters.
        for (uintsize j = 0; j < length; j++) {
            if (str1[j] != str2[j]) {
                found = false;

                break;
            }
        }

        if (found) {
            return i;
        }
    }

    return InvalidIndex;
}

public uintsize String_LastIndexOf(const String *str, char value)
{
    return String_LastIndexOf_Substring(str, value, String_GetLength(str) - 1, String_GetLength(str));
}

public uintsize String_LastIndexOf_Offset(const String *str, char value, uintsize startIndex)
{
    return String_LastIndexOf_Substring(str, value, startIndex, startIndex + 1);
}

public uintsize String_LastIndexOf_Substring(const String *str, char value, uintsize startIndex, uintsize count)
{
    Validate_NotNull(str);
    Validate_IsTrue(startIndex < str->Length || str->Length == 0, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");
    Validate_IsTrue(startIndex + 1 >= count || str->Length == 0, ArgumentOutOfRangeException,
        "Count must be positive and count must refer to a location within the string.");

    // If the string is empty, return InvalidIndex.
    if (str->Length == 0) {
        return InvalidIndex;
    }

    uintsize end = startIndex + 1 - count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex + 2; i-- > end; ) {
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
    return String_LastIndexOfAny_Substring(str, anyOf, startIndex, startIndex + 1);
}

public uintsize String_LastIndexOfAny_Substring(
    const String *str,
    const char *anyOf,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);
    Validate_IsTrue(startIndex < str->Length || str->Length == 0, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");
    Validate_IsTrue(startIndex + 1 >= count || str->Length == 0, ArgumentOutOfRangeException,
        "Count must be positive and count must refer to a location within the string.");

    // If the string is empty, return InvalidIndex.
    if (str->Length == 0) {
        return InvalidIndex;
    }

    uintsize end = startIndex + 1 - count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex + 2; i-- > end; ) {
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
    return String_LastIndexOfString_Substring(str, value, startIndex, startIndex + 1);
}

public uintsize String_LastIndexOfString_Substring(
    const String *str,
    const String *value,
    uintsize startIndex,
    uintsize count)
{
    Validate_NotNull(str);
    Validate_NotNull(value);
    Validate_IsTrue(startIndex <= str->Length, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");
    Validate_IsTrue(startIndex + 1 >= count || str->Length == 0, ArgumentOutOfRangeException,
        "Count must be positive and count must refer to a location within the string.");

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
    for (uintsize i = startIndex + 2 - length; i-- > end; ) {
        const char *str1 = &str->Value[i];
        const char *str2 = value->Value;

        bool found = true;

        // Iterate through all of the search string's characters.
        for (uintsize j = 0; j < length; j++) {
            if (str1[j] != str2[j]) {
                found = false;

                break;
            }
        }

        if (found) {
            return i;
        }
    }

    return InvalidIndex;
}

public char *String_ToCString(const String *str)
{
    Validate_NotNull(str);

    return CString_Copy(str->Value);
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
        Object_Constructor(buffer, &String_VTableNoDestructor);

        buffer->Length = CString_Length(value);
        buffer->Value = value;

        return buffer;
    }
}
