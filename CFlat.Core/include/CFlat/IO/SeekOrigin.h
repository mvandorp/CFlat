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

//! @file SeekOrigin.h

#ifndef CFLAT_CORE_IO_SEEKORIGIN_H
#define CFLAT_CORE_IO_SEEKORIGIN_H

#include "CFlat/Language/Bool.h"

/* Types */
/// <summary>
/// Specifies the position in a stream to use for seeking.
/// </summary>
typedef enum SeekOrigin {
    /// <summary>
    /// Specifies the beginning of a stream.
    /// </summary>
    SeekOrigin_Begin,
    /// <summary>
    /// Specifies the current position within a stream.
    /// </summary>
    SeekOrigin_Current,
    /// <summary>
    /// Specifies the end of a stream.
    /// </summary>
    SeekOrigin_End
} SeekOrigin;

/* Functions */
/// <summary>
/// Determines whether or not <paramref name="origin"/> is a valid <see cref="SeekOrigin"/>.
/// </summary>
/// <param name="origin">The <see cref="SeekOrigin"/> to validate.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="origin"/> is a valid <see cref="SeekOrigin"/>;
///     otherwise <see cref="false"/>.
/// </returns>
bool SeekOrigin_IsValid(SeekOrigin origin);

/// <summary>
/// Validates that <paramref name="origin"/> is a valid <see cref="SeekOrigin"/>.
/// </summary>
/// <param name="origin">The <see cref="SeekOrigin"/> to validate.</param>
/// <exception cref="::ArgumentException"><paramref name="origin"/> is not a valid <see cref="SeekOrigin"/>.</exception>
void SeekOrigin_Validate(SeekOrigin origin);

#endif
