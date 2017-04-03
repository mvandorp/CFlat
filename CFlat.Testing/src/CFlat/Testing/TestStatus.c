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

#include "CFlat/Testing/TestStatus.h"

#include "CFlat.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

/* Private constants */
private const String Error          = String_Initializer("Error");
private const String Failure        = String_Initializer("Failure");
private const String Inconclusive   = String_Initializer("Inconclusive");
private const String Skipped        = String_Initializer("Skipped");
private const String Success        = String_Initializer("Success");

/**************************************/
/* Public function definitions        */
/**************************************/

public bool TestStatus_IsValid(TestStatus status)
{
    return
        status == TestStatus_Error ||
        status == TestStatus_Failure ||
        status == TestStatus_Inconclusive ||
        status == TestStatus_Skipped ||
        status == TestStatus_Success;
}

public void TestStatus_Validate(TestStatus status)
{
    Validate_Argument(TestStatus_IsValid(status),
        "Value was out of legal range for enum TestStatus.", "status");
}

public const String *TestStatus_ToString(TestStatus status)
{
    switch (status) {
        case TestStatus_Error: return &Error;
        case TestStatus_Failure: return &Failure;
        case TestStatus_Inconclusive: return &Inconclusive;
        case TestStatus_Skipped: return &Skipped;
        case TestStatus_Success: return &Success;
        default:
            TestStatus_Validate(status);

            assert(!TestStatus_IsValid(status));
            return null;
    }
}
