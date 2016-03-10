#include "CFlat/Collections/IEnumerator.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

public void IEnumerator_Constructor(
    void *enumerator,
    Destructor destructor,
    IEnumerator_GetCurrentCallback getCurrent,
    IEnumerator_MoveNextCallback moveNext,
    IEnumerator_ResetCallback reset)
{
    Validate_NotNull(enumerator);
    Validate_NotNull(getCurrent);
    Validate_NotNull(moveNext);
    Validate_NotNull(reset);

    Object_Constructor(enumerator, destructor);

    ((IEnumerator*)enumerator)->GetCurrent = getCurrent;
    ((IEnumerator*)enumerator)->MoveNext = moveNext;
    ((IEnumerator*)enumerator)->Reset = reset;
}

public void *IEnumerator_GetCurrent(const void *enumerator)
{
    Validate_NotNull(enumerator);

    return ((const IEnumerator*)enumerator)->GetCurrent(enumerator);
}

public bool IEnumerator_MoveNext(void *enumerator)
{
    Validate_NotNull(enumerator);

    return ((IEnumerator*)enumerator)->MoveNext(enumerator);
}

public void IEnumerator_Reset(void *enumerator)
{
    Validate_NotNull(enumerator);

    ((IEnumerator*)enumerator)->Reset(enumerator);
}
