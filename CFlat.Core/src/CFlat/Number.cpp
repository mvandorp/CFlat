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

#include "CFlat/Number.h"
#include "CFlat/Number.NumberBuffer.h"

#include "CFlat.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"

#include "CFlat/IO/StringReader.h"

#include <utility>

using namespace CFlat;

/**************************************/
/* Private functions                  */
/**************************************/

static String FormatNumber(NumberBuffer &value, const String *format);
static void FormatNumberBuffered(StringBuilder &sb, NumberBuffer &value, const String *format);
static void FormatStandardNumber(
    StringBuilder &sb,
    NumberBuffer &value,
    char formatSpecifier,
    int precisionSpecifier);
static void FormatCustomNumber(StringBuilder &sb, NumberBuffer &value, StringReader &reader);
static bool ProcessStandardFormatString(StringReader &reader, char *formatSpecifier, int *precisionSpecifier);
static void ProcessCustomFormatString(
    StringReader &reader,
    NumberBuffer &value,
    int *integerDigits,
    int *decimalDigits,
    int *exponentDigits,
    bool *printSign);
static bool SkipFormatSection(StringReader &reader);
static void ParseFormatSection(
    StringReader &reader,
    int *integerDigits,
    int *decimalDigits,
    int *exponentDigits);
static void ReadString(StringBuilder &sb, StringReader &reader);
static void SkipString(StringReader &reader, uintsize *offset);
static void ReadEscapeSequence(StringBuilder &sb, StringReader &reader);
static void SkipEscapeSequence(StringReader &reader, uintsize *offset);
static bool IsEscapedCharacter(int ch);
static bool IsExponent(StringReader &reader, uintsize offset);
static void SkipExponent(StringReader &reader, uintsize *offset, int *exponentDigits);
static void PrintExponent(StringBuilder &sb, StringReader &reader, int exponent);
static void PrintDecimalSeparator(StringBuilder &sb, uintsize *decimalSeparatorIndex);
static void PrintLeadingZeros(StringBuilder &sb, int *numLeadingZeros);

/**************************************/
/* Internal function definitions      */
/**************************************/

String Number::Format(intmax value, const String *format)
{
    NumberBuffer number = NumberBuffer::FromIntMax(value);

    return FormatNumber(number, format);
}

String Number::Format(uintmax value, const String *format)
{
    NumberBuffer number = NumberBuffer::FromUIntMax(value);

    return FormatNumber(number, format);
}

String Number::Format(float value, const String *format)
{
    NumberBuffer number = NumberBuffer::FromSingle(value);

    return FormatNumber(number, format);
}

String Number::Format(double value, const String *format)
{
    NumberBuffer number = NumberBuffer::FromDouble(value);

    return FormatNumber(number, format);
}

void Number::Format(StringBuilder &sb, intmax value, const String *format)
{
    NumberBuffer number = NumberBuffer::FromIntMax(value);

    FormatNumberBuffered(sb, number, format);
}

void Number::Format(StringBuilder &sb, uintmax value, const String *format)
{
    NumberBuffer number = NumberBuffer::FromUIntMax(value);

    FormatNumberBuffered(sb, number, format);
}

void Number::Format(StringBuilder &sb, float value, const String *format)
{
    NumberBuffer number = NumberBuffer::FromSingle(value);

    FormatNumberBuffered(sb, number, format);
}

void Number::Format(StringBuilder &sb, double value, const String *format)
{
    NumberBuffer number = NumberBuffer::FromDouble(value);

    FormatNumberBuffered(sb, number, format);
}

