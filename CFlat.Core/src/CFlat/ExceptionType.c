/*
 * Copyright (C) 2015 Martijn van Dorp
 *
 * This file is part of CFlat.Core.
 *
 * CFlat.Core is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFlat.Core is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CFlat/ExceptionType.h"

#include "CFlat.h"
#include "CFlat/String.h"

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
    EXCEPTION(FormatException,              "One of the identified items was in an invalid format.")                \
    EXCEPTION(NotImplementedException,      "The method or operation is not implemented.")                          \
    EXCEPTION(NotSupportedException,        "The method or operation is not suppoted.")
#undef EXCEPTION

// Define strings containing the exception names.
#define EXCEPTION(name, message) \
private const String name##Name = CFLAT_STRING_LITERAL(#name);
EXCEPTIONS
#undef EXCEPTION

// Define strings containing the exception messages.
#define EXCEPTION(name, message) \
private const String name##Message = CFLAT_STRING_LITERAL(message);
EXCEPTIONS
#undef EXCEPTION

/**************************************/
/* Public function definitions        */
/**************************************/

public bool ExceptionType_IsAssignableFrom(ExceptionType type1, ExceptionType type2)
{
    return (type1 & type2) == type1;
}

public const String *ExceptionType_GetName(ExceptionType type)
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

public const String *ExceptionType_GetDefaultMessage(ExceptionType type)
{
    // Return the address of the string containing the exception message.
    switch (type) {
    #define EXCEPTION(name, message) \
        case name: return &name##Message;
        EXCEPTIONS
        default:
            throw_new(ArgumentException, "Invalid exception type.");
            return null;
    }
    #undef EXCEPTION
}
