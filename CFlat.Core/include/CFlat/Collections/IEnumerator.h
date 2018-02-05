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

//! @file IEnumerator.h

#ifndef CFLAT_CORE_COLLECTIONS_IENUMERATOR_H
#define CFLAT_CORE_COLLECTIONS_IENUMERATOR_H

namespace CFlat {
    /// <summary>
    /// Supports a simple iteration over a collection of elements.
    /// </summary>
    template <typename T>
    class IEnumerator {
    public:
        inline virtual ~IEnumerator() {}

        /// <summary>
        /// Returns the element at the current position in the collection of an <see cref="IEnumerator"/>.
        /// </summary>
        /// <remarks>
        ///     If the collection contains value types, the returned pointer shall no longer be dereferenced after the first
        ///     call to a function that modifies the collection.
        /// </remarks>
        /// <returns>A pointer to the current element.</returns>
        /// <exception cref="::InvalidOperationException">
        ///     The collection was modified during enumeration <b>-or-</b>
        ///     The enumeration has either not started or has already finished.
        /// </exception>
        virtual const T &GetCurrent() const = 0;

        /// <summary>
        /// Moves an <see cref="IEnumerator"/> to the next element in the collection
        /// </summary>
        /// <returns>
        ///     <see cref="true"/> if the enumerator was successfully advanced to the next element;
        ///     <see cref="false"/> if the enumerator passed the end of the collection.
        /// </returns>
        /// <exception cref="::InvalidOperationException">The collection was modified during enumeration.</exception>
        virtual bool MoveNext() = 0;

        /// <summary>
        /// Resets an <see cref="IEnumerator"/> to its initial position, which is before the first element in the
        /// collection.
        /// </summary>
        /// <exception cref="::InvalidOperationException">The collection was modified during enumeration.</exception>
        virtual void Reset() = 0;
    };
}

#endif
