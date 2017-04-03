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

#include "CFlat/Testing/TestSuiteResult.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/Enumerable.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/IList.h"
#include "CFlat/Collections/ObjectList.h"
#include "CFlat/Testing/TestStatus.h"
#include "CFlat/Testing/TestSuite.h"

/* Types */
struct TestSuiteResult {
    TestResult Base;
    IList *Children;
    int PassCount;
    int FailCount;
    int SkipCount;
    int InconclusiveCount;
};

typedef int (*GetCountFunc)(const TestResult *result);

typedef IEnumerable *(*GetEnumerableFunc)(const TestResult *result);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="TestSuiteReport"/> class.
/// </summary>
private const TestResultVTable VTable = TestResultVTable_Initializer(
    (DestructorFunc)TestSuiteResult_Destructor,
    (TestResult_GetPassCountFunc)TestSuiteResult_GetPassCount,
    (TestResult_GetFailCountFunc)TestSuiteResult_GetFailCount,
    (TestResult_GetSkipCountFunc)TestSuiteResult_GetSkipCount,
    (TestResult_GetInconclusiveCountFunc)TestSuiteResult_GetInconclusiveCount,
    (TestResult_CopyPassedTestsFunc)TestSuiteResult_CopyPassedTests,
    (TestResult_CopyFailedTestsFunc)TestSuiteResult_CopyFailedTests,
    (TestResult_CopySkippedTestsFunc)TestSuiteResult_CopySkippedTests,
    (TestResult_CopyInconclusiveTestsFunc)TestSuiteResult_CopyInconclusiveTests,
    (TestResult_GetChildrenFunc)TestSuiteResult_GetChildren,
    (TestResult_HasChildrenFunc)TestSuiteResult_HasChildren,
    (TestResult_IsSuiteResultFunc)TestSuiteResult_IsSuiteResult,
    (TestResult_AddChildResultFunc)TestSuiteResult_AddChildResult);

/**************************************/
/* Private functions                  */
/**************************************/

