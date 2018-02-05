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

#include "CFlat/String.h"

namespace CFlat {
    class StringBuilder;

    class Float {
    public:
        /* Static class */
        Float() = delete;

        /* Constants */
        /// <summary>
        /// The radix used for the <see cref="float"/> type.
        /// </summary>
        static const int Radix;

        /// <summary>
        /// The minimum exponent that generates a normalized <see cref="float"/> value.
        /// </summary>
        static const int MinExponent;

        /// <summary>
        /// The maximum exponent that generates a normalized <see cref="float"/> value.
        /// </summary>
        static const int MaxExponent;

        /// <summary>
        /// The minimum exponent of a base 10 expression that generates a normalized <see cref="float"/> value.
        /// </summary>
        static const int MinBase10Exponent;

        /// <summary>
        /// The maximum exponent of a base 10 expression that generates a normalized <see cref="float"/> value.
        /// </summary>
        static const int MaxBase10Exponent;

        /// <summary>
        /// The smallest possible value of <see cref="float"/>.
        /// </summary>
        static const float MinValue;

        /// <summary>
        /// The largest possible value of <see cref="float"/>.
        /// </summary>
        static const float MaxValue;

        /// <summary>
        /// The difference between 1 and the smallest value greater than 1 that can be represented by <see cref="float"/>.
        /// </summary>
        static const float Epsilon;

        /// <summary>
        /// The smallest possible normalized value of <see cref="float"/> that is greater than zero.
        /// </summary>
        static const float MinPositiveValue;

        /// <summary>
        /// The number of decimal digits a <see cref="float"/> can accurately represent.
        /// </summary>
        static const int Digits;

        /* Functions */
        /// <summary>
        /// Determines whether the given number is not a number (<c>NaN</c>).
        /// </summary>
        /// <param name="value">The number to check.</param>
        /// <returns>
        ///     <see cref="true"/> if the <paramref name="value"/> is <c>NaN</c>; otherwise, <see cref="false"/>.
        /// </returns>
        static bool IsNaN(float value);

        /// <summary>
        /// Determines whether the given number is negative or positive infinity.
        /// </summary>
        /// <param name="value">The number to check.</param>
        /// <returns>
        ///     <see cref="true"/> if the <paramref name="value"/> is negative or positive infinity;
        ///     otherwise, <see cref="false"/>.
        /// </returns>
        static bool IsInfinity(float value);

        /// <summary>
        /// Determines whether the given number is negative infinity.
        /// </summary>
        /// <param name="value">The number to check.</param>
        /// <returns>
        ///     <see cref="true"/> if the <paramref name="value"/> is negative infinity; otherwise, <see cref="false"/>.
        /// </returns>
        static bool IsNegativeInfinity(float value);

        /// <summary>
        /// Determines whether the given number is positive infinity.
        /// </summary>
        /// <param name="value">The number to check.</param>
        /// <returns>
        ///     <see cref="true"/> if the <paramref name="value"/> is positive infinity; otherwise, <see cref="false"/>.
        /// </returns>
        static bool IsPositiveInfinity(float value);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static float Max(float x, float y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static float Min(float x, float y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(float value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(float value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, float value, const String *format);
    };
}

#endif
