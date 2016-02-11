/// @file Integer.h
/// @author Martijn van Dorp
/// @date July 2015

#ifndef CFLAT_CORE_LANGUAGE_INTEGER_H
#define CFLAT_CORE_LANGUAGE_INTEGER_H

#include <stddef.h>
#include <limits.h>

/* Special integer types */
/// @name Special integer types
/// @{
#define CFLAT_UINTSIZE_MIN 0
#define CFLAT_UINTSIZE_MAX SIZE_MAX

/// <summary>
/// Represents an unsigned integer with a width of at least 16 bits
/// that is large enough to store the size of any array or object.
/// </summary>
typedef size_t uintsize;

/// <summary>
/// Represents the smallest possible value of <see cref="uintsize"/>.
/// </summary>
extern const uintsize UIntSize_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="uintsize"/>.
/// </summary>
extern const uintsize UIntSize_MaxValue;

/* Standard integer types */
/// @}
/// @name Standard integer types
/// @{
#define CFLAT_CHAR_MIN      CHAR_MIN
#define CFLAT_CHAR_MAX      CHAR_MIN
#define CFLAT_SBYTE_MIN     SCHAR_MIN
#define CFLAT_SBYTE_MAX     SCHAR_MAX
#define CFLAT_BYTRE_MAX     UCHAR_MAX
#define CFLAT_SHORT_MIN     SHRT_MIN
#define CFLAT_SHORT_MAX     SHRT_MAX
#define CFLAT_USHORT_MAX    USHRT_MAX
#define CFLAT_INT_MIN       INT_MIN
#define CFLAT_INT_MAX       INT_MAX
#define CFLAT_UINT_MAX      UINT_MAX
#define CFLAT_LONG_MIN      LONG_MIN
#define CFLAT_LONG_MAX      LONG_MAX
#define CFLAT_ULONG_MAX     ULONG_MAX

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
/// Represents the smallest possible value of <see cref="char"/>.
/// </summary>
extern const sbyte Char_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="char"/>.
/// </summary>
extern const sbyte Char_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="sbyte"/>.
/// </summary>
extern const sbyte SByte_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="sbyte"/>.
/// </summary>
extern const sbyte SByte_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="byte"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const byte Byte_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="byte"/>.
/// </summary>
extern const byte Byte_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="short"/>.
/// </summary>
extern const short Short_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="short"/>.
/// </summary>
extern const short Short_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="ushort"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const ushort UShort_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="ushort"/>.
/// </summary>
extern const ushort UShort_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="int"/>.
/// </summary>
extern const int Int_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="int"/>.
/// </summary>
extern const int Int_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="uint"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const uint UInt_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="uint"/>.
/// </summary>
extern const uint UInt_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="long"/>.
/// </summary>
extern const long Long_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="long"/>.
/// </summary>
extern const long Long_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="ulong"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const ulong ULong_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="ulong"/>.
/// </summary>
extern const ulong ULong_MaxValue;

/* Exact-width integer types */
/// @}
/// @{
/// @name Exact-width integer types
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (_MSC_VER >= 1700)
    #include <stdint.h.>

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
    #define CFLAT_INT8_MIN 0x80
    #define CFLAT_INT8_MAX 0x7F
    #define CFLAT_UINT8_MAX 0xFF

    /// <summary>
    /// Represents the smallest possible value of <see cref="int8"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is -128 (hexadecimal 0x80).</remarks>
    extern const int8 Int8_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="int8"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 127 (hexadecimal 0x7F).</remarks>
    extern const int8 Int8_MaxValue;

    /// <summary>
    /// Represents the smallest possible value of <see cref="uint8"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 0.</remarks>
    extern const uint8 UInt8_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="uint8"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 255 (hexadecimal 0xFF).</remarks>
    extern const uint8 UInt8_MaxValue;
#endif

#ifdef CFLAT_INT16
    #define CFLAT_INT16_MIN 0x8000
    #define CFLAT_INT16_MAX 0x7FFF
    #define CFLAT_UINT16_MAX 0xFFFF

    /// <summary>
    /// Represents the smallest possible value of <see cref="int16"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is -32768 (hexadecimal 0x8000).</remarks>
    extern const int16 Int16_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="int16"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 32767 (hexadecimal 0x7FFF).</remarks>
    extern const int16 Int16_MaxValue;

    /// <summary>
    /// Represents the smallest possible value of <see cref="uint16"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 0.</remarks>
    extern const uint16 UInt16_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="uint16"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 65535 (hexadecimal 0xFFFF).</remarks>
    extern const uint16 UInt16_MaxValue;
#endif

#ifdef CFLAT_INT32
    #define CFLAT_INT32_MIN 0x80000000
    #define CFLAT_INT32_MAX 0x7FFFFFFF
    #define CFLAT_UINT32_MAX 0xFFFFFFFF

    /// <summary>
    /// Represents the smallest possible value of <see cref="int32"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is -2147483648 (hexadecimal 0x80000000).</remarks>
    extern const int32 Int32_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="int32"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 2147483647 (hexadecimal 0x7FFFFFFF).</remarks>
    extern const int32 Int32_MaxValue;

    /// <summary>
    /// Represents the smallest possible value of <see cref="uint32"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 0.</remarks>
    extern const uint32 UInt32_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="uint32"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 4294967295 (hexadecimal 0xFFFFFFFF).</remarks>
    extern const uint32 UInt32_MaxValue;
