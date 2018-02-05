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

//! @file IList.h

#ifndef CFLAT_CORE_COLLECTIONS_ILIST_H
#define CFLAT_CORE_COLLECTIONS_ILIST_H

#include "CFlat/Collections/ICollection.h"
#include "CFlat/Collections/IReadOnlyList.h"
#include "CFlat/Language/Integer.h"

#include <type_traits>

namespace CFlat {
    template <typename T>
    class IList : public virtual IReadOnlyList<T>, public virtual ICollection<T> {
    public:
        inline virtual ~IList() {}

        /// <summary>
        /// Gets the item at the given index of an <see cref="IList"/>.
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
        virtual void SetItem(uintsize index, T item) = 0;
                
        /// <summary>
        /// Inserts an item into an <see cref="IList"/> at the given index.
        /// </summary>
        /// <param name="index">The index at which <paramref name="item"/> should be inserted.</param>
        /// <param name="item">The item to insert.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is greater than the number of elements in <paramref name="list"/>.
        /// </exception>
        virtual void Insert(uintsize index, T item) = 0;

        /// <summary>
        /// Removes the element at the given index of an <see cref="IList"/>.
        /// </summary>
        /// <param name="index">The index of the element to remove.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
        /// </exception>
        virtual void RemoveAt(uintsize index) = 0;

        virtual T& operator[](uintsize index) = 0;
    };
}

#endif
