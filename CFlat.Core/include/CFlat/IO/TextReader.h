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

//! @file TextReader.h

#ifndef CFLAT_CORE_IO_TEXTREADER_H
#define CFLAT_CORE_IO_TEXTREADER_H

#include "CFlat/Object.h"
#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"
#include "CFlat/Language/VarArgs.h"

/* Macros */
/// <summary>
/// Initializer for a <see cref="TextReaderVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>, or <see cref="null"/>.</param>
/// <param name="peek">A <see cref="TextReader_Peek"/>.</param>
/// <param name="read">A <see cref="TextReader_Read"/>.</param>
/// <param name="readBuffer">A <see cref="TextReader_ReadBuffer"/>.</param>
#define TextReaderVTable_Initializer(           \
    destructor,                                 \
    peek,                                       \
    read,                                       \
    readBuffer)                                 \
{                                               \
    ObjectVTable_Initializer(destructor),       \
    peek,                                       \
    read,                                       \
    readBuffer,                                 \
}

/* Types */
/// <summary>
/// Base class for objects that can read sequences of characters.
/// </summary>
typedef struct TextReader {
    /// <summary>
    /// The base class of <see cref="TextReader"/>.
    /// </summary>
    Object Base;
} TextReader;

/// <summary>
/// A function that returns the next available character of a <see cref="TextReader"/>.
/// </summary>
/// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
/// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
typedef int (*TextReader_PeekFunc)(TextReader *reader);

/// <summary>
/// A function that reads the next available character from the input source of a <see cref="TextReader"/> and
/// advances the character position to the next character.
/// </summary>
/// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
/// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
typedef int (*TextReader_ReadFunc)(TextReader *reader);

/// <summary>
/// A function that reads a given maximum number of characters from the input source of a <see cref="TextReader"/>
/// and advances the character position by the number of characters read.
/// </summary>
/// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
/// <param name="buffer">The array to which the characters should be read.</param>
/// <param name="offset">
///     The offset in <paramref name="buffer"/> at which to begin storing characters read from
///     <paramref name="reader"/>.
/// </param>
/// <param name="count">The maximum number of characters to read.</param>
/// <returns>
///     The total number of characters read into the buffer. This can be less than the number of bytes requested if
///     that many characters are currently not available, or zero if all characters have been read.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="reader"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="buffer"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
typedef uintsize (*TextReader_ReadBufferFunc)(TextReader *reader, char *buffer, uintsize offset, uintsize count);

/// <summary>
/// A virtual method table for the <see cref="TextReader"/> class.
/// </summary>
typedef struct TextReaderVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="TextReader"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that returns the next available character of a <see cref="TextReader"/>.
    /// </summary>
    TextReader_PeekFunc Peek;

    /// <summary>
    /// A function that reads the next available character from the input source of a <see cref="TextReader"/> and
    /// advances the character position to the next character.
    /// </summary>
    TextReader_ReadFunc Read;

    /// <summary>
    /// A function that reads a given maximum number of characters from the input source of a <see cref="TextReader"/>
    /// and advances the character position by the number of characters read.
    /// </summary>
    TextReader_ReadBufferFunc ReadBuffer;
} TextReaderVTable;

/* Constants */
/// <summary>
/// A <see cref="TextReader"/> with no backing store.
/// </summary>
public extern TextReader * const TextReader_Null;

/* Functions */
/// <summary>
/// Initializes a <see cref="TextReader"/>.
/// </summary>
/// <param name="reader">Pointer to an uninitialized <see cref="TextReader"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="reader"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void TextReader_Constructor(TextReader *reader, const TextReaderVTable *vtable);

/// <summary>
/// Returns the next available character of a <see cref="TextReader"/>.
/// </summary>
/// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
/// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
abstract int TextReader_Peek(TextReader *reader);

/// <summary>
/// Reads the next available character from the input source of a <see cref="TextReader"/> and advances the character
/// position to the next character.
/// </summary>
/// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
/// <returns>An integer representing the next character, or -1 if no more characters are available.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
abstract int TextReader_Read(TextReader *reader);

/// <summary>
/// Reads a given maximum number of characters from the input source of a <see cref="TextReader"/> and advances the
/// character position by the number of characters read.
/// </summary>
/// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
/// <param name="buffer">The array to which the characters should be read.</param>
/// <param name="offset">
///     The offset in <paramref name="buffer"/> at which to begin storing characters read from
///     <paramref name="reader"/>.
/// </param>
/// <param name="count">The maximum number of characters to read.</param>
/// <returns>
///     The total number of characters read into the buffer. This can be less than the number of bytes requested if
///     that many characters are currently not available, or zero if all characters have been read.
/// </returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="reader"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="buffer"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
abstract uintsize TextReader_ReadBuffer(TextReader *reader, char *buffer, uintsize offset, uintsize count);

/// <summary>
/// Reads a line of characters from the input source of a <see cref="TextReader"/> and returns the data as a
/// <see cref="String"/>.
/// </summary>
/// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
/// <returns>
///     A pointer to a <see cref="String"/> containing the next line of the reader, or <see cref="null"/> if all
///     characters have been read.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct String *TextReader_ReadLine(TextReader *reader);

/// <summary>
/// Reads all characters from the input source of a <see cref="TextReader"/> and returns the data as a
/// <see cref="String"/>.
/// </summary>
/// <param name="reader">Pointer to a <see cref="TextReader"/>.</param>
/// <returns>
///     A pointer to a <see cref="String"/> containing all remaining characters of the reader, or <see cref="null"/>
///     if all characters have been read.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="reader"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct String *TextReader_ReadToEnd(TextReader *reader);

#endif
