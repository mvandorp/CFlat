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
 * @file TestCaseResult.h
 */

#ifndef CFLAT_TESTING_TESTCASERESULT_H
#define CFLAT_TESTING_TESTCASERESULT_H

#include "CFlat/Language/Bool.h"
#include "CFlat/Testing/TestResult.h"

/* Forward declarations */
struct String;
struct TestCase;
struct TestSuiteResult;

/* Types */
/// <summary>
/// Represents a test case result. Extends <see cref="TestResult"/>.
/// </summary>
typedef struct TestCaseResult TestCaseResult;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="TestCaseResult"/>.
/// </summary>
/// <remarks>
///     The lifetime of the <see cref="TestCaseResult"/> should be managed with retain() and release().
/// </remarks>
/// <param name="test">The <see cref="TestCase"/> associated with the <see cref="TestCaseResult"/>.</param>
/// <returns>A pointer to the newly allocated <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
TestCaseResult *TestCaseResult_New(const struct TestCase *test);

/// <summary>
/// Initializes a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to an uninitialized <see cref="TestCaseResult"/>.</param>
/// <param name="test">The <see cref="TestCase"/> associated with the <see cref="TestCaseResult"/>.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="test"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
void TestCaseResult_Constructor(TestCaseResult *report, const struct TestCase *test);

/// <summary>
/// Destroys a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestCaseResult_Destructor(TestCaseResult *report);

/* TestResult */
/// <summary>
/// Returns the number of passed test cases in a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The number of passed test cases in the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override int TestCaseResult_GetPassCount(const TestCaseResult *result);

/// <summary>
/// Returns the number of failed test cases in a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The number of failed test cases in the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override int TestCaseResult_GetFailCount(const TestCaseResult *result);

/// <summary>
/// Returns the number of skipped test cases in a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The number of skipped test cases in the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override int TestCaseResult_GetSkipCount(const TestCaseResult *result);

/// <summary>
/// Returns the number of inconclusive test cases in a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The number of inconclusive test cases in the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override int TestCaseResult_GetInconclusiveCount(const TestCaseResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the passed test cases in a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the passed test cases in the <see cref="TestCaseResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestCaseResult_CopyPassedTests(const TestCaseResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the failed test cases in a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the failed test cases in the <see cref="TestCaseResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestCaseResult_CopyFailedTests(const TestCaseResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the skipped test cases in a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the skipped test cases in the <see cref="TestCaseResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestCaseResult_CopySkippedTests(const TestCaseResult *result);

/// <summary>
/// Returns a new <see cref="IEnumerable"/> containing the inconclusive test cases in a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>
///     A new <see cref="IEnumerable"/> containing the inconclusive test cases in the <see cref="TestCaseResult"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestCaseResult_CopyInconclusiveTests(const TestCaseResult *result);

/// <summary>
/// Gets the children of a <see cref="TestCaseResult"/>.
/// </summary>
/// <remarks>Returns <see cref="Enumerable_Empty()"/>.</remarks>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>An <see cref="IEnumerable"/> that contains the children of the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override struct IEnumerable *TestCaseResult_GetChildren(const TestCaseResult *result);

/// <summary>
/// Returns whether or not a <see cref="TestCaseResult"/> has children.
/// </summary>
/// <remarks>Returns <see cref="false"/>.</remarks>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>
///     <see cref="true"/> if the test result has children; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override bool TestCaseResult_HasChildren(const TestCaseResult *result);

/// <summary>
/// Returns whether or not a <see cref="TestCaseResult"/> is a <see cref="TestSuiteResult"/>.
/// </summary>
/// <remarks>Returns <see cref="false"/>.</remarks>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>
///     <see cref="true"/> if <paramref name="result"/> is a <see cref="TestSuiteResult"/>;
///     otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
override bool TestCaseResult_IsSuiteResult(const TestCaseResult *result);

/// <summary>
/// Adds a given test result as the child of a <see cref="TestCaseResult"/>.
/// </summary>
/// <remarks>Throws <see cref="NotSupportedException"/>.</remarks>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <param name="childResult">The <see cref="TestCaseResult"/> to add as a child.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="childResult"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::NotSupportedException">
///     <see cref="TestCaseResult_CanAddChildren()"/> returned <see cref="false"/>.
/// </exception>
override void TestCaseResult_AddChildResult(TestCaseResult *result, TestResult *childResult);

/// <summary>
/// Returns whether or not children can be added to a <see cref="TestCaseResult"/>.
/// </summary>
/// <remarks>Returns <see cref="false"/>.</remarks>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>
///     <see cref="true"/> if children can be added to the test result; otherwise, <see cref="false"/>.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
bool TestCaseResult_CanAddChildren(const TestCaseResult *result);

