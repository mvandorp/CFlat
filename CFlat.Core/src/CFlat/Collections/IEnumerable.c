#include "CFlat/Collections/IEnumerable.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

public void IEnumerable_Constructor(
    void *enumerable,
    Destructor destructor,
    IEnumerable_GetEnumeratorCallback getEnumerator)
{
    Validate_NotNull(enumerable);
    Validate_NotNull(getEnumerator);

    Object_Constructor(enumerable, destructor);

    ((IEnumerable*)enumerable)->GetEnumerator = getEnumerator;
}

public IEnumerator *IEnumerable_GetEnumerator(const void *enumerable)
{
    Validate_NotNull(enumerable);

    return ((const IEnumerable*)enumerable)->GetEnumerator(enumerable);
}
