#include "CFlat/StringHelper.h"

#include "CFlat/CString.h"

String String_WrapCString(const char *value)
{
    String str;

    // Do not set the destructor to prevent the value from being deallocated.
    Object_Constructor(&str, null);

    // Initialize the string.
    if (value == null) {
        str.length = 0;
        str.value = "";
    }
    else {
        str.length = CString_Length(value);
        str.value = value;
    }

    return str;
}
