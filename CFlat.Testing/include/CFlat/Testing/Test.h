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
 * @file Test.h
 */

#ifndef CFLAT_TESTING_TEST_H
#define CFLAT_TESTING_TEST_H

#include "CFlat/Object.h"
#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Keywords.h"

/* Forward declarations */
struct IEnumerable;
struct ITestListener;
struct TestResult;
struct String;

/* Macros */
/// <summary>
/// Initializer for a <see cref="TestVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="getChildren">A <see cref="Test_GetChildrenFunc"/>.</param>
/// <param name="hasChildren">A <see cref="Test_HasChildrenFunc"/>.</param>
/// <param name="isSuite">A <see cref="Test_IsSuiteFunc"/>.</param>
/// <param name="getTestCaseCount">A <see cref="Test_GetTestCaseCountFunc"/>.</param>
/// <param name="createResult">A <see cref="Test_CreateResultFunc"/>.</param>
/// <param name="runInternal">A <see cref="Test_RunInternalFunc"/>.</param>
#define TestVTable_Initializer(             \
    destructor,                             \
    getChildren,                            \
    hasChildren,                            \
    isSuite,                                \
    getTestCaseCount,                       \
    createResult,                           \
    runInternal)                            \
{                                           \
    ObjectVTable_Initializer(destructor),   \
    getChildren,                            \
    hasChildren,                            \
    isSuite,                                \
    getTestCaseCount,                       \
    createResult,                           \
    runInternal                             \
}

/* Types */
/// <summary>
/// Base class for a test.
/// </summary>
typedef struct Test {
    /// <summary>
    /// The base class of <see cref="Test"/>.
    /// </summary>
    Object Base;

    /// <summary>
    /// The name of the <see cref="Test"/>.
    /// </summary>
    const struct String *Name;

    /// <summary>
    /// The fully qualified name of the <see cref="Test"/>.
    /// </summary>
    const struct String *FullName;

    /// <summary>
    /// The parent of the <see cref="Test"/>.
    /// </summary>
    struct Test *Parent;
} Test;

/// <summary>
/// A function that returns the children of a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the children of the <see cref="Test"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
typedef struct IEnumerable *(*Test_GetChildrenFunc)(const Test *test);

/// <summary>
/// A function that returns whether or not a <see cref="Test"/> has children.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>
///     <see cref="true"/> if the test has children; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
typedef bool (*Test_HasChildrenFunc)(const Test *test);

/// <summary>
/// A function that returns whether or not a <see cref="Test"/> is a <see cref="TestSuite"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>
///     <see cref="true"/> if the test is a <see cref="TestSuite"/>, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
typedef bool (*Test_IsSuiteFunc)(const Test *test);

/// <summary>
/// A function that counts the number of test cases contained in a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>The number of test cases contained in the <see cref="Test"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
typedef int (*Test_GetTestCaseCountFunc)(const Test *test);

/// <summary>
/// A function that creates a <see cref="TestResult"/> for a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>A <see cref="TestResult"/> for the <see cref="Test"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
typedef struct TestResult *(*Test_CreateResultFunc)(const Test *test);

/// <summary>
/// A function that runs a <see cref="Test"/> and collects its result in a <see cref="TestResult"/> instance.
/// </summary>
/// <remarks>
///     This operation might throw a <see cref="ArgumentException"/> unless <paramref name="result"/> is created with
///     <see cref="Test_CreateResult()"/> using the same <see cref="Test"/> instance.
/// </remarks>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <param name="result">The <see cref="TestResult"/> used to collect the results of this run.</param>
/// <param name="listener">
///     A <see cref="ITestListener"/> that listens to the execution of tests; or <see cref="null"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="test"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="result"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
typedef void (*Test_RunInternalFunc)(const Test *test, struct TestResult *result, struct ITestListener *listener);

