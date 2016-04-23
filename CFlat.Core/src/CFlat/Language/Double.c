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

#include "CFlat/Language/Double.h"

#include "CFlat.h"
#include "CFlat/Macros.h"
#include "CFlat/Number.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L || _MSC_VER >= 1700
 #include <math.h>
 #define C99_math
#endif

/**************************************/
/* Public function definitions        */
/**************************************/

public bool double_IsNaN(double value)
{
#ifdef C99_math
    return isnan(value);
#else
    // HACK: Works only with IEEE-754 floating-point numbers.
    return value != value;
#endif
}

public bool double_IsInfinity(double value)
{
#ifdef C99_math
    return isinf(value);
#else
    return (value - value) != 0.0 && !double_IsNaN(value);
#endif
}

public bool double_IsNegativeInfinity(double value)
{
#ifdef C99_math
    return isinf(value) && value < 0.0;
#else
    return value < 0.0 && double_IsInfinity(value);
#endif
}

public bool double_IsPositiveInfinity(double value)
{
#ifdef C99_math
    return isinf(value) && value > 0.0;
#else
    return value > 0.0 && double_IsInfinity(value);
#endif
}

public double double_Max(double x, double y) {
    return MAX(x, y);
}

public double double_Min(double x, double y) {
    return MIN(x, y);
}

public String *double_ToString(double value)
{
    return Number_FormatDouble(value, null);
}

public String *double_ToStringFormat(double value, const String *format)
{
    return Number_FormatDouble(value, format);
}

public String *double_ToStringFormatC(double value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return Number_FormatDouble(value, str);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void double_ToStringBuffered(StringBuilder *sb, double value, const String *format)
{
    Number_FormatDoubleBuffered(sb, value, format);
}
