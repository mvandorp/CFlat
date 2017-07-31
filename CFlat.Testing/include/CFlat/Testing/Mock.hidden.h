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

#ifndef CFLAT_TESTING_MOCK_INTERNAL_H
#define CFLAT_TESTING_MOCK_INTERNAL_H

#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Exceptions.h"
#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Keywords.h"
#include "CFlat/Language/Macros.h"
#include "CFlat/Memory.h"

/* Forward declarations */
typedef struct String String;

/* Public variables */
extern int Mock_History_Length;
extern Action Mock_History[CFLAT_MOCK_MAX_HISTORY];

/**************************************/
/* Hidden                             */
/**************************************/

/* Hidden types */
typedef enum __CFLAT_MOCK_MATCH {
    __CFLAT_MOCK_MATCH_ANY = 0,
    __CFLAT_MOCK_MATCH_EQ,
    __CFLAT_MOCK_MATCH_EQ_STRING,
    __CFLAT_MOCK_MATCH_EQ_CSTRING,
    __CFLAT_MOCK_MATCH_NEQ,
    __CFLAT_MOCK_MATCH_NEQ_STRING,
    __CFLAT_MOCK_MATCH_NEQ_CSTRING,
    __CFLAT_MOCK_MATCH_GEQ,
    __CFLAT_MOCK_MATCH_GT,
    __CFLAT_MOCK_MATCH_LEQ,
    __CFLAT_MOCK_MATCH_LT,
    __CFLAT_MOCK_MATCH_NOT_NULL,
    __CFLAT_MOCK_MATCH_MATCHER
} __CFLAT_MOCK_MATCH;

typedef enum __CFLAT_MOCK_ACTION {
    __CFLAT_MOCK_ACTION_DO_NOTHING = 0,
    __CFLAT_MOCK_ACTION_RETURN = 0,
    __CFLAT_MOCK_ACTION_CUSTOM,
    __CFLAT_MOCK_ACTION_THROW
} __CFLAT_MOCK_ACTION;

typedef struct __CFLAT_MOCK_VERIFIERS_TYPE {
    void(*AtLeast)(int n);
    void(*AtLeastOnce)(void);
    void(*AtMost)(int n);
    void(*Never)(void);
    void(*Once)(void);
    void(*Times)(int n);
} __CFLAT_MOCK_VERIFIERS_TYPE;

typedef bool (*__CFLAT_MOCK_MATCHER)(const void *value);

/* Hidden variables */
extern __CFLAT_MOCK_MATCH __CFLAT_MOCK_MATCH_TEMP;
extern __CFLAT_MOCK_MATCHER __CFLAT_MOCK_MATCHER_TEMP;

/* Hidden functions */
bool __CLFAT_MOCK_MATCH_CSTRING(const void *matcherValue, const void *argValue);
bool __CLFAT_MOCK_MATCH_STRING(const void *matcherValue, const void *argValue);
bool __CLFAT_MOCK_MATCH_NOT_NULL(const void *argValue);

void __CFLAT_MOCK_ASSERT(bool condition, const char *file, int line, const char *format, ...);
void __CFLAT_MOCK_VALIDATE(bool condition, ExceptionType exception, const char *message, const char *file, int line);
void __CFLAT_MOCK_VALIDATE_STATE(bool condition, const char *message, const char *file, int line);

/**************************************/
/* Common macros                      */
/**************************************/

#define __CFLAT_MOCK_IGNORE_SEMICOLON               extern int __CFLAT_MOCK_IGNORE

#define __CFLAT_MOCK_ACTION_TYPE(func)              __CFLAT_MOCK__##func##_Action
#define __CFLAT_MOCK_CONDITION_TYPE(func)           __CFLAT_MOCK__##func##_Condition
#define __CFLAT_MOCK_DATA_TYPE(func)                __CFLAT_MOCK__##func##_Data
#define __CFLAT_MOCK_FUNCTIONS_TYPE(func)           __CFLAT_MOCK__##func##_FunctionsStruct

#define __CFLAT_MOCK_DATA(func)                     __CFLAT_MOCK__##func
#define __CFLAT_MOCK_FUNCTIONS(func)                __CFLAT_MOCK__##func##_Functions
#define __CFLAT_MOCK_VERIFIERS(func)                    __CFLAT_MOCK__##func##_Verifiers

#define __CFLAT_MOCK_COUNT_VERIFIER_MATCHES(func)       __CFLAT_MOCK__##func##_CountVerifierMatches()
#define __CFLAT_MOCK_MATCH_ARGS(func, condition, ...)   __CFLAT_MOCK__##func##_MatchArgs(condition, __VA_ARGS__)

#define __CFLAT_MOCK_DATA_CONDITIONS(func)          __CFLAT_MOCK_DATA(func).Conditions
#define __CFLAT_MOCK_DATA_CONDITION_COUNT(func)     __CFLAT_MOCK_DATA(func).ConditionCount
#define __CFLAT_MOCK_DATA_CALL_COUNT(func)          __CFLAT_MOCK_DATA(func).CallCount
#define __CFLAT_MOCK_DATA_ARG_VALUE(func, index)    __CFLAT_MOCK_DATA(func).Arg##index##Value
#define __CFLAT_MOCK_DATA_ARG_HISTORY(func, index)  __CFLAT_MOCK_DATA(func).Arg##index##History

#define __CFLAT_MOCK_REGISTER_CALL(func)                        \
    do {                                                        \
        if (Mock_History_Length < CFLAT_MOCK_MAX_HISTORY)       \
            Mock_History[Mock_History_Length++] = (Action)func; \
    }                                                           \
    while ((void)false, false)
#define __CFLAT_MOCK_INCREMENT_CALLS(func)          __CFLAT_MOCK_DATA_CALL_COUNT(func)++
#define __CFLAT_MOCK_SAVE_ARG(func, index)          __CFLAT_MOCK_DATA_ARG_VALUE(func, index) = arg##index
#define __CFLAT_MOCK_SAVE_ARG_HISTORY(func, index)  __CFLAT_MOCK_DATA_ARG_HISTORY(func, index)[__CFLAT_MOCK_DATA_CALL_COUNT(func)] = arg##index
#define __CFLAT_MOCK_CAN_SAVE_HISTORY(func)         __CFLAT_MOCK_DATA_CALL_COUNT(func) < CFLAT_MOCK_MAX_ARG_HISTORY

#define __CFLAT_MOCK_CONDITION(func, index)         __CFLAT_MOCK_DATA_CONDITIONS(func)[index]
#define __CFLAT_MOCK_CURRENT_CONDITION(func)        __CFLAT_MOCK_CONDITION(func, __CFLAT_MOCK_DATA_CONDITION_COUNT(func))
#define __CFLAT_MOCK_LAST_CONDITION(func)           __CFLAT_MOCK_CONDITION(func, __CFLAT_MOCK_DATA_CONDITION_COUNT(func) - 1)
#define __CFLAT_MOCK_VERIFIER_CONDITION_INDEX       CFLAT_MOCK_MAX_CONDITIONS
#define __CFLAT_MOCK_VERIFIER_CONDITION(func)       __CFLAT_MOCK_CONDITION(func, __CFLAT_MOCK_VERIFIER_CONDITION_INDEX)

#define __CFLAT_MOCK_CAN_ADD_ACTION(func)           __CFLAT_MOCK_LAST_CONDITION(func).ActionCount < CFLAT_MOCK_MAX_ACTIONS
#define __CFLAT_MOCK_CAN_ADD_CONDITION(func)        __CFLAT_MOCK_DATA_CONDITION_COUNT(func) < CFLAT_MOCK_MAX_CONDITIONS

#define __CFLAT_MOCK_ERR_MAX_CONDITIONS             "Attempted to add condition when the maximum number of conditions for the function has been reached."
#define __CFLAT_MOCK_ERR_MAX_ACTIONS                "Attempted to add action when the maximum number of actions for the condition has been reached."
#define __CFLAT_MOCK_ERR_NO_CONDITION               "Attempted to add action when no condition was specified."
#define __CFLAT_MOCK_ERR_NO_ACTION                  "Condition did not have any actions specified."

/**************************************/
/* Common declarations                */
/**************************************/

#define __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, ...) TReturn __CFLAT_MOCK__##func##_Mock(__VA_ARGS__)
#define __CFLAT_MOCK_DECLARE_SPY(func, TReturn, ...) TReturn __CFLAT_MOCK__##func##_Spy(__VA_ARGS__)

#define __CFLAT_MOCK_DECLARE_DATA_COMMON(func)                                                                          \
    __CFLAT_MOCK_CONDITION_TYPE(func) Conditions[CFLAT_MOCK_MAX_CONDITIONS + 1];                                        \
    int ConditionCount;                                                                                                 \
    int CallCount

#define __CFLAT_MOCK_DECLARE_DATA_ARG(type, index)                                                                      \
    type Arg##index##Value;                                                                                             \
    type Arg##index##History[CFLAT_MOCK_MAX_ARG_HISTORY]

#define __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func)                                                                     \
    __CFLAT_MOCK_ACTION_TYPE(func) Actions[CFLAT_MOCK_MAX_ACTIONS];                                                     \
    int ActionIndex;                                                                                                    \
    int ActionCount;                                                                                                    \
    const char *File;                                                                                                   \
    int Line

