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

#include "CFlat/Testing/TestResult.h"

#include "CFlat.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/Testing/TestStatus.h"
#include "CFlat/Testing/TestSuite.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const TestResultVTable *GetVTable(const struct TestResult *result);

private CFlatException *CopyExceptionWithNewFormattedMessage(
    const CFlatException *exception,
    const char *messageFormat, ...);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructors */
public void TestResult_Constructor(TestResult *result, const Test *test, const TestResultVTable *vtable)
{
    Validate_NotNull(result);
    Validate_NotNull(test);
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetPassCount);
    Validate_NotNull(vtable->GetFailCount);
    Validate_NotNull(vtable->GetSkipCount);
    Validate_NotNull(vtable->GetInconclusiveCount);
    Validate_NotNull(vtable->CopyPassedTests);
    Validate_NotNull(vtable->CopyFailedTests);
    Validate_NotNull(vtable->CopySkippedTests);
    Validate_NotNull(vtable->CopyInconclusiveTests);
    Validate_NotNull(vtable->GetChildren);
    Validate_NotNull(vtable->HasChildren);
    Validate_NotNull(vtable->IsSuiteResult);
    Validate_NotNull(vtable->AddChildResult);

    Object_Constructor((Object*)result, (const ObjectVTable*)vtable);

    result->Test = retain_const(test);
    result->Parent = null;
    result->StandardOutput = null;
    result->StandardError = null;
    result->Exception = null;
    result->Duration = 0.0;
    result->ResultStatus = TestStatus_Inconclusive;
}

/* Destructor */
public void TestResult_Destructor(TestResult *result)
{
    Validate_NotNull(result);

    release(result->Test);
    release(result->Exception);
    release(result->StandardOutput);
    release(result->StandardError);
}

/* Properties */
public abstract int TestResult_GetPassCount(const TestResult *result)
{
    return GetVTable(result)->GetPassCount(result);
}

public abstract int TestResult_GetFailCount(const TestResult *result)
{
    return GetVTable(result)->GetFailCount(result);
}

public abstract int TestResult_GetSkipCount(const TestResult *result)
{
    return GetVTable(result)->GetSkipCount(result);
}

public abstract int TestResult_GetInconclusiveCount(const TestResult *result)
{
    return GetVTable(result)->GetInconclusiveCount(result);
}

public abstract IEnumerable *TestResult_CopyPassedTests(const TestResult *result)
{
    return GetVTable(result)->CopyPassedTests(result);
}

public abstract IEnumerable *TestResult_CopyFailedTests(const TestResult *result)
{
    return GetVTable(result)->CopyFailedTests(result);
}

public abstract IEnumerable *TestResult_CopySkippedTests(const TestResult *result)
{
    return GetVTable(result)->CopySkippedTests(result);
}

public abstract IEnumerable *TestResult_CopyInconclusiveTests(const TestResult *result)
{
    return GetVTable(result)->CopyInconclusiveTests(result);
}

public abstract IEnumerable *TestResult_GetChildren(const TestResult *result)
{
    Validate_NotNull(result);

    return GetVTable(result)->GetChildren(result);
}

public abstract bool TestResult_HasChildren(const TestResult *result)
{
    Validate_NotNull(result);

    return GetVTable(result)->HasChildren(result);
}

public abstract bool TestResult_IsSuiteResult(const TestResult *result)
{
    return GetVTable(result)->IsSuiteResult(result);
}

public abstract void TestResult_AddChildResult(TestResult *result, TestResult *childResult)
{
    GetVTable(result)->AddChildResult(result, childResult);
}

public bool TestResult_CanAddChildren(const TestResult *result)
{
    return TestResult_IsSuiteResult(result);
}

public int TestResult_GetTestCaseCount(const TestResult *result)
{
    return Test_GetTestCaseCount(TestResult_GetTest(result));
}

public int TestResult_GetRunCount(const TestResult *result)
{
    return TestResult_GetTestCaseCount(result) - TestResult_GetSkipCount(result);
}

public const Test *TestResult_GetTest(const TestResult *result)
{
    Validate_NotNull(result);

    return result->Test;
}

public const String *TestResult_GetName(const TestResult *result)
{
    Validate_NotNull(result);

    return Test_GetName(result->Test);
}

public const String *TestResult_GetFullName(const TestResult *result)
{
    Validate_NotNull(result);

    return Test_GetFullName(result->Test);
}

public const TestResult *TestResult_GetParent(const TestResult *result)
{
    Validate_NotNull(result);

    return result->Parent;
}

public double TestResult_GetDuration(const TestResult *result)
{
    Validate_NotNull(result);

    return result->Duration;
}

public const CFlatException *TestResult_GetException(const TestResult *result)
{
    Validate_NotNull(result);

    return result->Exception;
}

public TestStatus TestResult_GetResult(const TestResult *result)
{
    Validate_NotNull(result);

    return result->ResultStatus;
}

public const String *TestResult_GetStandardOutput(const TestResult *result)
{
    Validate_NotNull(result);

    return result->StandardOutput;
}

