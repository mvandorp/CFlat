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

//! @file Console.h

#ifndef CFLAT_CORE_CONSOLE_H
#define CFLAT_CORE_CONSOLE_H

#include "CFlat/Language/VarArgs.h"

/* Forward declarations */
struct String;
struct Stream;
struct TextReader;
struct TextWriter;

/* Functions */
/// <summary>
/// Gets the standard input stream.
/// </summary>
/// <returns>A <see cref="TextReader"/> that represents the standard input stream.</returns>
struct TextReader *Console_GetIn(void);

/// <summary>
/// Sets the standard input stream.
/// </summary>
/// <param name="in">A pointer to a <see cref="TextReader"/> that is the new standard input stream.</param>
void Console_SetIn(struct TextReader *in);

/// <summary>
/// Gets the standard output stream.
/// </summary>
/// <returns>A pointer to a <see cref="TextWriter"/> that represents the standard output stream.</returns>
struct TextWriter *Console_GetOut(void);

/// <summary>
/// Sets the standard output stream.
/// </summary>
/// <param name="out">A <see cref="TextWriter"/> that is the new standard output stream.</param>
void Console_SetOut(struct TextWriter *out);

/// <summary>
/// Gets the standard error stream.
/// </summary>
/// <returns>A pointer to a <see cref="TextWriter"/> that represents the standard error stream.</returns>
struct TextWriter *Console_GetError(void);

/// <summary>
/// Sets the standard error stream.
/// </summary>
/// <param name="error">A <see cref="TextWriter"/> that is the new standard error stream.</param>
void Console_SetError(struct TextWriter *error);

/// <summary>
/// Acquires the standard input stream.
/// </summary>
/// <remarks>
///     This function can be used to reacquire the standard input stream after it has been changed by the
///     Console_SetIn() function.
/// </remarks>
/// <returns>A pointer to a <see cref="Stream"/> that is standard input stream.</returns>
struct Stream *Console_OpenStandardInput(void);

/// <summary>
/// Acquires the standard ouput stream.
/// </summary>
/// <remarks>
///     This function can be used to reacquire the standard ouput stream after it has been changed by the
///     Console_SetOut() function.
/// </remarks>
/// <returns>A pointer to a <see cref="Stream"/> that is standard ouput stream.</returns>
struct Stream *Console_OpenStandardOutput(void);

/// <summary>
/// Acquires the standard error stream.
/// </summary>
/// <remarks>
///     This function can be used to reacquire the standard error stream after it has been changed by the
///     Console_SetError() function.
/// </remarks>
/// <returns>A pointer to a <see cref="Stream"/> that is standard error stream.</returns>
struct Stream *Console_OpenStandardError(void);

/// <summary>
/// Reads the next character from the standard input stream.
/// </summary>
/// <returns>
///     The next character from the standard input stream, or -1 if there are currently no more characters available.
/// </returns>
/// <exception cref="::IOException">An I/O error occurs.</exception>
int Console_Read(void);

/// <summary>
/// Reads the next line of character from the standard input stream.
/// </summary>
/// <returns>
///     A pointer to a <see cref="String"/> containing the next line of characters from the standard input stream,
///     or -1 if there are currently no more characters available.
/// </returns>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct String *Console_ReadLine(void);

/// <summary>
/// Writes a character to the standard output stream.
/// </summary>
/// <param name="value">The character to write.</param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void Console_Write(char value);

/// <summary>
/// Writes a null-terminated string to the standard output stream.
/// </summary>
/// <remarks>If <paramref name="value"/> is <see cref="null"/>, nothing is written.</remarks>
/// <param name="value">Pointer to the null-terminated string to write.</param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void Console_Write_CString(const char *value);

/// <summary>
/// Writes a <see cref="String"/> to the standard output stream.
/// </summary>
/// <remarks>If <paramref name="value"/> is <see cref="null"/>, nothing is written.</remarks>
/// <param name="value">Pointer to the <see cref="String"/> to write.</param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void Console_Write_String(const struct String *value);

/// <summary>
/// Writes a formatted string to the standard output stream, the formatting is performed as if done by
/// String_FormatCString().
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Console_WriteFormat_CString(const char *format, ...);

/// <summary>
/// Writes a formatted string to the standard output stream, the formatting is performed as if done by
/// String_FormatCString().
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Console_WriteFormat_CStringV(const char *format, VarArgsList args);

/// <summary>
/// Writes a formatted string to the standard output stream, the formatting is performed as if done by
/// String_FormatString().
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Console_WriteFormat_String(const struct String *format, ...);

/// <summary>
/// Writes a formatted string to the standard output stream, the formatting is performed as if done by
/// String_FormatString().
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Console_WriteFormat_StringV(const struct String *format, VarArgsList args);

/// <summary>
/// Writes a line terminator to the standard output stream.
/// </summary>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void Console_WriteLine(void);

/// <summary>
/// Writes a null-terminated string followed by a line terminator to the standard output stream.
/// </summary>
/// <remarks>If <paramref name="value"/> is <see cref="null"/>, nothing is written.</remarks>
/// <param name="value">Pointer to the null-terminated string to write.</param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void Console_WriteLine_CString(const char *value);

/// <summary>
/// Writes a <see cref="String"/> followed by a line terminator to the standard output stream.
/// </summary>
/// <remarks>If <paramref name="value"/> is <see cref="null"/>, nothing is written.</remarks>
/// <param name="value">Pointer to the <see cref="String"/> to write.</param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
void Console_WriteLine_String(const struct String *value);

/// <summary>
/// Writes a formatted string followed by a line terminator to the standard output stream, the formatting is performed
/// as if done by String_FormatCString().
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Console_WriteLineFormat_CString(const char *format, ...);

/// <summary>
/// Writes a formatted string followed by a line terminator to the standard output stream, the formatting is performed
/// as if done by String_FormatCString().
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Console_WriteLineFormat_CStringV(const char *format, VarArgsList args);

/// <summary>
/// Writes a formatted string followed by a line terminator to the standard output stream, the formatting is performed
/// as if done by String_FormatString().
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="...">Objects to format according to the format specifiers in the format string.</param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Console_WriteLineFormat_String(const struct String *format, ...);

/// <summary>
/// Writes a formatted string followed by a line terminator to the standard output stream, the formatting is performed
/// as if done by String_FormatString().
/// </summary>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
///     A variable argument list containing the objects to format according to the format specifiers in the format
///     string.
/// </param>
/// <exception cref="::IOException">An I/O error occurs.</exception>
/// <exception cref="::ArgumentNullException"><paramref name="format"/> is <see cref="null"/>.</exception>
/// <exception cref="::FormatException"><paramref name="format"/> is invalid.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Console_WriteLineFormat_StringV(const struct String *format, VarArgsList args);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/Console.internal.h"
#endif

#endif
