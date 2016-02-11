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

#include "CFlat/StringHelper.h"

#include "CFlat.h"
#include "CFlat/CString.h"

String String_WrapCString(const char *value)
{
    String str;

    // Do not set the destructor to prevent the value from being deallocated.
    Object_Constructor(&str, null);

    // Initialize the string.
    if (value == null) {
        str.length = 0;
        str.value = "";
    }
    else {
        str.length = CString_Length(value);
        str.value = value;
    }

    return str;
}
