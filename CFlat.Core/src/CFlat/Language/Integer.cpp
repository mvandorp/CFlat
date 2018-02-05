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
#include "CFlat/Validate.h"

using namespace CFlat;

/**************************************/
/* Public function definitions        */
/**************************************/

/* IntPtr */
#ifdef CFLAT_INTPTR
    const intptr IntPtr::MinValue = INTPTR_MINVALUE;

    const intptr IntPtr::MaxValue = INTPTR_MAXVALUE;

    intptr IntPtr::CheckedAddition(intptr x, intptr y)
    {
        Validate_IsTrue(
            (y <= 0 || x <= IntPtr::MaxValue - y) &&
            (y >= 0 || x >= IntPtr::MinValue - y),
            OverflowException());

        return x + y;
    }

    intptr IntPtr::CheckedSubtraction(intptr x, intptr y)
    {
        Validate_IsTrue(
            (y <= 0 || x <= IntPtr::MaxValue + y) &&
            (y >= 0 || x >= IntPtr::MinValue + y),
            OverflowException());

        return x - y;
    }

    String IntPtr::ToString(intptr value)
    {
        return IntPtr::ToString(value, nullptr);
    }

    String IntPtr::ToString(intptr value, const String *format)
    {
        if (value < 0 && Number::IsNonDecimalFormat(format)) {
            return UIntMax::ToString(static_cast<uintmax>(value) & UIntPtr::MaxValue, format);
        }

        return IntMax::ToString(static_cast<intmax>(value), format);
    }

    void IntPtr::ToString(StringBuilder &sb, intptr value, const String *format)
    {
        if (value < 0 && Number::IsNonDecimalFormat(format)) {
            UIntMax::ToString(static_cast<uintmax>(value) & UIntPtr::MaxValue, format);
        }
        else {
            IntMax::ToString(sb, static_cast<intmax>(value), format);
        }
    }
#endif

#ifdef CFLAT_UINTPTR
    const uintptr UIntPtr::MinValue = UINTPTR_MINVALUE;

    const uintptr UIntPtr::MaxValue = UINTPTR_MAXVALUE;

    uintptr UIntPtr::CheckedAddition(uintptr x, uintptr y)
    {
        Validate_IsTrue(x <= UIntPtr::MaxValue - y, OverflowException());

        return x + y;
    }

    uintptr UIntPtr::CheckedSubtraction(uintptr x, uintptr y)
    {
        Validate_IsTrue(x >= y, OverflowException());

        return x - y;
    }

    String UIntPtr::ToString(uintptr value)
    {
        return UIntPtr::ToString(value, nullptr);
    }

    String UIntPtr::ToString(uintptr value, const String *format)
    {
        return UIntMax::ToString(static_cast<uintmax>(value), format);
    }

    void UIntPtr::ToString(StringBuilder &sb, uintptr value, const String *format)
    {
        UIntMax::ToString(sb, static_cast<uintmax>(value), format);
    }
#endif

/* UIntSize */
const uintsize UIntSize::MinValue = UINTSIZE_MINVALUE;

const uintsize UIntSize::MaxValue = UINTSIZE_MAXVALUE;

uintsize UIntSize::CheckedAddition(uintsize x, uintsize y)
{
    Validate_IsTrue(x <= UIntSize::MaxValue - y, OverflowException());

    return x + y;
}

uintsize UIntSize::CheckedSubtraction(uintsize x, uintsize y)
{
    Validate_IsTrue(x >= y, OverflowException());

    return x - y;
}

uintsize UIntSize::CheckedMultiplication(uintsize x, uintsize y)
{
    Validate_IsTrue(x <= UIntSize::MaxValue / y, OverflowException());

    return x * y;
}

uintsize UIntSize::CheckedDivision(uintsize x, uintsize y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return x / y;
}

uintsize UIntSize::Max(uintsize x, uintsize y)
{
    return MAX(x, y);
}

uintsize UIntSize::Min(uintsize x, uintsize y)
{
    return MIN(x, y);
}

String UIntSize::ToString(uintsize value)
{
    return UIntSize::ToString(value, nullptr);
}

String UIntSize::ToString(uintsize value, const String *format)
{
    return UIntMax::ToString(static_cast<uintmax>(value), format);
}

void UIntSize::ToString(StringBuilder &sb, uintsize value, const String *format)
{
    UIntMax::ToString(sb, static_cast<uintmax>(value), format);
}

