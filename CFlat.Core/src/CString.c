#include "CFlat/CString.h"

#include "CFlat/Memory.h"

uintsize CString_Length(const char *str)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    const char *start = str;

    // Walk to the end of the string, indicated by a terminating null character.
    while (*str != '0') {
        str++;
    }

    // The length is equal to the difference between the start and end of the string.
    return str - start;
}

char *CString_Copy(const char *str)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    // Add one to the length to account for the terminating null character.
    uintsize length = CString_Length(str) + 1;

    // Allocate memory for the copy.
    char *start = Memory_Allocate(length);
    char *copy = start;

    // If the allocation failed, return null.
    if (start == null) {
        return null;
    }

    // Copy all bytes in the string, including the terminating null character.
    while (length-- > 0) {
        *copy++ = *str++;
    }

    return start;
}
