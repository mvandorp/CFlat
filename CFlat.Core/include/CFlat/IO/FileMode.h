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

//! @file FileMode.h

#ifndef CFLAT_CORE_IO_FILEMODE_H
#define CFLAT_CORE_IO_FILEMODE_H

#include "CFlat/Language/Bool.h"

/* Types */
/// <summary>
/// Specifies how a file should be opened.
/// </summary>
typedef enum FileMode {
    /// <summary>
    /// Opens the file if it exists and seeks to the end of the file, or creates a new file. Trying to seek to a
    /// position before the end of the file throws an <see cref="IOException"/>, and any attempt to read fails and
    /// throws a <see cref="NotSupportedException"/>.
    /// </summary>
    FileMode_Append,

    /// <summary>
    /// Specifies that a new file should be created. If the file already exists, it will be overriden.
    /// </summary>
    FileMode_Create,

    /// <summary>
    /// Specifies that a new file should be created. If the file already exists, an <see cref="IOException"/> is thrown.
    /// </summary>
    FileMode_CreateNew,

    /// <summary>
    /// Specifies that an existing file should be opened. If the file does not exist, an <see cref="IOException"/> is
    /// thrown.
    /// </summary>
    FileMode_Open,

    /// <summary>
    /// Specifies that a file should be opened if it exists; otherwise, a new file should be created.
    /// </summary>
    FileMode_OpenOrCreate,

    /// <summary>
    /// Specifies that an existing file should be opened. When the file is opened, it should be truncated so that its
    /// size is zero bytes.
    /// </summary>
    FileMode_Truncate,
} FileMode;

/* Functions */
/// <summary>
/// Determines whether or not <paramref name="mode"/> is a valid <see cref="FileMode"/>.
/// </summary>
/// <param name="mode">The <see cref="FileMode"/> to validate.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="mode"/> is a valid <see cref="FileMode"/>; otherwise <see cref="false"/>.
/// </returns>
bool FileMode_IsValid(FileMode mode);

/// <summary>
/// Validates that <paramref name="mode"/> is a valid <see cref="FileMode"/>.
/// </summary>
/// <param name="mode">The <see cref="FileMode"/> to validate.</param>
/// <exception cref="::ArgumentException"><paramref name="mode"/> is not a valid <see cref="FileMode"/>.</exception>
void FileMode_Validate(FileMode mode);

#endif