/* IntFSize */
const intfsize IntFSize::MinValue = INTFSIZE_MINVALUE;

const intfsize IntFSize::MaxValue = INTFSIZE_MAXVALUE;

intfsize IntFSize::CheckedAddition(intfsize x, intfsize y)
{
    Validate_IsTrue(
        (y <= 0 || x <= IntFSize::MaxValue - y) &&
        (y >= 0 || x >= IntFSize::MinValue - y),
        OverflowException());

    return x + y;
}

intfsize IntFSize::CheckedSubtraction(intfsize x, intfsize y)
{
    Validate_IsTrue(
        (y <= 0 || x <= IntFSize::MaxValue + y) &&
        (y >= 0 || x >= IntFSize::MinValue + y),
        OverflowException());

    return x - y;
}

intfsize IntFSize::CheckedMultiplication(intfsize x, intfsize y)
{
    Validate_IsTrue(
        (x <= IntFSize::MaxValue / y) &&
        (x >= IntFSize::MinValue / y) &&
        (x != -1 || y != IntFSize::MinValue) &&
        (y != -1 || x != IntFSize::MinValue),
        OverflowException());

    return x * y;
}

intfsize IntFSize::CheckedDivision(intfsize x, intfsize y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return x / y;
}

intfsize IntFSize::Max(intfsize x, intfsize y)
{
    return MAX(x, y);
}

intfsize IntFSize::Min(intfsize x, intfsize y)
{
    return MIN(x, y);
}

String IntFSize::ToString(intfsize value)
{
    return IntFSize::ToString(value, nullptr);
}

String IntFSize::ToString(intfsize value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        return UIntMax::ToString(static_cast<uintmax>(value) & IntFSize::MaxValue, format);
    }

    return IntMax::ToString(static_cast<intmax>(value), format);
}

void IntFSize::ToString(StringBuilder &sb, intfsize value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        UIntMax::ToString(sb, static_cast<uintmax>(value) & IntFSize::MaxValue, format);
    }
    else {
        IntMax::ToString(sb, static_cast<intmax>(value), format);
    }
}

/* Byte */
const sbyte SByte::MinValue = SBYTE_MINVALUE;

const sbyte SByte::MaxValue = SBYTE_MAXVALUE;

sbyte SByte::CheckedAddition(sbyte x, sbyte y)
{
    Validate_IsTrue(
        (y <= 0 || x <= SByte::MaxValue - y) &&
        (y >= 0 || x >= SByte::MinValue - y),
        OverflowException());

    return static_cast<sbyte>(x + y);
}

sbyte SByte::CheckedSubtraction(sbyte x, sbyte y)
{
    Validate_IsTrue(
        (y <= 0 || x <= SByte::MaxValue + y) &&
        (y >= 0 || x >= SByte::MinValue + y),
        OverflowException());

    return static_cast<sbyte>(x - y);
}

sbyte SByte::CheckedMultiplication(sbyte x, sbyte y)
{
    Validate_IsTrue(
        (x <= SByte::MaxValue / y) &&
        (x >= SByte::MinValue / y) &&
        (x != -1 || y != SByte::MinValue) &&
        (y != -1 || x != SByte::MinValue),
        OverflowException());

    return static_cast<sbyte>(x * y);
}

sbyte SByte::CheckedDivision(sbyte x, sbyte y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return static_cast<sbyte>(x / y);
}

sbyte SByte::Max(sbyte x, sbyte y)
{
    return MAX(x, y);
}

sbyte SByte::Min(sbyte x, sbyte y)
{
    return MIN(x, y);
}

String SByte::ToString(sbyte value)
{
    return SByte::ToString(value, nullptr);
}

String SByte::ToString(sbyte value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        return UIntMax::ToString(static_cast<uintmax>(value) & Byte::MaxValue, format);
    }

    return IntMax::ToString(static_cast<intmax>(value), format);
}

void SByte::ToString(StringBuilder &sb, sbyte value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        UIntMax::ToString(sb, static_cast<uintmax>(value) & Byte::MaxValue, format);
    }
    else {
        IntMax::ToString(sb, static_cast<intmax>(value), format);
    }
}

const byte Byte::MinValue = BYTE_MINVALUE;

const byte Byte::MaxValue = BYTE_MAXVALUE;

byte Byte::CheckedAddition(byte x, byte y)
{
    Validate_IsTrue(x <= Byte::MaxValue - y, OverflowException());

    return static_cast<byte>(x + y);
}

