/// @file String.h
/// @author Martijn van Dorp
/// @date August 2015

#ifndef CFLAT_CORE_STRING_H
#define CFLAT_CORE_STRING_H

#include "CFlat.h"

/// <summary>
/// Represents text as a string of characters.
/// </summary>
typedef struct String String;

/// <summary>
/// Allocates and initializes a new <see cref="String"/> to the value represented by the given null-terminated string.
///
/// The lifetime of the string should be managed with Object_Aquire(), Object_Release() and Object_Delete().
/// </summary>
/// <param name="value">Pointer to a null-terminated string.</param>
/// <returns>Pointer to the newly allocated string.</returns>
String *String_New(const char *value);

/// <summary>
/// Initializes a given <see cref="String"/> to the value represented by the given null-terminated string.
/// </summary>
/// <param name="str">Pointer to an uninitialized <see cref="String"/>.</param>
/// <param name="value">Pointer to a null-terminated string.</param>
void String_Constructor(String *str, const char *value);

/// <summary>
/// Destroys a given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
void String_Destructor(String *str);

/// <summary>
/// Returns the length of a given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>The length of the string.</returns>
uintsize String_Length(const String *str);

/// <summary>
/// Returns a pointer to a null-terminated string representing the value of the given <see cref="String"/>.
/// </summary>
/// <param name="str">Pointer to a <see cref="String"/>.</param>
/// <returns>A pointer to a null-terminated string representing the value of the string.</returns>
const char *String_GetCString(const String *str);

#endif
