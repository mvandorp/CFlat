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

//! @file Integer.h

#ifndef CFLAT_CORE_LANGUAGE_INTEGER_H
#define CFLAT_CORE_LANGUAGE_INTEGER_H

#include <stddef.h>
#include <limits.h>

/* Forward declarations */
typedef struct String String;

/* Special integer types */
//! @name Special integer types
//! @{

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (_MSC_VER >= 1700)
    #include <stdint.h>

    #ifdef INTPTR_MAX
        #define CFLAT_INTPTR        intptr_t
        #define CFLAT_INTPTR_MIN    INTPTR_MIN
        #define CFLAT_INTPTR_MAX    INTPTR_MAX
    #endif

    #ifdef INTPTR_MAX
        #define CFLAT_UINTPTR       uintptr_t
        #define CFLAT_UINTPTR_MAX   UINTPTR_MAX
    #endif
#endif

#ifdef CFLAT_INTPTR
    /// <summary>
    /// Represents a signed integer capable of holding a void pointer.
    /// </summary>
    typedef CFLAT_INTPTR intptr;

    /// <summary>
    /// Represents the smallest possible value of <see cref="intptr"/>.
    /// </summary>
    #define intptr_MinValue CFLAT_INTPTR_MIN

    /// <summary>
    /// Represents the largest possible value of <see cref="intptr"/>.
    /// </summary>
    #define intptr_MaxValue CFLAT_INTPTR_MAX
#endif

#ifdef CFLAT_UINTPTR
    /// <summary>
    /// Represents an unsigned integer capable of holding a void pointer.
    /// </summary>
    typedef CFLAT_UINTPTR uintptr;

    /// <summary>
    /// Represents the smallest possible value of <see cref="uintptr"/>.
    /// </summary>
    /// <remarks>The value of this constant is 0.</remarks>
    #define uintptr_MinValue 0

    /// <summary>
    /// Represents the largest possible value of <see cref="uintptr"/>.
    /// </summary>
    #define uintptr_MaxValue CFLAT_UINTPTR_MAX
#endif

/// <summary>
/// Represents an unsigned integer with a width of at least 16 bits
/// that is large enough to store the size of any array or object.
/// </summary>
typedef size_t uintsize;

/// <summary>
/// Represents the smallest possible value of <see cref="uintsize"/>.
/// </summary>
#define uintsize_MinValue ((uintsize)0)

/// <summary>
/// Represents the largest possible value of <see cref="uintsize"/>.
/// </summary>
#define uintsize_MaxValue ((uintsize)-1)

/* Standard integer types */
//! @}
//! @name Standard integer types
//! @{

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
#define sbyte_MinValue ((sbyte)SCHAR_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="sbyte"/>.
/// </summary>
#define sbyte_MaxValue ((sbyte)SCHAR_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="byte"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define byte_MinValue ((byte)0)

/// <summary>
/// Represents the largest possible value of <see cref="byte"/>.
/// </summary>
#define byte_MaxValue ((byte)UCHAR_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="short"/>.
/// </summary>
#define short_MinValue ((short)SHRT_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="short"/>.
/// </summary>
#define short_MaxValue ((short)SHRT_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="ushort"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define ushort_MinValue ((ushort)0)

/// <summary>
/// Represents the largest possible value of <see cref="ushort"/>.
/// </summary>
#define ushort_MaxValue ((ushort)USHRT_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="int"/>.
/// </summary>
#define int_MinValue ((int)INT_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="int"/>.
/// </summary>
#define int_MaxValue ((int)INT_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="uint"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define uint_MinValue ((uint)0)

/// <summary>
/// Represents the largest possible value of <see cref="uint"/>.
/// </summary>
#define uint_MaxValue ((uint)UINT_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="long"/>.
/// </summary>
#define long_MinValue ((long)LONG_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="long"/>.
/// </summary>
#define long_MaxValue ((long)LONG_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="ulong"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define ulong_MinValue ((ulong)0)

/// <summary>
/// Represents the largest possible value of <see cref="ulong"/>.
/// </summary>
#define ulong_MaxValue ((ulong)ULONG_MAX)

/* Max-width integer types */
//! @}
//! @name Max-width integer types
//! @{

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (_MSC_VER >= 1700)
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
#define intmax_MinValue CFLAT_INTMAX_MIN

/// <summary>
/// Represents the largest possible value of <see cref="intmax"/>.
/// </summary>
#define intmax_MaxValue CFLAT_INTMAX_MAX

/// <summary>
/// Represents the smallest possible value of <see cref="uintmax"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define uintmax_MinValue 0

/// <summary>
/// Represents the largest possible value of <see cref="uintmax"/>.
/// </summary>
#define uintmax_MaxValue CFLAT_UINTMAX_MAX

