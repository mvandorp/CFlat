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

#include "CFlat/Testing/ConsoleTestRunner.h"

#include "CFlat.h"
#include "CFlat/Console.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/IO/Path.h"
#include "CFlat/Testing/Test.h"
#include "CFlat/Testing/TestResult.h"

/**************************************/
/* Private functions                  */
/**************************************/

private void PrintPassedTests(const TestResult *result);
private void PrintFailedTests(const TestResult *result);
private void PrintInconclusiveTests(const TestResult *result);
private void PrintSkippedTests(const TestResult *result);
private void PrintResults(IEnumerable *things);
private void PrintException(const CFlatException *exception, TestStatus result);

/**************************************/
/* Public function definitions        */
/**************************************/

public bool ConsoleTestRunner_Run(int argc, char *argv[], const struct Test *test)
{
    Validate_NotNull(test);

    // TODO: Allow for more options via the command line parameters.
    (void)argc;
    (void)argv;

    Console_WriteLine_CString("Running tests...");

    TestResult *result = Test_Run(test, null);
    TestStatus status = TestStatus_Inconclusive;

    try {
        Console_WriteLine_CString("Done.");
        Console_WriteLine();

        if (TestResult_GetPassCount(result) > 0) {
            PrintPassedTests(result);
        }

        if (TestResult_GetFailCount(result) > 0) {
            PrintFailedTests(result);
        }

        if (TestResult_GetInconclusiveCount(result) > 0) {
            PrintInconclusiveTests(result);
        }

        if (TestResult_GetSkipCount(result) > 0) {
            PrintSkippedTests(result);
        }

        status = TestResult_GetResult(result);

        Console_WriteLine_CString("Test Run Summary");
        Console_WriteLineFormat_CString("    Overall result: {string}", TestStatus_ToString(status));
        Console_WriteLineFormat_CString("    Tests run: {int}, Passed: {int}, Failed: {int}, Inconclusive: {int}.",
            TestResult_GetRunCount(result),
            TestResult_GetPassCount(result),
            TestResult_GetFailCount(result),
            TestResult_GetInconclusiveCount(result));
        Console_WriteLineFormat_CString("      Not run: {int}.", TestResult_GetSkipCount(result));
    }
    finally {
        release(result);
    }
    endtry;

    return status == TestStatus_Success;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void PrintPassedTests(const TestResult *result)
{
    Console_WriteLine_CString("Passed:");

    IEnumerable *passed = TestResult_CopyPassedTests(result);

    try {
        PrintResults(passed);
    }
    finally {
        release(passed);
    }
    endtry;

    Console_WriteLine();
}

private void PrintFailedTests(const TestResult *result)
{
    Console_WriteLine_CString("Failures:");

    IEnumerable *failed = TestResult_CopyFailedTests(result);

    try {
        PrintResults(failed);
    }
    finally {
        release(failed);
    }
    endtry;

    Console_WriteLine();
}

private void PrintInconclusiveTests(const TestResult *result)
{
    Console_WriteLine_CString("Inconclusive:");

    IEnumerable *inconclusive = TestResult_CopyInconclusiveTests(result);

    try {
        PrintResults(inconclusive);
    }
    finally {
        release(inconclusive);
    }
    endtry;

    Console_WriteLine();
}

private void PrintSkippedTests(const TestResult *result)
{
    Console_WriteLine_CString("Skipped:");

    IEnumerable *skipped = TestResult_CopySkippedTests(result);

    try {
        PrintResults(skipped);
    }
    finally {
        release(skipped);
    }
    endtry;

    Console_WriteLine();
}

private void PrintResults(IEnumerable *results)
{
    IEnumerator *enumerator = IEnumerable_GetEnumerator(results);

    try {
        int i = 1;
        while (IEnumerator_MoveNext(enumerator)) {
            TestResult *result = IEnumerator_GetCurrent(enumerator);

            const char *padding = (i < 10) ? " " : "";
            Console_WriteLineFormat_CString("{int}){cstring} {string}", i++, padding, TestResult_GetFullName(result));

            if (!String_IsNullOrWhiteSpace(TestResult_GetStandardOutput(result))) {
                const String *output = TestResult_GetStandardOutput(result);
                Console_WriteFormat_CString("    Standard Output: {string}{string}",
                    output,
                    String_EndsWith(output, '\n') ? String_Empty : Environment_NewLine);
            }

            if (!String_IsNullOrWhiteSpace(TestResult_GetStandardError(result))) {
                const String *output = TestResult_GetStandardError(result);
                Console_WriteFormat_CString("    Standard Error: {string}{string}",
                    output,
                    String_EndsWith(output, '\n') ? String_Empty : Environment_NewLine);
            }

            if (TestResult_GetException(result) != null) {
                PrintException(TestResult_GetException(result), TestResult_GetResult(result));
            }
        }
    }
    finally {
        release(enumerator);
    }
    endtry;
}

private void PrintException(const CFlatException *exception, TestStatus result)
{
    assert(exception != null);

    int line = Exception_GetLine(exception);
    const char *file = Exception_GetFile(exception);
    const String *name = Exception_GetName(exception);
    const String *message = Exception_GetMessage(exception);
    const String *filename = Path_GetFileName_CString(file);

    try {
        if (result == TestStatus_Error) {
            Console_WriteLineFormat_CString("    Unexpected {string} at {string}:{int}: {string}",
                name, filename, line, message);
        }
        else {
            Console_WriteLineFormat_CString("    {string}:{int} - {string}", filename, line, message);
        }
    }
    finally {
        release(filename);
    }
    endtry;
}
