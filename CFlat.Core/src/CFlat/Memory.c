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
#include "CFlat/Validate.h"

#include <stdlib.h>
#include <string.h>

public void *Memory_Allocate(uintsize size)
{
    if (size == 0) {
        return null;
    }

    void *memory = malloc(size);

    // If the allocation failed, throw an OutOfMemoryException.
    Validate_IsTrue(memory != null, OutOfMemoryException, null);

    return memory;
}

public void *Memory_AllocateZeroed(uintsize size)
{
    if (size == 0) {
        return null;
    }

    void *memory = calloc(1, size);

    // If the allocation failed, throw an OutOfMemoryException.
    Validate_IsTrue(memory != null, OutOfMemoryException, null);

    return memory;
}

public void Memory_Deallocate(void *memory)
{
    free(memory);
}

public void *Memory_Reallocate(void *memory, uintsize newSize)
{
    if (newSize == 0) {
        Memory_Deallocate(memory);

        return null;
    }

    memory = realloc(memory, newSize);

    // If the allocation failed, throw an OutOfMemoryException.
    Validate_IsTrue(memory != null, OutOfMemoryException, null);

    return memory;
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
