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

#include "CFlat/Event.h"

#include "CFlat.h"
#include "CFlat/const_cast.h"
#include "CFlat/Object.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/List.h"

/* Types */
typedef struct EventData {
    EventHandler Handler;
    void *HandlerData;
    bool HandlerDataIsObject;
} EventData;

/**************************************/
/* Private functions                  */
/**************************************/

private Event Event_Create(void);
private void Event_SubscribeRef_Full(Event *event, EventHandler handler, void *data, bool dataIsObject);
private void Event_UnsubscribeRef_Full(Event *event, EventHandler handler, const void *data, bool dataIsObject);
private bool EventData_Equals(const void *x, const void *y);

/**************************************/
/* Public function definitions        */
/**************************************/

public void Event_DestructorRef(Event *event)
{
    Validate_NotNull(event);

    if (*event == null) return;

    int count = List_GetCount((List*)*event);

    for (int i = 0; i < count; i++) {
        EventData eventData = List_GetItem((List*)*event, i, EventData);

        if (eventData.HandlerDataIsObject) {
            release(eventData.HandlerData);
        }
    }

    release(*event);

    *event = null;
}

public void Event_Raise(Event event, void *args)
{
    if (event == null) return;

    int count = List_GetCount((List*)event);

    for (int i = count - 1; i >= 0; i--) {
        EventData eventData = List_GetItem((List*)event, i, EventData);

        eventData.Handler(eventData.HandlerData, args);
    }
}

public void Event_SubscribeRef(Event *event, EventHandler handler)
{
    Event_SubscribeRef_Full(event, handler, null, false);
}

public void Event_SubscribeRef_WithData(Event *event, EventHandler handler, void *data)
{
    Event_SubscribeRef_Full(event, handler, data, false);
}

public void Event_SubscribeRef_WithObject(Event *event, EventHandler handler, Object *object)
{
    Event_SubscribeRef_Full(event, handler, object, true);
}

public void Event_UnsubscribeRef(Event *event, EventHandler handler)
{
    Event_UnsubscribeRef_Full(event, handler, null, false);
}

public void Event_UnsubscribeRef_WithData(Event *event, EventHandler handler, const void *data)
{
    Event_UnsubscribeRef_Full(event, handler, data, false);
}

public void Event_UnsubscribeRef_WithObject(Event *event, EventHandler handler, const Object *object)
{
    Event_UnsubscribeRef_Full(event, handler, object, true);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void Event_SubscribeRef_Full(Event *event, EventHandler handler, void *data, bool dataIsObject)
{
    Validate_NotNull(event);
    Validate_NotNull(handler);

    if (*event == null) *event = Event_Create();

    EventData eventData;
    eventData.Handler = handler;
    eventData.HandlerData = data;
    eventData.HandlerDataIsObject = dataIsObject;

    List_Add((List*)*event, eventData);

    if (eventData.HandlerDataIsObject) {
        retain(eventData.HandlerData);
    }
}

private void Event_UnsubscribeRef_Full(Event *event, EventHandler handler, const void *data, bool dataIsObject)
{
    Validate_NotNull(event);

    if (*event == null) return;

    EventData eventData;
    eventData.Handler = handler;
    eventData.HandlerData = const_cast(data);
    eventData.HandlerDataIsObject = dataIsObject;

    List_Remove((List*)*event, eventData);

    if (eventData.HandlerDataIsObject) {
        release(eventData.HandlerData);
    }

    if (List_GetCount((List*)*event) == 0) Event_Destructor(*event);
}

private Event Event_Create(void)
{
    return List_New(sizeof(EventData), EventData_Equals);
}

private bool EventData_Equals(const void *x, const void *y)
{
    const EventData *data1 = (const EventData*)x;
    const EventData *data2 = (const EventData*)y;

    return
        data1->Handler == data2->Handler &&
        data1->HandlerData == data2->HandlerData &&
        data1->HandlerDataIsObject == data2->HandlerDataIsObject;
}