/// <summary>
/// A virtual method table for the <see cref="Test"/> class.
/// </summary>
typedef struct TestVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="Test"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that returns the children of a <see cref="Test"/>.
    /// </summary>
    Test_GetChildrenFunc GetChildren;

    /// <summary>
    /// A function that returns whether or not a <see cref="Test"/> has children.
    /// </summary>
    Test_HasChildrenFunc HasChildren;

    /// <summary>
    /// A function that returns whether or not a <see cref="Test"/> is a <see cref="TestSuite"/>.
    /// </summary>
    Test_IsSuiteFunc IsSuite;

    /// <summary>
    /// A function that counts the number of test cases contained in a <see cref="Test"/>.
    /// </summary>
    Test_GetTestCaseCountFunc GetTestCaseCount;

    /// <summary>
    /// A function that creates a <see cref="TestResult"/> for a <see cref="Test"/>.
    /// </summary>
    Test_CreateResultFunc CreateResult;

    /// <summary>
    /// A function that runs a <see cref="Test"/> and collects its result in a <see cref="TestResult"/> instance.
    /// </summary>
    Test_RunInternalFunc RunInternal;
} TestVTable;

/* Functions */
/// <summary>
/// Initializes a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to an uninitialized <see cref="Test"/>.</param>
/// <param name="name">The name of the <see cref="Test"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="test"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="name"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void Test_Constructor(
    Test *test,
    const char *name,
    const struct TestVTable *vtable);

/// <summary>
/// Destroys a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
void Test_Destructor(Test *test);

/// <summary>
/// Gets the name of a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>The name of the <see cref="Test"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
const struct String *Test_GetName(const Test *test);

/// <summary>
/// Gets the fully qualified name of a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>The fully qualified name of the <see cref="Test"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
const struct String *Test_GetFullName(const Test *test);

/// <summary>
/// Gets the parent of a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>The parent of the <see cref="Test"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
Test *Test_GetParent(const Test *test);

/// <summary>
/// Sets the parent of a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <param name="parent">The parent of the <see cref="Test"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
void Test_SetParent(Test *test, Test *parent);

/// <summary>
/// Gets the children of a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the children of the <see cref="Test"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
abstract struct IEnumerable *Test_GetChildren(const Test *test);

/// <summary>
/// Returns whether or not a <see cref="Test"/> has children.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>
///     <see cref="true"/> if the test has children; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
abstract bool Test_HasChildren(const Test *test);

/// <summary>
/// Returns whether or not a <see cref="Test"/> is a <see cref="TestSuite"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>
///     <see cref="true"/> if the test is a <see cref="TestSuite"/>, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
abstract bool Test_IsSuite(const Test *test);

/// <summary>
/// Counts the number of test cases contained in a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>The number of test cases contained in the <see cref="Test"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
abstract int Test_GetTestCaseCount(const Test *test);

/// <summary>
/// Creates a <see cref="TestResult"/> for a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <returns>A <see cref="TestResult"/> for the <see cref="Test"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
abstract struct TestResult *Test_CreateResult(const Test *test);

/// <summary>
/// Runs a <see cref="Test"/> and collects its result in a <see cref="TestResult"/> instance.
/// </summary>
/// <remarks>
///     This operation might throw a <see cref="ArgumentException"/> unless <paramref name="result"/> is created with
///     <see cref="Test_CreateResult()"/> using the same <see cref="Test"/> instance.
/// </remarks>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <param name="result">The <see cref="TestResult"/> used to collect the results of this run.</param>
/// <param name="listener">
///     A <see cref="ITestListener"/> that listens to the execution of tests; or <see cref="null"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="test"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="result"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
abstract void Test_RunInternal(const Test *test, struct TestResult *result, struct ITestListener *listener);

/// <summary>
/// Runs a <see cref="Test"/> and returns its result in a <see cref="TestResult"/> instance.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <param name="listener">
///     A <see cref="ITestListener"/> that listens to the execution of tests; or <see cref="null"/>.
/// </param>
/// <returns>A new <see cref="TestResult"/> containing the results of the test run.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
struct TestResult *Test_Run(const Test *test, struct ITestListener *listener);

#endif
