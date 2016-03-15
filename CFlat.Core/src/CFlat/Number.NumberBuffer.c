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

#include "CFlat/Number.NumberBuffer.h"

#include "CFlat.h"
#include "CFlat/Math.h"
#include "CFlat/Memory.h"
#include "CFlat/StringBuilder.h"

/**************************************/
/* Private functions                  */
/**************************************/

private void NumberBuffer_Constructor(NumberBuffer *number);
private void NumberBuffer_FormatFloat(NumberBuffer *number, int precision, bool shiftIntegersBehindDecimalPoint);
private void NumberBuffer_FormatCustomExponential(NumberBuffer *number, int integerDigits, int precision);

private uintmax GetIntegerValue(const NumberBuffer *number);
private double GetFloatValue(const NumberBuffer *number, int *numSignificants, int *maxExponent);
private int Exponent(const NumberBuffer *number);
private int FloatExponent(double x);
private int IntegerExponent(uintmax x);
private double Normalize(double x, int numSignificantDigits, int maxExponent, int *exponent);
private bool HasAllZeroDigits(const NumberBuffer *number);
private void ReverseDigits(NumberBuffer *number);
private void RoundToPrecision(NumberBuffer *number, int precision);
private void PaddIntegerDigits(NumberBuffer *number, int minNumDigits);
private void PaddDecimalDigits(NumberBuffer *number, int minNumDigits);
private void StripTrailingDecimalZeros(NumberBuffer *number);

/**************************************/
/* Internal function definitions      */
/**************************************/

/* Constructor functions */
internal void NumberBuffer_FromIntMax(NumberBuffer *number, intmax value)
{
    NumberBuffer_FromUIntMax(number, value < 0 ? (uintmax)-value : (uintmax)value);

    number->IsNegative = value < 0;
}

internal void NumberBuffer_FromUIntMax(NumberBuffer *number, uintmax value)
{
    NumberBuffer_Constructor(number);

    number->Value.UIntValue = value;
    number->ValueType = NumberType_UInt;
    number->IsNegative = false;
}

internal void NumberBuffer_FromSingle(NumberBuffer *number, float value)
{
    NumberBuffer_Constructor(number);

    number->Value.SingleValue = value;
    number->ValueType = NumberType_Single;
    number->IsNegative = value < 0.0f;
}

internal void NumberBuffer_FromDouble(NumberBuffer *number, double value)
{
    NumberBuffer_Constructor(number);

    number->Value.DoubleValue = value;
    number->ValueType = NumberType_Double;
    number->IsNegative = value < 0.0;
}

/* Digit functions */
internal int NumberBuffer_GetExponent(const NumberBuffer *number)
{
    return number->Exponent;
}

internal int NumberBuffer_GetIntegerCount(const NumberBuffer *number)
{
    assert(number != null);

    return int_Max(number->DecimalPlace, 0) + number->LeadingIntegerZeros;
}

internal int NumberBuffer_GetDecimalCount(const NumberBuffer *number)
{
    assert(number != null);

    return int_Max(number->DigitCount - number->DecimalPlace, 0) + number->TrailingDecimalZeros;
}

internal char NumberBuffer_GetIntegerDigit(const NumberBuffer *number, int index)
{
    assert(number != null);
    assert(index < NumberBuffer_GetIntegerCount(number));

    int adjustedIndex = index - number->LeadingIntegerZeros;

    if (adjustedIndex < 0 || adjustedIndex >= number->DigitCount) {
        return '0';
    }

    return number->Digits[adjustedIndex];
}

internal char NumberBuffer_GetDecimalDigit(const NumberBuffer *number, int index)
{
    assert(number != null);
    assert(index < NumberBuffer_GetDecimalCount(number));

    int adjustedIndex = index + number->DecimalPlace;

    if (adjustedIndex < 0 || adjustedIndex >= number->DigitCount) {
        return '0';
    }

    return number->Digits[adjustedIndex];
}

