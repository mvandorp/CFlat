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

#ifndef CFLAT_CORE_NUMBER_NUMBERBUFFER_H
#define CFLAT_CORE_NUMBER_NUMBERBUFFER_H

#include "CFlat/Macros.h"
#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Double.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"

/* Forward declarations */
struct StringBuilder;

/* Macros */
#define MAX_INTEGER_BITS (sizeof(uintmax) * 8)
#define MAX_INTEGER_DIGITS (1 + MAX_INTEGER_BITS / 3)
#define MAX_DOUBLE_DIGITS (double_Digits)
#define MAX_DIGITS MAX(MAX_INTEGER_DIGITS, MAX_DOUBLE_DIGITS)

/* Types */
typedef union NumberValue {
    uintmax UIntValue;
    float SingleValue;
    double DoubleValue;
} NumberValue;

typedef enum NumberType {
    NumberType_UInt,
    NumberType_Single,
    NumberType_Double
} NumberType;

typedef struct NumberBuffer {
    NumberValue Value;
    NumberType ValueType;

    bool IsNegative;
    bool IsExponential;
    int Exponent;
    int DecimalPlace;

    int LeadingIntegerZeros;
    int TrailingDecimalZeros;

    int DigitCount;
    char Digits[MAX_DIGITS];
} NumberBuffer;

#undef MAX_INTEGER_BITS
#undef MAX_INTEGER_DIGITS
#undef MAX_DOUBLE_DIGITS
#undef MAX_DIGITS

/* Functions */
/// <summary>
/// Destroys the given <see cref="NumberBuffer"/>.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
internal void NumberBuffer_Destructor(NumberBuffer *number);

/// <summary>
/// Initializes the given <see cref="NumberBuffer"/> with the given value.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="value">The value to initialize the <see cref="NumberBuffer"/> with.</param>
internal void NumberBuffer_FromIntMax(NumberBuffer *number, intmax value);

/// <summary>
/// Initializes the given <see cref="NumberBuffer"/> with the given value.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="value">The value to initialize the <see cref="NumberBuffer"/> with.</param>
internal void NumberBuffer_FromUIntMax(NumberBuffer *number, uintmax value);

/// <summary>
/// Initializes the given <see cref="NumberBuffer"/> with the given value.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="value">The value to initialize the <see cref="NumberBuffer"/> with.</param>
internal void NumberBuffer_FromSingle(NumberBuffer *number, float value);

/// <summary>
/// Initializes the given <see cref="NumberBuffer"/> with the given value.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="value">The value to initialize the <see cref="NumberBuffer"/> with.</param>
internal void NumberBuffer_FromDouble(NumberBuffer *number, double value);

/// <summary>
/// Formats the value of the given <see cref="NumberBuffer"/> as an integer.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="minNumDigits">The minimum number of digits.</param>
/// <param name="base">The base used to present the value as a string, between 2 and 36.</param>
/// <param name="upperCase">Whether or not digits with letter values are printed uppercase.</param>
internal void NumberBuffer_FormatInteger(NumberBuffer *number, int minNumDigits, int base, bool uppercase);

/// <summary>
/// Formats the value of the given <see cref="NumberBuffer"/> as a fixed-point number.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="precision">The number of decimal digits.</param>
internal void NumberBuffer_FormatFixedPoint(NumberBuffer *number, int precision);

/// <summary>
/// Formats the value of the given <see cref="NumberBuffer"/> as a general number.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="precision">The number of digits.</param>
internal void NumberBuffer_FormatGeneral(NumberBuffer *number, int precision);

/// <summary>
/// Formats the value of the given <see cref="NumberBuffer"/> as an exponential number.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="precision">The number of decimal digits.</param>
internal void NumberBuffer_FormatExponential(NumberBuffer *number, int precision);

/// <summary>
/// Formats the value of the given <see cref="NumberBuffer"/> as a custom number.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="integerDigits">The number of integer digits.</param>
/// <param name="decimalDigits">The number of decimal digits.</param>
/// <param name="exponentialNotation">Whether or not to use exponential format.</param>
internal void NumberBuffer_FormatCustomNumber(
    NumberBuffer *number,
    int integerDigits,
    int decimalDigits,
    bool exponentialNotation);

/// <summary>
/// Converts the given <see cref="NumberBuffer"/> to a string representation.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
internal void NumberBuffer_ToString(const NumberBuffer *number, struct StringBuilder *sb);

/// <summary>
/// Gets the exponent of the given <see cref="NumberBuffer"/>.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <returns>The exponent of <paramref name="number"/>.</returns>
internal int NumberBuffer_GetExponent(const NumberBuffer *number);

/// <summary>
/// Gets the number of integer digits in the given <see cref="NumberBuffer"/>.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <returns>The number of integer digits in <paramref name="number"/>.</returns>
internal int NumberBuffer_GetIntegerCount(const NumberBuffer *number);

/// <summary>
/// Gets the number of decimal digits in the given <see cref="NumberBuffer"/>.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <returns>The number of decimal digits in <paramref name="number"/>.</returns>
internal int NumberBuffer_GetDecimalCount(const NumberBuffer *number);

/// <summary>
/// Gets the integer digit at the given index of the given <see cref="NumberBuffer"/>.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="index">The index of the integer digit for which to retrieve the value.</param>
/// <returns>The integer digit at <paramref name="index"/>.</returns>
internal char NumberBuffer_GetIntegerDigit(const NumberBuffer *number, int index);

/// <summary>
/// Gets the decimal digit at the given index of the given <see cref="NumberBuffer"/>.
/// </summary>
/// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <param name="index">The index of the decimal digit for which to retrieve the value.</param>
/// <returns>The decimal digit at <paramref name="index"/>.</returns>
internal char NumberBuffer_GetDecimalDigit(const NumberBuffer *number, int index);

/// <summary>
/// Determines whether the given <see cref="NumberBuffer"/> is negative.
/// </summary>
/// <param name="value">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <returns><see cref="true"/> if <paramref name="value"/> is negative; otherwise, <see cref="false"/>.</returns>
internal bool NumberBuffer_IsNegative(const NumberBuffer *value);

/// <summary>
/// Determines whether the given <see cref="NumberBuffer"/> represents zero after formatting the number.
/// </summary>
/// <param name="value">Pointer to a <see cref="NumberBuffer"/>.</param>
/// <returns><see cref="true"/> if <paramref name="value"/> represents zero; otherwise, <see cref="false"/>.</returns>
internal bool NumberBuffer_IsZero(const NumberBuffer *value);

#endif
