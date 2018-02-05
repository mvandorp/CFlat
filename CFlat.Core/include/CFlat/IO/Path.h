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

//! @file Path.h

#ifndef CFLAT_CORE_IO_PATH_H
#define CFLAT_CORE_IO_PATH_H

namespace CFlat {
    /* Forward declarations */
    class String;

    class Path {
    public:
        Path() = delete;

        /// <summary>
        /// Returns a new <see cref="String"/> with the file name of the given path.
        /// </summary>
        /// <remarks>
        ///     If <paramref name="path"/> is <see cref="null"/>, <see cref="null"/> is returned.
        /// </remarks>
        /// <param name="path">Pointer to a <see cref="String"/> containing the path for which to obtain the file name.</param>
        /// <returns>
        ///     A new <see cref="String"/> with the file name of the given path;
        ///     or <see cref="null"/> if <paramref name="path"/> is <see cref="null"/>.
        /// </returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String GetFileName(const String &path);

        /// <summary>
        /// Returns a new <see cref="String"/> with the file name of the given path.
        /// </summary>
        /// <remarks>
        ///     If <paramref name="path"/> is <see cref="null"/>, <see cref="null"/> is returned.
        /// </remarks>
        /// <param name="path">
        ///     Pointer to a null-terminated string containing the path for which to obtain the file name.
        /// </param>
        /// <returns>
        ///     A new <see cref="String"/> with the file name of the given path;
        ///     or <see cref="null"/> if <paramref name="path"/> is <see cref="null"/>.
        /// </returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String GetFileName(const char *path);
    };
}

#endif
