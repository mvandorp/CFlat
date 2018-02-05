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

using namespace CFlat;

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructor functions */
NumberBuffer NumberBuffer::FromIntMax(intmax value)
{
    NumberBuffer number = NumberBuffer::FromUIntMax(value < 0 ? (uintmax)-value : (uintmax)value);
    number._isNegative = value < 0;

    return number;
}

NumberBuffer NumberBuffer::FromUIntMax(uintmax value)
{
    NumberBuffer number = NumberBuffer();
    number._value.UIntValue = value;
    number._valueType = NumberType_UInt;
    number._isNegative = false;

    return number;
}

NumberBuffer NumberBuffer::FromSingle(float value)
{
    NumberBuffer number = NumberBuffer();
    number._value.SingleValue = value;
    number._valueType = NumberType_Single;
    number._isNegative = value < 0.0f;

    return number;
}

NumberBuffer NumberBuffer::FromDouble(double value)
{
    NumberBuffer number = NumberBuffer();
    number._value.DoubleValue = value;
    number._valueType = NumberType_Double;
    number._isNegative = value < 0.0;

    return number;
}

/* Digit functions */
int NumberBuffer::GetExponent() const
{
    return _exponent;
}

int NumberBuffer::GetIntegerCount() const
{
    return Int::Max(_decimalPlace, 0) + _leadingIntegerZeros;
}

int NumberBuffer::GetDecimalCount() const
{
    return Int::Max(_digitCount - _decimalPlace, 0) + _trailingDecimalZeros;
}

char NumberBuffer::GetIntegerDigit(int index) const
{
    assert(index < this->GetIntegerCount());

    int adjustedIndex = index - _leadingIntegerZeros;

    if (adjustedIndex < 0 || adjustedIndex >= _digitCount) {
        return '0';
    }

    return _digits[adjustedIndex];
}

char NumberBuffer::GetDecimalDigit(int index) const
{
    assert(index < this->GetDecimalCount());

    int adjustedIndex = index + _decimalPlace;

    if (adjustedIndex < 0 || adjustedIndex >= _digitCount) {
        return '0';
    }

    return _digits[adjustedIndex];
}

/* Flags functions */
bool NumberBuffer::IsNegative() const
{
    return _isNegative;
}

bool NumberBuffer::IsZero() const
{
    return _decimalPlace <= 0 && this->HasAllZeroDigits();
}

/* Formatting functions */
void NumberBuffer::FormatCustomNumber(
    int integerDigits,
    int decimalDigits,
    bool exponentialNotation)
{
    assert(integerDigits >= 0);
    assert(decimalDigits >= 0);

    if (exponentialNotation) {
        this->FormatCustomExponential(integerDigits, decimalDigits);
    }
    else {
        this->FormatFixedPoint(decimalDigits);
    }

    // Padd the number with leading integer zeros if required.
    this->PaddIntegerDigits(integerDigits);

    // Padd the number with trailing decimal zeros if required.
    this->PaddDecimalDigits(decimalDigits);
}

void NumberBuffer::FormatExponential(int precision)
{
    this->FormatCustomExponential(1, precision);

    // Padd the number with trailing decimal zeros if required.
    this->PaddDecimalDigits(precision);
}

void NumberBuffer::FormatFixedPoint(int precision)
{
    assert(precision >= 0);

    if (_valueType == NumberType_UInt) {
        this->FormatInteger(1, 10, false);
    }
    else {
        this->FormatFloat(precision, false);
    }

    // Padd the number with trailing decimal zeros if required.
    this->PaddDecimalDigits(precision);
}

void NumberBuffer::FormatInteger(int minNumDigits, int base, bool uppercase)
{
    assert(_valueType == NumberType_UInt);
    assert(minNumDigits >= 0);
    assert(base >= 2 && base <= 36);

    uintmax value = this->GetIntegerValue();
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
        _digits[_digitCount++] = (char)digit;
    }

    // Reverse the digits so that they are in normal order.
    this->ReverseDigits();

    // Set the number of integers and decimals.
    _decimalPlace = _digitCount;

    // Padd the number with leading integer zeros if required.
    this->PaddIntegerDigits(minNumDigits);
}

void NumberBuffer::FormatGeneral(int precision)
{
    assert(precision >= 0);

    // If the precision specifier is zero, determine the default precision.
    if (precision == 0) {
        if (_valueType == NumberType_Single) {
            precision = Float::Digits;
        }
        else if (_valueType == NumberType_Double) {
            precision = Double::Digits;
        }
        else {
            precision = 99;
        }
    }

    int exponent = this->Exponent();

    // Determine whether to use exponential or fixed notation based on the exponent and precision specifier.
    if (exponent <= -5 || exponent > precision) {
        this->FormatExponential(Int::Max(precision - 1, 0));
    }
    else {
        this->FormatFixedPoint(-exponent + precision);
    }

    this->StripTrailingDecimalZeros();
}

