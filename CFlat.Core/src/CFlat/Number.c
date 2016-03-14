#include "CFlat/Number.h"
#include "CFlat/Number.NumberBuffer.h"

#include "CFlat.h"
#include "CFlat/Math.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/StringReader.h"
#include "CFlat/Validate.h"

/**************************************/
/* Private functions                  */
/**************************************/

private String *FormatNumber(NumberBuffer *value, const String *format);
private void FormatNumberBuffered(StringBuilder *sb, NumberBuffer *value, const String *format);
private void FormatStandardNumber(
    StringBuilder *sb,
    NumberBuffer *value,
    char formatSpecifier,
    int precisionSpecifier);
private void FormatCustomNumber(StringBuilder *sb, NumberBuffer *value, StringReader *reader);
private bool ProcessStandardFormatString(StringReader *reader, char *formatSpecifier, int *precisionSpecifier);
private void ProcessCustomFormatString(
    StringReader *reader,
    NumberBuffer *value,
    int *integerDigits,
    int *decimalDigits,
    int *exponentDigits,
    bool *printSign);
private bool SkipFormatSection(StringReader *reader);
private void ParseFormatSection(
    StringReader *reader,
    int *integerDigits,
    int *decimalDigits,
    int *exponentDigits);
private void ReadString(StringBuilder *sb, StringReader *reader);
private void SkipString(StringReader *reader, uintsize *offset);
private void ReadEscapeSequence(StringBuilder *sb, StringReader *reader);
private void SkipEscapeSequence(StringReader *reader, uintsize *offset);
private bool IsEscapedCharacter(int ch);
private bool IsExponent(StringReader *reader, uintsize offset);
private void SkipExponent(StringReader *reader, uintsize *offset, int *exponentDigits);
private void PrintExponent(StringBuilder *sb, StringReader *reader, int exponent);
private void PrintDecimalSeparator(StringBuilder *sb, uintsize *decimalSeparatorIndex);
private void PrintLeadingZeros(StringBuilder *sb, int *numLeadingZeros);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal String *Number_FormatIntMax(intmax value, const String *format)
{
    NumberBuffer number;
    NumberBuffer_FromIntMax(&number, value);

    return FormatNumber(&number, format);
}

internal String *Number_FormatUIntMax(uintmax value, const String *format)
{
    NumberBuffer number;
    NumberBuffer_FromUIntMax(&number, value);

    return FormatNumber(&number, format);
}

internal String *Number_FormatSingle(float value, const String *format)
{
    NumberBuffer number;
    NumberBuffer_FromSingle(&number, value);

    return FormatNumber(&number, format);
}

internal String *Number_FormatDouble(double value, const String *format)
{
    NumberBuffer number;
    NumberBuffer_FromDouble(&number, value);

    return FormatNumber(&number, format);
}

internal void Number_FormatIntMaxBuffered(StringBuilder *sb, intmax value, const String *format)
{
    Validate_NotNull(sb);

    NumberBuffer number;
    NumberBuffer_FromIntMax(&number, value);

    FormatNumberBuffered(sb, &number, format);
}

internal void Number_FormatUIntMaxBuffered(StringBuilder *sb, uintmax value, const String *format)
{
    Validate_NotNull(sb);

    NumberBuffer number;
    NumberBuffer_FromUIntMax(&number, value);

    FormatNumberBuffered(sb, &number, format);
}

internal void Number_FormatSingleBuffered(StringBuilder *sb, float value, const String *format)
{
    Validate_NotNull(sb);

    NumberBuffer number;
    NumberBuffer_FromSingle(&number, value);

    FormatNumberBuffered(sb, &number, format);
}

internal void Number_FormatDoubleBuffered(StringBuilder *sb, double value, const String *format)
{
    Validate_NotNull(sb);

    NumberBuffer number;
    NumberBuffer_FromDouble(&number, value);

    FormatNumberBuffered(sb, &number, format);
}

