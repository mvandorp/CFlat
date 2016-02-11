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
#include "CFlat/String-private.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/StringBuilder-private.h"
#include "CFlat/Validate.h"

#include <stdarg.h>

/* Static variables */
static const String Empty = CFLAT_STRING_LITERAL("");

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

uintsize String_GetLength(const String *str)
{
    Validate_NotNull(str);

    return str->Length;
}

const char *String_GetCString(const String *str)
{
    Validate_NotNull(str);

    return str->Value;
}

char String_GetCharAt(const String *str, uintsize index)
{
    Validate_NotNull(str);
    Validate_IsTrue(index < str->Length, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");

    return str->Value[index];
}

char *String_ToCString(const String *str)
{
    Validate_NotNull(str);

    return CString_Copy(str->Value);
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

const String *String_Empty(void)
{
    return &Empty;
}

/**************************************/
/* Private function definitions       */
/**************************************/

String *String_Format(const String *format, va_list args)
{
    assert(format != null);

    StringBuilder *sb = StringBuilder_New();

    StringBuilder_AppendFormat(sb, format, args);

    String *result = StringBuilder_ToString(sb);

    Object_Delete(sb);

    return result;
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
