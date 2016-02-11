#include "CFlat/ExceptionType.h"

#include "CFlat.h"
#include "CFlat/String.h"
#include "CFlat/String-private.h"

#define EXCEPTION(name, message)
#define EXCEPTIONS \
    EXCEPTION(Exception,                    "")                                                                     \
    EXCEPTION(SystemException,              "System error.")                                                        \
    EXCEPTION(ArgumentException,            "Value does not fall within the expected range.")                       \
    EXCEPTION(IOException,                  "I/O error occurred.")                                                  \
    EXCEPTION(IndexOutOfRangeException,     "Index was outside the bounds of the array.")                           \
    EXCEPTION(NullReferenceException,       "Object reference not set to an instance of an object.")                \
    EXCEPTION(AccessViolationException,                                                                             \
        "Attempted to read or write protected memory. This is often an indication that other memory is corrupt.")   \
    EXCEPTION(InvalidOperationException,    "Operation is not valid due to the current state of the object.")       \
    EXCEPTION(ArgumentNullException,        "Value cannot be null.")                                                \
    EXCEPTION(ArgumentOutOfRangeException,  "Specified argument was out of the range of valid values.")             \
    EXCEPTION(OutOfMemoryException,         "Insufficient memory to continue the execution of the program.")        \
    EXCEPTION(FileNotFoundException,        "Unable to find the specified file.")                                   \
    EXCEPTION(FormatException,              "One of the identified items was in an invalid format.")
#undef EXCEPTION

// Define strings containing the exception names.
#define EXCEPTION(name, message) \
String name##Name = CFLAT_STRING_LITERAL(#name);
EXCEPTIONS
#undef EXCEPTION

// Define strings containing the exception messages.
#define EXCEPTION(name, message) \
String name##Message = CFLAT_STRING_LITERAL(message);
EXCEPTIONS
#undef EXCEPTION

/**************************************/
/* Extern function definitions        */
/**************************************/

bool ExceptionType_IsAssignableFrom(ExceptionType type1, ExceptionType type2)
{
    return (type1 & type2) == type1;
}

String *ExceptionType_GetName(ExceptionType type)
{
    // Return the address of the string containing the exception name.
    switch (type) {
    #define EXCEPTION(name, message) \
        case name: return &name##Name;
        EXCEPTIONS
        default:
            throw_new(ArgumentException, "Invalid exception type.");
            return null;
    }
    #undef EXCEPTION
}

String *ExceptionType_GetExceptionMessage(ExceptionType type, const char *userMessage)
{
    // If userMessage is null, return the address of the string containing the exception name.
    // Otherwise, create a new message based on the user message.
    switch (type) {
    #define EXCEPTION(name, message)                \
        case name:                                  \
            return (userMessage == null)            \
                ? &name##Message                    \
                : String_New(userMessage);
        EXCEPTIONS
        default:
            throw_new(ArgumentException, "Invalid exception type.");
            return null;
    }
    #undef EXCEPTION
}
