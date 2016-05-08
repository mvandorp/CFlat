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

#ifndef CFLAT_CORE_CFLATEXCEPTION_INTERNAL_H
#define CFLAT_CORE_CFLATEXCEPTION_INTERNAL_H

#ifndef CFLAT_CORE_CFLATEXCEPTION_H
 #error CFlatException.internal.h should not be included directly.
#endif

#include "CFlat/CFlatException.h"
#include "CFlat/ExceptionType.h"
#include "CFlat/Object.h"

/* Forward declarations */
struct String;

/* Types */
/// <summary>
/// Represents an error that occured.
/// </summary>
struct CFlatException {
    Object Base;
    const struct String *Message;
    const char *File;
    int Line;
    ExceptionType Type;
    CFlatException *InnerException;
};

#endif
