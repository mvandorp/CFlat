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

//! @file TextWriter.h

#ifndef CFLAT_CORE_IO_TEXTWRITER_H
#define CFLAT_CORE_IO_TEXTWRITER_H

#include "CFlat/Object.h"
#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"
#include "CFlat/Language/VarArgs.h"

/* Forward declarations */
struct String;

/* Macros */
/// <summary>
/// Initializer for a <see cref="TextWriterVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>, or <see cref="null"/>.</param>
/// <param name="flush">A <see cref="TextWriter_FlushFunc"/>.</param>
/// <param name="toString">A <see cref="TextWriter_ToStringFunc"/>, or <see cref="null"/>.</param>
/// <param name="writeBuffer">A <see cref="TextWriter_WriteBufferFunc"/>.</param>
#define TextWriterVTable_Initializer(           \
    destructor,                                 \
    flush,                                      \
    toString,                                   \
    writeBuffer)                                \
{                                               \
    ObjectVTable_Initializer(destructor),       \
    flush,                                      \
    toString,                                   \
    writeBuffer,                                \
}

/* Types */
/// <summary>
/// Base class for objects that can write sequences of characters.
/// </summary>
typedef struct TextWriter {
    /// <summary>
    /// The base class of <see cref="Stream"/>.
    /// </summary>
    Object Base;
    /// <summary>
    /// Indicates whether or not the writer will automatically flush its buffer to the underlying device after every
    /// call to TextWriter_Write().
    /// </summary>
    bool AutoFlush;
} TextWriter;

/// <summary>
/// A function that writes any unwritten data in the output buffer of a <see cref="TextWriter"/> to the underlying
/// device.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
typedef void (*TextWriter_FlushFunc)(TextWriter *writer);

/// <summary>
/// A function that returns a string that represents the given <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <returns>The string representation of the given writer.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
typedef struct String *(*TextWriter_ToStringFunc)(const TextWriter *writer);

/// <summary>
/// A function that writes an array of characters to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="buffer">The array of the characters to write data from.</param>
/// <param name="offset">
///     The offset in <paramref name="buffer"/> at which to begin writing <paramref name="writer"/>.
/// </param>
/// <param name="count">The number of characters to write.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="buffer"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
typedef void (*TextWriter_WriteBufferFunc)(TextWriter *writer, const char *buffer, uintsize offset, uintsize count);

/// <summary>
/// A virtual method table for the <see cref="TextWriter"/> class.
/// </summary>
typedef struct TextWriterVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="TextWriter"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that writes any unwritten data in the output buffer of a <see cref="TextWriter"/> to the underlying
    /// device.
    /// </summary>
    TextWriter_FlushFunc Flush;

    /// <summary>
    /// A function that returns a string that represents the given <see cref="TextWriter"/>.
    /// </summary>
    TextWriter_ToStringFunc ToString;

    /// <summary>
    /// A function that writes an array of characters to a <see cref="TextWriter"/>.
    /// </summary>
    TextWriter_WriteBufferFunc WriteBuffer;
} TextWriterVTable;

/* Constants */
/// <summary>
/// A <see cref="TextWriter"/> with no backing store.
/// </summary>
public extern TextWriter * const TextWriter_Null;

/* Functions */
/// <summary>
/// Initializes a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to an uninitialized <see cref="TextWriter"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void TextWriter_Constructor(TextWriter *writer, const TextWriterVTable *vtable);

/// <summary>
/// Gets whether or not a <see cref="TextWriter"/> will automatically flush its buffer to the underlying device after
/// every call to TextWriter_Write().
/// </summary>
/// <returns>
///     <see cref="true"/> if automatic flushing of the buffer is enabled; otherwise, <see cref="false"/>.
/// </returns>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
bool TextWriter_GetAutoFlush(const TextWriter *writer);

/// <summary>
/// Sets whether or not a <see cref="TextWriter"/> will automatically flush its buffer to the underlying device after
/// every call to TextWriter_Write().
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">
///     <see cref="true"/> to enable automatic flushing of the buffer is enabled; otherwise, <see cref="false"/>.
/// </param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_SetAutoFlush(TextWriter *writer, bool value);

/// <summary>
/// Writes any unwritten data in the output buffer of a <see cref="TextWriter"/> to the underlying device.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
virtual void TextWriter_Flush(TextWriter *writer);

/// <summary>
/// Returns a string that represents the given <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <returns>The string representation of the given writer.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
virtual struct String *TextWriter_ToString(const TextWriter *writer);

/// <summary>
/// Writes an array of characters to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="buffer">The array of the characters to write data from.</param>
/// <param name="offset">
///     The offset in <paramref name="buffer"/> at which to begin writing <paramref name="writer"/>.
/// </param>
/// <param name="count">The number of characters to write.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="buffer"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
abstract void TextWriter_WriteBuffer(TextWriter *writer, const char *buffer, uintsize offset, uintsize count);

/// <summary>
/// Writes a character to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The character to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write(TextWriter *writer, char value);