void NumberBuffer::ToString(StringBuilder &sb) const
{
    int integerCount = this->GetIntegerCount();
    int decimalCount = this->GetDecimalCount();

    // Print sign.
    if (_isNegative) {
        sb.Append('-');
    }

    // Print integer digits.
    for (int i = 0; i < integerCount; i++) {
        sb.Append(this->GetIntegerDigit(i));
    }

    // Print decimal point if there are decimal digits.
    if (decimalCount > 0) {
        sb.Append('.');
    }

    // Print decimal digits.
    for (int i = 0; i < decimalCount; i++) {
        sb.Append(this->GetDecimalDigit(i));
    }

    // Print the exponent if needed.
    if (_isExponential) {
        sb.Append('e');

        NumberBuffer exponentBuffer = NumberBuffer::FromIntMax(_exponent);
        exponentBuffer.FormatInteger(1, 10, false);
        exponentBuffer.ToString(sb);
    }
}

/**************************************/
/* Private function definitions       */
/**************************************/

/* Constructor */
/// <summary>
/// Initializes the given number with default values.
/// </summary>
NumberBuffer::NumberBuffer()
{
    _value.UIntValue = 0;
    _valueType = NumberType_UInt;

    _isNegative = false;
    _isExponential = false;
    _exponent = 0;
    _digitCount = 0;
    _decimalPlace = 0;
    _leadingIntegerZeros = 0;
    _trailingDecimalZeros = 0;
}

/* Formatting functions */
/// <summary>
/// Formats a floating-point number with the given number of decimal digits.
/// </summary>
void NumberBuffer::FormatFloat( int numDecimals, bool shiftIntegersBehindDecimalPoint)
{
    assert(_valueType == NumberType_Single || _valueType == NumberType_Double);
    assert(numDecimals >= 0);

    int exponent;
    int maxExponent;
    int numDigits;
    int numSignificantDigits;

    // Get the floating-point value of the number as a double and find the number of significant digits in this value.
    double value = this->GetFloatValue(numSignificantDigits, maxExponent);

    // Convert all significant digits to integers and get the exponent.
    value = Normalize(value, numSignificantDigits, maxExponent, &exponent);

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
        value = Math::Round(value * Math::Pow(10.0, -numSignificantDigits + numDigits));

        // Account for the result of rounding if the digits start directly behind the last decimal.
        if (numDigits == 0 && value >= 1.0) {
            _digits[_digitCount++] = '1';
            exponent++;
        }
    }

    // Convert the digits to a string.
    if (numDigits > 0) {
        double digit;

        // Fill the stringBuffer with the digits in reverse order.
        for (int i = 0; i < numDigits; i++) {
            digit = Math::Mod(value, 10.0);
            value = value / 10.0;

            // Add the digit to the string.
            _digits[_digitCount++] = (char)('0' + (int)digit);
        }

        // Reverse the digits so that they are in normal order.
        this->ReverseDigits();
    }

    // Set the number of integers and decimals.
    if (shiftIntegersBehindDecimalPoint) {
        _exponent = exponent;
        _decimalPlace = 0;
    }
    else {
        _exponent = 0;
        _decimalPlace = exponent;

        // Padd the number with leading integer zeros if required.
        this->PaddIntegerDigits(1);
    }
}

/// <summary>
/// Formats a number in exponential notation with the given number of integer and decimal digits.
/// </summary>
void NumberBuffer::FormatCustomExponential(int integerDigits, int precision)
{
    assert(integerDigits >= 0);
    assert(precision >= 0);

    if (_valueType == NumberType_UInt) {
        this->FormatInteger(1, 10, false);

        _exponent = _decimalPlace - integerDigits;
        _decimalPlace = integerDigits;
        _isExponential = true;

        this->RoundToPrecision(precision);
    }
    else {
        this->FormatFloat(integerDigits + precision, true);

        _exponent -= integerDigits;
        _decimalPlace += integerDigits;
        _isExponential = true;
    }
}

/* Misc functions */
/// <summary>
/// Returns the integer value as an unsigned integer.
/// </summary>
uintmax NumberBuffer::GetIntegerValue() const
{
    assert(_valueType == NumberType_UInt);

    return _value.UIntValue;
}

/// <summary>
/// Returns the floating-point value without sign as a double.
/// </summary>
double NumberBuffer::GetFloatValue(int &numSignificants, int &maxExponent) const
{
    assert(_valueType == NumberType_Single || _valueType == NumberType_Double);

    if (_valueType == NumberType_Single) {
        numSignificants = Float::Digits;
        maxExponent = Float::MaxBase10Exponent;

        return Math::Abs(_value.SingleValue);
    }
    else {
        numSignificants = Double::Digits;
        maxExponent = Double::MaxBase10Exponent;

        return Math::Abs(_value.DoubleValue);
    }
}

