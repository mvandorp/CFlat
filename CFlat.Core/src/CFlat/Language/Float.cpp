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

#include "CFlat/Language/Float.h"

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

const int Float::Radix = FLT_RADIX;
const int Float::MinExponent = FLT_MIN_EXP;
const int Float::MaxExponent = FLT_MAX_EXP;
const int Float::MinBase10Exponent = FLT_MIN_10_EXP;
const int Float::MaxBase10Exponent = FLT_MAX_10_EXP;
const float Float::MinValue = -FLT_MAX;
const float Float::MaxValue = FLT_MAX;
const float Float::Epsilon = FLT_EPSILON;
const float Float::MinPositiveValue = FLT_MIN;
const int Float::Digits = FLT_DIG;

/**************************************/
/* Public function definitions        */
/**************************************/

bool Float::IsNaN(float value)
{
#ifdef C99_math
    return isnan(value);
#else
    // HACK: Works only with IEEE-754 floating-point numbers.
    return value != value;
#endif
}

bool Float::IsInfinity(float value)
{
#ifdef C99_math
    return isinf(value);
#else
    return (value - value) != 0.0f && !Float::IsNaN(value);
#endif
}

bool Float::IsNegativeInfinity(float value)
{
#ifdef C99_math
    return isinf(value) && value < 0.0f;
#else
    return value < 0.0f && Float::IsInfinity(value);
#endif
}

bool Float::IsPositiveInfinity(float value)
{
#ifdef C99_math
    return isinf(value) && value > 0.0f;
#else
    return value > 0.0f && Float::IsInfinity(value);
#endif
}

float Float::Max(float x, float y) {
    return MAX(x, y);
}

float Float::Min(float x, float y) {
    return MIN(x, y);
}

String Float::ToString(float value)
{
    return Number::Format(value, nullptr);
}

String Float::ToString(float value, const String *format)
{
    return Number::Format(value, format);
}

void Float::ToString(StringBuilder &sb, float value, const String *format)
{
    Number::Format(sb, value, format);
}
