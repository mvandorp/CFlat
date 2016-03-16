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
#include "CFlat/String.h"
#include "CFlat/StringReader.h"
#include "CFlat/Validate.h"

/* Types */
typedef enum ArgumentType {
    ArgumentType_Pointer,
    ArgumentType_IntPtr,
    ArgumentType_UIntPtr,
    ArgumentType_UIntSize,

    ArgumentType_Char,
    ArgumentType_CString,
    ArgumentType_String,

    ArgumentType_SByte,
    ArgumentType_Byte,
    ArgumentType_Short,
    ArgumentType_UShort,
    ArgumentType_Int,
    ArgumentType_UInt,
    ArgumentType_Long,
    ArgumentType_ULong,
    ArgumentType_IntMax,
    ArgumentType_UIntMax,

    ArgumentType_Single,
    ArgumentType_Double
} ArgumentType;

/**************************************/
/* Private functions                  */
/**************************************/

private void ProcessFormatItem(StringBuilder *sb, StringReader *reader, StringBuilder *buffer, VarArgs *args);
private ArgumentType ReadFormatItem(StringReader *reader, char **formatString, StringBuilder *formatBuffer);
private ArgumentType ParseFormatItem(char *formatItem, char **formatString);
private ArgumentType ToArgumentType(const char *type);

/**************************************/
/* Public function definitions        */
/**************************************/

