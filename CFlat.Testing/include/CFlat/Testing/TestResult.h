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
 * @file TestResult.h
 */

#ifndef CFLAT_TESTING_TESTRESULT_H
#define CFLAT_TESTING_TESTRESULT_H

#include "CFlat/Object.h"
#include "CFlat/Language/Bool.h"
#include "CFlat/Testing/TestStatus.h"
#include "CFlat/Language/Keywords.h"

/* Forward declarations */
struct CFlatException;
struct IEnumerable;
struct IList;
struct ITestListener;
struct String;
struct Test;
struct TestOutput;

/* Macros */
/// <summary>
/// Initializer for a <see cref="TestResultVTable"/>.
/// </summary>
/// <param name="destructor">A <see cref="DestructorFunc"/>.</param>
/// <param name="getPassCount">A <see cref="TestResult_GetPassCountFunc"/>.</param>
/// <param name="getFailCount">A <see cref="TestResult_GetFailCountFunc"/>.</param>
/// <param name="getSkipCount">A <see cref="TestResult_GetSkipCountFunc"/>.</param>
/// <param name="getInconclusiveCount">A <see cref="TestResult_GetInconclusiveCountFunc"/>.</param>
/// <param name="copyPassedTests">A <see cref="TestResult_CopyPassedTestsFunc"/>.</param>
/// <param name="copyFailedTests">A <see cref="TestResult_CopyFailedTestsFunc"/>.</param>
/// <param name="copySkippedTests">A <see cref="TestResult_CopySkippedTestsFunc"/>.</param>
/// <param name="copyInconclusiveTests">A <see cref="TestResult_CopyInconclusiveTestsFunc"/>.</param>
/// <param name="getChildren">A <see cref="TestResult_GetChildrenFunc"/>.</param>
/// <param name="hasChildren">A <see cref="TestResult_HasChildrenFunc"/>.</param>
/// <param name="isSuiteResult">A <see cref="TestResult_IsSuiteResultFunc"/>.</param>
/// <param name="addChildResult">A <see cref="TestResult_AddChildResultFunc"/>.</param>
#define TestResultVTable_Initializer(       \
    destructor,                             \
    getPassCount,                           \
    getFailCount,                           \
    getSkipCount,                           \
    getInconclusiveCount,                   \
    copyPassedTests,                        \
    copyFailedTests,                        \
    copySkippedTests,                       \
    copyInconclusiveTests,                  \
    getChildren,                            \
    hasChildren,                            \
    isSuiteResult,                          \
    addChildResult)                         \
{                                           \
    ObjectVTable_Initializer(destructor),   \
    getPassCount,                           \
    getFailCount,                           \
    getSkipCount,                           \
    getInconclusiveCount,                   \
    copyPassedTests,                        \
    copyFailedTests,                        \
    copySkippedTests,                       \
    copyInconclusiveTests,                  \
    getChildren,                            \
    hasChildren,                            \
    isSuiteResult,                          \
    addChildResult                          \
}

/* Types */
/// <summary>
/// Base class for a test result.
/// </summary>
typedef struct TestResult {
    /// <summary>
    /// The base class of <see cref="TestResult"/>.
    /// </summary>
    Object Base;

    /// <summary>
    /// The <see cref="Test"/> associated with the <see cref="TestResult"/>.
    /// </summary>
    const struct Test *Test;

    /// <summary>
    /// The parent of the <see cref="TestResult"/>.
    /// </summary>
    const struct TestResult *Parent;

    /// <summary>
    /// The output to the standard output stream captured while running the tests associated with the
    /// <see cref="TestResult"/>.
    /// </summary>
    const struct String *StandardOutput;

    /// <summary>
    /// The output to the standard error stream captured while running the tests associated with the
    /// <see cref="TestResult"/>.
    /// </summary>
    const struct String *StandardError;

    /// <summary>
    /// The <see cref="CFlatException"/> associated with a skipped, failed, inconclusive or forcibly passed test.
    /// </summary>
    const struct CFlatException *Exception;

    /// <summary>
    /// The time it took to run the tests associated with the <see cref="TestResult"/>.
    /// </summary>
    double Duration;

    /// <summary>
    /// The result of the <see cref="TestResult"/>.
    /// </summary>
    TestStatus ResultStatus;
} TestResult;

