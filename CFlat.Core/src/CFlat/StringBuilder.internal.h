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

#ifndef CFLAT_CORE_STRINGBUILDER_INTERNAL_H
#define CFLAT_CORE_STRINGBUILDER_INTERNAL_H

#include "CFlat/Object.h"
#include "CFlat/Language/Integer.h"

#include <stdarg.h>

typedef struct String String;

typedef struct StringBuilder {
    Object Base;
    char *Value;
    uintsize Length;
    uintsize Capacity;
} StringBuilder;

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

/// <summary>
/// Gets the internal string buffer of the given <see cref="StringBuilder"/>, which contains a null-terminated string.
/// The buffer becomes invalid when the <see cref="StringBuilder"/> is modified.
/// </summary>
/// <param name="sb">Pointer to a <see cref="StringBuilder"/>.</param>
/// <returns>
/// A pointer to a null-terminated string with the same value as the given <see cref="StringBuilder"/>.
/// </returns>
const char *StringBuilder_GetBuffer(const StringBuilder *sb);

#endif
