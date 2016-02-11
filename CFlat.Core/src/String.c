#include "CFlat/String.h"

#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"

typedef struct String {
    uintsize length;
    char *cString;
} String;

String *String_New(const char *cString)
{
    // Allocate a new string and set the destructor callback.
    String *str = Object_New(sizeof(String), (Destructor)String_Destructor);

    assert(str != null);

    // Initialize the string to the value represented by cString.
    String_Constructor(str, cString);

    return str;
}

void String_Constructor(String *str, const char *cString)
{
    assert(str != null);

    if (cString == null) {
        str->length = 0;
        str->cString = null;
    }
    else {
        str->length = CString_Length(cString);
        str->cString = CString_Duplicate(cString);

        assert(str->cString != null);
    }
}

void String_Destructor(String *str)
{
    assert(str != null);

    Memory_Deallocate(str->cString);
}

uintsize String_Length(const String *str)
{
    return str->length;
}

const char *String_GetCString(const String *str)
{
    return str->cString;
}
