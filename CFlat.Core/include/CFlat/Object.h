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

/**
 * @file Object.h
 */

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
/// A <see cref="DestructorFunc"/> that is called when the object needs to be destroyed, or <see cref="null"/> if the
/// object should not automatically be destroyed.
/// </param>
#define ObjectVTable_Initializer(destructor) { destructor }

/* Types */
/// <summary>
/// A function to perform clean up of the given object before it gets deallocated.
/// </summary>
/// <param name="obj">The object to clean up.</param>
typedef void(*DestructorFunc)(void *obj);

/// <summary>
/// A function to deallocate the given object.
/// </summary>
/// <param name="obj">The object to deallocate.</param>
typedef void(*DeallocatorFunc)(void *obj);

/// <summary>
/// A virtual method table for the <see cref="Object"/> class.
/// </summary>
typedef struct ObjectVTable {
    /// <summary>
    /// The <see cref="DestructorFunc"/> of the object.
    /// </summary>
    /// <remarks>This member is intended for internal use only and should not be modified directly.</remarks>
    DestructorFunc Destructor;
} ObjectVTable;

/// <summary>
/// Base struct for reference counted objects. Every struct that is intended to be used with Object_Constructor(),
/// Object_Aquire() and Object_Release() should have a member of type Object as its first member.
/// </summary>
typedef struct Object {
    /// <summary>
    /// The reference count of the object.
    /// </summary>
    /// <remarks>This member is intended for internal use only and should not be modified directly.</remarks>
    uintsize RefCount;
    /// <summary>
    /// The <see cref="DeallocatorFunc"/> of the object.
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
/// Initializes the given <see cref="Object"/> and sets the vtable.
/// </summary>
/// <param name="obj">Pointer to an uninitialized <see cref="Object"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
void Object_Constructor(void *obj, const ObjectVTable *vtable);

/// <summary>
/// Sets the deallocator of the given <see cref="Object"/>.
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <param name="deallocator">
/// A <see cref="DeallocatorFunc"/> that is called when the <paramref name="obj"/> needs to be deallocated, or
/// <see cref="null"/> if <paramref name="obj"/> should not automatically be deallocated.
/// </param>
void Object_SetDeallocator(void *obj, DeallocatorFunc deallocator);

/// <summary>
/// Sets the virtual method table of the given <see cref="Object"/>.
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <param name="vtable">Pointer to a virtual method table.</param>
void Object_SetVTable(void *obj, const ObjectVTable *vtable);

/// <summary>
/// Increments the reference count of an <see cref="Object"/>.
///
/// If <paramref name="obj"/> is <see cref="null"/>, the function does nothing.
///
/// The behaviour is undefined if <paramref name="obj"/> has already been deleted as the result of a call to
/// Object_Release().
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <returns><paramref name="obj"/>.</returns>
/// <seealso cref="Object_Release()"/>
void *Object_Aquire(const void *obj);

/// <summary>
/// Decrements the reference count of an <see cref="Object"/>.
///
/// If <paramref name="obj"/> is <see cref="null"/>, the function does nothing and returns <see cref="false"/>.
///
/// If the reference count reaches zero, the object is deleted by first calling the destructor of the object, and then
/// deallocating the memory reserved for the object.
///
/// The behaviour is undefined if <paramref name="obj"/> has already been deleted as the result of a previous call to
/// Object_Release().
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <returns>
/// <see cref="true"/> if the reference count reached zero and <paramref name="obj"/> was deleted; otherwise
/// <see cref="false"/>.
/// </returns>
/// <seealso cref="Object_Aquire()"/>
bool Object_Release(const void *obj);

#endif
