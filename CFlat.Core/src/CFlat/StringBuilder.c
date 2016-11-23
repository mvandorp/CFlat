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
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

/* Private constants */
/// <summary>
/// The default capacity for an empty <see cref="StringBuilder"/>.
/// </summary>
private const uintsize DefaultCapacity = 16;

/// <summary>
/// The virtual method table for the <see cref="StringBuilder"/> class.
/// </summary>
private const ObjectVTable VTable = ObjectVTable_Initializer((DestructorFunc)StringBuilder_Destructor);

/// <summary>
/// The virtual method table for the <see cref="StringBuilder"/> class, without a destructor set so that the internal
/// null-terminated string is not automatically destroyed.
/// </summary>
private const ObjectVTable VTableNoDestructor = ObjectVTable_Initializer(null);

/**************************************/
/* Private functions                  */
/**************************************/

private void EnsureCapacity(StringBuilder *sb, uintsize minCapacity);

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
    Object_Constructor(sb, &VTable);

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
    if (length) {
        Memory_Copy(String_GetCString(value), sb->Value, length);
    }
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
    Validate_ArgumentRange(capacity >= sb->Length,
        "Capacity cannot be smaller than the current length.", "capacity");

    if (capacity != sb->Capacity) {
        sb->Value = Memory_Reallocate(sb->Value, capacity + 1);
        sb->Capacity = capacity;
    }
}

/* Methods */
public void StringBuilder_Append(StringBuilder *sb, char value)
{
    Validate_NotNull(sb);

    EnsureCapacity(sb, sb->Length + 1);

    sb->Value[sb->Length++] = value;
}

public void StringBuilder_AppendBuffer(StringBuilder *sb, const char *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(sb);
    Validate_NotNull(buffer);

    EnsureCapacity(sb, sb->Length + count);

    // Copy the string to the end of the buffer.
    Memory_CopyOffset(buffer, offset, sb->Value, sb->Length, count);

    sb->Length += count;
}

public void StringBuilder_AppendCString(StringBuilder *sb, const char *value)
{
    Validate_NotNull(sb);

    if (value == null) return;

    StringBuilder_AppendBuffer(sb, value, 0, CString_Length(value));
}

public void StringBuilder_AppendString(StringBuilder *sb, const String *value)
{
    Validate_NotNull(sb);

    if (value == null) return;

    StringBuilder_AppendBuffer(sb, String_GetCString(value), 0, String_GetLength(value));
}

public void StringBuilder_AppendFormatCString(StringBuilder *sb, const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    StringBuilder_AppendFormatCStringV(sb, format, args);

    VarArgs_End(args);
}

public void StringBuilder_AppendFormatCStringV(StringBuilder *sb, const char *format, VarArgsList args)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    StringBuilder_AppendFormatStringV(sb, str, args);
}

public void StringBuilder_AppendFormatString(StringBuilder *sb, const String *format, ...)
{
    VarArgsList args;
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
    Validate_NotNull(sb);

    StringBuilder_AppendCString(sb, value);
    StringBuilder_Append(sb, '\n');
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
        Object_SetVTable(str, (const ObjectVTable*)&String_VTable);
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
    char *buffer = StringBuilder_GetBuffer(sb);

    // Prevent the destructor from being invoked so that the buffer remains valid.
    Object_SetVTable(sb, &VTableNoDestructor);

    // If the StringBuilder was not deleted as a result of release(), throw an InvalidOperationException.
    if (!release(sb)) {
        Object_SetVTable(sb, &VTable);
        retain(sb);

        throw_new(
            InvalidOperationException,
            "Could not delete the object because there are still references to the object.");
    }

    return buffer;
}

public void StringBuilder_Insert(StringBuilder *sb, uintsize index, char value)
{
    Validate_NotNull(sb);
    Validate_ArgumentRange(index <= sb->Length, "Index must be within the bounds of the string.", "index");

    EnsureCapacity(sb, sb->Length + 1);

    // Copy the contents of the buffer after index forward by 1 byte.
    Memory_CopyOffset(sb->Value, index, sb->Value, index + 1, sb->Length - index);

    // Insert the character.
    sb->Value[index] = value;

    sb->Length++;
}