bool Number::IsNonDecimalFormat(const String *format)
{
    if (format == nullptr) {
        return false;
    }

    StringReader reader = StringReader(*format);

    char formatSpecifier;
    int precisionSpecifier;
    bool isNonDecimalFormat = false;

    if (ProcessStandardFormatString(reader, &formatSpecifier, &precisionSpecifier)) {
        if (formatSpecifier == 'b' || formatSpecifier == 'B' || formatSpecifier == 'x' || formatSpecifier == 'X') {
            isNonDecimalFormat = true;
        }
    }

    return isNonDecimalFormat;
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Formats a number according to the given format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static String FormatNumber(NumberBuffer &value, const String *format)
{
    StringBuilder sb = StringBuilder();
    FormatNumberBuffered(sb, value, format);

    return StringBuilder::ToString(std::move(sb));
}

/// <summary>
/// Formats a number according to the given format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void FormatNumberBuffered(StringBuilder &sb, NumberBuffer &value, const String *format)
{
    static String formatBuffer = String::Wrap("G");

    if (format == nullptr) {
        format = &formatBuffer;
    }

    StringReader reader = StringReader(*format);

    char formatSpecifier;
    int precisionSpecifier;

    if (ProcessStandardFormatString(reader, &formatSpecifier, &precisionSpecifier)) {
        FormatStandardNumber(sb, value, formatSpecifier, precisionSpecifier);
    }
    else {
        FormatCustomNumber(sb, value, reader);
    }
}

/// <summary>
/// Formats a number according to a standard format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void FormatStandardNumber(StringBuilder &sb, NumberBuffer &value, char formatSpecifier, int precisionSpecifier)
{
    assert(precisionSpecifier >= 0);

    if (formatSpecifier == 'b' || formatSpecifier == 'B') {
        value.FormatInteger(precisionSpecifier, 2, false);
    }
    else if (formatSpecifier == 'd' || formatSpecifier == 'D') {
        value.FormatInteger(precisionSpecifier, 10, false);
    }
    else if (formatSpecifier == 'x') {
        value.FormatInteger(precisionSpecifier, 16, false);
    }
    else if (formatSpecifier == 'X') {
        value.FormatInteger(precisionSpecifier, 16, true);
    }
    else if (formatSpecifier == 'e' || formatSpecifier == 'E') {
        value.FormatExponential(precisionSpecifier);
    }
    else if (formatSpecifier == 'f' || formatSpecifier == 'F') {
        value.FormatFixedPoint(precisionSpecifier);
    }
    else if (formatSpecifier == 'g' || formatSpecifier == 'G') {
        value.FormatGeneral(precisionSpecifier);
    }
    else {
        // Invalid format specifier.
        assert(false);
    }

    value.ToString(sb);
}

/// <summary>
/// Formats a number according to a custom format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void FormatCustomNumber(StringBuilder &sb, NumberBuffer &value, StringReader &reader)
{
    int formatIntegerDigits;
    int formatDecimalDigits;
    int formatExponentDigits;
    bool printSign;

    ProcessCustomFormatString(
        reader,
        value,
        &formatIntegerDigits,
        &formatDecimalDigits,
        &formatExponentDigits,
        &printSign);

    if (printSign && value.IsNegative()) {
        sb.Append('-');
    }

    int valueIntegerDigits = value.GetIntegerCount();
    int valueDecimalDigits = value.GetDecimalCount();

    int integerIndex = 0;
    int decimalIndex = 0;
    int leadingDecimalZeros = 0;

    bool printedInteger = false;
    bool integerPart = true;
    bool printedExponent = false;
    uintsize decimalSeparatorIndex = InvalidIndex;

    while (true) {
        int ch = reader.Peek();

        switch (ch) {
            case -1:
            case ';':
                return;
            case '\'':
            case '"':
                ReadString(sb, reader);
                break;
            case '\\':
                ReadEscapeSequence(sb, reader);
                break;
            case 'e':
            case 'E':
                if (!printedExponent && IsExponent(reader, 0)) {
                    PrintExponent(sb, reader, value.GetExponent());

                    printedExponent = true;
                }
                else {
                    sb.Append((char)reader.Read());
                }
                break;
            case '0':
            case '#':
                reader.Read();

                if (integerPart) {
                    // We're processing the integer part.

                    // While there are integer digits to print, print them.
                    while (valueIntegerDigits >= formatIntegerDigits) {
                        char digit = value.GetIntegerDigit(integerIndex++);

                        if (ch == '#' && digit == '0' && !printedInteger) {
                            // If we have not printed an integer yet, and the digit is zero and should not be printed,
                            // then do not print it.
                        }
                        else {
                            // Otherwise print the integer.
                            sb.Append(digit);
                            printedInteger = true;
                        }

                        valueIntegerDigits--;
                    }

                    formatIntegerDigits--;
                }
                else {
                    // We're processing the decimal part.

                    char digit = value.GetDecimalDigit(decimalIndex);

                    if (ch == '#' && digit == '0') {
                        // If the digit is zero and should not be printed, increment leadingDecimalZeros and break.
                        decimalIndex++;
                        leadingDecimalZeros++;
                        break;
                    }

                    // Print a decimal seperator and any leading zeros if required.
                    PrintDecimalSeparator(sb, &decimalSeparatorIndex);
                    PrintLeadingZeros(sb, &leadingDecimalZeros);

                    if (decimalIndex < valueDecimalDigits) {
                        // If there is a decimal digit left to print, print it.
                        sb.Append(digit);
                        decimalIndex++;
                    }
                    else if (ch == '0') {
                        // Otherwise, print a zero if required.
                        sb.Append('0');
                    }
                }

                break;
            case '.':
                reader.Read();

                if (integerPart) {
                    decimalSeparatorIndex = sb.GetLength();
                    integerPart = false;
                }

                break;
            default:
                sb.Append((char)reader.Read());
                break;
        }
    }
}

/// <summary>
/// Processes a format string and returns whether or not it is a standard format string.
/// If the format is a standard format the format specifier and precision specifier are determined as well.
/// </summary>
static bool ProcessStandardFormatString(StringReader &reader, char *formatSpecifier, int *precisionSpecifier)
{
    assert(formatSpecifier != nullptr);
    assert(precisionSpecifier != nullptr);

    int format = reader.Peek();
    int precision1 = reader.Peek(1);
    int precision2 = reader.Peek(2);
    int end = reader.Peek(3);

    int ch = Char::ToLower(format);

    // If the format is more than three characters long it cannot be a valid standard format string.
    if (end != -1) {
        return false;
    }

    // Check if the format specifier is valid.
    if (ch != 'b' && ch != 'd' && ch != 'e' && ch != 'f' && ch != 'g' && ch != 'x') {
        return false;
    }

    // Verify that the precision specifier is either valid or absent.
    if (!Char::IsDigit(precision1) && precision1 != -1) {
        return false;
    }

    // Verify that the precision specifier is either valid or absent.
    if (!Char::IsDigit(precision2) && precision2 != -1) {
        return false;
    }

    int precision = 0;

    // Parse the precision specifier.
    if (precision1 != -1) {
        precision = precision1 - '0';
    }

    if (precision2 != -1) {
        precision = precision * 10 + precision2 - '0';
    }

    *formatSpecifier = (char)format;
    *precisionSpecifier = precision;

    return true;
}

/// <summary>
/// Processes a custom format string and determines the properties.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void ProcessCustomFormatString(
    StringReader &reader,
    NumberBuffer &value,
    int *integerDigits,
    int *decimalDigits,
    int *exponentDigits,
    bool *printSign)
{
    assert(integerDigits != nullptr);
    assert(decimalDigits != nullptr);
    assert(exponentDigits != nullptr);
    assert(printSign != nullptr);

    // Keeps track of whether the format string contains multiple sections in order to avoid trying to skip to a third
    // section when it does not exist.
    bool formatContainsMultipleSections = true;

    // If the number is negative, try skipping to the next section of the format string which contains the format for
    // negative values.
    if (value.IsNegative()) {
        formatContainsMultipleSections = SkipFormatSection(reader);
    }

    // Count the number of digits in the format.
    ParseFormatSection(reader, integerDigits, decimalDigits, exponentDigits);

    // Prepare the number buffer by setting the decimal precision.
    value.FormatCustomNumber(*integerDigits, *decimalDigits, *exponentDigits > 0);

    // If the number is zero, try skipping to the third section of the format string which contains the format for zero
    // values.
    if (formatContainsMultipleSections && value.IsZero()) {
        // If the number is positive, we are still in the first section and so we must skip two sections.
        if (!value.IsNegative()) {
            formatContainsMultipleSections = SkipFormatSection(reader);
        }

        // If the format string does not contain at least second section then there cannot be a third section either,
        // so we don't bother trying. Only if the format string actually contains a third section, count the number of
        // digits in this section of the format string.
        if (formatContainsMultipleSections && SkipFormatSection(reader)) {
            // Count the number of digits in the format.
            ParseFormatSection(reader, integerDigits, decimalDigits, exponentDigits);

            // Prepare the number buffer by setting the decimal precision.
            value.FormatCustomNumber(*integerDigits, *decimalDigits, *exponentDigits > 0);
        }
    }

    // The sign should be printed only if the format string consists of a single section.
    *printSign = !formatContainsMultipleSections;
}

