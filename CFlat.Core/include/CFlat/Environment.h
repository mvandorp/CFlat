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

//! @file Environment.h

#ifndef CFLAT_CORE_ENVIRONMENT_H
#define CFLAT_CORE_ENVIRONMENT_H

#include "CFlat/String.h"

/* Macros */
/// <summary>
/// Represents the newline string.
/// </summary>
#define Environment_NewLine_CString "\r\n"

namespace CFlat {
    /* Forward declarations*/
    class String;

    class Environment {
    public:
        /* Static class */
        Environment() = delete;

        /* Constants */
        /// <summary>
        /// Represents the newline string.
        /// </summary>
        static const String NewLine;

        /* Functions */
        /// <summary>
        /// Exits the process and returns the given exit code to the operating system.
        /// </summary>
        /// <param name="exitCode">The exit code to return to the operating system.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void Exit(int exitCode);

        /// <summary>
        /// Terminates the process and signals failure to the operating system.
        /// </summary>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void FailFast();
    };
}

#endif
