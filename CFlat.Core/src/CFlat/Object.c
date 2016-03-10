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

public void Object_Constructor(void *obj, Destructor dtor)
{
    Validate_NotNull(obj);

    Object *object = (Object*)obj;

    object->RefCount = 1;
    object->Destructor = dtor;
    object->Deallocator = null;
}

public void Object_SetDeallocator(void *obj, Deallocator dealloc)
{
    Validate_NotNull(obj);

    Object *object = (Object*)obj;

    // Prevent modifying a constant object.
    if (object->RefCount != uintsize_MaxValue) {
        object->Deallocator = dealloc;
    }
}

public void Object_SetDestructor(void *obj, Destructor dtor)
{
    Validate_NotNull(obj);

    Object *object = (Object*)obj;

    // Prevent modifying a constant object.
    if (object->RefCount != uintsize_MaxValue) {
        object->Destructor = dtor;
    }
}

public void Object_Delete(const void *obj)
{
    if (obj == null) {
        return;
    }

    Object *object = (Object*)obj;

    if (object->Destructor != null) {
        object->Destructor(object);
    }

    if (object->Deallocator != null) {
        object->Deallocator(object);
    }
}

public void *Object_Aquire(const void *obj)
{
    if (obj == null) {
        return null;
    }

    Object *object = (Object*)obj;

    // Prevent overflow and prevent modifying a constant object.
    if (object->RefCount != uintsize_MaxValue) {
        object->RefCount++;
    }

    return (void*)obj;
}

public bool Object_Release(const void *obj)
{
    if (obj == null) {
        return false;
    }

    Object *object = (Object*)obj;

    // Prevent modifying a constant object.
    if (object->RefCount != uintsize_MaxValue) {
        object->RefCount--;
    }

    if (object->RefCount == 0) {
        Object_Delete(object);

        return true;
    }

    return false;
}
