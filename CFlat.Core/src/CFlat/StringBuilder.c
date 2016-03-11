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

/* Private constants */
private const uintsize DefaultCapacity = 16;
private const ObjectVTable StringBuilder_VTable = ObjectVTable_Initializer((Destructor)StringBuilder_Destructor);
private const ObjectVTable StringBuilder_VTableNoDestructor = ObjectVTable_Initializer(null);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public StringBuilder *StringBuilder_New(void)
{
    return StringBuilder_New_WithInitialStringValueAndCapacity(null, DefaultCapacity);
}

public StringBuilder *StringBuilder_New_WithCapacity(uintsize capacity)
{
    return StringBuilder_New_WithInitialStringValueAndCapacity(null, capacity);
}

public StringBuilder *StringBuilder_New_WithInitialCStringValue(const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    return StringBuilder_New_WithInitialStringValueAndCapacity(str, DefaultCapacity);
}

public StringBuilder *StringBuilder_New_WithInitialCStringValueAndCapacity(const char *value, uintsize capacity)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    return StringBuilder_New_WithInitialStringValueAndCapacity(str, capacity);
}

public StringBuilder *StringBuilder_New_WithInitialStringValue(const String *value)
{
    return StringBuilder_New_WithInitialStringValueAndCapacity(value, DefaultCapacity);
}

public StringBuilder *StringBuilder_New_WithInitialStringValueAndCapacity(const String *value, uintsize capacity)
{
    StringBuilder *sb = Memory_Allocate(sizeof(StringBuilder));

    try {
        StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, value, capacity);

        Object_SetDeallocator(sb, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(sb);
        throw;
    }
    endtry;

    return sb;
}

/* Constructors */
public void StringBuilder_Constructor(StringBuilder *sb)
{
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, String_Empty, DefaultCapacity);
}

public void StringBuilder_Constructor_WithCapacity(StringBuilder *sb, uintsize capacity)
{
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, String_Empty, capacity);
}

public void StringBuilder_Constructor_WithInitialCStringValue(StringBuilder *sb, const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, str, DefaultCapacity);
}

public void StringBuilder_Constructor_WithInitialCStringValueAndCapacity(
    StringBuilder *sb,
    const char *value,
    uintsize capacity)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, str, capacity);
}

public void StringBuilder_Constructor_WithInitialStringValue(StringBuilder *sb, const String *value)
{
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, value, DefaultCapacity);
}

public void StringBuilder_Constructor_WithInitialStringValueAndCapacity(
    StringBuilder *sb,
    const String *value,
    uintsize capacity)
{
    Object_Constructor(sb, &StringBuilder_VTable);

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

    // Initialize the StringBuilder.
    sb->Length = length;
    sb->Capacity = capacity;
    sb->Value = Memory_Allocate(capacity + 1);

    // Initialize the contents of the StringBuilder to the given string.
    Memory_Copy(String_GetCString(value), sb->Value, length);
}

/* Destructor */
public void StringBuilder_Destructor(StringBuilder *sb)
{
    Validate_NotNull(sb);

    Memory_Deallocate(sb->Value);
}

/* Properties */
public uintsize StringBuilder_GetLength(const StringBuilder *sb)
{
    Validate_NotNull(sb);

    return sb->Length;
}

public uintsize StringBuilder_GetCapacity(const StringBuilder *sb)
{
    Validate_NotNull(sb);

    return sb->Capacity;
}

public void StringBuilder_SetCapacity(StringBuilder *sb, uintsize capacity)
{
    Validate_NotNull(sb);
    Validate_IsTrue(
        capacity >= sb->Length,
        ArgumentOutOfRangeException,
        "Capacity cannot be smaller than the current length.");

    if (capacity != sb->Capacity) {
        sb->Value = Memory_Reallocate(sb->Value, capacity + 1);
        sb->Capacity = capacity;
    }
}

/* Methods */
public void StringBuilder_Append(StringBuilder *sb, char value)
{
    Validate_NotNull(sb);

    // Increase the capacity if needed.
    if (sb->Length == sb->Capacity) {
        StringBuilder_SetCapacity(sb, sb->Capacity * 2);
    }

    sb->Value[sb->Length++] = value;
}

