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

//! @file Object.h

#ifndef CFLAT_CORE_OBJECT_H
#define CFLAT_CORE_OBJECT_H

#include "CFlat/Language/Bool.h"
#include "CFlat/Language/Integer.h"

/* Macros */
/// <summary>
/// Initializer for an <see cref="Object"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define CFLAT_OBJECT_INITIALIZER(vtable) { 1, null, vtable }

/// <summary>
/// Initializer for a const <see cref="Object"/>.
/// </summary>
/// <param name="vtable">Pointer to a virtual method table.</param>
#define CFLAT_CONST_OBJECT_INITIALIZER(vtable) { uintsize_MaxValue, null, vtable }

/// <summary>
/// Initializer for an <see cref="ObjectVTable"/>.
/// </summary>
/// <param name="destructor">
///     A <see cref="DestructorFunc"/> that is called when an <see cref="Object"/> needs to be destroyed, or
///     <see cref="null"/> if the <see cref="Object"/> should not automatically be destroyed.
/// </param>
#define ObjectVTable_Initializer(destructor) { destructor }

/* Types */
/// <summary>
/// A function that performs clean up of an object before it gets deallocated.
/// </summary>
/// <param name="obj">Pointer to the object to clean up.</param>
typedef void(*DestructorFunc)(void *obj);

/// <summary>
/// A function that deallocates an object.
/// </summary>
/// <param name="obj">Pointer to the object to deallocate.</param>
typedef void(*DeallocatorFunc)(const void *obj);

/// <summary>
/// A virtual method table for the <see cref="Object"/> class.
/// </summary>
typedef struct ObjectVTable {
    /// <summary>
    /// A <see cref="DestructorFunc"/> that is called when an <see cref="Object"/> needs to be destroyed, or
    /// <see cref="null"/> if the <see cref="Object"/> should not automatically be destroyed.
    /// </summary>
    DestructorFunc Destructor;
} ObjectVTable;

/// <summary>
/// Base struct for reference counted objects. Every struct that is intended to be used with Object_Constructor(),
/// retain() and release() should have a member of type Object as its first member.
/// </summary>
typedef struct Object {
    /// <summary>
    /// The reference count of the object.
    /// </summary>
    /// <remarks>This member is intended for internal use only and should not be modified directly.</remarks>
    uintsize RefCount;
    /// <summary>
    /// A <see cref="DeallocatorFunc"/> that is called when the <see cref="Object"/> needs to be deallocated, or
    /// <see cref="null"/> if the <see cref="Object"/> should not automatically be deallocated.
    /// </summary>
    /// <remarks>This member is intended for internal use only and should not be modified directly.</remarks>
    DeallocatorFunc Deallocator;
    /// <summary>
    /// The virtual method table of the object.
    /// </summary>
    /// <remarks>This member is intended for internal use only and should not be modified directly.</remarks>
    const ObjectVTable *VTable;
} Object;

/* Functions */
/// <summary>
/// Initializes the an <see cref="Object"/> and sets the virtual method table.
/// </summary>
/// <param name="obj">Pointer to an uninitialized <see cref="Object"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="obj"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/>.
/// </exception>
void Object_Constructor(void *obj, const ObjectVTable *vtable);

/// <summary>
/// Sets the deallocator of an <see cref="Object"/>.
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <param name="deallocator">
///     A <see cref="DeallocatorFunc"/> that is called when <paramref name="obj"/> needs to be deallocated, or
///     <see cref="null"/> if <paramref name="obj"/> should not automatically be deallocated.
/// </param>
/// <exception cref="::ArgumentNullException"><paramref name="obj"/> is <see cref="null"/>.</exception>
void Object_SetDeallocator(void *obj, DeallocatorFunc deallocator);

/// <summary>
/// Sets the virtual method table of an <see cref="Object"/>.
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
/// <exception cref="::ArgumentNullException">
///     <paramref name="obj"/> is <see cref="null"/> <b>-or-</b>
///     <paramref name="vtable"/> is <see cref="null"/>.
/// </exception>
void Object_SetVTable(void *obj, const ObjectVTable *vtable);

#endif
