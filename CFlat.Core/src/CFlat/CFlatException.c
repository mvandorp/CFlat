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

#include "CFlat/CFlatException.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

/* Private constants */
private const ObjectVTable Exception_VTable = ObjectVTable_Initializer((DestructorFunc)Exception_Destructor);

/**************************************/
/* Public function definitions        */
/**************************************/

public CFlatException *Exception_New(
    ExceptionType type,
    const String *message,
    const char *file,
    int line,
    CFlatException *innerException)
{
    CFlatException *ex = Memory_Allocate(sizeof(CFlatException));

    try {
        Exception_Constructor(ex, type, message, file, line, innerException);

        Object_SetDeallocator(ex, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(ex);
        throw;
    }
    endtry;

    return ex;
}

public void Exception_Constructor(
    CFlatException *ex,
    ExceptionType type,
    const String *message,
    const char *file,
    int line,
    CFlatException *innerException)
{
    assert(ex != null);
    assert(file != null);
    assert(line > 0);

    Object_Constructor(ex, &Exception_VTable);

    ex->Type = type;
    ex->Message = retain_const(message);
    ex->File = file;
    ex->Line = line;
    ex->InnerException = retain(innerException);
}

public void Exception_Destructor(CFlatException *ex)
{
    Validate_NotNull(ex);

    release(ex->Message);
    release(ex->InnerException);
}

public bool Exception_IsInstanceOf(const CFlatException *ex, ExceptionType type)
{
    Validate_NotNull(ex);

    return ExceptionType_IsAssignableFrom(type, ex->Type);
}

public CFlatException *Exception_GetInnerException(const CFlatException *ex)
{
    Validate_NotNull(ex);

    return ex->InnerException;
}

public const String *Exception_GetMessage(const CFlatException *ex)
{
    Validate_NotNull(ex);

    if (ex->Message == null) {
        return ExceptionType_GetDefaultMessage(ex->Type);
    }
    else {
        return ex->Message;
    }
}

public const String *Exception_GetName(const CFlatException *ex)
{
    return ExceptionType_GetName(Exception_GetType(ex));
}

public ExceptionType Exception_GetType(const CFlatException *ex)
{
    Validate_NotNull(ex);

    return ex->Type;
}
