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

//! @file Validate.h
/// <summary>
/// Provides convenience functions for validating parameters and the state of objects.
/// </summary>

#ifndef CFLAT_CORE_ARGUMENT_H
#define CFLAT_CORE_ARGUMENT_H

#include "CFlat/Language/Exceptions.h"

/// <summary>
/// Validates that the specified condition is true; otherwise throws an exception of the given
/// <see cref="ExceptionType"/>.
/// </summary>
/// <param name="condition">The condition to check.</param>
/// <param name="exception">The <see cref="ExceptionType"/> to throw.</param>
/// <param name="message">
///     Pointer to a null-terminated string describing the exception, or <see cref="null"/> to use the default
///     exception message.
/// </param>
#define Validate_IsTrue(condition, exception, message) \
    ((void)((condition) ? 0 : (throw_new(exception, message), 0)))

/// <summary>
/// Validates that the specified argument is not <see cref="null"/>; otherwise throws an
/// <see cref="ArgumentNullException"/>.
/// </summary>
/// <param name="param">The object to check, this should be a parameter.</param>
/// <exception cref="::ArgumentNullException"><paramref name="param"/> is <see cref="null"/>.</exception>
#define Validate_NotNull(param) \
    Validate_IsTrue((param) != null, ArgumentNullException, "Parameter '" #param "' cannot be null.")

/// <summary>
/// Validates that the specified condition involving the state of an object is true; otherwise throws an
/// <see cref="InvalidOperationException"/>.
/// </summary>
/// <param name="condition">The condition to check.</param>
/// <param name="message">
///     Pointer to a null-terminated string describing the exception, or <see cref="null"/> to use the default
///     exception message.
/// </param>
/// <exception cref="::InvalidOperationException"><paramref name="condition"/> is <see cref="false"/>.</exception>
#define Validate_State(condition, message) \
    Validate_IsTrue((condition), InvalidOperationException, message)

#endif
