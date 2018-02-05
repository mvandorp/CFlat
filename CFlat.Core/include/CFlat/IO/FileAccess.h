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

//! @file FileAccess.h

#ifndef CFLAT_CORE_IO_FILEACCESS_H
#define CFLAT_CORE_IO_FILEACCESS_H

#include "CFlat/Validate.h"

namespace CFlat {
    namespace FileAccess {
        /// <summary>
        /// Defines constants for read, write, or read/write access to a file.
        /// </summary>
        enum Enum {
            /// <summary>
            /// Specifies read access to a file. Combine with <see cref="FileAccess_Write"/> for read/write access.
            /// </summary>
            Read = 1 << 0,

            /// <summary>
            /// Specifies write access to a file. Combine with <see cref="FileAccess_Read"/> for read/write access.
            /// </summary>
            Write = 1 << 1,

            /// <summary>
            /// Specifies read/write access to a file.
            /// </summary>
            ReadWrite = Read | Write
        };

        inline bool HasFlag(FileAccess::Enum fileAccess, FileAccess::Enum flag)
        {
            return (fileAccess & flag) == flag;
        }

        /// <summary>
        /// Determines whether or not <paramref name="fileAccess"/> is a valid <see cref="FileAccess"/>.
        /// </summary>
        /// <param name="fileAccess">The <see cref="FileAccess"/> to validate.</param>
        /// <returns>
        ///     <see cref="true"/> if <paramref name="fileAccess"/> is a valid <see cref="FileAccess"/>;
        ///     otherwise <see cref="false"/>.
        /// </returns>
        bool IsValid(FileAccess::Enum fileAccess);

        /// <summary>
        /// Validates that <paramref name="fileAccess"/> is a valid <see cref="FileAccess"/>.
        /// </summary>
        /// <param name="fileAccess">The <see cref="FileAccess"/> to validate.</param>
        /// <exception cref="::ArgumentException">
        ///     <paramref name="fileAccess"/> is not a valid <see cref="FileAccess"/>.
        /// </exception>
        void Validate(FileAccess::Enum fileAccess);
    }
}

#endif