/// <summary>
/// Skips to the next section of the format string.
/// </summary>
static bool SkipFormatSection(StringReader &reader)
{
    uintsize length = 0;

    while (true) {
        int ch = reader.Peek(length);

        switch (ch) {
            case -1:
                return false;
            case '\'':
            case '"':
                SkipString(reader, &length);
                break;
            case '\\':
                SkipEscapeSequence(reader, &length);
                break;
            case ';':
                length++;
                reader.Skip(length);
                return true;
            default:
                length++;
        }
    }
}

/// <summary>
/// Processes the current section of the custom format string.
/// </summary>
static void ParseFormatSection(
    StringReader &reader,
    int *integerDigits,
    int *decimalDigits,
    int *exponentDigits)
{
    assert(integerDigits != nullptr);
    assert(decimalDigits != nullptr);
    assert(exponentDigits != nullptr);

    bool integerPart = true;
    bool parsedExponent = false;

    *integerDigits = 0;
    *decimalDigits = 0;
    *exponentDigits = 0;

    uintsize length = 0;

    while (true) {
        int ch = reader.Peek(length);

        switch (ch) {
            case -1:
            case ';':
                return;
            case '\'':
            case '"':
                SkipString(reader, &length);
                break;
            case '\\':
                SkipEscapeSequence(reader, &length);
                break;
            case '.':
                length++;
                integerPart = false;
                break;
            case 'e':
            case 'E':
                if (!parsedExponent && IsExponent(reader, length)) {
                    SkipExponent(reader, &length, exponentDigits);

                    parsedExponent = true;
                }
                else {
                    length++;
                }
                break;
            case '0':
            case '#':
                length++;

                if (integerPart) {
                    *integerDigits += 1;
                }
                else {
                    *decimalDigits += 1;
                }

                break;
            default:
                length++;
        }
    }
}