/* Exact-width integer types */
//! @}
//! @name Exact-width integer types
//! @{

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (_MSC_VER >= 1700)
    #include <stdint.h>

    #ifdef INT8_MAX
        #define CFLAT_INT8      int8_t
        #define CFLAT_UINT8     uint8_t
    #endif

    #ifdef INT16_MAX
        #define CFLAT_INT16     int16_t
        #define CFLAT_UINT16    uint16_t
    #endif

    #ifdef INT32_MAX
        #define CFLAT_INT32     int32_t
        #define CFLAT_UINT32    uint32_t
    #endif

    #ifdef INT64_MAX
        #define CFLAT_INT64     int64_t
        #define CFLAT_UINT64    uint64_t
    #endif
#else
    #if SCHAR_MAX == 0x7F && UCHAR_MAX == 0xFF
        #define CFLAT_INT8      signed char
        #define CFLAT_UINT8     unsigned char
    #elif SCHAR_MAX == 0x7FFF && UCHAR_MAX == 0xFFFF
        #define CFLAT_INT16     signed char
        #define CFLAT_UINT16    unsigned char
    #elif SCHAR_MAX == 0x7FFFFFFF && UCHAR_MAX == 0xFFFFFFFF
        #define CFLAT_INT32     signed char
        #define CFLAT_UINT32    unsigned char
    #elif SCHAR_MAX == 0x7FFFFFFFFFFFFFFF && UCHAR_MAX == 0xFFFFFFFFFFFFFFFF
        #define CFLAT_INT64     signed char
        #define CFLAT_UINT64    unsigned char
    #endif

    #if !defined(CFLAT_INT16) && SHRT_MAX == 0x7FFF && USHRT_MAX == 0xFFFF
        #define CFLAT_INT16     short
        #define CFLAT_UINT16    unsigned short
    #elif !defined(CFLAT_INT32) && SHRT_MAX == 0x7FFFFFFF && USHRT_MAX == 0xFFFFFFFF
        #define CFLAT_INT32     short
        #define CFLAT_UINT32    unsigned short
    #elif !defined(CFLAT_INT64) && SHRT_MAX == 0x7FFFFFFFFFFFFFFF && USHRT_MAX == 0xFFFFFFFFFFFFFFFF
        #define CFLAT_INT64     short
        #define CFLAT_UINT64    unsigned short
    #endif

    #if !defined(CFLAT_INT16) && INT_MAX == 0x7FFF && UINT_MAX == 0xFFFF
        #define CFLAT_INT16     int
        #define CFLAT_UINT16    unsigned int
    #elif !defined(CFLAT_INT32) && INT_MAX == 0x7FFFFFFF && UINT_MAX == 0xFFFFFFFF
        #define CFLAT_INT32     int
        #define CFLAT_UINT32    unsigned int
    #elif !defined(CFLAT_INT64) && INT_MAX == 0x7FFFFFFFFFFFFFFF && UINT_MAX == 0xFFFFFFFFFFFFFFFF
        #define CFLAT_INT64     int
        #define CFLAT_UINT64    unsigned int
    #endif

    #if !defined(CFLAT_INT32) && LONG_MAX == 0x7FFFFFFF && ULONG_MAX == 0xFFFFFFFF
        #define CFLAT_INT32     long
        #define CFLAT_UINT32    unsigned long
    #elif !defined(CFLAT_INT64) && LONG_MAX == 0x7FFFFFFFFFFFFFFF && ULONG_MAX == 0xFFFFFFFFFFFFFFFF
        #define CFLAT_INT64     long
        #define CFLAT_UINT64    unsigned long
    #elif !defined(CFLAT_INT64) && defined(_MSC_VER) && defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64
        #define CFLAT_INT64     __int64
        #define CFLAT_UINT64    unsigned __int64
    #endif
#endif

#ifdef CFLAT_INT8
    /// <summary>
    /// Represents a signed integer with a width of exactly 8 bits.
    /// </summary>
    typedef CFLAT_INT8 int8;

    /// <summary>
    /// Represents an unsigned integer with a width of exactly 8 bits.
    /// </summary>
    typedef CFLAT_UINT8 uint8;
#endif

#ifdef CFLAT_INT16
    /// <summary>
    /// Represents a signed integer with a width of exactly 16 bits.
    /// </summary>
    typedef CFLAT_INT16 int16;

    /// <summary>
    /// Represents an unsigned integer with a width of exactly 16 bits.
    /// </summary>
    typedef CFLAT_UINT16 uint16;
#endif

#ifdef CFLAT_INT32
    /// <summary>
    /// Represents a signed integer with a width of exactly 32 bits.
    /// </summary>
    typedef CFLAT_INT32 int32;

    /// <summary>
    /// Represents an unsigned integer with a width of exactly 32 bits.
    /// </summary>
    typedef CFLAT_UINT32 uint32;
#endif

#ifdef CFLAT_INT64
    /// <summary>
    /// Represents a signed integer with a width of exactly 64 bits.
    /// </summary>
    typedef CFLAT_INT64 int64;

    /// <summary>
    /// Represents an unsigned integer with a width of exactly 64 bits.
    /// </summary>
    typedef CFLAT_UINT64 uint64;
#endif

