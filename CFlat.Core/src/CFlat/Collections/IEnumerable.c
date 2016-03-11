#include "CFlat/Collections/IEnumerable.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

/* Private functions */
private const IEnumerableVTable *GetVTable(const IEnumerable *enumerable);

/**************************************/
/* Public function definitions        */
/**************************************/

public void IEnumerable_Constructor(
    IEnumerable *enumerable,
    const IEnumerableVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetEnumerator);

    Object_Constructor(enumerable, (const ObjectVTable*)vtable);
}

public IEnumerator *IEnumerable_GetEnumerator(const IEnumerable *enumerable)
{
    return GetVTable(enumerable)->GetEnumerator(enumerable);
}

/**************************************/
/* Private function definitions       */
/**************************************/

private const IEnumerableVTable *GetVTable(const IEnumerable *enumerable)
{
    Validate_NotNull(enumerable);

    return (const IEnumerableVTable*)((const Object*)enumerable)->VTable;
}
