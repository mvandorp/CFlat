/*
 * Copyright (C) 2017 Martijn van Dorp
 *
 * This file is part of CFlat.Testing.Tests.
 *
 * CFlat.Testing.Tests is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFlat.Testing.Tests is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file Mock.h
 */

#ifndef CFLAT_TESTING_MOCK_H
#define CFLAT_TESTING_MOCK_H

/* Macros */
#ifndef CFLAT_MOCK_MAX_CONDITIONS
 /// <summary>
 /// Represents the maximum number of 'when-conditions' that can be defined per function.
 /// Define this symbol before the first inclusion of Mock.h to use a different value.
 /// </summary>
 #define CFLAT_MOCK_MAX_CONDITIONS 10
#endif

#ifndef CFLAT_MOCK_MAX_ACTIONS
 /// <summary>
 /// Represents the maximum number of actions that can be defined per condition.
 /// Define this symbol before the first inclusion of Mock.h to use a different value.
 /// </summary>
 #define CFLAT_MOCK_MAX_ACTIONS 10
#endif

#ifndef CFLAT_MOCK_MAX_HISTORY
 /// <summary>
 /// Represents the maximum number of calls saved in the call history.
 /// Define this symbol before the first inclusion of Mock.h to use a different value.
 /// </summary>
 #define CFLAT_MOCK_MAX_HISTORY 20
#endif

#ifndef CFLAT_MOCK_MAX_ARG_HISTORY
 /// <summary>
 /// Represents the maximum number of calls per function for which the argument values are saved.
 /// Define this symbol before the first inclusion of Mock.h to use a different value.
 /// </summary>
 #define CFLAT_MOCK_MAX_ARG_HISTORY 10
#endif

/// <summary>
/// Represents the maximum number of arguments a mocked function can have.
/// </summary>
#define CFLAT_MOCK_MAX_ARGS 20

/* Function macros */
#define spy(func)                               __CFLAT_MOCK__##func##_Spy
#define mock(func)                              __CFLAT_MOCK__##func##_Mock

#define Mock_ResetHistory()                     Mock_History_Length = 0
#define Mock_Reset(func)                        __CFLAT_MOCK__##func##_Reset()

#define Mock_When(func, ...)                    __CFLAT_OVERLOAD(Mock_When, CFLAT_ARG_COUNT(__VA_ARGS__), func, __VA_ARGS__)
#define Mock_Verify(func, ...)                  __CFLAT_OVERLOAD(Mock_Verify, CFLAT_ARG_COUNT(__VA_ARGS__), func, __VA_ARGS__)

#define Mock_Action(func, ...)                  __CFLAT_OVERLOAD(Mock_Action, CFLAT_ARG_COUNT(__VA_ARGS__), func, __VA_ARGS__)
#define Mock_DeclareAction(func, ...)           __CFLAT_OVERLOAD(Mock_DeclareAction, CFLAT_ARG_COUNT(__VA_ARGS__), func, __VA_ARGS__)
#define Mock_DefineAction(func, ...)            __CFLAT_OVERLOAD(Mock_DefineAction, CFLAT_ARG_COUNT(__VA_ARGS__), func, __VA_ARGS__)

#define Mock_Func(func, TReturn, ...)           __CFLAT_OVERLOAD(Mock_Func, CFLAT_ARG_COUNT(__VA_ARGS__), func, TReturn, __VA_ARGS__)
#define Mock_DeclareFunc(func, TReturn, ...)    __CFLAT_OVERLOAD(Mock_DeclareFunc, CFLAT_ARG_COUNT(__VA_ARGS__), func, TReturn, __VA_ARGS__)
#define Mock_DefineFunc(func, TReturn, ...)     __CFLAT_OVERLOAD(Mock_DefineFunc, CFLAT_ARG_COUNT(__VA_ARGS__), func, TReturn, __VA_ARGS__)

#define Mock_DefaultValue(type) \
    Mock_DeclareDefaultValue(type); \
    Mock_DefineDefaultValue(type)

#define Mock_DeclareDefaultValue(type) \
    type __CFLAT_MOCK_DEFAULT_VALUE_##type(void)

#define Mock_DefineDefaultValue(type) \
    public type __CFLAT_MOCK_DEFAULT_VALUE_##type(void) \
    { \
        __CFLAT_MOCK_RETURN_DEFAULT(type); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

/* Argument matcher macros */
#define Mock_Match_Any(type)                (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_ANY, __CFLAT_MOCK_DEFAULT_VALUE_##type())
#define Mock_Match_AnyFloat()               (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_ANY, 0)
#define Mock_Match_AnyInt()                 (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_ANY, 0)
#define Mock_Match_AnyPointer()             (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_ANY, null)
#define Mock_Match_AnyCString()             Mock_Match_AnyPointer()
#define Mock_Match_AnyString()              Mock_Match_AnyPointer()

#define Mock_Match_Equal(value)             (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_EQ, value)
#define Mock_Match_EqualString(value)       (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_EQ_STRING, value)
#define Mock_Match_EqualCString(value)      (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_EQ_CSTRING, value)
#define Mock_Match_NotEqual(value)          (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_NEQ, value)
#define Mock_Match_NotEqualString(value)    (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_NEQ_STRING, value)
#define Mock_Match_NotEqualCString(value)   (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_NEQ_CSTRING, value)
#define Mock_Match_GreaterOrEqual(value)    (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_GEQ, value)
#define Mock_Match_GreaterThan(value)       (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_GT, value)
#define Mock_Match_LessOrEqual(value)       (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_LEQ, value)
#define Mock_Match_LessThan(value)          (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_LT, value)
#define Mock_Match_NotNull()                (__CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_NOT_NULL, null)
#define Mock_Match_Custom(type, matchFunction) \
( \
    __CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_MATCHER, \
    __CFLAT_MOCK_MATCHER_TEMP = (__CFLAT_MOCK_MATCHER)(bool(*)(type))matchFunction, \
    __CFLAT_MOCK_DEFAULT_VALUE_##type() \
)

#include "Mock.hidden.h"

/* Default values for default types */
Mock_DeclareDefaultValue(char);
Mock_DeclareDefaultValue(sbyte);
Mock_DeclareDefaultValue(short);
Mock_DeclareDefaultValue(int);
Mock_DeclareDefaultValue(long);
Mock_DeclareDefaultValue(intmax);
Mock_DeclareDefaultValue(byte);
Mock_DeclareDefaultValue(ushort);
Mock_DeclareDefaultValue(uint);
Mock_DeclareDefaultValue(ulong);
Mock_DeclareDefaultValue(uintmax);
Mock_DeclareDefaultValue(uintsize);
Mock_DeclareDefaultValue(intfsize);
Mock_DeclareDefaultValue(float);
Mock_DeclareDefaultValue(double);

#ifdef CFLAT_INTPTR
 Mock_DeclareDefaultValue(intptr);
#endif

#ifdef CFLAT_UINTPTR
 Mock_DeclareDefaultValue(uintptr);
#endif

#endif
