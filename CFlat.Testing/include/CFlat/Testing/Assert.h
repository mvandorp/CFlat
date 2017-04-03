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

/**
 * @file Assert.h
 */

#ifndef CFLAT_TESTING_ASSERT_H
#define CFLAT_TESTING_ASSERT_H

#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Exceptions.h"
#include "CFlat/Language/Integer.h"

typedef struct String String;

/* Macros */
#define __CFLAT_TESTING_ASSERT(condition, message) \
    ((void)(!!(condition) || (throw_new(AssertionException, message), 0)))

/// <summary>
/// Verifies that two characters are equal.
/// </summary>
/// <param name="expected">The first character to compare. This is the character the unit test expects.</param>
/// <param name="actual">The second character to compare. This is the character the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is not equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreEqualChar(expected, actual) \
    __CFLAT_TESTING_AreEqualChar(expected, actual, false, #actual, __FILE__, __LINE__, false)

/// <summary>
/// Verifies that two null-terminated strings are equal.
/// </summary>
/// <param name="expected">The first string to compare. This is the string the unit test expects.</param>
/// <param name="actual">The second string to compare. This is the string the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is not equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreEqualCString(expected, actual) \
    __CFLAT_TESTING_AreEqualCString(expected, actual, false, #actual, __FILE__, __LINE__, false)

/// <summary>
/// Verifies that two numbers are equal.
/// </summary>
/// <param name="expected">The first number to compare. This is the number the unit test expects.</param>
/// <param name="actual">The second number to compare. This is the number the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is not equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreEqualDouble(expected, actual) \
    __CFLAT_TESTING_AreEqualDouble(expected, actual, false, #actual, __FILE__, __LINE__)

/// <summary>
/// Verifies that two numbers are equal.
/// </summary>
/// <param name="expected">The first number to compare. This is the number the unit test expects.</param>
/// <param name="actual">The second number to compare. This is the number the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is not equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreEqualInt(expected, actual) \
    __CFLAT_TESTING_AreEqualInt(expected, actual, false, #actual, __FILE__, __LINE__)

/// <summary>
/// Verifies that two pointers are equal.
/// </summary>
/// <param name="expected">The first pointers to compare. This is the pointers the unit test expects.</param>
/// <param name="actual">The second pointers to compare. This is the pointers the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is not equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreEqualPointer(expected, actual) \
    __CFLAT_TESTING_AreEqualPointer(expected, actual, false, #actual, __FILE__, __LINE__)

/// <summary>
/// Verifies that two numbers are equal.
/// </summary>
/// <param name="expected">The first number to compare. This is the number the unit test expects.</param>
/// <param name="actual">The second number to compare. This is the number the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is not equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreEqualUInt(expected, actual) \
    __CFLAT_TESTING_AreEqualUInt(expected, actual, false, #actual, __FILE__, __LINE__)

/// <summary>
/// Verifies that two strings are equal.
/// </summary>
/// <param name="expected">The first string to compare. This is the string the unit test expects.</param>
/// <param name="actual">The second string to compare. This is the string the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is not equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreEqualString(expected, actual) \
    __CFLAT_TESTING_AreEqualString(expected, actual, false, #actual, __FILE__, __LINE__, false)

/// <summary>
/// Verifies that two characters are not equal.
/// </summary>
/// <param name="expected">
///     The first character to compare. This is the character the unit test expects not to match
///     <paramref name="actual"/>.
/// </param>
/// <param name="actual">The second character to compare. This is the character the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreNotEqualChar(expected, actual) \
    __CFLAT_TESTING_AreEqualChar(expected, actual, true, #actual, __FILE__, __LINE__, false)

/// <summary>
/// Verifies that two null-terminated strings are not equal.
/// </summary>
/// <param name="expected">
///     The first string to compare. This is the string the unit test expects to not match <paramref name="actual"/>.
/// </param>
/// <param name="actual">The second string to compare. This is the string the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreNotEqualCString(notExpected, actual) \
    __CFLAT_TESTING_AreEqualCString(notExpected, actual, true, #actual, __FILE__, __LINE__, false)

/// <summary>
/// Verifies that two numbers are not equal.
/// </summary>
/// <param name="expected">
///     The first number to compare. This is the number the unit test expects to not match <paramref name="actual"/>.
/// </param>
/// <param name="actual">The second number to compare. This is the number the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreNotEqualDouble(notExpected, actual) \
    __CFLAT_TESTING_AreEqualDouble(notExpected, actual, true, #actual, __FILE__, __LINE__)

/// <summary>
/// Verifies that two numbers are not equal.
/// </summary>
/// <param name="expected">
///     The first number to compare. This is the number the unit test expects to not match <paramref name="actual"/>.
/// </param>
/// <param name="actual">The second number to compare. This is the number the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreNotEqualInt(notExpected, actual) \
    __CFLAT_TESTING_AreEqualInt(notExpected, actual, true, #actual, __FILE__, __LINE__)

/// <summary>
/// Verifies that two pointers are not equal.
/// </summary>
/// <param name="expected">
///     The first pointer to compare. This is the pointer the unit test expects to not match <paramref name="actual"/>.
/// </param>
/// <param name="actual">The pointer number to compare. This is the pointer the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreNotEqualPointer(notExpected, actual) \
    __CFLAT_TESTING_AreEqualPointer(notExpected, actual, true, #actual, __FILE__, __LINE__)

/// <summary>
/// Verifies that two numbers are not equal.
/// </summary>
/// <param name="expected">
///     The first number to compare. This is the number the unit test expects to not match <paramref name="actual"/>.
/// </param>
/// <param name="actual">The second number to compare. This is the number the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreNotEqualUInt(notExpected, actual) \
    __CFLAT_TESTING_AreEqualUInt(notExpected, actual, true, #actual, __FILE__, __LINE__)

/// <summary>
/// Verifies that two strings are not equal.
/// </summary>
/// <param name="expected">
///     The first string to compare. This is the string the unit test expects to not match <paramref name="actual"/>.
/// </param>
/// <param name="actual">The string number to compare. This is the string the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreNotEqualString(notExpected, actual) \
    __CFLAT_TESTING_AreEqualString(notExpected, actual, true, #actual, __FILE__, __LINE__, false)

/// <summary>
/// Verifies that two values are equal.
/// </summary>
/// <param name="expected">The first value to compare. This is the value the unit test expects.</param>
/// <param name="actual">The second value to compare. This is the value the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is not equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreEqual(expected, actual) __CFLAT_TESTING_ASSERT( \
    (expected) == (actual), "Expected <" #expected ">, but was <" #actual ">")

/// <summary>
/// Verifies that two values are not equal.
/// </summary>
/// <param name="expected">
///     The first value to compare. This is the value the unit test expects to not match <paramref name="actual"/>.
/// </param>
/// <param name="actual">The second value to compare. This is the value the unit test produced.</param>
/// <exception cref="::AssertionException">
///     <paramref name="actual"/> is equal to <paramref name="expected"/>.
/// </exception>
#define Assert_AreNotEqual(expected, actual) __CFLAT_TESTING_ASSERT( \
    (expected) != (actual), "Not expected <" #expected ">, but was <" #actual ">")

/// <summary>
/// Fails the unit test.
/// </summary>
/// <exception cref="::AssertionException">Always thrown.</exception>
#define Assert_Fail() throw_new(AssertionException, "")

/// <summary>
/// Fails the unit test.
/// </summary>
/// <param name="message">The message to display; or <see cref="null"/> to use the default message.</param>
/// <exception cref="::AssertionException">Always thrown.</exception>
#define Assert_Fail_WithMessage(message) throw_new(AssertionException, message)

/// <summary>
/// Skips the unit test.
/// </summary>
/// <exception cref="::IgnoreException">Always thrown.</exception>
#define Assert_Ignore() throw_new(IgnoreException, "")

/// <summary>
/// Skips the unit test.
/// </summary>
/// <param name="message">The message to display; or <see cref="null"/> to use the default message.</param>
/// <exception cref="::IgnoreException">Always thrown.</exception>
#define Assert_Ignore_WithMessage(message) throw_new(IgnoreException, message)

/// <summary>
/// Indicates that the unit test was inconclusive.
/// </summary>
/// <exception cref="::InconclusiveException">Always thrown.</exception>
#define Assert_Inconclusive() throw_new(InconclusiveException, "")

/// <summary>
/// Indicates that the unit test was inconclusive.
/// </summary>
/// <param name="message">The message to display; or <see cref="null"/> to use the default message.</param>
/// <exception cref="::InconclusiveException">Always thrown.</exception>
#define Assert_Inconclusive_WithMessage(message) throw_new(InconclusiveException, message)

/// <summary>
/// Verifies that the condition is <see cref="false"/>.
/// </summary>
/// <param name="condition">The condition the unit test expects to evaluate to <see cref="false"/>.</param>
/// <exception cref="::AssertionException">
///     <paramref name="condition"/> evaluates to <paramref name="true"/>.
/// </exception>
#define Assert_IsFalse(condition) __CFLAT_TESTING_ASSERT(!(condition), #condition)

/// <summary>
/// Verifies that the pointer is not <see cref="null"/>.
/// </summary>
/// <param name="ptr">The pointer the unit test expects to not equal <see cref="null"/>.</param>
/// <exception cref="::AssertionException">
///     <paramref name="ptr"/> is <paramref name="null"/>.
/// </exception>
#define Assert_IsNotNull(ptr) __CFLAT_TESTING_IsNull(ptr, true, #ptr, __FILE__, __LINE__)

/// <summary>
/// Verifies that the pointer is <see cref="null"/>.
/// </summary>
/// <param name="ptr">The pointer the unit test expects to equal <see cref="null"/>.</param>
/// <exception cref="::AssertionException">
///     <paramref name="ptr"/> is not <paramref name="null"/>.
/// </exception>
#define Assert_IsNull(ptr) __CFLAT_TESTING_IsNull(ptr, false, #ptr, __FILE__, __LINE__)

/// <summary>
/// Verifies that the condition is <see cref="true"/>.
/// </summary>
/// <param name="condition">The condition the unit test expects to evaluate to <see cref="true"/>.</param>
/// <exception cref="::AssertionException">
///     <paramref name="condition"/> evaluates to <paramref name="false"/>.
/// </exception>
#define Assert_IsTrue(condition) __CFLAT_TESTING_ASSERT(condition, #condition)

/// <summary>
/// Passes the unit test.
/// </summary>
/// <exception cref="::SuccessException">Always thrown.</exception>
#define Assert_Pass() throw_new(SuccessException, "")

/// <summary>
/// Passes the unit test.
/// </summary>
/// <param name="message">The message to display; or <see cref="null"/> to use the default message.</param>
/// <exception cref="::SuccessException">Always thrown.</exception>
#define Assert_Pass_WithMessage(message) throw_new(SuccessException, message)

/// <summary>
/// Verifies that <paramref name="action"/> throws an exception of type <see cref="exceptionType"/>, or an exception
/// of a type derived from <see cref="exceptionType"/>.
/// </summary>
/// <param name="exceptionType">The type of exception the unit test expects <paramref name="action"/> to throw.</param>
/// <param name="action">
///     The action the unit test expects to throw an exception of type <paramref name="exceptionType"/>.
/// </param>
/// <exception cref="::AssertionException">
///     <paramref name="action"/> did not throw an exception of type <paramref name="exceptionType"/>.
/// </exception>
#define Assert_Catch(exceptionType, action)                                                             \
    do {                                                                                                \
        bool __CFLAT_TESTING_threwException = false;                                                    \
                                                                                                        \
        try {                                                                                           \
            action;                                                                                     \
        }                                                                                               \
        catch (exceptionType) {                                                                         \
            __CFLAT_TESTING_threwException = true;                                                      \
        }                                                                                               \
        catch_ex (Exception, __CFLAT_TESTING_exception) {                                               \
            throw_new_tempstring(                                                                       \
                AssertionException,                                                                     \
                String_FormatCString(                                                                   \
                    "Expected <" #action "> to throw an exception compatible with <" #exceptionType ">,"\
                    " but threw <{string}>.",                                                           \
                    Exception_GetName(__CFLAT_TESTING_exception)));                                     \
        }                                                                                               \
        endtry;                                                                                         \
                                                                                                        \
        if (!__CFLAT_TESTING_threwException) {                                                          \
            Assert_Fail_WithMessage(                                                                    \
                "Expected <" #action "> to throw an exception compatible with <"#exceptionType ">.");   \
        }                                                                                               \
    }                                                                                                   \
    while ((void)false, false)

/// <summary>
/// Verifies that <paramref name="action"/> throws an exception of type <see cref="exceptionType"/>.
/// </summary>
/// <param name="exceptionType">The type of exception the unit test expects <paramref name="action"/> to throw.</param>
/// <param name="action">
///     The action the unit test expects to throw an exception of type <paramref name="exceptionType"/>.
/// </param>
/// <exception cref="::AssertionException">
///     <paramref name="action"/> did not throw an exception of type <paramref name="exceptionType"/>.
/// </exception>
#define Assert_Throws(exceptionType, action)                                                            \
    do {                                                                                                \
        bool __CFLAT_TESTING_threwException = false;                                                    \
                                                                                                        \
        try {                                                                                           \
            action;                                                                                     \
        }                                                                                               \
        catch_ex (Exception, __CFLAT_TESTING_exception) {                                               \
            if (Exception_GetType(__CFLAT_TESTING_exception) == exceptionType) {                        \
                __CFLAT_TESTING_threwException = true;                                                  \
            }                                                                                           \
            else {                                                                                      \
                throw_new_tempstring(                                                                   \
                    AssertionException,                                                                 \
                    String_FormatCString(                                                               \
                        "Expected <" #action "> to throw <" #exceptionType ">,"                         \
                        " but threw <{string}>.",                                                       \
                        Exception_GetName(__CFLAT_TESTING_exception)));                                 \
            }                                                                                           \
        }                                                                                               \
        endtry;                                                                                         \
                                                                                                        \
        if (!__CFLAT_TESTING_threwException) {                                                          \
            Assert_Fail_WithMessage("Expected <" #action "> to throw <"#exceptionType ">.");            \
        }                                                                                               \
    }                                                                                                   \
    while ((void)false, false)

/* Functions */
void __CFLAT_TESTING_AreEqualChar(
    char expected,
    char actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line,
    bool ignoreCase);
void __CFLAT_TESTING_AreEqualCString(
    const char *expected,
    const char *actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line,
    bool ignoreCase);
void __CFLAT_TESTING_AreEqualDouble(
    double expected,
    double actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line);
void __CFLAT_TESTING_AreEqualInt(
    intmax expected,
    intmax actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line);
void __CFLAT_TESTING_AreEqualPointer(
    const void *expected,
    const void *actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line);
void __CFLAT_TESTING_AreEqualUInt(
    uintmax expected,
    uintmax actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line);
void __CFLAT_TESTING_AreEqualString(
    const struct String *expected,
    const struct String *actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line,
    bool ignoreCase);
void __CFLAT_TESTING_IsNull(
    const void *actual,
    bool invert,
    const char *actualExpr,
    const char *file,
    int line);

#endif
