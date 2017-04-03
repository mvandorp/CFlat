/*
 * Copyright (C) 2017 Martijn van Dorp
 *
 * This file is part of CFlat.Testing.
 *
 * CFlat.Testing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFlat.Testing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file TestStatus.h
 */

#ifndef CFLAT_TESTING_TESTSTATUS_H
#define CFLAT_TESTING_TESTSTATUS_H

#include "CFlat/Language/Bool.h"

/* Forward declarations */
struct String;

/* Types */
/// <summary>
/// Represents the result of running a test.
/// </summary>
typedef enum TestStatus {
    /// <summary>
    /// The test was inconclusive.
    /// </summary>
    TestStatus_Inconclusive,

    /// <summary>
    /// The test was successful.
    /// </summary>
    TestStatus_Success,

    /// <summary>
    /// The test failed.
    /// </summary>
    TestStatus_Failure,

    /// <summary>
    /// An error occurred during the test.
    /// </summary>
    TestStatus_Error,

    /// <summary>
    /// The test was skipped.
    /// </summary>
    TestStatus_Skipped
} TestStatus;

/* Functions */
/// <summary>
/// Determines whether or not <paramref name="status"/> is a valid <see cref="TestStatus"/>.
/// </summary>
/// <param name="status">The <see cref="TestStatus"/> to validate.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="status"/> is a valid <see cref="TestStatus"/>;
///     otherwise <see cref="false"/>.
/// </returns>
bool TestStatus_IsValid(TestStatus status);

/// <summary>
/// Validates that <paramref name="status"/> is a valid <see cref="TestStatus"/>.
/// </summary>
/// <param name="status">The <see cref="TestStatus"/> to validate.</param>
/// <exception cref="::ArgumentException"><paramref name="status"/> is not a valid <see cref="TestStatus"/>.</exception>
void TestStatus_Validate(TestStatus status);

/// <summary>
/// Returns a string that represents the given <see cref="TestStatus"/>.
/// </summary>
/// <param name="status">The <see cref="TestStatus"/> to convert to a string.</param>
/// <returns>The string representation of the given test status.</returns>
/// <exception cref="::ArgumentException"><paramref name="status"/> is not a valid <see cref="TestStatus"/>.</exception>
const struct String *TestStatus_ToString(TestStatus status);

#endif
