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

//! @file Math.h

#ifndef CFLAT_CORE_MATH_H
#define CFLAT_CORE_MATH_H

/// <summary>
/// Returns the absolute value of the specified number.
/// </summary>
/// <param name="x">A floating-point number.</param>
/// <returns>The absolute value of the specified number.</returns>
double Math_Abs(double x);

/// <summary>
/// Returns the angle whose cosine is the specified number.
/// </summary>
/// <param name="x">A number representing a cosine, where <paramref name="x"/> must be in the range [-1, 1].</param>
/// <returns>The angle whose cosine is the specified number.</returns>
double Math_Acos(double x);

/// <summary>
/// Returns the angle whose sine is the specified number.
/// </summary>
/// <param name="x">A number representing a sine, where <paramref name="x"/> must be in the range [-1, 1].</param>
/// <returns>The angle whose sine is the specified number.</returns>
double Math_Asin(double x);

/// <summary>
/// Returns the angle whose tangent is the specified number.
/// </summary>
/// <param name="x">A number representing a tangent.</param>
/// <returns>The angle whose tangent is the specified number.</returns>
double Math_Atan(double x);

/// <summary>
/// Returns the angle whose tangent is the quotient of two specified numbers.
/// </summary>
/// <param name="y">A number representing the y coordinate of a point.</param>
/// <param name="x">A number representing the x coordinate of a point.</param>
/// <returns>The angle whose tangent is the quotient of two specified numbers.</returns>
double Math_Atan2(double y, double x);

/// <summary>
/// Returns the smallest integral value that is greater than or equal to the specified number.
/// </summary>
/// <param name="x">A floating-point number.</param>
/// <returns>
/// The smallest integral value that is greater than or equal to the specified number.
/// </returns>
double Math_Ceil(double x);

/// <summary>
/// Returns the cosine of the specified angle.
/// </summary>
/// <param name="x">An angle, measured in radians.</param>
/// <returns>The cosine of <paramref name="x"/>.</returns>
double Math_Cos(double x);

/// <summary>
/// Returns the hyperbolic cosine of the specified angle.
/// </summary>
/// <param name="x">An angle, measured in radians.</param>
/// <returns>The hyperbolic cosine of <paramref name="x"/>.</returns>
double Math_Cosh(double x);

/// <summary>
/// Returns <c>e</c> raised to the specified power.
/// </summary>
/// <param name="x">A number specifying a power.</param>
/// <returns>The number <c>e</c> raised to the power <paramref name="x"/>.</returns>
double Math_Exp(double x);

/// <summary>
/// Returns the largest integer less than or equal to the specified number.
/// </summary>
/// <param name="x">A floating-point number.</param>
/// <returns>The largest integer less than or equal to the specified number.</returns>
double Math_Floor(double x);

/// <summary>
/// Returns the natural logarithm of the specified number.
/// </summary>
/// <param name="x">The number of which to find the natural logarithm.</param>
/// <returns>The natural logarithm of the specified number.</returns>
double Math_Log(double x);

/// <summary>
/// Returns the base 10 logarithm of the specified number.
/// </summary>
/// <param name="x">The number of which to find the base 10 logarithm.</param>
/// <returns>The base 10 logarithm of the specified number.</returns>
double Math_Log10(double x);

/// <summary>
/// Returns the logarithm of a specified number in a specified base.
/// </summary>
/// <param name="x">A number of which to find the logarithm.</param>
/// <param name="base">A number specifying base of the logarithm.</param>
/// <returns>The base 10 logarithm of the specified number.</returns>
double Math_Logb(double x, double base);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">A floating-point number.</param>
/// <param name="y">A floating-point number.</param>
/// <returns>The larger of two numbers.</returns>
double Math_Max(double x, double y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">A floating-point number.</param>
/// <param name="y">A floating-point number.</param>
/// <returns>The smaller of two numbers.</returns>
double Math_Min(double x, double y);

/// <summary>
/// Returns the remainder resulting from the division of two specified numbers rounded towards zero.
/// </summary>
/// <param name="x">A number specifying the numerator.</param>
/// <param name="y">A number specifying the denominator.</param>
/// <returns>The remainder resulting from the division of two specified numbers.</returns>
double Math_Mod(double x, double y);

/// <summary>
/// Raises a specified number raised to the specified power.
/// </summary>
/// <param name="x">A number to be raised to a power.</param>
/// <param name="y">A number specifying a power.</param>
/// <returns>The number <paramref name="x"/> raised to the power <paramref name="y"/>.</returns>
double Math_Pow(double x, double y);

/// <summary>
/// Returns the remainder resulting from the division of two specified numbers rounded towards nearest.
/// </summary>
/// <param name="x">A number specifying the numerator.</param>
/// <param name="y">A number specifying the denominator.</param>
/// <returns>The remainder resulting from the division of two specified numbers.</returns>
double Math_Remainder(double x, double y);

/// <summary>
/// Rounds a specified number to the nearest integral value.
/// </summary>
/// <param name="x">A floating-point number.</param>
/// <returns>
/// The integer nearest <paramref name="x"/>. If the fractional component of <paramref name="x"/> is halfway between
/// two integers, one of which is even and the other odd, then the even number is returned.
/// </returns>
double Math_Round(double x);

/// <summary>
/// Returns the sine of the specified angle.
/// </summary>
/// <param name="x">An angle, measured in radians.</param>
/// <returns>The sine of <paramref name="x"/>.</returns>
double Math_Sin(double x);

/// <summary>
/// Returns the hyperbolic sine of the specified angle.
/// </summary>
/// <param name="x">An angle, measured in radians.</param>
/// <returns>The hyperbolic sine of <paramref name="x"/>.</returns>
double Math_Sinh(double x);

/// <summary>
/// Returns the square root of the specified number.
/// </summary>
/// <param name="x">The number of which to find the square root.</param>
/// <returns>The square root of <paramref name="x"/>.</returns>
double Math_Sqrt(double x);

/// <summary>
/// Returns the tangent of the specified angle.
/// </summary>
/// <param name="x">An angle, measured in radians.</param>
/// <returns>The tangent of <paramref name="x"/>.</returns>
double Math_Tan(double x);

/// <summary>
/// Returns the hyperbolic tangent of the specified angle.
/// </summary>
/// <param name="x">An angle, measured in radians.</param>
/// <returns>The hyperbolic tangent of <paramref name="x"/>.</returns>
double Math_Tanh(double x);

/// <summary>
/// Returns the integral part of a specified number.
/// </summary>
/// <param name="x">A floating-point number.</param>
/// <returns>The integral part of a specified number.</returns>
double Math_Truncate(double x);

#endif
