#include "CFlat/Collections/ListEnumerator.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/List.h"

/* Types */
typedef struct ListEnumerator {
    IEnumerator Base;
    List *List;
    void *Current;
    int Index;
    uintsize Version;
} ListEnumerator;

/* Private functions */
private void ListEnumerator_Constructor(ListEnumerator *enumerator, const List *list);
private void ListEnumerator_Destructor(void *enumerator);
private void *ListEnumerator_GetCurrent(const void *enumerator);
private bool ListEnumerator_MoveNext(void *enumerator);
private void ListEnumerator_Reset(void *enumerator);

/**************************************/
/* Internal function definitions      */
/**************************************/

internal IEnumerator *ListEnumerator_New(const List *list)
{
    Validate_NotNull(list);

    ListEnumerator *enumerator = Memory_Allocate(sizeof(ListEnumerator));

    try {
        ListEnumerator_Constructor(enumerator, list);

        Object_SetDeallocator(enumerator, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(enumerator);

        throw;
    }
    endtry;

    return (IEnumerator*)enumerator;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void ListEnumerator_Constructor(ListEnumerator *enumerator, const List *list)
{
    Validate_NotNull(enumerator);
    Validate_NotNull(list);

    IEnumerator_Constructor(
        enumerator,
        ListEnumerator_Destructor,
        ListEnumerator_GetCurrent,
        ListEnumerator_MoveNext,
        ListEnumerator_Reset);

    enumerator->List = Object_Aquire(list);
    enumerator->Index = 0;
    enumerator->Current = null;
    enumerator->Version = List_GetVersion(list);
}

private void ListEnumerator_Destructor(void *enumerator)
{
    Validate_NotNull(enumerator);

    Object_Release(((ListEnumerator*)enumerator)->List);
}

private void *ListEnumerator_GetCurrent(const void *enumerator)
{
    ListEnumerator *listEnumerator = (ListEnumerator*)enumerator;

    Validate_NotNull(listEnumerator);
    Validate_State(
        listEnumerator->Index > 0 &&
        listEnumerator->Index <= List_GetCount(listEnumerator->List),
        "Enumeration has either not started or has already finished.");

    return listEnumerator->Current;
}

private bool ListEnumerator_MoveNext(void *enumerator)
{
    ListEnumerator *listEnumerator = (ListEnumerator*)enumerator;

    Validate_NotNull(listEnumerator);

    if (listEnumerator->Version == List_GetVersion(listEnumerator->List) &&
        listEnumerator->Index < List_GetCount(listEnumerator->List)) {

        listEnumerator->Current = List_IndexRef(listEnumerator->List, listEnumerator->Index);
        listEnumerator->Index++;

        return true;
    }
    else {
        if (listEnumerator->Version != List_GetVersion(listEnumerator->List)) {
            throw_new(InvalidOperationException, "Collection was modified; enumeration operation may not execute.");
        }

        listEnumerator->Current = null;
        listEnumerator->Index = List_GetCount(listEnumerator->List) + 1;

        return false;
    }
}

private void ListEnumerator_Reset(void *enumerator)
{
    ListEnumerator *listEnumerator = (ListEnumerator*)enumerator;

    Validate_NotNull(listEnumerator);

    if (listEnumerator->Version != List_GetVersion(listEnumerator->List)) {
        throw_new(InvalidOperationException, "Collection was modified; enumeration operation may not execute.");
    }

    listEnumerator->Index = 0;
    listEnumerator->Current = null;
}
