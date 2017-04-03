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
 * @file ITestListener.h
 */

#ifndef CFLAT_TESTING_ITESTLISTENER_H
#define CFLAT_TESTING_ITESTLISTENER_H

#include "CFlat/Object.h"

/* Forward declarations */
struct Test;
struct TestResult;

/* Macros */
/// <summary>
/// Initializer for an <see cref="ITestListenerVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="testStarted">An <see cref="ITestListener_TestStartedFunc"/>.</param>
/// <param name="testFinished">An <see cref="ITestListener_TestFinishedFunc"/>.</param>
/// <param name="testOutput">An <see cref="ITestListener_TestOutputFunc"/>.</param>
#define ITestListenerVTable_Initializer(    \
    destructor,                             \
    testStarted,                            \
    testFinished)                           \
{                                           \
    ObjectVTable_Initializer(destructor),   \
    testStarted,                            \
    testFinished                            \
}

/* Types */
/// <summary>
/// Base class for a test listener.
/// </summary>
typedef struct ITestListener {
    /// <summary>
    /// The base class of <see cref="ITestListener"/>.
    /// </summary>
    Object Base;
} ITestListener;

/// <summary>
/// A function that is called when a test is starting.
/// </summary>
/// <param name="listener">Pointer to an <see cref="ITestListener"/>.</param>
/// <param name="test">The test that is starting.</param>
/// <exception cref="::AssertionException"><paramref name="listener"/> is <see cref="null"/>.</exception>
typedef void (*ITestListener_TestStartedFunc)(ITestListener *listener, const struct Test *test);

/// <summary>
/// A function that is called when a test is finished.
/// </summary>
/// <param name="listener">Pointer to an <see cref="ITestListener"/>.</param>
/// <param name="result">The test result of the test that finished.</param>
/// <exception cref="::AssertionException"><paramref name="listener"/> is <see cref="null"/>.</exception>
typedef void (*ITestListener_TestFinishedFunc)(ITestListener *listener, const struct TestResult *result);

/// <summary>
/// A virtual method table for the <see cref="ITestListener"/> class.
/// </summary>
typedef struct ITestListenerVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="ITestListener"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that is called when a test is starting.
    /// </summary>
    ITestListener_TestStartedFunc TestStarted;

    /// <summary>
    /// A function that is called when a test is finished.
    /// </summary>
    ITestListener_TestFinishedFunc TestFinished;
} ITestListenerVTable;

/* Functions */
/// <summary>
/// Initializes an <see cref="ITestListener"/>.
/// </summary>
/// <param name="listener">Pointer to an uninitialized <see cref="ITestListener"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="listener"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
void ITestListener_Constructor(
    ITestListener *listener,
    const struct ITestListenerVTable *vtable);

/// <summary>
/// Called when a test is starting.
/// </summary>
/// <param name="listener">Pointer to an <see cref="ITestListener"/>.</param>
/// <param name="test">The test that is starting.</param>
/// <exception cref="::AssertionException"><paramref name="listener"/> is <see cref="null"/>.</exception>
void ITestListener_TestStarted(ITestListener *listener, const struct Test *test);

/// <summary>
/// Called when a test is finished.
/// </summary>
/// <param name="listener">Pointer to an <see cref="ITestListener"/>.</param>
/// <param name="result">The test result of the test that finished.</param>
/// <exception cref="::AssertionException"><paramref name="listener"/> is <see cref="null"/>.</exception>
void ITestListener_TestFinished(ITestListener *listener, const struct TestResult *result);

#endif
