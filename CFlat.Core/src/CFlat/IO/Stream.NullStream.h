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

#ifndef CFLAT_CORE_IO_STREAM_NULLSTREAM_H
#define CFLAT_CORE_IO_STREAM_NULLSTREAM_H

#include "CFlat/Validate.h"

#include "CFlat/IO/Stream.h"

namespace CFlat {
    class Stream::NullStream : public Stream {
    public:
        inline bool CanRead() const override
        {
            return true;
        }

        inline bool CanSeek() const override
        {
            return true;
        }

        inline bool CanWrite() const override
        {
            return true;
        }

        inline intfsize GetLength() const override
        {
            return 0;
        }

        inline void SetLength(intfsize length) override
        {
            (void)length;
        }

        inline intfsize GetPosition() const override
        {
            return 0;
        }

        inline void SetPosition(intfsize position) override
        {
            (void)position;
        }

        inline void Flush() override
        {
        }

        inline uintsize Read(byte *buffer, uintsize offset, uintsize count) override
        {
            Validate_NotNull(buffer);

            (void)offset;
            (void)count;

            return 0;
        }

        inline intfsize Seek(intfsize offset, SeekOrigin::Enum origin) override
        {
            (void)offset;
            (void)origin;

            return 0;
        }

        inline void Write(const byte *buffer, uintsize offset, uintsize count) override
        {
            Validate_NotNull(buffer);

            (void)offset;
            (void)count;
        }
    };
}

#endif
