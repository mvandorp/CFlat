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
 * @file ConsoleTestRunner.h
 */

#ifndef CFLAT_TESTING_CONSOLETESTRUNNER_H
#define CFLAT_TESTING_CONSOLETESTRUNNER_H

#include "CFlat/Language/Bool.h"

/* Forward declarations */
struct Test;

/* Functions */
/// <summary>
/// Runs the given tests and prints the results to the console.
/// </summary>
/// <param name="argc">The number of command line arguments.</param>
/// <param name="argv">The command line parameters.</param>
/// <param name="test">The test to run.</param>
/// <return><see cref="true"/> if the test run was succesful; otherwise <see cref="false"/>.</return>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
bool ConsoleTestRunner_Run(int argc, char *argv[], const struct Test *test);

#endif
