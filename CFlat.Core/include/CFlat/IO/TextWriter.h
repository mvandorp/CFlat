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

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Pointers.h"
#include "CFlat/Language/VarArgs.h"

#include "CFlat/Environment.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"

#include <utility>

namespace CFlat {
    /* Types */
    /// <summary>
    /// Base class for objects that can write sequences of characters.
    /// </summary>
    class TextWriter {
    private:
        class NullWriter;

    public:
        /* Constants */
        /// <summary>
        /// A <see cref="TextWriter"/> with no backing store.
        /// </summary>
        static unique_ptr<TextWriter, NoOpDeleter<TextWriter>> Null();

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
        TextWriter();

        virtual ~TextWriter();

        /// <summary>
        /// Writes any unwritten data in the output buffer of a <see cref="TextWriter"/> to the underlying device.
        /// </summary>
        /// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual void Flush();

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
        virtual void Write(const char *buffer, uintsize offset, uintsize count) = 0;

        /// <summary>
        /// Writes a character to a <see cref="TextWriter"/>.
        /// </summary>
        /// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
        /// <param name="value">The character to write.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        template <typename T>
        inline void Write(T value)
        {
            StringBuilder sb = StringBuilder();
            sb.Append(value);

            uintsize length = sb.GetLength();

            //this->Write(StringBuilder::ToCString(std::move(sb)).Get(), 0, length);
        }
        
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
        virtual void WriteFormat(const char *format, ...);

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
        virtual void WriteFormatVA(const char *format, VarArgsList args);

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
        virtual void WriteFormat(String format, ...);

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
        virtual void WriteFormatVA(const String &format, VarArgsList args);

        /// <summary>
        /// Writes a line terminator to a <see cref="TextWriter"/>.
        /// </summary>
        /// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        virtual void WriteLine();

        /// <summary>
        /// Writes a character followed by a line terminator to a <see cref="TextWriter"/>.
        /// </summary>
        /// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
        /// <param name="value">The character to write.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        template <typename T>
        inline void WriteLine(T value)
        {
            StringBuilder sb = StringBuilder();
            sb.Append(value);
            sb.Append(Environment::NewLine);

            uintsize length = sb.GetLength();

            //this->Write(StringBuilder::ToCString(std::move(sb)).Get(), 0, length);
        }
        
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
        void WriteLineFormat(const char *format, ...);

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
        virtual void WriteLineFormatVA(const char *format, VarArgsList args);

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
        void WriteLineFormat(String format, ...);

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
        virtual void WriteLineFormatVA(const String &format, VarArgsList args);
    };

    template <>
    void TextWriter::Write<char>(char value);

    template <>
    void TextWriter::Write<const char*>(const char *value);

    template <>
    void TextWriter::Write<const String&>(const String &value);
        
    template <>
    void TextWriter::WriteLine<char>(char value);

    template <>
    void TextWriter::WriteLine<const char*>(const char *value);

    template <>
    void TextWriter::WriteLine<const String&>(const String &value);
}

#endif