/// <summary>
/// A function that returns the number of passed test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of passed test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef int (*TestResult_GetPassCountFunc)(const TestResult *result);

/// <summary>
/// A function that returns the number of failed test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of failed test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef int (*TestResult_GetFailCountFunc)(const TestResult *result);

/// <summary>
/// A function that returns the number of skipped test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of skipped test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef int (*TestResult_GetSkipCountFunc)(const TestResult *result);

/// <summary>
/// A function that returns the number of inconclusive test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of inconclusive test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef int (*TestResult_GetInconclusiveCountFunc)(const TestResult *result);

/// <summary>
/// A function that returns a new <see cref="IEnumerable"/> containing the passed test cases in a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>A new <see cref="IEnumerable"/> containing the passed test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef struct IEnumerable *(*TestResult_CopyPassedTestsFunc)(const TestResult *result);

/// <summary>
/// A function that returns a new <see cref="IEnumerable"/> containing the failed test cases in a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>A new <see cref="IEnumerable"/> containing the failed test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef struct IEnumerable *(*TestResult_CopyFailedTestsFunc)(const TestResult *result);

/// <summary>
/// A function that returns a new <see cref="IEnumerable"/> containing the skipped test cases in a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the skipped test cases in the <see cref="TestResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef struct IEnumerable *(*TestResult_CopySkippedTestsFunc)(const TestResult *result);

/// <summary>
/// A function that returns a new <see cref="IEnumerable"/> containing the inconclusive test cases in a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the inconclusive test cases in the <see cref="TestResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef struct IEnumerable *(*TestResult_CopyInconclusiveTestsFunc)(const TestResult *result);

/// <summary>
/// A function that returns the children of a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the children of the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef struct IEnumerable *(*TestResult_GetChildrenFunc)(const TestResult *result);

/// <summary>
/// A function that returns whether or not a <see cref="TestResult"/> has children.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     <see cref="true"/> if the test result has children; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef bool (*TestResult_HasChildrenFunc)(const TestResult *result);

/// <summary>
/// A function that returns whether or not children can be added to a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     <see cref="true"/> if children can be added to the test result; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
typedef bool (*TestResult_IsSuiteResultFunc)(const TestResult *result);

/// <summary>
/// A function that adds a given test result as the child of a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <param name="childResult">The <see cref="TestResult"/> to add as a child.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="childResult"/> is <see cref="null"/>.
/// </exception>
typedef void (*TestResult_AddChildResultFunc)(TestResult *result, TestResult *childResult);

/// <summary>
/// A virtual method table for the <see cref="TestResult"/> class.
/// </summary>
typedef struct TestResultVTable {
    /// <summary>
    /// The virtual method table of the base class of <see cref="TestResult"/>.
    /// </summary>
    ObjectVTable Base;

    /// <summary>
    /// A function that returns the number of passed test cases in a <see cref="TestResult"/>.
    /// </summary>
    TestResult_GetPassCountFunc GetPassCount;

    /// <summary>
    /// A function that returns the number of failed test cases in a <see cref="TestResult"/>.
    /// </summary>
    TestResult_GetFailCountFunc GetFailCount;

    /// <summary>
    /// A function that returns the number of skipped test cases in a <see cref="TestResult"/>.
    /// </summary>
    TestResult_GetSkipCountFunc GetSkipCount;

    /// <summary>
    /// A function that returns the number of inconclusive test cases in a <see cref="TestResult"/>.
    /// </summary>
    TestResult_GetInconclusiveCountFunc GetInconclusiveCount;

    /// <summary>
    /// A function that returns a new <see cref="IEnumerable"/> containing the passed test cases in a
    /// <see cref="TestResult"/>.
    /// </summary>
    TestResult_CopyPassedTestsFunc CopyPassedTests;

    /// <summary>
    /// A function that returns a new <see cref="IEnumerable"/> containing the failed test cases in a
    /// <see cref="TestResult"/>.
    /// </summary>
    TestResult_CopyFailedTestsFunc CopyFailedTests;

    /// <summary>
    /// A function that returns a new <see cref="IEnumerable"/> containing the skipped test cases in a
    /// <see cref="TestResult"/>.
    /// </summary>
    TestResult_CopySkippedTestsFunc CopySkippedTests;

    /// <summary>
    /// A function that returns a new <see cref="IEnumerable"/> containing the inconclusive test cases in a
    /// <see cref="TestResult"/>.
    /// </summary>
    TestResult_CopyInconclusiveTestsFunc CopyInconclusiveTests;

    /// <summary>
    /// A function that returns the children of a <see cref="TestResult"/>.
    /// </summary>
    TestResult_GetChildrenFunc GetChildren;

    /// <summary>
    /// A function that returns whether or not a <see cref="TestResult"/> has children.
    /// </summary>
    TestResult_HasChildrenFunc HasChildren;

    /// <summary>
    /// A function that returns whether or not children can be added to a <see cref="TestResult"/>.
    /// </summary>
    TestResult_IsSuiteResultFunc IsSuiteResult;

    /// <summary>
    /// A function that adds a given test result as the child of a <see cref="TestResult"/>.
    /// </summary>
    TestResult_AddChildResultFunc AddChildResult;
} TestResultVTable;