#ifdef CFLAT_INT8
    /// <summary>
    /// Represents the smallest possible value of <see cref="int8"/>.
    /// </summary>
    /// <remarks>The value of this constant is -128 (hexadecimal 0x80).</remarks>
    #define int8_MinValue ((int8)0x80)

    /// <summary>
    /// Represents the largest possible value of <see cref="int8"/>.
    /// </summary>
    /// <remarks>The value of this constant is 127 (hexadecimal 0x7F).</remarks>
    #define int8_MaxValue ((int8)0x7F)

    /// <summary>
    /// Represents the smallest possible value of <see cref="uint8"/>.
    /// </summary>
    /// <remarks>The value of this constant is 0.</remarks>
    #define uint8_MinValue ((int8)0)

    /// <summary>
    /// Represents the largest possible value of <see cref="uint8"/>.
    /// </summary>
    /// <remarks>The value of this constant is 255 (hexadecimal 0xFF).</remarks>
    #define uint8_MaxValue ((int8)0xFF)
#endif

#ifdef CFLAT_INT16
    /// <summary>
    /// Represents the smallest possible value of <see cref="int16"/>.
    /// </summary>
    /// <remarks>The value of this constant is -32768 (hexadecimal 0x8000).</remarks>
    #define int16_MinValue ((int16)0x8000)

    /// <summary>
    /// Represents the largest possible value of <see cref="int16"/>.
    /// </summary>
    /// <remarks>The value of this constant is 32767 (hexadecimal 0x7FFF).</remarks>
    #define int16_MaxValue ((int16)0x7FFF)

    /// <summary>
    /// Represents the smallest possible value of <see cref="uint16"/>.
    /// </summary>
    /// <remarks>The value of this constant is 0.</remarks>
    #define uint16_MinValue ((uint16)0)

    /// <summary>
    /// Represents the largest possible value of <see cref="uint16"/>.
    /// </summary>
    /// <remarks>The value of this constant is 65535 (hexadecimal 0xFFFF).</remarks>
    #define uint16_MaxValue ((uint16)0xFFFF)
#endif

#ifdef CFLAT_INT32
    /// <summary>
    /// Represents the smallest possible value of <see cref="int32"/>.
    /// </summary>
    /// <remarks>The value of this constant is -2147483648 (hexadecimal 0x80000000).</remarks>
    #define int32_MinValue ((int32)0x80000000)

    /// <summary>
    /// Represents the largest possible value of <see cref="int32"/>.
    /// </summary>
    /// <remarks>The value of this constant is 2147483647 (hexadecimal 0x7FFFFFFF).</remarks>
    #define int32_MaxValue ((int32)0x7FFFFFFF)

    /// <summary>
    /// Represents the smallest possible value of <see cref="uint32"/>.
    /// </summary>
    /// <remarks>The value of this constant is 0.</remarks>
    #define uint32_MinValue ((uint32)0)

    /// <summary>
    /// Represents the largest possible value of <see cref="uint32"/>.
    /// </summary>
    /// <remarks>The value of this constant is 4294967295 (hexadecimal 0xFFFFFFFF).</remarks>
    #define uint32_MaxValue ((uint32)0xFFFFFFFF)
#endif

#ifdef CFLAT_INT64
    /// <summary>
    /// Represents the smallest possible value of <see cref="int64"/>.
    /// </summary>
    /// <remarks>The value of this constant is -9223372036854775808 (hexadecimal 0x8000000000000000).</remarks>
    #define int64_MinValue ((int64)0x8000000000000000)

    /// <summary>
    /// Represents the largest possible value of <see cref="int64"/>.
    /// </summary>
    /// <remarks>The value of this constant is 9223372036854775807 (hexadecimal 0x7FFFFFFFFFFFFFFF).</remarks>
    #define int64_MaxValue ((int64)0x7FFFFFFFFFFFFFFF)

    /// <summary>
    /// Represents the smallest possible value of <see cref="uint64"/>.
    /// </summary>
    /// <remarks>The value of this constant is 0.</remarks>
    #define uint64_MinValue ((uint64)0)

    /// <summary>
    /// Represents the largest possible value of <see cref="uint64"/>.
    /// </summary>
    /// <remarks>The value of this constant is 18446744073709551613 (hexadecimal 0xFFFFFFFFFFFFFFFF).</remarks>
    #define uint64_MaxValue ((uint64)0xFFFFFFFFFFFFFFFF)
#endif