public void StringBuilder_InsertBuffer(
    StringBuilder *sb,
    uintsize index,
    const char *buffer,
    uintsize offset,
    uintsize count)
{
    Validate_NotNull(sb);
    Validate_NotNull(buffer);
    Validate_ArgumentRange(index <= sb->Length, "Index must be within the bounds of the string.", "index");

    EnsureCapacity(sb, sb->Length + count);

    // Copy the contents of the buffer after index forward by length bytes.
    Memory_CopyOffset(sb->Value, index, sb->Value, index + count, sb->Length - index);

    // Copy the string into the buffer.
    Memory_CopyOffset(buffer, offset, sb->Value, index, count);

    sb->Length += count;
}

public void StringBuilder_InsertCString(StringBuilder *sb, uintsize index, const char *value)
{
    Validate_NotNull(sb);
    Validate_ArgumentRange(index <= sb->Length, "Index must be within the bounds of the string.", "index");

    if (value == null) return;

    StringBuilder_InsertBuffer(sb, index, value, 0, CString_Length(value));
}

public void StringBuilder_InsertString(StringBuilder *sb, uintsize index, const String *value)
{
    Validate_NotNull(sb);
    Validate_ArgumentRange(index <= sb->Length, "Index must be within the bounds of the string.", "index");

    if (value == null) return;

    StringBuilder_InsertBuffer(sb, index, String_GetCString(value), 0, String_GetLength(value));
}

public void StringBuilder_Remove(StringBuilder *sb, uintsize startIndex, uintsize count)
{
    Validate_NotNull(sb);
    Validate_ArgumentRange(startIndex <= sb->Length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(startIndex + count <= sb->Length,
        "Count must refer to a location within the string/array/collection.", "count");

    // Copy the contents of the buffer backward after index forward by length bytes.
    Memory_CopyOffset(sb->Value, startIndex + count, sb->Value, startIndex, sb->Length - (startIndex + count));

    sb->Length -= count;
}

public void StringBuilder_Replace(StringBuilder *sb, char oldValue, char newValue)
{
    Validate_NotNull(sb);

    for (uintsize i = 0; i < sb->Length; i++) {
        if (sb->Value[i] == oldValue) sb->Value[i] = newValue;
    }
}

public void StringBuilder_ReplaceCString(StringBuilder *sb, const char *oldValue, const char *newValue)
{
    Validate_NotNull(sb);
    Validate_NotNull(oldValue);
    Validate_Argument(oldValue[0] != '\0', "String cannot be of zero length.", "oldValue");

    uintsize oldValueLength = CString_Length(oldValue);
    uintsize newValueLength = newValue == null ? 0 : CString_Length(newValue);
    uintsize i = 0;

    while (i < sb->Length) {
        if (CString_StartsWithCString(&sb->Value[i], oldValue)) {
            StringBuilder_Remove(sb, i, oldValueLength);
            StringBuilder_InsertCString(sb, i, newValue);

            i += newValueLength;
        }
        else {
            i++;
        }
    }
}

public void StringBuilder_ReplaceString(StringBuilder *sb, const String *oldValue, const String *newValue)
{
    Validate_NotNull(sb);
    Validate_NotNull(oldValue);
    Validate_Argument(oldValue->Length != 0, "String cannot be of zero length.", "oldValue");

    uintsize oldValueLength = String_GetLength(oldValue);
    uintsize newValueLength = newValue == null ? 0 : String_GetLength(newValue);
    uintsize i = 0;

    while (i < sb->Length) {
        if (CString_StartsWithString(&sb->Value[i], oldValue)) {
            StringBuilder_Remove(sb, i, oldValueLength);
            StringBuilder_InsertString(sb, i, newValue);

            i += newValueLength;
        }
        else {
            i++;
        }
    }
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

internal char *StringBuilder_GetBuffer(const StringBuilder *sb)
{
    Validate_NotNull(sb);

    // Ensure that the buffer has a terminating null character.
    sb->Value[sb->Length] = '\0';

    return sb->Value;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void EnsureCapacity(StringBuilder *sb, uintsize minCapacity)
{
    assert(sb != null);

    if (sb->Capacity < minCapacity) {
        uintsize capacity;
        capacity = uintsize_Max(minCapacity, sb->Length * 2);
        capacity = uintsize_Max(capacity, DefaultCapacity);

        StringBuilder_SetCapacity(sb, capacity);
    }
}