#endif

#ifdef CFLAT_INT64
    #define CFLAT_INT64_MIN 0x8000000000000000
    #define CFLAT_INT64_MAX 0x7FFFFFFFFFFFFFFF
    #define CFLAT_UINT64_MAX 0xFFFFFFFFFFFFFFFF

    /// <summary>
    /// Represents the smallest possible value of <see cref="int64"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is -9223372036854775808 (hexadecimal 0x8000000000000000).</remarks>
    extern const int64 Int64_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="int64"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 9223372036854775807 (hexadecimal 0x7FFFFFFFFFFFFFFF).</remarks>
    extern const int64 Int64_MaxValue;

    /// <summary>
    /// Represents the smallest possible value of <see cref="uint64"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 0.</remarks>
    extern const uint64 UInt64_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="uint64"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 18446744073709551613 (hexadecimal 0xFFFFFFFFFFFFFFFF).</remarks>
    extern const uint64 UInt64_MaxValue;
#endif

/* Least-width integer types */
/// @}
/// @{
/// @name Least-width integer types
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1700)
    #include <stdint.h.>

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
    #else
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
    #else
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
extern const int8_least Int8Least_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="int8_least"/>.
/// </summary>
extern const int8_least Int8Least_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="uint8_least"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const uint8_least UInt8Least_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="uint8_least"/>.
/// </summary>
extern const uint8_least UInt8Least_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="int16_least"/>.
/// </summary>
extern const int16_least Int16Least_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="int16_least"/>.
/// </summary>
extern const int16_least Int16Least_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="uint16_least"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const uint16_least UInt16Least_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="uint16_least"/>.
/// </summary>
extern const uint16_least UInt16Least_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="int32_least"/>.
/// </summary>
extern const int32_least Int32Least_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="int32_least"/>.
/// </summary>
extern const int32_least Int32Least_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="uint32_least"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const uint32_least UInt32Least_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="uint32_least"/>.
/// </summary>
extern const uint32_least UInt32Least_MaxValue;

#ifdef CFLAT_INT64_LEAST
    /// <summary>
    /// Represents the smallest possible value of <see cref="int64_least"/>.
    /// </summary>
    extern const int64_least Int64Least_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="int64_least"/>.
    /// </summary>
    extern const int64_least Int64Least_MaxValue;
#endif

#ifdef CFLAT_UINT64_LEAST
    /// <summary>
    /// Represents the smallest possible value of <see cref="uint64_least"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 0.</remarks>
    extern const uint64_least UInt64Least_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="uint64_least"/>.
    /// </summary>
    extern const uint64_least UInt64Least_MaxValue;
#endif

/* Fast integer types */
/// @}
/// @{
/// @name Fast integer types
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1700)
    #include <stdint.h.>

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
extern const int8_fast Int8Fast_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="int8_fast"/>.
/// </summary>
extern const int8_fast Int8Fast_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="uint8_fast"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const uint8_fast UInt8Fast_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="uint8_fast"/>.
/// </summary>
extern const uint8_fast UInt8Fast_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="int16_fast"/>.
/// </summary>
extern const int16_fast Int16Fast_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="int16_fast"/>.
/// </summary>
extern const int16_fast Int16Fast_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="uint16_fast"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const uint16_fast UInt16Fast_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="uint16_fast"/>.
/// </summary>
extern const uint16_fast UInt16Fast_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="int32_fast"/>.
/// </summary>
extern const int32_fast Int32Fast_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="int32_fast"/>.
/// </summary>
extern const int32_fast Int32Fast_MaxValue;

/// <summary>
/// Represents the smallest possible value of <see cref="uint32_fast"/>.
/// </summary>
/// <remarks>The value of this extern constant is 0.</remarks>
extern const uint32_fast UInt32Fast_MinValue;

/// <summary>
/// Represents the largest possible value of <see cref="uint32_fast"/>.
/// </summary>
extern const uint32_fast UInt32Fast_MaxValue;

#ifdef CFLAT_INT64_FAST
    /// <summary>
    /// Represents the smallest possible value of <see cref="int64_fast"/>.
    /// </summary>
    extern const int64_fast Int64Fast_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="int64_fast"/>.
    /// </summary>
    extern const int64_fast Int64Fast_MaxValue;
#endif

#ifdef CFLAT_UINT64_FAST
    /// <summary>
    /// Represents the smallest possible value of <see cref="uint64_fast"/>.
    /// </summary>
    /// <remarks>The value of this extern constant is 0.</remarks>
    extern const uint64_fast UInt64Fast_MinValue;

    /// <summary>
    /// Represents the largest possible value of <see cref="uint64_fast"/>.
    /// </summary>
    extern const uint64_fast UInt64Fast_MaxValue;
#endif

/// @}

#endif
