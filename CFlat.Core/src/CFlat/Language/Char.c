#include "CFlat/Language/Char.h"

#include "CFlat.h"

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

#define ASCII_MASK              0x7F
#define IS_ASCII(c)             !((c) & ~ASCII_MASK)
#define CHAR_IS(c, group)       ((LookupTable[(c) & ASCII_MASK] & (group)) && IS_ASCII(c))

/* Private constants */
private const int LookupTable[128] =
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

/**************************************/
/* Public function definitions        */
/**************************************/

public bool char_IsBinaryDigit(int c)
{
    return CHAR_IS(c, CHAR_BINARY);
}

public bool char_IsControl(int c)
{
    return CHAR_IS(c, CHAR_CONTROL);
}

public bool char_IsDigit(int c)
{
    return CHAR_IS(c, CHAR_DIGIT);
}

public bool char_IsGraphic(int c)
{
    return CHAR_IS(c, CHAR_GRAPHIC);
}

public bool char_IsHexDigit(int c)
{
    return CHAR_IS(c, CHAR_HEX);
}

public bool char_IsLetter(int c)
{
    return CHAR_IS(c, CHAR_LETTER);
}

public bool char_IsLetterOrDigit(int c)
{
    return CHAR_IS(c, CHAR_LETTER_OR_DIGIT);
}

public bool char_IsLower(int c)
{
    return CHAR_IS(c, CHAR_LOWER);
}

public bool char_IsPrintable(int c)
{
    return CHAR_IS(c, CHAR_PRINTABLE);
}

public bool char_IsPunctation(int c)
{
    return CHAR_IS(c, CHAR_PUNCTATION);
}

public bool char_IsSeparator(int c)
{
    return CHAR_IS(c, CHAR_SEPARATOR);
}

public bool char_IsUpper(int c)
{
    return CHAR_IS(c, CHAR_UPPER);
}

public bool char_IsWhiteSpace(int c)
{
    return CHAR_IS(c, CHAR_WHITESPACE);
}

public int char_ToLower(int c)
{
    if (char_IsUpper(c)) {
        return 'a' + c - 'A';
    }
    else {
        return c;
    }
}

public int char_ToUpper(int c)
{
    if (char_IsLower(c)) {
        return 'A' + c - 'a';
    }
    else {
        return c;
    }
}
