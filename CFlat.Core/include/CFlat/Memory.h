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
#include "CFlat/Language/Pointers.h"

#include "CFlat/ExceptionType.h"

#include <cstring>

namespace CFlat {
    class Memory {
    public:
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
        template <typename T>
        static inline void Copy(const T *source, T *destination, uintsize length)
        {
            std::memmove(destination, source, length);
        }

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
        template <typename T>
        static inline void Copy(
            const T *source,
            uintsize sourceOffset,
            T *destination,
            uintsize destinationOffset,
            uintsize length)
        {
            const byte *src = reinterpret_cast<const byte*>(source) + sourceOffset;
            byte *dest = reinterpret_cast<byte*>(destination) + destinationOffset;

            std::memmove(dest, src, length);
        }

        /// <summary>
        /// Sets the first <paramref name="length"/> bytes of the memory block pointed to by <paramref name="memory"/> to zero.
        /// </summary>
        /// <param name="memory">Pointer to the memory to be zeroed.</param>
        /// <param name="length">The number of bytes to zero.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="memory"/> is <see cref="null"/>.</exception>
        template <typename T>
        static inline void Zero(T *memory, uintsize length)
        {
            std::memset(memory, 0, length);
        }
    };
}

#endif
