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

#include "CFlat/StringBuilder.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/Math.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

#include <stdarg.h>

/* Static constants */
static const uintsize DefaultCapacity = 16;

/**************************************/
/* Extern function definitions        */
/**************************************/

/* Allocators */
StringBuilder *StringBuilder_New(void)
{
    return StringBuilder_New_WithInitialStringValueAndCapacity(null, DefaultCapacity);
}

StringBuilder *StringBuilder_New_WithCapacity(uintsize capacity)
{
    return StringBuilder_New_WithInitialStringValueAndCapacity(null, capacity);
}

StringBuilder *StringBuilder_New_WithInitialCStringValue(const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    return StringBuilder_New_WithInitialStringValueAndCapacity(str, DefaultCapacity);
}

StringBuilder *StringBuilder_New_WithInitialCStringValueAndCapacity(const char *value, uintsize capacity)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    return StringBuilder_New_WithInitialStringValueAndCapacity(str, capacity);
}

StringBuilder *StringBuilder_New_WithInitialStringValue(const String *value)
{
    return StringBuilder_New_WithInitialStringValueAndCapacity(value, DefaultCapacity);
}

StringBuilder *StringBuilder_New_WithInitialStringValueAndCapacity(const String *value, uintsize capacity)
{
    // Allocate a new string builder and set the destructor callback.
    StringBuilder *sb = Memory_Allocate(sizeof(StringBuilder));

    // Initialize the string builder with the given initial value and capacity.
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, value, capacity);

    // Set the proper deallocator that corresponds with the allocator.
    Object_SetDeallocator(sb, Memory_Deallocate);

    return sb;
}

/* Constructors */
void StringBuilder_Constructor(StringBuilder *sb)
{
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, String_Empty, DefaultCapacity);
}

void StringBuilder_Constructor_WithCapacity(StringBuilder *sb, uintsize capacity)
{
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, String_Empty, capacity);
}

void StringBuilder_Constructor_WithInitialCStringValue(StringBuilder *sb, const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, str, DefaultCapacity);
}

void StringBuilder_Constructor_WithInitialCStringValueAndCapacity(
    StringBuilder *sb,
    const char *value,
    uintsize capacity)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, str, capacity);
}

void StringBuilder_Constructor_WithInitialStringValue(StringBuilder *sb, const String *value)
{
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, value, DefaultCapacity);
}

void StringBuilder_Constructor_WithInitialStringValueAndCapacity(
    StringBuilder *sb,
    const String *value,
    uintsize capacity)
{
    Validate_NotNull(sb);

    // Initialize the object and set the destructor.
    Object_Constructor(sb, StringBuilder_Destructor);

    // If the value is null, initialize to an empty string instead.
    if (value == null) {
        value = String_Empty;
    }

    uintsize length = String_GetLength(value);

    // If the capacity is zero, use the default capacity instead.
    if (capacity == 0) {
        capacity = DefaultCapacity;
    }

    // If the capacity is not large enough for the given value, increase the capacity.
    if (capacity < length) {
        capacity = length;
    }

    // Initialize the stringbuilder.
    sb->Length = length;
    sb->Capacity = capacity;
    sb->Value = Memory_Allocate(capacity + 1);

    // Initialize the contents of the stringbuilder to the given string.
    Memory_Copy(String_GetCString(value), sb->Value, length);
}

/* Destructor */
void StringBuilder_Destructor(void *sb)
{
    Validate_NotNull(sb);

    StringBuilder *stringBuilder = (StringBuilder*)sb;

    Memory_Deallocate(stringBuilder->Value);
}

/* Methods */
uintsize StringBuilder_GetLength(const StringBuilder *sb)
{
    Validate_NotNull(sb);

    return sb->Length;
}

uintsize StringBuilder_GetCapacity(const StringBuilder *sb)
{
    Validate_NotNull(sb);

    return sb->Capacity;
}

void StringBuilder_SetCapacity(StringBuilder *sb, uintsize capacity)
{
    Validate_NotNull(sb);
    Validate_IsTrue(capacity >= sb->Length, ArgumentOutOfRangeException,
        "Capacity cannot be smaller than the current length.");

    sb->Capacity = capacity;
    sb->Value = Memory_Reallocate(sb->Value, capacity + 1);
}

void StringBuilder_Append(StringBuilder *sb, char value)
{
    Validate_NotNull(sb);

    // Increase the capacity if needed.
    if (sb->Length == sb->Capacity) {
        StringBuilder_SetCapacity(sb, sb->Capacity * 2);
    }

    sb->Value[sb->Length++] = value;
}

void StringBuilder_AppendCString(StringBuilder *sb, const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_AppendString(sb, str);
}

void StringBuilder_AppendString(StringBuilder *sb, const String *value)
{
    Validate_NotNull(sb);

    if (value == null) {
        return;
    }

    uintsize length = String_GetLength(value);

    // Increase the capacity if needed.
    if (sb->Length + length > sb->Capacity) {
        StringBuilder_SetCapacity(sb, int_Max(sb->Capacity * 2, sb->Capacity + length));
    }

    // Copy the string to the end of the buffer.
    Memory_CopyOffset(String_GetCString(value), 0, sb->Value, sb->Length, length);

    sb->Length += length;
}

void StringBuilder_AppendFormatCString(StringBuilder *sb, const char *format, ...)
{
    Validate_NotNull(sb);
    Validate_NotNull(format);

    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    va_list args;
    va_start(args, format);

    StringBuilder_AppendFormat(sb, str, args);

    va_end(args);
}

