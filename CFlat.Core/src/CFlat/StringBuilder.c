#include "CFlat/StringBuilder.h"

#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/StringHelper.h"

#include <stdarg.h>
#include <string.h>

struct StringBuilder {
    Object object;
    char *value;
    uintsize length;
    uintsize capacity;
};

static uintsize DEFAULT_CAPACITY = 16;

/* Static function declarations */
static void StringBuilder_AppendFormat(StringBuilder *sb, const String *format, va_list args);

/**************************************/
/* Extern functions                   */
/**************************************/

/* Allocators */
StringBuilder *StringBuilder_New(void)
{
    return StringBuilder_New_WithInitialStringValueAndCapacity(null, DEFAULT_CAPACITY);
}

StringBuilder *StringBuilder_New_WithCapacity(uintsize capacity)
{
    return StringBuilder_New_WithInitialStringValueAndCapacity(null, capacity);
}

StringBuilder *StringBuilder_New_WithInitialCStringValue(const char *value)
{
    const String str = String_WrapCString(value);

    return StringBuilder_New_WithInitialStringValueAndCapacity(&str, DEFAULT_CAPACITY);
}

StringBuilder *StringBuilder_New_WithInitialCStringValueAndCapacity(const char *value, uintsize capacity)
{
    const String str = String_WrapCString(value);

    return StringBuilder_New_WithInitialStringValueAndCapacity(&str, capacity);
}

StringBuilder *StringBuilder_New_WithInitialStringValue(const String *value)
{
    return StringBuilder_New_WithInitialStringValueAndCapacity(value, DEFAULT_CAPACITY);
}

StringBuilder *StringBuilder_New_WithInitialStringValueAndCapacity(const String *value, uintsize capacity)
{
    // Allocate a new string builder and set the destructor callback.
    StringBuilder *sb = Memory_Allocate(sizeof(StringBuilder));

    // Initialize the string builder with the given initial value and capacity.
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, value, capacity);

    Object_SetDeallocator(sb, Memory_Deallocate);

    return sb;
}

/* Constructors */
void StringBuilder_Constructor(StringBuilder *sb)
{
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, String_Empty(), DEFAULT_CAPACITY);
}

void StringBuilder_Constructor_WithCapacity(StringBuilder *sb, uintsize capacity)
{
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, String_Empty(), capacity);
}

void StringBuilder_Constructor_WithInitialCStringValue(StringBuilder *sb, const char *value)
{
    const String str = String_WrapCString(value);

    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, &str, DEFAULT_CAPACITY);
}

void StringBuilder_Constructor_WithInitialCStringValueAndCapacity(
    StringBuilder *sb,
    const char *value,
    uintsize capacity)
{
    const String str = String_WrapCString(value);

    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, &str, capacity);
}

void StringBuilder_Constructor_WithInitialStringValue(StringBuilder *sb, const String *value)
{
    StringBuilder_Constructor_WithInitialStringValueAndCapacity(sb, value, DEFAULT_CAPACITY);
}

void StringBuilder_Constructor_WithInitialStringValueAndCapacity(
    StringBuilder *sb,
    const String *value,
    uintsize capacity)
{
    Object_Constructor(sb, StringBuilder_Destructor);

    if (value == null) {
        value = String_Empty();
    }

    uintsize length = String_GetLength(value);

    if (capacity == 0) {
        capacity = DEFAULT_CAPACITY;
    }

    if (capacity < length) {
        capacity = length;
    }

    sb->length = length;
    sb->capacity = capacity;
    sb->value = Memory_Allocate(capacity + 1);

    Memory_Copy(String_GetCString(value), sb->value, length);
}

/* Destructor */
void StringBuilder_Destructor(void *sb)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    StringBuilder *stringBuilder = (StringBuilder*)sb;

    Memory_Deallocate(stringBuilder->value);
}

/* Methods */
uintsize StringBuilder_GetLength(const StringBuilder *sb)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    return sb->length;
}

uintsize StringBuilder_GetCapacity(const StringBuilder *sb)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    return sb->capacity;
}

void StringBuilder_SetCapacity(StringBuilder *sb, uintsize capacity)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    // TODO: If capacity is less than length, throw an ArgumentOutOfRangeException.
    assert(capacity >= sb->length);

    sb->capacity = capacity;
    sb->value = Memory_Reallocate(sb->value, capacity + 1);
}

