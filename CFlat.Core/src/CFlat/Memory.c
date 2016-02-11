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

#include <stdlib.h>
#include <string.h>

void *Memory_Allocate(uintsize size)
{
    if (size == 0) {
        return null;
    }

    void *memory = malloc(size);

    // TODO: If the allocation failed, throw an OutOfMemoryException.
    assert(memory != null);

    return memory;
}

void *Memory_AllocateZeroed(uintsize size)
{
    if (size == 0) {
        return null;
    }

    void *memory = calloc(1, size);

    // TODO: If the allocation failed, throw an OutOfMemoryException.
    assert(memory != null);

    return memory;
}

void Memory_Deallocate(void *memory)
{
    free(memory);
}

void *Memory_Reallocate(void *memory, uintsize newSize)
{
    if (newSize == 0) {
        Memory_Deallocate(memory);

        return null;
    }

    memory = realloc(memory, newSize);

    // TODO: If the allocation failed, throw an OutOfMemoryException.
    assert(memory != null);

    return memory;
}

void Memory_Copy(const void *source, void *destination, uintsize length)
{
    // TODO: If source or destination is null, throw an ArgumentNullException.
    assert(source != null);
    assert(destination != null);

    memmove(destination, source, length);
}

void Memory_CopyOffset(
    const void *source,
    uintsize sourceOffset,
    void *destination,
    uintsize destinationOffset,
    uintsize length)
{
    // TODO: If source or destination is null, throw an ArgumentNullException.
    assert(source != null);
    assert(destination != null);

    const byte *src = (const byte*)source + sourceOffset;
    byte *dest = (byte*)destination + destinationOffset;

    memmove(dest, src, length);
}
