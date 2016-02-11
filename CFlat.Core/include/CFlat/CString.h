/// @file CString.h
/// @author Martijn van Dorp
/// @date August 2015

#ifndef CFLAT_CORE_CSTRING_H
#define CFLAT_CORE_CSTRING_H

#include "CFlat.h"

/// <summary>
/// Gets the length of a null-terminated string.
///
/// The length does not include the terminating null character.
/// </summary>
/// <param name="str">A null-terminated string.</param>
/// <returns>The length of the string.</returns>
uintsize CString_Length(const char *str);

/// <summary>
/// Returns a pointer to a new null-terminated string that is a copy of the given string.
/// </summary>
/// <param name="str">A null-terminated string.</param>
/// <returns>
/// On success, returns the pointer to the copy of the string.
///
/// On failure, returns <see cref="null"/>.
/// </returns>
char *CString_Copy(const char *str);

#endif
