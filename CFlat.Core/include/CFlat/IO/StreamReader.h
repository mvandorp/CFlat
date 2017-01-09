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

//! @file StreamReader.h

#ifndef CFLAT_CORE_IO_STREAMREADER_H
#define CFLAT_CORE_IO_STREAMREADER_H

/* Forward declarations */
struct Stream;
struct String;
struct TextReader;

/* Types */
/// <summary>
/// Implements a <see cref="TextReader"/> for reading characters from a <see cref="Stream"/>.
/// </summary>
typedef struct StreamReader StreamReader;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="StreamReader"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StreamReader"/> should be managed with retain() and release().
/// </remarks>
/// <param name="stream">Pointer to the <see cref="Stream"/> to read from.</param>
/// <returns>A pointer to the newly allocated stream reader.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="stream"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct TextReader *StreamReader_New(struct Stream *stream);

/// <summary>
/// Allocates and initializes a new <see cref="StreamReader"/> for the specified file.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StreamWriter"/> should be managed with retain() and release().
/// </remarks>
/// <param name="path">The file path to read from.</param>
/// <returns>A pointer to the newly allocated stream reader.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="path"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct TextReader *StreamReader_New_FromFile(const struct String *path);

/// <summary>
/// Allocates and initializes a new <see cref="StreamReader"/> for the specified file.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StreamWriter"/> should be managed with retain() and release().
/// </remarks>
/// <param name="path">The file path to read from.</param>
/// <returns>A pointer to the newly allocated stream reader.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="path"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct TextReader *StreamReader_New_FromFile_CString(const char *path);

#endif
