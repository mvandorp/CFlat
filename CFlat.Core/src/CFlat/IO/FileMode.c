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

#include "CFlat/IO/FileMode.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

public bool FileMode_IsValid(FileMode mode)
{
    return
        mode == FileMode_Append ||
        mode == FileMode_Create ||
        mode == FileMode_CreateNew ||
        mode == FileMode_Open ||
        mode == FileMode_OpenOrCreate ||
        mode == FileMode_Truncate;
}

public void FileMode_Validate(FileMode mode)
{
    Validate_IsTrue(
        FileMode_IsValid(mode),
        ArgumentException,
        "Value was out of legal range for enum FileMode.");
}
