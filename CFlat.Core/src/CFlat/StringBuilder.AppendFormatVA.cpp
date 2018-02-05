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
#include "CFlat/Validate.h"
#include "CFlat/IO/StringReader.h"

#include <utility>

using namespace CFlat;

/* Types */
enum ArgumentType {
    ArgumentType_Pointer,
    ArgumentType_IntPtr,
    ArgumentType_UIntPtr,
    ArgumentType_IntFSize,
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
    ArgumentType_Double,

    ArgumentType_Bool
};

/**************************************/
/* Private functions                  */
/**************************************/

static void ProcessFormatItem(StringBuilder &sb, StringReader &reader, StringBuilder &buffer, VarArgsList *args);
static ArgumentType ReadFormatItem(StringReader &reader, StringBuilder &formatBuffer, char **formatString);
static ArgumentType ParseFormatItem(char *formatItem, char **formatString);
static ArgumentType ToArgumentType(const char *type);

/**************************************/
/* Public function definitions        */
/**************************************/

void StringBuilder::AppendFormatVA(const String &format, VarArgsList args)
{
    StringBuilder buffer = StringBuilder();
    StringReader reader = StringReader(format);

    while (reader.Peek() != -1) {
        int ch = reader.Peek();

        // Found opening brace.
        if (ch == '{') {
            // Parse '{{'.
            if (reader.Peek(1) == '{') {
                reader.Skip(2);
                this->Append('{');
            }
            // Parse format item.
            else {
                ProcessFormatItem(*this, reader, buffer, &args);
            }
        }
        // Found random closing brace.
        else if (ch == '}') {
            // Parse '}}'.
            if (reader.Peek(1) == '}') {
                reader.Skip(2);
                this->Append('}');
            }
            // Handle invalid '}'.
            else {
                throw FormatException(String::Wrap("Invalid format string."));
            }
        }
        // Otherwise add character.
        else {
            this->Append((char)reader.Read());
        }
    }
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Processes the format item that the given <see cref="StringReader"/> is reading and appends the resulting string
/// to the given <see cref="StringReader"/>.
/// </summary>
/// <exception cref="::FormatException"><paramref name="reader"/> does not contain a valid format item.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void ProcessFormatItem(StringBuilder &sb, StringReader &reader, StringBuilder &formatBuffer, VarArgsList *args)
{
    assert(reader.Peek() == '{');

    // Read the type and format.
    char *formatString = nullptr;
    ArgumentType formatSpecifier = ReadFormatItem(reader, formatBuffer, &formatString);

    unique_ptr<String> format = String::WrapPointer(formatString);

    static String pointerFormat = String::Wrap("x8");

    switch (formatSpecifier) {
        case ArgumentType_Pointer:
            sb.Append('0');
            sb.Append('x');
#ifdef CFLAT_UINTPTR
            UIntPtr::ToString(sb, reinterpret_cast<uintptr>(VarArg(*args, const void*)), &pointerFormat);
#else
            UIntMax::ToString(sb, (uintmax)(VarArg(*args, const void*)), &pointerFormat);
#endif
            break;

#ifdef CFLAT_INTPTR
        case ArgumentType_IntPtr:
            if (sizeof(intptr) < sizeof(int)) {
                IntPtr::ToString(sb, static_cast<intptr>(VarArg(*args, int)), format.Get());
            }
            else {
                IntPtr::ToString(sb, VarArg(*args, intptr), format.Get());
            }
            break;
#endif

#ifdef CFLAT_UINTPTR
        case ArgumentType_UIntPtr:
            if (sizeof(uintptr) < sizeof(uint)) {
                UIntPtr::ToString(sb, static_cast<uintptr>(VarArg(*args, uint)), format.Get());
            }
            else {
                UIntPtr::ToString(sb, VarArg(*args, uintptr), format.Get());
            }
            break;
#endif

        case ArgumentType_IntFSize:
            if (sizeof(intfsize) < sizeof(int)) {
                IntFSize::ToString(sb, static_cast<intfsize>(VarArg(*args, int)), format.Get());
            }
            else {
                IntFSize::ToString(sb, VarArg(*args, intfsize), format.Get());
            }
            break;

        case ArgumentType_UIntSize:
            if (sizeof(uintsize) < sizeof(uint)) {
                UIntSize::ToString(sb, static_cast<uintsize>(VarArg(*args, uint)), format.Get());
            }
            else {
                UIntSize::ToString(sb, VarArg(*args, uintsize), format.Get());
            }
            break;

        case ArgumentType_CString:
            sb.Append(VarArg(*args, const char*));
            break;

        case ArgumentType_String:
            sb.Append(*VarArg(*args, String*));
            break;

        case ArgumentType_Char:
            sb.Append(static_cast<char>(VarArg(*args, int)));
            break;

        case ArgumentType_SByte:
            SByte::ToString(sb, static_cast<sbyte>(VarArg(*args, int)), format.Get());
            break;

        case ArgumentType_Short:
            Short::ToString(sb, static_cast<short>(VarArg(*args, int)), format.Get());
            break;

        case ArgumentType_Int:
            Int::ToString(sb, VarArg(*args, int), format.Get());
            break;

        case ArgumentType_Long:
            Long::ToString(sb, VarArg(*args, long), format.Get());
            break;

        case ArgumentType_IntMax:
            IntMax::ToString(sb, VarArg(*args, intmax), format.Get());
            break;

        case ArgumentType_Byte:
            Byte::ToString(sb, static_cast<byte>(VarArg(*args, uint)), format.Get());
            break;

        case ArgumentType_UShort:
            UShort::ToString(sb, static_cast<ushort>(VarArg(*args, uint)), format.Get());
            break;

        case ArgumentType_UInt:
            UInt::ToString(sb, VarArg(*args, uint), format.Get());
            break;

        case ArgumentType_ULong:
            ULong::ToString(sb, VarArg(*args, ulong), format.Get());
            break;

        case ArgumentType_UIntMax:
            UIntMax::ToString(sb, VarArg(*args, uintmax), format.Get());
            break;

        case ArgumentType_Single:
            Float::ToString(sb, static_cast<float>(VarArg(*args, double)), format.Get());
            break;

        case ArgumentType_Double:
            Double::ToString(sb, VarArg(*args, double), format.Get());
            break;

        case ArgumentType_Bool:
            Bool::ToString(sb, VarArg(*args, int));
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
static ArgumentType ReadFormatItem(StringReader &reader, StringBuilder &formatBuffer, char **formatString)
{
    assert(formatString != nullptr);
    assert(reader.Peek() == '{');

    // Skip the '{' character.
    reader.Read();

    // Clear the string buffer.
    formatBuffer.Clear();

    // Indicates whether we're now reading in the format specifier part of the format item.
    bool inFormatSpecifier = false;

    // Read the format specifier.
    int ch;
    while ((ch = reader.Peek()) != -1) {
        if (ch == '{') {
            if (reader.Peek(1) == '{') {
                reader.Read();
            }
            else {
                break;
            }
        }
        else if (ch == '}') {
            // Do not escape '}}' unless reading a format specifier, since no valid format item contains '}'.
            if (!inFormatSpecifier) break;

            if (reader.Peek(1) == '}') {
                reader.Read();
            }
            else {
                break;
            }
        }
        else if (ch == ':') {
            inFormatSpecifier = true;
        }

        formatBuffer.Append((char)reader.Read());
    }

    // Check for invalid format.
    if (reader.Peek() != '}') {
        throw FormatException(String::Wrap("Invalid format string."));
    }

    // Skip the '}' character.
    reader.Read();

    // Prase the format item to find the type and format string.
    return ParseFormatItem(formatBuffer.GetData(), formatString);
}

/// <summary>
/// Parses the format item into the type and format string..
/// </summary>
/// <exception cref="::FormatException"><paramref name="formatItem"/> does not contain a known type.</exception>
static ArgumentType ParseFormatItem(char *formatItem, char **formatString)
{
    assert(formatItem != nullptr);
    assert(formatString != nullptr);

    uintsize index = CString::IndexOf(formatItem, ':');

    if (index == InvalidIndex) {
        *formatString = nullptr;
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
static ArgumentType ToArgumentType(const char *type)
{
    // TODO: Use a hashmap for lookup.
    if (CString::Equals(type, "pointer")) {
        return ArgumentType_Pointer;
    }
#ifdef CFLAT_INTPTR
    else if (CString::Equals(type, "intptr")) {
        return ArgumentType_IntPtr;
    }
#endif
#ifdef CFLAT_UINTPTR
    else if (CString::Equals(type, "uintptr")) {
        return ArgumentType_UIntPtr;
    }
#endif
    else if (CString::Equals(type, "intfsize")) {
        return ArgumentType_IntFSize;
    }
    else if (CString::Equals(type, "uintsize")) {
        return ArgumentType_UIntSize;
    }
    else if (CString::Equals(type, "string")) {
        return ArgumentType_String;
    }
    else if (CString::Equals(type, "cstring")) {
        return ArgumentType_CString;
    }
    else if (CString::Equals(type, "char")) {
        return ArgumentType_Char;
    }
    else if (CString::Equals(type, "int")) {
        return ArgumentType_Int;
    }
    else if (CString::Equals(type, "uint")) {
        return ArgumentType_UInt;
    }
    else if (CString::Equals(type, "long")) {
        return ArgumentType_Long;
    }
    else if (CString::Equals(type, "ulong")) {
        return ArgumentType_ULong;
    }
    else if (CString::Equals(type, "intmax")) {
        return ArgumentType_IntMax;
    }
    else if (CString::Equals(type, "uintmax")) {
        return ArgumentType_UIntMax;
    }
    else if (CString::Equals(type, "short")) {
        return ArgumentType_Short;
    }
    else if (CString::Equals(type, "ushort")) {
        return ArgumentType_UShort;
    }
    else if (CString::Equals(type, "sbyte")) {
        return ArgumentType_SByte;
    }
    else if (CString::Equals(type, "byte")) {
        return ArgumentType_Byte;
    }
    else if (CString::Equals(type, "float")) {
        return ArgumentType_Single;
    }
    else if (CString::Equals(type, "double")) {
        return ArgumentType_Double;
    }
    else if (CString::Equals(type, "bool")) {
        return ArgumentType_Bool;
    }
    else {
        throw FormatException(String::Wrap("Invalid format string."));
    }
}
