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

//! @file FileStream.h

#ifndef CFLAT_CORE_IO_FILESTREAM_H
#define CFLAT_CORE_IO_FILESTREAM_H

#include "CFlat/IO/FileAccess.h"
#include "CFlat/IO/FileMode.h"

/* Forward declarations */
struct Stream;
struct String;
struct TextReader;

/* Types */
/// <summary>
/// Implements a <see cref="Stream"/> for reading/writing to a file.
/// </summary>
typedef struct FileStream FileStream;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="FileStream"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="FileStream"/> should be managed with retain() and release().
/// </remarks>
/// <returns>A pointer to the newly allocated stream.</returns>
/// <param name="path">Pointer to a <see cref="String"/> containg the path of the file.</param>
/// <param name="mode">A <see cref="FileMode"/> value that determines how to open or create the file.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="stream"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="path"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentException"><paramref name="mode"/> is not a valid <see cref="FileMode"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct Stream *FileStream_New(const struct String *path, FileMode mode);

/// <summary>
/// Allocates and initializes a new <see cref="FileStream"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="FileStream"/> should be managed with retain() and release().
/// </remarks>
/// <returns>A pointer to the newly allocated stream.</returns>
/// <param name="path">Pointer to a null-terminated string containg the path of the file.</param>
/// <param name="mode">A <see cref="FileMode"/> value that determines how to open or create the file.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="stream"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="path"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentException"><paramref name="mode"/> is not a valid <see cref="FileMode"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct Stream *FileStream_New_CString(const char *path, FileMode mode);

/// <summary>
/// Allocates and initializes a new <see cref="FileStream"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="FileStream"/> should be managed with retain() and release().
/// </remarks>
/// <returns>A pointer to the newly allocated stream.</returns>
/// <param name="path">Pointer to a <see cref="String"/> containg the path of the file.</param>
/// <param name="mode">A <see cref="FileMode"/> value that determines how to open or create the file.</param>
/// <param name="fileAccess">
///     A <see cref="FileAccess"/> value that indicates the desired permissions on the file.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="stream"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="path"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentException">
///     <paramref name="mode"/> is not a valid <see cref="FileMode"/> <b>-or-</b>
///     <paramref name="fileAccess"/> is not a valid <see cref="FileAccess"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct Stream *FileStream_New_WithAccess(const struct String *path, FileMode mode, FileAccess fileAccess);

/// <summary>
/// Allocates and initializes a new <see cref="FileStream"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="FileStream"/> should be managed with retain() and release().
/// </remarks>
/// <returns>A pointer to the newly allocated stream.</returns>
/// <param name="path">Pointer to a null-terminated string containg the path of the file.</param>
/// <param name="mode">A <see cref="FileMode"/> value that determines how to open or create the file.</param>
/// <param name="fileAccess">
///     A <see cref="FileAccess"/> value that indicates the desired permissions on the file.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="stream"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="path"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::ArgumentException">
///     <paramref name="mode"/> is not a valid <see cref="FileMode"/> <b>-or-</b>
///     <paramref name="fileAccess"/> is not a valid <see cref="FileAccess"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct Stream *FileStream_New_WithAccess_CString(const char *path, FileMode mode, FileAccess fileAccess);

#endif
