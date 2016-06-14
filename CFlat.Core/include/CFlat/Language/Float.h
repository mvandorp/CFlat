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

//! @file Float.h

#ifndef CFLAT_CORE_LANGUAGE_FLOAT_H
#define CFLAT_CORE_LANGUAGE_FLOAT_H

#include "CFlat/Language/Bool.h"

#include <float.h>

struct String;

/* Macros */
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
/// The smallest possible value of <see cref="float"/>.
/// </summary>
#define float_MinValue ((float)-FLT_MAX)

/// <summary>
/// The largest possible value of <see cref="float"/>.
/// </summary>
#define float_MaxValue ((float)FLT_MAX)

/// <summary>
/// The difference between 1 and the smallest value greater than 1 that can be represented by <see cref="float"/>.
/// </summary>
#define float_Epsilon ((float)FLT_EPSILON)

/// <summary>
/// The smallest possible normalized value of <see cref="float"/> that is greater than zero.
/// </summary>
#define float_MinPositiveValue ((float)FLT_MIN)

/// <summary>
/// The number of decimal digits a <see cref="float"/> can accurately represent.
/// </summary>
#define float_Digits ((int)FLT_DIG)

/* Functions */
/// <summary>
/// Determines whether the given number is not a number (<c>NaN</c>).
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
///     <see cref="true"/> if the <paramref name="value"/> is <c>NaN</c>; otherwise, <see cref="false"/>.
/// </returns>
bool float_IsNaN(float value);

/// <summary>
/// Determines whether the given number is negative or positive infinity.
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
///     <see cref="true"/> if the <paramref name="value"/> is negative or positive infinity;
///     otherwise, <see cref="false"/>.
/// </returns>
bool float_IsInfinity(float value);

/// <summary>
/// Determines whether the given number is negative infinity.
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
///     <see cref="true"/> if the <paramref name="value"/> is negative infinity; otherwise, <see cref="false"/>.
/// </returns>
bool float_IsNegativeInfinity(float value);

/// <summary>
/// Determines whether the given number is positive infinity.
/// </summary>
/// <param name="value">The number to check.</param>
/// <returns>
///     <see cref="true"/> if the <paramref name="value"/> is positive infinity; otherwise, <see cref="false"/>.
/// </returns>
bool float_IsPositiveInfinity(float value);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
float float_Max(float x, float y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
float float_Min(float x, float y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct String *float_ToString(float value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct String *float_ToStringFormat(float value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct String *float_ToStringFormatC(float value, const char *format);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/Language/Float.internal.h"
#endif

#endif