String *StringBuilder_ToString(const StringBuilder *sb)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    // Ensure that the buffer has a terminating null character.
    sb->value[sb->length] = '\0';

    return String_New(sb->value);
}

char *StringBuilder_ToCString(const StringBuilder *sb)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    // Ensure that the buffer has a terminating null character.
    sb->value[sb->length] = '\0';

    return CString_Copy(sb->value);
}

void StringBuilder_Append(StringBuilder *sb, char value)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    if (sb->length == sb->capacity) {
        StringBuilder_SetCapacity(sb, sb->capacity * 2);
    }

    sb->value[sb->length++] = value;
}

void StringBuilder_AppendCString(StringBuilder *sb, const char *value)
{
    const String str = String_WrapCString(value);

    StringBuilder_AppendString(sb, &str);
}

void StringBuilder_AppendString(StringBuilder *sb, const String *value)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    if (value == null) {
        return;
    }

    uintsize length = String_GetLength(value);

    if (sb->length + length > sb->capacity) {
        // TODO: Use Math_Max when Math.h is implemented.
        // StringBuilder_SetCapacity(sb, Math_Max(sb->capacity * 2, sb->capacity + length));

        if (sb->capacity * 2 > sb->capacity + length) {
            StringBuilder_SetCapacity(sb, sb->capacity * 2);
        }
        else {
            StringBuilder_SetCapacity(sb, sb->capacity + length);
        }
    }

    Memory_CopyOffset(String_GetCString(value), 0, sb->value, sb->length, length);
    sb->length += length;
}

void StringBuilder_AppendFormatCString(StringBuilder *sb, const char *format, ...)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    // TODO: If format is null, throw an ArgumentNullException.
    assert(format != null);

    const String str = String_WrapCString(format);

    va_list args;
    va_start(args, format);
    StringBuilder_AppendFormat(sb, &str, args);
    va_end(args);
}

void StringBuilder_AppendFormatString(StringBuilder *sb, const String *format, ...)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    // TODO: If format is null, throw an ArgumentNullException.
    assert(format != null);

    va_list args;
    va_start(args, format);
    StringBuilder_AppendFormat(sb, format, args);
    va_end(args);
}

void StringBuilder_AppendLine(StringBuilder *sb)
{
    StringBuilder_Append(sb, '\n');
}

void StringBuilder_AppendLineCString(StringBuilder *sb, const char *value)
{
    const String str = String_WrapCString(value);

    StringBuilder_AppendLineString(sb, &str);
}

void StringBuilder_AppendLineString(StringBuilder *sb, const String *value)
{
    // TODO: If sb is null, throw an ArgumentNullException.
    assert(sb != null);

    StringBuilder_AppendString(sb, value);
    StringBuilder_Append(sb, '\n');
}

/**************************************/
/* Static functions                   */
/**************************************/

// TODO: Refactor this method!!
static void StringBuilder_AppendFormat(StringBuilder *sb, const String *format, va_list args)
{
    assert(sb != null);
    assert(format != null);

    const char *value = String_GetCString(format);
    uintsize length = String_GetLength(format);

    for (uintsize i = 0; i < length; i++) {
        if (value[i] != '%') {
            StringBuilder_Append(sb, value[i]);
        }
        else {
            if (i + 1 == length) {
                // Incomplete format specifier, the format string is invalid
                // TODO: throw an ArgumentException.
                assert(false);
            }

            switch (value[i + 1]) {
                case '%':
                    StringBuilder_Append(sb, value[i]);
                    break;
                case 's':
                    StringBuilder_AppendCString(sb, va_arg(args, char*));
                    break;
                case '#':
                    if (i + 2 == length) {
                        // Incomplete format specifier, the format string is invalid
                        // TODO: throw an ArgumentException.
                        assert(false);
                    }

                    switch (value[i + 2]) {
                        case 's':
                            StringBuilder_AppendString(sb, va_arg(args, String*));
                            break;
                        default:
                            // Unknown format specifier, the format string is invalid
                            // TODO: throw an ArgumentException.
                            assert(false);
                            break;
                    }

                    i++;
                    break;
                case 'c':
                    StringBuilder_Append(sb, va_arg(args, char));
                    break;
                default:
                    // Unknown format specifier, the format string is invalid
                    // TODO: throw an ArgumentException.
                    assert(false);
                    break;
            }

            i++;
        }
    }
}