public void StringBuilder_AppendCString(StringBuilder *sb, const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_AppendString(sb, str);
}

public void StringBuilder_AppendString(StringBuilder *sb, const String *value)
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

public void StringBuilder_AppendFormatCString(StringBuilder *sb, const char *format, ...)
{
    VarArgs args;
    VarArgs_Start(args, format);

    StringBuilder_AppendFormatCStringV(sb, format, args);

    VarArgs_End(args);
}

public void StringBuilder_AppendFormatCStringV(StringBuilder *sb, const char *format, VarArgs args)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    StringBuilder_AppendFormatStringV(sb, str, args);
}

public void StringBuilder_AppendFormatString(StringBuilder *sb, const String *format, ...)
{
    VarArgs args;
    VarArgs_Start(args, format);

    StringBuilder_AppendFormatStringV(sb, format, args);

    VarArgs_End(args);
}

public void StringBuilder_AppendLine(StringBuilder *sb)
{
    StringBuilder_Append(sb, '\n');
}

public void StringBuilder_AppendLineCString(StringBuilder *sb, const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_AppendLineString(sb, str);
}

public void StringBuilder_AppendLineString(StringBuilder *sb, const String *value)
{
    Validate_NotNull(sb);

    StringBuilder_AppendString(sb, value);
    StringBuilder_Append(sb, '\n');
}

public void StringBuilder_Clear(StringBuilder *sb)
{
    Validate_NotNull(sb);

    // Reset the length to zero.
    sb->Length = 0;
}

public String *StringBuilder_DeleteAndToString(StringBuilder *sb)
{
    Validate_NotNull(sb);

    // Manually allocate a String wrapper for the C-string.
    String *str = Memory_Allocate(sizeof(String));

    try {
        char *buffer = StringBuilder_DeleteAndToCString(sb);

        // Create a String wrapper to hold the actual value.
        String_WrapCString(buffer, str);

        // Restore the vtable and deallocator of the String.
        Object_SetVTable(str, &String_VTable);
        Object_SetDeallocator(str, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(str);
        throw;
    }
    endtry;

    return str;
}

public char *StringBuilder_DeleteAndToCString(StringBuilder *sb)
{
    char *buffer = (char*)StringBuilder_GetBuffer(sb);

    // Prevent the destructor from being invoked so that the buffer remains valid.
    Object_SetVTable(sb, &StringBuilder_VTableNoDestructor);

    // If the StringBuilder was not deleted as a result of Object_Release(), throw an InvalidOperationException.
    if (!Object_Release(sb)) {
        Object_SetVTable(sb, &StringBuilder_VTable);
        Object_Aquire(sb);

        throw_new(
            InvalidOperationException,
            "Could not delete the object because there are still references to the object.");
    }

    return buffer;
}

public void StringBuilder_Insert(StringBuilder *sb, uintsize index, char value)
{
    Validate_NotNull(sb);
    Validate_IsTrue(index <= sb->Length, ArgumentOutOfRangeException, "Index must be within the bounds of the string.");

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

public void StringBuilder_InsertCString(StringBuilder *sb, uintsize index, const char *value)
{
    String strBuffer;
    String *str = String_WrapCString(value, &strBuffer);

    StringBuilder_InsertString(sb, index, str);
}

public void StringBuilder_InsertString(StringBuilder *sb, uintsize index, const String *value)
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

public void StringBuilder_Remove(StringBuilder *sb, uintsize startIndex, uintsize count)
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

public String *StringBuilder_ToString(const StringBuilder *sb)
{
    return String_New(StringBuilder_GetBuffer(sb));
}

public char *StringBuilder_ToCString(const StringBuilder *sb)
{
    return CString_Copy(StringBuilder_GetBuffer(sb));
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal const char *StringBuilder_GetBuffer(const StringBuilder *sb)
{
    Validate_NotNull(sb);

    // Ensure that the buffer has a terminating null character.
    sb->Value[sb->Length] = '\0';

    return sb->Value;
}