/// <summary>
/// Returns the number of test cases in a <see cref="TestCaseResult"/>.
/// </summary>
/// <remarks>Returns 1.</remarks>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The number of test cases in the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
int TestCaseResult_GetTestCaseCount(const TestCaseResult *result);

/// <summary>
/// Returns the number of test cases ran in a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The number of test cases ran in the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
int TestCaseResult_GetRunCount(const TestCaseResult *result);

/// <summary>
/// Gets the <see cref="Test"/> with which a <see cref="TestCaseResult"/> is associated.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The <see cref="Test"/> with which the <see cref="TestCaseResult"/> is associated.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct Test *TestCaseResult_GetTest(const TestCaseResult *result);

/// <summary>
/// Gets the name of a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The name of the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct String *TestCaseResult_GetName(const TestCaseResult *result);

/// <summary>
/// Gets the fully qualified name of a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The fully qualified name of the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct String *TestCaseResult_GetFullName(const TestCaseResult *result);

/// <summary>
/// Gets the parent of a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>The parent of the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const TestResult *TestCaseResult_GetParent(const TestCaseResult *result);

/// <summary>
/// Returns the time it took to run the tests associated with a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to an <see cref="TestCaseResult"/>.</param>
/// <returns>The time it took to run the tests associated with a <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
double TestCaseResult_GetDuration(const TestCaseResult *result);

/// <summary>
/// Gets the <see cref="CFlatException"/> associated with a skipped, failed, inconclusive or forcibly passed test.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <returns>
///     The <see cref="CFlatException"/> associated with a skipped, failed, inconclusive or forcibly passed test;
///     or <see cref="null"/> if the test passed and no exception occured or the exception message was empty.
/// </returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
const struct CFlatException *TestCaseResult_GetException(const TestCaseResult *result);

/// <summary>
/// Returns the result of a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <returns>The result of the <see cref="TestCaseResult"/>.</returns>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
TestStatus TestCaseResult_GetResult(const TestCaseResult *result);

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
const struct String *TestCaseResult_GetStandardOutput(const TestCaseResult *result);

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
const struct String *TestCaseResult_GetStandardError(const TestCaseResult *result);

/// <summary>
/// Sets the parent of a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <param name="parent>The parent of the <see cref="TestCaseResult"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestCaseResult_SetParent(TestCaseResult *result, const TestResult *parent);

/// <summary>
/// Sets the time it took to run the tests associated with a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to an <see cref="TestCaseResult"/>.</param>
/// <param name="duration>The time it took to run the tests.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
/// <exception cref="::ArgumentOutOfRangeException"><paramref name="duration"/> is negative.</exception>
void TestCaseResult_SetDuration(TestCaseResult *result, double duration);

/// <summary>
/// Sets the result of a <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <param name="status>The result of the test.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestCaseResult_SetResult(TestCaseResult *result, TestStatus status);

/// <summary>
/// Sets the output to the standard output stream captured while running the tests associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <param name="output">The output captured while running the tests.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestCaseResult_SetStandardOutput(const TestCaseResult *result, const struct String *output);

/// <summary>
/// Sets the output to the standard error stream captured while running the tests associated with a
/// <see cref="TestResult"/>.
/// </summary>
/// <param name="report">Pointer to an <see cref="TestReport"/>.</param>
/// <param name="output">The output captured while running the tests.</param>
/// <exception cref="::ArgumentNullException"><paramref name="result"/> is <see cref="null"/>.</exception>
void TestCaseResult_SetStandardError(const TestCaseResult *result, const struct String *error);

/// <summary>
/// Records a <see cref="CFlatException"/> that was thrown while running a test associated with a
/// <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <param name="exception">A <see cref="CFlatException"/> that was thrown while running a test.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="exception"/> is <see cref="null"/>.
/// </exception>
void TestCaseResult_RecordException(TestCaseResult *result, const struct CFlatException *exception);

/// <summary>
/// Records a <see cref="CFlatException"/> that was thrown during the setup of a test associated with a
/// <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <param name="exception">A <see cref="CFlatException"/> that was thrown during the setup.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="exception"/> is <see cref="null"/>.
/// </exception>
void TestCaseResult_RecordSetUpException(TestCaseResult *result, const struct CFlatException *exception);

/// <summary>
/// Records a <see cref="CFlatException"/> that was thrown during the teardown of a test associated with a
/// <see cref="TestCaseResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestCaseResult"/>.</param>
/// <param name="exception">A <see cref="CFlatException"/> that was thrown during the teardown.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="result"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="exception"/> is <see cref="null"/>.
/// </exception>
void TestCaseResult_RecordTearDownException(TestCaseResult *result, const struct CFlatException *exception);

#endif
