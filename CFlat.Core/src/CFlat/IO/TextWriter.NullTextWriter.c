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
#include "CFlat/Validate.h"

/* Macros */
/// <summary>
/// Initializer for a <see cref="TextWriter"/> with no backing store.
/// </summary>
#define NullTextWriter_Initializer()                                                \
{                                                                                   \
    CFLAT_CONST_OBJECT_INITIALIZER((const ObjectVTable*)&NullTextWriter_VTable),    \
    false                                                                           \
}

/**************************************/
/* Private functions                  */
/**************************************/

private override void NullTextWriter_Flush(TextWriter *writer);
private override void NullTextWriter_WriteBuffer(
    TextWriter *writer,
    const char *buffer,
    uintsize offset,
    uintsize count);

/* Private constants */
/// <summary>
/// The virtual method table for a <see cref="TextWriter"/> with no backing store.
/// </summary>
private const TextWriterVTable NullTextWriter_VTable = TextWriterVTable_Initializer(
    null,
    NullTextWriter_Flush,
    null,
    NullTextWriter_WriteBuffer);

/// <summary>
/// A <see cref="TextWriter"/> with no backing store.
/// </summary>
private TextWriter Null = NullTextWriter_Initializer();

/* Public constants */
/// <summary>
/// A <see cref="TextWriter"/> with no backing store.
/// </summary>
public TextWriter * const TextWriter_Null = &Null;

/**************************************/
/* Private function definitions       */
/**************************************/

private override void NullTextWriter_Flush(TextWriter *writer)
{
    Validate_NotNull(writer);
}

private override void NullTextWriter_WriteBuffer(
    TextWriter *writer,
    const char *buffer,
    uintsize offset,
    uintsize count)
{
    Validate_NotNull(writer);
    Validate_NotNull(buffer);

    (void)offset;
    (void)count;
}
