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

#include "CFlat/Memory.h"

#include "CFlat.h"
#include "CFlat/const_cast.h"
#include "CFlat/CFlatException.h"
#include "CFlat/Validate.h"

#include <stdlib.h>
#include <string.h>

/* Macros */
/// <summary>
/// Throws a buffered <see cref="CFlatException"/> of the given type.
/// </summary>
/// <param name="buffer">The buffer to use for the exception.</param>
/// <param name="type">The type of exception thrown.</param>
#define ThrowBufferedException(buffer, type)                                    \
    do {                                                                        \
        Exception_Constructor(buffer, type, null, __FILE__, __LINE__, null);    \
                                                                                \
        throw_ex(buffer);                                                       \
    }                                                                           \
    while (false)

/* Private variables */
/// <summary>
/// A buffer for exceptions so that an <see cref="OutOfMemoryException"/> can still be thrown when the system is out of
/// memory.
/// </summary>
private CFlatException ExceptionBuffer[3];

/**************************************/
/* Public function definitions        */
/**************************************/

public void *Memory_Allocate(uintsize size)
{
    if (size == 0) {
        return null;
    }

    void *memory = malloc(size);

    // If the allocation failed, throw an OutOfMemoryException.
    if (memory == null) ThrowBufferedException(&ExceptionBuffer[0], OutOfMemoryException);

    return memory;
}

public void *Memory_AllocateZeroed(uintsize size)
{
    if (size == 0) {
        return null;
    }

    void *memory = calloc(1, size);

    // If the allocation failed, throw an OutOfMemoryException.
    if (memory == null) ThrowBufferedException(&ExceptionBuffer[1], OutOfMemoryException);

    return memory;
}

public void Memory_Deallocate(const void *memory)
{
    free(const_cast(memory));
}

public void *Memory_Reallocate(void *memory, uintsize newSize)
{
    if (newSize == 0) {
        Memory_Deallocate(memory);

        return null;
    }

    memory = realloc(memory, newSize);

    // If the allocation failed, throw an OutOfMemoryException.
    if (memory == null) ThrowBufferedException(&ExceptionBuffer[2], OutOfMemoryException);

    return memory;
}

public const void *Memory_ReallocateConst(const void *memory, uintsize newSize)
{
    return Memory_Reallocate(const_cast(memory), newSize);
}

public void Memory_Copy(const void *source, void *destination, uintsize length)
{
    Validate_NotNull(source);
    Validate_NotNull(destination);

    memmove(destination, source, length);
}

public void Memory_CopyOffset(
    const void *source,
    uintsize sourceOffset,
    void *destination,
    uintsize destinationOffset,
    uintsize length)
{
    Validate_NotNull(source);
    Validate_NotNull(destination);

    const byte *src = (const byte*)source + sourceOffset;
    byte *dest = (byte*)destination + destinationOffset;

    memmove(dest, src, length);
}