private int AggregateChildrenCount(const TestSuiteResult *result, GetCountFunc aggregateFunc);
private IEnumerable *AggregateChildrenEnumerables(const TestSuiteResult *result, GetEnumerableFunc aggregateFunc);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public TestSuiteResult *TestSuiteResult_New(const TestSuite *test)
{
    TestSuiteResult *result = Memory_Allocate(sizeof(TestSuiteResult));

    try {
        TestSuiteResult_Constructor(result, test);

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
public void TestSuiteResult_Constructor(TestSuiteResult *result, const TestSuite *test)
{
    Validate_NotNull(result);
    Validate_NotNull(test);

    TestResult_Constructor((TestResult*)result, (const Test*)test, &VTable);

    result->Children = (IList*)ObjectList_New();
    result->PassCount = 0;
    result->FailCount = 0;
    result->SkipCount = 0;
    result->InconclusiveCount = 0;
}

/* Destructor */
public void TestSuiteResult_Destructor(TestSuiteResult *result)
{
    Validate_NotNull(result);

    release(result->Children);

    TestResult_Destructor((TestResult*)result);
}

/* TestResult */
public override int TestSuiteResult_GetPassCount(const TestSuiteResult *result)
{
    return AggregateChildrenCount(result, TestResult_GetPassCount);
}

public override int TestSuiteResult_GetFailCount(const TestSuiteResult *result)
{
    return AggregateChildrenCount(result, TestResult_GetFailCount);
}

public override int TestSuiteResult_GetSkipCount(const TestSuiteResult *result)
{
    return AggregateChildrenCount(result, TestResult_GetSkipCount);
}

public override int TestSuiteResult_GetInconclusiveCount(const TestSuiteResult *result)
{
    return AggregateChildrenCount(result, TestResult_GetInconclusiveCount);
}

public override IEnumerable *TestSuiteResult_CopyPassedTests(const TestSuiteResult *result)
{
    return AggregateChildrenEnumerables(result, TestResult_CopyPassedTests);
}

public override IEnumerable *TestSuiteResult_CopyFailedTests(const TestSuiteResult *result)
{
    return AggregateChildrenEnumerables(result, TestResult_CopyFailedTests);
}

public override IEnumerable *TestSuiteResult_CopySkippedTests(const TestSuiteResult *result)
{
    return AggregateChildrenEnumerables(result, TestResult_CopySkippedTests);
}

public override IEnumerable *TestSuiteResult_CopyInconclusiveTests(const TestSuiteResult *result)
{
    return AggregateChildrenEnumerables(result, TestResult_CopyInconclusiveTests);
}

public override struct IEnumerable *TestSuiteResult_GetChildren(const TestSuiteResult *result)
{
    Validate_NotNull(result);

    return (IEnumerable*)result->Children;
}

public override bool TestSuiteResult_HasChildren(const TestSuiteResult *result)
{
    Validate_NotNull(result);

    return IList_GetCount(result->Children) > 0;
}

public override bool TestSuiteResult_IsSuiteResult(const TestSuiteResult *result)
{
    Validate_NotNull(result);

    return true;
}

public override void TestSuiteResult_AddChildResult(TestSuiteResult *result, TestResult *childResult)
{
    Validate_NotNull(result);
    Validate_NotNull(childResult);

    IList_Add(result->Children, childResult);

    result->PassCount += TestResult_GetPassCount(childResult);
    result->FailCount += TestResult_GetFailCount(childResult);
    result->SkipCount += TestResult_GetSkipCount(childResult);
    result->InconclusiveCount += TestResult_GetInconclusiveCount(childResult);

    TestSuiteResult_SetDuration(result, TestSuiteResult_GetDuration(result) + TestResult_GetDuration(childResult));

    if ((TestSuiteResult_GetResult(result) == TestStatus_Success ||
        TestSuiteResult_GetResult(result) == TestStatus_Inconclusive) && result->FailCount > 0) {
        TestSuiteResult_SetResult(result, TestStatus_Failure);
    }
    else if (TestSuiteResult_GetResult(result) == TestStatus_Success && result->InconclusiveCount > 0) {
        TestSuiteResult_SetResult(result, TestStatus_Inconclusive);
    }
}

public bool TestSuiteResult_CanAddChildren(const TestSuiteResult *result)
{
    return TestResult_CanAddChildren((const TestResult*)result);
}

public int TestSuiteResult_GetTestSuiteCount(const TestSuiteResult *result)
{
    return TestResult_GetTestCaseCount((const TestResult*)result);
}

public int TestSuiteResult_GetRunCount(const TestSuiteResult *result)
{
    return TestResult_GetRunCount((const TestResult*)result);
}

public const Test *TestSuiteResult_GetTest(const TestSuiteResult *result)
{
    return TestResult_GetTest((const TestResult*)result);
}

public const String *TestSuiteResult_GetName(const TestSuiteResult *result)
{
    return TestResult_GetName((const TestResult*)result);
}

public const String *TestSuiteResult_GetFullName(const TestSuiteResult *result)
{
    return TestResult_GetFullName((const TestResult*)result);
}

public const TestResult *TestSuiteResult_GetParent(const TestSuiteResult *result)
{
    return TestResult_GetParent((const TestResult*)result);
}

public double TestSuiteResult_GetDuration(const TestSuiteResult *result)
{
    return TestResult_GetDuration((const TestResult*)result);
}

public const CFlatException *TestSuiteResult_GetException(const TestSuiteResult *result)
{
    return TestResult_GetException((const TestResult*)result);
}

public TestStatus TestSuiteResult_GetResult(const TestSuiteResult *result)
{
    return TestResult_GetResult((const TestResult*)result);
}

public const String *TestSuiteResult_GetStandardOutput(const TestSuiteResult *result)
{
    return TestResult_GetStandardOutput((const TestResult*)result);
}

public const String *TestSuiteResult_GetStandardError(const TestSuiteResult *result)
{
    return TestResult_GetStandardError((const TestResult*)result);
}

public void TestSuiteResult_SetParent(TestSuiteResult *result, const TestResult *parent)
{
    TestResult_SetParent((TestResult*)result, parent);
}

public void TestSuiteResult_SetDuration(TestSuiteResult *result, double duration)
{
    TestResult_SetDuration((TestResult*)result, duration);
}

public void TestSuiteResult_SetResult(TestSuiteResult *result, TestStatus status)
{
    TestResult_SetResult((TestResult*)result, status);
}

public void TestSuiteResult_SetStandardOutput(const TestSuiteResult *result, const String *output)
{
    TestResult_SetStandardOutput((TestResult*)result, output);
}

public void TestSuiteResult_SetStandardError(const TestSuiteResult *result, const String *error)
{
    TestResult_SetStandardError((TestResult*)result, error);
}

public void TestSuiteResult_RecordException(TestSuiteResult *result, const CFlatException *exception)
{
    TestResult_RecordException((TestResult*)result, exception);
}

public void TestSuiteResult_RecordSetUpException(TestSuiteResult *result, const CFlatException *exception)
{
    TestResult_RecordSetUpException((TestResult*)result, exception);
}

public void TestSuiteResult_RecordTearDownException(TestSuiteResult *result, const CFlatException *exception)
{
    TestResult_RecordTearDownException((TestResult*)result, exception);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private int AggregateChildrenCount(const TestSuiteResult *result, GetCountFunc getCount)
{
    Validate_NotNull(result);
    assert(getCount != null);

    int count = 0;
    IEnumerator *enumerator = IEnumerable_GetEnumerator((IEnumerable*)result->Children);

    try {
        while (IEnumerator_MoveNext(enumerator)) {
            count += getCount(IEnumerator_GetCurrent(enumerator));
        }
    }
    finally {
        release(enumerator);
    }
    endtry;

    return count;
}

private IEnumerable *AggregateChildrenEnumerables(const TestSuiteResult *result, GetEnumerableFunc getEnumerable)
{
    Validate_NotNull(result);
    assert(getEnumerable != null);

    IEnumerable *enumerable = null;
    IList *enumerablesList = (IList*)ObjectList_New();

    try {
        IEnumerator *enumerator = IEnumerable_GetEnumerator((IEnumerable*)result->Children);

        try {
            while (IEnumerator_MoveNext(enumerator)) {
                IEnumerable *childEnumerable = getEnumerable(IEnumerator_GetCurrent(enumerator));

                try {
                    IList_Add(enumerablesList, childEnumerable);
                }
                finally {
                    release(childEnumerable);
                }
                endtry;
            }
        }
        finally {
            release(enumerator);
        }
        endtry;

        enumerable = Enumerable_ConcatEnumerable((IEnumerable*)enumerablesList);
    }
    finally {
        release(enumerablesList);
    }
    endtry;

    return enumerable;
}
