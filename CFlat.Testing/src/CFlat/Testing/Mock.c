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

#include "CFlat/Testing/Mock.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/String.h"

Mock_DefineDefaultValue(char);
Mock_DefineDefaultValue(sbyte);
Mock_DefineDefaultValue(short);
Mock_DefineDefaultValue(int);
Mock_DefineDefaultValue(long);
Mock_DefineDefaultValue(intmax);
Mock_DefineDefaultValue(byte);
Mock_DefineDefaultValue(ushort);
Mock_DefineDefaultValue(uint);
Mock_DefineDefaultValue(ulong);
Mock_DefineDefaultValue(uintmax);
Mock_DefineDefaultValue(uintsize);
Mock_DefineDefaultValue(intfsize);
Mock_DefineDefaultValue(float);
Mock_DefineDefaultValue(double);
#ifdef CFLAT_INTPTR
Mock_DefineDefaultValue(intptr);
#endif
#ifdef CFLAT_UINTPTR
Mock_DefineDefaultValue(uintptr);
#endif

/* Public variables */
public Action Mock_History[CFLAT_MOCK_MAX_HISTORY];
public int Mock_History_Length;

public __CFLAT_MOCK_MATCH __CFLAT_MOCK_MATCH_TEMP;
public __CFLAT_MOCK_MATCHER __CFLAT_MOCK_MATCHER_TEMP;

/**************************************/
/* Public function definitions        */
/**************************************/

public bool __CLFAT_MOCK_MATCH_CSTRING(const void *matcherValue, const void *argValue)
{
    assert(matcherValue != null);
    assert(argValue != null);

    return CString_Equals(*(const char**)matcherValue, *(const char**)argValue);
}

public bool __CLFAT_MOCK_MATCH_STRING(const void *matcherValue, const void *argValue)
{
    assert(matcherValue != null);
    assert(argValue != null);

    return String_Equals(*(const String**)matcherValue, *(const String**)argValue);
}

public bool __CLFAT_MOCK_MATCH_NOT_NULL(const void *argValue)
{
    assert(argValue != null);

    return *(const void**)argValue != null;
}

public void __CFLAT_MOCK_ASSERT(bool condition, const char *file, int line, const char *format, ...)
{
    if (!condition) {
        VarArgsList args;
        VarArgs_Start(args, format);

        __CFLAT_EXCEPTION_THROW_NEW_TEMPSTRING(
            AssertionException, String_FormatCStringV(format, args), file, line, null);

        VarArgs_End(args);
    }
}

public void __CFLAT_MOCK_VALIDATE(
    bool condition,
    ExceptionType exception,
    const char *message,
    const char *file,
    int line)
{
    if (!condition) {
        __CFLAT_EXCEPTION_THROW_NEW(exception, message, file, line, null);
    }
}

public void __CFLAT_MOCK_VALIDATE_STATE(bool condition, const char *message, const char *file, int line)
{
    __CFLAT_MOCK_VALIDATE(condition, InvalidOperationException, message, file, line);
}
