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

#include "CFlat/IO/TextReader.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/StringWriter.h"
#include "CFlat/IO/TextWriter.h"

/* Private constants */
/// <summary>
/// The default buffer capacity to use when reading.
/// </summary>
private const uintsize DefaultBufferSize = 4096;

 /**************************************/
/* Private functions                  */
/**************************************/

private const TextReaderVTable *GetVTable(const TextReader *reader);

/**************************************/
/* Public function definitions        */
/**************************************/

public void TextReader_Constructor(TextReader *reader, const TextReaderVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->ReadBuffer);

    Object_Constructor((Object*)reader, (const ObjectVTable*)vtable);
}

public abstract int TextReader_Peek(TextReader *reader)
{
    return GetVTable(reader)->Peek(reader);
}

public abstract int TextReader_Read(TextReader *reader)
{
    return GetVTable(reader)->Read(reader);
}

public abstract uintsize TextReader_ReadBuffer(TextReader *reader, char *buffer, uintsize offset, uintsize count)
{
    return GetVTable(reader)->ReadBuffer(reader, buffer, offset, count);
}

public String *TextReader_ReadLine(TextReader *reader)
{
    Validate_NotNull(reader);

    // If we reached the end of the stream, return null.
    if (TextReader_Peek(reader) == -1) return null;

    StringBuilder sb;
    StringBuilder_Constructor(&sb);
    String *result = null;

    try {
        while (true) {
            int ch = TextReader_Read(reader);

            // Deal with CR+LF line endings.
            if (ch == '\r' && TextReader_Peek(reader) == '\n') {
                TextReader_Read(reader);
                break;
            }

            if (ch == -1 || ch == '\r' || ch == '\n') break;

            StringBuilder_Append(&sb, (char)ch);
        }

        result = StringBuilder_DeleteAndToString(&sb);
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

public String *TextReader_ReadToEnd(TextReader *reader)
{
    Validate_NotNull(reader);

    String *result = null;
    StringBuilder sb;
    StringBuilder_Constructor(&sb);

    try {
        char *buffer = Memory_Allocate(DefaultBufferSize);

        try {
            uintsize bytesRead;

            while ((bytesRead = TextReader_ReadBuffer(reader, buffer, 0, DefaultBufferSize)) != 0) {
                StringBuilder_AppendBuffer(&sb, buffer, 0, bytesRead);
            }

            result = StringBuilder_DeleteAndToString(&sb);
        }
        finally {
            release(buffer);
        }
        endtry;
    }
    catch (Exception) {
        release(&sb);
        throw;
    }
    endtry;

    return result;
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of a <see cref="TextReader"/>.
/// </summary>
/// <param name="stream">Pointer to a <see cref="TextReader"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
private const TextReaderVTable *GetVTable(const TextReader *reader)
{
    Validate_NotNull(reader);

    return (const TextReaderVTable*)((const Object*)reader)->VTable;
}