#define __CFLAT_MOCK_DECLARE_CONDITION_ARG(type, index)                                                                 \
    __CFLAT_MOCK_MATCH Arg##index##Match;                                                                               \
    __CFLAT_MOCK_MATCHER Arg##index##Matcher;                                                                           \
    type Arg##index##Value

#define __CFLAT_MOCK_DECLARE_ACTION_TYPE_ACTION(func, ...)                                                              \
    typedef struct __CFLAT_MOCK_ACTION_TYPE(func) {                                                                     \
        __CFLAT_MOCK_ACTION Type;                                                                                       \
        union {                                                                                                         \
            ExceptionType Exception;                                                                                    \
            void (*CustomFunction)(__VA_ARGS__);                                                                        \
        } Data;                                                                                                         \
    } __CFLAT_MOCK_ACTION_TYPE(func)

#define __CFLAT_MOCK_DECLARE_ACTION_TYPE_FUNCTION(func, TReturn, ...)                                                   \
    typedef struct __CFLAT_MOCK_ACTION_TYPE(func) {                                                                     \
        __CFLAT_MOCK_ACTION Type;                                                                                       \
        union {                                                                                                         \
            ExceptionType Exception;                                                                                    \
            TReturn (*CustomFunction)(__VA_ARGS__);                                                                     \
            TReturn ReturnValue;                                                                                        \
        } Data;                                                                                                         \
    } __CFLAT_MOCK_ACTION_TYPE(func)

#define __CFLAT_MOCK_DECLARE_COMMON(TYPE, func, ...) CFLAT_EXPAND(__CFLAT_MOCK_DECLARE_COMMON_##TYPE(func, __VA_ARGS__))

#define __CFLAT_MOCK_DECLARE_COMMON_ACTION(func, TReturn, ...)                                                          \
    __CFLAT_MOCK_DECLARE_FUNCTIONS_STRUCT_ACTION(func, __VA_ARGS__);                                                    \
    __CFLAT_MOCK_DECLARE_VERIFIERS_STRUCT(func);                                                                        \
    __CFLAT_MOCK_DECLARE_ACTION_TYPE_ACTION(func, __VA_ARGS__)

#define __CFLAT_MOCK_DECLARE_COMMON_FUNCTION(func, TReturn, ...)                                                        \
    __CFLAT_MOCK_DECLARE_FUNCTIONS_STRUCT_FUNCTION(func, TReturn, __VA_ARGS__);                                         \
    __CFLAT_MOCK_DECLARE_VERIFIERS_STRUCT(func);                                                                        \
    __CFLAT_MOCK_DECLARE_ACTION_TYPE_FUNCTION(func, TReturn, __VA_ARGS__)

#define __CFLAT_MOCK_DECLARE_VERIFIERS_STRUCT(func) \
    extern const __CFLAT_MOCK_VERIFIERS_TYPE __CFLAT_MOCK_VERIFIERS(func)

#define __CFLAT_MOCK_DECLARE_FUNCTIONS_STRUCT_ACTION(func, ...)                                                         \
    typedef struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) {                                                                  \
        struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) (*DoInstead)(void (*action)(__VA_ARGS__));                             \
        struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) (*DoNothing)(void);                                                    \
        struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) (*Throw)(ExceptionType);                                               \
        struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) (*CallRealFunction)(void);                                             \
    } __CFLAT_MOCK_FUNCTIONS_TYPE(func);                                                                                \
    extern const __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK_FUNCTIONS(func)

#define __CFLAT_MOCK_DECLARE_FUNCTIONS_STRUCT_FUNCTION(func, TReturn, ...)                                              \
    typedef struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) {                                                                  \
        struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) (*Answer)(TReturn (*function)(__VA_ARGS__));                           \
        struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) (*Return)(TReturn value);                                              \
        struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) (*Throw)(ExceptionType);                                               \
        struct __CFLAT_MOCK_FUNCTIONS_TYPE(func) (*CallRealFunction)(void);                                             \
    } __CFLAT_MOCK_FUNCTIONS_TYPE(func);                                                                                \
    extern const __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK_FUNCTIONS(func)

#define __CFLAT_MOCK_DECLARE_RESET(func) \
    void __CFLAT_MOCK__##func##_Reset(void)

/**************************************/
/* Common definitions                 */
/**************************************/

#define __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, ...) public TReturn __CFLAT_MOCK__##func##_Mock(__VA_ARGS__)
#define __CFLAT_MOCK_DEFINE_SPY(func, TReturn, ...) public TReturn __CFLAT_MOCK__##func##_Spy(__VA_ARGS__)

#define __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, ...) CFLAT_EXPAND(__CFLAT_MOCK_DEFINE_COMMON_##TYPE(func, __VA_ARGS__))

#define __CFLAT_MOCK_DEFINE_COMMON_ACTION(func, TReturn, ...)                                                           \
    __CFLAT_MOCK_DEFINE_DO_INSTEAD(func, __VA_ARGS__);                                                                  \
    __CFLAT_MOCK_DEFINE_DO_NOTHING(func);                                                                               \
    __CFLAT_MOCK_DEFINE_THEN_THROW(func);                                                                               \
    __CFLAT_MOCK_DEFINE_CALL_REAL_FUNCTION(func);                                                                       \
    __CFLAT_MOCK_DEFINE_FUNCTIONS_STRUCT_ACTION(func);                                                                  \
    __CFLAT_MOCK_DEFINE_VERIFIERS(func);                                                                                \
    __CFLAT_MOCK_DEFINE_VERIFIERS_STRUCT(func)

#define __CFLAT_MOCK_DEFINE_COMMON_FUNCTION(func, TReturn, ...)                                                         \
    __CFLAT_MOCK_DEFINE_THEN_ANSWER(func, TReturn, __VA_ARGS__);                                                        \
    __CFLAT_MOCK_DEFINE_THEN_RETURN(func, TReturn);                                                                     \
    __CFLAT_MOCK_DEFINE_THEN_THROW(func);                                                                               \
    __CFLAT_MOCK_DEFINE_CALL_REAL_FUNCTION(func);                                                                       \
    __CFLAT_MOCK_DEFINE_FUNCTIONS_STRUCT_FUNCTION(func);                                                                \
    __CFLAT_MOCK_DEFINE_VERIFIERS(func);                                                                                \
    __CFLAT_MOCK_DEFINE_VERIFIERS_STRUCT(func)

