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

/**
 * @file Functions.h
 */

#ifndef CFLAT_CORE_LANGUAGE_FUNCTIONS_H
#define CFLAT_CORE_LANGUAGE_FUNCTIONS_H

#include "CFlat/Language/Bool.h"

/// <summary>
/// A function that determines whether two given objects compare equal.
/// </summary>
/// <param name="x">The first object to compare.</param>
/// <param name="x">The second object to compare.</param>
/// <returns><see cref="true"/> if the objects compare equal; otherwise <see cref="false"/>.</returns>
typedef bool (*EqualityPredicate)(const void *x, const void *y);

#endif
