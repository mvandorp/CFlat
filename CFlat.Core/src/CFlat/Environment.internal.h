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

#ifndef CFLAT_CORE_ENVIRONMENT_INTERNAL_H
#define CFLAT_CORE_ENVIRONMENT_INTERNAL_H

#ifndef CFLAT_CORE_ENVIRONMENT_H
 #error Environment.internal.h should not be included directly.
#endif

#include "CFlat/Language/Keywords.h"

/* Forward declarations */
struct CFlatException;

/* Functions */
/// <summary>
/// Raises the <see cref="Environment_FirstChanceException"/> event with the given exception.
/// </summary>
/// <param name="ex">Pointer to the <see cref="CFlatException"/> that occured.</param>
internal void Environment_OnFirstChanceException(struct CFlatException *ex);

/// <summary>
/// Raises the <see cref="Environment_UnhandledException"/> event with the given exception.
/// </summary>
/// <param name="ex">Pointer to the <see cref="CFlatException"/> that occured.</param>
internal void Environment_OnUnhandledException(struct CFlatException *ex);

#endif