/* Least-width integer types */
//! @}
//! @name Least-width integer types
//! @{

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1700)
    #include <stdint.h>

    #define CFLAT_INT8_LEAST        int_least8_t
    #define CFLAT_UINT8_LEAST       uint_least8_t
    #define CFLAT_INT16_LEAST       int_least16_t
    #define CFLAT_UINT16_LEAST      uint_least16_t
    #define CFLAT_INT32_LEAST       int_least32_t
    #define CFLAT_UINT32_LEAST      uint_least32_t
    #define CFLAT_INT64_LEAST       int_least64_t
    #define CFLAT_UINT64_LEAST      uint_least64_t

    #define CFLAT_INT8_LEAST_MIN    INT_LEAST8_MIN
    #define CFLAT_INT8_LEAST_MAX    INT_LEAST8_MAX
    #define CFLAT_UINT8_LEAST_MAX   UINT_LEAST8_MAX
    #define CFLAT_INT16_LEAST_MIN   INT_LEAST16_MIN
    #define CFLAT_INT16_LEAST_MAX   INT_LEAST16_MAX
    #define CFLAT_UINT16_LEAST_MAX  UINT_LEAST16_MAX
    #define CFLAT_INT32_LEAST_MIN   INT_LEAST32_MIN
    #define CFLAT_INT32_LEAST_MAX   INT_LEAST32_MAX
    #define CFLAT_UINT32_LEAST_MAX  UINT_LEAST32_MAX
    #define CFLAT_INT64_LEAST_MIN   INT_LEAST64_MIN
    #define CFLAT_INT64_LEAST_MAX   INT_LEAST64_MAX
    #define CFLAT_UINT64_LEAST_MAX  UINT_LEAST64_MAX
#else
    #ifdef CFLAT_INT8
        #define CFLAT_INT8_LEAST        CFLAT_INT8
        #define CFLAT_INT8_LEAST_MIN    0x80
        #define CFLAT_INT8_LEAST_MAX    0x7F
    #else
        #define CFLAT_INT8_LEAST        signed char
        #define CFLAT_INT8_LEAST_MIN    SCHAR_MIN
        #define CFLAT_INT8_LEAST_MAX    SCHAR_MAX
    #endif

    #ifdef CFLAT_UINT8
        #define CFLAT_UINT8_LEAST       CFLAT_UINT8
        #define CFLAT_UINT8_LEAST_MAX   0xFF
    #else
        #define CFLAT_UINT8_LEAST       unsigned char
        #define CFLAT_UINT8_LEAST_MAX   UCHAR_MAX
    #endif

    #ifdef CFLAT_INT16
        #define CFLAT_INT16_LEAST       CFLAT_INT16
        #define CFLAT_INT16_LEAST_MIN   0x8000
        #define CFLAT_INT16_LEAST_MAX   0x7FFF
    #elif SCHAR_MAX >= 0x7FFF
        #define CFLAT_INT16_LEAST       signed char
        #define CFLAT_INT16_LEAST_MIN   SCHAR_MIN
        #define CFLAT_INT16_LEAST_MAX   SCHAR_MAX
    #else
        #define CFLAT_INT16_LEAST       short
        #define CFLAT_INT16_LEAST_MIN   SHRT_MIN
        #define CFLAT_INT16_LEAST_MAX   SHRT_MAX
    #endif

    #ifdef CFLAT_UINT16
        #define CFLAT_UINT16_LEAST      CFLAT_UINT16
        #define CFLAT_UINT16_LEAST_MAX  0xFFFF
    #elif UCHAR_MAX >= 0xFFFF
        #define CFLAT_UINT16_LEAST      unsigned char
        #define CFLAT_UINT16_LEAST_MAX  UCHAR_MAX
    #else
        #define CFLAT_UINT16_LEAST      unsigned short
        #define CFLAT_UINT16_LEAST_MAX  USHRT_MAX
    #endif

    #ifdef CFLAT_INT32
        #define CFLAT_INT32_LEAST       CFLAT_INT32
        #define CFLAT_INT32_LEAST_MIN   0x80000000
        #define CFLAT_INT32_LEAST_MAX   0x7FFFFFFF
    #elif SCHAR_MAX >= 0x7FFFFFFF
        #define CFLAT_INT32_LEAST       signed char
        #define CFLAT_INT32_LEAST_MIN   SCHAR_MIN
        #define CFLAT_INT32_LEAST_MAX   SCHAR_MAX
    #elif SHRT_MAX >= 0x7FFFFFFF
        #define CFLAT_INT32_LEAST       short
        #define CFLAT_INT32_LEAST_MIN   SHRT_MIN
        #define CFLAT_INT32_LEAST_MAX   SHRT_MAX
    #elif INT_MAX >= 0x7FFFFFFF
        #define CFLAT_INT32_LEAST       int
        #define CFLAT_INT32_LEAST_MIN   INT_MIN
        #define CFLAT_INT32_LEAST_MAX   INT_MAX
    #else
        #define CFLAT_INT32_LEAST       long
        #define CFLAT_INT32_LEAST_MIN   LONG_MIN
        #define CFLAT_INT32_LEAST_MAX   LONG_MAX
    #endif

    #ifdef CFLAT_UINT32
        #define CFLAT_UINT32_LEAST      CFLAT_UINT32
        #define CFLAT_UINT32_LEAST_MAX  0xFFFFFFFF
    #elif UCHAR_MAX >= 0xFFFFFFFF
        #define CFLAT_UINT32_LEAST      unsigned char
        #define CFLAT_UINT32_LEAST_MAX  UCHAR_MAX
    #elif USHRT_MAX >= 0xFFFFFFFF
        #define CFLAT_UINT32_LEAST      unsigned short
        #define CFLAT_UINT32_LEAST_MAX  USHRT_MAX
    #elif UINT_MAX >= 0xFFFFFFFF
        #define CFLAT_UINT32_LEAST      unsigned int
        #define CFLAT_UINT32_LEAST_MAX  UINT_MAX
    #else
        #define CFLAT_UINT32_LEAST      unsigned long
        #define CFLAT_UINT32_LEAST_MAX  ULONG_MAX
    #endif

    #ifdef CFLAT_INT64
        #define CFLAT_INT64_LEAST       CFLAT_INT64
        #define CFLAT_INT64_LEAST_MIN   0x8000000000000000
        #define CFLAT_INT64_LEAST_MAX   0x7FFFFFFFFFFFFFFF
    #elif SCHAR_MAX >= 0x7FFFFFFFFFFFFFFF
        #define CFLAT_INT64_LEAST       signed char
        #define CFLAT_INT64_LEAST_MIN   SCHAR_MIN
        #define CFLAT_INT64_LEAST_MAX   SCHAR_MAX
    #elif SHRT_MAX >= 0x7FFFFFFFFFFFFFFF
        #define CFLAT_INT64_LEAST       short
        #define CFLAT_INT64_LEAST_MIN   SHRT_MIN
        #define CFLAT_INT64_LEAST_MAX   SHRT_MAX
    #elif INT_MAX >= 0x7FFFFFFFFFFFFFFF
        #define CFLAT_INT64_LEAST       int
        #define CFLAT_INT64_LEAST_MIN   INT_MIN
        #define CFLAT_INT64_LEAST_MAX   INT_MAX
    #else LONG_MAX >= 0x7FFFFFFFFFFFFFFF
        #define CFLAT_INT64_LEAST       long
        #define CFLAT_INT64_LEAST_MIN   LONG_MIN
        #define CFLAT_INT64_LEAST_MAX   LONG_MAX
    #endif

    #ifdef CFLAT_UINT64
        #define CFLAT_UINT64_LEAST      CFLAT_UINT64
        #define CFLAT_UINT64_LEAST_MAX  0xFFFFFFFFFFFFFFFF
    #elif UCHAR_MAX >= 0xFFFFFFFFFFFFFFFF
        #define CFLAT_UINT64_LEAST      unsigned char
        #define CFLAT_UINT64_LEAST_MAX  UCHAR_MAX
    #elif USHRT_MAX >= 0xFFFFFFFFFFFFFFFF
        #define CFLAT_UINT64_LEAST      unsigned short
        #define CFLAT_UINT64_LEAST_MAX  USHRT_MAX
    #elif UINT_MAX >= 0xFFFFFFFFFFFFFFFF
        #define CFLAT_UINT64_LEAST      unsigned int
        #define CFLAT_UINT64_LEAST_MAX  UINT_MAX
    #else ULONG_MAX >= 0xFFFFFFFFFFFFFFFF
        #define CFLAT_UINT64_LEAST      unsigned long
        #define CFLAT_UINT64_LEAST_MAX  ULONG_MAX
    #endif
