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

#include "CFlat/Testing/TestSuite.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/IList.h"
#include "CFlat/Collections/ObjectList.h"
#include "CFlat/Testing/ITestListener.h"
#include "CFlat/Testing/Test.h"
#include "CFlat/Testing/TestCase.h"
#include "CFlat/Testing/TestResult.h"
#include "CFlat/Testing/TestStatus.h"
#include "CFlat/Testing/TestSuiteResult.h"

/* Types */
struct TestSuite {
    Test Base;
    IList *Tests;
    Action SetUp;
    Action TearDown;
};

typedef void(*RecordExceptionFunc)(TestResult *result, const CFlatException *exception);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="TestSuite"/> class.
/// </summary>
private const TestVTable VTable = TestVTable_Initializer(
    (DestructorFunc)TestSuite_Destructor,
    (Test_GetChildrenFunc)TestSuite_GetChildren,
    (Test_HasChildrenFunc)TestSuite_HasChildren,
    (Test_IsSuiteFunc)TestSuite_IsSuite,
    (Test_GetTestCaseCountFunc)TestSuite_GetTestCaseCount,
    (Test_CreateResultFunc)TestSuite_CreateResult,
    (Test_RunInternalFunc)TestSuite_RunInternal);

/**************************************/
/* Private functions                  */
/**************************************/

private TestResult *RunChild(const TestSuite *suite, const Test *child, ITestListener *listener);
private bool SetUp(const TestSuite* suite, TestResult *childResult);
private bool TearDown(const TestSuite *suite, TestResult *childResult);
private bool TryRunAction(Action action, RecordExceptionFunc recordException, TestResult *result);
private void SkipChildren(const Test *suite, TestResult *result, TestStatus status, const CFlatException *ex);

/**************************************/
/* Public function definitions        */
/**************************************/

