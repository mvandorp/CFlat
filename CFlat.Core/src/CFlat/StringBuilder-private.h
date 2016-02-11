#ifndef CFLAT_CORE_STRINGBUILDER_PRIVATE_H
#define CFLAT_CORE_STRINGBUILDER_PRIVATE_H

#include <stdarg.h>

typedef struct String String;
typedef struct StringBuilder StringBuilder;

/// <summary>
/// Appends a string that is formatted according to the given format string, to the given <see cref="StringBuilder"/>.
/// Each format specifier replaced with a string representation of the corresponding argument.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <param name="format">Pointer to a format string.</param>
/// <param name="args">
/// A variable argument list containing the objects to format according to the format specifiers in the format string.
/// </param>
void StringBuilder_AppendFormat(StringBuilder *sb, const String *format, va_list args);

#endif