#endif

/// <summary>
/// Represents the smallest signed integer with a width of at least 8 bits.
/// </summary>
typedef CFLAT_INT8_LEAST int8_least;

/// <summary>
/// Represents the smallest unsigned integer with a width of at least 8 bits.
/// </summary>
typedef CFLAT_UINT8_LEAST uint8_least;

/// <summary>
/// Represents the smallest signed integer with a width of at least 16 bits.
/// </summary>
typedef CFLAT_INT16_LEAST int16_least;

/// <summary>
/// Represents the smallest unsigned integer with a width of at least 16 bits.
/// </summary>
typedef CFLAT_UINT16_LEAST uint16_least;

/// <summary>
/// Represents the smallest signed integer with a width of at least 32 bits.
/// </summary>
typedef CFLAT_INT32_LEAST int32_least;

/// <summary>
/// Represents the smallest unsigned integer with a width of at least 32 bits.
/// </summary>
typedef CFLAT_UINT32_LEAST uint32_least;

#ifdef CFLAT_INT64_LEAST
    /// <summary>
    /// Represents the smallest signed integer with a width of at least 64 bits.
    /// </summary>
    typedef CFLAT_INT64_LEAST int64_least;
#endif

#ifdef CFLAT_UINT64_LEAST
    /// <summary>
    /// Represents the smallest unsigned integer with a width of at least 64 bits.
    /// </summary>
    typedef CFLAT_UINT64_LEAST uint64_least;
#endif

/// <summary>
/// Represents the smallest possible value of <see cref="int8_least"/>.
/// </summary>
#define int8_least_MinValue ((int8_least)CFLAT_INT8_LEAST_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="int8_least"/>.
/// </summary>
#define int8_least_MaxValue ((int8_least)CFLAT_INT8_LEAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="uint8_least"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define uint8_least_MinValue ((uint8_least)0)

