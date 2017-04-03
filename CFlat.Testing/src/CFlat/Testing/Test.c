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

#include "CFlat/Testing/Test.h"

#include "CFlat.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Testing/ITestListener.h"
#include "CFlat/Testing/TestResult.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const TestVTable *GetVTable(const Test *test);

private void UpdateFullName(Test *test);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructors */
public void Test_Constructor(
    Test *test,
    const char *name,
    const TestVTable *vtable)
{
    Validate_NotNull(name);
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetChildren);
    Validate_NotNull(vtable->HasChildren);
    Validate_NotNull(vtable->IsSuite);
    Validate_NotNull(vtable->GetTestCaseCount);
    Validate_NotNull(vtable->CreateResult);
    Validate_NotNull(vtable->RunInternal);

    Object_Constructor((Object*)test, (const ObjectVTable*)vtable);

    test->Name = String_New(name);
    test->FullName = retain_const(test->Name);
}

/* Destructor */
public void Test_Destructor(Test *test)
{
    Validate_NotNull(test);

    release(test->Name);
    release(test->FullName);
}

/* Properties */
public const String *Test_GetName(const Test *test)
{
    Validate_NotNull(test);

    return test->Name;
}

public const String *Test_GetFullName(const Test *test)
{
    Validate_NotNull(test);

    return test->FullName;;
}

public Test *Test_GetParent(const Test *test)
{
    Validate_NotNull(test);

    return test->Parent;
}

public void Test_SetParent(Test *test, Test *parent)
{
    Validate_NotNull(test);

    if (test->Parent != parent) {
        test->Parent = parent;

        UpdateFullName(test);
    }
}

/* Methods */
public abstract IEnumerable *Test_GetChildren(const Test *test)
{
    return GetVTable(test)->GetChildren(test);
}

public abstract bool Test_HasChildren(const Test *test)
{
    return GetVTable(test)->HasChildren(test);
}

public abstract bool Test_IsSuite(const Test *test)
{
    return GetVTable(test)->IsSuite(test);
}

public abstract int Test_GetTestCaseCount(const Test *test)
{
    return GetVTable(test)->GetTestCaseCount(test);
}

public abstract TestResult *Test_CreateResult(const Test *test)
{
    return GetVTable(test)->CreateResult(test);
}

public abstract void Test_RunInternal(const Test *test, TestResult *result, ITestListener *listener)
{
    GetVTable(test)->RunInternal(test, result, listener);
}

public TestResult *Test_Run(const Test *test, ITestListener *listener)
{
    TestResult *result = Test_CreateResult(test);

    try {
        Test_RunInternal(test, result, listener);
    }
    catch (Exception) {
        release(result);
        throw;
    }
    endtry;

    return result;
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of a <see cref="Test"/>.
/// </summary>
/// <param name="test">Pointer to a <see cref="Test"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="test"/> is <see cref="null"/>.</exception>
private const TestVTable *GetVTable(const Test *test)
{
    Validate_NotNull(test);

    return (const TestVTable*)((const Object*)test)->VTable;
}

private void UpdateFullName(Test *test)
{
    assert(test != null);

    // Update own name.
    const String *oldName = test->FullName;

    if (test->Parent == null) {
        test->FullName = retain_const(Test_GetName(test));
    }
    else {
        test->FullName = String_FormatCString("{string}.{string}", Test_GetFullName(test->Parent), Test_GetName(test));
    }

    release(oldName);

    // Update name of children.
    if (Test_HasChildren(test)) {
        IEnumerator *enumerator = IEnumerable_GetEnumerator(Test_GetChildren(test));

        try {
            while (IEnumerator_MoveNext(enumerator)) {
                Test *child = IEnumerator_GetCurrent(enumerator);

                UpdateFullName(child);
            }
        }
        finally {
            release(enumerator);
        }
        endtry;
    }
}
