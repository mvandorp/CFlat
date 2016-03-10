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
/// Initializer for an <see cref="Object"/> that initializes the destructor to the given value.
/// </summary>
#define CFLAT_OBJECT_INITIALIZER(destructor) { 1, destructor, null }

/// <summary>
/// Initializer for a const <see cref="Object"/>.
/// </summary>
#define CFLAT_CONST_OBJECT_INITIALIZER() { uintsize_MaxValue, null, null }

/* Types */
/// <summary>
/// A function to perform clean up of the given object before it gets deallocated.
/// </summary>
/// <param name="obj">The object to clean up.</param>
typedef void(*Destructor)(void *obj);

/// <summary>
/// A function to deallocate the given object.
/// </summary>
/// <param name="obj">The object to deallocate.</param>
typedef void(*Deallocator)(void *obj);

/// <summary>
/// Base struct for reference counted objects. Every struct that is intended to be used with Object_Constructor(),
/// Object_Aquire(), Object_Release() and Object_Delete() should have a member of type Object as its first member.
/// </summary>
typedef struct Object {
    /// <summary>
    /// The reference count of the object.
    /// </summary>
    /// <remarks>This member is intended for internal use only and should not be modified directly.</remarks>
    uintsize RefCount;
    /// <summary>
    /// The <see cref="Destructor"/> of the object.
    /// </summary>
    /// <remarks>This member is intended for internal use only and should not be modified directly.</remarks>
    Destructor Destructor;
    /// <summary>
    /// The <see cref="Deallocator"/> of the object.
    /// </summary>
    /// <remarks>This member is intended for internal use only and should not be modified directly.</remarks>
    Deallocator Deallocator;
} Object;

/* Functions */
/// <summary>
/// Initializes the given <see cref="Object"/> and sets the destructor.
/// </summary>
/// <param name="obj">Pointer to an uninitialized <see cref="Object"/>.</param>
/// <param name="destructor">
/// Pointer to a <see cref="Destructor"/> to call when the object needs to be destroyed, or <see cref="null"/> if
/// <paramref name="obj"/> should not automatically be destroyed.
/// </param>
void Object_Constructor(void *obj, Destructor destructor);

/// <summary>
/// Sets the deallocator of the given <see cref="Object"/>.
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <param name="deallocator">
/// Pointer to a <see cref="Deallocator"/> to call when the object needs to be deallocated, or <see cref="null"/> if
/// <paramref name="obj"/> should not automatically be deallocated.
/// </param>
void Object_SetDeallocator(void *obj, Deallocator deallocator);

/// <summary>
/// Sets the destructor of the given <see cref="Object"/>.
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <param name="dtor">
/// Pointer to a <see cref="Destructor"/> to call when the object needs to be destroyed, or <see cref="null"/> if
/// <paramref name="obj"/> should not automatically be destroyed.
/// </param>
void Object_SetDestructor(void *obj, Destructor dtor);

/// <summary>
/// Deletes an <see cref="Object"/> regardless of its reference count.
///
/// Deleting an object is performed by first calling the destructor of the object, and then deallocating the memory
/// reserved for the object.
///
/// If <paramref name="obj"/> is <see cref="null"/>, the function does nothing.
///
/// The behaviour is undefined if <paramref name="obj"/> has already been deleted either by Object_Delete() or because
/// the reference count reached zero after a call to Object_Release().
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <seealso cref="Object_Aquire()"/>
/// <seealso cref="Object_Release()"/>
void Object_Delete(const void *obj);

/// <summary>
/// Increments the reference count of an <see cref="Object"/>.
///
/// If <paramref name="obj"/> is <see cref="null"/>, the function does nothing.
///
/// The behaviour is undefined if <paramref name="obj"/> has already been deleted either by Object_Delete() or because
/// the reference count reached zero after a call to Object_Release().
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <returns><paramref name="obj"/>.</returns>
/// <seealso cref="Object_Delete()"/>
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
/// The behaviour is undefined if <paramref name="obj"/> has already been deleted either by Object_Delete() or because
/// the reference count reached zero after a call to Object_Release().
/// </summary>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
/// <returns>
/// <see cref="true"/> if the reference count reached zero and <paramref name="obj"/> was deleted; otherwise
/// <see cref="false"/>.
/// </returns>
/// <seealso cref="Object_Delete()"/>
/// <seealso cref="Object_Aquire()"/>
bool Object_Release(const void *obj);

#endif
