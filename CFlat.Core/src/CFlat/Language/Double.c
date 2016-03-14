#include "CFlat/Language/Double.h"

#include "CFlat.h"
#include "CFlat/Macros.h"
#include "CFlat/Number.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"

/**************************************/
/* Public function definitions        */
/**************************************/

public bool double_IsNaN(double value)
{
    // HACK: Works only with IEEE-754 floating-point numbers.
    return value != value;
}

public bool double_IsInfinity(double value)
{
    return (value - value) != 0.0 && !double_IsNaN(value);
}

public bool double_IsNegativeInfinity(double value)
{
    return value < 0.0 && double_IsInfinity(value);
}

public bool double_IsPositiveInfinity(double value)
{
    return value > 0.0 && double_IsInfinity(value);
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
