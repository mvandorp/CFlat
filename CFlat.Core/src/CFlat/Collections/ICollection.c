#include "CFlat/Collections/ICollection.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

/* Private functions */
private const ICollectionVTable *GetVTable(const ICollection *collection);

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructors */
public void ICollection_Constructor(
    ICollection *collection,
    const ICollectionVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetCount);
    Validate_NotNull(vtable->IsReadOnly);
    Validate_NotNull(vtable->Add);
    Validate_NotNull(vtable->Clear);
    Validate_NotNull(vtable->Contains);
    Validate_NotNull(vtable->CopyTo);
    Validate_NotNull(vtable->Remove);

    IEnumerable_Constructor((IEnumerable*)collection, (const IEnumerableVTable*)vtable);
}

/* IEnumerable */
public IEnumerator *ICollection_GetEnumerator(const ICollection *collection)
{
    return IEnumerable_GetEnumerator((const IEnumerable*)collection);
}

/* Properties */
public int ICollection_GetCount(const ICollection *collection)
{
    return GetVTable(collection)->GetCount(collection);
}

public bool ICollection_IsReadOnly(const ICollection *collection)
{
    return GetVTable(collection)->IsReadOnly(collection);
}

/* Methods */
public void ICollection_Add(ICollection *collection, const void *item)
{
    GetVTable(collection)->Add(collection, item);
}

public void ICollection_Clear(ICollection *collection)
{
    GetVTable(collection)->Clear(collection);
}

public bool ICollection_Contains(const ICollection *collection, const void *item)
{
    return GetVTable(collection)->Contains(collection, item);
}

public void ICollection_CopyTo(const ICollection *collection, void *destination, uintsize destinationSize)
{
     GetVTable(collection)->CopyTo(collection, destination, destinationSize);
}

public bool ICollection_Remove(ICollection *collection, const void *item)
{
    return GetVTable(collection)->Remove(collection, item);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private const ICollectionVTable *GetVTable(const ICollection *collection)
{
    Validate_NotNull(collection);

    return (const ICollectionVTable*)((const Object*)collection)->VTable;
}
