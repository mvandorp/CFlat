#include "CFlat/Object.h"

#include "CFlat/Memory.h"

void Object_Constructor(void *obj, Destructor dtor)
{
    // TODO: If obj is null, throw an ArgumentNullException.
    assert(obj != null);

    Object *object = (Object*)obj;

    object->refCount = 1;
    object->destructor = dtor;
    object->deallocator = null;
}

void Object_SetDeallocator(void *obj, Deallocator dealloc)
{
    // TODO: If obj is null, throw an ArgumentNullException.
    assert(obj != null);

    Object *object = (Object*)obj;

    object->deallocator = dealloc;
}

void Object_Delete(void *obj)
{
    if (obj == null) {
        return;
    }

    Object *object = (Object*)obj;

    if (object->destructor != null) {
        object->destructor(object);
    }

    if (object->deallocator != null) {
        object->deallocator(object);
    }
}

void *Object_Aquire(void *obj)
{
    if (obj == null) {
        return null;
    }

    Object *object = (Object*)obj;

    object->refCount++;

    return obj;
}

bool Object_Release(void *obj)
{
    if (obj == null) {
        return false;
    }

    Object *object = (Object*)obj;

    object->refCount--;

    if (object->refCount == 0) {
        Object_Delete(object);

        return true;
    }

    return false;
}