#define __CFLAT_MOCK_DEFINE_DO_INSTEAD(func, ...)                                                                       \
    private __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK__##func##_DoInstead(void (*action)(__VA_ARGS__))             \
    {                                                                                                                   \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_DATA_CONDITION_COUNT(func) > 0, __CFLAT_MOCK_ERR_NO_CONDITION, __FILE__, __LINE__); \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_CAN_ADD_ACTION(func), __CFLAT_MOCK_ERR_MAX_ACTIONS, __CFLAT_MOCK_LAST_CONDITION(func).File, __CFLAT_MOCK_LAST_CONDITION(func).Line); \
                                                                                                                        \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Type = __CFLAT_MOCK_ACTION_CUSTOM; \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Data.CustomFunction = action; \
        __CFLAT_MOCK_LAST_CONDITION(func).ActionCount++;                                                                \
                                                                                                                        \
        return __CFLAT_MOCK_FUNCTIONS(func);                                                                            \
    }                                                                                                                   \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_DO_NOTHING(func)                                                                            \
    private __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK__##func##_DoNothing(void)                                    \
    {                                                                                                                   \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_DATA_CONDITION_COUNT(func) > 0, __CFLAT_MOCK_ERR_NO_CONDITION, __FILE__, __LINE__); \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_CAN_ADD_ACTION(func), __CFLAT_MOCK_ERR_MAX_ACTIONS, __CFLAT_MOCK_LAST_CONDITION(func).File, __CFLAT_MOCK_LAST_CONDITION(func).Line); \
                                                                                                                        \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Type = __CFLAT_MOCK_ACTION_DO_NOTHING; \
        __CFLAT_MOCK_LAST_CONDITION(func).ActionCount++;                                                                \
                                                                                                                        \
        return __CFLAT_MOCK_FUNCTIONS(func);                                                                            \
    }                                                                                                                   \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_THEN_ANSWER(func, TResult, ...)                                                             \
    private __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK__##func##_Answer(TResult (*function)(__VA_ARGS__))           \
    {                                                                                                                   \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_DATA_CONDITION_COUNT(func) > 0, __CFLAT_MOCK_ERR_NO_CONDITION, __FILE__, __LINE__); \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_CAN_ADD_ACTION(func), __CFLAT_MOCK_ERR_MAX_ACTIONS, __CFLAT_MOCK_LAST_CONDITION(func).File, __CFLAT_MOCK_LAST_CONDITION(func).Line); \
                                                                                                                        \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Type = __CFLAT_MOCK_ACTION_CUSTOM; \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Data.CustomFunction = function; \
        __CFLAT_MOCK_LAST_CONDITION(func).ActionCount++;                                                                \
                                                                                                                        \
        return __CFLAT_MOCK_FUNCTIONS(func);                                                                            \
    }                                                                                                                   \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_THEN_RETURN(func, TResult)                                                                  \
    private __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK__##func##_Return(TResult value)                              \
    {                                                                                                                   \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_DATA_CONDITION_COUNT(func) > 0, __CFLAT_MOCK_ERR_NO_CONDITION, __FILE__, __LINE__); \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_CAN_ADD_ACTION(func), __CFLAT_MOCK_ERR_MAX_ACTIONS, __CFLAT_MOCK_LAST_CONDITION(func).File, __CFLAT_MOCK_LAST_CONDITION(func).Line); \
                                                                                                                        \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Type = __CFLAT_MOCK_ACTION_RETURN; \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Data.ReturnValue = value; \
        __CFLAT_MOCK_LAST_CONDITION(func).ActionCount++;                                                                \
                                                                                                                        \
        return __CFLAT_MOCK_FUNCTIONS(func);                                                                            \
    }                                                                                                                   \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_THEN_THROW(func)                                                                            \
    private __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK__##func##_Throw(ExceptionType exception)                     \
    {                                                                                                                   \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_DATA_CONDITION_COUNT(func) > 0, __CFLAT_MOCK_ERR_NO_CONDITION, __FILE__, __LINE__); \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_CAN_ADD_ACTION(func), __CFLAT_MOCK_ERR_MAX_ACTIONS, __CFLAT_MOCK_LAST_CONDITION(func).File, __CFLAT_MOCK_LAST_CONDITION(func).Line); \
                                                                                                                        \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Type = __CFLAT_MOCK_ACTION_THROW; \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Data.Exception = exception; \
        __CFLAT_MOCK_LAST_CONDITION(func).ActionCount++;                                                                \
                                                                                                                        \
        return __CFLAT_MOCK_FUNCTIONS(func);                                                                            \
    }                                                                                                                   \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_CALL_REAL_FUNCTION(func)                                                                    \
    private __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK__##func##_CallRealFunction(void)                             \
    {                                                                                                                   \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_DATA_CONDITION_COUNT(func) > 0, __CFLAT_MOCK_ERR_NO_CONDITION, __FILE__, __LINE__); \
        __CFLAT_MOCK_VALIDATE_STATE(__CFLAT_MOCK_CAN_ADD_ACTION(func), __CFLAT_MOCK_ERR_MAX_ACTIONS, __CFLAT_MOCK_LAST_CONDITION(func).File, __CFLAT_MOCK_LAST_CONDITION(func).Line); \
                                                                                                                        \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Type = __CFLAT_MOCK_ACTION_CUSTOM; \
        __CFLAT_MOCK_LAST_CONDITION(func).Actions[__CFLAT_MOCK_LAST_CONDITION(func).ActionCount].Data.CustomFunction = &func; \
        __CFLAT_MOCK_LAST_CONDITION(func).ActionCount++;                                                                \
                                                                                                                        \
        return __CFLAT_MOCK_FUNCTIONS(func);                                                                            \
    }                                                                                                                   \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_FUNCTIONS_STRUCT_ACTION(func)                                                               \
    const __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK_FUNCTIONS(func) = {                                            \
        &__CFLAT_MOCK__##func##_DoInstead,                                                                              \
        &__CFLAT_MOCK__##func##_DoNothing,                                                                              \
        &__CFLAT_MOCK__##func##_Throw,                                                                                  \
        &__CFLAT_MOCK__##func##_CallRealFunction,                                                                       \
    }

#define __CFLAT_MOCK_DEFINE_FUNCTIONS_STRUCT_FUNCTION(func)                                                             \
    const __CFLAT_MOCK_FUNCTIONS_TYPE(func) __CFLAT_MOCK_FUNCTIONS(func) = {                                            \
        &__CFLAT_MOCK__##func##_Answer,                                                                                 \
        &__CFLAT_MOCK__##func##_Return,                                                                                 \
        &__CFLAT_MOCK__##func##_Throw,                                                                                  \
        &__CFLAT_MOCK__##func##_CallRealFunction,                                                                       \
    }

