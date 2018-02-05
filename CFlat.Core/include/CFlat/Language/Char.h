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

//! @file Char.h

#ifndef CFLAT_CORE_LANGUAGE_CHAR_H
#define CFLAT_CORE_LANGUAGE_CHAR_H

#include "CFlat/String.h"

namespace CFlat {
    class Char {
    public:
        /* Static class */
        Char() = delete;

        /* Constants */
        /// <summary>
        /// Represents the smallest possible value of <see cref="char"/>.
        /// </summary>
        static const char MinValue;

        /// <summary>
        /// Represents the largest possible value of <see cref="char"/>.
        /// </summary>
        static const char MaxValue;

        /* Functions */
        /// <summary>
        /// Determines whether a character is catagorized as a binary digit.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a binary digit; otherwise, <see cref="false"/>.</returns>
        static bool IsBinaryDigit(int c);

        /// <summary>
        /// Determines whether a character is catagorized as a control character.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a control character; otherwise, <see cref="false"/>.</returns>
        static bool IsControl(int c);

        /// <summary>
        /// Determines whether a character is catagorized as a decimal digit.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a decimal digit; otherwise, <see cref="false"/>.</returns>
        static bool IsDigit(int c);

        /// <summary>
        /// Determines whether a character is catagorized as a graphical character.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a graphical character; otherwise, <see cref="false"/>.</returns>
        static bool IsGraphic(int c);

        /// <summary>
        /// Determines whether a character is catagorized as a hexadecimal digit.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a hexadecimal digit; otherwise, <see cref="false"/>.</returns>
        static bool IsHexadecimalDigit(int c);

        /// <summary>
        /// Determines whether a character is catagorized as a letter.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a letter; otherwise, <see cref="false"/>.</returns>
        static bool IsLetter(int c);

        /// <summary>
        /// Determines whether a character is catagorized as a letter or decimal digit.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a letter or decimal digit; otherwise, <see cref="false"/>.</returns>
        static bool IsLetterOrDigit(int c);

        /// <summary>
        /// Determines whether a character is catagorized as a lowercase letter.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a lowercase letter; otherwise, <see cref="false"/>.</returns>
        static bool IsLower(int c);

        /// <summary>
        /// Determines whether a character is catagorized as a printable character.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a printable character; otherwise, <see cref="false"/>.</returns>
        static bool IsPrintable(int c);

        /// <summary>
        /// Determines whether a character is catagorized as punctation.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is punctation; otherwise, <see cref="false"/>.</returns>
        static bool IsPunctation(int c);

        /// <summary>
        /// Determines whether a character is catagorized as a separator character.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is a separator character; otherwise, <see cref="false"/>.</returns>
        static bool IsSeparator(int c);

        /// <summary>
        /// Determines whether a character is catagorized as an uppercase letter.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is an uppercase letter; otherwise, <see cref="false"/>.</returns>
        static bool IsUpper(int c);

        /// <summary>
        /// Determines whether a character is catagorized as white space.
        /// </summary>
        /// <param name="c">The character to check.</param>
        /// <returns><see cref="true"/> if the character is white space; otherwise, <see cref="false"/>.</returns>
        static bool IsWhiteSpace(int c);

        /// <summary>
        /// Converts a character to its lowercase equivalent.
        /// </summary>
        /// <param name="c">The character to convert.</param>
        /// <returns>
        ///     The lowercase equivalent of <paramref name="c"/> if <paramref name="c"/> is an uppercase letter;
        ///     otherwise, returns <paramref name="c"/>.
        /// </returns>
        static int ToLower(int c);

        /// <summary>
        /// Converts a character to its upercase equivalent.
        /// </summary>
        /// <param name="c">The character to convert.</param>
        /// <returns>
        ///     The uppercase equivalent of <paramref name="c"/> if <paramref name="c"/> is a lowercase letter;
        ///     otherwise, returns <paramref name="c"/>.
        /// </returns>
        static int ToUpper(int c);

        /// <summary>
        /// Converts a character to a string representation.
        /// </summary>
        /// <param name="c">The value to be converted to a string.</param>
        /// <returns>The string representation of the character.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        static String ToString(char c);
    };
}

#endif
