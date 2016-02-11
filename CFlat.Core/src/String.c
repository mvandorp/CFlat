#include "CFlat/String.h"

#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"

typedef struct String {
    uintsize length;
    char *value;
} String;

String *String_New(const char *value)
{
    // Allocate a new string and set the destructor callback.
    String *str = Object_New(sizeof(String), (Destructor)String_Destructor);

    // TODO: If the allocation failed, throw an OutOfMemoryException.
    assert(str != null);

    // Initialize the string to the value represented by cString.
    String_Constructor(str, value);

    return str;
}

void String_Constructor(String *str, const char *value)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    if (value == null) {
        str->length = 0;
        str->value = null;
    }
    else {
        str->length = CString_Length(value);
        str->value = CString_Duplicate(value);

        // TODO: If the duplication failed, throw an OutOfMemoryException.
        assert(str->value != null);
    }
}

void String_Destructor(String *str)
{
    // TODO: If str is null, throw an ArgumentNullException.
    assert(str != null);

    Memory_Deallocate(str->value);
}

uintsize String_Length(const String *str)
{
    return str->length;
}

const char *String_GetCString(const String *str)
{
    return str->value;
}
