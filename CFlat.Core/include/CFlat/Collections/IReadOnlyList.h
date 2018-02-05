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

//! @file IReadOnlyList.h

#ifndef CFLAT_CORE_COLLECTIONS_IREADONLYLIST_H
#define CFLAT_CORE_COLLECTIONS_IREADONLYLIST_H

#include "CFlat/Collections/IReadOnlyCollection.h"
#include "CFlat/Language/Integer.h"

namespace CFlat {
    template <typename T>
    class IReadOnlyList : public virtual IReadOnlyCollection<T> {
    public:
        inline virtual ~IReadOnlyList() {}

        /// <summary>
        /// Gets the item at the given index of an <see cref="IReadOnlyList"/>.
        /// </summary>
        /// <remarks>
        ///     If <paramref name="list"/> contains value types, the returned pointer shall no longer be dereferenced after the
        ///     first call to a function that modifies <paramref name="list"/>.
        /// </remarks>
        /// <param name="index">The index of the element to retrieve.</param>
        /// <returns>The item at the given index of the <see cref="IList"/>.</returns>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
        /// </exception>
        inline const T &operator[](uintsize index) const
        {
            return this->GetItem(index);
        }
        
        /// <summary>
        /// Gets the item at the given index of an <see cref="IReadOnlyList"/>.
        /// </summary>
        /// <remarks>
        ///     If <paramref name="list"/> contains value types, the returned pointer shall no longer be dereferenced after the
        ///     first call to a function that modifies <paramref name="list"/>.
        /// </remarks>
        /// <param name="index">The index of the element to retrieve.</param>
        /// <returns>The item at the given index of the <see cref="IList"/>.</returns>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
        /// </exception>
        virtual const T &GetItem(uintsize index) const = 0;

        /// <summary>
        /// Determines the index of the given item in an <see cref="IReadOnlyList"/>.
        /// </summary>
        /// <param name="item">The item to find.</param>
        /// <returns>The index of <paramref name="item"/> if found; otherwise -1.</returns>
        virtual uintsize IndexOf(const T &item) const = 0;
    };
}

#endif