/// <summary>
/// Writes a null-terminated string to a <see cref="TextWriter"/>.
/// </summary>
/// <remarks>If <paramref name="value"/> is <see cref="null"/>, nothing is written.</remarks>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">Pointer to the null-terminated string to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_CString(TextWriter *writer, const char *value);

/// <summary>
/// Writes a <see cref="String"/> to a <see cref="TextWriter"/>.
/// </summary>
/// <remarks>If <paramref name="value"/> is <see cref="null"/>, nothing is written.</remarks>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">Pointer to the <see cref="String"/> to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_String(TextWriter *writer, const struct String *value);

/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_Int(TextWriter *writer, int value);

/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_IntMax(TextWriter *writer, intmax value);

#ifdef CFLAT_INTPTR
/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_IntPtr(TextWriter *writer, intptr value);
#endif

/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_IntFSize(TextWriter *writer, intfsize value);

/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_UInt(TextWriter *writer, uint value);

/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_UIntMax(TextWriter *writer, uintmax value);

#ifdef CFLAT_INTPTR
/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_UIntPtr(TextWriter *writer, uintptr value);
#endif

/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_UIntSize(TextWriter *writer, uintsize value);

/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_Single(TextWriter *writer, float value);

/// <summary>
/// Writes a the string representation of the given number to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_Write_Double(TextWriter *writer, double value);

/// <summary>
/// Writes a formatted string to a <see cref="TextWriter"/>, the formatting is performed as if done by
/// String_FormatCString().
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TextWriter_WriteFormat_CString(TextWriter *writer, const char *format, ...);

/// <summary>
/// Writes a formatted string to a <see cref="TextWriter"/>, the formatting is performed as if done by
/// String_FormatCString().
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TextWriter_WriteFormat_CStringV(TextWriter *writer, const char *format, VarArgsList args);

/// <summary>
/// Writes a formatted string to a <see cref="TextWriter"/>, the formatting is performed as if done by
/// String_FormatString().
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TextWriter_WriteFormat_String(TextWriter *writer, const struct String *format, ...);

/// <summary>
/// Writes a formatted string to a <see cref="TextWriter"/>, the formatting is performed as if done by
/// String_FormatString().
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TextWriter_WriteFormat_StringV(TextWriter *writer, const struct String *format, VarArgsList args);

/// <summary>
/// Writes a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine(TextWriter *writer);

/// <summary>
/// Writes a character followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The character to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_Char(TextWriter *writer, char value);

/// <summary>
/// Writes a null-terminated string followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <remarks>If <paramref name="value"/> is <see cref="null"/>, only the line terminator is written.</remarks>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">Pointer to the null-terminated string to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_CString(TextWriter *writer, const char *value);

/// <summary>
/// Writes a <see cref="String"/> followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <remarks>If <paramref name="value"/> is <see cref="null"/>, only the line terminator is written.</remarks>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">Pointer to the <see cref="String"/> to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_String(TextWriter *writer, const struct String *value);

/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_Int(TextWriter *writer, int value);

/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_IntMax(TextWriter *writer, intmax value);

#ifdef CFLAT_INTPTR
/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_IntPtr(TextWriter *writer, intptr value);
#endif

/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_IntFSize(TextWriter *writer, intfsize value);

/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_UInt(TextWriter *writer, uint value);

/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_UIntMax(TextWriter *writer, uintmax value);

#ifdef CFLAT_UINTPTR
/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_UIntPtr(TextWriter *writer, uintptr value);
#endif

/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_UIntSize(TextWriter *writer, uintsize value);

/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_Single(TextWriter *writer, float value);

/// <summary>
/// Writes a the string representation of the given number followed by a line terminator to a <see cref="TextWriter"/>.
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="value">The number to write.</param>
/// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void TextWriter_WriteLine_Double(TextWriter *writer, double value);

/// <summary>
/// Writes a formatted string followed by a line terminator to a <see cref="TextWriter"/>, the formatting is performed
/// as if done by String_FormatCString().
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TextWriter_WriteLineFormat_CString(TextWriter *writer, const char *format, ...);

/// <summary>
/// Writes a formatted string followed by a line terminator to a <see cref="TextWriter"/>, the formatting is performed
/// as if done by String_FormatCString().
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TextWriter_WriteLineFormat_CStringV(TextWriter *writer, const char *format, VarArgsList args);

/// <summary>
/// Writes a formatted string followed by a line terminator to a <see cref="TextWriter"/>, the formatting is performed
/// as if done by String_FormatString().
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TextWriter_WriteLineFormat_String(TextWriter *writer, const struct String *format, ...);

/// <summary>
/// Writes a formatted string followed by a line terminator to a <see cref="TextWriter"/>, the formatting is performed
/// as if done by String_FormatString().
/// </summary>
/// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="writer"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="format"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TextWriter_WriteLineFormat_StringV(TextWriter *writer, const struct String *format, VarArgsList args);

#endif
