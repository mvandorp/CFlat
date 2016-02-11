#include "CFlat/Math.h"

#include <math.h>

double Math_Abs(double x)
{
    return fabs(x);
}

double Math_Acos(double x)
{
    return acos(x);
}

double Math_Asin(double x)
{
    return asin(x);
}

double Math_Atan(double x)
{
    return atan(x);
}

double Math_Atan2(double y, double x)
{
    return atan2(y, x);
}

double Math_Ceil(double x)
{
    return ceil(x);
}

double Math_Cos(double x)
{
    return cos(x);
}

double Math_Cosh(double x)
{
    return cosh(x);
}

double Math_Exp(double x)
{
    return exp(x);
}

double Math_Floor(double x)
{
    return floor(x);
}

double Math_Log(double x)
{
    return log(x);
}

double Math_Log10(double x)
{
    return log10(x);
}

double Math_Logb(double x, double base)
{
    return Math_Log(x) / Math_Log(base);
}

double Math_Max(double x, double y)
{
    return (x >= y) ? x : y;
}

double Math_Min(double x, double y)
{
    return (x <= y) ? x : y;
}

double Math_Mod(double x, double y)
{
    return fmod(x, y);
}

double Math_Pow(double x, double y)
{
    return pow(x, y);
}

double Math_Remainder(double x, double y)
{
    return x - y * Math_Round(x / y);
}

double Math_Round(double x)
{
    return round(x);
}

double Math_Sin(double x)
{
    return sin(x);
}

double Math_Sinh(double x)
{
    return sinh(x);
}

double Math_Sqrt(double x)
{
    return sqrt(x);
}

double Math_Tan(double x)
{
    return tan(x);
}

double Math_Tanh(double x)
{
    return tanh(x);
}

double Math_Truncate(double x)
{
    return trunc(x);
}
