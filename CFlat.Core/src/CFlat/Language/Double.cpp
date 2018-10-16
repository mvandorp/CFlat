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
#include "CFlat/StringBuilder.h"

#include <cfloat>

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L || defined(_MSC_VER) && _MSC_VER >= 1700
 #include <cmath>
 #define C99_math
#endif

using namespace CFlat;

const int Double::Radix = FLT_RADIX;
const int Double::MinExponent = DBL_MIN_EXP;
const int Double::MaxExponent = DBL_MAX_EXP;
const int Double::MinBase10Exponent = DBL_MIN_10_EXP;
const int Double::MaxBase10Exponent = DBL_MAX_10_EXP;
const double Double::MinValue = -DBL_MAX;
const double Double::MaxValue = DBL_MAX;
const double Double::Epsilon = DBL_EPSILON;
const double Double::MinPositiveValue = DBL_MIN;
const int Double::Digits = DBL_DIG;

/**************************************/
/* Public function definitions        */
/**************************************/

bool Double::IsNaN(double value)
{
#ifdef C99_math
    return isnan(value);
#else
    // HACK: Works only with IEEE-754 doubleing-point numbers.
    return value != value;
#endif
}

bool Double::IsInfinity(double value)
{
#ifdef C99_math
    return isinf(value);
#else
    return (value - value) != 0.0f && !Double::IsNaN(value);
#endif
}

bool Double::IsNegativeInfinity(double value)
{
#ifdef C99_math
    return isinf(value) && value < 0.0f;
#else
    return value < 0.0f && Double::IsInfinity(value);
#endif
}

bool Double::IsPositiveInfinity(double value)
{
#ifdef C99_math
    return isinf(value) && value > 0.0f;
#else
    return value > 0.0f && Double::IsInfinity(value);
#endif
}

double Double::Max(double x, double y) {
    return MAX(x, y);
}

double Double::Min(double x, double y) {
    return MIN(x, y);
}

String Double::ToString(double value)
{
    return Number::Format(value, nullptr);
}

String Double::ToString(double value, const String *format)
{
    return Number::Format(value, format);
}

void Double::ToString(StringBuilder &sb, double value, const String *format)
{
    return Number::Format(sb, value, format);
}