byte Byte::CheckedSubtraction(byte x, byte y)
{
    Validate_IsTrue(x >= y, OverflowException());

    return static_cast<byte>(x - y);
}

byte Byte::CheckedMultiplication(byte x, byte y)
{
    Validate_IsTrue(x <= Byte::MaxValue / y, OverflowException());

    return static_cast<byte>(x * y);
}

byte Byte::CheckedDivision(byte x, byte y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return static_cast<byte>(x / y);
}

byte Byte::Max(byte x, byte y)
{
    return MAX(x, y);
}

byte Byte::Min(byte x, byte y)
{
    return MIN(x, y);
}

String Byte::ToString(byte value)
{
    return Byte::ToString(value, nullptr);
}

String Byte::ToString(byte value, const String *format)
{
    return UIntMax::ToString(static_cast<uintmax>(value), format);
}

void Byte::ToString(StringBuilder &sb, byte value, const String *format)
{
    UIntMax::ToString(sb, static_cast<uintmax>(value), format);
}

/* Short */
const short Short::MinValue = SHORT_MINVALUE;

const short Short::MaxValue = SHORT_MAXVALUE;

short Short::CheckedAddition(short x, short y)
{
    Validate_IsTrue(
        (y <= 0 || x <= Short::MaxValue - y) &&
        (y >= 0 || x >= Short::MinValue - y),
        OverflowException());

    return static_cast<short>(x + y);
}

short Short::CheckedSubtraction(short x, short y)
{
    Validate_IsTrue(
        (y <= 0 || x <= Short::MaxValue + y) &&
        (y >= 0 || x >= Short::MinValue + y),
        OverflowException());

    return static_cast<short>(x - y);
}

short Short::CheckedMultiplication(short x, short y)
{
    Validate_IsTrue(
        (x <= Short::MaxValue / y) &&
        (x >= Short::MinValue / y) &&
        (x != -1 || y != Short::MinValue) &&
        (y != -1 || x != Short::MinValue),
        OverflowException());

    return static_cast<short>(x * y);
}

short Short::CheckedDivision(short x, short y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return static_cast<short>(x / y);
}

short Short::Max(short x, short y)
{
    return MAX(x, y);
}

short Short::Min(short x, short y)
{
    return MIN(x, y);
}

String Short::ToString(short value)
{
    return Short::ToString(value, nullptr);
}

String Short::ToString(short value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        return UIntMax::ToString(static_cast<uintmax>(value) & UShort::MaxValue, format);
    }

    return IntMax::ToString(static_cast<intmax>(value), format);
}

void Short::ToString(StringBuilder &sb, short value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        UIntMax::ToString(sb, static_cast<uintmax>(value) & UShort::MaxValue, format);
    }
    else {
        IntMax::ToString(sb, static_cast<intmax>(value), format);
    }
}

const ushort UShort::MinValue = USHORT_MINVALUE;

const ushort UShort::MaxValue = USHORT_MAXVALUE;

ushort UShort::Max(ushort x, ushort y)
{
    return MAX(x, y);
}

ushort UShort::Min(ushort x, ushort y)
{
    return MIN(x, y);
}

ushort UShort::CheckedAddition(ushort x, ushort y)
{
    Validate_IsTrue(x <= UShort::MaxValue - y, OverflowException());

    return static_cast<ushort>(x + y);
}

ushort UShort::CheckedSubtraction(ushort x, ushort y)
{
    Validate_IsTrue(x >= y, OverflowException());

    return static_cast<ushort>(x - y);
}

ushort UShort::CheckedMultiplication(ushort x, ushort y)
{
    Validate_IsTrue(x <= UShort::MaxValue / y, OverflowException());

    return static_cast<ushort>(x * y);
}

ushort UShort::CheckedDivision(ushort x, ushort y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return static_cast<ushort>(x / y);
}

String UShort::ToString(ushort value)
{
    return UShort::ToString(value, nullptr);
}

String UShort::ToString(ushort value, const String *format)
{
    return UIntMax::ToString(static_cast<uintmax>(value), format);
}

void UShort::ToString(StringBuilder &sb, ushort value, const String *format)
{
    UIntMax::ToString(sb, static_cast<uintmax>(value), format);
}

/* Int */
const int Int::MinValue = INT_MINVALUE;

const int Int::MaxValue = INT_MAXVALUE;

int Int::CheckedAddition(int x, int y)
{
    Validate_IsTrue(
        (y <= 0 || x <= Int::MaxValue - y) &&
        (y >= 0 || x >= Int::MinValue - y),
        OverflowException());

    return x + y;
}

