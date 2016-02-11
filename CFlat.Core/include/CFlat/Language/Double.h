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
 * @file Double.h
 */

#ifndef CFLAT_CORE_LANGUAGE_DOUBLE_H
#define CFLAT_CORE_LANGUAGE_DOUBLE_H

#include "CFlat/Language/Bool.h"

#include <float.h>

 /// <summary>
 /// The radix used for the <see cref="double"/> type.
 /// </summary>
#define double_Radix ((int)FLT_RADIX)

/// <summary>
/// The minimum exponent that generates a normalized <see cref="double"/> value.
/// </summary>
#define double_MinExponent ((int)DBL_MIN_EXP)

/// <summary>
/// The maximum exponent that generates a normalized <see cref="double"/> value.
/// </summary>
#define double_MaxExponent ((int)DBL_MAX_EXP)

/// <summary>
/// The minimum exponent of a base 10 expression that generates a normalized <see cref="double"/> value.
/// </summary>
#define double_MinBase10Exponent ((int)DBL_MIN_10_EXP)

/// <summary>
/// The maximum exponent of a base 10 expression that generates a normalized <see cref="double"/> value.
/// </summary>
#define double_MaxBase10Exponent ((int)DBL_MAX_10_EXP)

/// <summary>
/// Represents the smallest possible value of <see cref="double"/>.
/// </summary>
#define double_MinValue ((double)DBL_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="double"/>.
/// </summary>
#define double_MaxValue ((double)DBL_MAX)

/// <summary>
/// Represents the smallest possible <see cref="double"/> value that is greater than zero.
/// </summary>
#define double_Epsilon ((double)DBL_EPSILON)

/// <summary>
/// Represents the number of decimal digits a <see cref="double"/> can accurately represent.
/// </summary>
#define double_Digits ((int)DBL_DIG)

/* Functions */

/// <summary>
/// Returns whether the given number is not a number (<c>NaN</c>).
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns><see cref="true"/> if the <paramref name="value"/> is <c>NaN</c>; otherwise <see cref="false"/>.</returns>
bool double_IsNaN(double value);

/// <summary>
/// Returns whether the given number is negative or positive infinity.
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
/// <see cref="true"/> if the <paramref name="value"/> is negative or positive infinity; otherwise <see cref="false"/>.
/// </returns>
bool double_IsInfinity(double value);

/// <summary>
/// Returns whether the given number is negative infinity.
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
/// <see cref="true"/> if the <paramref name="value"/> is negative infinity; otherwise <see cref="false"/>.
/// </returns>
bool double_IsNegativeInfinity(double value);

/// <summary>
/// Returns whether the given number is positive infinity.
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
/// <see cref="true"/> if the <paramref name="value"/> is positive infinity; otherwise <see cref="false"/>.
/// </returns>
bool double_IsPositiveInfinity(double value);

#endif
