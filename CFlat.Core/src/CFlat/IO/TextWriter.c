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

#include "CFlat/IO/TextWriter.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"

/* Macros */
#define WriteWithStringBuilder(writer, bufferName, write)           \
{                                                                   \
    Validate_NotNull(writer);                                       \
                                                                    \
    StringBuilder __CFLAT_STRINGBUILDER_##__LINE__;                 \
    StringBuilder *bufferName = &__CFLAT_STRINGBUILDER_##__LINE__;  \
    StringBuilder_Constructor(bufferName);                          \
                                                                    \
    try {                                                           \
        write;                                                      \
                                                                    \
        WriteStringBuilder(writer, bufferName);                     \
    }                                                               \
    finally {                                                       \
        release(bufferName);                                        \
    }                                                               \
    endtry;                                                         \
}

/* Private constants */
/// <summary>
/// The default buffer capacity to use when copying a stream.
/// </summary>
private const uintsize DefaultBufferSize = 81920;

/* Private variables */
/// <summary>
/// The default string representation of a <see cref="TextWriter"/>.
/// </summary>
private String ClassName = String_Initializer("TextWriter");

 /**************************************/
/* Private functions                  */
/**************************************/

private void WriteStringBuilder(TextWriter *writer, const StringBuilder *sb);

private const TextWriterVTable *GetVTable(const TextWriter *writer);

/**************************************/
/* Public function definitions        */
/**************************************/

public void TextWriter_Constructor(TextWriter *writer, const TextWriterVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->WriteBuffer);

    Object_Constructor((Object*)writer, (const ObjectVTable*)vtable);

    writer->AutoFlush = false;
}

public bool TextWriter_GetAutoFlush(const TextWriter *writer)
{
    Validate_NotNull(writer);

    return writer->AutoFlush;
}

public void TextWriter_SetAutoFlush(TextWriter *writer, bool value)
{
    Validate_NotNull(writer);

    writer->AutoFlush = value;

    if (value) {
        TextWriter_Flush(writer);
    }
}

public virtual void TextWriter_Flush(TextWriter *writer)
{
    TextWriter_FlushFunc flush = GetVTable(writer)->Flush;

    if (flush != null)
        flush(writer);
}

public virtual String *TextWriter_ToString(const TextWriter *writer)
{
    TextWriter_ToStringFunc toString = GetVTable(writer)->ToString;

    if (toString != null) {
        return toString(writer);
    }
    else {
        return &ClassName;
    }
}

public abstract void TextWriter_WriteBuffer(TextWriter *writer, const char *buffer, uintsize offset, uintsize count)
{
    GetVTable(writer)->WriteBuffer(writer, buffer, offset, count);

    if (writer->AutoFlush) {
        TextWriter_Flush(writer);
    }
}

public void TextWriter_Write(TextWriter *writer, char value)
{
    TextWriter_WriteBuffer(writer, &value, 0, 1);
}

public void TextWriter_Write_CString(TextWriter *writer, const char *value)
{
    Validate_NotNull(writer);

    if (value == null) return;

    TextWriter_WriteBuffer(writer, value, 0, CString_Length(value));
}

public void TextWriter_Write_String(TextWriter *writer, const String *value)
{
    Validate_NotNull(writer);

    if (value == null) return;

    TextWriter_WriteBuffer(writer, String_GetCString(value), 0, String_GetLength(value));
}

public void TextWriter_WriteFormat_CString(TextWriter *writer, const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    TextWriter_WriteFormat_CStringV(writer, format, args);

    VarArgs_End(args);
}

public void TextWriter_WriteFormat_CStringV(TextWriter *writer, const char *format, VarArgsList args)
{
    Validate_NotNull(format);

    WriteWithStringBuilder(writer, sb, {
        StringBuilder_AppendFormatCStringV(sb, format, args);
    });
}

public void TextWriter_WriteFormat_String(TextWriter *writer, const String *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    TextWriter_WriteFormat_StringV(writer, format, args);

    VarArgs_End(args);
}

public void TextWriter_WriteFormat_StringV(TextWriter *writer, const String *format, VarArgsList args)
{
    Validate_NotNull(format);

    WriteWithStringBuilder(writer, sb, {
        StringBuilder_AppendFormatStringV(sb, format, args);
    });
}

public void TextWriter_WriteLine(TextWriter *writer)
{
    TextWriter_Write(writer, '\n');
}

public void TextWriter_WriteLine_CString(TextWriter *writer, const char *value)
{
    TextWriter_Write_CString(writer, value);
    TextWriter_WriteLine(writer);
}

public void TextWriter_WriteLine_String(TextWriter *writer, const String *value)
{
    TextWriter_Write_String(writer, value);
    TextWriter_WriteLine(writer);
}

public void TextWriter_WriteLineFormat_CString(TextWriter *writer, const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    TextWriter_WriteLineFormat_CStringV(writer, format, args);

    VarArgs_End(args);
}

public void TextWriter_WriteLineFormat_CStringV(TextWriter *writer, const char *format, VarArgsList args)
{
    Validate_NotNull(format);

    WriteWithStringBuilder(writer, sb, {
        StringBuilder_AppendFormatCStringV(sb, format, args);
        StringBuilder_Append(sb, '\n');
    });
}

public void TextWriter_WriteLineFormat_String(TextWriter *writer, const String *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    TextWriter_WriteLineFormat_StringV(writer, format, args);

    VarArgs_End(args);
}

public void TextWriter_WriteLineFormat_StringV(TextWriter *writer, const String *format, VarArgsList args)
{
    Validate_NotNull(format);

    WriteWithStringBuilder(writer, sb, {
        StringBuilder_AppendFormatStringV(sb, format, args);
        StringBuilder_Append(sb, '\n');
    });
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void WriteStringBuilder(TextWriter *writer, const StringBuilder *sb)
{
    assert(writer != null);
    assert(sb != null);

    TextWriter_WriteBuffer(writer, StringBuilder_GetBuffer(sb), 0, StringBuilder_GetLength(sb));
}

/// <summary>
/// Gets the virtual method table of a <see cref="TextWriter"/>.
/// </summary>
/// <param name="stream">Pointer to a <see cref="TextWriter"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
private const TextWriterVTable *GetVTable(const TextWriter *writer)
{
    Validate_NotNull(writer);

    return (const TextWriterVTable*)((const Object*)writer)->VTable;
}
