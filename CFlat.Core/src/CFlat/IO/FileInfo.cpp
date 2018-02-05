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

#include "CFlat/IO/FileInfo.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

#include "CFlat/IO/FileStream.h"
#include "CFlat/IO/Stream.h"
#include "CFlat/IO/StreamReader.h"
#include "CFlat/IO/TextReader.h"
#include "CFlat/IO/Path.h"

#include <utility>

using namespace CFlat;

/* Constructors / destructors */
FileInfo::FileInfo(String path) :
    FileSystemInfo(std::move(path)),
    _length(-1),
    _name(nullptr)
{
}

FileInfo::~FileInfo()
{
}

/* Properties */
bool FileInfo::Exists() const
{
    // TODO: Implement
    return false;
}

String FileInfo::GetName() const
{
    // TODO: Better lazy initialization!
    if (_name.IsEmpty()) {
        _name = Path::GetFileName(this->GetOriginalPath());
    }

    return _name;
}

intfsize FileInfo::GetLength() const
{
    // TODO: Better lazy initialization?
    if (_length == -1) {
        _length = this->OpenRead()->GetLength();
    }

    return _length;
}

/* Methods */
void FileInfo::Delete() const
{
    // TODO: Implement
}

unique_ptr<Stream> FileInfo::Open(FileMode::Enum mode, FileAccess::Enum access) const
{
    return unique_ptr<Stream>(new FileStream(this->GetOriginalPath(), mode, access));
}

unique_ptr<Stream> FileInfo::OpenRead() const
{
    return this->Open(FileMode::Open, FileAccess::Read);
}

unique_ptr<Stream> FileInfo::OpenWrite() const
{
    return this->Open(FileMode::Create, FileAccess::Write);
}

unique_ptr<TextReader> FileInfo::OpenText() const
{
    return unique_ptr<TextReader>(new StreamReader(this->GetOriginalPath()));
}
