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

/* Types */
typedef enum ArgumentType {
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

    ArgumentType_Single,
    ArgumentType_Double
} ArgumentType;

/* Private functions */
private void ProcessFormatItem(StringBuilder *sb, StringReader *reader, StringBuilder *buffer, va_list *args);
private ArgumentType ReadFormatItem(StringReader *reader, char **formatString, StringBuilder *formatBuffer);
private ArgumentType ParseFormatItem(char *formatItem, char **formatString);
private ArgumentType ToArgumentType(const char *type);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void StringBuilder_AppendFormat(StringBuilder *sb, const String *format, va_list args)
{
    assert(sb != null);
    assert(format != null);

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
            Object_Release(reader);
            Object_Release(buffer);

            throw_new(FormatException, "Invalid format string.");
        }
        // Otherwise add character.
        else {
            StringBuilder_Append(sb, (char)StringReader_Read(reader));
        }
    }

    Object_Release(reader);
    Object_Release(buffer);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Processes the format item that the given <see cref="StringReader"/> is reading and appends the resulting string
/// to the given  <see cref="StringReader"/>.
/// </summary>
private void ProcessFormatItem(StringBuilder *sb, StringReader *reader, StringBuilder *buffer, va_list *args)
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
        case ArgumentType_CString:
            StringBuilder_AppendCString(sb, va_arg(*args, char*));
            break;

        case ArgumentType_String:
            StringBuilder_AppendString(sb, va_arg(*args, String*));
            break;

        case ArgumentType_Char:
            StringBuilder_Append(sb, (char)va_arg(*args, int));
            break;

        case ArgumentType_SByte:
        case ArgumentType_Short:
        case ArgumentType_Int:
            int_ToStringBuffered(sb, va_arg(*args, int), format);
            break;

        case ArgumentType_Long:
            long_ToStringBuffered(sb, va_arg(*args, long), format);
            break;

        case ArgumentType_Byte:
        case ArgumentType_UShort:
        case ArgumentType_UInt:
            uint_ToStringBuffered(sb, va_arg(*args, uint), format);
            break;

        case ArgumentType_ULong:
            ulong_ToStringBuffered(sb, va_arg(*args, ulong), format);
            break;

        case ArgumentType_Single:
            float_ToStringBuffered(sb, (float)va_arg(*args, double), format);
            break;

        case ArgumentType_Double:
            double_ToStringBuffered(sb, va_arg(*args, double), format);
            break;

        default:
            assert(false);
            break;
    }
}

/// <summary>
/// Reads the format item that the given <see cref="StringReader"/> is reading and returns the type and format string.
/// </summary>
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

    char *buffer = (char*)StringBuilder_GetBuffer(formatBuffer);

    // Prase the format item to find the type and format string.
    return ParseFormatItem(buffer, formatString);
}

/// <summary>
/// Parses the format item into the type and format string..
/// </summary>
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
private ArgumentType ToArgumentType(const char *type)
{
    // TODO: Use a hashmap for lookup.
    if (CString_Equals(type, "string")) {
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
