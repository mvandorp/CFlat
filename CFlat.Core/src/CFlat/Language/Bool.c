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

#include "CFlat/Language/Bool.h"

#include "CFlat.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"

/* Private constants */

private String True = String_Initializer("true");
private String False = String_Initializer("false");

/**************************************/
/* Public function definitions        */
/**************************************/

public String *bool_ToString(bool value)
{
    if (value) return &True;

    return &False;
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void bool_ToStringBuffered(StringBuilder *sb, bool value)
{
    Validate_NotNull(sb);

    if (value) {
        StringBuilder_AppendCString(sb, "true");
    }
    else {
        StringBuilder_AppendCString(sb, "false");
    }
}