#define __CFLAT_MOCK_DEFINE_VERIFIERS(func)                                                                             \
    private void __CFLAT_MOCK__##func##_AtLeast(int n)                                                                  \
    {                                                                                                                   \
        const char *file = __CFLAT_MOCK_VERIFIER_CONDITION(func).File;                                                  \
        int line = __CFLAT_MOCK_VERIFIER_CONDITION(func).Line;                                                          \
        int matches = __CFLAT_MOCK_COUNT_VERIFIER_MATCHES(func);                                                        \
        __CFLAT_MOCK_ASSERT(matches >= n, file, line,                                                                   \
            "Expected at least {int} calls to " #func ". Actual: {int}.", n, matches);                                  \
    }                                                                                                                   \
    private void __CFLAT_MOCK__##func##_AtLeastOnce(void)                                                               \
    {                                                                                                                   \
        const char *file = __CFLAT_MOCK_VERIFIER_CONDITION(func).File;                                                  \
        int line = __CFLAT_MOCK_VERIFIER_CONDITION(func).Line;                                                          \
        int matches = __CFLAT_MOCK_COUNT_VERIFIER_MATCHES(func);                                                        \
        __CFLAT_MOCK_ASSERT(matches >= 1, file, line,                                                                   \
            "Expected at least one call to " #func ". Actual: {int}.", matches);                                        \
    }                                                                                                                   \
    private void __CFLAT_MOCK__##func##_AtMost(int n)                                                                   \
    {                                                                                                                   \
        const char *file = __CFLAT_MOCK_VERIFIER_CONDITION(func).File;                                                  \
        int line = __CFLAT_MOCK_VERIFIER_CONDITION(func).Line;                                                          \
        int matches = __CFLAT_MOCK_COUNT_VERIFIER_MATCHES(func);                                                        \
        __CFLAT_MOCK_ASSERT(matches <= n, file, line,                                                                   \
            "Expected at most {int} calls to " #func ". Actual: {int}.", n, matches);                                   \
    }                                                                                                                   \
    private void __CFLAT_MOCK__##func##_Never(void)                                                                     \
    {                                                                                                                   \
        const char *file = __CFLAT_MOCK_VERIFIER_CONDITION(func).File;                                                  \
        int line = __CFLAT_MOCK_VERIFIER_CONDITION(func).Line;                                                          \
        int matches = __CFLAT_MOCK_COUNT_VERIFIER_MATCHES(func);                                                        \
        __CFLAT_MOCK_ASSERT(matches == 0, file, line,                                                                   \
            "Expected no calls to " #func ". Actual: {int}.", matches);                                                 \
    }                                                                                                                   \
    private void __CFLAT_MOCK__##func##_Once(void)                                                                      \
    {                                                                                                                   \
        const char *file = __CFLAT_MOCK_VERIFIER_CONDITION(func).File;                                                  \
        int line = __CFLAT_MOCK_VERIFIER_CONDITION(func).Line;                                                          \
        int matches = __CFLAT_MOCK_COUNT_VERIFIER_MATCHES(func);                                                        \
        __CFLAT_MOCK_ASSERT(matches == 1, file, line,                                                                   \
            "Expected one call to " #func ". Actual: {int}.", matches);                                                 \
    }                                                                                                                   \
    private void __CFLAT_MOCK__##func##_Times(int n)                                                                    \
    {                                                                                                                   \
        const char *file = __CFLAT_MOCK_VERIFIER_CONDITION(func).File;                                                  \
        int line = __CFLAT_MOCK_VERIFIER_CONDITION(func).Line;                                                          \
        int matches = __CFLAT_MOCK_COUNT_VERIFIER_MATCHES(func);                                                        \
        __CFLAT_MOCK_ASSERT(matches == n, file, line,                                                                   \
            "Expected {int} calls to " #func ". Actual: {int}.", n, matches);                                           \
    }                                                                                                                   \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_VERIFIERS_STRUCT(func)                                                                      \
    const __CFLAT_MOCK_VERIFIERS_TYPE __CFLAT_MOCK_VERIFIERS(func) = {                                                  \
        &__CFLAT_MOCK__##func##_AtLeast,                                                                                \
        &__CFLAT_MOCK__##func##_AtLeastOnce,                                                                            \
        &__CFLAT_MOCK__##func##_AtMost,                                                                                 \
        &__CFLAT_MOCK__##func##_Never,                                                                                  \
        &__CFLAT_MOCK__##func##_Once,                                                                                   \
        &__CFLAT_MOCK__##func##_Times,                                                                                  \
    }

#define __CFLAT_MOCK_DEFINE_RESET(func)                                                                                 \
    public void __CFLAT_MOCK__##func##_Reset(void)                                                                      \
    {                                                                                                                   \
        Memory_Zero(&__CFLAT_MOCK_DATA(func), sizeof(__CFLAT_MOCK_DATA_TYPE(func)));                                    \
    }                                                                                                                   \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_DATA(func) \
    public __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func)

/**************************************/
/* Function snippets                  */
/**************************************/

#define __CFLAT_MOCK_RETURN_DEFAULT(type)                                                                               \
    do {                                                                                                                \
        type __CFLAT_MOCK_DEFAULT_VALUE;                                                                                \
        Memory_Zero(&__CFLAT_MOCK_DEFAULT_VALUE, sizeof(type));                                                         \
        return __CFLAT_MOCK_DEFAULT_VALUE;                                                                              \
    }                                                                                                                   \
    while ((void)false, false)

#define __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, type) __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID_##TYPE(type)
#define __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID_ACTION(type) (void)null
#define __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID_FUNCTION(type) __CFLAT_MOCK_RETURN_DEFAULT(type)

#define __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, ...) __CFLAT_MOCK_RETURN_OR_PERFORM_REAL_##TYPE(func, __VA_ARGS__)
#define __CFLAT_MOCK_RETURN_OR_PERFORM_REAL_ACTION(func, ...) func(__VA_ARGS__)
#define __CFLAT_MOCK_RETURN_OR_PERFORM_REAL_FUNCTION(func, ...) return func(__VA_ARGS__)

#define __CFLAT_MOCK_MATCH_ARG(func, index, condition, TArg)                                                            \
(                                                                                                                       \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_ANY) ||                            \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_EQ &&                              \
        arg##index == __CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value) ||                                     \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_EQ_CSTRING &&                      \
        __CLFAT_MOCK_MATCH_CSTRING(&__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value, &arg##index)) ||         \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_EQ_STRING &&                       \
        __CLFAT_MOCK_MATCH_STRING(&__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value, &arg##index)) ||          \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_NEQ &&                             \
        arg##index != __CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value) ||                                     \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_NEQ_CSTRING &&                     \
        !__CLFAT_MOCK_MATCH_CSTRING(&__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value, &arg##index)) ||        \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_NEQ_STRING &&                      \
        !__CLFAT_MOCK_MATCH_STRING(&__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value, &arg##index)) ||         \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_GEQ &&                             \
        arg##index >= __CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value) ||                                     \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_GT &&                              \
        arg##index > __CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value) ||                                      \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_LEQ &&                             \
        arg##index <= __CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value) ||                                     \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_LT &&                              \
        arg##index < __CFLAT_MOCK_CONDITION(func, condition).Arg##index##Value) ||                                      \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_NOT_NULL &&                        \
        __CLFAT_MOCK_MATCH_NOT_NULL(&arg##index)) ||                                                                    \
    (__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Match == __CFLAT_MOCK_MATCH_MATCHER &&                         \
        ((bool(*)(TArg))__CFLAT_MOCK_CONDITION(func, condition).Arg##index##Matcher)(arg##index))                       \
)

#define __CFLAT_MOCK_TRY_INCREMENT_ACTION(func, condition)                                                              \
    do {                                                                                                                \
        if (__CFLAT_MOCK_CONDITION(func, condition).ActionIndex < __CFLAT_MOCK_CONDITION(func, condition).ActionCount)  \
            __CFLAT_MOCK_CONDITION(func, condition).ActionIndex++;                                                      \
    }                                                                                                                   \
    while ((void)false, false)

#define __CFLAT_MOCK_LAST_ACTION(func, condition) \
    __CFLAT_MOCK_CONDITION(func, condition).Actions[__CFLAT_MOCK_CONDITION(func, condition).ActionIndex - 1]

#define __CFLAT_MOCK_PERFORM_ACTION_AND_RETURN(func, condition, ...)                                                    \
    do {                                                                                                                \
        __CFLAT_MOCK_VALIDATE_STATE(                                                                                    \
            __CFLAT_MOCK_CONDITION(func, condition).ActionCount > 0,                                                    \
            __CFLAT_MOCK_ERR_NO_ACTION,                                                                                 \
            __CFLAT_MOCK_CONDITION(func, condition).File,                                                               \
            __CFLAT_MOCK_CONDITION(func, condition).Line);                                                              \
                                                                                                                        \
        __CFLAT_MOCK_TRY_INCREMENT_ACTION(func, condition);                                                             \
                                                                                                                        \
        if (__CFLAT_MOCK_LAST_ACTION(func, condition).Type == __CFLAT_MOCK_ACTION_THROW) {                              \
            throw_new(__CFLAT_MOCK_LAST_ACTION(func, condition).Data.Exception, null);                                  \
        }                                                                                                               \
        else if (__CFLAT_MOCK_LAST_ACTION(func, condition).Type == __CFLAT_MOCK_ACTION_CUSTOM) {                        \
            __CFLAT_MOCK_LAST_ACTION(func, condition).Data.CustomFunction(__VA_ARGS__);                                 \
        }                                                                                                               \
        return;                                                                                                         \
    }                                                                                                                   \
    while ((void)false, false)

#define __CFLAT_MOCK_PERFORM_FUNCTION_AND_RETURN(func, condition, ...)                                                  \
    do {                                                                                                                \
        __CFLAT_MOCK_VALIDATE_STATE(                                                                                    \
            __CFLAT_MOCK_CONDITION(func, condition).ActionCount > 0,                                                    \
            __CFLAT_MOCK_ERR_NO_ACTION,                                                                                 \
            __CFLAT_MOCK_CONDITION(func, condition).File,                                                               \
            __CFLAT_MOCK_CONDITION(func, condition).Line);                                                              \
                                                                                                                        \
        __CFLAT_MOCK_TRY_INCREMENT_ACTION(func, condition);                                                             \
                                                                                                                        \
        if (__CFLAT_MOCK_LAST_ACTION(func, condition).Type == __CFLAT_MOCK_ACTION_THROW) {                              \
            throw_new(__CFLAT_MOCK_LAST_ACTION(func, condition).Data.Exception, null);                                  \
        }                                                                                                               \
        else if (__CFLAT_MOCK_LAST_ACTION(func, condition).Type == __CFLAT_MOCK_ACTION_CUSTOM) {                        \
            return __CFLAT_MOCK_LAST_ACTION(func, condition).Data.CustomFunction(__VA_ARGS__);                          \
        }                                                                                                               \
        else {                                                                                                          \
            return __CFLAT_MOCK_LAST_ACTION(func, condition).Data.ReturnValue;                                          \
        }                                                                                                               \
    }                                                                                                                   \
    while ((void)false, false)

/**************************************/
/* Macro overloads                    */
/**************************************/

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS0(func) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition) \
    { \
        return true; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS1(func, TArg1) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS2(func, TArg1, TArg2) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS3(func, TArg1, TArg2, TArg3) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS4(func, TArg1, TArg2, TArg3, TArg4) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS5(func, TArg1, TArg2, TArg3, TArg4, TArg5) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS6(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS7(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS8(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS9(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS10(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS11(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS12(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11) && \
            __CFLAT_MOCK_MATCH_ARG(func, 12, condition, TArg12); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS13(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11) && \
            __CFLAT_MOCK_MATCH_ARG(func, 12, condition, TArg12) && \
            __CFLAT_MOCK_MATCH_ARG(func, 13, condition, TArg13); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS14(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11) && \
            __CFLAT_MOCK_MATCH_ARG(func, 12, condition, TArg12) && \
            __CFLAT_MOCK_MATCH_ARG(func, 13, condition, TArg13) && \
            __CFLAT_MOCK_MATCH_ARG(func, 14, condition, TArg14); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS15(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11) && \
            __CFLAT_MOCK_MATCH_ARG(func, 12, condition, TArg12) && \
            __CFLAT_MOCK_MATCH_ARG(func, 13, condition, TArg13) && \
            __CFLAT_MOCK_MATCH_ARG(func, 14, condition, TArg14) && \
            __CFLAT_MOCK_MATCH_ARG(func, 15, condition, TArg15); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS16(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11) && \
            __CFLAT_MOCK_MATCH_ARG(func, 12, condition, TArg12) && \
            __CFLAT_MOCK_MATCH_ARG(func, 13, condition, TArg13) && \
            __CFLAT_MOCK_MATCH_ARG(func, 14, condition, TArg14) && \
            __CFLAT_MOCK_MATCH_ARG(func, 15, condition, TArg15) && \
            __CFLAT_MOCK_MATCH_ARG(func, 16, condition, TArg16); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS17(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11) && \
            __CFLAT_MOCK_MATCH_ARG(func, 12, condition, TArg12) && \
            __CFLAT_MOCK_MATCH_ARG(func, 13, condition, TArg13) && \
            __CFLAT_MOCK_MATCH_ARG(func, 14, condition, TArg14) && \
            __CFLAT_MOCK_MATCH_ARG(func, 15, condition, TArg15) && \
            __CFLAT_MOCK_MATCH_ARG(func, 16, condition, TArg16) && \
            __CFLAT_MOCK_MATCH_ARG(func, 17, condition, TArg17); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS18(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17, TArg18 arg18) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11) && \
            __CFLAT_MOCK_MATCH_ARG(func, 12, condition, TArg12) && \
            __CFLAT_MOCK_MATCH_ARG(func, 13, condition, TArg13) && \
            __CFLAT_MOCK_MATCH_ARG(func, 14, condition, TArg14) && \
            __CFLAT_MOCK_MATCH_ARG(func, 15, condition, TArg15) && \
            __CFLAT_MOCK_MATCH_ARG(func, 16, condition, TArg16) && \
            __CFLAT_MOCK_MATCH_ARG(func, 17, condition, TArg17) && \
            __CFLAT_MOCK_MATCH_ARG(func, 18, condition, TArg18); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS19(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17, TArg18 arg18, TArg19 arg19) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11) && \
            __CFLAT_MOCK_MATCH_ARG(func, 12, condition, TArg12) && \
            __CFLAT_MOCK_MATCH_ARG(func, 13, condition, TArg13) && \
            __CFLAT_MOCK_MATCH_ARG(func, 14, condition, TArg14) && \
            __CFLAT_MOCK_MATCH_ARG(func, 15, condition, TArg15) && \
            __CFLAT_MOCK_MATCH_ARG(func, 16, condition, TArg16) && \
            __CFLAT_MOCK_MATCH_ARG(func, 17, condition, TArg17) && \
            __CFLAT_MOCK_MATCH_ARG(func, 18, condition, TArg18) && \
            __CFLAT_MOCK_MATCH_ARG(func, 19, condition, TArg19); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_MATCH_ARGS20(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20) \
    private bool __CFLAT_MOCK__##func##_MatchArgs(int condition, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17, TArg18 arg18, TArg19 arg19, TArg20 arg20) \
    { \
        return \
            __CFLAT_MOCK_MATCH_ARG(func, 1, condition, TArg1) && \
            __CFLAT_MOCK_MATCH_ARG(func, 2, condition, TArg2) && \
            __CFLAT_MOCK_MATCH_ARG(func, 3, condition, TArg3) && \
            __CFLAT_MOCK_MATCH_ARG(func, 4, condition, TArg4) && \
            __CFLAT_MOCK_MATCH_ARG(func, 5, condition, TArg5) && \
            __CFLAT_MOCK_MATCH_ARG(func, 6, condition, TArg6) && \
            __CFLAT_MOCK_MATCH_ARG(func, 7, condition, TArg7) && \
            __CFLAT_MOCK_MATCH_ARG(func, 8, condition, TArg8) && \
            __CFLAT_MOCK_MATCH_ARG(func, 9, condition, TArg9) && \
            __CFLAT_MOCK_MATCH_ARG(func, 10, condition, TArg10) && \
            __CFLAT_MOCK_MATCH_ARG(func, 11, condition, TArg11) && \
            __CFLAT_MOCK_MATCH_ARG(func, 12, condition, TArg12) && \
            __CFLAT_MOCK_MATCH_ARG(func, 13, condition, TArg13) && \
            __CFLAT_MOCK_MATCH_ARG(func, 14, condition, TArg14) && \
            __CFLAT_MOCK_MATCH_ARG(func, 15, condition, TArg15) && \
            __CFLAT_MOCK_MATCH_ARG(func, 16, condition, TArg16) && \
            __CFLAT_MOCK_MATCH_ARG(func, 17, condition, TArg17) && \
            __CFLAT_MOCK_MATCH_ARG(func, 18, condition, TArg18) && \
            __CFLAT_MOCK_MATCH_ARG(func, 19, condition, TArg19) && \
            __CFLAT_MOCK_MATCH_ARG(func, 20, condition, TArg20); \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES0(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, __CFLAT_MOCK_VERIFIER_CONDITION_INDEX)) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES1(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES2(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES3(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES4(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES5(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES6(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES7(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES8(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES9(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES10(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES11(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES12(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 12)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES13(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 12)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 13)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES14(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 12)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 13)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 14)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES15(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 12)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 13)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 14)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 15)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES16(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 12)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 13)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 14)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 15)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 16)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES17(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 12)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 13)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 14)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 15)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 16)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 17)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES18(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 12)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 13)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 14)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 15)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 16)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 17)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 18)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES19(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION_INDEX, \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 12)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 13)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 14)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 15)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 16)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 17)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 18)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 19)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES20(func) \
    private int __CFLAT_MOCK__##func##_CountVerifierMatches(void) \
    { \
        int count = 0; \
        for (int i = 0; i < __CFLAT_MOCK_DATA_CALL_COUNT(func); i++) { \
            if (__CFLAT_MOCK_MATCH_ARGS(func, \
                __CFLAT_MOCK_VERIFIER_CONDITION(func), \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 1)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 2)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 3)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 4)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 5)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 6)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 7)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 8)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 9)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 10)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 11)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 12)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 13)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 14)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 15)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 16)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 17)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 18)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 19)[i], \
                __CFLAT_MOCK_DATA_ARG_HISTORY(func, 20)[i])) \
                count++; \
        } \
        return count; \
    } \
    __CFLAT_MOCK_IGNORE_SEMICOLON

