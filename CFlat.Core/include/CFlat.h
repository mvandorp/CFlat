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

//! @file CFlat.h

#ifndef CFLAT_CORE_CFLAT_H
#define CFLAT_CORE_CFLAT_H

#include "CFlat/Language/Assert.h"
#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Char.h"
#include "CFlat/Language/Constants.h"
#include "CFlat/Language/Double.h"
#include "CFlat/Language/Float.h"
#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Pointers.h"
#include "CFlat/Language/VarArgs.h"

//#include "CFlat/Language/Assert.h"
//#include "CFlat/Language/Bool.h"
//#include "CFlat/Language/Char.h"
//#include "CFlat/Language/Constants.h"
//#include "CFlat/Language/Double.h"
//#include "CFlat/Language/Exceptions.h"
//#include "CFlat/Language/Float.h"
//#include "CFlat/Language/Functions.h"
//#include "CFlat/Language/Integer.h"
//#include "CFlat/Language/Keywords.h"
//#include "CFlat/Language/Macros.h"
//#include "CFlat/Language/VarArgs.h"

#include "CFlat/String.h"

namespace CFlat {
    /* Functions */
    #ifdef CFLAT_INTPTR
    class IntPtr {
    public:
        IntPtr() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="intptr"/>.
        /// </summary>
        static const intptr MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="intptr"/>.
        /// </summary>
        static const intptr MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static intptr CheckedAddition(intptr x, intptr y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static intptr CheckedSubtraction(intptr x, intptr y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(intptr value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(intptr value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, intptr value, const String *format);
    };
    #endif

    #ifdef CFLAT_UINTPTR
    class UIntPtr {
    public:
        UIntPtr() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="uintptr"/>.
        /// </summary>
        /// <remarks>The value of this constant is 0.</remarks>
        static const uintptr MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="uintptr"/>.
        /// </summary>
        static const uintptr MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static uintptr CheckedAddition(uintptr x, uintptr y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static uintptr CheckedSubtraction(uintptr x, uintptr y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(uintptr value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(uintptr value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, uintptr value, const String *format);
    };
    #endif

    class UIntSize {
    public:
        UIntSize() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="uintsize"/>.
        /// </summary>
        static const uintsize MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="uintsize"/>.
        /// </summary>
        static const uintsize MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static uintsize CheckedAddition(uintsize x, uintsize y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static uintsize CheckedSubtraction(uintsize x, uintsize y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static uintsize CheckedMultiplication(uintsize x, uintsize y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static uintsize CheckedDivision(uintsize x, uintsize y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static uintsize Max(uintsize x, uintsize y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static uintsize Min(uintsize x, uintsize y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(uintsize value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(uintsize value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, uintsize value, const String *format);
    };

    class IntFSize {
    public:
        IntFSize() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="intfsize"/>.
        /// </summary>
        static const intfsize MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="intfsize"/>.
        /// </summary>
        static const intfsize MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static intfsize CheckedAddition(intfsize x, intfsize y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static intfsize CheckedSubtraction(intfsize x, intfsize y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static intfsize CheckedMultiplication(intfsize x, intfsize y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static intfsize CheckedDivision(intfsize x, intfsize y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static intfsize Max(intfsize x, intfsize y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static intfsize Min(intfsize x, intfsize y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(intfsize value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(intfsize value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, intfsize value, const String *format);
    };

    class SByte {
    public:
        SByte() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="sbyte"/>.
        /// </summary>
        static const sbyte MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="sbyte"/>.
        /// </summary>
        static const sbyte MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static sbyte CheckedAddition(sbyte x, sbyte y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static sbyte CheckedSubtraction(sbyte x, sbyte y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static sbyte CheckedMultiplication(sbyte x, sbyte y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static sbyte CheckedDivision(sbyte x, sbyte y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static sbyte Max(sbyte x, sbyte y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static sbyte Min(sbyte x, sbyte y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(sbyte value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(sbyte value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, sbyte value, const String *format);
    };

    class Byte {
    public:
        Byte() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="byte"/>.
        /// </summary>
        /// <remarks>The value of this constant is 0.</remarks>
        static const byte MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="byte"/>.
        /// </summary>
        static const byte MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static byte CheckedAddition(byte x, byte y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static byte CheckedSubtraction(byte x, byte y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static byte CheckedMultiplication(byte x, byte y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static byte CheckedDivision(byte x, byte y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static byte Max(byte x, byte y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static byte Min(byte x, byte y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(byte value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(byte value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, byte value, const String *format);
    };

    class Short {
    public:
        Short() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="short"/>.
        /// </summary>
        static const short MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="short"/>.
        /// </summary>
        static const short MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static short CheckedAddition(short x, short y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static short CheckedSubtraction(short x, short y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static short CheckedMultiplication(short x, short y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static short CheckedDivision(short x, short y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static short Max(short x, short y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static short Min(short x, short y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(short value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(short value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, short value, const String *format);
    };

    class UShort {
    public:
        UShort() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="ushort"/>.
        /// </summary>
        /// <remarks>The value of this constant is 0.</remarks>
        static const ushort MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="ushort"/>.
        /// </summary>
        static const ushort MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static ushort CheckedAddition(ushort x, ushort y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static ushort CheckedSubtraction(ushort x, ushort y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static ushort CheckedMultiplication(ushort x, ushort y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static ushort CheckedDivision(ushort x, ushort y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static ushort Max(ushort x, ushort y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static ushort Min(ushort x, ushort y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(ushort value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(ushort value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, ushort value, const String *format);
    };

    class Int {
    public:
        Int() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="int"/>.
        /// </summary>
        static const int MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="int"/>.
        /// </summary>
        static const int MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static int CheckedAddition(int x, int y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static int CheckedSubtraction(int x, int y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static int CheckedMultiplication(int x, int y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static int CheckedDivision(int x, int y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static int Max(int x, int y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static int Min(int x, int y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(int value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(int value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, int value, const String *format);
    };

    class UInt {
    public:
        UInt() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="uint"/>.
        /// </summary>
        /// <remarks>The value of this constant is 0.</remarks>
        static const uint MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="uint"/>.
        /// </summary>
        static const uint MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static uint CheckedAddition(uint x, uint y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static uint CheckedSubtraction(uint x, uint y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static uint CheckedMultiplication(uint x, uint y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static uint CheckedDivision(uint x, uint y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static uint Max(uint x, uint y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static uint Min(uint x, uint y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(uint value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(uint value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, uint value, const String *format);
    };

    class Long {
    public:
        Long() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="long"/>.
        /// </summary>
        static const long MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="long"/>.
        /// </summary>
        static const long MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static long CheckedAddition(long x, long y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static long CheckedSubtraction(long x, long y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static long CheckedMultiplication(long x, long y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static long CheckedDivision(long x, long y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static long Max(long x, long y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static long Min(long x, long y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(long value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(long value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, long value, const String *format);
    };

    class ULong {
    public:
        ULong() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="ulong"/>.
        /// </summary>
        /// <remarks>The value of this constant is 0.</remarks>
        static const ulong MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="ulong"/>.
        /// </summary>
        static const ulong MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static ulong CheckedAddition(ulong x, ulong y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static ulong CheckedSubtraction(ulong x, ulong y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static ulong CheckedMultiplication(ulong x, ulong y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static ulong CheckedDivision(ulong x, ulong y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static ulong Max(ulong x, ulong y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static ulong Min(ulong x, ulong y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(ulong value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(ulong value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, ulong value, const String *format);
    };

    class IntMax {
    public:
        IntMax() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="intmax"/>.
        /// </summary>
        static const intmax MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="intmax"/>.
        /// </summary>
        static const intmax MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static intmax CheckedAddition(intmax x, intmax y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static intmax CheckedSubtraction(intmax x, intmax y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static intmax CheckedMultiplication(intmax x, intmax y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static intmax CheckedDivision(intmax x, intmax y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static intmax Max(intmax x, intmax y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static intmax Min(intmax x, intmax y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(intmax value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(intmax value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, intmax value, const String *format);
    };

    class UIntMax {
    public:
        UIntMax() = delete;

        /// <summary>
        /// Represents the smallest possible value of <see cref="uintmax"/>.
        /// </summary>
        /// <remarks>The value of this constant is 0.</remarks>
        static const uintmax MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="uintmax"/>.
        /// </summary>
        static const uintmax MaxValue;

        /// <summary>
        /// Returns the sum of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The sum of two numbers.</returns>
        /// <exception cref="::OverflowException">The addition results in an overflow.</exception>
        static uintmax CheckedAddition(uintmax x, uintmax y);

        /// <summary>
        /// Returns the difference between two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The difference between two numbers.</returns>
        /// <exception cref="::OverflowException">The subtraction results in an overflow.</exception>
        static uintmax CheckedSubtraction(uintmax x, uintmax y);

        /// <summary>
        /// Returns the product of two numbers and checks if overflow occurs.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The product of two numbers.</returns>
        /// <exception cref="::OverflowException">The multiplication results in an overflow.</exception>
        static uintmax CheckedMultiplication(uintmax x, uintmax y);

        /// <summary>
        /// Returns the quotient of two numbers and checks for division by zero.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The quotient of two numbers.</returns>
        /// <exception cref="::DivideByZeroException"><paramref name="y"/> is zero.</exception>
        static uintmax CheckedDivision(uintmax x, uintmax y);

        /// <summary>
        /// Returns the larger of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The larger of two numbers.</returns>
        static uintmax Max(uintmax x, uintmax y);

        /// <summary>
        /// Returns the smaller of two numbers.
        /// </summary>
        /// <param name="x">The first number.</param>
        /// <param name="y">The second number.</param>
        /// <returns>The smaller of two numbers.</returns>
        static uintmax Min(uintmax x, uintmax y);

        /// <summary>
        /// Converts the given number to a string representation.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <returns>The string representation of the given number.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(uintmax value);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <returns>The string representation of the given number as specified by <paramref name="format"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(uintmax value, const String *format);

        /// <summary>
        /// Converts the given number to a string representation, using the specified format.
        /// </summary>
        /// <param name="sb">The <see cref="StringBuilder"/> onto which to append the resulting string.</param>
        /// <param name="value">The value to be converted to a string.</param>
        /// <param name="format">A standard or custom numeric format string.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="sb"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static void ToString(StringBuilder &sb, uintmax value, const String *format);
    };
}

#endif
