#include "CFlat/Language/Integer.h"

const uintsize UIntSize_MinValue = CFLAT_UINTSIZE_MIN;
const uintsize UIntSize_MaxValue= CFLAT_UINTSIZE_MAX;

/* Standard integer types */
const sbyte Char_MinValue = CHAR_MIN;
const sbyte Char_MaxValue = CHAR_MAX;
const sbyte SByte_MinValue = SCHAR_MIN;
const sbyte SByte_MaxValue = SCHAR_MAX;
const byte Byte_MinValue = 0;
const byte Byte_MaxValue = UCHAR_MAX;
const short Short_MinValue = SHRT_MIN;
const short Short_MaxValue = SHRT_MAX;
const ushort UShort_MinValue = 0;
const ushort UShort_MaxValue = USHRT_MAX;
const int Int_MinValue = INT_MIN;
const int Int_MaxValue = INT_MAX;
const uint UInt_MinValue = 0;
const uint UInt_MaxValue = UINT_MAX;
const long Long_MinValue = LONG_MIN;
const long Long_MaxValue = LONG_MAX;
const ulong ULong_MinValue = 0;
const ulong ULong_MaxValue = ULONG_MAX;

/* Exact-width integer types */
#ifdef CFLAT_INT8
    const int8 Int8_MinValue = CFLAT_INT8_MIN;
    const int8 Int8_MaxValue = CFLAT_INT8_MAX;
    const uint8 UInt8_MinValue = 0;
    const uint8 UInt8_MaxValue = CFLAT_UINT8_MAX;
#endif

#ifdef CFLAT_INT16
    const int16 Int16_MinValue = CFLAT_INT16_MIN;
    const int16 Int16_MaxValue = CFLAT_INT16_MAX;
    const uint16 UInt16_MinValue = 0;
    const uint16 UInt16_MaxValue = CFLAT_INT16_MAX;
#endif

#ifdef CFLAT_INT32
    const int32 Int32_MinValue = CFLAT_INT32_MIN;
    const int32 Int32_MaxValue = CFLAT_INT32_MAX;
    const uint32 UInt32_MinValue = 0;
    const uint32 UInt32_MaxValue = CFLAT_UINT32_MAX;
#endif

#ifdef CFLAT_INT64
    const int64 Int64_MinValue = CFLAT_INT64_MIN;
    const int64 Int64_MaxValue = CFLAT_INT64_MAX;
    const uint64 UInt64_MinValue = 0;
    const uint64 UInt64_MaxValue = CFLAT_UINT64_MAX;
#endif

/* Least-width integer types */
const int8_least Int8Least_MinValue = CFLAT_INT8_LEAST_MIN;
const int8_least Int8Least_MaxValue = CFLAT_INT8_LEAST_MAX;
const uint8_least UInt8Least_MinValue = 0;
const uint8_least UInt8Least_MaxValue = CFLAT_UINT8_LEAST_MAX;
const int16_least Int16Least_MinValue = CFLAT_INT16_LEAST_MIN;
const int16_least Int16Least_MaxValue = CFLAT_INT16_LEAST_MAX;
const uint16_least UInt16Least_MinValue = 0;
const uint16_least UInt16Least_MaxValue = CFLAT_UINT16_LEAST_MAX;
const int32_least Int32Least_MinValue = CFLAT_INT32_LEAST_MIN;
const int32_least Int32Least_MaxValue = CFLAT_INT32_LEAST_MAX;
const uint32_least UInt32Least_MinValue = 0;
const uint32_least UInt32Least_MaxValue = CFLAT_UINT32_LEAST_MAX;

#ifdef CFLAT_INT64_LEAST
    const int64_least Int64Least_MinValue = CFLAT_INT64_LEAST_MIN;
    const int64_least Int64Least_MaxValue = CFLAT_INT64_LEAST_MAX;
#endif

#ifdef CFLAT_UINT64_LEAST
    const uint64_least UInt64Least_MinValue = 0;
    const uint64_least UInt64Least_MaxValue = CFLAT_UINT64_LEAST_MAX;
#endif

/* Fast integer types */
const int8_fast Int8Fast_MinValue = CFLAT_INT8_FAST_MIN;
const int8_fast Int8Fast_MaxValue = CFLAT_INT8_FAST_MAX;
const uint8_fast UInt8Fast_MinValue = 0;
const uint8_fast UInt8Fast_MaxValue = CFLAT_UINT8_FAST_MAX;
const int16_fast Int16Fast_MinValue = CFLAT_INT16_FAST_MIN;
const int16_fast Int16Fast_MaxValue = CFLAT_INT16_FAST_MAX;
const uint16_fast UInt16Fast_MinValue = 0;
const uint16_fast UInt16Fast_MaxValue = CFLAT_UINT16_FAST_MAX;
const int32_fast Int32Fast_MinValue = CFLAT_INT32_FAST_MIN;
const int32_fast Int32Fast_MaxValue = CFLAT_INT32_FAST_MAX;
const uint32_fast UInt32Fast_MinValue = 0;
const uint32_fast UInt32Fast_MaxValue = CFLAT_UINT32_FAST_MAX;

#ifdef CFLAT_INT64_FAST
    const int64_fast Int64Fast_MinValue = CFLAT_INT64_FAST_MIN;
    const int64_fast Int64Fast_MaxValue = CFLAT_INT64_FAST_MAX;
#endif

#ifdef CFLAT_UINT64_FAST
    const uint64_fast UInt64Fast_MinValue = 0;
    const uint64_fast UInt64Fast_MaxValue = CFLAT_UINT64_FAST_MAX;
#endif
