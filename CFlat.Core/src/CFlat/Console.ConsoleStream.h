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

#ifndef CFLAT_CORE_CONSOLE_CONSOLESTREAM_H
#define CFLAT_CORE_CONSOLE_CONSOLESTREAM_H

#include "CFlat/IO/FileAccess.h"
#include "CFlat/IO/Stream.h"

//#include <cstdio>

namespace CFlat {
    class ConsoleStream : public Stream {
    private:
        int *_file;
        FileAccess::Enum _access;

        void ValidateReadSupported() const;
        void ValidateSeekSupported() const;
        void ValidateWriteSupported() const;

    public:
        ConsoleStream(int *file, FileAccess::Enum fileAccess);
        ~ConsoleStream();

        /* Properties */
        bool CanRead() const override;
        bool CanSeek() const override;
        bool CanWrite() const override;

        intfsize GetLength() const override;
        void SetLength(intfsize length) override;

        intfsize GetPosition() const override;
        void SetPosition(intfsize position) override;

        /* Methods */
        void Flush() override;
        uintsize Read(byte *buffer, uintsize offset, uintsize count) override;
        intfsize Seek(intfsize offset, SeekOrigin::Enum origin) override;
        void Write(const byte *buffer, uintsize offset, uintsize count) override;
    };
}

#endif
