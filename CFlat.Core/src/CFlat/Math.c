#include "CFlat/Math.h"

#include "CFlat.h"

#include <math.h>

public double Math_Abs(double x)
{
    return fabs(x);
}

public double Math_Acos(double x)
{
    return acos(x);
}

public double Math_Asin(double x)
{
    return asin(x);
}

public double Math_Atan(double x)
{
    return atan(x);
}

public double Math_Atan2(double y, double x)
{
    return atan2(y, x);
}

public double Math_Ceil(double x)
{
    return ceil(x);
}

public double Math_Cos(double x)
{
    return cos(x);
}

public double Math_Cosh(double x)
{
    return cosh(x);
}

public double Math_Exp(double x)
{
    return exp(x);
}

public double Math_Floor(double x)
{
    return floor(x);
}

public double Math_Log(double x)
{
    return log(x);
}

public double Math_Log10(double x)
{
    return log10(x);
}

public double Math_Logb(double x, double base)
{
    return Math_Log(x) / Math_Log(base);
}

public double Math_Max(double x, double y)
{
    return (x >= y) ? x : y;
}

public double Math_Min(double x, double y)
{
    return (x <= y) ? x : y;
}

public double Math_Mod(double x, double y)
{
    return fmod(x, y);
}

public double Math_Pow(double x, double y)
{
    return pow(x, y);
}

public double Math_Remainder(double x, double y)
{
    return x - y * Math_Round(x / y);
}

public double Math_Round(double x)
{
    return round(x);
}

public double Math_Sin(double x)
{
    return sin(x);
}

public double Math_Sinh(double x)
{
    return sinh(x);
}

public double Math_Sqrt(double x)
{
    return sqrt(x);
}

public double Math_Tan(double x)
{
    return tan(x);
}

public double Math_Tanh(double x)
{
    return tanh(x);
}

public double Math_Truncate(double x)
{
    return trunc(x);
}
