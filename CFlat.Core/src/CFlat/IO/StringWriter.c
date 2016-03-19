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

#include "CFlat/IO/StringWriter.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/TextWriter.h"

/* Types */
struct StringWriter {
    TextWriter Base;
    StringBuilder *StringBuilder;
};

/**************************************/
/* Private functions                  */
/**************************************/

private void StringWriter_Constructor(StringWriter *writer);
private void StringWriter_Destructor(StringWriter *writer);

private override void StringWriter_Flush(StringWriter *writer);
private override String *StringWriter_ToString(const StringWriter *writer);
private override void StringWriter_WriteBuffer(
    StringWriter *writer,
    const char *buffer,
    uintsize offset,
    uintsize count);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="ConsoleStream"/> class.
/// </summary>
private const TextWriterVTable VTable = TextWriterVTable_Initializer(
    (DestructorFunc)StringWriter_Destructor,
    (TextWriter_FlushFunc)StringWriter_Flush,
    (TextWriter_ToStringFunc)StringWriter_ToString,
    (TextWriter_WriteBufferFunc)StringWriter_WriteBuffer);

/// <summary>
/// The virtual method table for the <see cref="StringWriter"/> class, without a destructor set so that the internal
/// string builder is not automatically destroyed.
/// </summary>
private const TextWriterVTable VTableNoDestructor = TextWriterVTable_Initializer(
    null,
    (TextWriter_FlushFunc)StringWriter_Flush,
    (TextWriter_ToStringFunc)StringWriter_ToString,
    (TextWriter_WriteBufferFunc)StringWriter_WriteBuffer);

/**************************************/
/* Public function definitions        */
/**************************************/

public TextWriter *StringWriter_New(void)
{
    StringWriter *writer = Memory_Allocate(sizeof(StringWriter));

    try {
        StringWriter_Constructor(writer);

        Object_SetDeallocator(writer, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(writer);
        throw;
    }
    endtry;

    return (TextWriter*)writer;
}

public String *StringWriter_DeleteAndToString(StringWriter *writer)
{
    Validate_NotNull(writer);

    StringBuilder *buffer = writer->StringBuilder;

    // Prevent the destructor from being invoked so that the buffer remains valid.
    Object_SetVTable(writer, (const ObjectVTable*)&VTableNoDestructor);

    // If the StringWriter was not deleted as a result of release(), throw an InvalidOperationException.
    if (!release(writer)) {
        Object_SetVTable(writer, (const ObjectVTable*)&VTable);
        retain(writer);

        throw_new(
            InvalidOperationException,
            "Could not delete the object because there are still references to the object.");
    }

    return StringBuilder_DeleteAndToString(buffer);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void StringWriter_Constructor(StringWriter *writer)
{
    TextWriter_Constructor((TextWriter*)writer, &VTable);

    writer->StringBuilder = StringBuilder_New_WithCapacity(4096);
}

private void StringWriter_Destructor(StringWriter *writer)
{
    Validate_NotNull(writer);

    release(writer->StringBuilder);
}

private override void StringWriter_Flush(StringWriter *writer)
{
    Validate_NotNull(writer);
}

private override String *StringWriter_ToString(const StringWriter *writer)
{
    Validate_NotNull(writer);

    return StringBuilder_ToString(writer->StringBuilder);
}

private override void StringWriter_WriteBuffer(
    StringWriter *writer,
    const char *buffer,
    uintsize offset,
    uintsize count)
{
    Validate_NotNull(writer);
    Validate_NotNull(buffer);

    StringBuilder_AppendBuffer(writer->StringBuilder, buffer, offset, count);
}
