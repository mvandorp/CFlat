#include "CFlat/Collections/IEnumerable.h"

#include "CFlat.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/IEnumerator.h"

/**************************************/
/* Private functions                  */
/**************************************/

private const IEnumerableVTable *GetVTable(const IEnumerable *collection);

/**************************************/
/* Public function definitions        */
/**************************************/

public void IEnumerable_Constructor(
    IEnumerable *collection,
    const IEnumerableVTable *vtable)
{
    Validate_NotNull(vtable);
    Validate_NotNull(vtable->GetEnumerator);

    Object_Constructor(collection, (const ObjectVTable*)vtable);
}

public IEnumerator *IEnumerable_GetEnumerator(const IEnumerable *collection)
{
    return GetVTable(collection)->GetEnumerator(collection);
}

/**************************************/
/* Private function definitions       */
/**************************************/

/// <summary>
/// Gets the virtual method table of an <see cref="IEnumerable"/>.
/// </summary>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/>.</param>
/// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
private const IEnumerableVTable *GetVTable(const IEnumerable *collection)
{
    Validate_NotNull(collection);

    return (const IEnumerableVTable*)((const Object*)collection)->VTable;
}