/// <summary>
/// Represents the largest possible value of <see cref="uint8_least"/>.
/// </summary>
#define uint8_least_MaxValue ((uint8_least)CFLAT_UINT8_LEAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="int16_least"/>.
/// </summary>
#define int16_least_MinValue ((int16_least)CFLAT_INT16_LEAST_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="int16_least"/>.
/// </summary>
#define int16_least_MaxValue ((int16_least)CFLAT_INT16_LEAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="uint16_least"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define uint16_least_MinValue ((uint16_least)0)

/// <summary>
/// Represents the largest possible value of <see cref="uint16_least"/>.
/// </summary>
#define uint16_least_MaxValue ((uint16_least)CFLAT_UINT16_LEAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="int32_least"/>.
/// </summary>
#define int32_least_MinValue ((int32_least)CFLAT_INT32_LEAST_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="int32_least"/>.
/// </summary>
#define int32_least_MaxValue ((int32_least)CFLAT_INT32_LEAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="uint32_least"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define uint32_least_MinValue ((uint32_least)0)

/// <summary>
/// Represents the largest possible value of <see cref="uint32_least"/>.
/// </summary>
#define uint32_least_MaxValue ((uint32_least)CFLAT_UINT32_LEAST_MAX)

#ifdef CFLAT_INT64_LEAST
    /// <summary>
    /// Represents the smallest possible value of <see cref="int64_least"/>.
    /// </summary>
    #define int64_least_MinValue ((int64_least)CFLAT_INT64_LEAST_MIN)

    /// <summary>
    /// Represents the largest possible value of <see cref="int64_least"/>.
    /// </summary>
    #define int64_least_MaxValue ((int64_least)CFLAT_INT64_LEAST_MAX)
#endif

#ifdef CFLAT_UINT64_LEAST
    /// <summary>
    /// Represents the smallest possible value of <see cref="uint64_least"/>.
    /// </summary>
    /// <remarks>The value of this constant is 0.</remarks>
    #define uint64_least_MinValue ((uint64_least)0)

    /// <summary>
    /// Represents the largest possible value of <see cref="uint64_least"/>.
    /// </summary>
    #define uint64_least_MaxValue ((uint64_least)CFLAT_UINT64_LEAST_MAX)
#endif

/* Fast integer types */
//! @}
//! @name Fast integer types
//! @{

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1700)
    #include <stdint.h>

    #define CFLAT_INT8_FAST        int_fast8_t
    #define CFLAT_UINT8_FAST       uint_fast8_t
    #define CFLAT_INT16_FAST       int_fast16_t
    #define CFLAT_UINT16_FAST      uint_fast16_t
    #define CFLAT_INT32_FAST       int_fast32_t
    #define CFLAT_UINT32_FAST      uint_fast32_t
    #define CFLAT_INT64_FAST       int_fast64_t
    #define CFLAT_UINT64_FAST      uint_fast64_t

    #define CFLAT_INT8_FAST_MIN    INT_FAST8_MIN
    #define CFLAT_INT8_FAST_MAX    INT_FAST8_MAX
    #define CFLAT_UINT8_FAST_MAX   UINT_FAST8_MAX
    #define CFLAT_INT16_FAST_MIN   INT_FAST16_MIN
    #define CFLAT_INT16_FAST_MAX   INT_FAST16_MAX
    #define CFLAT_UINT16_FAST_MAX  UINT_FAST16_MAX
    #define CFLAT_INT32_FAST_MIN   INT_FAST32_MIN
    #define CFLAT_INT32_FAST_MAX   INT_FAST32_MAX
    #define CFLAT_UINT32_FAST_MAX  UINT_FAST32_MAX
    #define CFLAT_INT64_FAST_MIN   INT_FAST64_MIN
    #define CFLAT_INT64_FAST_MAX   INT_FAST64_MAX
    #define CFLAT_UINT64_FAST_MAX  UINT_FAST64_MAX
