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

#include "CFlat/IO/StringReader.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="StringReader"/> class.
/// </summary>
private const TextReaderVTable VTable = TextReaderVTable_Initializer(
    (DestructorFunc)StringReader_Destructor,
    (TextReader_PeekFunc)StringReader_Peek,
    (TextReader_ReadFunc)StringReader_Read,
    (TextReader_ReadBufferFunc)StringReader_ReadBuffer);

/**************************************/
/* Public function definitions        */
/**************************************/

public StringReader *StringReader_New(const String *str)
{
    Validate_NotNull(str);

    StringReader *reader = Memory_Allocate(sizeof(StringReader));

    try {
        StringReader_Constructor(reader, str);

        Object_SetDeallocator(reader, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(reader);
        throw;
    }
    endtry;

    return reader;
}

public void StringReader_Constructor(StringReader *reader, const String *str)
{
    Validate_NotNull(str);

    TextReader_Constructor((TextReader*)reader, &VTable);

    reader->Value = retain_const(str);
    reader->Position = 0;
}

public void StringReader_Destructor(StringReader *reader)
{
    Validate_NotNull(reader);

    release(reader->Value);
}

public override int StringReader_Peek(const StringReader *reader)
{
    return StringReader_PeekOffset(reader, 0);
}

public int StringReader_PeekOffset(const StringReader *reader, uintsize offset)
{
    Validate_NotNull(reader);

    if (reader->Position + offset >= String_GetLength(reader->Value)) {
        return -1;
    }
    else {
        return String_GetCharAt(reader->Value, reader->Position + offset);
    }
}

public override int StringReader_Read(StringReader *reader)
{
    Validate_NotNull(reader);

    if (reader->Position >= String_GetLength(reader->Value)) {
        return -1;
    }
    else {
        return String_GetCharAt(reader->Value, reader->Position++);
    }
}

public override uintsize StringReader_ReadBuffer(StringReader *reader, char *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(reader);
    Validate_NotNull(buffer);

    if (count == 0) return 0;

    // The number of characters read.
    uintsize charactersRead = 0;

    // The number of characters remaining.
    uintsize remaining = String_GetLength(reader->Value) - reader->Position;

    if (remaining > 0) {
        charactersRead = uintsize_Min(remaining, count);

        Memory_CopyOffset(String_GetCString(reader->Value), reader->Position, buffer, offset, charactersRead);

        reader->Position += charactersRead;
    }

    return charactersRead;
}

public String *StringReader_ReadLine(StringReader *reader)
{
    return TextReader_ReadLine((TextReader*)reader);
}

public String *StringReader_ReadToEnd(StringReader *reader)
{
    return TextReader_ReadToEnd((TextReader*)reader);
}

public void StringReader_Skip(StringReader *reader, uintsize amount)
{
    Validate_NotNull(reader);

    uintsize length = String_GetLength(reader->Value);

    if (reader->Position + amount >= length) {
        reader->Position = length;
    }
    else {
        reader->Position += amount;
    }
}
