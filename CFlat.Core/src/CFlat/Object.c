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

void Object_Constructor(void *obj, Destructor dtor)
{
    Validate_NotNull(obj);

    Object *object = (Object*)obj;

    object->RefCount = 1;
    object->Destructor = dtor;
    object->Deallocator = null;
}

void Object_SetDeallocator(void *obj, Deallocator dealloc)
{
    Validate_NotNull(obj);

    Object *object = (Object*)obj;

    object->Deallocator = dealloc;
}

void Object_Delete(void *obj)
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

void *Object_Aquire(void *obj)
{
    if (obj == null) {
        return null;
    }

    Object *object = (Object*)obj;

    object->RefCount++;

    return obj;
}

bool Object_Release(void *obj)
{
    if (obj == null) {
        return false;
    }

    Object *object = (Object*)obj;

    object->RefCount--;

    if (object->RefCount == 0) {
        Object_Delete(object);

        return true;
    }

    return false;
}
