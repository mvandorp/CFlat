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

#include <stdarg.h>

/* Static constants */
static const String Empty = CFLAT_STRING_LITERAL("");

/* Extern constants */
extern const String * const String_Empty = &Empty;

/**************************************/
/* Extern function definitions        */
/**************************************/

String *String_New(const char *value)
{
    String *str = Memory_Allocate(sizeof(String));

    // Initialize the string to the value represented by value.
    String_Constructor(str, value);

    // Set the proper deallocator that corresponds with the allocator.
    Object_SetDeallocator(str, Memory_Deallocate);

    return str;
}

void String_Constructor(String *str, const char *value)
{
    // Initialize the object and set the destructor.
    Object_Constructor(str, String_Destructor);

    // Initialize the string.
    if (value == null) {
        str->Length = 0;
        str->Value = "";
    }
    else {
        str->Length = CString_Length(value);
        str->Value = CString_Copy(value);
    }
}

void String_Destructor(void *str)
{
    Validate_NotNull(str);

    Memory_Deallocate((char*)((String*)str)->Value);
}

char String_GetCharAt(const String *str, uintsize index)
{
    Validate_NotNull(str);
    Validate_IsTrue(index < str->Length, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");

    return str->Value[index];
}

const char *String_GetCString(const String *str)
{
    Validate_NotNull(str);

    return str->Value;
}

uintsize String_GetLength(const String *str)
{
    Validate_NotNull(str);

    return str->Length;
}

bool String_Equals(const String *str1, const String *str2)
{
    return str1 == str2 || (
        str1 != null &&
        str2 != null &&
        String_GetLength(str1) == String_GetLength(str2) &&
        CString_Equals(String_GetCString(str1), String_GetCString(str2)));
}

bool String_EqualsCString(const String *str1, const char *str2)
{
    return (str1 == null && str2 == null) || (
        str1 != null &&
        str2 != null &&
        CString_Equals(String_GetCString(str1), str2));
}

String *String_FormatCString(const char *format, ...)
{
    Validate_NotNull(format);

    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    va_list args;
    va_start(args, format);

    String *result = String_Format(str, args);

    va_end(args);

    return result;
}

String *String_FormatString(const String *format, ...)
{
    Validate_NotNull(format);

    va_list args;
    va_start(args, format);

    String *result = String_Format(format, args);

    va_end(args);

    return result;
}

uintsize String_IndexOf(const String *str, char value)
{
    return String_IndexOf_Substring(str, value, 0, String_GetLength(str));
}

uintsize String_IndexOf_Offset(const String *str, char value, uintsize startIndex)
{
    return String_IndexOf_Substring(str, value, startIndex, String_GetLength(str) - startIndex);
}

uintsize String_IndexOf_Substring(const String *str, char value, uintsize startIndex, uintsize count)
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

uintsize String_IndexOfAny(const String *str, const char *anyOf)
{
    return String_IndexOfAny_Substring(str, anyOf, 0, String_GetLength(str));
}

uintsize String_IndexOfAny_Offset(const String *str, const char *anyOf, uintsize startIndex)
{
    return String_IndexOfAny_Substring(str, anyOf, startIndex, String_GetLength(str) - startIndex);
}

uintsize String_IndexOfAny_Substring(const String *str, const char *anyOf, uintsize startIndex, uintsize count)
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

uintsize String_IndexOfCString(const String *str, const char *value)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_IndexOfString(str, valueWrapper);
}

uintsize String_IndexOfCString_Offset(const String *str, const char *value, uintsize startIndex)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_IndexOfString_Offset(str, valueWrapper, startIndex);
}

uintsize String_IndexOfCString_Substring(const String *str, const char *value, uintsize startIndex, uintsize count)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_IndexOfString_Substring(str, valueWrapper, startIndex, count);
}

uintsize String_IndexOfString(const String *str, const String *value)
{
    return String_IndexOfString_Substring(str, value, 0, String_GetLength(str));
}

uintsize String_IndexOfString_Offset(const String *str, const String *value, uintsize startIndex)
{
    return String_IndexOfString_Substring(str, value, startIndex, String_GetLength(str) - startIndex);
}

uintsize String_IndexOfString_Substring(const String *str, const String *value, uintsize startIndex, uintsize count)
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

uintsize String_LastIndexOf(const String *str, char value)
{
    return String_LastIndexOf_Substring(str, value, String_GetLength(str) - 1, String_GetLength(str));
}

uintsize String_LastIndexOf_Offset(const String *str, char value, uintsize startIndex)
{
    return String_LastIndexOf_Substring(str, value, startIndex, startIndex + 1);
}

uintsize String_LastIndexOf_Substring(const String *str, char value, uintsize startIndex, uintsize count)
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

uintsize String_LastIndexOfAny(const String *str, const char *anyOf)
{
    Validate_NotNull(str);

    if (str->Length == 0) {
        return InvalidIndex;
    }
    else {
        return String_LastIndexOfAny_Substring(str, anyOf, str->Length - 1, str->Length);
    }
}

uintsize String_LastIndexOfAny_Offset(const String *str, const char *anyOf, uintsize startIndex)
{
    return String_LastIndexOfAny_Substring(str, anyOf, startIndex, startIndex + 1);
}

uintsize String_LastIndexOfAny_Substring(const String *str, const char *anyOf, uintsize startIndex, uintsize count)
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

uintsize String_LastIndexOfCString(const String *str, const char *value)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_LastIndexOfString(str, valueWrapper);
}

uintsize String_LastIndexOfCString_Offset(const String *str, const char *value, uintsize startIndex)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_LastIndexOfString_Offset(str, valueWrapper, startIndex);
}

uintsize String_LastIndexOfCString_Substring(const String *str, const char *value, uintsize startIndex, uintsize count)
{
    String valueBuffer;
    String *valueWrapper = String_WrapCString(value, &valueBuffer);

    return String_LastIndexOfString_Substring(str, valueWrapper, startIndex, count);
}

uintsize String_LastIndexOfString(const String *str, const String *value)
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

uintsize String_LastIndexOfString_Offset(const String *str, const String *value, uintsize startIndex)
{
    return String_LastIndexOfString_Substring(str, value, startIndex, startIndex + 1);
}

uintsize String_LastIndexOfString_Substring(
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

char *String_ToCString(const String *str)
{
    Validate_NotNull(str);

    return CString_Copy(str->Value);
}

/**************************************/
/* Private function definitions       */
/**************************************/

String *String_Format(const String *format, va_list args)
{
    assert(format != null);

    StringBuilder sb;
    StringBuilder_Constructor(&sb);

    StringBuilder_AppendFormat(&sb, format, args);

    return StringBuilder_DeleteAndToString(&sb);
}

String *String_WrapCString(const char *value, String *buffer)
{
    assert(buffer != null);

    if (value == null) {
        // If the string is null, return a null pointer.
        return null;
    }
    else {
        // Otherwise, initialize the buffer.

        // Do not set the destructor to prevent the value from being deallocated.
        Object_Constructor(buffer, null);

        buffer->Length = CString_Length(value);
        buffer->Value = value;

        return buffer;
    }
}
