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

#include "CFlat/Language/Double.h"
#include "CFlat/Language/Integer.h"

#include "CFlat/Macros.h"

/* Macros */
#define MAX_INTEGER_BITS (sizeof(uintmax) * 8)
#define MAX_INTEGER_DIGITS (1 + MAX_INTEGER_BITS / 3)
#define MAX_DOUBLE_DIGITS (DOUBLE_DIGITS)
#define MAX_DIGITS MAX(MAX_INTEGER_DIGITS, MAX_DOUBLE_DIGITS)

namespace CFlat {
    /* Forward declarations */
    class StringBuilder;

    /* Types */
    union NumberValue {
        uintmax UIntValue;
        float SingleValue;
        double DoubleValue;
    };

    enum NumberType {
        NumberType_UInt,
        NumberType_Single,
        NumberType_Double
    };

    class NumberBuffer {
    private:
        NumberValue _value;
        NumberType _valueType;

        bool _isNegative;
        bool _isExponential;
        int _exponent;
        int _decimalPlace;

        int _leadingIntegerZeros;
        int _trailingDecimalZeros;

        int _digitCount;
        char _digits[MAX_DIGITS];

        NumberBuffer();

        void FormatFloat(int precision, bool shiftIntegersBehindDecimalPoint);
        void FormatCustomExponential(int integerDigits, int precision);

        uintmax GetIntegerValue() const;
        double GetFloatValue(int &numSignificants, int &maxExponent) const;
        int Exponent() const;
        static int FloatExponent(double x);
        static int IntegerExponent(uintmax x);
        double Normalize(double x, int numSignificantDigits, int maxExponent, int *exponent);
        bool HasAllZeroDigits() const;
        void ReverseDigits();
        void RoundToPrecision(int precision);
        void PaddIntegerDigits(int minNumDigits);
        void PaddDecimalDigits(int minNumDigits);
        void StripTrailingDecimalZeros();

    public:
        /// <summary>
        /// Initializes the given <see cref="NumberBuffer"/> with the given value.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="value">The value to initialize the <see cref="NumberBuffer"/> with.</param>
        static NumberBuffer FromIntMax(intmax value);

        /// <summary>
        /// Initializes the given <see cref="NumberBuffer"/> with the given value.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="value">The value to initialize the <see cref="NumberBuffer"/> with.</param>
        static NumberBuffer FromUIntMax(uintmax value);

        /// <summary>
        /// Initializes the given <see cref="NumberBuffer"/> with the given value.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="value">The value to initialize the <see cref="NumberBuffer"/> with.</param>
        static NumberBuffer FromSingle(float value);

        /// <summary>
        /// Initializes the given <see cref="NumberBuffer"/> with the given value.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="value">The value to initialize the <see cref="NumberBuffer"/> with.</param>
        static NumberBuffer FromDouble(double value);

        /// <summary>
        /// Formats the value of the given <see cref="NumberBuffer"/> as an integer.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="minNumDigits">The minimum number of digits.</param>
        /// <param name="base">The base used to present the value as a string, between 2 and 36.</param>
        /// <param name="upperCase">Whether or not digits with letter values are printed uppercase.</param>
        void FormatInteger(int minNumDigits, int base, bool uppercase);

        /// <summary>
        /// Formats the value of the given <see cref="NumberBuffer"/> as a fixed-point number.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="precision">The number of decimal digits.</param>
        void FormatFixedPoint(int precision);

        /// <summary>
        /// Formats the value of the given <see cref="NumberBuffer"/> as a general number.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="precision">The number of digits.</param>
        void FormatGeneral(int precision);

        /// <summary>
        /// Formats the value of the given <see cref="NumberBuffer"/> as an exponential number.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="precision">The number of decimal digits.</param>
        void FormatExponential(int precision);

        /// <summary>
        /// Formats the value of the given <see cref="NumberBuffer"/> as a custom number.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="integerDigits">The number of integer digits.</param>
        /// <param name="decimalDigits">The number of decimal digits.</param>
        /// <param name="exponentialNotation">Whether or not to use exponential format.</param>
        void FormatCustomNumber(
            int integerDigits,
            int decimalDigits,
            bool exponentialNotation);

        /// <summary>
        /// Converts the given <see cref="NumberBuffer"/> to a string representation.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        void ToString(StringBuilder &sb) const;

        /// <summary>
        /// Gets the exponent of the given <see cref="NumberBuffer"/>.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <returns>The exponent of <paramref name="number"/>.</returns>
        int GetExponent() const;

        /// <summary>
        /// Gets the number of integer digits in the given <see cref="NumberBuffer"/>.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <returns>The number of integer digits in <paramref name="number"/>.</returns>
        int GetIntegerCount() const;

        /// <summary>
        /// Gets the number of decimal digits in the given <see cref="NumberBuffer"/>.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <returns>The number of decimal digits in <paramref name="number"/>.</returns>
        int GetDecimalCount() const;

        /// <summary>
        /// Gets the integer digit at the given index of the given <see cref="NumberBuffer"/>.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="index">The index of the integer digit for which to retrieve the value.</param>
        /// <returns>The integer digit at <paramref name="index"/>.</returns>
        char GetIntegerDigit(int index) const;

        /// <summary>
        /// Gets the decimal digit at the given index of the given <see cref="NumberBuffer"/>.
        /// </summary>
        /// <param name="number">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <param name="index">The index of the decimal digit for which to retrieve the value.</param>
        /// <returns>The decimal digit at <paramref name="index"/>.</returns>
        char GetDecimalDigit(int index) const;

        /// <summary>
        /// Determines whether the given <see cref="NumberBuffer"/> is negative.
        /// </summary>
        /// <param name="value">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <returns><see cref="true"/> if <paramref name="value"/> is negative; otherwise, <see cref="false"/>.</returns>
        bool IsNegative() const;

        /// <summary>
        /// Determines whether the given <see cref="NumberBuffer"/> represents zero after formatting the number.
        /// </summary>
        /// <param name="value">Pointer to a <see cref="NumberBuffer"/>.</param>
        /// <returns><see cref="true"/> if <paramref name="value"/> represents zero; otherwise, <see cref="false"/>.</returns>
        bool IsZero() const;
    };
}

#undef MAX_INTEGER_BITS
#undef MAX_INTEGER_DIGITS
#undef MAX_DOUBLE_DIGITS
#undef MAX_DIGITS

#endif
