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

#include "CFlat/Language/Assert.h"

#include "CFlat.h"
#include "CFlat/Console.h"
#include "CFlat/Environment.h"
#include "CFlat/ExceptionType.h"

#include "CFlat/IO/TextWriter.h"

using namespace CFlat;

void __CFLAT_ASSERT_FAIL(const char *condition, const char *file, int line)
{
    assert(condition != nullptr);
    assert(file != nullptr);
    assert(line > 0);

    try {
        Console::GetError()->WriteFormat(
            "Assertion failed: {cstring}" Environment_NewLine_CString
            "   at {cstring}:{int}" Environment_NewLine_CString,
            condition,
            file,
            line);
    }
    catch (const Exception &ex) {
        (void)ex;
    }

    Environment::FailFast();
}
