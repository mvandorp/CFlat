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

//! @file Environment.h

#ifndef CFLAT_CORE_ENVIRONMENT_H
#define CFLAT_CORE_ENVIRONMENT_H

#include "CFlat/Event.h"

/* Types */
/// <summary>
/// A function that performs clean up of static resources.
/// </summary>
typedef void(*StaticDestructorFunc)(void);

/* Events */
/// <summary>
/// Occurs when the process is about to exit.
/// </summary>
extern Event Environment_AtExit;

/// <summary>
/// Occurs when an exception is thrown, before the runtime searches the call stack for an exception handler.
/// </summary>
extern Event Environment_FirstChanceException;

/// <summary>
/// Occurs when an exception is not caught.
/// </summary>
extern Event Environment_UnhandledException;

/* Functions */
/// <summary>
/// Initializes the environment. To ensure proper cleanup, this function must be called before <c>main()</c> returns.
/// </summary>
/// <remarks>
///     The environment is automatically initialized when any of the other <c>Environment</c> functions are used. If an
///     unhandled exception occurs, the environment is also automatically initialized before the process terminates.
/// </remarks>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Environment_Initialize(void);

/// <summary>
/// Exits the process and returns the given exit code to the operating system.
/// </summary>
/// <param name="exitCode">The exit code to return to the operating system.</param>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Environment_Exit(int exitCode);

/// <summary>
/// Terminates the process and signals failure to the operating system.
/// </summary>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Environment_FailFast(void);

/// <summary>
/// Registers a static destructor that will be called before the process exits.
/// </summary>
/// <param name="dtor">A <see cref="StaticDestructorFunc"/> that is called before the process exits.</param>
/// <exception cref="::ArgumentNullException"><paramref name="dtor"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Environment_RegisterStaticDestructor(StaticDestructorFunc dtor);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/Environment.internal.h"
#endif

#endif
