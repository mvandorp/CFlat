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
 * @file Assert.h
 */

#ifndef CFLAT_CORE_LANGUAGE_ASSERT_H
#define CFLAT_CORE_LANGUAGE_ASSERT_H

#ifdef NDEBUG
    /// <summary>
    /// Checks for a condition; if the condition is <see cref="false"/>, prints a message and aborts the program.
    /// If the macro NDEBUG is defined before the inclusion of Assert.h, assertions are disabled and the conditions
    /// will not be evaluated.
    /// </summary>
    /// <param name="condition">The condition to evaluate.</param>
    #define assert(condition) ((void)0)
#else
    /// <summary>
    /// Prints an assertion failed message and aborts the program.
    /// </summary>
    /// <param name="condition">Pointer to a string representation of the condition.</param>
    /// <param name="file">Pointer to a string that contains the name of the file where the assertion failed.</param>
    /// <param name="line">The line number where the assertion failed.</param>
    /// <remarks>This function is intended for internal use only.</remarks>
    void __CFLAT_ASSERT_FAIL(const char *condition, const char *file, int line);

    /// <summary>
    /// Checks for a condition; if the condition is <see cref="false"/>, prints a message and aborts the program.
    /// If the macro NDEBUG is defined before the inclusion of Assert.h, assertions are disabled and the conditions
    /// will not be evaluated.
    /// </summary>
    /// <param name="condition">The condition to evaluate.</param>
    #define assert(condition) ((void)(!!(condition) || (__CFLAT_ASSERT_FAIL(#condition, __FILE__, __LINE__), 0)))
#endif

#endif