#define __CFLAT_MOCK_DECLARE_MOCK0(TYPE, func, TReturn) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, void); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, void); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, void); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK1(TYPE, func, TReturn, TArg1) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK2(TYPE, func, TReturn, TArg1, TArg2) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK3(TYPE, func, TReturn, TArg1, TArg2, TArg3) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK4(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK5(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK6(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK7(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK8(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK9(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK10(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK11(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11);\
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK12(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg12, 12); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg12, 12); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12);\
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK13(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg13, 13); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg13, 13); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13);\
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK14(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg14, 14); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg14, 14); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14);\
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK15(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg15, 15); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg15, 15); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15);\
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK16(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg16, 16); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg16, 16); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16);\
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK17(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg16, 16); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg17, 17); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg16, 16); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg17, 17); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17);\
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK18(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg16, 16); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg17, 17); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg18, 18); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg16, 16); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg17, 17); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg18, 18); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18);\
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK19(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg16, 16); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg17, 17); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg18, 18); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg19, 19); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg16, 16); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg17, 17); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg18, 18); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg19, 19); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19);\
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DECLARE_MOCK20(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20) \
    __CFLAT_MOCK_DECLARE_COMMON(TYPE,func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20); \
    typedef struct __CFLAT_MOCK_CONDITION_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_CONDITION_COMMON(func); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg16, 16); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg17, 17); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg18, 18); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg19, 19); \
        __CFLAT_MOCK_DECLARE_CONDITION_ARG(TArg20, 20); \
    } __CFLAT_MOCK_CONDITION_TYPE(func); \
    typedef struct __CFLAT_MOCK_DATA_TYPE(func) { \
        __CFLAT_MOCK_DECLARE_DATA_COMMON(func); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg1, 1); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg2, 2); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg3, 3); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg4, 4); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg5, 5); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg6, 6); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg7, 7); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg8, 8); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg9, 9); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg10, 10); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg11, 11); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg12, 12); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg13, 13); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg14, 14); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg15, 15); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg16, 16); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg17, 17); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg18, 18); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg19, 19); \
        __CFLAT_MOCK_DECLARE_DATA_ARG(TArg20, 20); \
    } __CFLAT_MOCK_DATA_TYPE(func); \
    extern __CFLAT_MOCK_DATA_TYPE(func) __CFLAT_MOCK_DATA(func); \
    __CFLAT_MOCK_DECLARE_MOCK(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20); \
    __CFLAT_MOCK_DECLARE_SPY(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20); \
    __CFLAT_MOCK_DECLARE_RESET(func)

