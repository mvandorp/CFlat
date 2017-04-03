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
 * @file TestSuiteResult.h
 */

#ifndef CFLAT_TESTING_TESTSUITERESULT_H
#define CFLAT_TESTING_TESTSUITERESULT_H

#include "CFlat/Language/Bool.h"
#include "CFlat/Testing/TestResult.h"

/* Forward declarations */
struct String;
struct TestSuite;
struct TestSuiteResult;

/* Types */
/// <summary>
/// Represents a test suite result. Extends <see cref="TestResult"/>.
/// </summary>
typedef struct TestSuiteResult TestSuiteResult;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="TestSuiteResult"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="TestSuiteResult"/> should be managed with retain() and release().
/// </remarks>
/// <param name="test">The <see cref="TestSuite"/> associated with the <see cref="TestSuiteResult"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
TestSuiteResult *TestSuiteResult_New(const struct TestSuite *test);

/// <summary>
/// Initializes a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to an uninitialized <see cref="TestSuiteResult"/>.</param>
/// <param name="test">The <see cref="TestSuite"/> associated with the <see cref="TestSuiteResult"/>.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="test"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TestSuiteResult_Constructor(TestSuiteResult *report, const struct TestSuite *test);

/// <summary>
/// Destroys a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestSuiteResult_Destructor(TestSuiteResult *report);

/* TestResult */
/// <summary>
/// Returns the number of passed test cases in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The number of passed test cases in the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override int TestSuiteResult_GetPassCount(const TestSuiteResult *result);

/// <summary>
/// Returns the number of failed test cases in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The number of failed test cases in the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override int TestSuiteResult_GetFailCount(const TestSuiteResult *result);

/// <summary>
/// Returns the number of skipped test cases in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The number of skipped test cases in the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override int TestSuiteResult_GetSkipCount(const TestSuiteResult *result);

/// <summary>
/// Returns the number of inconclusive test cases in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The number of inconclusive test cases in the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override int TestSuiteResult_GetInconclusiveCount(const TestSuiteResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the passed test cases in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the passed test cases in the <see cref="TestSuiteResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestSuiteResult_CopyPassedTests(const TestSuiteResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the failed test cases in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the failed test cases in the <see cref="TestSuiteResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestSuiteResult_CopyFailedTests(const TestSuiteResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the skipped test cases in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the skipped test cases in the <see cref="TestSuiteResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestSuiteResult_CopySkippedTests(const TestSuiteResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the inconclusive test cases in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the inconclusive test cases in the <see cref="TestSuiteResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestSuiteResult_CopyInconclusiveTests(const TestSuiteResult *result);

/// <summary>
/// Gets the children of a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the children of the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestSuiteResult_GetChildren(const TestSuiteResult *result);

/// <summary>
/// Returns whether or not a <see cref="TestSuiteResult"/> has children.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>
///     <see cref="true"/> if the test result has children; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override bool TestSuiteResult_HasChildren(const TestSuiteResult *result);

/// <summary>
/// Returns whether or not a <see cref="TestSuiteResult"/> is a <see cref="TestSuiteResult"/>.
/// </summary>
/// <remarks>Returns <see cref="true"/>.</remarks>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="result"/> is a <see cref="TestSuiteResult"/>;
///     otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override bool TestSuiteResult_IsSuiteResult(const TestSuiteResult *result);

/// <summary>
/// Adds a given test result as the child of a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <param name="childResult">The <see cref="TestSuiteResult"/> to add as a child.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="childResult"/> is <see cref="null"/>.
/// </exception>
override void TestSuiteResult_AddChildResult(TestSuiteResult *result, TestResult *childResult);

/// <summary>
/// Returns whether or not children can be added to a <see cref="TestSuiteResult"/>.
/// </summary>
/// <remarks>Returns <see cref="true"/>.</remarks>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>
///     <see cref="true"/> if children can be added to the test result; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
bool TestSuiteResult_CanAddChildren(const TestSuiteResult *result);

/// <summary>
/// Returns the number of test cases in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The number of test cases in the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
int TestSuiteResult_GetTestSuiteCount(const TestSuiteResult *result);

