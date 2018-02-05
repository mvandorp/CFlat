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

//! @file IEnumerable.h

#ifndef CFLAT_CORE_COLLECTIONS_IENUMERABLE_H
#define CFLAT_CORE_COLLECTIONS_IENUMERABLE_H

#include "CFlat/Language/Pointers.h"

namespace CFlat {
    /* Forward declarations */
    template <typename T>
    class IEnumerator;

    /// <summary>
    /// Base class that exposes an enumerator, which supports a simple iteration over a collection of elements.
    /// </summary>
    template <typename T>
    class IEnumerable {
    public:
        inline virtual ~IEnumerable() {}

        /// <summary>
        /// Returns a pointer to an <see cref="IEnumerator"/> that iterates through an <see cref="IEnumerable"/>.
        /// </summary>
        /// <returns>An <see cref="IEnumerator"/> that iterates through the <see cref="IEnumerable"/>.</returns>
        virtual unique_ptr<IEnumerator<T>> GetEnumerator() const = 0;
    };
}

#endif
