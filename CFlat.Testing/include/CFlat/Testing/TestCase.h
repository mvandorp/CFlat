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
 * @file TestCase.h
 */

#ifndef CFLAT_TESTING_TESTCASE_H
#define CFLAT_TESTING_TESTCASE_H

#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Keywords.h"
#include "CFlat/Testing/Test.h"

/* Forward declarations */
struct IEnumerable;
struct ITestListener;
struct String;
struct TestResult;

/* Types */
/// <summary>
/// Represents a test case. Extends <see cref="Test"/>.
/// </summary>
typedef struct TestCase TestCase;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="TestCase"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="TestCase"/> should be managed with retain() and release().
/// </remarks>
/// <param name="name">The name of the <see cref="TestCase"/>.</param>
/// <param name="testFunction">The <see cref="Action"/> that is the test function.</param>
/// <returns>A pointer to the newly allocated <see cref="TestCase"/>.</returns>
/// <exception cref="::ArgumentNullException">
///     <paramref name="name"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="testFunction"/> is <see cref="null"/>/.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
TestCase *TestCase_New(const char *name, Action testFunction);

/// <summary>
/// Initializes a <see cref="TestCase"/>.
/// </summary>
/// <param name="test">Pointer to an uninitialized <see cref="TestCase"/>.</param>
/// <param name="name">The name of the <see cref="TestCase"/>.</param>
/// <param name="testFunction">The <see cref="Action"/> that is the test function.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="test"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="name"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="testFunction"/> is <see cref="null"/>/.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TestCase_Constructor(TestCase *test, const char *name, Action testFunction);

/// <summary>
/// Destroys a <see cref="TestCase"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
void TestCase_Destructor(TestCase *test);

/* Test */
/// <summary>
/// Gets the name of a <see cref="TestCase"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <returns>The name of the <see cref="TestCase"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
const struct String *TestCase_GetName(const TestCase *test);

/// <summary>
/// Gets the fully qualified name of a <see cref="TestCase"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <returns>The fully qualified name of the <see cref="TestCase"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
const struct String *TestCase_GetFullName(const TestCase *test);

/// <summary>
/// Gets the parent of a <see cref="TestCase"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <returns>The parent of the <see cref="TestCase"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
Test *TestCase_GetParent(const TestCase *test);

/// <summary>
/// Sets the parent of a <see cref="TestCase"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <param name="parent">The parent of the <see cref="TestCase"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
void TestCase_SetParent(TestCase *test, Test *parent);

/// <summary>
/// Gets the children of a <see cref="TestCase"/>.
/// </summary>
/// <remarks>Returns <see cref="Enumerable_Empty()"/>.</remarks>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the children of the <see cref="TestCase"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestCase_GetChildren(const TestCase *test);

/// <summary>
/// Returns whether or not a <see cref="TestCase"/> has children.
/// </summary>
/// <remarks>Returns <see cref="false"/>.</remarks>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <returns>
///     <see cref="true"/> if the test has children; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
override bool TestCase_HasChildren(const TestCase *test);

/// <summary>
/// Returns whether or not a <see cref="TestCase"/> is a <see cref="TestSuite"/>.
/// </summary>
/// <remarks>Returns <see cref="false"/>.</remarks>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <returns>
///     <see cref="true"/> if the test is a <see cref="TestSuite"/>, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
override bool TestCase_IsSuite(const TestCase *test);

/// <summary>
/// Counts the number of test cases contained in a <see cref="TestCase"/>.
/// </summary>
/// <remarks>Returns 1.</remarks>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <returns>The number of test cases contained in the <see cref="TestCase"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
override int TestCase_GetTestCaseCount(const TestCase *test);

/// <summary>
/// Creates a <see cref="TestResult"/> for a <see cref="TestCase"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <returns>A <see cref="TestResult"/> for the <see cref="TestCase"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
override struct TestResult *TestCase_CreateResult(const TestCase *test);

/// <summary>
/// Runs a <see cref="TestCase"/> and collects its result in a <see cref="TestResult"/> instance.
/// </summary>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <param name="result">The <see cref="TestResult"/> used to collect the results of this run.</param>
/// <param name="listener">
///     A <see cref="ITestListener"/> that listens to the execution of tests; or <see cref="null"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="test"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="result"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
override void TestCase_RunInternal(const TestCase *test, struct TestResult *result, struct ITestListener *listener);

/// <summary>
/// Runs a <see cref="TestCase"/> and returns its result in a <see cref="TestResult"/> instance.
/// </summary>
/// <param name="test">Pointer to a <see cref="TestCase"/>.</param>
/// <param name="listener">
///     A <see cref="ITestListener"/> that listens to the execution of tests; or <see cref="null"/>.
/// </param>
/// <returns>A new <see cref="TestResult"/> containing the results of the test run.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct TestResult *TestCase_Run(const TestCase *test, struct ITestListener *listener);

#endif