int Int::CheckedSubtraction(int x, int y)
{
    Validate_IsTrue(
        (y <= 0 || x <= Int::MaxValue + y) &&
        (y >= 0 || x >= Int::MinValue + y),
        OverflowException());

    return x - y;
}

int Int::CheckedMultiplication(int x, int y)
{
    Validate_IsTrue(
        (x <= Int::MaxValue / y) &&
        (x >= Int::MinValue / y) &&
        (x != -1 || y != Int::MinValue) &&
        (y != -1 || x != Int::MinValue),
        OverflowException());

    return x * y;
}

int Int::CheckedDivision(int x, int y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return x / y;
}

int Int::Max(int x, int y)
{
    return MAX(x, y);
}

int Int::Min(int x, int y)
{
    return MIN(x, y);
}

String Int::ToString(int value)
{
    return Int::ToString(value, nullptr);
}

String Int::ToString(int value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        return UIntMax::ToString(static_cast<uintmax>(value) & UInt::MaxValue, format);
    }

    return IntMax::ToString(static_cast<intmax>(value), format);
}

void Int::ToString(StringBuilder &sb, int value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        UIntMax::ToString(sb, static_cast<uintmax>(value) & UInt::MaxValue, format);
    }
    else {
        IntMax::ToString(sb, static_cast<intmax>(value), format);
    }
}

const uint UInt::MinValue = UINT_MINVALUE;

const uint UInt::MaxValue = UINT_MAXVALUE;

uint UInt::CheckedAddition(uint x, uint y)
{
    Validate_IsTrue(x <= UInt::MaxValue - y, OverflowException());

    return x + y;
}

uint UInt::CheckedSubtraction(uint x, uint y)
{
    Validate_IsTrue(x >= y, OverflowException());

    return x - y;
}

uint UInt::CheckedMultiplication(uint x, uint y)
{
    Validate_IsTrue(x <= UInt::MaxValue / y, OverflowException());

    return x * y;
}

uint UInt::CheckedDivision(uint x, uint y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return x / y;
}

uint UInt::Max(uint x, uint y)
{
    return MAX(x, y);
}

uint UInt::Min(uint x, uint y)
{
    return MIN(x, y);
}

String UInt::ToString(uint value)
{
    return UInt::ToString(value, nullptr);
}

String UInt::ToString(uint value, const String *format)
{
    return UIntMax::ToString(static_cast<uintmax>(value), format);
}

void UInt::ToString(StringBuilder &sb, uint value, const String *format)
{
    UIntMax::ToString(sb, static_cast<uintmax>(value), format);
}

/* Long */
const long Long::MinValue = LONG_MINVALUE;

const long Long::MaxValue = LONG_MAXVALUE;

long Long::CheckedAddition(long x, long y)
{
    Validate_IsTrue(
        (y <= 0 || x <= Long::MaxValue - y) &&
        (y >= 0 || x >= Long::MinValue - y),
        OverflowException());

    return x + y;
}

long Long::CheckedSubtraction(long x, long y)
{
    Validate_IsTrue(
        (y <= 0 || x <= Long::MaxValue + y) &&
        (y >= 0 || x >= Long::MinValue + y),
        OverflowException());

    return x - y;
}

long Long::CheckedMultiplication(long x, long y)
{
    Validate_IsTrue(
        (x <= Long::MaxValue / y) &&
        (x >= Long::MinValue / y) &&
        (x != -1 || y != Long::MinValue) &&
        (y != -1 || x != Long::MinValue),
        OverflowException());

    return x * y;
}

long Long::CheckedDivision(long x, long y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return x / y;
}

long Long::Max(long x, long y)
{
    return MAX(x, y);
}

long Long::Min(long x, long y)
{
    return MIN(x, y);
}

String Long::ToString(long value)
{
    return Long::ToString(value, nullptr);
}

String Long::ToString(long value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        return UIntMax::ToString(static_cast<uintmax>(value) & ULong::MaxValue, format);
    }

    return IntMax::ToString(static_cast<intmax>(value), format);
}

void Long::ToString(StringBuilder &sb, long value, const String *format)
{
    if (value < 0 && Number::IsNonDecimalFormat(format)) {
        UIntMax::ToString(sb, static_cast<uintmax>(value) & ULong::MaxValue, format);
    }
    else {
        IntMax::ToString(sb, static_cast<intmax>(value), format);
    }
}

