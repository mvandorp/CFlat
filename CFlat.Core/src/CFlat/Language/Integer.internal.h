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

#ifndef CFLAT_CORE_LANGUAGE_INTEGER_INTERNAL_H
#define CFLAT_CORE_LANGUAGE_INTEGER_INTERNAL_H

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"

/* Types */
typedef struct String String;
typedef struct StringBuilder StringBuilder;

/* Functions */
#ifdef CFLAT_INTPTR
/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void intptr_ToStringBuffered(StringBuilder *sb, intptr value, const String *format);
#endif

#ifdef CFLAT_UINTPTR
/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void uintptr_ToStringBuffered(StringBuilder *sb, uintptr value, const String *format);
#endif

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void uintsize_ToStringBuffered(StringBuilder *sb, uintsize value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void sbyte_ToStringBuffered(StringBuilder *sb, sbyte value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void byte_ToStringBuffered(StringBuilder *sb, byte value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void short_ToStringBuffered(StringBuilder *sb, short value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void ushort_ToStringBuffered(StringBuilder *sb, ushort value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void int_ToStringBuffered(StringBuilder *sb, int value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void uint_ToStringBuffered(StringBuilder *sb, uint value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void long_ToStringBuffered(StringBuilder *sb, long value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void ulong_ToStringBuffered(StringBuilder *sb, ulong value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void intmax_ToStringBuffered(StringBuilder *sb, intmax value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void uintmax_ToStringBuffered(StringBuilder *sb, uintmax value, const String *format);

#endif
