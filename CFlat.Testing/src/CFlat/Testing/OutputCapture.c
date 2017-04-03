/*
 * Copyright (C) 2017 Martijn van Dorp
 *
 * This file is part of CFlat.Testing.
 *
 * CFlat.Testing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFlat.Testing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CFlat/Testing/OutputCapture.h"

#include "CFlat.h"
#include "CFlat/Console.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/TextWriter.h"
#include "CFlat/IO/StringWriter.h"

public void OutputCapture_Destructor(OutputCapture *output)
{
    Validate_NotNull(output);

    release(output->CaptureOutput);
    release(output->CaptureError);

    release(output->StandardOutput);
    release(output->StandardError);

    release(output->Output);
    release(output->Error);
}

public void OutputCapture_Constructor(OutputCapture *output)
{
    Validate_NotNull(output);

    output->CaptureOutput = null;
    output->CaptureError = null;

    output->StandardOutput = null;
    output->StandardError = null;

    output->Output = null;
    output->Error = null;
}

public String *OutputCapture_GetStandardOutput(OutputCapture *output)
{
    Validate_NotNull(output);

    return output->Output;
}

public String *OutputCapture_GetStandardError(OutputCapture *output)
{
    Validate_NotNull(output);

    return output->Error;
}

public void OutputCapture_BeginCapture(OutputCapture *output)
{
    Validate_NotNull(output);

    output->StandardOutput = retain(Console_GetOut());
    output->StandardError = retain(Console_GetError());

    output->CaptureOutput = (StringWriter*)StringWriter_New();
    output->CaptureError = (StringWriter*)StringWriter_New();

    Console_SetOut((TextWriter*)output->CaptureOutput);
    Console_SetError((TextWriter*)output->CaptureError);
}

public void OutputCapture_EndCapture(OutputCapture *output)
{
    Validate_NotNull(output);

    Console_SetOut(output->StandardOutput);
    Console_SetError(output->StandardError);

    release(output->StandardOutput);
    release(output->StandardError);

    output->Output = StringWriter_DeleteAndToString(output->CaptureOutput);
    output->Error = StringWriter_DeleteAndToString(output->CaptureError);

    output->CaptureOutput = null;
    output->CaptureError = null;

    output->StandardOutput = null;
    output->StandardError = null;
}