internal bool Number_IsNonDecimalFormat(const String *format)
{
    if (format == null) {
        return false;
    }

    StringReader reader;
    StringReader_Constructor(&reader, format);

    char formatSpecifier;
    int precisionSpecifier;
    bool isNonDecimalFormat = false;

    if (ProcessStandardFormatString(&reader, &formatSpecifier, &precisionSpecifier)) {
        if (formatSpecifier == 'b' || formatSpecifier == 'B' || formatSpecifier == 'x' || formatSpecifier == 'X') {
            isNonDecimalFormat = true;
        }
    }

    Object_Release(&reader);

    return isNonDecimalFormat;
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Formats a number according to the given format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private String *FormatNumber(NumberBuffer *value, const String *format)
{
    assert(value != null);

    StringBuilder sb;
    StringBuilder_Constructor(&sb);

    FormatNumberBuffered(&sb, value, format);

    return StringBuilder_DeleteAndToString(&sb);
}

/// <summary>
/// Formats a number according to the given format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private void FormatNumberBuffered(StringBuilder *sb, NumberBuffer *value, const String *format)
{
    assert(sb != null);
    assert(value != null);

    String formatBuffer;

    if (format == null) {
        format = String_WrapCString("G", &formatBuffer);
    }

    StringReader reader;
    StringReader_Constructor(&reader, format);

    char formatSpecifier;
    int precisionSpecifier;

    if (ProcessStandardFormatString(&reader, &formatSpecifier, &precisionSpecifier)) {
        FormatStandardNumber(sb, value, formatSpecifier, precisionSpecifier);
    }
    else {
        FormatCustomNumber(sb, value, &reader);
    }

    Object_Release(&reader);
}

/// <summary>
/// Formats a number according to a standard format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private void FormatStandardNumber(StringBuilder *sb, NumberBuffer *value, char formatSpecifier, int precisionSpecifier)
{
    assert(sb != null);
    assert(value != null);
    assert(precisionSpecifier >= 0);

    if (formatSpecifier == 'b' || formatSpecifier == 'B') {
        NumberBuffer_FormatInteger(value, precisionSpecifier, 2, false);
    }
    else if (formatSpecifier == 'd' || formatSpecifier == 'D') {
        NumberBuffer_FormatInteger(value, precisionSpecifier, 10, false);
    }
    else if (formatSpecifier == 'x') {
        NumberBuffer_FormatInteger(value, precisionSpecifier, 16, false);
    }
    else if (formatSpecifier == 'X') {
        NumberBuffer_FormatInteger(value, precisionSpecifier, 16, true);
    }
    else if (formatSpecifier == 'e' || formatSpecifier == 'E') {
        NumberBuffer_FormatExponential(value, precisionSpecifier);
    }
    else if (formatSpecifier == 'f' || formatSpecifier == 'F') {
        NumberBuffer_FormatFixedPoint(value, precisionSpecifier);
    }
    else if (formatSpecifier == 'g' || formatSpecifier == 'G') {
        NumberBuffer_FormatGeneral(value, precisionSpecifier);
    }
    else {
        // Invalid format specifier.
        assert(false);
    }

    NumberBuffer_ToString(value, sb);
}

/// <summary>
/// Formats a number according to a custom format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private void FormatCustomNumber(StringBuilder *sb, NumberBuffer *value, StringReader *reader)
{
    assert(sb != null);
    assert(value != null);
    assert(reader != null);

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

    if (printSign && NumberBuffer_IsNegative(value)) {
        StringBuilder_Append(sb, '-');
    }

    int valueIntegerDigits = NumberBuffer_GetIntegerCount(value);
    int valueDecimalDigits = NumberBuffer_GetDecimalCount(value);

    int integerIndex = 0;
    int decimalIndex = 0;
    int leadingDecimalZeros = 0;

    bool integerPart = true;
    bool printedExponent = false;
    uintsize decimalSeparatorIndex = InvalidIndex;

    while (true) {
        int ch = StringReader_Peek(reader);

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
                    PrintExponent(sb, reader, NumberBuffer_GetExponent(value));

                    printedExponent = true;
                }
                else {
                    StringBuilder_Append(sb, (char)StringReader_Read(reader));
                }
                break;
            case '0':
            case '#':
                StringReader_Read(reader);

                if (integerPart) {
                    // We're processing the integer part.

                    // While there are integer digits to print, print them.
                    while (valueIntegerDigits >= formatIntegerDigits) {
                        StringBuilder_Append(sb, NumberBuffer_GetIntegerDigit(value, integerIndex++));
                        valueIntegerDigits--;
                    }

                    formatIntegerDigits--;
                }
                else {
                    // We're processing the decimal part.

                    bool isZero =
                        decimalIndex >= valueDecimalDigits ||
                        NumberBuffer_GetDecimalDigit(value, decimalIndex) == '0';

                    if (ch == '#' && isZero) {
                        // If the digit is zero and it should not be printed, increment leadingDecimalZeros and break.
                        decimalIndex++;
                        leadingDecimalZeros++;
                        break;
                    }

                    // Print a decimal seperator and any leading zeros if required.
                    PrintDecimalSeparator(sb, &decimalSeparatorIndex);
                    PrintLeadingZeros(sb, &leadingDecimalZeros);

                    if (decimalIndex < valueDecimalDigits) {
                        // If there is a decimal digit left to print, print it.
                        StringBuilder_Append(sb, NumberBuffer_GetDecimalDigit(value, decimalIndex++));
                    }
                    else if (ch == '0') {
                        // Otherwise, print a zero if required.
                        StringBuilder_Append(sb, '0');
                    }
                }

                break;
            case '.':
                StringReader_Read(reader);

                if (integerPart) {
                    decimalSeparatorIndex = StringBuilder_GetLength(sb);
                    integerPart = false;
                }

                break;
            default:
                StringBuilder_Append(sb, (char)StringReader_Read(reader));
                break;
        }
    }
}

