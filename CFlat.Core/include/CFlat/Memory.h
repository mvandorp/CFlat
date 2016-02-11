/// @file Memory.h
/// @author Martijn van Dorp
/// @date August 2015

#ifndef CFLAT_CORE_MEMORY_H
#define CFLAT_CORE_MEMORY_H

#include "CFlat.h"

/// <summary>
/// Allocates <paramref name="size"/> bytes of uninitialized memory.
///
/// If <paramref name="size"/> is zero, <see cref="null"/> is returned.
/// </summary>
/// <param name="size">The number of bytes of memory to allocate.</param>
/// <returns>
/// On success, returns the pointer to the newly allocated memory. The returned pointer must be deallocated with
/// Memory_Deallocate() or Memory_Reallocate().
/// 
/// On failure, returns <see cref="null"/>.
/// </returns>
/// <seealso cref="Memory_AllocateZeroed()"/>
/// <seealso cref="Memory_Deallocate()"/>
/// <seealso cref="Memory_Reallocate()"/>
void *Memory_Allocate(uintsize size);

/// <summary>
/// Allocates <paramref name="size"/> bytes of memory and initializes all its bits to zero.
///
/// If <paramref name="size"/> is zero, <see cref="null"/> is returned.
/// </summary>
/// <param name="size">The number of bytes of memory to allocate.</param>
/// <returns>
/// On success, returns the pointer to the newly allocated memory. The returned pointer must be deallocated with
/// Memory_Deallocate() or Memory_Reallocate().
/// 
/// On failure, returns <see cref="null"/>.
/// </returns>
/// <seealso cref="Memory_Allocate()"/>
/// <seealso cref="Memory_Deallocate()"/>
/// <seealso cref="Memory_Reallocate()"/>
void *Memory_AllocateZeroed(uintsize size);

/// <summary>
/// Deallocates memory previously allocated by Memory_Allocate(), Memory_AllocateZeroed() or Memory_Reallocate().
/// 
/// If <paramref name="memory"/> is <see cref="null"/>, the function does nothing.
/// 
/// The behaviour is undefined if the memory pointed to by <paramref name="memory"/> has already been deallocated by
/// Memory_Deallocate() or Memory_Reallocate().
/// </summary>
/// <param name="memory">Pointer to the memory to free.</param>
/// <seealso cref="Memory_Allocate()"/>
/// <seealso cref="Memory_AllocateZeroed()"/>
/// <seealso cref="Memory_Reallocate()"/>
void Memory_Deallocate(void *memory);

/// <summary>
/// Reallocates memory previously allocated by Memory_Allocate(), Memory_AllocateZeroed() or Memory_Reallocate() so
/// that it is <paramref name="newSize"/> bytes long.
/// 
/// The reallocation is achieved through either:
/// <list>
/// <item>
/// <description>
/// growing or shrinking the existing memory block pointed to by <paramref name="memory"/>, in which case
/// <paramref name="memory"/> is returned. The contents of the memory block remain unchanged up to the lesser of the
/// new and old sizes.
/// </description>
/// </item>
/// <item>
/// <description>
/// allocating a new block of memory of <paramref name="newSize"/> bytes, copying the contents of the old memory block
/// up to the lesser of the new and old sizes, and freeing the old memory block, in which case the pointer to the newly
/// allocated memory is returned.
/// </description>
/// </item>
/// </list>
/// 
/// If <paramref name="newSize"/> is greater than the old size, the newly allocated portion of the memory block remains
/// uninitialized.
/// 
/// If memory allocation fails, the old memory block is not freed and <see cref="null"/> is returned.
/// 
/// If <paramref name="memory"/> is <see cref="null"/>, the behaviour is the same as calling
/// <c>Memory_Allocate(newSize)</c>.
///
/// If <paramref name="newSize"/> is zero, the behaviour is the same as calling <c>Memory_Deallocate(memory)</c>, and
/// <see cref="null"/> is returned.
/// 
/// The behaviour is undefined if the memory pointed to by <paramref name="memory"/> has been deallocated by
/// Memory_Deallocate() or Memory_Reallocate().
/// </summary>
/// <param name="memory">Pointer to the memory to reallocate.</param>
/// <param name="newSize">The new number of bytes of memory to allocate.</param>
/// <returns>
/// On success, returns the pointer to the reallocated memory, which may be the same are <paramref name="memory"/> or a
/// different value. The returned pointer must be deallocated with Memory_Deallocate() or Memory_Reallocate().
/// 
/// On failure, returns <see cref="null"/>.
/// </returns>
/// <seealso cref="Memory_Allocate()"/>
/// <seealso cref="Memory_AllocateZeroed()"/>
/// <seealso cref="Memory_Deallocate()"/>
void *Memory_Reallocate(void* memory, uintsize newSize);

/// <summary>
/// Copies <paramref name="length"/> bytes from the memory block pointed to by the <paramref name="source"/> pointer to
/// the memory block pointed to by <paramref name="destination"/> pointer.
/// </summary>
/// <param name="source">Pointer to the data to be copied.</param>
/// <param name="destination">Pointer to a location where the data should be copied to.</param>
/// <param name="length">The number of bytes to copy.</param>
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
void Memory_CopyOffset(
    const void *source,
    uintsize sourceOffset, 
    void *destination,
    uintsize destinationOffset, 
    uintsize length);

#endif
