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

#include "CFlat/Language/Keywords.h"

#if defined(__GNUC__) && defined(__GNUC_MINOR__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
 // Defined if the compiler is GCC version is 4.6 or newer.
 #define GCC_4_6
#endif

#if defined(GCC_4_6) || defined(__clang__)
 // Defined if the compiler supports GCC diagnostic pragmas.
 #define GCC_diagnostic
#endif

#ifdef GCC_diagnostic
 #pragma GCC diagnostic push
 #pragma GCC diagnostic ignored "-Wcast-qual"
#endif

// This function is not declared in any header, it should not be used outside of Memory.c and Object.c.
internal void *const_cast(const void *ptr);
internal void *const_cast(const void *ptr)
{
    return (void*)ptr;
}

#ifdef GCC_diagnostic
 #pragma GCC diagnostic pop
#endif
