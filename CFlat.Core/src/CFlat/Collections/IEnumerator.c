#include "CFlat/Collections/IEnumerator.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

/* Private functions */
private const IEnumeratorVTable *GetVTable(const IEnumerator *enumerator);

/**************************************/
/* Public function definitions        */
/**************************************/

public void IEnumerator_Constructor(
    IEnumerator *enumerator,
    const IEnumeratorVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetCurrent);
    Validate_NotNull(vtable->MoveNext);
    Validate_NotNull(vtable->Reset);

    Object_Constructor(enumerator, (const ObjectVTable*)vtable);
}

public void *IEnumerator_GetCurrent(const IEnumerator *enumerator)
{
    return GetVTable(enumerator)->GetCurrent(enumerator);
}

public bool IEnumerator_MoveNext(IEnumerator *enumerator)
{
    return GetVTable(enumerator)->MoveNext(enumerator);
}

public void IEnumerator_Reset(IEnumerator *enumerator)
{
    GetVTable(enumerator)->Reset(enumerator);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private const IEnumeratorVTable *GetVTable(const IEnumerator *enumerator)
{
    Validate_NotNull(enumerator);

    return (const IEnumeratorVTable*)((const Object*)enumerator)->VTable;
}