#else
    #define CFLAT_INT8_FAST         signed char
    #define CFLAT_INT8_FAST_MIN     SCHAR_MIN
    #define CFLAT_INT8_FAST_MAX     SCHAR_MAX

    #define CFLAT_UINT8_FAST        unsigned char
    #define CFLAT_UINT8_FAST_MAX    UCHAR_MAX

    #define CFLAT_INT16_FAST        int
    #define CFLAT_INT16_FAST_MIN    INT_MIN
    #define CFLAT_INT16_FAST_MAX    INT_MAX

    #define CFLAT_UINT16_FAST       unsigned int
    #define CFLAT_UINT16_FAST_MAX   UINT_MAX

    #if INT_MAX >= 0x7FFFFFFF
        #define CFLAT_INT32_FAST        int
        #define CFLAT_INT32_FAST_MIN    INT_MIN
        #define CFLAT_INT32_FAST_MAX    INT_MAX
    #else
        #define CFLAT_INT32_FAST        long
        #define CFLAT_INT32_FAST_MIN    LONG_MIN
        #define CFLAT_INT32_FAST_MAX    LONG_MAX
    #endif

    #if UINT_MAX >= 0xFFFFFFFF
        #define CFLAT_UINT32_FAST       unsigned int
        #define CFLAT_UINT32_FAST_MAX   UINT_MAX
    #else
        #define CFLAT_UINT32_FAST       unsigned long
        #define CFLAT_UINT32_FAST_MAX   ULONG_MAX
    #endif

    #if INT_MAX >= 0x7FFFFFFFFFFFFFFF
        #define CFLAT_INT64_FAST        int
        #define CFLAT_INT64_FAST_MIN    INT_MIN
        #define CFLAT_INT64_FAST_MAX    INT_MAX
    #elif LONG_MAX >= 0x7FFFFFFFFFFFFFFF
        #define CFLAT_INT64_FAST        long
        #define CFLAT_INT64_FAST_MIN    LONG_MIN
        #define CFLAT_INT64_FAST_MAX    LONG_MAX
    #elif defined(_MSC_VER) && defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64
        #define CFLAT_INT64_FAST        __int64
        #define CFLAT_INT64_FAST_MIN    0x8000000000000000
        #define CFLAT_INT64_FAST_MAX    0x7FFFFFFFFFFFFFFF
    #endif

    #if UINT_MAX >= 0xFFFFFFFFFFFFFFFF
        #define CFLAT_UINT64_FAST       unsigned int
        #define CFLAT_UINT64_FAST_MAX   UINT_MAX
    #elif ULONG_MAX >= 0xFFFFFFFFFFFFFFFF
        #define CFLAT_UINT64_FAST       unsigned long
        #define CFLAT_UINT64_FAST_MAX   ULONG_MAX
    #elif defined(_MSC_VER) && defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64
        #define CFLAT_UINT64_FAST       unsigned __int64
        #define CFLAT_UINT64_FAST_MAX   0xFFFFFFFFFFFFFFFF
    #endif
#endif

/// <summary>
/// Represents the fastest signed integer with a width of at least 8 bits.
/// </summary>
typedef CFLAT_INT8_FAST int8_fast;

/// <summary>
/// Represents the fastest unsigned integer with a width of at least 8 bits.
/// </summary>
typedef CFLAT_UINT8_FAST uint8_fast;

/// <summary>
/// Represents the fastest signed integer with a width of at least 16 bits.
/// </summary>
typedef CFLAT_INT16_FAST int16_fast;

/// <summary>
/// Represents the fastest unsigned integer with a width of at least 16 bits.
/// </summary>
typedef CFLAT_UINT16_FAST uint16_fast;

/// <summary>
/// Represents the fastest signed integer with a width of at least 32 bits.
/// </summary>
typedef CFLAT_INT32_FAST int32_fast;

/// <summary>
/// Represents the fastest unsigned integer with a width of at least 32 bits.
/// </summary>
typedef CFLAT_UINT32_FAST uint32_fast;

#ifdef CFLAT_INT64_FAST
    /// <summary>
    /// Represents the fastest signed integer with a width of at least 64 bits.
    /// </summary>
    typedef CFLAT_INT64_FAST int64_fast;
#endif

#ifdef CFLAT_UINT64_FAST
    /// <summary>
    /// Represents the fastest unsigned integer with a width of at least 64 bits.
    /// </summary>
    typedef CFLAT_UINT64_FAST uint64_fast;
#endif

/// <summary>
/// Represents the smallest possible value of <see cref="int8_fast"/>.
/// </summary>
#define int8_fast_MinValue ((int8_fast)CFLAT_INT8_FAST_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="int8_fast"/>.
/// </summary>
#define int8_fast_MaxValue ((int8_fast)CFLAT_INT8_FAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="uint8_fast"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define uint8_fast_MinValue ((uint8_fast)0)

/// <summary>
/// Represents the largest possible value of <see cref="uint8_fast"/>.
/// </summary>
#define uint8_fast_MaxValue ((uint8_fast)CFLAT_UINT8_FAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="int16_fast"/>.
/// </summary>
#define int16_fast_MinValue ((int16_fast)CFLAT_INT16_FAST_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="int16_fast"/>.
/// </summary>
#define int16_fast_MaxValue ((int16_fast)CFLAT_INT16_FAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="uint16_fast"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define uint16_fast_MinValue ((uint16_fast)0)

/// <summary>
/// Represents the largest possible value of <see cref="uint16_fast"/>.
/// </summary>
#define uint16_fast_MaxValue ((uint16_fast)CFLAT_UINT16_FAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="int32_fast"/>.
/// </summary>
#define int32_fast_MinValue ((int32_fast)CFLAT_INT32_FAST_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="int32_fast"/>.
/// </summary>
#define int32_fast_MaxValue ((int32_fast)CFLAT_INT32_FAST_MAX)

/// <summary>
/// Represents the smallest possible value of <see cref="uint32_fast"/>.
/// </summary>
/// <remarks>The value of this constant is 0.</remarks>
#define uint32_fast_MinValue ((uint32_fast)0)

