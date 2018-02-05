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

#include "CFlat/Language/Char.h"

#include "CFlat.h"
#include "CFlat/String.h"

using namespace CFlat;

/* Macros */
#define CHAR_CONTROL            0x0001
#define CHAR_LOWER              0x0002
#define CHAR_UPPER              0x0004
#define CHAR_DIGIT              0x0008
#define CHAR_BINARY             0x0010
#define CHAR_HEX                0x0020
#define CHAR_PUNCTATION         0x0040
#define CHAR_WHITESPACE         0x0080
#define CHAR_SEPARATOR          0x0100
#define CHAR_LETTER             (CHAR_LOWER | CHAR_UPPER)
#define CHAR_LETTER_OR_DIGIT    (CHAR_LETTER | CHAR_DIGIT)
#define CHAR_GRAPHIC            (CHAR_LETTER_OR_DIGIT | CHAR_PUNCTATION)
#define CHAR_PRINTABLE          (CHAR_GRAPHIC | CHAR_SEPARATOR)

/// <summary>
/// The bitmask for valid ASCII characters.
/// </summary>
#define ASCII_MASK              0x7F

/// <summary>
/// Determines whether a character is a valid ASCII characters.
/// </summary>
#define IS_ASCII(c)             !((c) & ~ASCII_MASK)

/// <summary>
/// Determines whether a character belongs to the given character class.
/// </summary>
#define CHAR_IS(c, group)       ((LookupTable[(c) & ASCII_MASK] & (group)) && IS_ASCII(c))

/* Private constants */
/// <summary>
/// A lookup table that maps ASCII characters to a bitmask representing their character classes.
/// </summary>
static const int LookupTable[128] =
{
    /* 0x00 .. 0x08 */
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,

    /* 0x09 .. 0x0D */
    CHAR_CONTROL | CHAR_WHITESPACE,
    CHAR_CONTROL | CHAR_WHITESPACE,
    CHAR_CONTROL | CHAR_WHITESPACE,
    CHAR_CONTROL | CHAR_WHITESPACE,
    CHAR_CONTROL | CHAR_WHITESPACE,

    /* 0x0E .. 0x1F */
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,
    CHAR_CONTROL,

    /* 0x20 */
    CHAR_WHITESPACE | CHAR_SEPARATOR,

    /* 0x21 .. 0x2F */
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,

    /* 0x30 .. 0x39 */
    CHAR_DIGIT | CHAR_HEX | CHAR_BINARY,
    CHAR_DIGIT | CHAR_HEX | CHAR_BINARY,
    CHAR_DIGIT | CHAR_HEX,
    CHAR_DIGIT | CHAR_HEX,
    CHAR_DIGIT | CHAR_HEX,
    CHAR_DIGIT | CHAR_HEX,
    CHAR_DIGIT | CHAR_HEX,
    CHAR_DIGIT | CHAR_HEX,
    CHAR_DIGIT | CHAR_HEX,
    CHAR_DIGIT | CHAR_HEX,

    /* 0x3A .. 0x40 */
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,

    /* 0x41 .. 0x46 */
    CHAR_UPPER | CHAR_HEX,
    CHAR_UPPER | CHAR_HEX,
    CHAR_UPPER | CHAR_HEX,
    CHAR_UPPER | CHAR_HEX,
    CHAR_UPPER | CHAR_HEX,
    CHAR_UPPER | CHAR_HEX,

    /* 0x47 .. 0x5A */
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,
    CHAR_UPPER,

    /* 0x5B .. 0x60 */
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,

    /* 0x61 .. 0x66 */
    CHAR_LOWER | CHAR_HEX,
    CHAR_LOWER | CHAR_HEX,
    CHAR_LOWER | CHAR_HEX,
    CHAR_LOWER | CHAR_HEX,
    CHAR_LOWER | CHAR_HEX,
    CHAR_LOWER | CHAR_HEX,

    /* 0x67 .. 0x7A */
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,
    CHAR_LOWER,

    /* 0x7B .. 0x7E */
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,
    CHAR_PUNCTATION,

    /* 0x7F */
    CHAR_CONTROL,
};

const char Char::MinValue = CHAR_MIN;

const char Char::MaxValue = CHAR_MAX;

/**************************************/
/* Public function definitions        */
/**************************************/

bool Char::IsBinaryDigit(int c)
{
    return CHAR_IS(c, CHAR_BINARY);
}

bool Char::IsControl(int c)
{
    return CHAR_IS(c, CHAR_CONTROL);
}

bool Char::IsDigit(int c)
{
    return CHAR_IS(c, CHAR_DIGIT);
}

bool Char::IsGraphic(int c)
{
    return CHAR_IS(c, CHAR_GRAPHIC);
}

bool Char::IsHexadecimalDigit(int c)
{
    return CHAR_IS(c, CHAR_HEX);
}

bool Char::IsLetter(int c)
{
    return CHAR_IS(c, CHAR_LETTER);
}

bool Char::IsLetterOrDigit(int c)
{
    return CHAR_IS(c, CHAR_LETTER_OR_DIGIT);
}

bool Char::IsLower(int c)
{
    return CHAR_IS(c, CHAR_LOWER);
}

bool Char::IsPrintable(int c)
{
    return CHAR_IS(c, CHAR_PRINTABLE);
}

bool Char::IsPunctation(int c)
{
    return CHAR_IS(c, CHAR_PUNCTATION);
}

bool Char::IsSeparator(int c)
{
    return CHAR_IS(c, CHAR_SEPARATOR);
}

bool Char::IsUpper(int c)
{
    return CHAR_IS(c, CHAR_UPPER);
}

bool Char::IsWhiteSpace(int c)
{
    return CHAR_IS(c, CHAR_WHITESPACE);
}

int Char::ToLower(int c)
{
    if (Char::IsUpper(c)) {
        return 'a' + c - 'A';
    }
    else {
        return c;
    }
}

int Char::ToUpper(int c)
{
    if (Char::IsLower(c)) {
        return 'A' + c - 'a';
    }
    else {
        return c;
    }
}

String Char::ToString(char c)
{
    char buffer[2];
    buffer[0] = c;
    buffer[1] = '\0';

    return String(buffer);
}