/* Flags functions */
internal bool NumberBuffer_IsNegative(const NumberBuffer *number)
{
    assert(number != null);

    return number->IsNegative;
}

internal bool NumberBuffer_IsZero(const NumberBuffer *number)
{
    assert(number != null);

    return NumberBuffer_GetIntegerCount(number) == 0 && HasAllZeroDigits(number);
}

/* Formatting functions */
internal void NumberBuffer_FormatCustomNumber(
    NumberBuffer *number,
    int integerDigits,
    int decimalDigits,
    bool exponentialNotation)
{
    assert(number != null);
    assert(integerDigits >= 0);
    assert(decimalDigits >= 0);

    if (exponentialNotation) {
        NumberBuffer_FormatCustomExponential(number, integerDigits, decimalDigits);
    }
    else {
        NumberBuffer_FormatFixedPoint(number, decimalDigits);
    }

    // Padd the number with leading integer zeros if required.
    PaddIntegerDigits(number, integerDigits);

    // Padd the number with trailing decimal zeros if required.
    PaddDecimalDigits(number, decimalDigits);
}

internal void NumberBuffer_FormatExponential(NumberBuffer *number, int precision)
{
    NumberBuffer_FormatCustomExponential(number, 1, precision);

    // Padd the number with trailing decimal zeros if required.
    PaddDecimalDigits(number, precision);
}

internal void NumberBuffer_FormatFixedPoint(NumberBuffer *number, int precision)
{
    assert(number != null);
    assert(precision >= 0);

    if (number->ValueType == NumberType_UInt) {
        NumberBuffer_FormatInteger(number, 0, 10, false);
    }
    else {
        NumberBuffer_FormatFloat(number, precision, false);
    }

    // Padd the number with trailing decimal zeros if required.
    PaddDecimalDigits(number, precision);
}

internal void NumberBuffer_FormatInteger(NumberBuffer *number, int minNumDigits, int base, bool uppercase)
{
    assert(number != null);
    assert(number->ValueType == NumberType_UInt);
    assert(minNumDigits >= 0);
    assert(base >= 2 && base <= 36);

    uintmax value = GetIntegerValue(number);
    uintmax ubase = (uintmax)base;
    uintmax last;

    // Fill the stringBuffer with the digits in reverse order.
    while (value) {
        last = value % ubase;
        value = value / ubase;

        int digit = (int)last;

        if (digit < 10) {
            digit = '0' + digit;
        }
        else if (uppercase) {
            digit = 'A' + digit - 10;
        }
        else {
            digit = 'a' + digit - 10;
        }

        // Add the digit to the string.
        number->Digits[number->DigitCount++] = (char)digit;
    }

    // Reverse the digits so that they are in normal order.
    ReverseDigits(number);

    // Set the number of integers and decimals.
    number->DecimalPlace = number->DigitCount;

    // Padd the number with leading integer zeros if required.
    PaddIntegerDigits(number, minNumDigits);
}

internal void NumberBuffer_FormatGeneral(NumberBuffer *number, int precision)
{
    assert(number != null);
    assert(precision >= 0);

    // If the precision specifier is zero, determine the default precision.
    if (precision == 0) {
        if (number->ValueType == NumberType_Single) {
            precision = float_Digits;
        }
        else if (number->ValueType == NumberType_Double) {
            precision = double_Digits;
        }
        else {
            precision = 99;
        }
    }

    int exponent = Exponent(number);

    // Determine whether to use exponential or fixed notation based on the exponent and precision specifier.
    if (exponent <= -5 || exponent > precision) {
        NumberBuffer_FormatExponential(number, int_Max(precision - 1, 0));
    }
    else {
        NumberBuffer_FormatFixedPoint(number, -exponent + precision);
    }

    StripTrailingDecimalZeros(number);
}