public const String *TestResult_GetStandardError(const TestResult *result)
{
    Validate_NotNull(result);

    return result->StandardError;
}

public void TestResult_SetParent(TestResult *result, const TestResult *parent)
{
    Validate_NotNull(result);

    result->Parent = parent;
}

public void TestResult_SetDuration(TestResult *result, double duration)
{
    Validate_NotNull(result);
    Validate_NotNegative(duration);

    result->Duration = duration;
}

public void TestResult_SetResult(TestResult *result, TestStatus status)
{
    Validate_NotNull(result);
    TestStatus_Validate(status);

    result->ResultStatus = status;
}

public void TestResult_SetStandardOutput(TestResult *result, const String *output)
{
    Validate_NotNull(result);

    if (result->StandardOutput != output) {
        release(result->StandardOutput);

        result->StandardOutput = retain_const(output);
    }
}

public void TestResult_SetStandardError(TestResult *result, const String *error)
{
    Validate_NotNull(result);

    if (result->StandardError != error) {
        release(result->StandardError);

        result->StandardError = retain_const(error);
    }
}

/* Methods */
public void TestResult_RecordException(TestResult *result, const CFlatException *exception)
{
    Validate_NotNull(result);
    Validate_NotNull(exception);

    if (!String_IsNullOrEmpty(Exception_GetMessage(exception))) {
        if (result->Exception == null) {
            result->Exception = retain_const(exception);
        }
        else {
            const CFlatException *oldException = result->Exception;

            result->Exception = CopyExceptionWithNewFormattedMessage(
                oldException,
                "{string}" Environment_NewLine_CString "{string}",
                Exception_GetMessage(oldException),
                Exception_GetMessage(exception));

            release(oldException);
        }
    }

    if (Exception_IsInstanceOf(exception, AssertionException)) {
        TestResult_SetResult(result, TestStatus_Failure);
    }
    else if (Exception_IsInstanceOf(exception, SuccessException)) {
        TestResult_SetResult(result, TestStatus_Success);
    }
    else if (Exception_IsInstanceOf(exception, IgnoreException)) {
        TestResult_SetResult(result, TestStatus_Skipped);
    }
    else if (Exception_IsInstanceOf(exception, InconclusiveException)) {
        TestResult_SetResult(result, TestStatus_Inconclusive);
    }
    else {
        TestResult_SetResult(result, TestStatus_Error);
    }
}

public void TestResult_RecordSetUpException(TestResult *result, const CFlatException *exception)
{
    Validate_NotNull(result);
    Validate_NotNull(exception);

    if (Exception_IsInstanceOf(exception, IgnoreException)) {
        TestResult_RecordException(result, exception);
        return;
    }

    if (!String_IsNullOrEmpty(Exception_GetMessage(exception))) {
        if (result->Exception == null) {
            result->Exception = CopyExceptionWithNewFormattedMessage(
                exception,
                "SetUp: {string}",
                Exception_GetMessage(exception));
        }
        else {
            const CFlatException *oldException = result->Exception;

            result->Exception = CopyExceptionWithNewFormattedMessage(
                oldException,
                "{string}" Environment_NewLine_CString "SetUp: {string}",
                Exception_GetMessage(oldException),
                Exception_GetMessage(exception));

            release(oldException);
        }
    }

    TestResult_SetResult(result, TestStatus_Error);
}

public void TestResult_RecordTearDownException(TestResult *result, const CFlatException *exception)
{
    Validate_NotNull(result);
    Validate_NotNull(exception);

    if (!String_IsNullOrEmpty(Exception_GetMessage(exception))) {
        if (result->Exception == null) {
            result->Exception = CopyExceptionWithNewFormattedMessage(
                exception,
                "TearDown: {string}",
                Exception_GetMessage(exception));
        }
        else {
            const CFlatException *oldException = result->Exception;

            result->Exception = CopyExceptionWithNewFormattedMessage(
                oldException,
                "{string}" Environment_NewLine_CString "TearDown: {string}",
                Exception_GetMessage(oldException),
                Exception_GetMessage(exception));

            release(oldException);
        }
    }

    TestResult_SetResult(result, TestStatus_Error);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/* Methods */
/// <summary>
/// Gets the virtual method table of a <see cref="TestResult"/>.
/// </summary>
/// <param name="result">Pointer to a <see cref="TestResult"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
private const TestResultVTable *GetVTable(const TestResult *result)
{
    Validate_NotNull(result);

    return (const TestResultVTable*)((const Object*)result)->VTable;
}

private CFlatException *CopyExceptionWithNewFormattedMessage(
    const CFlatException *exception,
    const char *messageFormat, ...)
{
    CFlatException *result = null;

    VarArgsList args;
    VarArgs_Start(args, messageFormat);

    String *message = String_FormatCStringV(messageFormat, args);

    VarArgs_End(args);

    try {
        result = Exception_New(
            Exception_GetType(exception),
            message,
            Exception_GetFile(exception),
            Exception_GetLine(exception),
            null);
    }
    finally {
        release(message);
    }
    endtry;

    return result;
}
