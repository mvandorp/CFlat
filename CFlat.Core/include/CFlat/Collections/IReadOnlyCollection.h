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

//! @file IReadOnlyCollection.h

#ifndef CFLAT_CORE_COLLECTIONS_IREADONLYCOLLECTION_H
#define CFLAT_CORE_COLLECTIONS_IREADONLYCOLLECTION_H

#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Language/Integer.h"

namespace CFlat {
    template <typename T>
    class IReadOnlyCollection : public virtual IEnumerable<T> {
    public:
        inline virtual ~IReadOnlyCollection() {}

        /// <summary>
        /// Gets the number of elements in an <see cref="IReadOnlyCollection"/>.
        /// </summary>
        /// <returns>The number of elements in the <see cref="IReadOnlyCollection"/>.</returns>
        virtual uintsize GetCount() const = 0;

        virtual bool Contains(const T &item) const = 0;

        virtual void CopyTo(T destination[]) const = 0;
    };
}

#endif