internal void NumberBuffer_ToString(const NumberBuffer *number, StringBuilder *sb)
{
    assert(number != null);
    assert(sb != null);

    int integerCount = NumberBuffer_GetIntegerCount(number);
    int decimalCount = NumberBuffer_GetDecimalCount(number);

    // Print sign.
    if (number->IsNegative) {
        StringBuilder_Append(sb, '-');
    }

    // Print integer digits.
    for (int i = 0; i < integerCount; i++) {
        StringBuilder_Append(sb, NumberBuffer_GetIntegerDigit(number, i));
    }

    // Print decimal point if there are decimal digits.
    if (decimalCount > 0) {
        StringBuilder_Append(sb, '.');
    }

    // Print decimal digits.
    for (int i = 0; i < decimalCount; i++) {
        StringBuilder_Append(sb, NumberBuffer_GetDecimalDigit(number, i));
    }

    // Print the exponent if needed.
    if (number->IsExponential) {
        StringBuilder_Append(sb, 'e');

        NumberBuffer exponentBuffer;
        NumberBuffer_FromIntMax(&exponentBuffer, number->Exponent);
        NumberBuffer_FormatInteger(&exponentBuffer, 0, 10, false);
        NumberBuffer_ToString(&exponentBuffer, sb);
    }
}

/**************************************/
/* Private function definitions       */
/**************************************/

/* Constructor */
/// <summary>
/// Initializes the given number with default values.
/// </summary>
private void NumberBuffer_Constructor(NumberBuffer *number)
{
    assert(number != null);

    number->Value.UIntValue = 0;
    number->ValueType = NumberType_UInt;

    number->IsNegative = false;
    number->IsExponential = false;
    number->Exponent = 0;
    number->DigitCount = 0;
    number->DecimalPlace = 0;
    number->LeadingIntegerZeros = 0;
    number->TrailingDecimalZeros = 0;
}

/* Formatting functions */
/// <summary>
/// Formats a floating-point number with the given number of decimal digits.
/// </summary>
private void NumberBuffer_FormatFloat(NumberBuffer *number,  int numDecimals, bool shiftIntegersBehindDecimalPoint)
{
    assert(number != null);
    assert(number->ValueType == NumberType_Single || number->ValueType == NumberType_Double);
    assert(numDecimals >= 0);

    // Get the floating-point value of the number as a double and find the number of significant digits in this value.
    int numSignificantDigits;
    int maxExponent;
    double value = GetFloatValue(number, &numSignificantDigits, &maxExponent);

    int exponent;

    // Convert all significant digits to integers and get the exponent.
    value = Normalize(value, numSignificantDigits, maxExponent, &exponent);

    int numDigits;

    // Find the number of significant digits needed.
    if (shiftIntegersBehindDecimalPoint) {
        // If all integers are shifted behind the decimal point, the total number of digits needed is equal to the
        // number of decimal digits.
        numDigits = numDecimals;
    }
    else {
        // Otherwise, the number of digits depends on the exponent.
        numDigits = exponent + numDecimals;
    }

    // Limit the number of digits to the number of significant digits.
    if (numDigits >= numSignificantDigits) {
        numDigits = numSignificantDigits;
    }

    // Scale value down to the right amount of significant digits.
    if (numDigits >= 0 && numDigits < numSignificantDigits) {
        value = Math_Round(value * Math_Pow(10.0, -numSignificantDigits + numDigits));

        // Account for the result of rounding if the digits start directly behind the last decimal.
        if (numDigits == 0 && value >= 1.0) {
            number->Digits[number->DigitCount++] = '1';
            exponent++;
        }
    }

    // Convert the digits to a string.
    if (numDigits > 0) {
        double digit;

        // Fill the stringBuffer with the digits in reverse order.
        for (int i = 0; i < numDigits; i++) {
            digit = Math_Mod(value, 10.0);
            value = value / 10.0;

            // Add the digit to the string.
            number->Digits[number->DigitCount++] = (char)('0' + (int)digit);
        }

        // Reverse the digits so that they are in normal order.
        ReverseDigits(number);
    }

    // Set the number of integers and decimals.
    if (shiftIntegersBehindDecimalPoint) {
        number->Exponent = exponent;
        number->DecimalPlace = 0;
    }
    else {
        number->Exponent = 0;
        number->DecimalPlace = exponent;
    }
}