#define __CFLAT_MOCK_DEFINE_MOCK0_BODY(TYPE, func) \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK1_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK2_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK3_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK4_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK5_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK6_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK7_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK8_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK9_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK10_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK11_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK12_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 12); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    __CFLAT_MOCK_SAVE_ARG(func, 12); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK13_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 12); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 13); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    __CFLAT_MOCK_SAVE_ARG(func, 12); \
    __CFLAT_MOCK_SAVE_ARG(func, 13); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK14_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 12); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 13); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 14); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    __CFLAT_MOCK_SAVE_ARG(func, 12); \
    __CFLAT_MOCK_SAVE_ARG(func, 13); \
    __CFLAT_MOCK_SAVE_ARG(func, 14); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK15_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 12); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 13); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 14); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 15); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    __CFLAT_MOCK_SAVE_ARG(func, 12); \
    __CFLAT_MOCK_SAVE_ARG(func, 13); \
    __CFLAT_MOCK_SAVE_ARG(func, 14); \
    __CFLAT_MOCK_SAVE_ARG(func, 15); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK16_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 12); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 13); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 14); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 15); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 16); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    __CFLAT_MOCK_SAVE_ARG(func, 12); \
    __CFLAT_MOCK_SAVE_ARG(func, 13); \
    __CFLAT_MOCK_SAVE_ARG(func, 14); \
    __CFLAT_MOCK_SAVE_ARG(func, 15); \
    __CFLAT_MOCK_SAVE_ARG(func, 16); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK17_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 12); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 13); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 14); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 15); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 16); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 17); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    __CFLAT_MOCK_SAVE_ARG(func, 12); \
    __CFLAT_MOCK_SAVE_ARG(func, 13); \
    __CFLAT_MOCK_SAVE_ARG(func, 14); \
    __CFLAT_MOCK_SAVE_ARG(func, 15); \
    __CFLAT_MOCK_SAVE_ARG(func, 16); \
    __CFLAT_MOCK_SAVE_ARG(func, 17); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK18_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 12); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 13); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 14); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 15); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 16); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 17); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 18); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    __CFLAT_MOCK_SAVE_ARG(func, 12); \
    __CFLAT_MOCK_SAVE_ARG(func, 13); \
    __CFLAT_MOCK_SAVE_ARG(func, 14); \
    __CFLAT_MOCK_SAVE_ARG(func, 15); \
    __CFLAT_MOCK_SAVE_ARG(func, 16); \
    __CFLAT_MOCK_SAVE_ARG(func, 17); \
    __CFLAT_MOCK_SAVE_ARG(func, 18); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK19_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 12); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 13); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 14); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 15); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 16); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 17); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 18); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 19); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    __CFLAT_MOCK_SAVE_ARG(func, 12); \
    __CFLAT_MOCK_SAVE_ARG(func, 13); \
    __CFLAT_MOCK_SAVE_ARG(func, 14); \
    __CFLAT_MOCK_SAVE_ARG(func, 15); \
    __CFLAT_MOCK_SAVE_ARG(func, 16); \
    __CFLAT_MOCK_SAVE_ARG(func, 17); \
    __CFLAT_MOCK_SAVE_ARG(func, 18); \
    __CFLAT_MOCK_SAVE_ARG(func, 19); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK20_BODY(TYPE, func) \
    if (__CFLAT_MOCK_CAN_SAVE_HISTORY(func)) { \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 1); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 2); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 3); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 4); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 5); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 6); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 7); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 8); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 9); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 10); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 11); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 12); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 13); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 14); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 15); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 16); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 17); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 18); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 19); \
        __CFLAT_MOCK_SAVE_ARG_HISTORY(func, 20); \
    } \
    __CFLAT_MOCK_REGISTER_CALL(func); \
    __CFLAT_MOCK_INCREMENT_CALLS(func); \
    __CFLAT_MOCK_SAVE_ARG(func, 1); \
    __CFLAT_MOCK_SAVE_ARG(func, 2); \
    __CFLAT_MOCK_SAVE_ARG(func, 3); \
    __CFLAT_MOCK_SAVE_ARG(func, 4); \
    __CFLAT_MOCK_SAVE_ARG(func, 5); \
    __CFLAT_MOCK_SAVE_ARG(func, 6); \
    __CFLAT_MOCK_SAVE_ARG(func, 7); \
    __CFLAT_MOCK_SAVE_ARG(func, 8); \
    __CFLAT_MOCK_SAVE_ARG(func, 9); \
    __CFLAT_MOCK_SAVE_ARG(func, 10); \
    __CFLAT_MOCK_SAVE_ARG(func, 11); \
    __CFLAT_MOCK_SAVE_ARG(func, 12); \
    __CFLAT_MOCK_SAVE_ARG(func, 13); \
    __CFLAT_MOCK_SAVE_ARG(func, 14); \
    __CFLAT_MOCK_SAVE_ARG(func, 15); \
    __CFLAT_MOCK_SAVE_ARG(func, 16); \
    __CFLAT_MOCK_SAVE_ARG(func, 17); \
    __CFLAT_MOCK_SAVE_ARG(func, 18); \
    __CFLAT_MOCK_SAVE_ARG(func, 19); \
    __CFLAT_MOCK_SAVE_ARG(func, 20); \
    for (int i = 0; i < __CFLAT_MOCK_DATA_CONDITION_COUNT(func); i++) { \
        if (__CFLAT_MOCK_MATCH_ARGS(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20)) { \
            __CFLAT_MOCK_PERFORM_##TYPE##_AND_RETURN(func, i, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20); \
        } \
    }

#define __CFLAT_MOCK_DEFINE_MOCK0(TYPE, func, TReturn) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS0(func); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES0(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, void); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, void) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK0_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, void) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK0_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK1(TYPE, func, TReturn, TArg1) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS1(func, TArg1); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES1(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK1_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK1_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK2(TYPE, func, TReturn, TArg1, TArg2) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS2(func, TArg1, TArg2); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES2(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK2_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK2_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK3(TYPE, func, TReturn, TArg1, TArg2, TArg3) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS3(func, TArg1, TArg2, TArg3); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES3(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK3_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK3_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK4(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS4(func, TArg1, TArg2, TArg3, TArg4); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES4(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK4_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK4_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK5(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS5(func, TArg1, TArg2, TArg3, TArg4, TArg5); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES5(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK5_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK5_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK6(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS6(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES6(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK6_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK6_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK7(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS7(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES7(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK7_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK7_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK8(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS8(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES8(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK8_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK8_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK9(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS9(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES9(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK9_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK9_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK10(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS10(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES10(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK10_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK10_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK11(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS11(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES11(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK11_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK11_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK12(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS12(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES12(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK12_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK12_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK13(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS13(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES13(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK13_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK13_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK14(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS14(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES14(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK14_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK14_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK15(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS15(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES15(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK15_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK15_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK16(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS16(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES16(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK16_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK16_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK17(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS17(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES17(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK17_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK17_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK18(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS18(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES18(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17, TArg18 arg18) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK18_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17, TArg18 arg18) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK18_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK19(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS19(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES19(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17, TArg18 arg18, TArg19 arg19) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK20_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17, TArg18 arg18, TArg19 arg19) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK20_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define __CFLAT_MOCK_DEFINE_MOCK20(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20) \
    __CFLAT_MOCK_DEFINE_MATCH_ARGS20(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20); \
    __CFLAT_MOCK_DEFINE_COUNT_VERIFIER_MATCHES20(func); \
    __CFLAT_MOCK_DEFINE_COMMON(TYPE, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20); \
    __CFLAT_MOCK_DEFINE_MOCK(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17, TArg18 arg18, TArg19 arg19, TArg20 arg20) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK20_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_DEFAULT_OR_VOID(TYPE, TReturn); \
    } \
    __CFLAT_MOCK_DEFINE_SPY(func, TReturn, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9, TArg10 arg10, TArg11 arg11, TArg12 arg12, TArg13 arg13, TArg14 arg14, TArg15 arg15, TArg16 arg16, TArg17 arg17, TArg18 arg18, TArg19 arg19, TArg20 arg20) \
    { \
        __CFLAT_MOCK_DEFINE_MOCK20_BODY(TYPE, func); \
        __CFLAT_MOCK_RETURN_OR_PERFORM_REAL(TYPE, func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20); \
    } \
    __CFLAT_MOCK_DEFINE_RESET(func); \
    __CFLAT_MOCK_DEFINE_DATA(func)

#define Mock_DeclareAction0(func) __CFLAT_MOCK_DECLARE_MOCK0(ACTION, func, void)
#define Mock_DeclareAction1(func, TArg1) __CFLAT_MOCK_DECLARE_MOCK1(ACTION, func, void, TArg1)
#define Mock_DeclareAction2(func, TArg1, TArg2) __CFLAT_MOCK_DECLARE_MOCK2(ACTION, func, void, TArg1, TArg2)
#define Mock_DeclareAction3(func, TArg1, TArg2, TArg3) __CFLAT_MOCK_DECLARE_MOCK3(ACTION, func, void, TArg1, TArg2, TArg3)
#define Mock_DeclareAction4(func, TArg1, TArg2, TArg3, TArg4) __CFLAT_MOCK_DECLARE_MOCK4(ACTION, func, void, TArg1, TArg2, TArg3, TArg4)
#define Mock_DeclareAction5(func, TArg1, TArg2, TArg3, TArg4, TArg5) __CFLAT_MOCK_DECLARE_MOCK5(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5)
#define Mock_DeclareAction6(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6) __CFLAT_MOCK_DECLARE_MOCK6(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6)
#define Mock_DeclareAction7(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7) __CFLAT_MOCK_DECLARE_MOCK7(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7)
#define Mock_DeclareAction8(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8) __CFLAT_MOCK_DECLARE_MOCK8(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8)
#define Mock_DeclareAction9(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9) __CFLAT_MOCK_DECLARE_MOCK9(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9)
#define Mock_DeclareAction10(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10) __CFLAT_MOCK_DECLARE_MOCK10(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10)
#define Mock_DeclareAction11(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11) __CFLAT_MOCK_DECLARE_MOCK11(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11)
#define Mock_DeclareAction12(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12) __CFLAT_MOCK_DECLARE_MOCK12(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12)
#define Mock_DeclareAction13(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13) __CFLAT_MOCK_DECLARE_MOCK13(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13)
#define Mock_DeclareAction14(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14) __CFLAT_MOCK_DECLARE_MOCK14(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14)
#define Mock_DeclareAction15(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15) __CFLAT_MOCK_DECLARE_MOCK15(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15)
#define Mock_DeclareAction16(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16) __CFLAT_MOCK_DECLARE_MOCK16(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16)
#define Mock_DeclareAction17(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17) __CFLAT_MOCK_DECLARE_MOCK17(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17)
#define Mock_DeclareAction18(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18) __CFLAT_MOCK_DECLARE_MOCK18(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18)
#define Mock_DeclareAction19(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19) __CFLAT_MOCK_DECLARE_MOCK19(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19)
#define Mock_DeclareAction20(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20) __CFLAT_MOCK_DECLARE_MOCK20(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20)

