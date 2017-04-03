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
 * @file TestSuite.h
 */

#ifndef CFLAT_TESTING_TESTSUITE_H
#define CFLAT_TESTING_TESTSUITE_H

#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Functions.h"
#include "CFlat/Testing/Test.h"

/* Forward declarations */
struct IEnumerable;
struct ITestListener;
struct String;
struct TestResult;

/* Types */
/// <summary>
/// Represents a test suite. Extends <see cref="Test"/>.
/// </summary>
typedef struct TestSuite TestSuite;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="TestSuite"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="TestSuite"/> should be managed with retain() and release().
/// </remarks>
/// <param name="name">The name of the <see cref="TestSuite"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="TestSuite"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="name"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
TestSuite *TestSuite_New(const char *name);

/// <summary>
/// Initializes a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to an uninitialized <see cref="TestSuite"/>.</param>
/// <param name="name">The name of the <see cref="TestSuite"/>.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="suite"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="name"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TestSuite_Constructor(TestSuite *suite, const char *name);

/// <summary>
/// Destroys a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
void TestSuite_Destructor(TestSuite *suite);

/// <summary>
/// Adds a <see cref="Test"/> to a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <param name="test">The <see cref="Test"/> to add to the suite.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="suite"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="test"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TestSuite_Add(TestSuite *suite, struct Test *test);

/// <summary>
/// Adds a test case to a <see cref="TestSuite"/>.
/// </summary>
/// <remarks>
///     The stringized value of <paramref name="testFunction"/> will be used as name.
///     Use <see cref="TestSuite_AddNamedTestCase()"/> to provide a custom name.
/// </remarks>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <param name="testFunction">The <see cref="Action"/> that is the test function.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="suite"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="testFunction"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
#define TestSuite_AddTestCase(suite, testFunction) TestSuite_AddNamedTestCase(suite, #testFunction, testFunction)

/// <summary>
/// Adds a test case to a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <param name="name">The name of the test case.</param>
/// <param name="testFunction">The <see cref="Action"/> that is the test function.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="suite"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="name"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="testFunction"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TestSuite_AddNamedTestCase(TestSuite *suite, const char *name, Action testFunction);

/// <summary>
/// Sets the setup function of a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <param name="setUp">The <see cref="Action"/> that is the setup function; or <see cref="null"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
void TestSuite_SetSetUpFunction(TestSuite *suite, Action setUp);

/// <summary>
/// Sets the teardown function of a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <param name="tearDown">The <see cref="Action"/> that is the teardown function; or <see cref="null"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
void TestSuite_SetTearDownFunction(TestSuite *suite, Action tearDown);

/* Test */
/// <summary>
/// Gets the name of a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <returns>The name of the <see cref="TestSuite"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
const struct String *TestSuite_GetName(const TestSuite *test);

/// <summary>
/// Gets the fully qualified name of a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <returns>The fully qualified name of the <see cref="TestSuite"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
const struct String *TestSuite_GetFullName(const TestSuite *test);

/// <summary>
/// Gets the parent of a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <returns>The parent of the <see cref="TestSuite"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
Test *TestSuite_GetParent(const TestSuite *test);

/// <summary>
/// Sets the parent of a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <param name="parent">The parent of the <see cref="TestSuite"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
void TestSuite_SetParent(TestSuite *test, Test *parent);

/// <summary>
/// Gets the children of a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the children of the <see cref="TestSuite"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestSuite_GetChildren(const TestSuite *test);

/// <summary>
/// Returns whether or not a <see cref="TestSuite"/> has children.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <returns>
///     <see cref="true"/> if the test has children; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
override bool TestSuite_HasChildren(const TestSuite *test);

/// <summary>
/// Returns whether or not a <see cref="TestSuite"/> is a <see cref="TestSuite"/>.
/// </summary>
/// <remarks>Returns <see cref="true"/>.</remarks>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <returns>
///     <see cref="true"/> if the test is a <see cref="TestSuite"/>, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
override bool TestSuite_IsSuite(const TestSuite *test);

/// <summary>
/// Counts the number of test cases contained in a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <returns>The number of test cases contained in the <see cref="TestSuite"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
override int TestSuite_GetTestCaseCount(const TestSuite *test);

/// <summary>
/// Creates a <see cref="TestResult"/> for a <see cref="TestSuite"/>.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <returns>A <see cref="TestResult"/> for the <see cref="TestSuite"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
override struct TestResult *TestSuite_CreateResult(const TestSuite *test);

/// <summary>
/// Runs a <see cref="TestSuite"/> and collects its result in a <see cref="TestResult"/> instance.
/// </summary>
/// <remarks>
///     This operation might throw a <see cref="ArgumentException"/> unless <paramref name="result"/> is created with
///     <see cref="Test_CreateResult()"/> using the same <see cref="Test"/> instance.
/// </remarks>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <param name="result">The <see cref="TestResult"/> used to collect the results of this run.</param>
/// <param name="listener">
///     A <see cref="ITestListener"/> that listens to the execution of tests; or <see cref="null"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="suite"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="result"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
override void TestSuite_RunInternal(const TestSuite *test, struct TestResult *result, struct ITestListener *listener);

/// <summary>
/// Runs a <see cref="TestSuite"/> and returns its result in a <see cref="TestResult"/> instance.
/// </summary>
/// <param name="suite">Pointer to a <see cref="TestSuite"/>.</param>
/// <param name="listener">
///     A <see cref="ITestListener"/> that listens to the execution of tests; or <see cref="null"/>.
/// </param>
/// <returns>A new <see cref="TestResult"/> containing the results of the test run.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="suite"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct TestResult *TestSuite_Run(const TestSuite *test, struct ITestListener *listener);

#endif