/// <summary>
/// Reads and prints a string literal in a custom format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void ReadString(StringBuilder &sb, StringReader &reader)
{
    assert(reader.Peek() == '\'' || reader.Peek() == '"');

    int delimiter = reader.Read();
    int ch = reader.Read();

    while (ch != -1 && ch != delimiter) {
        sb.Append((char)ch);

        ch = reader.Read();
    }
}

/// <summary>
/// Skips a string literal in a custom format string.
/// </summary>
static void SkipString(StringReader &reader, uintsize *offset)
{
    assert(offset != nullptr);
    assert(reader.Peek(*offset) == '\'' || reader.Peek(*offset) == '"');

    int delimiter = reader.Peek(*offset);
    int ch;

    *offset += 1;

    do {
        ch = reader.Peek(*offset);

        *offset += 1;
    } while (ch != -1 && ch != delimiter);
}

/// <summary>
/// Reads and prints an escape sequence in a custom format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void ReadEscapeSequence(StringBuilder &sb, StringReader &reader)
{
    assert(reader.Peek() == '\\');

    int ch = reader.Peek(1);

    if (IsEscapedCharacter(ch)) {
        sb.Append((char)ch);
        reader.Skip(2);
    }
    else {
        reader.Skip(1);
    }
}

/// <summary>
/// Skips an escape sequence in a custom format string.
/// </summary>
static void SkipEscapeSequence(StringReader &reader, uintsize *offset)
{
    assert(offset != nullptr);
    assert(reader.Peek(*offset) == '\\');

    int ch = reader.Peek(*offset + 1);

    if (IsEscapedCharacter(ch)) {
        *offset += 2;
    }
    else {
        *offset += 1;
    }
}

