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

//! @file FileSystemInfo.h

#ifndef CFLAT_CORE_IO_FILESYSTEMINFO_H
#define CFLAT_CORE_IO_FILESYSTEMINFO_H

#include "CFlat/Language/Pointers.h"

#include "CFlat/String.h"

namespace CFlat {
    class FileSystemInfo {
    private:
        String _path;

    public:
        /* Constructors */
        FileSystemInfo(String path);

        /* Destructor */
        virtual ~FileSystemInfo();

        /* Properties */
        virtual bool Exists() const = 0;

        virtual String GetName() const = 0;

        String GetOriginalPath() const;

        /* Methods */
        virtual void Delete() const = 0;
    };
}

#endif
