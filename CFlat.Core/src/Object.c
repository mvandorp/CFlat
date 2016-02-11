#include "CFlat/Object.h"

#include "CFlat/Memory.h"

typedef struct Object {
    uintsize referenceCount;
    Destructor destructor;
} Object;

static Object *Object_DataToObject(const void *data);
static void *Object_ObjectToData(const Object *obj);

/**************************************/
/* Extern functions                   */
/**************************************/

void *Object_New(uintsize size, Destructor dtor)
{
    Object *object = Memory_Allocate(size + sizeof(Object));

    assert(object != null);

    object->referenceCount = 1;
    object->destructor = dtor;

    return Object_ObjectToData(object);
}

void Object_Delete(void *obj)
{
    if (obj == null) {
        return;
    }

    Object *object = Object_DataToObject(obj);

    if (object->destructor != null) {
        object->destructor(object);
    }

    Memory_Deallocate(object);
}

void *Object_Aquire(void *obj)
{
    if (obj == null) {
        return;
    }
    
    Object *object = Object_DataToObject(obj);

    object->referenceCount++;

    return obj;
}

bool Object_Release(void *obj)
{
    if (obj == null) {
        return false;
    }
    
    Object *object = Object_DataToObject(obj);

    object->referenceCount--;

    if (object->referenceCount == 0) {
        Object_Delete(obj);

        return true;
    }

    return false;
}

/**************************************/
/* Static functions                   */
/**************************************/

static Object *Object_DataToObject(const void *data)
{
    return (byte*)data - sizeof(Object);
}

static void *Object_ObjectToData(const Object *obj)
{
    return (byte*)obj + sizeof(Object);
}