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

typedef struct String {
    Object object;
    uintsize length;
    const char* value;
} String;

#endif
