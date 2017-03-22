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

public String *Path_GetFileName(const String *path)
{
    if (path == null) return null;

    uintsize lastSeperator = String_LastIndexOfAny(path, "/\\");

    return String_Substring(path, lastSeperator + 1);
}

public String *Path_GetFileName_CString(const char *path)
{
    if (path == null) return null;

    uintsize lastSeperator = CString_LastIndexOfAny(path, "/\\");

    return CString_Substring(path, lastSeperator + 1);
}