public TestSuite *TestSuite_New(const char *name)
{
    TestSuite *suite = Memory_Allocate(sizeof(TestSuite));

    try {
        TestSuite_Constructor(suite, name);

        Object_SetDeallocator(suite, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(suite);
        throw;
    }
    endtry;

    return suite;
}

public void TestSuite_Constructor(TestSuite *suite, const char *name)
{
    Test_Constructor((Test*)suite, name, &VTable);

    suite->Tests = (IList*)ObjectList_New();
    suite->SetUp = null;
    suite->TearDown = null;
}

public void TestSuite_Destructor(TestSuite *suite)
{
    Validate_NotNull(suite);

    release(suite->Tests);

    Test_Destructor((Test*)suite);
}

public void TestSuite_Add(TestSuite *suite, Test *test)
{
    Validate_NotNull(suite);
    Validate_NotNull(test);

    IList_Add(suite->Tests, test);
    Test_SetParent(test, (Test*)suite);
}

public void TestSuite_AddNamedTestCase(TestSuite *suite, const char *name, Action testFunction)
{
    Validate_NotNull(suite);

    Test *test = (Test*)TestCase_New(name, testFunction);

    try {
        IList_Add(suite->Tests, test);
        Test_SetParent(test, (Test*)suite);
    }
    finally {
        release(test);
    }
    endtry;
}

public void TestSuite_SetSetUpFunction(TestSuite *suite, Action setUp)
{
    Validate_NotNull(suite);

    suite->SetUp = setUp;
}

public void TestSuite_SetTearDownFunction(TestSuite *suite, Action tearDown)
{
    Validate_NotNull(suite);

    suite->TearDown = tearDown;
}

/* Test */
public const String *TestSuite_GetName(const TestSuite *suite)
{
    return Test_GetName((const Test*)suite);
}

public const String *TestSuite_GetFullName(const TestSuite *test)
{
    return Test_GetFullName((const Test*)test);
}

public Test *TestSuite_GetParent(const TestSuite *suite)
{
    return Test_GetParent((const Test*)suite);
}

public void TestSuite_SetParent(TestSuite *suite, Test *parent)
{
    Test_SetParent((Test*)suite, parent);
}

public override int TestSuite_GetTestCaseCount(const TestSuite *suite)
{
    Validate_NotNull(suite);

    int count = 0;

    // Recursively count the number of test cases.
    for (uintsize i = 0; i < IList_GetCount(suite->Tests); i++) {
        count += Test_GetTestCaseCount((const Test*)IList_GetItem(suite->Tests, i));
    }

    return count;
}

public override IEnumerable *TestSuite_GetChildren(const TestSuite *suite)
{
    Validate_NotNull(suite);

    return (IEnumerable*)suite->Tests;
}

public override bool TestSuite_HasChildren(const TestSuite *suite)
{
    Validate_NotNull(suite);

    return IList_GetCount(suite->Tests) > 0;
}

public override bool TestSuite_IsSuite(const TestSuite *suite)
{
    Validate_NotNull(suite);

    return true;
}

public override TestResult *TestSuite_CreateResult(const TestSuite *suite)
{
    Validate_NotNull(suite);

    return (TestResult*)TestSuiteResult_New(suite);
}

public override void TestSuite_RunInternal(const TestSuite *test, TestResult *result, ITestListener *listener)
{
    Validate_NotNull(test);
    Validate_NotNull(result);
    Validate_Argument(TestResult_CanAddChildren(result),
        "The test result must support adding child results.",
        "result");

    if (listener != null) {
        ITestListener_TestStarted(listener, (const Test*)test);
    }

    TestResult_SetResult(result, TestStatus_Success);

    // Iterate through and run all children.
    for (uintsize i = 0; i < IList_GetCount(test->Tests); i++) {
        Test *child = IList_GetItem(test->Tests, i);
        TestResult *childResult = RunChild(test, child ,listener);

        try {
            TestResult_AddChildResult(result, childResult);
        }
        finally {
            release(childResult);
        }
        endtry;
    }

    if (listener != null) {
        ITestListener_TestFinished(listener, (const TestResult*)result);
    }
}

public TestResult *TestSuite_Run(const TestSuite *test, ITestListener *listener)
{
    return Test_Run((Test*)test, listener);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private TestResult *RunChild(const TestSuite *suite, const Test *child, ITestListener *listener)
{
    assert(suite != null);
    assert(child != null);

    TestResult *childResult = Test_CreateResult(child);

    try {
        if (SetUp(suite, childResult)) {
            try {
                Test_RunInternal(child, childResult, listener);
            }
            finally {
                TearDown(suite, childResult);
            }
            endtry;
        }
        else if (Test_IsSuite(child) && Test_HasChildren(child)) {
            SkipChildren(child, childResult, TestResult_GetResult(childResult), TestResult_GetException(childResult));
        }
    }
    catch (Exception) {
        release(childResult);
        throw;
    }
    endtry;

    return childResult;
}

private bool SetUp(const TestSuite* suite, TestResult *childResult)
{
    assert(suite != null);
    assert(childResult != null);

    return TryRunAction(suite->SetUp, TestResult_RecordSetUpException, childResult);
}

private bool TearDown(const TestSuite* suite, TestResult *childResult)
{
    assert(suite != null);
    assert(childResult != null);

    return TryRunAction(suite->TearDown, TestResult_RecordTearDownException, childResult);
}

private bool TryRunAction(Action action, RecordExceptionFunc recordException, TestResult *result)
{
    assert(recordException != null);
    assert(result != null);

    bool success = true;

    if (action != null) {
        try {
            action();
        }
        catch_ex (Exception, ex) {
            recordException(result, ex);

            success = false;
        }
        endtry;
    }

    return success;
}

private void SkipChildren(const Test *test, TestResult *result, TestStatus status, const CFlatException *exception)
{
    assert(test != null);
    assert(result != null);
    assert(Test_IsSuite(test));
    Validate_Argument(TestResult_CanAddChildren(result),
        "The test result must support adding child results.",
        "result");

    IEnumerator *enumerator = IEnumerable_GetEnumerator(Test_GetChildren(test));

    try {
        while (IEnumerator_MoveNext(enumerator)) {
            Test *child = IEnumerator_GetCurrent(enumerator);

            TestResult *childResult = Test_CreateResult(child);

            try {
                if (exception != null) {
                    TestResult_RecordException(childResult, exception);
                }

                TestResult_SetResult(childResult, status);

                TestResult_AddChildResult(result, childResult);

                if (Test_IsSuite(child) && Test_HasChildren(child)) {
                    SkipChildren(child, childResult, status, exception);
                }
            }
            finally {
                release(childResult);
            }
            endtry;
        }
    }
    finally {
        release(enumerator);
    }
    endtry;
}
