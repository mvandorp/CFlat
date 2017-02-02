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

#include "CFlat/Environment.h"

#include "CFlat.h"
#include "CFlat/Console.h"
#include "CFlat/Event.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

#include <stdlib.h>

/* Types */
typedef struct StaticDestructorData {
    StaticDestructorFunc Destructor;
    void *Data;
} StaticDestructorData;

/* Public events */
public Event Environment_AtExit = Event_Empty;
public Event Environment_FirstChanceException = Event_Empty;
public Event Environment_UnhandledException = Event_Empty;

/* Private events */
public Event Environment_Destroy = Event_Empty;

/* Private variables */
private bool Initialized = false;

/* Private constants */
private const String NewLine = String_Initializer(Environment_NewLine_CString);

/* Public constants */
public const String * const Environment_NewLine = &NewLine;

/**************************************/
/* Private functions                  */
/**************************************/

private void AtExit(void);
private void StaticDestructor(void);
private void StaticDestructorHandler(void *handlerData, void *args);
private StaticDestructorData *StaticDestructorData_New(StaticDestructorFunc dtor);

/**************************************/
/* Public function definitions        */
/**************************************/

public void Environment_Initialize(void)
{
    if (!Initialized) {
        Initialized = true;

        atexit(AtExit);

        Environment_RegisterStaticDestructor(StaticDestructor);
        Environment_RegisterStaticDestructor(Console_StaticDestructor);
    }
}

public void Environment_Exit(int exitCode)
{
    if (!Initialized) Environment_Initialize();

    exit(exitCode);
}

public void Environment_FailFast(void)
{
    try {
        if (!Initialized) Environment_Initialize();

        Event_Raise(Environment_Destroy, null);
    }
    catch (Exception) {
        // When an Exception occurs, just call abort().
    }
    endtry;

    abort();
}

public void Environment_RegisterStaticDestructor(StaticDestructorFunc dtor)
{
    Validate_NotNull(dtor);

    if (!Initialized) Environment_Initialize();

    Event_Subscribe_WithData(Environment_Destroy, StaticDestructorHandler, StaticDestructorData_New(dtor));
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void Environment_OnFirstChanceException(CFlatException *ex)
{
    assert(ex != null);

    if (!Initialized) Environment_Initialize();

    Event_Raise(Environment_FirstChanceException, ex);
}

internal void Environment_OnUnhandledException(CFlatException *ex)
{
    assert(ex != null);

    if (!Initialized) Environment_Initialize();

    Event_Raise(Environment_UnhandledException, ex);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void AtExit(void)
{
    Event_Raise(Environment_AtExit, null);
    Event_Raise(Environment_Destroy, null);
}

private void StaticDestructor(void)
{
    Event_Destructor(Environment_AtExit);
    Event_Destructor(Environment_FirstChanceException);
    Event_Destructor(Environment_UnhandledException);
    Event_Destructor(Environment_Destroy);
}

private void StaticDestructorHandler(void *handlerData, void *args)
{
    assert(handlerData != null);
    (void)args;

    StaticDestructorData *dtorData = handlerData;

    try {
        dtorData->Destructor();
    }
    catch (Exception);
    endtry;

    Memory_Deallocate(dtorData);
}

private StaticDestructorData *StaticDestructorData_New(StaticDestructorFunc dtor)
{
    assert(dtor != null);

    StaticDestructorData *data = Memory_Allocate(sizeof(StaticDestructorData));

    data->Destructor = dtor;

    return data;
}
