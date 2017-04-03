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

#include "CFlat/Testing/ITestListener.h"

#include "CFlat.h"
#include "CFlat/Validate.h"
#include "CFlat/Testing/Test.h"
#include "CFlat/Testing/TestResult.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const ITestListenerVTable *GetVTable(const ITestListener *listener);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructors */
public void ITestListener_Constructor(
    ITestListener *test,
    const ITestListenerVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->TestStarted);
    Validate_NotNull(vtable->TestFinished);

    Object_Constructor((Object*)test, (const ObjectVTable*)vtable);
}

/* ITestListener */
public void ITestListener_TestStarted(ITestListener *listener, const Test *test)
{
    GetVTable(listener)->TestStarted(listener, test);
}

public void ITestListener_TestFinished(ITestListener *listener, const TestResult *result)
{
    GetVTable(listener)->TestFinished(listener, result);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of an <see cref="ITestListener"/>.
/// </summary>
/// <param name="test">Pointer to an <see cref="ITestListener"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="listener"/> is <see cref="null"/>.</exception>
private const ITestListenerVTable *GetVTable(const ITestListener *listener)
{
    Validate_NotNull(listener);

    return (const ITestListenerVTable*)((const Object*)listener)->VTable;
}
