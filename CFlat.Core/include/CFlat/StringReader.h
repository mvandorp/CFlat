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

//! @file StringReader.h

#ifndef CFLAT_CORE_STRINGREADER_H
#define CFLAT_CORE_STRINGREADER_H

#include "CFlat/Language/Integer.h"

/* Forward declarations */
typedef struct String String;

/* Types */
/// <summary>
/// Implements a reader that reads from a string of characters.
/// </summary>
typedef struct StringReader StringReader;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="StringReader"/> that reads from the given <see cref="String"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="StringReader"/> should be managed with Object_Aquire() and Object_Release().
/// </remarks>
/// <param name="str">Pointer to a string.</param>
/// <returns>A pointer to the newly allocated <see cref="StringReader"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="str"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
StringReader *StringReader_New(const String *str);

/// <summary>
/// Initializes a <see cref="StringReader"/> so that reads from the given <see cref="String"/>.
/// </summary>
/// <param name="reader">Pointer to an uninitialized <see cref="StringReader"/>.</param>
/// <param name="str">Pointer to a string.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="reader"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="str"/> is <see cref="null"/>.
/// </exception>
void StringReader_Constructor(StringReader *reader, const String *str);

/// <summary>
/// Destroys a <see cref="StringReader"/>.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
void StringReader_Destructor(StringReader *reader);

/// <summary>
/// Returns the next available character of a <see cref="StringReader"/>.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
/// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
int StringReader_Peek(const StringReader *reader);

/// <summary>
/// Returns the character at the given offset of a <see cref="StringReader"/>.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
/// <param name="offset">The offset at which to peek.</param>
/// <returns>
///     An integer representing the character at the given offset, or -1 if no more characters are available.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
int StringReader_PeekOffset(const StringReader *reader, uintsize offset);

/// <summary>
/// Reads the next available character from the input string of a <see cref="StringReader"/> and advances the character
/// position to the next character.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
/// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
int StringReader_Read(StringReader *reader);

/// <summary>
/// Advances the position of a <see cref="StringReader"/> by the given number of characters.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
/// <param name="amount">The number of characters to skip.</param>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
void StringReader_Skip(StringReader *reader, uintsize amount);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/StringReader.internal.h"
#endif

#endif