/* Functions */
/// <summary>
/// Initializes a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to an uninitialized <see cref="TestResult"/>.</param>
/// <param name="test">The <see cref="Test"/> associated with the <see cref="TestResult"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="test"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> contains a <see cref="null"/> pointer.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TestResult_Constructor(TestResult *result, const struct Test *test, const TestResultVTable *vtable);

/// <summary>
/// Destroys a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestResult_Destructor(TestResult *result);

/// <summary>
/// Returns the number of passed test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of passed test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract int TestResult_GetPassCount(const TestResult *result);

/// <summary>
/// Returns the number of failed test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of failed test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract int TestResult_GetFailCount(const TestResult *result);

/// <summary>
/// Returns the number of skipped test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of skipped test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract int TestResult_GetSkipCount(const TestResult *result);

/// <summary>
/// Returns the number of inconclusive test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of inconclusive test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract int TestResult_GetInconclusiveCount(const TestResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the passed test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>A new <see cref="IEnumerable"/> containing the passed test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract struct IEnumerable *TestResult_CopyPassedTests(const TestResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the failed test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>A new <see cref="IEnumerable"/> containing the failed test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract struct IEnumerable *TestResult_CopyFailedTests(const TestResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the skipped test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the skipped test cases in the <see cref="TestResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract struct IEnumerable *TestResult_CopySkippedTests(const TestResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the inconclusive test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the inconclusive test cases in the <see cref="TestResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract struct IEnumerable *TestResult_CopyInconclusiveTests(const TestResult *result);

/// <summary>
/// Gets the children of a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the children of the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract struct IEnumerable *TestResult_GetChildren(const TestResult *result);

/// <summary>
/// Returns whether or not a <see cref="TestResult"/> has children.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     <see cref="true"/> if the test result has children; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract bool TestResult_HasChildren(const TestResult *result);

/// <summary>
/// Returns whether or not a <see cref="TestResult"/> is a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="result"/> is a <see cref="TestSuiteResult"/>;
///     otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
abstract bool TestResult_IsSuiteResult(const TestResult *result);

/// <summary>
/// Adds a given test result as the child of a <see cref="TestResult"/>.
/// </summary>
/// <remarks>
///     Use <see cref="TestResult_CanAddChildren()"/> to determine whether the test results supports adding child
///     results.
/// </remarks>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <param name="childResult">The <see cref="TestResult"/> to add as a child.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="childResult"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::NotSupportedException">
///     <see cref="TestCaseResult_CanAddChildren"/> returned <see cref="false"/>.
/// </exception>
abstract void TestResult_AddChildResult(TestResult *result, TestResult *childResult);

/// <summary>
/// Returns whether or not children can be added to a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     <see cref="true"/> if children can be added to the test result; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
bool TestResult_CanAddChildren(const TestResult *result);

