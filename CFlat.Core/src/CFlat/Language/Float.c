#include "CFlat/Language/Float.h"

#include "CFlat/Macros.h"

/**************************************/
/* Extern function definitions        */
/**************************************/

bool float_IsNaN(float value)
{
    // HACK: Works only with IEEE-754 floating-point numbers.
    return value != value;
}

bool float_IsInfinity(float value)
{
    return (value - value) != 0.0f && !float_IsNaN(value);
}

bool float_IsNegativeInfinity(float value)
{
    return value < 0.0f && float_IsInfinity(value);
}

bool float_IsPositiveInfinity(float value)
{
    return value > 0.0f && float_IsInfinity(value);
}

float float_Max(float x, float y) {
    return MAX(x, y);
}

float float_Min(float x, float y) {
    return MIN(x, y);
}
