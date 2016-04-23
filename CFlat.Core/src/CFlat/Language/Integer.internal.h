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

#ifndef CFLAT_CORE_LANGUAGE_INTEGER_H
 #error Integer.internal.h should not be included directly.
#endif

#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"

/* Types */
struct String;
struct StringBuilder;

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
internal void intptr_ToStringBuffered(struct StringBuilder *sb, intptr value, const struct String *format);
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
internal void uintptr_ToStringBuffered(struct StringBuilder *sb, uintptr value, const struct String *format);
#endif

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void uintsize_ToStringBuffered(struct StringBuilder *sb, uintsize value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void intfsize_ToStringBuffered(struct StringBuilder *sb, intfsize value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void sbyte_ToStringBuffered(struct StringBuilder *sb, sbyte value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void byte_ToStringBuffered(struct StringBuilder *sb, byte value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void short_ToStringBuffered(struct StringBuilder *sb, short value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void ushort_ToStringBuffered(struct StringBuilder *sb, ushort value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void int_ToStringBuffered(struct StringBuilder *sb, int value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void uint_ToStringBuffered(struct StringBuilder *sb, uint value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void long_ToStringBuffered(struct StringBuilder *sb, long value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void ulong_ToStringBuffered(struct StringBuilder *sb, ulong value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void intmax_ToStringBuffered(struct StringBuilder *sb, intmax value, const struct String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void uintmax_ToStringBuffered(struct StringBuilder *sb, uintmax value, const struct String *format);

#endif