#define Mock_DeclareFunc0(func, TReturn) __CFLAT_MOCK_DECLARE_MOCK0(FUNCTION, func, TReturn)
#define Mock_DeclareFunc1(func, TReturn, TArg1) __CFLAT_MOCK_DECLARE_MOCK1(FUNCTION, func, TReturn, TArg1)
#define Mock_DeclareFunc2(func, TReturn, TArg1, TArg2) __CFLAT_MOCK_DECLARE_MOCK2(FUNCTION, func, TReturn, TArg1, TArg2)
#define Mock_DeclareFunc3(func, TReturn, TArg1, TArg2, TArg3) __CFLAT_MOCK_DECLARE_MOCK3(FUNCTION, func, TReturn, TArg1, TArg2, TArg3)
#define Mock_DeclareFunc4(func, TReturn, TArg1, TArg2, TArg3, TArg4) __CFLAT_MOCK_DECLARE_MOCK4(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4)
#define Mock_DeclareFunc5(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5) __CFLAT_MOCK_DECLARE_MOCK5(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5)
#define Mock_DeclareFunc6(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6) __CFLAT_MOCK_DECLARE_MOCK6(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6)
#define Mock_DeclareFunc7(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7) __CFLAT_MOCK_DECLARE_MOCK7(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7)
#define Mock_DeclareFunc8(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8) __CFLAT_MOCK_DECLARE_MOCK8(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8)
#define Mock_DeclareFunc9(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9) __CFLAT_MOCK_DECLARE_MOCK9(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9)
#define Mock_DeclareFunc10(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10) __CFLAT_MOCK_DECLARE_MOCK10(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10)
#define Mock_DeclareFunc11(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11) __CFLAT_MOCK_DECLARE_MOCK11(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11)
#define Mock_DeclareFunc12(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12) __CFLAT_MOCK_DECLARE_MOCK12(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12)
#define Mock_DeclareFunc13(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13) __CFLAT_MOCK_DECLARE_MOCK13(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13)
#define Mock_DeclareFunc14(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14) __CFLAT_MOCK_DECLARE_MOCK14(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14)
#define Mock_DeclareFunc15(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15) __CFLAT_MOCK_DECLARE_MOCK15(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15)
#define Mock_DeclareFunc16(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16) __CFLAT_MOCK_DECLARE_MOCK16(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16)
#define Mock_DeclareFunc17(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17) __CFLAT_MOCK_DECLARE_MOCK17(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17)
#define Mock_DeclareFunc18(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18) __CFLAT_MOCK_DECLARE_MOCK18(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18)
#define Mock_DeclareFunc19(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19) __CFLAT_MOCK_DECLARE_MOCK19(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19)
#define Mock_DeclareFunc20(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20) __CFLAT_MOCK_DECLARE_MOCK20(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20)

#define Mock_DefineAction0(func) __CFLAT_MOCK_DEFINE_MOCK0(ACTION, func, void)
#define Mock_DefineAction1(func, TArg1) __CFLAT_MOCK_DEFINE_MOCK1(ACTION, func, void, TArg1)
#define Mock_DefineAction2(func, TArg1, TArg2) __CFLAT_MOCK_DEFINE_MOCK2(ACTION, func, void, TArg1, TArg2)
#define Mock_DefineAction3(func, TArg1, TArg2, TArg3) __CFLAT_MOCK_DEFINE_MOCK3(ACTION, func, void, TArg1, TArg2, TArg3)
#define Mock_DefineAction4(func, TArg1, TArg2, TArg3, TArg4) __CFLAT_MOCK_DEFINE_MOCK4(ACTION, func, void, TArg1, TArg2, TArg3, TArg4)
#define Mock_DefineAction5(func, TArg1, TArg2, TArg3, TArg4, TArg5) __CFLAT_MOCK_DEFINE_MOCK5(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5)
#define Mock_DefineAction6(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6) __CFLAT_MOCK_DEFINE_MOCK6(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6)
#define Mock_DefineAction7(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7) __CFLAT_MOCK_DEFINE_MOCK7(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7)
#define Mock_DefineAction8(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8) __CFLAT_MOCK_DEFINE_MOCK8(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8)
#define Mock_DefineAction9(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9) __CFLAT_MOCK_DEFINE_MOCK9(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9)
#define Mock_DefineAction10(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10) __CFLAT_MOCK_DEFINE_MOCK10(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10)
#define Mock_DefineAction11(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11) __CFLAT_MOCK_DEFINE_MOCK11(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11)
#define Mock_DefineAction12(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12) __CFLAT_MOCK_DEFINE_MOCK12(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12)
#define Mock_DefineAction13(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13) __CFLAT_MOCK_DEFINE_MOCK13(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13)
#define Mock_DefineAction14(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14) __CFLAT_MOCK_DEFINE_MOCK14(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14)
#define Mock_DefineAction15(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15) __CFLAT_MOCK_DEFINE_MOCK15(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15)
#define Mock_DefineAction16(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16) __CFLAT_MOCK_DEFINE_MOCK16(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16)
#define Mock_DefineAction17(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17) __CFLAT_MOCK_DEFINE_MOCK17(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17)
#define Mock_DefineAction18(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18) __CFLAT_MOCK_DEFINE_MOCK18(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18)
#define Mock_DefineAction19(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19) __CFLAT_MOCK_DEFINE_MOCK19(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19)
#define Mock_DefineAction20(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20) __CFLAT_MOCK_DEFINE_MOCK20(ACTION, func, void, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20)

#define Mock_DefineFunc0(func, TReturn) __CFLAT_MOCK_DEFINE_MOCK0(FUNCTION, func, TReturn)
#define Mock_DefineFunc1(func, TReturn, TArg1) __CFLAT_MOCK_DEFINE_MOCK1(FUNCTION, func, TReturn, TArg1)
#define Mock_DefineFunc2(func, TReturn, TArg1, TArg2) __CFLAT_MOCK_DEFINE_MOCK2(FUNCTION, func, TReturn, TArg1, TArg2)
#define Mock_DefineFunc3(func, TReturn, TArg1, TArg2, TArg3) __CFLAT_MOCK_DEFINE_MOCK3(FUNCTION, func, TReturn, TArg1, TArg2, TArg3)
#define Mock_DefineFunc4(func, TReturn, TArg1, TArg2, TArg3, TArg4) __CFLAT_MOCK_DEFINE_MOCK4(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4)
#define Mock_DefineFunc5(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5) __CFLAT_MOCK_DEFINE_MOCK5(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5)
#define Mock_DefineFunc6(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6) __CFLAT_MOCK_DEFINE_MOCK6(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6)
#define Mock_DefineFunc7(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7) __CFLAT_MOCK_DEFINE_MOCK7(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7)
#define Mock_DefineFunc8(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8) __CFLAT_MOCK_DEFINE_MOCK8(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8)
#define Mock_DefineFunc9(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9) __CFLAT_MOCK_DEFINE_MOCK9(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9)
#define Mock_DefineFunc10(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10) __CFLAT_MOCK_DEFINE_MOCK10(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10)
#define Mock_DefineFunc11(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11) __CFLAT_MOCK_DEFINE_MOCK11(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11)
#define Mock_DefineFunc12(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12) __CFLAT_MOCK_DEFINE_MOCK12(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12)
#define Mock_DefineFunc13(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13) __CFLAT_MOCK_DEFINE_MOCK13(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13)
#define Mock_DefineFunc14(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14) __CFLAT_MOCK_DEFINE_MOCK14(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14)
#define Mock_DefineFunc15(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15) __CFLAT_MOCK_DEFINE_MOCK15(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15)
#define Mock_DefineFunc16(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16) __CFLAT_MOCK_DEFINE_MOCK16(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16)
#define Mock_DefineFunc17(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17) __CFLAT_MOCK_DEFINE_MOCK17(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17)
#define Mock_DefineFunc18(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18) __CFLAT_MOCK_DEFINE_MOCK18(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18)
#define Mock_DefineFunc19(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19) __CFLAT_MOCK_DEFINE_MOCK19(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19)
#define Mock_DefineFunc20(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20) __CFLAT_MOCK_DEFINE_MOCK20(FUNCTION, func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20)

#define Mock_Action0(func) \
    Mock_DeclareAction0(func); \
    Mock_DefineAction0(func)
#define Mock_Action1(func, TArg1) \
    Mock_DeclareAction1(func, TArg1); \
    Mock_DefineAction1(func, TArg1)
#define Mock_Action2(func, TArg1, TArg2) \
    Mock_DeclareAction2(func, TArg1, TArg2); \
    Mock_DefineAction2(func, TArg1, TArg2)
#define Mock_Action3(func, TArg1, TArg2, TArg3) \
    Mock_DeclareAction3(func, TArg1, TArg2, TArg3); \
    Mock_DefineAction3(func, TArg1, TArg2, TArg3)
#define Mock_Action4(func, TArg1, TArg2, TArg3, TArg4) \
    Mock_DeclareAction4(func, TArg1, TArg2, TArg3, TArg4); \
    Mock_DefineAction4(func, TArg1, TArg2, TArg3, TArg4)
#define Mock_Action5(func, TArg1, TArg2, TArg3, TArg4, TArg5) \
    Mock_DeclareAction5(func, TArg1, TArg2, TArg3, TArg4, TArg5); \
    Mock_DefineAction5(func, TArg1, TArg2, TArg3, TArg4, TArg5)
#define Mock_Action6(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6) \
    Mock_DeclareAction6(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6); \
    Mock_DefineAction6(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6)
#define Mock_Action7(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7) \
    Mock_DeclareAction7(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7); \
    Mock_DefineAction7(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7)
#define Mock_Action8(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8) \
    Mock_DeclareAction8(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8); \
    Mock_DefineAction8(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8)
#define Mock_Action9(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9) \
    Mock_DeclareAction9(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9); \
    Mock_DefineAction9(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9)
