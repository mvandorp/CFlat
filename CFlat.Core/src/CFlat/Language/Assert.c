#include "CFlat/Language/Assert.h"

#include "CFlat.h"
#include "CFlat/String.h"

#include <stdio.h>
#include <stdlib.h>

public void __CFLAT_ASSERT_FAIL(const char *condition, const char *file, int line)
{
    assert(condition != null);
    assert(file != null);
    assert(line > 0);

    try {
        String *message = String_FormatCString(
            "Assertion failed: {cstring}\n   at {cstring}:{int}\n",
            condition,
            file,
            line);

        fprintf(stderr, "%s", String_GetCString(message));

        Object_Release(message);
    }
    catch (Exception);
    endtry;

    abort();
}