/// <summary>
/// Returns the number of test cases ran in a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The number of test cases ran in the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
int TestSuiteResult_GetRunCount(const TestSuiteResult *result);

/// <summary>
/// Gets the <see cref="Test"/> with which a <see cref="TestSuiteResult"/> is associated.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The <see cref="Test"/> with which the <see cref="TestSuiteResult"/> is associated.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct Test *TestSuiteResult_GetTest(const TestSuiteResult *result);

/// <summary>
/// Gets the name of a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The name of the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct String *TestSuiteResult_GetName(const TestSuiteResult *result);

/// <summary>
/// Gets the fully qualified name of a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The fully qualified name of the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct String *TestSuiteResult_GetFullName(const TestSuiteResult *result);

/// <summary>
/// Gets the parent of a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>The parent of the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const TestResult *TestSuiteResult_GetParent(const TestSuiteResult *result);

/// <summary>
/// Returns the time it took to run the tests associated with a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to an <see cref="TestSuiteResult"/>.</param>
/// <returns>The time it took to run the tests associated with a <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
double TestSuiteResult_GetDuration(const TestSuiteResult *result);

/// <summary>
/// Gets the <see cref="CFlatException"/> associated with a skipped, failed, inconclusive or forcibly passed test.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <returns>
///     The <see cref="CFlatException"/> associated with a skipped, failed, inconclusive or forcibly passed test;
///     or <see cref="null"/> if the test passed and no exception occured or the exception message was empty.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct CFlatException *TestSuiteResult_GetException(const TestSuiteResult *result);

/// <summary>
/// Returns the result of a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <returns>The result of the <see cref="TestSuiteResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
TestStatus TestSuiteResult_GetResult(const TestSuiteResult *result);

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
const struct String *TestSuiteResult_GetStandardOutput(const TestSuiteResult *result);

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
const struct String *TestSuiteResult_GetStandardError(const TestSuiteResult *result);

/// <summary>
/// Sets the parent of a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <param name="parent>The parent of the <see cref="TestSuiteResult"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestSuiteResult_SetParent(TestSuiteResult *result, const TestResult *parent);

/// <summary>
/// Sets the time it took to run the tests associated with a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to an <see cref="TestSuiteResult"/>.</param>
/// <param name="duration>The time it took to run the tests.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException"><paramref name="duration"/> is negative.</exception>
void TestSuiteResult_SetDuration(TestSuiteResult *result, double duration);

/// <summary>
/// Sets the result of a <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <param name="status>The result of the test.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestSuiteResult_SetResult(TestSuiteResult *result, TestStatus status);

/// <summary>
/// Sets the output to the standard output stream captured while running the tests associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <param name="output">The output captured while running the tests.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestSuiteResult_SetStandardOutput(const TestSuiteResult *result, const struct String *output);

/// <summary>
/// Sets the output to the standard error stream captured while running the tests associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <param name="output">The output captured while running the tests.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestSuiteResult_SetStandardError(const TestSuiteResult *result, const struct String *output);

/// <summary>
/// Records a <see cref="CFlatException"/> that was thrown while running a test associated with a
/// <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <param name="exception">A <see cref="CFlatException"/> that was thrown while running a test.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="exception"/> is <see cref="null"/>.
/// </exception>
void TestSuiteResult_RecordException(TestSuiteResult *result, const struct CFlatException *exception);

/// <summary>
/// Records a <see cref="CFlatException"/> that was thrown during the setup of a test associated with a
/// <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <param name="exception">A <see cref="CFlatException"/> that was thrown during the setup.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="exception"/> is <see cref="null"/>.
/// </exception>
void TestSuiteResult_RecordSetUpException(TestSuiteResult *result, const struct CFlatException *exception);

/// <summary>
/// Records a <see cref="CFlatException"/> that was thrown during the teardown of a test associated with a
/// <see cref="TestSuiteResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestSuiteResult"/>.</param>
/// <param name="exception">A <see cref="CFlatException"/> that was thrown during the teardown.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="exception"/> is <see cref="null"/>.
/// </exception>
void TestSuiteResult_RecordTearDownException(TestSuiteResult *result, const struct CFlatException *exception);

#endif
