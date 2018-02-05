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

//! @file Bool.h

#ifndef CFLAT_CORE_LANGUAGE_BOOL_H
#define CFLAT_CORE_LANGUAGE_BOOL_H

#include "CFlat/String.h"

namespace CFlat {
    /* Forward declarations */
    class StringBuilder;

    class Bool {
    public:
        /* Static class */
        Bool() = delete;

        /* Functions */
        /// <summary>
        /// Converts the given boolean to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given boolean.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(bool value);

        /// <summary>
        /// Converts the given boolean to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, bool value);
    };
}

#endif