void StringBuilder_AppendFormatString(StringBuilder *sb, const String *format, ...)
{
    Validate_NotNull(sb);
    Validate_NotNull(format);

    va_list args;
    va_start(args, format);

    StringBuilder_AppendFormat(sb, format, args);

    va_end(args);
}

void StringBuilder_AppendLine(StringBuilder *sb)
{
    StringBuilder_Append(sb, '\n');
}

void StringBuilder_AppendLineCString(StringBuilder *sb, const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_AppendLineString(sb, str);
}

void StringBuilder_AppendLineString(StringBuilder *sb, const String *value)
{
    Validate_NotNull(sb);

    StringBuilder_AppendString(sb, value);
    StringBuilder_Append(sb, '\n');
}

void StringBuilder_Clear(StringBuilder *sb)
{
    Validate_NotNull(sb);

    // Reset the length to zero.
    sb->Length = 0;
}

String *StringBuilder_DeleteAndToString(StringBuilder *sb)
{
    // Manually allocate a String wrapper for the C-string.
    String *str = Memory_Allocate(sizeof(String));

    // Create a String wrapper to hold the actual value.
    String_WrapCString(StringBuilder_DeleteAndToCString(sb), str);

    // Restore the destructor and deallocator of the String.
    Object_SetDestructor(str, String_Destructor);
    Object_SetDeallocator(str, Memory_Deallocate);

    return str;
}

char *StringBuilder_DeleteAndToCString(StringBuilder *sb)
{
    char *buffer = (char*)StringBuilder_GetBuffer(sb);

    // Make sure the destructor is not invoked and delete the StringBuilder.
    Object_SetDestructor(sb, null);
    Object_Delete(sb);

    return buffer;
}

void StringBuilder_Insert(StringBuilder *sb, uintsize index, char value)
{
    Validate_NotNull(sb);

    // Increase the capacity if needed.
    if (sb->Length == sb->Capacity) {
        StringBuilder_SetCapacity(sb, sb->Capacity * 2);
    }

    // Copy the contents of the buffer after index forward by 1 byte.
    Memory_CopyOffset(sb->Value, index, sb->Value, index + 1, sb->Length - index);

    // Insert the character.
    sb->Value[index] = value;

    sb->Length++;
}

void StringBuilder_InsertCString(StringBuilder *sb, uintsize index, const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_InsertString(sb, index, str);
}

void StringBuilder_InsertString(StringBuilder *sb, uintsize index, const String *value)
{
    Validate_NotNull(sb);

    if (value == null) {
        return;
    }

    uintsize length = String_GetLength(value);

    // Increase the capacity if needed.
    if (sb->Length + length > sb->Capacity) {
        StringBuilder_SetCapacity(sb, int_Max(sb->Capacity * 2, sb->Capacity + length));
    }

    // Copy the contents of the buffer after index forward by length bytes.
    Memory_CopyOffset(sb->Value, index, sb->Value, index + length, sb->Length - index);

    // Copy the string into the buffer.
    Memory_CopyOffset(String_GetCString(value), 0, sb->Value, index, length);

    sb->Length += length;
}

void StringBuilder_Remove(StringBuilder *sb, uintsize startIndex, uintsize count)
{
    Validate_NotNull(sb);
    Validate_IsTrue(startIndex <= sb->Length, ArgumentOutOfRangeException,
        "Index was out of range. Must be less than the length of the string.");
    Validate_IsTrue(startIndex + count <= sb->Length, ArgumentOutOfRangeException,
        "Count must be positive and count must refer to a location within the string.");

    // Copy the contents of the buffer backward after index forward by length bytes.
    Memory_CopyOffset(sb->Value, startIndex + count, sb->Value, startIndex, sb->Length - (startIndex + count));

    sb->Length -= count;
}

String *StringBuilder_ToString(const StringBuilder *sb)
{
    return String_New(StringBuilder_GetBuffer(sb));
}

char *StringBuilder_ToCString(const StringBuilder *sb)
{
    return CString_Copy(StringBuilder_GetBuffer(sb));
}

/**************************************/
/* Private function definitions       */
/**************************************/

const char *StringBuilder_GetBuffer(const StringBuilder *sb)
{
    Validate_NotNull(sb);

    // Ensure that the buffer has a terminating null character.
    sb->Value[sb->Length] = '\0';

    return sb->Value;
}

// TODO: Refactor this method!!
void StringBuilder_AppendFormat(StringBuilder *sb, const String *format, va_list args)
{
    Validate_NotNull(sb);
    Validate_NotNull(format);

    const char *value = String_GetCString(format);
    uintsize length = String_GetLength(format);

    for (uintsize i = 0; i < length; i++) {
        if (value[i] != '%') {
            StringBuilder_Append(sb, value[i]);
        }
        else {
            if (i + 1 == length) {
                throw_new(FormatException, "Invalid format string.");
            }

            switch (value[i + 1]) {
                case '%':
                    StringBuilder_Append(sb, value[i]);
                    break;
                case 's':
                    StringBuilder_AppendCString(sb, va_arg(args, char*));
                    break;
                case '#':
                    if (i + 2 == length) {
                        throw_new(FormatException, "Invalid format string.");
                    }

                    switch (value[i + 2]) {
                        case 's':
                            StringBuilder_AppendString(sb, va_arg(args, String*));
                            break;
                        default:
                            throw_new(FormatException, "Invalid format string.");
                            break;
                    }

                    i++;
                    break;
                case 'c':
                    StringBuilder_Append(sb, va_arg(args, char));
                    break;
                default:
                    throw_new(FormatException, "Invalid format string.");
                    break;
            }

            i++;
        }
    }
}
