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

#include "CFlat/IO/TextWriter.h"
#include "CFlat/IO/TextWriter.NullTextWriter.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/String.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"

#include <utility>

using namespace CFlat;

/* Macros */
#define WriteWithStringBuilder(bufferName, write)                                   \
{                                                                                   \
    StringBuilder bufferName;                                                       \
    write;                                                                          \
                                                                                    \
    uintsize length = bufferName.GetLength();                                       \
                                                                                    \
    this->Write(StringBuilder::ToCString(std::move(bufferName)).Get(), 0, length);  \
}

/* Private constants */
/// <summary>
/// The default buffer capacity to use when copying a stream.
/// </summary>
static const uintsize DefaultBufferSize = 81920;

/**************************************/
/* Public function definitions        */
/**************************************/

TextWriter::TextWriter()
{
}

TextWriter::~TextWriter()
{
}

unique_ptr<TextWriter, NoOpDeleter<TextWriter>> TextWriter::Null()
{
    static NullWriter instance = NullWriter();

    return unique_ptr<TextWriter, NoOpDeleter<TextWriter>>(&instance);
}

void TextWriter::Flush()
{
}

template <>
void TextWriter::Write<char>(char value)
{
    this->Write(&value, 0, 1);
}

template <>
void TextWriter::Write<const char*>(const char *value)
{
    if (value == nullptr) return;

    this->Write(value, 0, CString::Length(value));
}

template <>
void TextWriter::Write<const String&>(const String &value)
{
    this->Write(value.GetCString(), 0, value.GetLength());
}

/*
template <typename T>
void TextWriter::Write(T value)
{
    StringBuilder sb = StringBuilder();
    sb.Append(value);

    uintsize length = sb.GetLength();

    this->Write(StringBuilder::ToCString(std::move(sb)).Get(), 0, length);
}
*/

void TextWriter::WriteFormat(const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    this->WriteFormatVA(format, args);

    VarArgs_End(args);
}

void TextWriter::WriteFormatVA(const char *format, VarArgsList args)
{
    Validate_NotNull(format);

    WriteWithStringBuilder(sb, sb.AppendFormatVA(format, args));
}

void TextWriter::WriteFormat(String format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    this->WriteFormatVA(format, args);

    VarArgs_End(args);
}

void TextWriter::WriteFormatVA(const String &format, VarArgsList args)
{
    WriteWithStringBuilder(sb, sb.AppendFormatVA(format, args));
}

void TextWriter::WriteLine()
{
    this->Write(Environment::NewLine);
}

template <>
void TextWriter::WriteLine<char>(char value)
{
    this->Write(value);
    this->WriteLine();
}

template <>
void TextWriter::WriteLine<const char*>(const char *value)
{
    this->Write(value);
    this->WriteLine();
}

template <>
void TextWriter::WriteLine<const String&>(const String &value)
{
    this->Write(value);
    this->WriteLine();
}

/*
template <typename T>
void TextWriter::WriteLine(T value)
{
    StringBuilder sb = StringBuilder();
    sb.Append(value);
    sb.Append(Environment::NewLine);

    uintsize length = sb.GetLength();

    this->Write(StringBuilder::ToCString(std::move(sb)).Get(), 0, length);
}
*/

void TextWriter::WriteLineFormat(const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    this->WriteLineFormatVA(format, args);

    VarArgs_End(args);
}

void TextWriter::WriteLineFormatVA(const char *format, VarArgsList args)
{
    Validate_NotNull(format);

    WriteWithStringBuilder(sb, {
        sb.AppendFormatVA(format, args);
        sb.Append(Environment::NewLine);
    });
}

void TextWriter::WriteLineFormat(String format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    this->WriteLineFormatVA(format, args);

    VarArgs_End(args);
}

void TextWriter::WriteLineFormatVA(const String &format, VarArgsList args)
{
    WriteWithStringBuilder(sb, {
        sb.AppendFormatVA(format, args);
        sb.Append(Environment::NewLine);
    });
}
