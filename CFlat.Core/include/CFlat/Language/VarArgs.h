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

//! @file VarArgs.h

#ifndef CFLAT_CORE_LANGUAGE_VARARGS_H
#define CFLAT_CORE_LANGUAGE_VARARGS_H

#include <stdarg.h>

/* Macros */
/// <summary>
/// Initializes a <see cref="VarArgsList"/> to retrieve a variable number of arguments.
///
/// A function that invokes <see cref="VarArgs_Start"/> must also invoke <see cref="VarArgs_End"/> before it returns.
/// </summary>
/// <param name="args">An uninitialized <see cref="VarArgsList"/>.</param>
/// <param name="lastArg">
///     Name of the last named parameter in the function definition. The arguments extracted by subsequent calls to
///     <see cref="VarArg"/> are those after <paramref name="lastArg"/>.
/// </param>
#define VarArgs_Start(args, lastArg) va_start((args).List, lastArg)

/// <summary>
/// Destroys a <see cref="VarArgsList"/>.
/// </summary>
/// <param name="args">A <see cref="VarArgsList"/> previously initialized by <see cref="VarArgs_Start"/>.</param>
#define VarArgs_End(args) va_end((args).List)

/// <summary>
/// Retrieves the next argument from a <see cref="VarArgsList"/>.
/// </summary>
/// <param name="args">A <see cref="VarArgsList"/> previously initialized by <see cref="VarArgs_Start"/>.</param>
/// <param name="type">The type of the argument to retrieve.</param>
/// <returns>The value of the current variable argument as an expression of type <paramref name="type"/>.</returns>
#define VarArg(args, type) va_arg((args).List, type)

/* Types */
/// <summary>
/// Represents a variable arguments list.
/// </summary>
class VarArgsList {
public:
    /// <summary>
    /// Do not touch.
    /// </summary>
    va_list List;
};

#endif
