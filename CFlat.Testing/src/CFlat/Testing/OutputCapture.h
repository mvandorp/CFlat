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

#ifndef CFLAT_TESTING_TESTOUTPUT_H
#define CFLAT_TESTING_TESTOUTPUT_H

/* Forward declarations */
struct String;
struct StringWriter;
struct TextWriter;

/* Types */
typedef struct OutputCapture  {
    struct StringWriter *CaptureOutput;
    struct StringWriter *CaptureError;

    struct TextWriter *StandardOutput;
    struct TextWriter *StandardError;

    struct String *Output;
    struct String *Error;
} OutputCapture;

/* Functions */
void OutputCapture_Constructor(OutputCapture *output);
void OutputCapture_Destructor(OutputCapture *output);

void OutputCapture_BeginCapture(OutputCapture *output);
void OutputCapture_EndCapture(OutputCapture *output);

struct String *OutputCapture_GetStandardOutput(OutputCapture *output);
struct String *OutputCapture_GetStandardError(OutputCapture *output);

#endif
