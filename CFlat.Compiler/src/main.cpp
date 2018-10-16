/*
 * Copyright (C) 2015 Martijn van Dorp
 *
 * This file is part of CFlat.Compiler.
 *
 * CFlat.Compiler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFlat.Compiler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstddef>
#include <climits>

#include <stdint.h>

 /// <summary>
 /// Represents the smallest signed integer with a width of at least 8 bits.
 /// </summary>
typedef signed char sbyte;

/// <summary>
/// Represents the smallest unsigned integer with a width of at least 8 bits.
/// </summary>
typedef unsigned char byte;

/// <summary>
/// Represents the fastest unsigned integer with a width of at least 16 bits.
/// </summary>
typedef unsigned short ushort;

/// <summary>
/// Represents an unsigned integer with a width of at least 16 bits.
/// </summary>
typedef unsigned int uint;

/// <summary>
/// Represents an unsigned integer with a width of at least 32 bits.
/// </summary>
typedef unsigned long ulong;

/// <summary>
/// Represents the smallest possible value of <see cref="sbyte"/>.
/// </summary>
#define SBYTE_MINVALUE static_cast<sbyte>(SCHAR_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="sbyte"/>.
/// </summary>
#define SBYTE_MAXVALUE static_cast<sbyte>(SCHAR_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="byte"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define BYTE_MINVALUE static_cast<byte>(0)

/// <summary>
/// Represents the largest possible value of <see cref="byte"/>.
/// </summary>
#define BYTE_MAXVALUE static_cast<byte>(UCHAR_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="short"/>.
/// </summary>
#define SHORT_MINVALUE static_cast<short>(SHRT_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="short"/>.
/// </summary>
#define SHORT_MAXVALUE static_cast<short>(SHRT_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="ushort"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define USHORT_MINVALUE static_cast<ushort>(0)

/// <summary>
/// Represents the largest possible value of <see cref="ushort"/>.
/// </summary>
#define USHORT_MAXVALUE static_cast<ushort>(USHRT_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="int"/>.
/// </summary>
#define INT_MINVALUE static_cast<int>(INT_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="int"/>.
/// </summary>
#define INT_MAXVALUE static_cast<int>(INT_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="uint"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define UINT_MINVALUE static_cast<uint>(0)

/// <summary>
/// Represents the largest possible value of <see cref="uint"/>.
/// </summary>
#define UINT_MAXVALUE static_cast<uint>(UINT_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="long"/>.
/// </summary>
#define LONG_MINVALUE static_cast<long>(LONG_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="long"/>.
/// </summary>
#define LONG_MAXVALUE static_cast<long>(LONG_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="ulong"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define ULONG_MINVALUE static_cast<ulong>(0)

/// <summary>
/// Represents the largest possible value of <see cref="ulong"/>.
/// </summary>
#define ULONG_MAXVALUE static_cast<ulong>(ULONG_MAX)

/* Max-width integer types */
//! @}
//! @name Max-width integer types
//! @{

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L || defined(_MSC_VER) && _MSC_VER >= 1700
#include <stdint.h>

#define CFLAT_INTMAX        intmax_t
#define CFLAT_UINTMAX       uintmax_t

#define CFLAT_INTMAX_MIN    INTMAX_MIN
#define CFLAT_INTMAX_MAX    INTMAX_MAX
#define CFLAT_UINTMAX_MAX   UINTMAX_MAX
#else
#define CFLAT_INTMAX        long
#define CFLAT_UINTMAX       unsigned long

#define CFLAT_INTMAX_MIN    LONG_MIN
#define CFLAT_INTMAX_MAX    LONG_MAX
#define CFLAT_UINTMAX_MAX   ULONG_MAX
#endif

/// <summary>
/// Represents a signed integer with the largest possible width.
/// </summary>
typedef CFLAT_INTMAX intmax;

/// <summary>
/// Represents an unsigned integer with the largest possible width.
/// </summary>
typedef CFLAT_UINTMAX uintmax;

/// <summary>
/// Represents the smallest possible value of <see cref="intmax"/>.
/// </summary>
#define INTMAX_MINVALUE static_cast<intmax>(CFLAT_INTMAX_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="intmax"/>.
/// </summary>
#define INTMAX_MAXVALUE static_cast<intmax>(CFLAT_INTMAX_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="uintmax"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define UINTMAX_MINVALUE static_cast<uintmax>(0)

/// <summary>
/// Represents the largest possible value of <see cref="uintmax"/>.
/// </summary>
#define UINTMAX_MAXVALUE static_cast<uintmax>(CFLAT_UINTMAX_MAX)

#include <cstdio>

int main(int argc, char *argv[])
{
    fclose(nullptr);

    return 0;
}
