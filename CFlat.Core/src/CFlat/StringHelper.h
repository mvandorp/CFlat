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

#ifndef CFLAT_CORE_INTERNAL_STRINGHELPER_H
#define CFLAT_CORE_INTERNAL_STRINGHELPER_H

#include "CFlat/String-private.h"

/// <summary>
/// Returns a <see cref="String"/> wrapper for the given null-terminated string.
/// </summary>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <returns>A <see cref="String"/> wrapper for the given null-terminated string.</returns>
String String_WrapCString(const char *value);

#endif