const ulong ULong::MinValue = ULONG_MINVALUE;

const ulong ULong::MaxValue = ULONG_MAXVALUE;

ulong ULong::CheckedAddition(ulong x, ulong y)
{
    Validate_IsTrue(x <= ULong::MaxValue - y, OverflowException());

    return x + y;
}

ulong ULong::CheckedSubtraction(ulong x, ulong y)
{
    Validate_IsTrue(x >= y, OverflowException());

    return x - y;
}

ulong ULong::CheckedMultiplication(ulong x, ulong y)
{
    Validate_IsTrue(x <= ULong::MaxValue / y, OverflowException());

    return x * y;
}

ulong ULong::CheckedDivision(ulong x, ulong y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return x / y;
}

ulong ULong::Max(ulong x, ulong y)
{
    return MAX(x, y);
}

ulong ULong::Min(ulong x, ulong y)
{
    return MIN(x, y);
}

String ULong::ToString(ulong value)
{
    return ULong::ToString(value, nullptr);
}

String ULong::ToString(ulong value, const String *format)
{
    return UIntMax::ToString(static_cast<uintmax>(value), format);
}

void ULong::ToString(StringBuilder &sb, ulong value, const String *format)
{
    UIntMax::ToString(sb, static_cast<uintmax>(value), format);
}

/* IntMax */
const intmax IntMax::MinValue = INTMAX_MINVALUE;

const intmax IntMax::MaxValue = INTMAX_MAXVALUE;

intmax IntMax::CheckedAddition(intmax x, intmax y)
{
    Validate_IsTrue(
        (y <= 0 || x <= IntMax::MaxValue - y) &&
        (y >= 0 || x >= IntMax::MinValue - y),
        OverflowException());

    return x + y;
}

intmax IntMax::CheckedSubtraction(intmax x, intmax y)
{
    Validate_IsTrue(
        (y <= 0 || x <= IntMax::MaxValue + y) &&
        (y >= 0 || x >= IntMax::MinValue + y),
        OverflowException());

    return x - y;
}

intmax IntMax::CheckedMultiplication(intmax x, intmax y)
{
    Validate_IsTrue(
        (x <= IntMax::MaxValue / y) &&
        (x >= IntMax::MinValue / y) &&
        (x != -1 || y != IntMax::MinValue) &&
        (y != -1 || x != IntMax::MinValue),
        OverflowException());

    return x * y;
}

intmax IntMax::CheckedDivision(intmax x, intmax y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return x / y;
}

intmax IntMax::Max(intmax x, intmax y)
{
    return MAX(x, y);
}

intmax IntMax::Min(intmax x, intmax y)
{
    return MIN(x, y);
}

String IntMax::ToString(intmax value)
{
    return IntMax::ToString(value, nullptr);
}

String IntMax::ToString(intmax value, const String *format)
{
    return Number::Format(value, format);
}

void IntMax::ToString(StringBuilder &sb, intmax value, const String *format)
{
    Number::Format(sb, value, format);
}

const uintmax UIntMax::MinValue = UINTMAX_MINVALUE;

const uintmax UIntMax::MaxValue = UINTMAX_MAXVALUE;

uintmax UIntMax::CheckedAddition(uintmax x, uintmax y)
{
    Validate_IsTrue(x <= UIntMax::MaxValue - y, OverflowException());

    return x + y;
}

uintmax UIntMax::CheckedSubtraction(uintmax x, uintmax y)
{
    Validate_IsTrue(x >= y, OverflowException());

    return x - y;
}

uintmax UIntMax::CheckedMultiplication(uintmax x, uintmax y)
{
    Validate_IsTrue(x <= UIntMax::MaxValue / y, OverflowException());

    return x * y;
}

uintmax UIntMax::CheckedDivision(uintmax x, uintmax y)
{
    Validate_IsTrue(y != 0, DivideByZeroException());

    return x / y;
}

uintmax UIntMax::Max(uintmax x, uintmax y)
{
    return MAX(x, y);
}

uintmax UIntMax::Min(uintmax x, uintmax y)
{
    return MIN(x, y);
}

String UIntMax::ToString(uintmax value)
{
    return UIntMax::ToString(value, nullptr);
}

String UIntMax::ToString(uintmax value, const String *format)
{
    return Number::Format(value, format);
}

void UIntMax::ToString(StringBuilder &sb, uintmax value, const String *format)
{
    Number::Format(sb, value, format);
}
