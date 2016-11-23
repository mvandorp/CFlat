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

//! @file Event.h

#ifndef CFLAT_CORE_EVENT_H
#define CFLAT_CORE_EVENT_H

#include "CFlat/Object.h"
#include "CFlat/Language/Keywords.h"

/* Types */
/// <summary>
/// Used to notify subscribers when an event occurs.
/// </summary>
/// <remarks>
///     Functions that match the <see cref="EventHandler"/> prototype can subscribe to an event with
///     <see cref="Event_Subscribe()"/>. When the event is raised, all subscribed event handlers are invoked.
///
///     An event shall be initialized to the value <see cref="Event_Empty"/>. At the end of the event's lifetime,
///     <see cref="Event_Destructor"/> shall be called on that event.
/// </remarks>
typedef void *Event;

/// <summary>
/// A function that can be subscribed to an <see cref="Event"/>.
/// </summary>
/// <param name="handlerData">Pointer to data associated with the subscriber itsself, or <see cref="null"/>.</param>
/// <param name="args">Pointer to event data, or <see cref="null"/>.</param>
typedef void (*EventHandler)(void *handlerData, void *args);

/* Constants */
/// <summary>
/// Represents an event with no subscribers.
/// </summary>
#define Event_Empty null

/* Functions */
/// <summary>
/// Destroys an <see cref="Event"/>.
/// </summary>
/// <param name="event">An <see cref="Event"/>, must be an lvalue.</param>
#define Event_Destructor(event) Event_DestructorRef(&event)

/// <summary>
/// Destroys an <see cref="Event"/>.
/// </summary>
/// <param name="event">Pointer to an <see cref="Event"/>.</param>
public void Event_DestructorRef(Event *event);

/// <summary>
/// Raises an <see cref="Event"/>, which invokes all event handlers subscribed to the event.
/// </summary>
/// <param name="event">An <see cref="Event"/>.</param>
/// <param name="args">Pointer to event data, or <see cref="null"/>.</param>
public void Event_Raise(Event event, void *args);

/// <summary>
/// Subscribes an event handler to an <see cref="Event"/>.
/// </summary>
/// <param name="event">An <see cref="Event"/>, must be an lvalue.</param>
/// <param name="handler">An <see cref="EventHandler"/> that is called when <paramref name="event"/> is raied.</param>
/// <exception cref="::ArgumentNullException"><paramref name="handler"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
#define Event_Subscribe(event, handler) Event_SubscribeRef(&event, handler)

/// <summary>
/// Subscribes an event handler to an <see cref="Event"/>.
/// </summary>
/// <param name="event">Pointer to an <see cref="Event"/>.</param>
/// <param name="handler">An <see cref="EventHandler"/> that is called when <paramref name="event"/> is raied.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="event"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="handler"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
public void Event_SubscribeRef(Event *event, EventHandler handler);

/// <summary>
/// Subscribes an event handler to an <see cref="Event"/>.
/// </summary>
/// <param name="event">An <see cref="Event"/>, must be an lvalue.</param>
/// <param name="handler">An <see cref="EventHandler"/> that is called when <paramref name="event"/> is raied.</param>
/// <param name="data">Pointer to data associated with the subscriber itsself, or <see cref="null"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="handler"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
#define Event_Subscribe_WithData(event, handler, data) Event_SubscribeRef_WithData(&event, handler, data)

/// <summary>
/// Subscribes an event handler to an <see cref="Event"/>.
/// </summary>
/// <param name="event">Pointer to an <see cref="Event"/>.</param>
/// <param name="handler">An <see cref="EventHandler"/> that is called when <paramref name="event"/> is raied.</param>
/// <param name="data">Pointer to data associated with the subscriber itsself, or <see cref="null"/>.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="event"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="handler"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
public void Event_SubscribeRef_WithData(Event *event, EventHandler handler, void *data);