/// <summary>
/// Returns the number of test cases in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of test cases in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
int TestResult_GetTestCaseCount(const TestResult *result);

/// <summary>
/// Returns the number of test cases ran in a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The number of test cases ran in the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
int TestResult_GetRunCount(const TestResult *result);

/// <summary>
/// Gets the <see cref="Test"/> with which a <see cref="TestResult"/> is associated.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The <see cref="Test"/> with which the <see cref="TestResult"/> is associated.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct Test *TestResult_GetTest(const TestResult *result);

/// <summary>
/// Gets the name of a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The name of the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct String *TestResult_GetName(const TestResult *result);

/// <summary>
/// Gets the fully qualified name of a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The fully qualified name of the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct String *TestResult_GetFullName(const TestResult *result);

/// <summary>
/// Gets the parent of a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>The parent of the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const TestResult *TestResult_GetParent(const TestResult *result);

/// <summary>
/// Returns the time it took to run the tests associated with a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to an <see cref="TestResult"/>.</param>
/// <returns>The time it took to run the tests associated with a <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
double TestResult_GetDuration(const TestResult *result);

/// <summary>
/// Gets the <see cref="CFlatException"/> associated with a skipped, failed, inconclusive or forcibly passed test.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <returns>
///     The <see cref="CFlatException"/> associated with a skipped, failed, inconclusive or forcibly passed test;
///     or <see cref="null"/> if the test passed and no exception occured or the exception message was empty.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct CFlatException *TestResult_GetException(const TestResult *result);

/// <summary>
/// Returns the result of a <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <returns>The result of the <see cref="TestResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
TestStatus TestResult_GetResult(const TestResult *result);

/// <summary>
/// Gets the output to the standard output stream captured while running the tests associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <returns>
///     The output to the standard output stream captured while running the tests associated with a
///     <see cref="TestResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct String *TestResult_GetStandardOutput(const TestResult *result);

/// <summary>
/// Gets the output to the standard error stream captured while running the tests associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <returns>
///     The output to the standard error stream captured while running the tests associated with a
///     <see cref="TestResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct String *TestResult_GetStandardError(const TestResult *result);

/// <summary>
/// Sets the parent of a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <param name="parent>The parent of the <see cref="TestResult"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestResult_SetParent(TestResult *result, const TestResult *parent);

/// <summary>
/// Sets the time it took to run the tests associated with a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to an <see cref="TestResult"/>.</param>
/// <param name="duration>The time it took to run the tests.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException"><paramref name="duration"/> is negative.</exception>
void TestResult_SetDuration(TestResult *result, double duration);

/// <summary>
/// Sets the result of a <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <param name="status>The result of the test.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestResult_SetResult(TestResult *result, TestStatus status);

/// <summary>
/// Sets the output to the standard output stream captured while running the tests associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <param name="output">The output captured while running the tests.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestResult_SetStandardOutput(TestResult *result, const struct String *output);

/// <summary>
/// Sets the output to the standard error stream captured while running the tests associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <param name="output">The output captured while running the tests.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestResult_SetStandardError(TestResult *result, const struct String *output);

/// <summary>
/// Records a <see cref="CFlatException"/> that was thrown while running a test associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <param name="exception">A <see cref="CFlatException"/> that was thrown while running a test.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="exception"/> is <see cref="null"/>.
/// </exception>
void TestResult_RecordException(TestResult *result, const struct CFlatException *exception);

/// <summary>
/// Records a <see cref="CFlatException"/> that was thrown during the setup of a test associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <param name="exception">A <see cref="CFlatException"/> that was thrown during the setup.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="exception"/> is <see cref="null"/>.
/// </exception>
void TestResult_RecordSetUpException(TestResult *result, const struct CFlatException *exception);

/// <summary>
/// Records a <see cref="CFlatException"/> that was thrown during the teardown of a test associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <param name="exception">A <see cref="CFlatException"/> that was thrown during the teardown.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="exception"/> is <see cref="null"/>.
/// </exception>
void TestResult_RecordTearDownException(TestResult *result, const struct CFlatException *exception);

#endif
