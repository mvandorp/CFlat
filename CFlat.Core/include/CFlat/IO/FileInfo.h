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

//! @file FileInfo.h

#ifndef CFLAT_CORE_IO_FILEINFO_H
#define CFLAT_CORE_IO_FILEINFO_H

#include "CFlat/Language/Integer.h"

#include "CFlat/String.h"

#include "CFlat/IO/FileAccess.h"
#include "CFlat/IO/FileMode.h"
#include "CFlat/IO/FileSystemInfo.h"

namespace CFlat {
    /* Forward declarations */
    class Stream;
    class TextReader;

    /* Types */
    class FileInfo : public FileSystemInfo {
    private:
        mutable intfsize _length;
        mutable String _name;

    public:
        FileInfo(String path);

        ~FileInfo();

        intfsize GetLength() const;

        unique_ptr<Stream> Open(FileMode::Enum mode, FileAccess::Enum access) const;

        unique_ptr<Stream> OpenRead() const;

        unique_ptr<Stream> OpenWrite() const;

        unique_ptr<TextReader> OpenText() const;

        /* FileSystemInfo */
        bool Exists() const override;

        String GetName() const override;

        void Delete() const override;
    };
}

#endif
