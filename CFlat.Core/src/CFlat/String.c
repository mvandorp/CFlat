#include "CFlat/String.h"
#include "CFlat/String-private.h"

#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"

#include <stdarg.h>

static const String Empty = CFLAT_STRING_LITERAL("");

String *String_New(const char *value)
{
    String *str = Memory_Allocate(sizeof(String));

    // Initialize the string to the value represented by value.
    String_Constructor(str, value);

    // Set the proper deallocator that corresponds with the allocator.
    Object_SetDeallocator(str, Memory_Deallocate);

    return str;
}

void String_Constructor(String *str, const char *value)
{
    // Initialize the object and set the destructor.
    Object_Constructor(str, String_Destructor);

    // Initialize the string.
    if (value == null) {
        str->length = 0;
        str->value = "";
    }
    else {
        str->length = CString_Length(value);
        str->value = CString_Copy(value);
    }
}

void String_Destructor(void *str)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    Memory_Deallocate((char*)((String*)str)->value);
}

uintsize String_GetLength(const String *str)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    return str->length;
}

const char *String_GetCString(const String *str)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    return str->value;
}

char *String_ToCString(const String *str)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    return CString_Copy(str->value);
}

const String *String_Empty(void)
{
    return &Empty;
}
