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

#include "CFlat/Testing/TestCaseResult.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/Enumerable.h"
#include "CFlat/Testing/TestCase.h"
#include "CFlat/Testing/TestStatus.h"

/* Types */
struct TestCaseResult {
    TestResult Base;
};

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="TestCaseReport"/> class.
/// </summary>
private const TestResultVTable VTable = TestResultVTable_Initializer(
    (DestructorFunc)TestCaseResult_Destructor,
    (TestResult_GetPassCountFunc)TestCaseResult_GetPassCount,
    (TestResult_GetFailCountFunc)TestCaseResult_GetFailCount,
    (TestResult_GetSkipCountFunc)TestCaseResult_GetSkipCount,
    (TestResult_GetInconclusiveCountFunc)TestCaseResult_GetInconclusiveCount,
    (TestResult_CopyPassedTestsFunc)TestCaseResult_CopyPassedTests,
    (TestResult_CopyFailedTestsFunc)TestCaseResult_CopyFailedTests,
    (TestResult_CopySkippedTestsFunc)TestCaseResult_CopySkippedTests,
    (TestResult_CopyInconclusiveTestsFunc)TestCaseResult_CopyInconclusiveTests,
    (TestResult_GetChildrenFunc)TestCaseResult_GetChildren,
    (TestResult_HasChildrenFunc)TestCaseResult_HasChildren,
    (TestResult_IsSuiteResultFunc)TestCaseResult_IsSuiteResult,
    (TestResult_AddChildResultFunc)TestCaseResult_AddChildResult);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public TestCaseResult *TestCaseResult_New(const TestCase *test)
{
    TestCaseResult *result = Memory_Allocate(sizeof(TestCaseResult));

    try {
        TestCaseResult_Constructor(result, test);

        Object_SetDeallocator(result, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(result);
        throw;
    }
    endtry;

    return result;
}

/* Constructors */
public void TestCaseResult_Constructor(TestCaseResult *result, const TestCase *test)
{
    Validate_NotNull(result);
    Validate_NotNull(test);

    TestResult_Constructor((TestResult*)result, (const Test*)test, &VTable);
}

/* Destructor */
public void TestCaseResult_Destructor(TestCaseResult *result)
{
    TestResult_Destructor((TestResult*)result);
}

/* TestResult */
public override int TestCaseResult_GetPassCount(const TestCaseResult *result)
{
    return TestCaseResult_GetResult(result) == TestStatus_Success ? 1 : 0;
}

public override int TestCaseResult_GetFailCount(const TestCaseResult *result)
{
    TestStatus status = TestCaseResult_GetResult(result);

    return  (status == TestStatus_Error || status == TestStatus_Failure) ? 1 : 0;
}

public override int TestCaseResult_GetSkipCount(const TestCaseResult *result)
{
    return TestCaseResult_GetResult(result) == TestStatus_Skipped ? 1 : 0;
}

public override int TestCaseResult_GetInconclusiveCount(const TestCaseResult *result)
{
    return TestCaseResult_GetResult(result) == TestStatus_Inconclusive ? 1 : 0;
}

public override IEnumerable *TestCaseResult_CopyPassedTests(const TestCaseResult *result)
{
    return TestCaseResult_GetResult(result) == TestStatus_Success ?
        Enumerable_FromSingleObject((Object*)result) :
        Enumerable_Empty();
}

public override IEnumerable *TestCaseResult_CopyFailedTests(const TestCaseResult *result)
{
    TestStatus status = TestCaseResult_GetResult(result);

    return (status == TestStatus_Error || status == TestStatus_Failure) ?
        Enumerable_FromSingleObject((Object*)result) :
        Enumerable_Empty();
}

public override IEnumerable *TestCaseResult_CopySkippedTests(const TestCaseResult *result)
{
    return TestCaseResult_GetResult(result) == TestStatus_Skipped ?
        Enumerable_FromSingleObject((Object*)result) :
        Enumerable_Empty();
}

public override IEnumerable *TestCaseResult_CopyInconclusiveTests(const TestCaseResult *result)
{
    return TestCaseResult_GetResult(result) == TestStatus_Inconclusive ?
        Enumerable_FromSingleObject((Object*)result) :
        Enumerable_Empty();
}

public override struct IEnumerable *TestCaseResult_GetChildren(const TestCaseResult *result)
{
    Validate_NotNull(result);

    return Enumerable_Empty();
}

public override bool TestCaseResult_HasChildren(const TestCaseResult *result)
{
    Validate_NotNull(result);

    return false;
}

public override bool TestCaseResult_IsSuiteResult(const TestCaseResult *result)
{
    Validate_NotNull(result);

    return false;
}

public override void TestCaseResult_AddChildResult(TestCaseResult *result, TestResult *childResult)
{
    Validate_NotNull(result);
    (void)childResult;

    throw_new(NotSupportedException, "The test result does not support adding child results.");
}

public bool TestCaseResult_CanAddChildren(const TestCaseResult *result)
{
    return TestResult_CanAddChildren((const TestResult*)result);
}

public int TestCaseResult_GetTestCaseCount(const TestCaseResult *result)
{
    return TestResult_GetTestCaseCount((const TestResult*)result);
}

public int TestCaseResult_GetRunCount(const TestCaseResult *result)
{
    return TestResult_GetRunCount((const TestResult*)result);
}

public const Test *TestCaseResult_GetTest(const TestCaseResult *result)
{
    return TestResult_GetTest((const TestResult*)result);
}

public const String *TestCaseResult_GetName(const TestCaseResult *result)
{
    return TestResult_GetName((const TestResult*)result);
}

public const String *TestCaseResult_GetFullName(const TestCaseResult *result)
{
    return TestResult_GetFullName((const TestResult*)result);
}

public const TestResult *TestCaseResult_GetParent(const TestCaseResult *result)
{
    return TestResult_GetParent((const TestResult*)result);
}

public double TestCaseResult_GetDuration(const TestCaseResult *result)
{
    return TestResult_GetDuration((const TestResult*)result);
}

public const CFlatException *TestCaseResult_GetException(const TestCaseResult *result)
{
    return TestResult_GetException((const TestResult*)result);
}

public TestStatus TestCaseResult_GetResult(const TestCaseResult *result)
{
    return TestResult_GetResult((const TestResult*)result);
}

public const String *TestCaseResult_GetStandardOutput(const TestCaseResult *result)
{
    return TestResult_GetStandardOutput((const TestResult*)result);
}

public const String *TestCaseResult_GetStandardError(const TestCaseResult *result)
{
    return TestResult_GetStandardError((const TestResult*)result);
}

public void TestCaseResult_SetParent(TestCaseResult *result, const TestResult *parent)
{
    TestResult_SetParent((TestResult*)result, parent);
}

public void TestCaseResult_SetDuration(TestCaseResult *result, double duration)
{
    TestResult_SetDuration((TestResult*)result, duration);
}

public void TestCaseResult_SetStandardOutput(const TestCaseResult *result, const String *output)
{
    TestResult_SetStandardOutput((TestResult*)result, output);
}

public void TestCaseResult_SetStandardError(const TestCaseResult *result, const String *error)
{
    TestResult_SetStandardError((TestResult*)result, error);
}

public void TestCaseResult_SetResult(TestCaseResult *result, TestStatus status)
{
    TestResult_SetResult((TestResult*)result, status);
}

public void TestCaseResult_RecordException(TestCaseResult *result, const CFlatException *exception)
{
    TestResult_RecordException((TestResult*)result, exception);
}

public void TestCaseResult_RecordSetUpException(TestCaseResult *result, const CFlatException *exception)
{
    TestResult_RecordSetUpException((TestResult*)result, exception);
}

public void TestCaseResult_RecordTearDownException(TestCaseResult *result, const CFlatException *exception)
{
    TestResult_RecordTearDownException((TestResult*)result, exception);
}