/// <summary>
/// Processes a format string and returns whether or not it is a standard format string.
/// If the format is a standard format the format specifier and precision specifier are determined as well.
/// </summary>
private bool ProcessStandardFormatString(StringReader *reader, char *formatSpecifier, int *precisionSpecifier)
{
    assert(reader != null);
    assert(formatSpecifier != null);
    assert(precisionSpecifier != null);

    int format = StringReader_Peek(reader);
    int precision1 = StringReader_PeekOffset(reader, 1);
    int precision2 = StringReader_PeekOffset(reader, 2);
    int end = StringReader_PeekOffset(reader, 3);

    int ch = char_ToLower(format);

    // If the format is more than three characters long it cannot be a valid standard format string.
    if (end != -1) {
        return false;
    }

    // Check if the format specifier is valid.
    if (ch != 'b' && ch != 'd' && ch != 'e' && ch != 'f' && ch != 'g' && ch != 'x') {
        return false;
    }

    // Verify that the precision specifier is either valid or absent.
    if (!char_IsDigit(precision1) && precision1 != -1) {
        return false;
    }

    // Verify that the precision specifier is either valid or absent.
    if (!char_IsDigit(precision2) && precision2 != -1) {
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
private void ProcessCustomFormatString(
    StringReader *reader,
    NumberBuffer *value,
    int *integerDigits,
    int *decimalDigits,
    int *exponentDigits,
    bool *printSign)
{
    assert(reader != null);
    assert(value != null);
    assert(integerDigits != null);
    assert(decimalDigits != null);
    assert(exponentDigits != null);
    assert(printSign != null);

    // Keeps track of whether the format string contains multiple sections in order to avoid trying to skip to a third
    // section when it does not exist.
    bool formatContainsMultipleSections = true;

    // If the number is negative, try skipping to the next section of the format string which contains the format for
    // negative values.
    if (NumberBuffer_IsNegative(value)) {
        formatContainsMultipleSections = SkipFormatSection(reader);
    }

    // Count the number of digits in the format.
    ParseFormatSection(reader, integerDigits, decimalDigits, exponentDigits);

    // Prepare the number buffer by setting the decimal precision.
    NumberBuffer_FormatCustomNumber(value, *integerDigits, *decimalDigits, *exponentDigits > 0);

    // If the number is zero, try skipping to the third section of the format string which contains the format for zero
    // values.
    if (NumberBuffer_IsZero(value)) {
        // If the number is positive, we are still in the first section and so we must skip two sections.
        if (!NumberBuffer_IsNegative(value)) {
            formatContainsMultipleSections = SkipFormatSection(reader);
        }

        // If the format string does not contain at least second section then there cannot be a third section either,
        // so we don't bother trying.
        if (formatContainsMultipleSections) {
            // Only if the format string actually contains a third section, count the number of digits in this section
            // of the format string.
            if (SkipFormatSection(reader)) {
                ParseFormatSection(reader, integerDigits, decimalDigits, exponentDigits);
            }
        }
    }

    // The sign should be printed only if the format string consists of a single section.
    *printSign = !formatContainsMultipleSections;
}

/// <summary>
/// Skips to the next section of the format string.
/// </summary>
private bool SkipFormatSection(StringReader *reader)
{
    assert(reader != null);

    uintsize length = 0;

    while (true) {
        int ch = StringReader_PeekOffset(reader, length);

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
                StringReader_Skip(reader, length);
                return true;
            default:
                length++;
        }
    }
}

/// <summary>
/// Processes the current section of the custom format string.
/// </summary>
private void ParseFormatSection(
    StringReader *reader,
    int *integerDigits,
    int *decimalDigits,
    int *exponentDigits)
{
    assert(reader != null);
    assert(integerDigits != null);
    assert(decimalDigits != null);
    assert(exponentDigits != null);

    bool integerPart = true;
    bool parsedExponent = false;

    *integerDigits = 0;
    *decimalDigits = 0;
    *exponentDigits = 0;

    uintsize length = 0;

    while (true) {
        int ch = StringReader_PeekOffset(reader, length);

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
private void ReadString(StringBuilder *sb, StringReader *reader)
{
    assert(sb != null);
    assert(reader != null);
    assert(StringReader_Peek(reader) == '\'' || StringReader_Peek(reader) == '"');

    int delimiter = StringReader_Read(reader);
    int ch = StringReader_Read(reader);

    while (ch != -1 && ch != delimiter) {
        StringBuilder_Append(sb, (char)ch);

        ch = StringReader_Read(reader);
    }
}

/// <summary>
/// Skips a string literal in a custom format string.
/// </summary>
private void SkipString(StringReader *reader, uintsize *offset)
{
    assert(reader != null);
    assert(offset != null);
    assert(StringReader_PeekOffset(reader, *offset) == '\'' || StringReader_PeekOffset(reader, *offset) == '"');

    int delimiter = StringReader_PeekOffset(reader, *offset);
    int ch;

    *offset += 1;

    do {
        ch = StringReader_PeekOffset(reader, *offset);

        *offset += 1;
    }
    while (ch != -1 && ch != delimiter);
}

/// <summary>
/// Reads and prints an escape sequence in a custom format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private void ReadEscapeSequence(StringBuilder *sb, StringReader *reader)
{
    assert(sb != null);
    assert(reader != null);
    assert(StringReader_Peek(reader) == '\\');

    int ch = StringReader_PeekOffset(reader, 1);

    if (IsEscapedCharacter(ch)) {
        StringBuilder_Append(sb, (char)ch);
        StringReader_Skip(reader, 2);
    }
    else {
        StringReader_Skip(reader, 1);
    }
}

/// <summary>
/// Skips an escape sequence in a custom format string.
/// </summary>
private void SkipEscapeSequence(StringReader *reader, uintsize *offset)
{
    assert(reader != null);
    assert(offset != null);
    assert(StringReader_PeekOffset(reader, *offset) == '\\');

    int ch = StringReader_PeekOffset(reader, *offset + 1);

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
private bool IsEscapedCharacter(int ch)
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
private bool IsExponent(StringReader *reader, uintsize offset)
{
    assert(reader != null);

    int ch0 = StringReader_PeekOffset(reader, offset);
    int ch1 = StringReader_PeekOffset(reader, offset + 1);
    int ch2 = StringReader_PeekOffset(reader, offset + 2);

    return char_ToLower(ch0) == 'e' && (ch1 == '0' || ((ch1 == '+' || ch1 == '-') && ch2 == '0'));
}

/// <summary>
/// Skips the exponent in a custom format string.
/// </summary>
private void SkipExponent(StringReader *reader, uintsize *offset, int *exponentDigits)
{
    assert(reader != null);
    assert(offset != null);
    assert(IsExponent(reader, *offset));
    assert(exponentDigits != null);

    // Skip the 'e' character.
    *offset += 1;

    // Read the character after the exponent.
    int ch = StringReader_PeekOffset(reader, *offset);

    // If the character is a sign, skip it also.
    if (ch == '+' || ch == '-') {
        *offset += 1;
    }

    *exponentDigits = 0;

    // Skip all zeros directly following the 'e'.
    while (StringReader_PeekOffset(reader, *offset) == '0') {
        *offset += 1;
        *exponentDigits += 1;
    }
}

/// <summary>
/// Processes and prints the exponent in a custom format string.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private void PrintExponent(StringBuilder *sb, StringReader *reader, int exponent)
{
    assert(sb != null);
    assert(reader != null);
    assert(IsExponent(reader, 0));

    // Print the 'e' character.
    StringBuilder_Append(sb, (char)StringReader_Read(reader));

    // Read the character after the exponent.
    int ch = StringReader_Peek(reader);

    // If the character is a sign, read it also.
    if (ch == '+' || ch == '-') {
        // If the sign is +, print the sign of the exponent is positive.
        if (ch == '+' && exponent >= 0) {
            StringBuilder_Append(sb, '+');
        }

        StringReader_Read(reader);
    }

    int exponentDigits = 0;

    // Count the minimum number of exponent digits.
    while (StringReader_Peek(reader) == '0') {
        exponentDigits++;

        StringReader_Read(reader);
    }

    // Print the exponent with the given minimum number of digits.
    NumberBuffer exponentBuffer;
    NumberBuffer_FromIntMax(&exponentBuffer, exponent);
    NumberBuffer_FormatInteger(&exponentBuffer, exponentDigits, 10, false);
    NumberBuffer_ToString(&exponentBuffer, sb);
}

/// <summary>
/// Prints the decimal separator if needed.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private void PrintDecimalSeparator(StringBuilder *sb, uintsize *decimalSeparatorIndex)
{
    assert(sb != null);
    assert(decimalSeparatorIndex != null);

    if (*decimalSeparatorIndex != InvalidIndex) {
        StringBuilder_Insert(sb, *decimalSeparatorIndex, '.');
        *decimalSeparatorIndex = InvalidIndex;
    }
}

/// <summary>
/// Prints any  leading zeros if needed.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
private void PrintLeadingZeros(StringBuilder *sb, int *numLeadingZeros)
{
    assert(sb != null);
    assert(numLeadingZeros != null);

    int length = *numLeadingZeros;

    for (int i = 0; i < length; i++) {
        StringBuilder_Append(sb, '0');
    }

    *numLeadingZeros = 0;
}
