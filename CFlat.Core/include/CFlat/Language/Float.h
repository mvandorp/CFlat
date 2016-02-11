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

/**
 * @file Float.h
 */

#ifndef CFLAT_CORE_LANGUAGE_FLOAT_H
#define CFLAT_CORE_LANGUAGE_FLOAT_H

#include "CFlat/Language/Boolean.h"

#include <float.h>

 /// <summary>
 /// The radix used for the <see cref="float"/> type.
 /// </summary>
#define float_Radix ((int)FLT_RADIX)

/// <summary>
/// The minimum exponent that generates a normalized <see cref="float"/> value.
/// </summary>
#define float_MinExponent ((int)FLT_MIN_EXP)

/// <summary>
/// The maximum exponent that generates a normalized <see cref="float"/> value.
/// </summary>
#define float_MaxExponent ((int)FLT_MAX_EXP)

/// <summary>
/// The minimum exponent of a base 10 expression that generates a normalized <see cref="float"/> value.
/// </summary>
#define float_MinBase10Exponent ((int)FLT_MIN_10_EXP)

/// <summary>
/// The maximum exponent of a base 10 expression that generates a normalized <see cref="float"/> value.
/// </summary>
#define float_MaxBase10Exponent ((int)FLT_MAX_10_EXP)

 /// <summary>
/// Represents the smallest possible value of <see cref="float"/>.
/// </summary>
#define float_MinValue ((float)FLT_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="float"/>.
/// </summary>
#define float_MaxValue ((float)FLT_MAX)

/// <summary>
/// Represents the smallest possible <see cref="float"/> value that is greater than zero.
/// </summary>
#define float_Epsilon ((float)FLT_EPSILON)

/// <summary>
/// Represents the number of decimal digits a <see cref="float"/> can accurately represent.
/// </summary>
#define float_Digits ((int)FLT_DIG)

/* Functions */

/// <summary>
/// Returns whether the given number is not a number (<c>NaN</c>).
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns><see cref="true"/> if the <paramref name="value"/> is <c>NaN</c>; otherwise <see cref="false"/>.</returns>
bool float_IsNaN(float value);

/// <summary>
/// Returns whether the given number is negative or positive infinity.
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
/// <see cref="true"/> if the <paramref name="value"/> is negative or positive infinity; otherwise <see cref="false"/>.
/// </returns>
bool float_IsInfinity(float value);

/// <summary>
/// Returns whether the given number is negative infinity.
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
/// <see cref="true"/> if the <paramref name="value"/> is negative infinity; otherwise <see cref="false"/>.
/// </returns>
bool float_IsNegativeInfinity(float value);

/// <summary>
/// Returns whether the given number is positive infinity.
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
/// <see cref="true"/> if the <paramref name="value"/> is positive infinity; otherwise <see cref="false"/>.
/// </returns>
bool float_IsPositiveInfinity(float value);

#endif
