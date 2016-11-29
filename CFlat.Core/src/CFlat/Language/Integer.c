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

#include "CFlat/Language/Integer.h"

#include "CFlat.h"
#include "CFlat/Macros.h"
#include "CFlat/Number.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"

/**************************************/
/* Public function definitions        */
/**************************************/

/* IntPtr */
#ifdef CFLAT_INTPTR
public intptr intptr_CheckedAddition(intptr x, intptr y)
{
    Validate_IsTrue(
        (y <= 0 || x <= intptr_MaxValue - y) &&
        (y >= 0 || x >= intptr_MinValue - y),
        OverflowException, null);

    return x + y;
}

public intptr intptr_CheckedSubtraction(intptr x, intptr y)
{
    Validate_IsTrue(
        (y <= 0 || x <= intptr_MaxValue + y) &&
        (y >= 0 || x >= intptr_MinValue + y),
        OverflowException, null);

    return x - y;
}

public String *intptr_ToString(intptr value)
{
    return intptr_ToStringFormat(value, null);
}

public String *intptr_ToStringFormat(intptr value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        return uintmax_ToStringFormat((uintmax)value & uintptr_MaxValue, format);
    }

    return intmax_ToStringFormat((intmax)value, format);
}

public String *intptr_ToStringFormatC(intptr value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return intptr_ToStringFormat(value, str);
}
#endif

#ifdef CFLAT_UINTPTR
public uintptr uintptr_CheckedAddition(uintptr x, uintptr y)
{
    Validate_IsTrue(x <= uintptr_MaxValue - y, OverflowException, null);

    return x + y;
}

public uintptr uintptr_CheckedSubtraction(uintptr x, uintptr y)
{
    Validate_IsTrue(x >= y, OverflowException, null);

    return x - y;
}

public String *uintptr_ToString(uintptr value)
{
    return uintptr_ToStringFormat(value, null);
}

public String *uintptr_ToStringFormat(uintptr value, const String *format)
{
    return uintmax_ToStringFormat((uintmax)value, format);
}

public String *uintptr_ToStringFormatC(uintptr value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return uintptr_ToStringFormat(value, str);
}
#endif

/* UIntSize */
public uintsize uintsize_CheckedAddition(uintsize x, uintsize y)
{
    Validate_IsTrue(x <= uintsize_MaxValue - y, OverflowException, null);

    return x + y;
}

public uintsize uintsize_CheckedSubtraction(uintsize x, uintsize y)
{
    Validate_IsTrue(x >= y, OverflowException, null);

    return x - y;
}

public uintsize uintsize_CheckedMultiplication(uintsize x, uintsize y)
{
    Validate_IsTrue(x <= uintsize_MaxValue / y, OverflowException, null);

    return x * y;
}

public uintsize uintsize_CheckedDivision(uintsize x, uintsize y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return x / y;
}

public uintsize uintsize_Max(uintsize x, uintsize y) {
    return MAX(x, y);
}

public uintsize uintsize_Min(uintsize x, uintsize y) {
    return MIN(x, y);
}

public String *uintsize_ToString(uintsize value)
{
    return uintsize_ToStringFormat(value, null);
}

public String *uintsize_ToStringFormat(uintsize value, const String *format)
{
    return uintmax_ToStringFormat((uintmax)value, format);
}

public String *uintsize_ToStringFormatC(uintsize value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return uintsize_ToStringFormat(value, str);
}

/* IntFSize */
public intfsize intfsize_CheckedAddition(intfsize x, intfsize y)
{
    Validate_IsTrue(
        (y <= 0 || x <= intfsize_MaxValue - y) &&
        (y >= 0 || x >= intfsize_MinValue - y),
        OverflowException, null);

    return x + y;
}

public intfsize intfsize_CheckedSubtraction(intfsize x, intfsize y)
{
    Validate_IsTrue(
        (y <= 0 || x <= intfsize_MaxValue + y) &&
        (y >= 0 || x >= intfsize_MinValue + y),
        OverflowException, null);

    return x - y;
}

public intfsize intfsize_CheckedMultiplication(intfsize x, intfsize y)
{
    Validate_IsTrue(
        (x <= intfsize_MaxValue / y) &&
        (x >= intfsize_MinValue / y) &&
        (x != -1 || y != intfsize_MinValue) &&
        (y != -1 || x != intfsize_MinValue),
        OverflowException, null);

    return x * y;
}