/// <summary>
/// Formats a number in exponential notation with the given number of integer and decimal digits.
/// </summary>
private void NumberBuffer_FormatCustomExponential(NumberBuffer *number, int integerDigits, int precision)
{
    assert(number != null);
    assert(integerDigits >= 0);
    assert(precision >= 0);

    if (number->ValueType == NumberType_UInt) {
        NumberBuffer_FormatInteger(number, 0, 10, false);

        number->Exponent = number->DecimalPlace - integerDigits;
        number->DecimalPlace = integerDigits;
        number->IsExponential = true;

        RoundToPrecision(number, precision);
    }
    else {
        NumberBuffer_FormatFloat(number, integerDigits + precision, true);

        number->Exponent -= integerDigits;
        number->DecimalPlace += integerDigits;
        number->IsExponential = true;
    }
}

/* Misc functions */
/// <summary>
/// Returns the integer value as an unsigned integer.
/// </summary>
private uintmax GetIntegerValue(const NumberBuffer *number)
{
    assert(number != null);
    assert(number->ValueType == NumberType_UInt);

    return number->Value.UIntValue;
}

/// <summary>
/// Returns the floating-point value without sign as a double.
/// </summary>
private double GetFloatValue(const NumberBuffer *number, int *numSignificants, int *maxExponent)
{
    assert(number != null);
    assert(number->ValueType == NumberType_Single || number->ValueType == NumberType_Double);
    assert(numSignificants != null);
    assert(maxExponent != null);

    if (number->ValueType == NumberType_Single) {
        *numSignificants = float_Digits;
        *maxExponent = float_MaxBase10Exponent;

        return Math_Abs(number->Value.SingleValue);
    }
    else {
        *numSignificants = double_Digits;
        *maxExponent = double_MaxBase10Exponent;

        return Math_Abs(number->Value.DoubleValue);
    }
}

/// <summary>
/// Determines the exponent of the value of a number.
/// </summary>
private int Exponent(const NumberBuffer *number)
{
    assert(number != null);

    if (number->ValueType == NumberType_UInt) {
        return IntegerExponent(GetIntegerValue(number));
    }
    else {
        int tmp1, tmp2;
        return FloatExponent(GetFloatValue(number, &tmp1, &tmp2));
    }
}

/// <summary>
/// Determines the exponent of a floating-point value.
/// </summary>
private int FloatExponent(double x)
{
    if (x < 0.0) {
        x = -x;
    }

    if (x < double_Epsilon) {
        return 0;
    }

    return (int)Math_Floor(Math_Log10(x)) + 1;
}

/// <summary>
/// Determines the exponent of an integer number.
/// </summary>
private int IntegerExponent(uintmax x)
{
    int exponent = 0;

    while (x != 0) {
        x = x / 10;
        exponent++;
    }

    return exponent;
}

/// <summary>
/// Normalizes a floating-point value so that it has the given number of significant digits
/// and determines the exponent.
/// </summary>
private double Normalize(double x, int numSignificantDigits, int maxExponent, int *exponent)
{
    assert(exponent != null);
    assert(numSignificantDigits >= 0);
    assert(maxExponent >= 0);

    // Calculate the exponent and negate it to scale it the number to normal range.
    int exp = FloatExponent(x);

    *exponent = exp;

    // If the exponent is too large to be represented we must scale in two steps.
    while (-exp + numSignificantDigits > maxExponent) {
        x = x * Math_Pow(10.0, maxExponent);

        exp += maxExponent;
    }

    return Math_Round(x * Math_Pow(10.0, -exp + numSignificantDigits));
}