/// <summary>
/// Represents the largest possible value of <see cref="uint32_fast"/>.
/// </summary>
#define uint32_fast_MaxValue ((uint32_fast)CFLAT_UINT32_FAST_MAX)

#ifdef CFLAT_INT64_FAST
    /// <summary>
    /// Represents the smallest possible value of <see cref="int64_fast"/>.
    /// </summary>
    #define int64_fast_MinValue ((int64_fast)CFLAT_INT64_FAST_MIN)

    /// <summary>
    /// Represents the largest possible value of <see cref="int64_fast"/>.
    /// </summary>
    #define int64_fast_MaxValue ((int64_fast)CFLAT_INT64_FAST_MAX)
#endif

#ifdef CFLAT_UINT64_FAST
    /// <summary>
    /// Represents the smallest possible value of <see cref="uint64_fast"/>.
    /// </summary>
    /// <remarks>The value of this constant is 0.</remarks>
    #define uint64_fast_MinValue ((uint64_fast)0)

    /// <summary>
    /// Represents the largest possible value of <see cref="uint64_fast"/>.
    /// </summary>
    #define uint64_fast_MaxValue ((uint64_fast)CFLAT_UINT64_FAST_MAX)
#endif

//! @}

/* Functions */
/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
uintsize uintsize_Max(uintsize x, uintsize y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
uintsize uintsize_Min(uintsize x, uintsize y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uintsize_ToString(uintsize value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uintsize_ToStringFormat(uintsize value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uintsize_ToStringFormatC(uintsize value, const char *format);

#ifdef CFLAT_INTPTR
/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *intptr_ToString(intptr value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *intptr_ToStringFormat(intptr value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *intptr_ToStringFormatC(intptr value, const char *format);
#endif

#ifdef CFLAT_UINTPTR
/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uintptr_ToString(uintptr value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uintptr_ToStringFormat(uintptr value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uintptr_ToStringFormatC(uintptr value, const char *format);
#endif

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
sbyte sbyte_Max(sbyte x, sbyte y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
sbyte sbyte_Min(sbyte x, sbyte y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *sbyte_ToString(sbyte value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *sbyte_ToStringFormat(sbyte value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *sbyte_ToStringFormatC(sbyte value, const char *format);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
byte byte_Max(byte x, byte y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
byte byte_Min(byte x, byte y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *byte_ToString(byte value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *byte_ToStringFormat(byte value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *byte_ToStringFormatC(byte value, const char *format);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
short short_Max(short x, short y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
short short_Min(short x, short y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *short_ToString(short value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *short_ToStringFormat(short value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *short_ToStringFormatC(short value, const char *format);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
ushort ushort_Max(ushort x, ushort y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
ushort ushort_Min(ushort x, ushort y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *ushort_ToString(ushort value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *ushort_ToStringFormat(ushort value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *ushort_ToStringFormatC(ushort value, const char *format);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
int int_Max(int x, int y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
int int_Min(int x, int y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *int_ToString(int value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *int_ToStringFormat(int value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *int_ToStringFormatC(int value, const char *format);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
uint uint_Max(uint x, uint y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
uint uint_Min(uint x, uint y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uint_ToString(uint value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uint_ToStringFormat(uint value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uint_ToStringFormatC(uint value, const char *format);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
long long_Max(long x, long y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
long long_Min(long x, long y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *long_ToString(long value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *long_ToStringFormat(long value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *long_ToStringFormatC(long value, const char *format);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
ulong ulong_Max(ulong x, ulong y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
ulong ulong_Min(ulong x, ulong y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *ulong_ToString(ulong value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *ulong_ToStringFormat(ulong value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *ulong_ToStringFormatC(ulong value, const char *format);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
intmax intmax_Max(intmax x, intmax y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
intmax intmax_Min(intmax x, intmax y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *intmax_ToString(intmax value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *intmax_ToStringFormat(intmax value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *intmax_ToStringFormatC(intmax value, const char *format);

/// <summary>
/// Returns the larger of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The larger of two numbers.</returns>
uintmax uintmax_Max(uintmax x, uintmax y);

/// <summary>
/// Returns the smaller of two numbers.
/// </summary>
/// <param name="x">The first number.</param>
/// <param name="y">The second number.</param>
/// <returns>The smaller of two numbers.</returns>
uintmax uintmax_Min(uintmax x, uintmax y);

/// <summary>
/// Converts the given number to a string representation.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <returns>The string representation of the given number.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uintmax_ToString(uintmax value);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uintmax_ToStringFormat(uintmax value, const String *format);

/// <summary>
/// Converts the given number to a string representation, using the specified format.
/// </summary>
/// <param name="value">The value to be converted to a string.</param>
/// <param name="format">A standard or custom numeric format string.</param>
/// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
String *uintmax_ToStringFormatC(uintmax value, const char *format);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/Language/Integer.internal.h"
#endif

#endif