public void StringBuilder_AppendFormatStringV(StringBuilder *sb, const String *format, VarArgs args)
{
    Validate_NotNull(sb);
    Validate_NotNull(format);

    StringReader *reader = StringReader_New(format);
    StringBuilder *buffer = StringBuilder_New();

    while (StringReader_Peek(reader) != -1) {
        int ch = StringReader_Peek(reader);

        // Found opening brace.
        if (ch == '{') {
            // Parse '{{'.
            if (StringReader_PeekOffset(reader, 1) == '{') {
                StringReader_Skip(reader, 2);
                StringBuilder_Append(sb, '{');
            }
            // Parse format item.
            else {
                ProcessFormatItem(sb, reader, buffer, &args);
            }
        }
        // Found random closing brace.
        else if (ch == '}' && StringReader_Peek(reader) != '}') {
            release(reader);
            release(buffer);

            throw_new(FormatException, "Invalid format string.");
        }
        // Otherwise add character.
        else {
            StringBuilder_Append(sb, (char)StringReader_Read(reader));
        }
    }

    release(reader);
    release(buffer);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Processes the format item that the given <see cref="StringReader"/> is reading and appends the resulting string
/// to the given  <see cref="StringReader"/>.
/// </summary>
/// <exception cref="::FormatException"><paramref name="reader"/> does not contain a valid format item.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private void ProcessFormatItem(StringBuilder *sb, StringReader *reader, StringBuilder *buffer, VarArgs *args)
{
    assert(sb != null);
    assert(reader != null);
    assert(buffer != null);
    assert(StringReader_Peek(reader) == '{');
    assert(args != null);

    // Read the type and format.
    char *formatPointer;
    ArgumentType formatSpecifier = ReadFormatItem(reader, &formatPointer, buffer);

    // Wrap the format as a String.
    String formatBuffer;
    String *format = String_WrapCString(formatPointer, &formatBuffer);

    switch (formatSpecifier) {
        case ArgumentType_Pointer:
            StringBuilder_Append(sb, '0');
            StringBuilder_Append(sb, 'x');
#ifdef CFLAT_UINTPTR
            uintptr_ToStringBuffered(sb, (uintptr)VarArg(*args, void*), String_WrapCString("x8", &formatBuffer));
#else
            uintmax_ToStringBuffered(sb, (uintmax)VarArg(*args, void*), String_WrapCString("x8", &formatBuffer));
#endif
            break;

#ifdef CFLAT_INTPTR
        case ArgumentType_IntPtr:
            if (sizeof(intptr) < sizeof(int)) {
                intptr_ToStringBuffered(sb, (intptr)VarArg(*args, int), format);
            }
            else {
                intptr_ToStringBuffered(sb, VarArg(*args, intptr), format);
            }
            break;
#endif

#ifdef CFLAT_UINTPTR
        case ArgumentType_UIntPtr:
            if (sizeof(uintptr) < sizeof(uint)) {
                uintptr_ToStringBuffered(sb, (uintptr)VarArg(*args, uint), format);
            }
            else {
                uintptr_ToStringBuffered(sb, VarArg(*args, uintptr), format);
            }
            break;
#endif

        case ArgumentType_UIntSize:
            if (sizeof(uintsize) < sizeof(uint)) {
                uintsize_ToStringBuffered(sb, (uintsize)VarArg(*args, uint), format);
            }
            else {
                uintsize_ToStringBuffered(sb, VarArg(*args, uintsize), format);
            }
            break;

        case ArgumentType_CString:
            StringBuilder_AppendCString(sb, VarArg(*args, char*));
            break;

        case ArgumentType_String:
            StringBuilder_AppendString(sb, VarArg(*args, String*));
            break;

        case ArgumentType_Char:
            StringBuilder_Append(sb, (char)VarArg(*args, int));
            break;

        case ArgumentType_SByte:
        case ArgumentType_Short:
        case ArgumentType_Int:
            int_ToStringBuffered(sb, VarArg(*args, int), format);
            break;

        case ArgumentType_Long:
            long_ToStringBuffered(sb, VarArg(*args, long), format);
            break;

        case ArgumentType_IntMax:
            intmax_ToStringBuffered(sb, VarArg(*args, intmax), format);
            break;

        case ArgumentType_Byte:
        case ArgumentType_UShort:
        case ArgumentType_UInt:
            uint_ToStringBuffered(sb, VarArg(*args, uint), format);
            break;

        case ArgumentType_ULong:
            ulong_ToStringBuffered(sb, VarArg(*args, ulong), format);
            break;

        case ArgumentType_UIntMax:
            uintmax_ToStringBuffered(sb, VarArg(*args, uintmax), format);
            break;

        case ArgumentType_Single:
            float_ToStringBuffered(sb, (float)VarArg(*args, double), format);
            break;

        case ArgumentType_Double:
            double_ToStringBuffered(sb, VarArg(*args, double), format);
            break;

        default:
            assert(false);
            break;
    }
}

/// <summary>
/// Reads the format item that the given <see cref="StringReader"/> is reading and returns the type and format string.
/// </summary>
/// <exception cref="::FormatException"><paramref name="reader"/> does not contain a valid format item.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private ArgumentType ReadFormatItem(StringReader *reader, char **formatString, StringBuilder *formatBuffer)
{
    assert(reader != null);
    assert(formatString != null);
    assert(formatBuffer != null);
    assert(StringReader_Peek(reader) == '{');

    // Skip the '{' character.
    StringReader_Read(reader);

    // Clear the string buffer.
    StringBuilder_Clear(formatBuffer);

    // Read the format specifier.
    while (StringReader_Peek(reader) != -1) {
        if (StringReader_Peek(reader) == '{') {
            if (StringReader_PeekOffset(reader, 1) == '{') {
                StringReader_Read(reader);
            }
            else {
                break;
            }
        }
        if (StringReader_Peek(reader) == '}') {
            if (StringReader_PeekOffset(reader, 1) == '}') {
                StringReader_Read(reader);
            }
            else {
                break;
            }
        }

        StringBuilder_Append(formatBuffer, (char)StringReader_Read(reader));
    }

    // Check for invalid format.
    if (StringReader_Peek(reader) != '}') {
        throw_new(FormatException, "Invalid format string.");
    }

    // Skip the '}' character.
    StringReader_Read(reader);

    char *buffer = StringBuilder_GetBuffer(formatBuffer);

    // Prase the format item to find the type and format string.
    return ParseFormatItem(buffer, formatString);
}

/// <summary>
/// Parses the format item into the type and format string..
/// </summary>
/// <exception cref="::FormatException"><paramref name="formatItem"/> does not contain a known type.</exception>
private ArgumentType ParseFormatItem(char *formatItem, char **formatString)
{
    assert(formatItem != null);
    assert(formatString != null);

    uintsize index = CString_IndexOf(formatItem, ':');

    if (index == InvalidIndex) {
        *formatString = null;
    }
    else {
        *formatString = &formatItem[index + 1];

        formatItem[index] = '\0';
    }

    return ToArgumentType(formatItem);
}

/// <summary>
/// Finds the <see cref="ArgumentType"/> for the given string representation of a type.
/// </summary>
/// <exception cref="::FormatException"><paramref name="type"/> does not represent a known type.</exception>
private ArgumentType ToArgumentType(const char *type)
{
    // TODO: Use a hashmap for lookup.
    if (CString_Equals(type, "pointer")) {
        return ArgumentType_Pointer;
    }
#ifdef CFLAT_INTPTR
    else if (CString_Equals(type, "intptr")) {
        return ArgumentType_IntPtr;
    }
#endif
#ifdef CFLAT_UINTPTR
    else if (CString_Equals(type, "uintptr")) {
        return ArgumentType_UIntPtr;
    }
#endif
    else if (CString_Equals(type, "uintsize")) {
        return ArgumentType_UIntSize;
    }
    else if (CString_Equals(type, "string")) {
        return ArgumentType_String;
    }
    else if (CString_Equals(type, "cstring")) {
        return ArgumentType_CString;
    }
    else if (CString_Equals(type, "char")) {
        return ArgumentType_Char;
    }
    else if (CString_Equals(type, "int")) {
        return ArgumentType_Int;
    }
    else if (CString_Equals(type, "uint")) {
        return ArgumentType_UInt;
    }
    else if (CString_Equals(type, "long")) {
        return ArgumentType_Long;
    }
    else if (CString_Equals(type, "ulong")) {
        return ArgumentType_ULong;
    }
    else if (CString_Equals(type, "intmax")) {
        return ArgumentType_IntMax;
    }
    else if (CString_Equals(type, "uintmax")) {
        return ArgumentType_UIntMax;
    }
    else if (CString_Equals(type, "short")) {
        return ArgumentType_Short;
    }
    else if (CString_Equals(type, "ushort")) {
        return ArgumentType_UShort;
    }
    else if (CString_Equals(type, "sbyte")) {
        return ArgumentType_SByte;
    }
    else if (CString_Equals(type, "byte")) {
        return ArgumentType_Byte;
    }
    else if (CString_Equals(type, "float")) {
        return ArgumentType_Single;
    }
    else if (CString_Equals(type, "double")) {
        return ArgumentType_Double;
    }
    else {
        throw_new(FormatException, "Invalid format string.");

        return (ArgumentType)0;
    }
}