/// <summary>
/// Determines the exponent of the value of a number.
/// </summary>
int NumberBuffer::Exponent() const
{
    if (_valueType == NumberType_UInt) {
        return NumberBuffer::IntegerExponent(this->GetIntegerValue());
    }
    else {
        int tmp1, tmp2;
        return NumberBuffer::FloatExponent(this->GetFloatValue(tmp1, tmp2));
    }
}

/// <summary>
/// Determines the exponent of a floating-point value.
/// </summary>
int NumberBuffer::FloatExponent(double x)
{
    if (x < 0.0) {
        x = -x;
    }

    if (x < Double::MinPositiveValue) {
        return 0;
    }

    return (int)Math::Floor(Math::Log10(x)) + 1;
}

/// <summary>
/// Determines the exponent of an integer number.
/// </summary>
int NumberBuffer::IntegerExponent(uintmax x)
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
double NumberBuffer::Normalize(double x, int numSignificantDigits, int maxExponent, int *exponent)
{
    assert(exponent != nullptr);
    assert(numSignificantDigits >= 0);
    assert(maxExponent >= 0);

    // Calculate the exponent and negate it to scale it the number to normal range.
    int exp = -FloatExponent(x);

    *exponent = -exp;

    // If the exponent is too large to be represented we must scale in multiple steps.
    while (exp + numSignificantDigits > maxExponent) {
        x = x * Math::Pow(10.0, maxExponent);

        exp -= maxExponent;
    }

    return Math::Round(x * Math::Pow(10.0, exp + numSignificantDigits));
}

/// <summary>
/// Determines whether all of the number digits are zero.
/// </summary>
bool NumberBuffer::HasAllZeroDigits() const
{
    for (int i = 0; i < _digitCount; i++) {
        if (_digits[i] != '0') {
            return false;
        }
    }

    return true;
}

/// <summary>
/// Reverses the digits of the given number.
/// </summary>
void NumberBuffer::ReverseDigits()
{
    const int count = _digitCount;

    for (int i = 0; i < count / 2; i++) {
        char tmp = _digits[i];
        _digits[i] = _digits[count - 1 - i];
        _digits[count - 1 - i] = tmp;
    }
}

/// <summary>
/// Rounds the given number to the given number of decimal digits.
/// </summary>
void NumberBuffer::RoundToPrecision(int precision)
{
    assert(precision >= 0);

    this->StripTrailingDecimalZeros();

    int lastDecimal = _digitCount - 1;
    int lastDecimalAfterRounding = _decimalPlace + precision;
    int i;

    int carry = 0;

    // Compute the carry from the decimals that will be rounded off.
    for (i = lastDecimal; i >= lastDecimalAfterRounding; i--) {
        if (_digits[i] == '5' || _digits[i] + carry > '5') {
            carry = 1;
        }
        else {
            carry = 0;
        }
    }

    // Add the resulting carry to the number.
    while (carry && i >= 0) {
        if (_digits[i] == '9') {
            _digits[i] = '0';

            carry = 1;
        }
        else {
            _digits[i] = (char)(_digits[i] + 1);

            carry = 0;
        }

        i--;
    }

    // If the addition results in a carry out, shift the number right to prepend a 1.
    if (carry && i < 0) {
        Memory::Copy<char>(&_digits[0], &_digits[1], (uintsize)(_digitCount - 1));

        _digits[0] = '1';

        if (_isExponential) {
            _exponent++;
        }
        else {
            _decimalPlace++;
        }
    }

    int decimalDigits = this->GetDecimalCount();

    // Adjust the number of decimals.
    if (decimalDigits > precision) {
        _digitCount -= decimalDigits - precision;
    }
    else if (decimalDigits < precision) {
        this->PaddDecimalDigits(precision);
    }
}

/// <summary>
/// Padds the given number to the given number of integer digits.
/// </summary>
void NumberBuffer::PaddIntegerDigits(int count)
{
    assert(count >= 0);

    _leadingIntegerZeros = 0;
    _leadingIntegerZeros = Int::Max(0, count - this->GetIntegerCount());
}

/// <summary>
/// Padds the given number to the given number of decimal digits.
/// </summary>
void NumberBuffer::PaddDecimalDigits(int count)
{
    assert(count >= 0);

    _trailingDecimalZeros = 0;
    _trailingDecimalZeros = Int::Max(0, count - this->GetDecimalCount());
}

/// <summary>
/// Stripts the given number of all decimal digits.
/// </summary>
void NumberBuffer::StripTrailingDecimalZeros()
{
    int firstDecimal = Int::Max(_decimalPlace, 0);
    int lastDecimal = _digitCount - 1;

    int trailingZeros = 0;

    // Iterate backward through the decimals and count the zeros.
    for (int i = lastDecimal; i >= firstDecimal; i--) {
        if (_digits[i] == '0') {
            trailingZeros++;
        }
        else {
            break;
        }
    }

    _trailingDecimalZeros = 0;
    _digitCount -= trailingZeros;
}
