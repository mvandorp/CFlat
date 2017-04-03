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

#include "CFlat/Testing/Assert.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/String.h"

#define InvertString(invert) ((invert) ? "not " : "")

public void __CFLAT_TESTING_AreEqualChar(
    char expected,
    char actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line,
    bool ignoreCase)
{
    if (((ignoreCase && char_ToLower(expected) == char_ToLower(actual)) || (!ignoreCase && expected == actual)) == invert) {
        String *message = String_FormatCString(
            "Expected <{cstring}> to {cstring}evaluate to '{char}', but was '{char}'.",
            actualExpr, InvertString(invert), expected, actual);

        try {
            __CFLAT_EXCEPTION_THROW_NEW_STRING(AssertionException, message, file, line, null);
        }
        finally {
            release(message);
        }
        endtry;
    }
}

public void __CFLAT_TESTING_AreEqualCString(
    const char *expected,
    const char *actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line,
    bool ignoreCase)
{
    if (CString_Equals_IgnoreCase(expected, actual, ignoreCase) == invert) {
        String *message = String_FormatCString(
            "Expected <{cstring}> to {cstring}evaluate to \"{cstring}\", but was \"{cstring}\".",
            actualExpr, InvertString(invert), expected, actual);

        try {
            __CFLAT_EXCEPTION_THROW_NEW_STRING(AssertionException, message, file, line, null);
        }
        finally {
            release(message);
        }
        endtry;
    }
}

public void __CFLAT_TESTING_AreEqualDouble(
    double expected,
    double actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line)
{
    if ((expected == actual) == invert) {
        String *message = String_FormatCString(
            "Expected <{cstring}> to {cstring}evaluate to {double}, but was {double}.",
            actualExpr, InvertString(invert), expected, actual);

        try {
            __CFLAT_EXCEPTION_THROW_NEW_STRING(AssertionException, message, file, line, null);
        }
        finally {
            release(message);
        }
        endtry;
    }
}

public void __CFLAT_TESTING_AreEqualInt(
    intmax expected,
    intmax actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line)
{
    if ((expected == actual) == invert) {
        String *message = String_FormatCString(
            "Expected <{cstring}> to {cstring}evaluate to {intmax}, but was {intmax}.",
            actualExpr, InvertString(invert), expected, actual);

        try {
            __CFLAT_EXCEPTION_THROW_NEW_STRING(AssertionException, message, file, line, null);
        }
        finally {
            release(message);
        }
        endtry;
    }
}

public void __CFLAT_TESTING_AreEqualPointer(
    const void *expected,
    const void *actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line)
{
    if ((expected == actual) == invert) {
        String *message = String_FormatCString(
            "Expected <{cstring}> to {cstring}evaluate to {pointer}, but was {pointer}.",
            actualExpr, InvertString(invert), expected, actual);

        try {
            __CFLAT_EXCEPTION_THROW_NEW_STRING(AssertionException, message, file, line, null);
        }
        finally {
            release(message);
        }
        endtry;
    }
}

public void __CFLAT_TESTING_AreEqualUInt(
    uintmax expected,
    uintmax actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line)
{
    if ((expected == actual) == invert) {
        String *message = String_FormatCString(
            "Expected <{cstring}> to {cstring}evaluate to {uintmax}, but was {uintmax}.",
            actualExpr, InvertString(invert), expected, actual);

        try {
            __CFLAT_EXCEPTION_THROW_NEW_STRING(AssertionException, message, file, line, null);
        }
        finally {
            release(message);
        }
        endtry;
    }
}

public void __CFLAT_TESTING_AreEqualString(
    const String *expected,
    const String *actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line,
    bool ignoreCase)
{
    if (String_Equals_IgnoreCase(expected, actual, ignoreCase) == invert) {
        String *message = String_FormatCString(
            "Expected <{cstring}> to {cstring}evaluate to \"{string}\", but was \"{string}\".",
            actualExpr, InvertString(invert), expected, actual);

        try {
            __CFLAT_EXCEPTION_THROW_NEW_STRING(AssertionException, message, file, line, null);
        }
        finally {
            release(message);
        }
        endtry;
    }
}

public void __CFLAT_TESTING_IsNull(
    const void *actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line)
{
    if ((actual == null) == invert) {
        String *message;

        if (invert) {
            message = String_FormatCString(
                "Expected <{cstring}> to not evaluate to null, but was null.",
                actualExpr);
        }
        else {
            message = String_FormatCString(
                "Expected <{cstring}> to evaluate to null, but was {pointer}.",
                actualExpr, actual);
        }

        try {
            __CFLAT_EXCEPTION_THROW_NEW_STRING(AssertionException, message, file, line, null);
        }
        finally {
            release(message);
        }
        endtry;
    }
}
