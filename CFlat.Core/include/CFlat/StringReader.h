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

/**
 * @file StringReader.h
 */

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
///
/// The lifetime of the <see cref="StringReader"/> should be managed with Object_Aquire(), Object_Release() and
/// Object_Delete().
/// </summary>
/// <param name="str">Pointer to a string.</param>
/// <returns>Pointer to the newly allocated <see cref="StringReader"/>.</returns>
StringReader *StringReader_New(const String *str);

/// <summary>
/// Initializes the given <see cref="StringReader"/> so that reads from the given <see cref="String"/>.
/// </summary>
/// <param name="reader">Pointer to an uninitialized <see cref="StringReader"/>.</param>
/// <param name="str">Pointer to a string.</param>
void StringReader_Constructor(StringReader *reader, const String *str);

/// <summary>
/// Destroys the given <see cref="StringReader"/>.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
void StringReader_Destructor(void *reader);

/// <summary>
/// Returns the next available character without advancing the position of the reader.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
/// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
int StringReader_Peek(const StringReader *reader);

/// <summary>
/// Returns the character at the given offset without advancing the position of the reader.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
/// <param name="offset">The offset at which to peek.</param>
/// <returns>
/// An integer representing the character at the given offset, or -1 if no more characters are available.
/// </returns>
int StringReader_PeekOffset(const StringReader *reader, uintsize offset);

/// <summary>
/// Returns the next available character and advances the position of the reader.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
/// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
int StringReader_Read(StringReader *reader);

/// <summary>
/// Advances the position of the reader by the given amount.
/// </summary>
/// <param name="reader">Pointer to a <see cref="StringReader"/>.</param>
/// <param name="amount">The number of characters to skip.</param>
void StringReader_Skip(StringReader *reader, uintsize amount);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/StringReader.internal.h"
#endif

#endif
