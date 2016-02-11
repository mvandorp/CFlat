#include "CFlat/Language/Float.h"

#include "CFlat.h"
#include "CFlat/Macros.h"

public bool float_IsNaN(float value)
{
    // HACK: Works only with IEEE-754 floating-point numbers.
    return value != value;
}

public bool float_IsInfinity(float value)
{
    return (value - value) != 0.0f && !float_IsNaN(value);
}

public bool float_IsNegativeInfinity(float value)
{
    return value < 0.0f && float_IsInfinity(value);
}

public bool float_IsPositiveInfinity(float value)
{
    return value > 0.0f && float_IsInfinity(value);
}

public float float_Max(float x, float y) {
    return MAX(x, y);
}

public float float_Min(float x, float y) {
    return MIN(x, y);
}
