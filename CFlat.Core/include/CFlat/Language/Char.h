/*
 * Copyright (C) 2015 Martijn van Dorp
 *
 * This file is part of CFlat.Core.
 *
 * CFlat.Core is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFlat.Core is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file Char.h
 */

#ifndef CFLAT_CORE_LANGUAGE_CHAR_H
#define CFLAT_CORE_LANGUAGE_CHAR_H

#include "CFlat/Language/Bool.h"

/* Macros */
/// <summary>
/// Represents the smallest possible value of <see cref="char"/>.
/// </summary>
#define char_MinValue ((char)CHAR_MIN)

/// <summary>
/// Represents the largest possible value of <see cref="char"/>.
/// </summary>
#define char_MaxValue ((char)CHAR_MAX)

/* Functions */
/// <summary>
/// Returns whether the given character is catagorized as a binary digit.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a binary digit; otherwise <see cref="false"/>.</returns>
bool char_IsBinaryDigit(int c);

/// <summary>
/// Returns whether the given character is catagorized as a control character.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a control character; otherwise <see cref="false"/>.</returns>
bool char_IsControl(int c);

/// <summary>
/// Returns whether the given character is catagorized as a decimal digit.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a decimal digit; otherwise <see cref="false"/>.</returns>
bool char_IsDigit(int c);

/// <summary>
/// Returns whether the given character is catagorized as a graphical character.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a graphical character; otherwise <see cref="false"/>.</returns>
bool char_IsGraphic(int c);

/// <summary>
/// Returns whether the given character is catagorized as a hexadecimal digit.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a hexadecimal digit; otherwise <see cref="false"/>.</returns>
bool char_IsHexadecimalDigit(int c);

/// <summary>
/// Returns whether the given character is catagorized as a letter.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a letter; otherwise <see cref="false"/>.</returns>
bool char_IsLetter(int c);

/// <summary>
/// Returns whether the given character is catagorized as a letter or decimal digit.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a letter or decimal digit; otherwise <see cref="false"/>.</returns>
bool char_IsLetterOrDigit(int c);

/// <summary>
/// Returns whether the given character is catagorized as a lowercase letter.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a lowercase letter; otherwise <see cref="false"/>.</returns>
bool char_IsLower(int c);

/// <summary>
/// Returns whether the given character is catagorized as a printable character.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a printable character; otherwise <see cref="false"/>.</returns>
bool char_IsPrintable(int c);

/// <summary>
/// Returns whether the given character is catagorized as punctation.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is punctation; otherwise <see cref="false"/>.</returns>
bool char_IsPunctation(int c);

/// <summary>
/// Returns whether the given character is catagorized as a separator character.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is a separator character; otherwise <see cref="false"/>.</returns>
bool char_IsSeparator(int c);

/// <summary>
/// Returns whether the given character is catagorized as an uppercase letter.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is an uppercase letter; otherwise <see cref="false"/>.</returns>
bool char_IsUpper(int c);

/// <summary>
/// Returns whether the given character is catagorized as white space.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns><see cref="true"/> if the character is white space; otherwise <see cref="false"/>.</returns>
bool char_IsWhiteSpace(int c);

/// <summary>
/// Converts the given character to its lowercase equivalent.
/// </summary>
/// <param name="c">The character to convert.</param>
/// <returns>
/// The lowercase equivalent of <c>c</c> if <c>c</c> is an uppercase letter; otherwise returns <c>c</c>.
/// </returns>
int char_ToLower(int c);

/// <summary>
/// Converts the given character to its upercase equivalent.
/// </summary>
/// <param name="c">The character to convert.</param>
/// <returns>
/// The uppercase equivalent of <c>c</c> if <c>c</c> is a lowercase letter; otherwise returns <c>c</c>.
/// </returns>
int char_ToUpper(int c);

#endif