public intfsize intfsize_CheckedDivision(intfsize x, intfsize y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return x / y;
}

public intfsize intfsize_Max(intfsize x, intfsize y) {
    return MAX(x, y);
}

public intfsize intfsize_Min(intfsize x, intfsize y) {
    return MIN(x, y);
}

public String *intfsize_ToString(intfsize value)
{
    return intfsize_ToStringFormat(value, null);
}

public String *intfsize_ToStringFormat(intfsize value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        return uintmax_ToStringFormat((uintmax)value & intfsize_MaxValue, format);
    }

    return intmax_ToStringFormat((intmax)value, format);
}

public String *intfsize_ToStringFormatC(intfsize value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return intfsize_ToStringFormat(value, str);
}

/* Byte */
public sbyte sbyte_CheckedAddition(sbyte x, sbyte y)
{
    Validate_IsTrue(
        (y <= 0 || x <= sbyte_MaxValue - y) &&
        (y >= 0 || x >= sbyte_MinValue - y),
        OverflowException, null);

    return (sbyte)(x + y);
}

public sbyte sbyte_CheckedSubtraction(sbyte x, sbyte y)
{
    Validate_IsTrue(
        (y <= 0 || x <= sbyte_MaxValue + y) &&
        (y >= 0 || x >= sbyte_MinValue + y),
        OverflowException, null);

    return (sbyte)(x - y);
}

public sbyte sbyte_CheckedMultiplication(sbyte x, sbyte y)
{
    Validate_IsTrue(
        (x <= sbyte_MaxValue / y) &&
        (x >= sbyte_MinValue / y) &&
        (x != -1 || y != sbyte_MinValue) &&
        (y != -1 || x != sbyte_MinValue),
        OverflowException, null);

    return (sbyte)(x * y);
}

public sbyte sbyte_CheckedDivision(sbyte x, sbyte y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return (sbyte)(x / y);
}

public sbyte sbyte_Max(sbyte x, sbyte y) {
    return MAX(x, y);
}

public sbyte sbyte_Min(sbyte x, sbyte y) {
    return MIN(x, y);
}

public String *sbyte_ToString(sbyte value)
{
    return sbyte_ToStringFormat(value, null);
}

public String *sbyte_ToStringFormat(sbyte value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        return uintmax_ToStringFormat((uintmax)value & byte_MaxValue, format);
    }

    return intmax_ToStringFormat((intmax)value, format);
}

public String *sbyte_ToStringFormatC(sbyte value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return sbyte_ToStringFormat(value, str);
}

public byte byte_CheckedAddition(byte x, byte y)
{
    Validate_IsTrue(x <= byte_MaxValue - y, OverflowException, null);

    return (byte)(x + y);
}

public byte byte_CheckedSubtraction(byte x, byte y)
{
    Validate_IsTrue(x >= y, OverflowException, null);

    return (byte)(x - y);
}

public byte byte_CheckedMultiplication(byte x, byte y)
{
    Validate_IsTrue(x <= byte_MaxValue / y, OverflowException, null);

    return (byte)(x * y);
}

public byte byte_CheckedDivision(byte x, byte y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return (byte)(x / y);
}

public byte byte_Max(byte x, byte y) {
    return MAX(x, y);
}

public byte byte_Min(byte x, byte y) {
    return MIN(x, y);
}

public String *byte_ToString(byte value)
{
    return byte_ToStringFormat(value, null);
}

public String *byte_ToStringFormat(byte value, const String *format)
{
    return uintmax_ToStringFormat((uintmax)value, format);
}

public String *byte_ToStringFormatC(byte value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return byte_ToStringFormat(value, str);
}

/* Short */
public short short_CheckedAddition(short x, short y)
{
    Validate_IsTrue(
        (y <= 0 || x <= short_MaxValue - y) &&
        (y >= 0 || x >= short_MinValue - y),
        OverflowException, null);

    return (short)(x + y);
}

public short short_CheckedSubtraction(short x, short y)
{
    Validate_IsTrue(
        (y <= 0 || x <= short_MaxValue + y) &&
        (y >= 0 || x >= short_MinValue + y),
        OverflowException, null);

    return (short)(x - y);
}

public short short_CheckedMultiplication(short x, short y)
{
    Validate_IsTrue(
        (x <= short_MaxValue / y) &&
        (x >= short_MinValue / y) &&
        (x != -1 || y != short_MinValue) &&
        (y != -1 || x != short_MinValue),
        OverflowException, null);

    return (short)(x * y);
}