#define Mock_Action10(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10) \
    Mock_DeclareAction10(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10); \
    Mock_DefineAction10(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10)
#define Mock_Action11(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11) \
    Mock_DeclareAction11(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11); \
    Mock_DefineAction11(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11)
#define Mock_Action12(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12) \
    Mock_DeclareAction12(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12); \
    Mock_DefineAction12(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12)
#define Mock_Action13(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13) \
    Mock_DeclareAction13(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13); \
    Mock_DefineAction13(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13)
#define Mock_Action14(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14) \
    Mock_DeclareAction14(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14); \
    Mock_DefineAction14(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14)
#define Mock_Action15(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15) \
    Mock_DeclareAction15(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15); \
    Mock_DefineAction15(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15)
#define Mock_Action16(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16) \
    Mock_DeclareAction16(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16); \
    Mock_DefineAction16(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16)
#define Mock_Action17(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17) \
    Mock_DeclareAction17(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17); \
    Mock_DefineAction17(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17)
#define Mock_Action18(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18) \
    Mock_DeclareAction18(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18); \
    Mock_DefineAction18(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18)
#define Mock_Action19(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19) \
    Mock_DeclareAction19(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19); \
    Mock_DefineAction19(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19)
#define Mock_Action20(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20) \
    Mock_DeclareAction20(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20); \
    Mock_DefineAction20(func, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20)

#define Mock_Func0(func, TReturn) \
    Mock_DeclareFunc0(func, TReturn); \
    Mock_DefineFunc0(func, TReturn)
#define Mock_Func1(func, TReturn, TArg1) \
    Mock_DeclareFunc1(func, TReturn, TArg1); \
    Mock_DefineFunc1(func, TReturn, TArg1)
#define Mock_Func2(func, TReturn, TArg1, TArg2) \
    Mock_DeclareFunc2(func, TReturn, TArg1, TArg2); \
    Mock_DefineFunc2(func, TReturn, TArg1, TArg2)
#define Mock_Func3(func, TReturn, TArg1, TArg2, TArg3) \
    Mock_DeclareFunc3(func, TReturn, TArg1, TArg2, TArg3); \
    Mock_DefineFunc3(func, TReturn, TArg1, TArg2, TArg3)
#define Mock_Func4(func, TReturn, TArg1, TArg2, TArg3, TArg4) \
    Mock_DeclareFunc4(func, TReturn, TArg1, TArg2, TArg3, TArg4); \
    Mock_DefineFunc4(func, TReturn, TArg1, TArg2, TArg3, TArg4)
#define Mock_Func5(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5) \
    Mock_DeclareFunc5(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5); \
    Mock_DefineFunc5(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5)
#define Mock_Func6(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6) \
    Mock_DeclareFunc6(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6); \
    Mock_DefineFunc6(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6)
#define Mock_Func7(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7) \
    Mock_DeclareFunc7(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7); \
    Mock_DefineFunc7(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7)
#define Mock_Func8(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8) \
    Mock_DeclareFunc8(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8); \
    Mock_DefineFunc8(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8)
#define Mock_Func9(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9) \
    Mock_DeclareFunc9(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9); \
    Mock_DefineFunc9(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9)
#define Mock_Func10(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10) \
    Mock_DeclareFunc10(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10); \
    Mock_DefineFunc10(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10)
#define Mock_Func11(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11) \
    Mock_DeclareFunc11(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11); \
    Mock_DefineFunc11(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11)
#define Mock_Func12(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12) \
    Mock_DeclareFunc12(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12); \
    Mock_DefineFunc12(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12)
#define Mock_Func13(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13) \
    Mock_DeclareFunc13(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13); \
    Mock_DefineFunc13(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13)
#define Mock_Func14(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14) \
    Mock_DeclareFunc14(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14); \
    Mock_DefineFunc14(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14)
#define Mock_Func15(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15) \
    Mock_DeclareFunc15(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15); \
    Mock_DefineFunc15(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15)
#define Mock_Func16(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16) \
    Mock_DeclareFunc16(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16); \
    Mock_DefineFunc16(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16)
#define Mock_Func17(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17) \
    Mock_DeclareFunc17(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17); \
    Mock_DefineFunc17(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17)
#define Mock_Func18(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18) \
    Mock_DeclareFunc18(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18); \
    Mock_DefineFunc18(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18)
#define Mock_Func19(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19) \
    Mock_DeclareFunc19(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19); \
    Mock_DefineFunc19(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19)
#define Mock_Func20(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20) \
    Mock_DeclareFunc20(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20); \
    Mock_DefineFunc20(func, TReturn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20)

#define __CFLAT_MOCK_WHEN_COMMON_BODY(func) \
    __CFLAT_MOCK_CURRENT_CONDITION(func).File = __FILE__, \
    __CFLAT_MOCK_CURRENT_CONDITION(func).Line = __LINE__, \
    __CFLAT_MOCK_VALIDATE_STATE( \
        __CFLAT_MOCK_CAN_ADD_CONDITION(func), \
        __CFLAT_MOCK_ERR_MAX_CONDITIONS, \
        __CFLAT_MOCK_CURRENT_CONDITION(func).File, \
        __CFLAT_MOCK_CURRENT_CONDITION(func).Line)

#define __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, index, arg) \
    __CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_EQ, \
    __CFLAT_MOCK_MATCHER_TEMP = null, \
    __CFLAT_MOCK_CURRENT_CONDITION(func).Arg##index##Value = arg, \
    __CFLAT_MOCK_CURRENT_CONDITION(func).Arg##index##Match = __CFLAT_MOCK_MATCH_TEMP, \
    __CFLAT_MOCK_CURRENT_CONDITION(func).Arg##index##Matcher = __CFLAT_MOCK_MATCHER_TEMP

#define Mock_When0(func) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When1(func, arg1) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When2(func, arg1, arg2) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When3(func, arg1, arg2, arg3) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When4(func, arg1, arg2, arg3, arg4) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When5(func, arg1, arg2, arg3, arg4, arg5) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When6(func, arg1, arg2, arg3, arg4, arg5, arg6) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When7(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When8(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When9(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When10(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When11(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When12(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When13(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When14(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When15(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When16(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When17(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 17, arg17), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When18(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 17, arg17), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 18, arg18), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When19(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 17, arg17), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 18, arg18), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 19, arg19), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define Mock_When20(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20) \
( \
    __CFLAT_MOCK_WHEN_COMMON_BODY(func), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 17, arg17), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 18, arg18), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 19, arg19), \
    __CFLAT_MOCK_WHEN_SAVE_ARG_TO_CONDITION(func, 20, arg20), \
    __CFLAT_MOCK_DATA_CONDITION_COUNT(func)++, \
    __CFLAT_MOCK_FUNCTIONS(func) \
)

#define __CFLAT_MOCK_VERIFIER_RESET_CONDITION(func) \
    Memory_Zero(&__CFLAT_MOCK_VERIFIER_CONDITION(func), sizeof(__CFLAT_MOCK_CONDITION_TYPE(func)))

#define __CFLAT_MOCK_VERIFIER_COMMON_BODY(func) \
    __CFLAT_MOCK_VERIFIER_RESET_CONDITION(func), \
    __CFLAT_MOCK_VERIFIER_CONDITION(func).File = __FILE__, \
    __CFLAT_MOCK_VERIFIER_CONDITION(func).Line = __LINE__

#define __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, index, arg) \
    __CFLAT_MOCK_MATCH_TEMP = __CFLAT_MOCK_MATCH_EQ, \
    __CFLAT_MOCK_MATCHER_TEMP = null, \
    __CFLAT_MOCK_VERIFIER_CONDITION(func).Arg##index##Value = arg, \
    __CFLAT_MOCK_VERIFIER_CONDITION(func).Arg##index##Match = __CFLAT_MOCK_MATCH_TEMP, \
    __CFLAT_MOCK_VERIFIER_CONDITION(func).Arg##index##Matcher = __CFLAT_MOCK_MATCHER_TEMP

#define Mock_Verify0(func) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify1(func, arg1) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify2(func, arg1, arg2) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify3(func, arg1, arg2, arg3) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify4(func, arg1, arg2, arg3, arg4) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify5(func, arg1, arg2, arg3, arg4, arg5) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify6(func, arg1, arg2, arg3, arg4, arg5, arg6) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify7(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify8(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify9(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify10(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify11(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify12(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify13(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify14(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify15(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify16(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify17(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 17, arg17), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify18(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 17, arg17), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 18, arg18), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify19(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 17, arg17), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 18, arg18), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 19, arg19), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#define Mock_Verify20(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20) \
( \
    __CFLAT_MOCK_VERIFIER_COMMON_BODY(func), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 1, arg1), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 2, arg2), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 3, arg3), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 4, arg4), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 5, arg5), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 6, arg6), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 7, arg7), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 8, arg8), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 9, arg9), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 10, arg10), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 11, arg11), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 12, arg12), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 13, arg13), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 14, arg14), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 15, arg15), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 16, arg16), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 17, arg17), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 18, arg18), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 19, arg19), \
    __CFLAT_MOCK_VERIFIER_SAVE_ARG_TO_CONDITION(func, 20, arg20), \
    __CFLAT_MOCK_VERIFIERS(func) \
)

#endif
