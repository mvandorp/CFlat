#include "CFlat/Collections/List.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/ICollection.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/IList.h"
#include "CFlat/Collections/ListEnumerator.h"

/* Private constants */
/// <summary>
/// The default capacity for a list that is not empty.
/// </summary>
private const int DefaultCapacity = 4;

/**************************************/
/* Private functions                  */
/**************************************/

private void EnsureCapacity(List *list, int capacity);
private bool IsReadOnly(const List *list);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="List"/> class.
/// </summary>
private const IListVTable VTable = IListVTable_Initializer(
    (DestructorFunc)List_Destructor,
    (IEnumerable_GetEnumeratorFunc)List_GetEnumerator,
    (ICollection_GetCountFunc)List_GetCount,
    (ICollection_IsReadOnlyFunc)IsReadOnly,
    (ICollection_AddFunc)List_AddRef,
    (ICollection_ClearFunc)List_Clear,
    (ICollection_ContainsFunc)List_ContainsRef,
    (ICollection_CopyToFunc)List_CopyTo,
    (ICollection_RemoveFunc)List_RemoveRef,
    (IList_GetItemFunc)List_GetItemRef,
    (IList_SetItemFunc)List_SetItemRef,
    (IList_IndexOfFunc)List_IndexOfRef,
    (IList_InsertFunc)List_InsertRef,
    (IList_RemoveAtFunc)List_RemoveAt);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Allocators */
public List *List_New(uintsize elementSize, EqualityPredicate equals)
{
    return List_New_WithCapacity(elementSize, equals, 0);
}

