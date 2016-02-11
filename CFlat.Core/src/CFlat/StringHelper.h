#ifndef CFLAT_CORE_INTERNAL_STRINGHELPER_H
#define CFLAT_CORE_INTERNAL_STRINGHELPER_H

#include "CFlat/String.h"
#include "CFlat/String-private.h"

/// <summary>
/// Returns a <see cref="String"/> wrapper for the given null-terminated string.
/// </summary>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <returns>A <see cref="String"/> wrapper for the given null-terminated string.</returns>
String String_WrapCString(const char *value);

#endif
