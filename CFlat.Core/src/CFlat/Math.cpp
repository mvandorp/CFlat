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

#include "CFlat/Math.h"

#include <math.h>

using namespace CFlat;

double Math::Abs(double x)
{
    return fabs(x);
}

double Math::Acos(double x)
{
    return acos(x);
}

double Math::Asin(double x)
{
    return asin(x);
}

double Math::Atan(double x)
{
    return atan(x);
}

double Math::Atan2(double y, double x)
{
    return atan2(y, x);
}

double Math::Ceil(double x)
{
    return ceil(x);
}

double Math::Cos(double x)
{
    return cos(x);
}

double Math::Cosh(double x)
{
    return cosh(x);
}

double Math::Exp(double x)
{
    return exp(x);
}

double Math::Floor(double x)
{
    return floor(x);
}

double Math::Log(double x)
{
    return log(x);
}

double Math::Log10(double x)
{
    return log10(x);
}

double Math::Logb(double x, double base)
{
    return Math::Log(x) / Math::Log(base);
}

double Math::Max(double x, double y)
{
    return (x >= y) ? x : y;
}

double Math::Min(double x, double y)
{
    return (x <= y) ? x : y;
}

double Math::Mod(double x, double y)
{
    return fmod(x, y);
}

double Math::Pow(double x, double y)
{
    return pow(x, y);
}

double Math::Remainder(double x, double y)
{
    return x - y * Math::Round(x / y);
}

double Math::Round(double x)
{
    return round(x);
}

double Math::Sin(double x)
{
    return sin(x);
}

double Math::Sinh(double x)
{
    return sinh(x);
}

double Math::Sqrt(double x)
{
    return sqrt(x);
}

double Math::Tan(double x)
{
    return tan(x);
}

double Math::Tanh(double x)
{
    return tanh(x);
}

double Math::Truncate(double x)
{
    return trunc(x);
}
