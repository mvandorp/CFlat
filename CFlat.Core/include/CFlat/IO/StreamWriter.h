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

#include "CFlat/Language/Pointers.h"

#include "CFlat/IO/TextWriter.h"

namespace CFlat {
    /* Forward declarations */
    class Stream;

    /// <summary>
    /// Implements a <see cref="TextWriter"/> for writing characters to a <see cref="Stream"/>.
    /// </summary>
    class StreamWriter : public TextWriter {
    private:
        bool _autoFlush;
        unique_ptr<Stream> _stream;

    public:
        StreamWriter() = delete;

        StreamWriter(const StreamWriter &writer) = delete;

        StreamWriter(StreamWriter &&writer);

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
        StreamWriter(unique_ptr<Stream> stream);

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
        StreamWriter(const String &path, bool append);

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
        StreamWriter(const char *path, bool append);

        virtual ~StreamWriter();

        StreamWriter &operator=(const StreamWriter &writer) = delete;

        StreamWriter &operator=(StreamWriter &&writer);

        /// <summary>
        /// Gets whether or not a <see cref="TextWriter"/> will automatically flush its buffer to the underlying device after
        /// every call to Write().
        /// </summary>
        /// <returns>
        ///     <see cref="true"/> if automatic flushing of the buffer is enabled; otherwise, <see cref="false"/>.
        /// </returns>
        /// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
        bool GetAutoFlush() const;

        /// <summary>
        /// Sets whether or not a <see cref="TextWriter"/> will automatically flush its buffer to the underlying device after
        /// every call to Write().
        /// </summary>
        /// <param name="writer">Pointer to a <see cref="TextWriter"/>.</param>
        /// <param name="value">
        ///     <see cref="true"/> to enable automatic flushing of the buffer is enabled; otherwise, <see cref="false"/>.
        /// </param>
        /// <exception cref="::ArgumentNullException"><paramref name="writer"/> is <see cref="null"/>.</exception>
        /// <exception cref="::IOException">An I/O error occurs.</exception>
        void SetAutoFlush(bool value);

        void Flush() override;

        void Write(const char *buffer, uintsize offset, uintsize count) override;
    };
}

#endif