public List *List_New_WithCapacity(uintsize elementSize, EqualityPredicate equals, int capacity)
{
    List *list = Memory_Allocate(sizeof(List));

    try {
        List_Constructor_WithCapacity(list, elementSize, equals, capacity);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

public List *List_New_FromEnumerable(uintsize elementSize, EqualityPredicate equals, const IEnumerable *collection)
{
    List *list = Memory_Allocate(sizeof(List));

    try {
        List_Constructor_FromEnumerable(list, elementSize, equals, collection);

        Object_SetDeallocator(list, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(list);
        throw;
    }
    endtry;

    return list;
}

public List *List_New_FromCollection(uintsize elementSize, EqualityPredicate equals, const ICollection *collection)
{
    List *list = Memory_Allocate(sizeof(List));

    try {
        List_Constructor_FromCollection(list, elementSize, equals, collection);

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
public void List_Constructor(List *list, uintsize elementSize, EqualityPredicate equals)
{
    List_Constructor_WithCapacity(list, elementSize, equals, 0);
}

public void List_Constructor_WithCapacity(List *list, uintsize elementSize, EqualityPredicate equals, int capacity)
{
    List_Constructor_Full(list, &VTable, elementSize, equals, capacity);
}

public void List_Constructor_FromEnumerable(
    List *list,
    uintsize elementSize,
    EqualityPredicate equals,
    const IEnumerable *collection)
{
    Validate_NotNull(collection);

    List_Constructor(list, elementSize, equals);
    List_AddRange(list, collection);
}

public void List_Constructor_FromCollection(
    List *list,
    uintsize elementSize,
    EqualityPredicate equals,
    const ICollection *collection)
{
    Validate_NotNull(collection);

    List_Constructor_WithCapacity(list, elementSize, equals, ICollection_GetCount(collection));
    List_AddRange(list, (const IEnumerable*)collection);
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
        list->Array = Memory_Reallocate(list->Array, (uintsize)capacity * list->ElementSize);
        list->Capacity = capacity;
    }
}

public uintsize List_GetElementSize(const List *list)
{
    Validate_NotNull(list);

    return list->ElementSize;
}

/* Methods */
public void List_AddRange(List *list, const IEnumerable *collection)
{
    Validate_NotNull(list);
    Validate_NotNull(collection);

    List_InsertRange(list, list->Count, collection);
}

public void List_InsertRange(List *list, int index, const IEnumerable *collection)
{
    Validate_NotNull(list);
    Validate_NotNull(collection);
    Validate_IsTrue(
        index >= 0 && index <= list->Count,
        ArgumentOutOfRangeException,
        "Index must be within the bounds of the List.");

    IEnumerator *enumerator = IEnumerable_GetEnumerator(collection);

    try {
        int i = index;

        while (IEnumerator_MoveNext(enumerator)) {
            List_InsertRef(list, i++, IEnumerator_GetCurrent(enumerator));
        }
    }
    finally{
        Object_Release(enumerator);
    }
    endtry;
}

public void List_RemoveRange(List *list, int index, int count)
{
    Validate_NotNull(list);
    Validate_IsTrue(index >= 0, ArgumentOutOfRangeException, "Index cannot be negative.");
    Validate_IsTrue(count >= 0, ArgumentOutOfRangeException, "Count cannot be negative.");
    Validate_IsTrue(
        list->Count < index + count,
        ArgumentException,
        "Index and count were out of bounds for the list or count is greater than the number of elements from index to "
        "the end of the list.");

    uintsize size = list->ElementSize;

    // Copy the contents of the buffer backward after index forward by length bytes.
    Memory_CopyOffset(
        list->Array, (uintsize)(index + count) * size,
        list->Array, (uintsize)count * size,
        (uintsize)(list->Count - (index + count)) * size);

    list->Count -= count;
    list->Version++;
}

/* IEnumerable */
public IEnumerator *List_GetEnumerator(const List *list)
{
    return ListEnumerator_New(list);
}

/* ICollection */
public int List_GetCount(const List *list)
{
    Validate_NotNull(list);

    return list->Count;
}

public void List_AddRef(List *list, const void *item)
{
    Validate_NotNull(list);
    Validate_NotNull(item);

    List_InsertRef(list, list->Count, item);
}

public void List_Clear(List *list)
{
    Validate_NotNull(list);

    list->Count = 0;
    list->Version++;
}

public bool List_ContainsRef(const List *list, const void *item)
{
    return List_IndexOfRef(list, item) >= 0;
}

public void List_CopyTo(const List *list, void *destination, uintsize destinationSize)
{
    Validate_NotNull(list);
    Validate_NotNull(destination);
    Validate_IsTrue(
        destinationSize >= (uintsize)list->Count * list->ElementSize,
        ArgumentException,
        "The number of elements in the list is greater than the number of elements that the destination array can "
        "contain.");

    Memory_Copy(list->Array, destination, (uintsize)list->Count * list->ElementSize);
}

public bool List_RemoveRef(List *list, const void *item)
{
    int index = List_IndexOfRef(list, item);

    if (index >= 0) {
        List_RemoveAt(list, index);
    }

    return index >= 0;
}

/* IList */
public void *List_GetItemRef(const List *list, int index)
{
    Validate_NotNull(list);
    Validate_IsTrue(
        index >= 0 && index <= list->Count,
        ArgumentOutOfRangeException,
        "Index must be within the bounds of the List.");

    byte *array = list->Array;
    uintsize size = list->ElementSize;
    uintsize i = (uintsize)index;

    return &array[i * size];
}

public void List_SetItemRef(List *list, int index, const void *item)
{
    Validate_NotNull(list);
    Validate_NotNull(item);

    Memory_Copy(item, List_GetItemRef(list, index), list->ElementSize);

    list->Version++;
}

public int List_IndexOfRef(const List *list, const void *item)
{
    Validate_NotNull(list);
    Validate_NotNull(item);

    if (list->Equals == null) {
        throw_new(
            InvalidOperationException,
            "Cannot find the index of an element because an equality predicate is not set.");
    }

    byte *array = list->Array;
    uintsize size = list->ElementSize;
    uintsize count = (uintsize)list->Count;

    for (uintsize i = 0; i < count; i++) {
        if (list->Equals(&array[i * size], item)) {
            return (int)i;
        }
    }

    return -1;
}

public void List_InsertRef(List *list, int index, const void *item)
{
    Validate_NotNull(list);
    Validate_NotNull(item);
    Validate_IsTrue(
        index >= 0 && index <= list->Count,
        ArgumentOutOfRangeException,
        "Index must be within the bounds of the List.");

    EnsureCapacity(list, list->Count + 1);

    byte *array = list->Array;
    uintsize size = list->ElementSize;
    uintsize i = (uintsize)index;
    uintsize length = (uintsize)list->Count;

    if (i < length) {
        // Move the contents of the array after index forward by 1 index.
        Memory_Copy(
            &array[i * size],
            &array[(i + 1) * size],
            (length - i) * size);
    }

    // Insert the item.
    Memory_Copy(item, &array[i * size], size);

    list->Count++;
    list->Version++;
}

public void List_RemoveAt(List *list, int index)
{
    List_RemoveRange(list, index, 1);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void List_Constructor_Full(
    List *list,
    const IListVTable *vtable,
    uintsize elementSize,
    EqualityPredicate equals,
    int capacity)
{
    Validate_IsTrue(elementSize > 0, ArgumentOutOfRangeException, "Element size cannot be zero.");
    Validate_IsTrue(capacity >= 0, ArgumentOutOfRangeException, "Capacity cannot be negative.");

    IList_Constructor((IList*)list, vtable);

    list->Equals = equals;
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
    assert(minCapacity >= 0);

    if (list->Capacity < minCapacity) {
        if (minCapacity > List_MaxCapacity) {
            throw_new(OutOfMemoryException, "Capacity exceeded the maximum capacity of a List.");
        }

        int finalCapacity;
        uint capacity;
        capacity = uint_Max((uint)minCapacity, (uint)list->Count * 2);
        capacity = uint_Max(capacity, (uint)DefaultCapacity);
        capacity = uint_Min(capacity, (uint)List_MaxCapacity);
        finalCapacity = (int)uint_Min(capacity, int_MaxValue);

        List_SetCapacity(list, finalCapacity);
    }
}

private bool IsReadOnly(const List *list)
{
    Validate_NotNull(list);

    return false;
}
