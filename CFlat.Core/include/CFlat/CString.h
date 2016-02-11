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
/// Allocates a new null-terminated string that is a duplicated of the given string, and returns a pointer to the new
/// copy.
/// </summary>
/// <param name="str">A null-terminated string.</param>
/// <returns>
/// On success, returns the pointer to the copy of the string.
/// 
/// On failure, returns <see cref="null"/>.
char *CString_Duplicate(const char *str);

#endif