public short short_CheckedDivision(short x, short y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return (short)(x / y);
}

public short short_Max(short x, short y) {
    return MAX(x, y);
}

public short short_Min(short x, short y) {
    return MIN(x, y);
}

public String *short_ToString(short value)
{
    return short_ToStringFormat(value, null);
}

public String *short_ToStringFormat(short value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        return uintmax_ToStringFormat((uintmax)value & ushort_MaxValue, format);
    }

    return intmax_ToStringFormat((intmax)value, format);
}

public String *short_ToStringFormatC(short value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return short_ToStringFormat(value, str);
}

public ushort ushort_Max(ushort x, ushort y) {
    return MAX(x, y);
}

public ushort ushort_Min(ushort x, ushort y) {
    return MIN(x, y);
}

public ushort ushort_CheckedAddition(ushort x, ushort y)
{
    Validate_IsTrue(x <= ushort_MaxValue - y, OverflowException, null);

    return (ushort)(x + y);
}

public ushort ushort_CheckedSubtraction(ushort x, ushort y)
{
    Validate_IsTrue(x >= y, OverflowException, null);

    return (ushort)(x - y);
}

public ushort ushort_CheckedMultiplication(ushort x, ushort y)
{
    Validate_IsTrue(x <= ushort_MaxValue / y, OverflowException, null);

    return (ushort)(x * y);
}

public ushort ushort_CheckedDivision(ushort x, ushort y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return (ushort)(x / y);
}

public String *ushort_ToString(ushort value)
{
    return ushort_ToStringFormat(value, null);
}

public String *ushort_ToStringFormat(ushort value, const String *format)
{
    return uintmax_ToStringFormat((uintmax)value, format);
}

public String *ushort_ToStringFormatC(ushort value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return ushort_ToStringFormat(value, str);
}

/* Int */
public int int_CheckedAddition(int x, int y)
{
    Validate_IsTrue(
        (y <= 0 || x <= int_MaxValue - y) &&
        (y >= 0 || x >= int_MinValue - y),
        OverflowException, null);

    return x + y;
}

public int int_CheckedSubtraction(int x, int y)
{
    Validate_IsTrue(
        (y <= 0 || x <= int_MaxValue + y) &&
        (y >= 0 || x >= int_MinValue + y),
        OverflowException, null);

    return x - y;
}

public int int_CheckedMultiplication(int x, int y)
{
    Validate_IsTrue(
        (x <= int_MaxValue / y) &&
        (x >= int_MinValue / y) &&
        (x != -1 || y != int_MinValue) &&
        (y != -1 || x != int_MinValue),
        OverflowException, null);

    return x * y;
}

public int int_CheckedDivision(int x, int y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return x / y;
}

public int int_Max(int x, int y) {
    return MAX(x, y);
}

public int int_Min(int x, int y) {
    return MIN(x, y);
}

public String *int_ToString(int value)
{
    return int_ToStringFormat(value, null);
}

public String *int_ToStringFormat(int value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        return uintmax_ToStringFormat((uintmax)value & uint_MaxValue, format);
    }

    return intmax_ToStringFormat((intmax)value, format);
}

public String *int_ToStringFormatC(int value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return int_ToStringFormat(value, str);
}

public uint uint_CheckedAddition(uint x, uint y)
{
    Validate_IsTrue(x <= uint_MaxValue - y, OverflowException, null);

    return x + y;
}

public uint uint_CheckedSubtraction(uint x, uint y)
{
    Validate_IsTrue(x >= y, OverflowException, null);

    return x - y;
}

public uint uint_CheckedMultiplication(uint x, uint y)
{
    Validate_IsTrue(x <= uint_MaxValue / y, OverflowException, null);

    return x * y;
}

public uint uint_CheckedDivision(uint x, uint y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return x / y;
}

public uint uint_Max(uint x, uint y) {
    return MAX(x, y);
}

public uint uint_Min(uint x, uint y) {
    return MIN(x, y);
}

public String *uint_ToString(uint value)
{
    return uint_ToStringFormat(value, null);
}

public String *uint_ToStringFormat(uint value, const String *format)
{
    return uintmax_ToStringFormat((uintmax)value, format);
}

public String *uint_ToStringFormatC(uint value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return uint_ToStringFormat(value, str);
}

