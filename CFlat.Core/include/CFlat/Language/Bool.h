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

//! @file Bool.h

#ifndef CFLAT_CORE_LANGUAGE_BOOL_H
#define CFLAT_CORE_LANGUAGE_BOOL_H

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && (_MSC_VER >= 1800))
    // The compiler supports C99 or later, use the C99 _Bool type
    #define CFLAT_BOOL _Bool
#elif defined(_MSC_VER)
    // Visual Studio 2012 or earlier, use the int type
    #define CFLAT_BOOL int
#else
    // Otherwise use the char type
    #define CFLAT_BOOL char
#endif

/* Macros */
/// <summary>
/// The <see cref="bool"/> value <c>true</c>.
/// </summary>
#define true ((bool)1)

/// <summary>
/// The <see cref="bool"/> value <c>false</c>.
/// </summary>
#define false ((bool)0)

/* Types */
/// <summary>
/// Represents a boolean value, which can be either <see cref="true"/> or <see cref="false"/>.
/// </summary>
typedef CFLAT_BOOL bool;

#undef CFLAT_BOOL

#endif
