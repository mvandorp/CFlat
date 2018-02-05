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

#include "CFlat/IO/FileAccess.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

using namespace CFlat;

bool FileAccess::IsValid(FileAccess::Enum fileAccess)
{
    return
        FileAccess::HasFlag(fileAccess, FileAccess::Read) ||
        FileAccess::HasFlag(fileAccess, FileAccess::Write);
}

void FileAccess::Validate(FileAccess::Enum fileAccess)
{
    Validate_Argument(FileAccess::IsValid(fileAccess),
        "Value was out of legal range for enum FileAccess.", "fileAccess");
}