/* Long */
public long long_CheckedAddition(long x, long y)
{
    Validate_IsTrue(
        (y <= 0 || x <= long_MaxValue - y) &&
        (y >= 0 || x >= long_MinValue - y),
        OverflowException, null);

    return x + y;
}

public long long_CheckedSubtraction(long x, long y)
{
    Validate_IsTrue(
        (y <= 0 || x <= long_MaxValue + y) &&
        (y >= 0 || x >= long_MinValue + y),
        OverflowException, null);

    return x - y;
}

public long long_CheckedMultiplication(long x, long y)
{
    Validate_IsTrue(
        (x <= long_MaxValue / y) &&
        (x >= long_MinValue / y) &&
        (x != -1 || y != long_MinValue) &&
        (y != -1 || x != long_MinValue),
        OverflowException, null);

    return x * y;
}

public long long_CheckedDivision(long x, long y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return x / y;
}

public long long_Max(long x, long y) {
    return MAX(x, y);
}

public long long_Min(long x, long y) {
    return MIN(x, y);
}

public String *long_ToString(long value)
{
    return long_ToStringFormat(value, null);
}

public String *long_ToStringFormat(long value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        return uintmax_ToStringFormat((uintmax)value & ulong_MaxValue, format);
    }

    return intmax_ToStringFormat((intmax)value, format);
}

public String *long_ToStringFormatC(long value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return long_ToStringFormat(value, str);
}

public ulong ulong_CheckedAddition(ulong x, ulong y)
{
    Validate_IsTrue(x <= ulong_MaxValue - y, OverflowException, null);

    return x + y;
}

public ulong ulong_CheckedSubtraction(ulong x, ulong y)
{
    Validate_IsTrue(x >= y, OverflowException, null);

    return x - y;
}

public ulong ulong_CheckedMultiplication(ulong x, ulong y)
{
    Validate_IsTrue(x <= ulong_MaxValue / y, OverflowException, null);

    return x * y;
}

public ulong ulong_CheckedDivision(ulong x, ulong y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return x / y;
}

public ulong ulong_Max(ulong x, ulong y) {
    return MAX(x, y);
}

public ulong ulong_Min(ulong x, ulong y) {
    return MIN(x, y);
}

public String *ulong_ToString(ulong value)
{
    return ulong_ToStringFormat(value, null);
}

public String *ulong_ToStringFormat(ulong value, const String *format)
{
    return uintmax_ToStringFormat((uintmax)value, format);
}

public String *ulong_ToStringFormatC(ulong value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return ulong_ToStringFormat(value, str);
}

/* IntMax */
public intmax intmax_CheckedAddition(intmax x, intmax y)
{
    Validate_IsTrue(
        (y <= 0 || x <= intmax_MaxValue - y) &&
        (y >= 0 || x >= intmax_MinValue - y),
        OverflowException, null);

    return x + y;
}

public intmax intmax_CheckedSubtraction(intmax x, intmax y)
{
    Validate_IsTrue(
        (y <= 0 || x <= intmax_MaxValue + y) &&
        (y >= 0 || x >= intmax_MinValue + y),
        OverflowException, null);

    return x - y;
}

public intmax intmax_CheckedMultiplication(intmax x, intmax y)
{
    Validate_IsTrue(
        (x <= intmax_MaxValue / y) &&
        (x >= intmax_MinValue / y) &&
        (x != -1 || y != intmax_MinValue) &&
        (y != -1 || x != intmax_MinValue),
        OverflowException, null);

    return x * y;
}

public intmax intmax_CheckedDivision(intmax x, intmax y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return x / y;
}

public intmax intmax_Max(intmax x, intmax y) {
    return MAX(x, y);
}

public intmax intmax_Min(intmax x, intmax y) {
    return MIN(x, y);
}

public String *intmax_ToString(intmax value)
{
    return intmax_ToStringFormat(value, null);
}

public String *intmax_ToStringFormat(intmax value, const String *format)
{
    return Number_FormatIntMax(value, format);
}

public String *intmax_ToStringFormatC(intmax value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return intmax_ToStringFormat(value, str);
}

public uintmax uintmax_CheckedAddition(uintmax x, uintmax y)
{
    Validate_IsTrue(x <= uintmax_MaxValue - y, OverflowException, null);

    return x + y;
}

