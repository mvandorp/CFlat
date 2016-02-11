#ifndef CFLAT_CORE_STRING_PRIVATE_H
#define CFLAT_CORE_STRING_PRIVATE_H

#include "CFlat/Object.h"

/// <summary>
/// Evaluates to the size of the given string literal.
/// </summary>
/// <param name="value">A string literal.</param>
#define CFLAT_STRING_LITERAL_LENGTH(value) (sizeof(value) - 1)

/// <summary>
/// Initializer for a <see cref="String"/> that initializes the value to the given value string literal.
/// </summary>
/// <param name="value">A string literal.</param>
#define CFLAT_STRING_LITERAL(value) { CFLAT_OBJECT_INITIALIZER(null), CFLAT_STRING_LITERAL_LENGTH(value), value }

struct String {
    Object object;
    uintsize length;
    const char* value;
};

#endif
