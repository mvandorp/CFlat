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

#include "CFlat/Object.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"

/* Internal functions */
internal void *const_cast(const void *ptr);

/**************************************/
/* Private functions                  */
/**************************************/

private void Delete(Object *obj);

/**************************************/
/* Public function definitions        */
/**************************************/

public void Object_Constructor(void *obj, const ObjectVTable *vtable)
{
    Validate_NotNull(obj);
    Validate_NotNull(vtable);

    Object *object = obj;

    object->RefCount = 1;
    object->Deallocator = null;
    object->VTable = vtable;
}

public void Object_SetDeallocator(void *obj, DeallocatorFunc dealloc)
{
    Validate_NotNull(obj);

    Object *object = obj;

    // Prevent modifying a constant object.
    if (object->RefCount != uintsize_MaxValue) {
        object->Deallocator = dealloc;
    }
}

public void Object_SetVTable(void *obj, const ObjectVTable *vtable)
{
    Validate_NotNull(obj);
    Validate_NotNull(vtable);

    Object *object = obj;

    // Prevent modifying a constant object.
    if (object->RefCount != uintsize_MaxValue) {
        object->VTable = vtable;
    }
}

public void *Object_Aquire(const void *obj)
{
    if (obj == null) {
        return null;
    }

    Object *object = const_cast(obj);

    // Prevent overflow and prevent modifying a constant object.
    if (object->RefCount != uintsize_MaxValue) {
        object->RefCount++;
    }

    return object;
}

public const void *Object_AquireConst(const void *obj)
{
    return Object_Aquire(obj);
}

public bool Object_Release(const void *obj)
{
    if (obj == null) {
        return false;
    }

    Object *object = const_cast(obj);

    // Prevent modifying a constant object.
    if (object->RefCount != uintsize_MaxValue) {
        object->RefCount--;
    }

    if (object->RefCount == 0) {
        Delete(object);

        return true;
    }

    return false;
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Deletes an <see cref="Object"/>.
/// </summary>
/// <remarks>
///     Deleting an object is performed by first calling the destructor of the object, and then deallocating the memory
///     reserved for the object.
/// </remarks>
/// <param name="obj">Pointer to an <see cref="Object"/>.</param>
private void Delete(Object *obj)
{
    assert(obj != null);

    if (obj->VTable->Destructor != null) {
        obj->VTable->Destructor(obj);
    }

    if (obj->Deallocator != null) {
        obj->Deallocator(obj);
    }
}
