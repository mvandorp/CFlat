/// @file Boolean.h
/// @author Martijn van Dorp
/// @date July 2015

#ifndef CFLAT_CORE_LANGUAGE_BOOLEAN_H
#define CFLAT_CORE_LANGUAGE_BOOLEAN_H

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && (_MSC_VER >= 1800))
    /* The compiler supports C99 or later, use the C99 _Bool type */
    #define CFLAT_BOOL _Bool
#elif defined(_MSC_VER)
    /* Visual Studio 2012 or earlier, use the int type */
    #define CFLAT_BOOL int
#else
    /* Otherwise use the char type */
    #define CFLAT_BOOL char
#endif

/// <summary>
/// Represents a boolean value, which can be either <see cref="true"/> or <see cref="false"/>.
/// </summary>
typedef CFLAT_BOOL bool;

/// <summary>
/// The <see cref="bool"/> value <c>true</c>.
/// </summary>
extern const bool true;

/// <summary>
/// The <see cref="bool"/> value <c>false</c>.
/// </summary>
extern const bool false;

#undef CFLAT_BOOL

#endif