public uintmax uintmax_CheckedSubtraction(uintmax x, uintmax y)
{
    Validate_IsTrue(x >= y, OverflowException, null);

    return x - y;
}

public uintmax uintmax_CheckedMultiplication(uintmax x, uintmax y)
{
    Validate_IsTrue(x <= uintmax_MaxValue / y, OverflowException, null);

    return x * y;
}

public uintmax uintmax_CheckedDivision(uintmax x, uintmax y)
{
    Validate_IsTrue(y != 0, DivideByZeroException, null);

    return x / y;
}

public uintmax uintmax_Max(uintmax x, uintmax y) {
    return MAX(x, y);
}

public uintmax uintmax_Min(uintmax x, uintmax y) {
    return MIN(x, y);
}

public String *uintmax_ToString(uintmax value)
{
    return uintmax_ToStringFormat(value, null);
}

public String *uintmax_ToStringFormat(uintmax value, const String *format)
{
    return Number_FormatUIntMax(value, format);
}

public String *uintmax_ToStringFormatC(uintmax value, const char *format)
{
    String strBuffer;
    String *str = String_WrapCString(format, &strBuffer);

    return uintmax_ToStringFormat(value, str);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

#ifdef CFLAT_INTPTR
internal void intptr_ToStringBuffered(StringBuilder *sb, intptr value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        uintmax_ToStringFormat((uintmax)value & uintptr_MaxValue, format);
    }
    else {
        intmax_ToStringBuffered(sb, (intmax)value, format);
    }
}
#endif

#ifdef CFLAT_UINTPTR
internal void uintptr_ToStringBuffered(StringBuilder *sb, uintptr value, const String *format)
{
    uintmax_ToStringBuffered(sb, (uintmax)value, format);
}
#endif

internal void uintsize_ToStringBuffered(StringBuilder *sb, uintsize value, const String *format)
{
    uintmax_ToStringBuffered(sb, (uintmax)value, format);
}

internal void intfsize_ToStringBuffered(StringBuilder *sb, intfsize value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        uintmax_ToStringBuffered(sb, (uintmax)value & intfsize_MaxValue, format);
    }
    else {
        intmax_ToStringBuffered(sb, (intmax)value, format);
    }
}

internal void sbyte_ToStringBuffered(StringBuilder *sb, sbyte value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        uintmax_ToStringBuffered(sb, (uintmax)value & byte_MaxValue, format);
    }
    else {
        intmax_ToStringBuffered(sb, (intmax)value, format);
    }
}

internal void byte_ToStringBuffered(StringBuilder *sb, byte value, const String *format)
{
    uintmax_ToStringBuffered(sb, (uintmax)value, format);
}

internal void short_ToStringBuffered(StringBuilder *sb, short value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        uintmax_ToStringBuffered(sb, (uintmax)value & ushort_MaxValue, format);
    }
    else {
        intmax_ToStringBuffered(sb, (intmax)value, format);
    }
}

internal void ushort_ToStringBuffered(StringBuilder *sb, ushort value, const String *format)
{
    uintmax_ToStringBuffered(sb, (uintmax)value, format);
}

internal void int_ToStringBuffered(StringBuilder *sb, int value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        uintmax_ToStringBuffered(sb, (uintmax)value & uint_MaxValue, format);
    }
    else {
        intmax_ToStringBuffered(sb, (intmax)value, format);
    }
}

internal void uint_ToStringBuffered(StringBuilder *sb, uint value, const String *format)
{
    uintmax_ToStringBuffered(sb, (uintmax)value, format);
}

internal void long_ToStringBuffered(StringBuilder *sb, long value, const String *format)
{
    if (value < 0 && Number_IsNonDecimalFormat(format)) {
        uintmax_ToStringBuffered(sb, (uintmax)value & ulong_MaxValue, format);
    }
    else {
        intmax_ToStringBuffered(sb, (intmax)value, format);
    }
}

internal void ulong_ToStringBuffered(StringBuilder *sb, ulong value, const String *format)
{
    uintmax_ToStringBuffered(sb, (uintmax)value, format);
}

internal void intmax_ToStringBuffered(StringBuilder *sb, intmax value, const String *format)
{
    Number_FormatIntMaxBuffered(sb, value, format);
}

internal void uintmax_ToStringBuffered(StringBuilder *sb, uintmax value, const String *format)
{
    Number_FormatUIntMaxBuffered(sb, value, format);
}
