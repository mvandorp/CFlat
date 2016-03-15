#include "CFlat/Language/Float.h"

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

public bool float_IsNaN(float value)
{
#ifdef C99_math
    return isnan(value);
#else
    // HACK: Works only with IEEE-754 floating-point numbers.
    return value != value;
#endif
}

public bool float_IsInfinity(float value)
{
#ifdef C99_math
    return isinf(value);
#else
    return (value - value) != 0.0f && !float_IsNaN(value);
#endif
}

public bool float_IsNegativeInfinity(float value)
{
#ifdef C99_math
    return isinf(value) && value < 0.0f;
#else
    return value < 0.0f && float_IsInfinity(value);
#endif
}

public bool float_IsPositiveInfinity(float value)
{
#ifdef C99_math
    return isinf(value) && value > 0.0f;
#else
    return value > 0.0f && float_IsInfinity(value);
#endif
}

public float float_Max(float x, float y) {
    return MAX(x, y);
}

public float float_Min(float x, float y) {
    return MIN(x, y);
}

public String *float_ToString(float value)
{
    return Number_FormatSingle(value, null);
}

public String *float_ToStringFormat(float value, const String *format)
{
    return Number_FormatSingle(value, format);
}

public String *float_ToStringFormatC(float value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return Number_FormatSingle(value, str);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void float_ToStringBuffered(StringBuilder *sb, float value, const String *format)
{
    Number_FormatSingleBuffered(sb, value, format);
}
