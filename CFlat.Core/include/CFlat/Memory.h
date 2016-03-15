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

//! @file Memory.h

#ifndef CFLAT_CORE_MEMORY_H
#define CFLAT_CORE_MEMORY_H

#include "CFlat/Language/Integer.h"

/// <summary>
/// Allocates <paramref name="size"/> bytes of uninitialized memory.
/// </summary>
/// <remarks>
///     If <paramref name="size"/> is zero, <see cref="null"/> is returned.
/// </remarks>
/// <param name="size">The number of bytes of memory to allocate.</param>
/// <returns>
///     Returns the pointer to the newly allocated memory. The returned pointer must be deallocated with
///     Memory_Deallocate() or Memory_Reallocate().
/// </returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
/// <seealso cref="Memory_AllocateZeroed()"/>
/// <seealso cref="Memory_Deallocate()"/>
/// <seealso cref="Memory_Reallocate()"/>
void *Memory_Allocate(uintsize size);

/// <summary>
/// Allocates <paramref name="size"/> bytes of memory and initializes all its bits to zero.
/// </summary>
/// <remarks>
///     If <paramref name="size"/> is zero, <see cref="null"/> is returned.
/// </remarks>
/// <param name="size">The number of bytes of memory to allocate.</param>
/// <returns>
///     Returns the pointer to the newly allocated memory. The returned pointer must be deallocated with
///     Memory_Deallocate() or Memory_Reallocate().
/// </returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
/// <seealso cref="Memory_Allocate()"/>
/// <seealso cref="Memory_Deallocate()"/>
/// <seealso cref="Memory_Reallocate()"/>
void *Memory_AllocateZeroed(uintsize size);

/// <summary>
/// Deallocates memory previously allocated by Memory_Allocate(), Memory_AllocateZeroed() or Memory_Reallocate().
/// </summary>
/// <remarks>
///     If <paramref name="memory"/> is <see cref="null"/>, the function does nothing.
///
///     The behaviour is undefined if the memory pointed to by <paramref name="memory"/> has already been deallocated by
///     Memory_Deallocate() or Memory_Reallocate().
/// </remarks>
/// <param name="memory">Pointer to the memory to free.</param>
/// <seealso cref="Memory_Allocate()"/>
/// <seealso cref="Memory_AllocateZeroed()"/>
/// <seealso cref="Memory_Reallocate()"/>
void Memory_Deallocate(const void *memory);

/// <summary>
/// Reallocates memory previously allocated by Memory_Allocate(), Memory_AllocateZeroed() or Memory_Reallocate() so
/// that it is <paramref name="newSize"/> bytes long.
/// </summary>
/// <remarks>
///     The reallocation is achieved through either:
///     <list>
///         <item>
///             <description>
///                 growing or shrinking the existing memory block pointed to by <paramref name="memory"/>, in which
///                 case <paramref name="memory"/> is returned. The contents of the memory block remain unchanged up to
///                 the lesser of the new and old sizes.
///             </description>
///         </item>
///         <item>
///             <description>
///                 allocating a new block of memory of <paramref name="newSize"/> bytes, copying the contents of the
///                 old memory block up to the lesser of the new and old sizes, and freeing the old memory block, in
///                 which case the pointer to the newly allocated memory is returned.
///             </description>
///         </item>
///     </list>
///
///     If <paramref name="newSize"/> is greater than the old size, the newly allocated portion of the memory block
///     remains uninitialized.
///
///     If memory allocation fails, the old memory block is not freed and an <see cref="OutOfMemoryException"/> is
///     thrown.
///
///     If <paramref name="memory"/> is <see cref="null"/>, the behaviour is the same as calling
///     <c>Memory_Allocate(newSize)</c>.
///
///     If <paramref name="newSize"/> is zero, the behaviour is the same as calling <c>Memory_Deallocate(memory)</c>,
///     and <see cref="null"/> is returned.
///
///     The behaviour is undefined if the memory pointed to by <paramref name="memory"/> has been deallocated by
///     Memory_Deallocate() or Memory_Reallocate().
/// </remarks>
/// <param name="memory">Pointer to the memory to reallocate.</param>
/// <param name="newSize">The new number of bytes of memory to allocate.</param>
/// <returns>
///     Returns the pointer to the reallocated memory, which may be the same are <paramref name="memory"/> or a
///     different value. The returned pointer must be deallocated with Memory_Deallocate() or Memory_Reallocate().
/// </returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
/// <seealso cref="Memory_Allocate()"/>
/// <seealso cref="Memory_AllocateZeroed()"/>
/// <seealso cref="Memory_Deallocate()"/>
void *Memory_Reallocate(void* memory, uintsize newSize);

/// <summary>
/// Reallocates memory previously allocated by Memory_Allocate(), Memory_AllocateZeroed() or Memory_Reallocate() so
/// that it is <paramref name="newSize"/> bytes long.
/// </summary>
/// <param name="memory">Pointer to the memory to reallocate.</param>
/// <param name="newSize">The new number of bytes of memory to allocate.</param>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
/// <seealso cref="Memory_Reallocate()"/>
const void *Memory_ReallocateConst(const void* memory, uintsize newSize);

/// <summary>
/// Copies <paramref name="length"/> bytes from the memory block pointed to by the <paramref name="source"/> pointer to
/// the memory block pointed to by <paramref name="destination"/> pointer.
/// </summary>
/// <param name="source">Pointer to the data to be copied.</param>
/// <param name="destination">Pointer to a location where the data should be copied to.</param>
/// <param name="length">The number of bytes to copy.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="source"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
void Memory_Copy(const void *source, void *destination, uintsize length);

/// <summary>
/// Copies <paramref name="length"/> bytes from the memory block pointed to by the <paramref name="source"/> pointer to
/// the memory block pointed to by <paramref name="destination"/> pointer, starting at the given offset within both
/// blocks.
/// </summary>
/// <param name="source">Pointer to the data to be copied.</param>
/// <param name="sourceOffset">The offset in bytes into <paramref name="source"/>.</param>
/// <param name="destination">Pointer to a location where the data should be copied to.</param>
/// <param name="destinationOffset">The offset in bytes into <paramref name="destination"/>.</param>
/// <param name="length">The number of bytes to copy.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="source"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="destination"/> is <see cref="null"/>.
/// </exception>
void Memory_CopyOffset(
    const void *source,
    uintsize sourceOffset,
    void *destination,
    uintsize destinationOffset,
    uintsize length);

#endif
