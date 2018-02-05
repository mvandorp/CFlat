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

#include "CFlat/IO/StringWriter.h"

#include "CFlat.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"

#include <utility>

using namespace CFlat;

/* Private constants */
static const uintsize DefaultCapacity = 4096;

/**************************************/
/* Public function definitions        */
/**************************************/

StringWriter::StringWriter() : _writer(DefaultCapacity)
{
}

StringWriter::StringWriter(const StringBuilder &sb) : _writer(sb)
{
}

StringWriter::StringWriter(StringBuilder &&sb) : _writer(std::move(sb))
{
}

String StringWriter::ToString() const
{
    return _writer.ToString();
}

String StringWriter::ToString(const StringWriter &writer)
{
    return writer.ToString();
}

String StringWriter::ToString(StringWriter &&writer)
{
    return StringBuilder::ToString(std::move(writer._writer));
}

void StringWriter::Write(
    const char *buffer,
    uintsize offset,
    uintsize count)
{
    Validate_NotNull(buffer);

    _writer.Append(buffer, offset, count);
}
