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

//! @file ICollection.h

#ifndef CFLAT_CORE_COLLECTIONS_ICOLLECTION_H
#define CFLAT_CORE_COLLECTIONS_ICOLLECTION_H

#include "CFlat/Collections/IReadOnlyCollection.h"

#include <type_traits>

namespace CFlat {
    template <class T>
    class ICollection : public virtual IReadOnlyCollection<T> {
    public:
        inline virtual ~ICollection() {}

        /// <summary>
        /// Adds an item to an <see cref="ICollection"/>.
        /// </summary>
        /// <param name="item">The item to add.</param>
        virtual void Add(T item) = 0;

        /// <summary>
        /// Removes all elements from an <see cref="ICollection"/>.
        /// </summary>
        virtual void Clear() = 0;

        /// <summary>
        /// Removes the first occurance of the given item from an <see cref="ICollection"/>.
        /// </summary>
        /// <param name="item">The item to remove.</param>
        /// <returns>
        ///     <see cref="true"/> if <paramref name="item"/> was successfully removed; otherwise, <see cref="false"/>.
        /// </returns>
        virtual bool Remove(const T &item) = 0;
    };
}

#endif
