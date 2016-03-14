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

#ifndef CFLAT_CORE_NUMBER_H
#define CFLAT_CORE_NUMBER_H

#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"

/* Forward declarations */
typedef struct String String;
typedef struct StringBuilder StringBuilder;

/* Functions */
/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal String *Number_FormatIntMax(intmax value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal String *Number_FormatUIntMax(uintmax value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal String *Number_FormatSingle(float value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal String *Number_FormatDouble(double value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void Number_FormatIntMaxBuffered(StringBuilder *sb, intmax value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void Number_FormatUIntMaxBuffered(StringBuilder *sb, uintmax value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void Number_FormatSingleBuffered(StringBuilder *sb, float value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void Number_FormatDoubleBuffered(StringBuilder *sb, double value, const String *format);

/// <summary>
/// Determines whether the given number format will cause the number to be formatted in a numeral system other than
/// the decimal system, for example hexadecimal or binary.
/// </summary>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="value"/> is a non-decimal format; otherwise, <see cref="false"/>.
/// </returns>
internal bool Number_IsNonDecimalFormat(const String *format);

#endif
