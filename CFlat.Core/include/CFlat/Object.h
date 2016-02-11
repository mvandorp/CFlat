/// @file Object.h
/// @author Martijn van Dorp
/// @date August 2015

#ifndef CFLAT_CORE_OBJECT_H
#define CFLAT_CORE_OBJECT_H

#include "CFlat.h"

/// <summary>
/// A function to perform clean up on <paramref name="object"/> before it gets deallocated.
/// </summary>
/// <param name="obj">The object to clean up.</param>
typedef void(*Destructor)(void *obj);

/// <summary>
/// Allocates a new object of <paramref name="size"/> bytes.
///
/// The object keeps track of the number of references to itself. The reference count can be incremented with
/// Object_Aquire() and decremented with Object_Release(). If the reference count reaches zero, the destructor is
/// called before the object is automatically deallocated.
///
/// The reference count of the newly allocated object gets initialized to <c>1</c>.
/// </summary>
/// <param name="size">The number of bytes of memory to allocate.</param>
/// <param name="dtor">
/// A <see cref="Destructor"/> callback that points to a function to clean up the memory. The value can be
/// <see cref="null"/>, in which case a destructor will not be invoked.
/// </param>
/// <returns>The pointer to the newly allocated object.</returns>
/// <seealso cref="Object_Delete()"/>
/// <seealso cref="Object_Aquire()"/>
/// <seealso cref="Object_Release()"/>
void *Object_New(uintsize size, Destructor dtor);

/// <summary>
/// Deletes an object allocated by Object_New() regardless of its reference count.
///
/// Deleting an object is performed by first calling the destructor of the object, and then deallocating the memory
/// occupied by the object.
///
/// If <paramref name="obj"/> is <see cref="null"/>, the function does nothing.
///
/// The behaviour is undefined if <paramref name="obj"/> has already been deleted either by Object_Delete() or because
/// the reference count reached zero after a call to Object_Release().
/// </summary>
/// <param name="obj">The object to delete.</param>
/// <seealso cref="Object_New()"/>
/// <seealso cref="Object_Aquire()"/>
/// <seealso cref="Object_Release()"/>
void Object_Delete(void *obj);

/// <summary>
/// Increments the reference count of an object allocated by Object_New().
///
/// If <paramref name="obj"/> is <see cref="null"/>, the function does nothing.
///
/// The behaviour is undefined if <paramref name="obj"/> has already been deleted either by Object_Delete() or because
/// the reference count reached zero after a call to Object_Release().
/// </summary>
/// <param name="obj">The object for which to increment the reference count.</param>
/// <returns><paramref name="obj"/>.</returns>
/// <seealso cref="Object_New()"/>
/// <seealso cref="Object_Delete()"/>
/// <seealso cref="Object_Release()"/>
void *Object_Aquire(void *obj);

/// <summary>
/// Decrements the reference count of an object allocated by Object_New().
///
/// If <paramref name="obj"/> is <see cref="null"/>, the function does nothing and returns <see cref="false"/>.
///
/// If the reference count reaches zero, the destructor of the objet is called, after which the object is deallocated.
///
/// The behaviour is undefined if <paramref name="obj"/> has already been deleted either by Object_Delete() or because
/// the reference count reached zero after a call to Object_Release().
/// </summary>
/// <param name="obj">The object for which to decrement the reference count.</param>
/// <returns>
/// <see cref="true"/> if the reference count reached zero and <paramref name="obj"/> was deleted; otherwise
/// <see cref="false"/>.
/// </returns>
/// <seealso cref="Object_New()"/>
/// <seealso cref="Object_Delete()"/>
/// <seealso cref="Object_Aquire()"/>
bool Object_Release(void *obj);

#endif
