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

#include "CFlat/Testing/TestCase.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/Enumerable.h"
#include "CFlat/Testing/ITestListener.h"
#include "CFlat/Testing/OutputCapture.h"
#include "CFlat/Testing/Test.h"
#include "CFlat/Testing/TestResult.h"
#include "CFlat/Testing/TestCaseResult.h"

/* Types */
struct TestCase {
    Test Base;
    Action Test;
};

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="TestCase"/> class.
/// </summary>
private const TestVTable VTable = TestVTable_Initializer(
    (DestructorFunc)TestCase_Destructor,
    (Test_GetChildrenFunc)TestCase_GetChildren,
    (Test_HasChildrenFunc)TestCase_HasChildren,
    (Test_IsSuiteFunc)TestCase_IsSuite,
    (Test_GetTestCaseCountFunc)TestCase_GetTestCaseCount,
    (Test_CreateResultFunc)TestCase_CreateResult,
    (Test_RunInternalFunc)TestCase_RunInternal);

/**************************************/
/* Public function definitions        */
/**************************************/

public TestCase *TestCase_New(const char *name, Action testFunction)
{
    TestCase *test = Memory_Allocate(sizeof(TestCase));

    try {
        TestCase_Constructor(test, name, testFunction);

        Object_SetDeallocator(test, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(test);
        throw;
    }
    endtry;

    return test;
}

public void TestCase_Constructor(TestCase *test, const char *name, Action testFunction)
{
    Validate_NotNull(testFunction);

    Test_Constructor((Test*)test, name, &VTable);

    test->Test = testFunction;
}

public void TestCase_Destructor(TestCase *test)
{
    Test_Destructor((Test*)test);
}

/* Test */
public const String *TestCase_GetName(const TestCase *test)
{
    return Test_GetName((const Test*)test);
}

public const String *TestCase_GetFullName(const TestCase *test)
{
    return Test_GetFullName((const Test*)test);
}

public Test *TestCase_GetParent(const TestCase *test)
{
    return Test_GetParent((const Test*)test);
}

public void TestCase_SetParent(TestCase *test, Test *parent)
{
    Test_SetParent((Test*)test, parent);
}

public override int TestCase_GetTestCaseCount(const TestCase *test)
{
    Validate_NotNull(test);

    return 1;
}

public override IEnumerable *TestCase_GetChildren(const TestCase *test)
{
    Validate_NotNull(test);

    return Enumerable_Empty();
}

public override bool TestCase_HasChildren(const TestCase *test)
{
    Validate_NotNull(test);

    return false;
}

public override bool TestCase_IsSuite(const TestCase *test)
{
    Validate_NotNull(test);

    return false;
}

public override TestResult *TestCase_CreateResult(const TestCase *test)
{
    Validate_NotNull(test);

    return (TestResult*)TestCaseResult_New(test);
}

public override void TestCase_RunInternal(const TestCase *test, TestResult *result, ITestListener *listener)
{
    Validate_NotNull(test);
    Validate_NotNull(result);

    if (listener != null) {
        ITestListener_TestStarted(listener, (const Test*)test);
    }

    TestResult_SetResult(result, TestStatus_Success);

    OutputCapture output;
    OutputCapture_Constructor(&output);
    OutputCapture_BeginCapture(&output);

    try {
        test->Test();
    }
    catch_ex(Exception, ex)
    {
        TestResult_RecordException(result, ex);
    }
    finally {
        OutputCapture_EndCapture(&output);

        TestResult_SetStandardOutput(result, OutputCapture_GetStandardOutput(&output));
        TestResult_SetStandardError(result, OutputCapture_GetStandardError(&output));

        OutputCapture_Destructor(&output);
    }
    endtry;

    TestResult_SetDuration(result, 0.0);

    if (listener != null) {
        ITestListener_TestFinished(listener, result);
    }
}

public TestResult *TestCase_Run(const TestCase *test, ITestListener *listener)
{
    return Test_Run((Test*)test, listener);
}
