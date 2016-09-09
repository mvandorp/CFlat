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
#include "CFlat/Validate.h"

/* Macros */
/// <summary>
/// Initializer for a <see cref="TextReader"/> with no backing store.
/// </summary>
#define NullTextReader_Initializer() { Object_const_Initializer((const ObjectVTable*)&NullTextReader_VTable) }

/**************************************/
/* Private functions                  */
/**************************************/

private abstract int NullTextReader_Peek(TextReader *reader);
private abstract int NullTextReader_Read(TextReader *reader);
private abstract uintsize NullTextReader_ReadBuffer(TextReader *reader, char *buffer, uintsize offset, uintsize count);

/* Private constants */
/// <summary>
/// The virtual method table for a <see cref="TextReader"/> with no backing store.
/// </summary>
private const TextReaderVTable NullTextReader_VTable = TextReaderVTable_Initializer(
    null,
    NullTextReader_Peek,
    NullTextReader_Read,
    NullTextReader_ReadBuffer);

/// <summary>
/// A <see cref="TextReader"/> with no backing store.
/// </summary>
private TextReader Null = NullTextReader_Initializer();

/* Public constants */
/// <summary>
/// A <see cref="TextReader"/> with no backing store.
/// </summary>
public TextReader * const TextReader_Null = &Null;

/**************************************/
/* Private function definitions       */
/**************************************/

private abstract int NullTextReader_Peek(TextReader *reader)
{
    Validate_NotNull(reader);

    return -1;
}

private abstract int NullTextReader_Read(TextReader *reader)
{
    Validate_NotNull(reader);

    return -1;
}

private abstract uintsize NullTextReader_ReadBuffer(TextReader *reader, char *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(reader);
    Validate_NotNull(buffer);

    (void)offset;
    (void)count;

    return 0;
}
