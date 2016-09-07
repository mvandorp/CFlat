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

//! @file StreamWriter.h

#ifndef CFLAT_CORE_IO_STREAMWRITER_H
#define CFLAT_CORE_IO_STREAMWRITER_H

#include "CFlat/Language/Bool.h"

/* Forward declarations */
struct Stream;
struct TextWriter;

/* Types */
/// <summary>
/// Implements a <see cref="TextWriter"/> for writing characters to a <see cref="Stream"/>.
/// </summary>
typedef struct StreamWriter StreamWriter;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="StreamWriter"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StreamWriter"/> should be managed with retain() and release().
/// </remarks>
/// <param name="stream">Pointer to the <see cref="Stream"/> to write to.</param>
/// <returns>A pointer to the newly allocated stream writer.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct TextWriter *StreamWriter_New(struct Stream *stream);

/// <summary>
/// Allocates and initializes a new <see cref="StreamWriter"/> for the specified file. If the file exists, it can be
/// either overriden or appended to. If the file does not exist, a new file is created.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StreamWriter"/> should be managed with retain() and release().
/// </remarks>
/// <param name="path">The file path to write to.</param>
/// <param name="append">
///     <see cref="true"/> to append data to the file; <see cref="false"/> to overwrite the file. If the specified file
///     does not exist, this parameter has no effect since a new file is created.
/// </param>
/// <returns>A pointer to the newly allocated stream writer.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="path"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct TextWriter *StreamWriter_New_FromFile(const char *path, bool append);

#endif
