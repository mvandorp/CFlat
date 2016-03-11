#include "CFlat/Collections/List.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/ListEnumerator.h"

/* Private constants */
private const int DefaultCapacity = 4;

/* Private functions */
private void EnsureCapacity(List *list, int capacity);

/* Private constants */
private const IEnumerableVTable VTable = IEnumerableVTable_Initializer(
    (DestructorFunc)List_Destructor,
    (IEnumerable_GetEnumeratorFunc)List_GetEnumerator);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public List *List_New(uintsize elementSize)
{
    return List_New_WithCapacity(elementSize, 0);
}

public List *List_New_WithCapacity(uintsize elementSize, int capacity)
{
    List *list = Memory_Allocate(sizeof(List));

    try {
        List_Constructor_WithCapacity(list, elementSize, capacity);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

/* Constructors */
public void List_Constructor(List *list, uintsize elementSize)
{
    List_Constructor_Full(list, &VTable, elementSize, DefaultCapacity);
}

public void List_Constructor_WithCapacity(List *list, uintsize elementSize, int capacity)
{
    List_Constructor_Full(list, &VTable, elementSize, capacity);
}

/* Destructor */
public void List_Destructor(List *list)
{
    Validate_NotNull(list);

    Memory_Deallocate(list->Array);
}

/* Properties */
public int List_GetCapacity(const List *list)
{
    Validate_NotNull(list);

    return list->Capacity;
}

public void List_SetCapacity(List *list, int capacity)
{
    Validate_NotNull(list);
    Validate_IsTrue(
        capacity >= list->Count,
        ArgumentOutOfRangeException,
        "Capacity cannot be smaller than the current length.");

    if (capacity != list->Capacity) {
        list->Array = Memory_Reallocate(list->Array, capacity * list->ElementSize);
        list->Capacity = capacity;
    }
}

public int List_GetCount(const List *list)
{
    Validate_NotNull(list);

    return list->Count;
}

public uintsize List_GetElementSize(const List *list)
{
    Validate_NotNull(list);

    return list->ElementSize;
}

/* Methods */
public void List_AddRef(List *list, const void *value)
{
    Validate_NotNull(list);
    Validate_NotNull(value);

    List_InsertRef(list, list->Count, value);
}

public void List_AddRange(List *list, IEnumerable *enumerable)
{
    Validate_NotNull(list);
    Validate_NotNull(enumerable);

    List_InsertRange(list, list->Count, enumerable);
}

public void List_Clear(List *list)
{
    Validate_NotNull(list);

    list->Count = 0;
    list->Version++;
}

public IEnumerator *List_GetEnumerator(const List *list)
{
    return ListEnumerator_New(list);
}

public void *List_IndexRef(const List *list, int index)
{
    Validate_NotNull(list);
    Validate_IsTrue(
        index >= 0 && index <= list->Count,
        ArgumentOutOfRangeException,
        "Index must be within the bounds of the List.");

    byte *array = list->Array;

    return &array[index * list->ElementSize];
}

public void List_InsertRef(List *list, int index, const void *value)
{
    Validate_NotNull(list);
    Validate_IsTrue(
        index >= 0 && index <= list->Count,
        ArgumentOutOfRangeException,
        "Index must be within the bounds of the List.");

    EnsureCapacity(list, list->Count + 1);

    uintsize size = list->ElementSize;

    if (index < list->Count) {
        // Move the contents of the array after index forward by 1 index.
        Memory_CopyOffset(
            list->Array, index * size,
            list->Array, (index + 1) * size,
            (list->Count - index) * size);
    }

    // Insert the value.
    Memory_CopyOffset(value, 0, list->Array, index * size, size);

    list->Count++;
    list->Version++;
}

public void List_InsertRange(List *list, int index, IEnumerable *enumerable)
{
    Validate_NotNull(list);
    Validate_NotNull(enumerable);
    Validate_IsTrue(
        index >= 0 && index <= list->Count,
        ArgumentOutOfRangeException,
        "Index must be within the bounds of the List.");

    IEnumerator *enumerator = IEnumerable_GetEnumerator(enumerable);

    try {
        while (IEnumerator_MoveNext(enumerator)) {
            List_InsertRef(list, index++, IEnumerator_GetCurrent(enumerator));
        }
    }
    finally{
        Object_Release(enumerator);
    }
    endtry;
}

public void List_RemoveAt(List *list, int index)
{
    List_RemoveRange(list, index, 1);
}

public void List_RemoveRange(List *list, int startIndex, int count)
{
    Validate_NotNull(list);
    Validate_IsTrue(
        startIndex >= 0 && startIndex <= list->Count,
        ArgumentOutOfRangeException,
        "Index must be within the bounds of the List.");
    Validate_IsTrue(
        count >= 0 && startIndex + count <= list->Count,
        ArgumentOutOfRangeException,
        "Count must be positive and refer to a location within the list.");

    uintsize size = list->ElementSize;

    // Copy the contents of the buffer backward after index forward by length bytes.
    Memory_CopyOffset(
        list->Array, (startIndex + count) * size,
        list->Array, startIndex * size,
        (list->Count - (startIndex + count)) * size);

    list->Count -= count;
    list->Version++;
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void List_Constructor_Full(
    List *list,
    const IEnumerableVTable *vtable,
    uintsize elementSize,
    int capacity)
{
    Validate_IsTrue(capacity >= 0, ArgumentOutOfRangeException, "Capacity cannot be negative.");
    Validate_IsTrue(elementSize > 0, ArgumentOutOfRangeException, "Element size cannot be zero.");

    IEnumerable_Constructor((IEnumerable*)list, vtable);

    list->Array = null;
    list->Capacity = 0;
    list->Count = 0;
    list->ElementSize = elementSize;
    list->Version = 0;

    List_SetCapacity(list, capacity);
}

internal uintsize List_GetVersion(const List *list)
{
    Validate_NotNull(list);

    return list->Version;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void EnsureCapacity(List *list, int minCapacity)
{
    assert(list != null);

    if (list->Capacity < minCapacity) {
        if (minCapacity > List_MaxCapacity) {
            throw_new(OutOfMemoryException, "Capacity exceeded the maximum capacity of a List.");
        }

        uint capacity;
        capacity = uint_Max(minCapacity, list->Count * 2);
        capacity = uint_Max(capacity, DefaultCapacity);
        capacity = uint_Min(capacity, List_MaxCapacity);

        List_SetCapacity(list, capacity);
    }
}
