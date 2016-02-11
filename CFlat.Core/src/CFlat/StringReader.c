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

#include "CFlat/StringReader.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

/**************************************/
/* Extern function definitions        */
/**************************************/

StringReader *StringReader_New(const String *str)
{
    Validate_NotNull(str);

    // Allocate a new string reader and set the destructor callback.
    StringReader *reader = Memory_Allocate(sizeof(StringReader));

    // Initialize the string reader with the given string.
    StringReader_Constructor(reader, str);

    // Set the proper deallocator that corresponds with the allocator.
    Object_SetDeallocator(reader, Memory_Deallocate);

    return reader;
}

void StringReader_Constructor(StringReader *reader, const String *str)
{
    Validate_NotNull(reader);
    Validate_NotNull(str);

    Object_Constructor(reader, StringReader_Destructor);

    reader->Value = Object_Aquire(str);
    reader->Position = 0;
}

void StringReader_Destructor(void *reader)
{
    Validate_NotNull(reader);

    StringReader *stringReader = (StringReader*)reader;

    Object_Release(stringReader->Value);
}

int StringReader_Peek(const StringReader *reader)
{
    return StringReader_PeekOffset(reader, 0);
}

int StringReader_PeekOffset(const StringReader *reader, uintsize offset)
{
    Validate_NotNull(reader);

    if (reader->Position + offset >= String_GetLength(reader->Value)) {
        return -1;
    }
    else {
        return String_GetCharAt(reader->Value, reader->Position + offset);
    }
}

int StringReader_Read(StringReader *reader)
{
    Validate_NotNull(reader);

    if (reader->Position >= String_GetLength(reader->Value)) {
        return -1;
    }
    else {
        return String_GetCharAt(reader->Value, reader->Position++);
    }
}

void StringReader_Skip(StringReader *reader, uintsize amount)
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
