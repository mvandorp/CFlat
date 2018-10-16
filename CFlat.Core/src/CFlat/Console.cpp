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

#include "CFlat/Console.h"
#include "CFlat/Console.ConsoleStream.h"

#include "CFlat.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/FileAccess.h"
#include "CFlat/IO/Stream.h"
#include "CFlat/IO/StreamReader.h"
#include "CFlat/IO/StreamWriter.h"
#include "CFlat/IO/TextReader.h"
#include "CFlat/IO/TextWriter.h"

using namespace CFlat;

/* Private variables */
static shared_ptr<TextReader> _in = nullptr;
static shared_ptr<TextWriter> _out = nullptr;
static shared_ptr<TextWriter> _error = nullptr;

/**************************************/
/* Public function definitions        */
/**************************************/

shared_ptr<TextReader> Console::GetIn()
{
    if (_in == nullptr) {
        _in = shared_ptr<TextReader>(new StreamReader(Console::OpenStandardInput()));
    }

    return _in;
}

void Console::SetIn(shared_ptr<TextReader> reader)
{
    _in = reader;
}

shared_ptr<TextWriter> Console::GetOut()
{
    if (_out == nullptr) {
        _out = shared_ptr<TextWriter>(new StreamWriter(Console::OpenStandardOutput()));
    }

    return _out;
}

void Console::SetOut(shared_ptr<TextWriter> writer)
{
    _out = writer;
}

shared_ptr<TextWriter> Console::GetError()
{
    if (_error == nullptr) {
        _error = shared_ptr<TextWriter>(new StreamWriter(Console::OpenStandardError()));
    }

    return _error;
}

void Console::SetError(shared_ptr<TextWriter> writer)
{
    _error = writer;
}

unique_ptr<Stream> Console::OpenStandardInput()
{
    return unique_ptr<Stream>(new ConsoleStream(0, FileAccess::Read));
}

unique_ptr<Stream> Console::OpenStandardOutput()
{
    return unique_ptr<Stream>(new ConsoleStream(0, FileAccess::Write));
}

unique_ptr<Stream> Console::OpenStandardError()
{
    return unique_ptr<Stream>(new ConsoleStream(0, FileAccess::Write));
}

int Console::Read()
{
    return Console::GetIn()->Read();
}

String Console::ReadLine()
{
    return Console::GetIn()->ReadLine();
}

void Console::Write(char value)
{
    Console::GetOut()->Write(value);
}

void Console::Write(const char *value)
{
    Console::GetOut()->Write(value);
}

void Console::Write(const String &value)
{
    Console::GetOut()->Write(value);
}

void Console::WriteFormat(const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    Console::WriteFormatVA(format, args);

    VarArgs_End(args);
}

void Console::WriteFormatVA(const char *format, VarArgsList args)
{
    Console::GetOut()->WriteFormatVA(format, args);
}

void Console::WriteFormat(String format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    Console::WriteFormatVA(format, args);

    VarArgs_End(args);
}

void Console::WriteFormatVA(const String &format, VarArgsList args)
{
    Console::GetOut()->WriteFormatVA(format, args);
}

void Console::WriteLine()
{
    Console::GetOut()->WriteLine();
}

void Console::WriteLine(const char *value)
{
    Console::GetOut()->WriteLine(value);
}

void Console::WriteLine(const String &value)
{
    Console::GetOut()->WriteLine(value);
}

void Console::WriteLineFormat(const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    Console::WriteLineFormatVA(format, args);

    VarArgs_End(args);
}

void Console::WriteLineFormatVA(const char *format, VarArgsList args)
{
    Console::GetOut()->WriteLineFormatVA(format, args);
}

void Console::WriteLineFormat(String format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    Console::WriteLineFormatVA(format, args);

    VarArgs_End(args);
}

void Console::WriteLineFormatVA(const String &format, VarArgsList args)
{
    Console::GetOut()->WriteLineFormatVA(format, args);
}