/// <summary>
/// Subscribes an event handler to an <see cref="Event"/>.
/// </summary>
/// <param name="event">An <see cref="Event"/>, must be an lvalue.</param>
/// <param name="handler">An <see cref="EventHandler"/> that is called when <paramref name="event"/> is raied.</param>
/// <param name="object">
///     Pointer to an <see cref="Object"/> associated with the subscriber itsself, or <see cref="null"/>.
/// </param>
/// <exception cref="::ArgumentNullException"><paramref name="handler"/> is <see cref="null"/>.</exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
#define Event_Subscribe_WithObject(event, handler, object) Event_SubscribeRef_WithObject(&event, handler, object)

/// <summary>
/// Subscribes an event handler to an <see cref="Event"/>.
/// </summary>
/// <param name="event">Pointer to an <see cref="Event"/>.</param>
/// <param name="handler">An <see cref="EventHandler"/> that is called when <paramref name="event"/> is raied.</param>
/// <param name="object">
///     Pointer to an <see cref="Object"/> associated with the subscriber itsself, or <see cref="null"/>.
/// </param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="event"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="handler"/> is <see cref="null"/>.
/// </exception>
/// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
public void Event_SubscribeRef_WithObject(Event *event, EventHandler handler, Object *object);

/// <summary>
/// Unsubscribes an event handler from an <see cref="Event"/>.
/// </summary>
/// <param name="event">An <see cref="Event"/>, must be an lvalue.</param>
/// <param name="handler">The <see cref="EventHandler"/> to unsubscribe.</param>
#define Event_Unsubscribe(event, handler) Event_UnsubscribeRef(&event, handler)

/// <summary>
/// Unsubscribes an event handler from an <see cref="Event"/>.
/// </summary>
/// <param name="event">Pointer to an <see cref="Event"/>.</param>
/// <param name="handler">The <see cref="EventHandler"/> to unsubscribe.</param>
/// <exception cref="::ArgumentNullException"><paramref name="event"/> is <see cref="null"/>.</exception>
public void Event_UnsubscribeRef(Event *event, EventHandler handler);

/// <summary>
/// Unsubscribes an event handler from an <see cref="Event"/>.
/// </summary>
/// <param name="event">An <see cref="Event"/>, must be an lvalue.</param>
/// <param name="handler">The <see cref="EventHandler"/> to unsubscribe.</param>
/// <param name="data">Pointer to data associated with the subscriber itsself, or <see cref="null"/>.</param>
#define Event_Unsubscribe_WithData(event, handler, data) Event_UnsubscribeRef_WithData(&event, handler, data)

/// <summary>
/// Unsubscribes an event handler from an <see cref="Event"/>.
/// </summary>
/// <param name="event">Pointer to an <see cref="Event"/>.</param>
/// <param name="handler">The <see cref="EventHandler"/> to unsubscribe.</param>
/// <param name="data">Pointer to data associated with the subscriber itsself, or <see cref="null"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="event"/> is <see cref="null"/>.</exception>
public void Event_UnsubscribeRef_WithData(Event *event, EventHandler handler, const void *data);

/// <summary>
/// Unsubscribes an event handler from an <see cref="Event"/>.
/// </summary>
/// <param name="event">An <see cref="Event"/>, must be an lvalue.</param>
/// <param name="handler">The <see cref="EventHandler"/> to unsubscribe.</param>
/// <param name="object">
///     Pointer to an <see cref="Object"/> associated with the subscriber itsself, or <see cref="null"/>.
/// </param>
#define Event_Unsubscribe_WithObject(event, handler, object) Event_UnsubscribeRef_WithObject(&event, handler, object)

/// <summary>
/// Unsubscribes an event handler from an <see cref="Event"/>.
/// </summary>
/// <param name="event">Pointer to an <see cref="Event"/>.</param>
/// <param name="handler">The <see cref="EventHandler"/> to unsubscribe.</param>
/// <param name="object">
///     Pointer to an <see cref="Object"/> associated with the subscriber itsself, or <see cref="null"/>.
/// </param>
/// <exception cref="::ArgumentNullException"><paramref name="event"/> is <see cref="null"/>.</exception>
public void Event_UnsubscribeRef_WithObject(Event *event, EventHandler handler, const Object *object);

#endif