/// <summary>
/// Determines whether the character is a valid escaped character.
/// </summary>
static bool IsEscapedCharacter(int ch)
{
    switch (ch) {
        case '\\':
        case '#':
        case '0':
        case '.':
        case ',':
        case '%':
        case ';':
            return true;
        default:
            return false;
    }
}

/// <summary>
/// Determines whether the next characters in the format string represent an exponent.
/// </summary>
static bool IsExponent(StringReader &reader, uintsize offset)
{
    int ch0 = reader.Peek(offset);
    int ch1 = reader.Peek(offset + 1);
    int ch2 = reader.Peek(offset + 2);

    return Char::ToLower(ch0) == 'e' && (ch1 == '0' || ((ch1 == '+' || ch1 == '-') && ch2 == '0'));
}

/// <summary>
/// Skips the exponent in a custom format string.
/// </summary>
static void SkipExponent(StringReader &reader, uintsize *offset, int *exponentDigits)
{
    assert(offset != nullptr);
    assert(IsExponent(reader, *offset));
    assert(exponentDigits != nullptr);

    // Skip the 'e' character.
    *offset += 1;

    // Read the character after the exponent.
    int ch = reader.Peek(*offset);

    // If the character is a sign, skip it also.
    if (ch == '+' || ch == '-') {
        *offset += 1;
    }

    *exponentDigits = 0;

    // Skip all zeros directly following the 'e'.
    while (reader.Peek(*offset) == '0') {
        *offset += 1;
        *exponentDigits += 1;
    }
}

/// <summary>
/// Processes and prints the exponent in a custom format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void PrintExponent(StringBuilder &sb, StringReader &reader, int exponent)
{
    assert(IsExponent(reader, 0));

    // Print the 'e' character.
    sb.Append((char)reader.Read());

    // Read the character after the exponent.
    int ch = reader.Peek();

    // If the character is a sign, read it also.
    if (ch == '+' || ch == '-') {
        // If the sign is +, print the sign of the exponent is positive.
        if (ch == '+' && exponent >= 0) {
            sb.Append('+');
        }

        reader.Read();
    }

    int exponentDigits = 0;

    // Count the minimum number of exponent digits.
    while (reader.Peek() == '0') {
        exponentDigits++;

        reader.Read();
    }

    // Print the exponent with the given minimum number of digits.
    NumberBuffer exponentBuffer = NumberBuffer::FromIntMax(exponent);
    exponentBuffer.FormatInteger(exponentDigits, 10, false);
    exponentBuffer.ToString(sb);
}

/// <summary>
/// Prints the decimal separator if needed.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void PrintDecimalSeparator(StringBuilder &sb, uintsize *decimalSeparatorIndex)
{
    assert(decimalSeparatorIndex != nullptr);

    if (*decimalSeparatorIndex != InvalidIndex) {
        sb.Insert(*decimalSeparatorIndex, '.');
        *decimalSeparatorIndex = InvalidIndex;
    }
}

/// <summary>
/// Prints any leading zeros if needed.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
static void PrintLeadingZeros(StringBuilder &sb, int *numLeadingZeros)
{
    assert(numLeadingZeros != nullptr);

    int length = *numLeadingZeros;

    for (int i = 0; i < length; i++) {
        sb.Append('0');
    }

    *numLeadingZeros = 0;
}
