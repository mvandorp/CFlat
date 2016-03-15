#include "CFlat/Language/Double.h"

#include "CFlat.h"
#include "CFlat/Macros.h"
#include "CFlat/Number.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (_MSC_VER >= 1700)
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
