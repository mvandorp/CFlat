#include "CFlat/Language/Double.h"

#include "CFlat/Macros.h"

/**************************************/
/* Extern function definitions        */
/**************************************/

bool double_IsNaN(double value)
{
    // HACK: Works only with IEEE-754 floating-point numbers.
    return value != value;
}

bool double_IsInfinity(double value)
{
    return (value - value) != 0.0 && !double_IsNaN(value);
}

bool double_IsNegativeInfinity(double value)
{
    return value < 0.0 && double_IsInfinity(value);
}

bool double_IsPositiveInfinity(double value)
{
    return value > 0.0 && double_IsInfinity(value);
}

double double_Max(double x, double y) {
    return MAX(x, y);
}

double double_Min(double x, double y) {
    return MIN(x, y);
}
