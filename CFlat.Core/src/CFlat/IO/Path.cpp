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

#include "CFlat/IO/Path.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/String.h"

using namespace CFlat;

String Path::GetFileName(const String &path)
{
    uintsize lastSeperator = path.LastIndexOfAny("/\\");

    return path.Substring(lastSeperator + 1);
}

String Path::GetFileName(const char *path)
{
    uintsize lastSeperator = CString::LastIndexOfAny(path, "/\\");

    return CString::Substring(path, lastSeperator + 1);
}