/// <summary>
/// Determines whether all of the number's decimal digits are zero.
/// </summary>
private bool HasAllZeroDigits(const NumberBuffer *number)
{
    assert(number != null);

    for (int i = 0; i < number->DigitCount; i++) {
        if (number->Digits[i] != '0') {
            return false;
        }
    }

    return true;
}

/// <summary>
/// Reverses the digits of the given number.
/// </summary>
private void ReverseDigits(NumberBuffer *number)
{
    assert(number != null);

    int count = number->DigitCount;
    int halfCount = count / 2;

    for (int i = 0; i < halfCount; i++) {
        char tmp = number->Digits[i];
        number->Digits[i] = number->Digits[count - 1 - i];
        number->Digits[count - 1 - i] = tmp;
    }
}

/// <summary>
/// Rounds the given number to the given number of decimal digits.
/// </summary>
private void RoundToPrecision(NumberBuffer *number, int precision)
{
    assert(number != null);
    assert(precision >= 0);

    StripTrailingDecimalZeros(number);

    int lastDecimal = number->DigitCount - 1;
    int lastDecimalAfterRounding = number->DecimalPlace + precision;
    int i;

    int carry = 0;

    // Compute the carry from the decimals that will be rounded off.
    for (i = lastDecimal; i >= lastDecimalAfterRounding; i--) {
        if (number->Digits[i] == '5' || number->Digits[i] + carry > '5') {
            carry = 1;
        }
        else {
            carry = 0;
        }
    }

    // Add the resulting carry to the number.
    while (carry && i >= 0) {
        if (number->Digits[i] == '9') {
            number->Digits[i] = '0';

            carry = 1;
        }
        else {
            number->Digits[i] = (char)(number->Digits[i] + 1);

            carry = 0;
        }

        i--;
    }

    // If the addition results in a carry out, shift the number right to prepend a 1.
    if (carry && i < 0) {
        Memory_Copy(&number->Digits[0], &number->Digits[1], (uintsize)(number->DigitCount - 1));

        number->Digits[0] = '1';

        if (number->IsExponential) {
            number->Exponent++;
        }
        else {
            number->DecimalPlace++;
        }
    }

    int decimalDigits = NumberBuffer_GetDecimalCount(number);

    // Adjust the number of decimals.
    if (decimalDigits > precision) {
        number->DigitCount -= decimalDigits - precision;
    }
    else if (decimalDigits < precision) {
        PaddDecimalDigits(number, precision);
    }
}

/// <summary>
/// Padds the given number to the given number of integer digits.
/// </summary>
private void PaddIntegerDigits(NumberBuffer *number, int count)
{
    assert(number != null);
    assert(count >= 0);

    number->LeadingIntegerZeros = 0;
    number->LeadingIntegerZeros = int_Max(0, count - NumberBuffer_GetIntegerCount(number));
}

/// <summary>
/// Padds the given number to the given number of decimal digits.
/// </summary>
private void PaddDecimalDigits(NumberBuffer *number, int count)
{
    assert(number != null);
    assert(count >= 0);

    number->TrailingDecimalZeros = 0;
    number->TrailingDecimalZeros = int_Max(0, count - NumberBuffer_GetDecimalCount(number));
}

/// <summary>
/// Stripts the given number of all decimal digits.
/// </summary>
private void StripTrailingDecimalZeros(NumberBuffer *number)
{
    assert(number != null);

    int firstDecimal = int_Max(number->DecimalPlace, 0);
    int lastDecimal = number->DigitCount - 1;

    int trailingZeros = 0;

    // Iterate backward through the decimals and count the zeros.
    for (int i = lastDecimal; i >= firstDecimal; i--) {
        if (number->Digits[i] == '0') {
            trailingZeros++;
        }
        else {
            break;
        }
    }

    number->TrailingDecimalZeros = 0;
    number->DigitCount -= trailingZeros;
}
