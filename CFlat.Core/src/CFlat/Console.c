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

#include "CFlat.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/FileAccess.h"
#include "CFlat/IO/Stream.h"
#include "CFlat/IO/StreamReader.h"
#include "CFlat/IO/StreamWriter.h"
#include "CFlat/IO/TextReader.h"
#include "CFlat/IO/TextWriter.h"

#include <stdio.h>

/* Private variables */
private TextReader *In = null;
private TextWriter *Out = null;
private TextWriter *Error = null;

/**************************************/
/* Internal functions                 */
/**************************************/

internal Stream *ConsoleStream_New(FILE *file, FileAccess fileAccess);

/**************************************/
/* Public function definitions        */
/**************************************/

public TextReader *Console_GetIn(void)
{
    if (In == null) {
        Stream *stdIn = Console_OpenStandardInput();

        try {
            In = StreamReader_New(stdIn);
        }
        finally {
            release(stdIn);
        }
        endtry;
    }

    return In;
}

public void Console_SetIn(TextReader *reader)
{
    if (In != reader) {
        release(In);

        In = retain(reader);
    }
}

public TextWriter *Console_GetOut(void)
{
    if (Out == null) {
        Stream *stdOut = Console_OpenStandardOutput();

        try {
            Out = StreamWriter_New(stdOut);
        }
        finally {
            release(stdOut);
        }
        endtry;
    }

    return Out;
}

public void Console_SetOut(TextWriter *writer)
{
    if (Out != writer) {
        release(Out);

        Out = retain(writer);
    }
}

public TextWriter *Console_GetError(void)
{
    if (Error == null) {
        Stream *stdError = Console_OpenStandardError();

        try {
            Error = StreamWriter_New(stdError);
        }
        finally {
            release(stdError);
        }
        endtry;
    }

    return Error;
}

public void Console_SetError(TextWriter *writer)
{
    if (Error != writer) {
        release(Error);

        Error = retain(writer);
    }
}

public Stream *Console_OpenStandardInput(void)
{
    return ConsoleStream_New(stdin, FileAccess_Read);
}

public Stream *Console_OpenStandardOutput(void)
{
    return ConsoleStream_New(stdout, FileAccess_Write);
}

public Stream *Console_OpenStandardError(void)
{
    return ConsoleStream_New(stderr, FileAccess_Write);
}

public int Console_Read(void)
{
    return TextReader_Read(Console_GetIn());
}

public String *Console_ReadLine(void)
{
    return TextReader_ReadLine(Console_GetIn());
}

public void Console_Write(char value)
{
    TextWriter_Write(Console_GetOut(), value);
}

public void Console_Write_CString(const char *value)
{
    TextWriter_Write_CString(Console_GetOut(), value);
}

public void Console_Write_String(const String *value)
{
    TextWriter_Write_String(Console_GetOut(), value);
}

public void Console_WriteFormat_CString(const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    Console_WriteFormat_CStringV(format, args);

    VarArgs_End(args);
}

public void Console_WriteFormat_CStringV(const char *format, VarArgsList args)
{
    TextWriter_WriteFormat_CStringV(Console_GetOut(), format, args);
}

public void Console_WriteFormat_String(const String *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    Console_WriteFormat_StringV(format, args);

    VarArgs_End(args);
}

public void Console_WriteFormat_StringV(const String *format, VarArgsList args)
{
    TextWriter_WriteFormat_StringV(Console_GetOut(), format, args);
}

public void Console_WriteLine(void)
{
    TextWriter_WriteLine(Console_GetOut());
}

public void Console_WriteLine_CString(const char *value)
{
    TextWriter_WriteLine_CString(Console_GetOut(), value);
}

public void Console_WriteLine_String(const String *value)
{
    TextWriter_WriteLine_String(Console_GetOut(), value);
}

public void Console_WriteLineFormat_CString(const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    Console_WriteLineFormat_CStringV(format, args);

    VarArgs_End(args);
}

public void Console_WriteLineFormat_CStringV(const char *format, VarArgsList args)
{
    TextWriter_WriteLineFormat_CStringV(Console_GetOut(), format, args);
}

public void Console_WriteLineFormat_String(const String *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    Console_WriteLineFormat_StringV(format, args);

    VarArgs_End(args);
}

public void Console_WriteLineFormat_StringV(const String *format, VarArgsList args)
{
    TextWriter_WriteLineFormat_StringV(Console_GetOut(), format, args);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

internal void Console_StaticDestructor(void)
{
    release(In);
    release(Out);
    release(Error);
}
