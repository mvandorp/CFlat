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

#ifndef CFLAT_CORE_STRING_ENUMERATOR_H
#define CFLAT_CORE_STRING_ENUMERATOR_H

#include "CFlat/Collections/IEnumerator.h"

#include "CFlat/String.h"

namespace CFlat {
    class String::Enumerator : public IEnumerator<char> {
    private:
        String _string;
        char _current;
        uintsize _index;

    public:
        /// <summary>
        /// Allocates and initializes a new <see cref="IEnumerator"/> that can iterate over the given <see cref="String"/>.
        ///
        /// The lifetime of the <see cref="IEnumerator"/> should be managed with retain() and release().
        /// </summary>
        /// <param name="str">Pointer to a <see cref="String"/>.</param>
        /// <returns>A pointer to the newly allocated <see cref="IEnumerator"/>.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        Enumerator(String str);

        virtual ~Enumerator();

        const char &GetCurrent() const override;

        bool MoveNext() override;

        void Reset() override;
    };
}

#endif
