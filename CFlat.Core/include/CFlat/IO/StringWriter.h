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

//! @file StringWriter.h

#ifndef CFLAT_CORE_IO_STRINGWRITER_H
#define CFLAT_CORE_IO_STRINGWRITER_H

/* Forward declarations */
struct String;
struct TextWriter;

/* Types */
/// <summary>
/// Implements a <see cref="TextWriter"/> for writing characters to a string. The information is stored in an underlying
/// <see cref="StringBuilder"/>. The resulting string can be retrieved via TextWriter_ToString().
/// </summary>
typedef struct StringWriter StringWriter;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="StringWriter"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StringWriter"/> should be managed with retain() and release().
/// </remarks>
/// <returns>A pointer to the newly allocated string writer.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct TextWriter *StringWriter_New(void);

/// <summary>
/// Deletes a <see cref="StringWriter"/> and returns its value as a <see cref="String"/>.
/// </summary>
/// <remarks>
///     This operation can only be performed if there are no other references to <paramref name="writer"/>.
/// </remarks>
/// <param name="writer">Pointer to a <see cref="StringWriter"/>.</param>
/// <returns>
///     A pointer to a <see cref="String"/> with the same value as the <see cref="StringBuilder"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::InvalidOperationException">There are still references to <paramref name="writer"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct String *StringWriter_DeleteAndToString(StringWriter *writer);

#endif
