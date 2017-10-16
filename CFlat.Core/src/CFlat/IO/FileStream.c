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

#include "CFlat/IO/FileStream.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Object.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/FileAccess.h"
#include "CFlat/IO/FileMode.h"
#include "CFlat/IO/Stream.h"

#include <errno.h>
#include <stdio.h>

#if defined(__unix__) || (defined (__APPLE__) && defined (__MACH__))
 #include <unistd.h>
#endif

#if defined(_LARGEFILE_SOURCE) || \
    defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 500 || \
    defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    // POSIX.1-2001

    #define POSIX_fileno
    #define POSIX_ftruncate
#elif defined(_MSC_VER) && _MSC_VER >= 1400
    // MSVC++ 8.0 or newer
    #include <io.h>

    #define fileno      _fileno
    #define fseeko      _fseeki64
    #define ftello      _ftelli64
    #define ftruncate   _chsize_s

    #define POSIX_fileno
    #define POSIX_ftruncate
#elif defined(_MSC_VER)
    // MSVC++
    #include <io.h>

    #define fileno      _fileno
    #define fseeko      fseek
    #define ftruncate   _chsize_s
    #define ftello      ftell

    #define POSIX_fileno
    #define POSIX_ftruncate
#else
    #define ftello ftell
    #define fseeko fseek
#endif

/* Types */
struct FileStream {
    Stream Base;
    FILE *File;
    FileAccess Access;
    FileMode Mode;
};

/**************************************/
/* Private functions                  */
/**************************************/

private void FileStream_Constructor(FileStream *stream, const char *path, FileMode mode, FileAccess fileAccess);
private void FileStream_Destructor(FileStream *stream);

private override bool FileStream_CanRead(const FileStream *stream);
private override bool FileStream_CanSeek(const FileStream *stream);
private override bool FileStream_CanWrite(const FileStream *stream);

private override intfsize FileStream_GetLength(const FileStream *stream);
private override void FileStream_SetLength(FileStream *stream, intfsize length);

private override intfsize FileStream_GetPosition(const FileStream *stream);
private override void FileStream_SetPosition(FileStream *stream, intfsize position);

private override void FileStream_Flush(FileStream *stream);
private override uintsize FileStream_Read(FileStream *stream, byte *buffer, uintsize offset, uintsize count);
private override intfsize FileStream_Seek(FileStream *stream, intfsize offset, SeekOrigin origin);
private override void FileStream_Write(FileStream *stream, const byte *buffer, uintsize offset, uintsize count);

private void ValidateReadSupported(const FileStream *stream);
private void ValidateSeekSupported(const FileStream *stream);
private void ValidateWriteSupported(const FileStream *stream);

private FILE *FileOpen(const char *path, FileMode mode, FileAccess fileAccess);
private void FileSeek(FILE *file, intfsize offset, SeekOrigin origin);
private intfsize FileTell(FILE *file);
private void FileTruncate(FILE *file, intfsize length);

private void ValidateFileDoesNotExist(const char *path);
private void ValidateModeAccessCombination(FileMode mode, FileAccess fileAccess);
private const char *GetCFileModeString(FileMode mode, FileAccess fileAccess);
private int GetCSeekOrigin(SeekOrigin origin);
private void GenerateFileOpenException(int errorCode, FileMode mode);

/* Private constants */
/// <summary>
/// The virtual method table for the <see cref="FileStream"/> class.
/// </summary>
private const StreamVTable VTable = StreamVTable_Initializer(
    (DestructorFunc)FileStream_Destructor,
    (Stream_CanReadFunc)FileStream_CanRead,
    (Stream_CanSeekFunc)FileStream_CanSeek,
    (Stream_CanWriteFunc)FileStream_CanWrite,
    (Stream_GetLengthFunc)FileStream_GetLength,
    (Stream_SetLengthFunc)FileStream_SetLength,
    (Stream_GetPositionFunc)FileStream_GetPosition,
    (Stream_SetPositionFunc)FileStream_SetPosition,
    (Stream_FlushFunc)FileStream_Flush,
    (Stream_ReadFunc)FileStream_Read,
    (Stream_SeekFunc)FileStream_Seek,
    (Stream_WriteFunc)FileStream_Write);

/**************************************/
/* Public function definitions        */
/**************************************/

public Stream *FileStream_New(const String *path, FileMode mode)
{
    return FileStream_New_CString(String_GetCString(path), mode);
}

public Stream *FileStream_New_CString(const char *path, FileMode mode)
{
    return FileStream_New_WithAccess_CString(
        path,
        mode,
        mode == FileMode_Append ? FileAccess_Write : FileAccess_ReadWrite);
}

public Stream *FileStream_New_WithAccess(const String *path, FileMode mode, FileAccess fileAccess)
{
    return FileStream_New_WithAccess_CString(String_GetCString(path), mode, fileAccess);
}

public Stream *FileStream_New_WithAccess_CString(const char *path, FileMode mode, FileAccess fileAccess)
{
    FileStream *stream = Memory_Allocate(sizeof(FileStream));

    try {
        FileStream_Constructor(stream, path, mode, fileAccess);

        Object_SetDeallocator(stream, Memory_Deallocate);
    }
    catch (Exception) {
        Memory_Deallocate(stream);
        throw;
    }
    endtry;

    return (Stream*)stream;
}

/**************************************/
/* Private function definitions       */
/**************************************/

private void FileStream_Constructor(FileStream *stream, const char *path, FileMode mode, FileAccess fileAccess)
{
    Validate_NotNull(path);
    FileMode_Validate(mode);
    FileAccess_Validate(fileAccess);

    Stream_Constructor((Stream*)stream, &VTable);

    stream->File = FileOpen(path, mode, fileAccess);
    stream->Access = fileAccess;
    stream->Mode = mode;
}

private void FileStream_Destructor(FileStream *stream)
{
    if (FileStream_CanWrite(stream)) {
        try {
            FileStream_Flush(stream);
        }
        catch (Exception);
        endtry;
    }

    fclose(stream->File);
}

private override bool FileStream_CanRead(const FileStream *stream)
{
    Validate_NotNull(stream);

    return (stream->Access & FileAccess_Read) == FileAccess_Read;
}

private override bool FileStream_CanSeek(const FileStream *stream)
{
    Validate_NotNull(stream);

    return stream->Mode != FileMode_Append;
}

private override bool FileStream_CanWrite(const FileStream *stream)
{
    Validate_NotNull(stream);

    return (stream->Access & FileAccess_Write) == FileAccess_Write;
}

private override intfsize FileStream_GetLength(const FileStream *stream)
{
    Validate_NotNull(stream);

    if (stream->Mode != FileMode_Append) {
        ValidateSeekSupported(stream);
    }

    intfsize length = 0;

    try {
        intfsize cur = FileTell(stream->File);

        FileSeek(stream->File, 0, SeekOrigin_End);

        length = FileTell(stream->File);

        FileSeek(stream->File, cur, SeekOrigin_Begin);
    }
    catch (Exception) {
        throw_new(IOException, "Failed to get the length of the file.");
    }
    endtry;

    return length;
}

private override void FileStream_SetLength(FileStream *stream, intfsize length)
{
    ValidateSeekSupported(stream);
    Validate_NotNegative(length);

    FileTruncate(stream->File, length);
}

private override intfsize FileStream_GetPosition(const FileStream *stream)
{
    ValidateSeekSupported(stream);

    return FileTell(stream->File);
}

private override void FileStream_SetPosition(FileStream *stream, intfsize position)
{
    FileStream_Seek(stream, position, SeekOrigin_Begin);
}

private override void FileStream_Flush(FileStream *stream)
{
    Validate_NotNull(stream);

    if (FileStream_CanWrite(stream)) {
        fflush(stream->File);

        if (ferror(stream->File)) {
            throw_new(IOException, "Failed to flush the stream.");
        }
    }
}

private override uintsize FileStream_Read(FileStream *stream, byte *buffer, uintsize offset, uintsize count)
{
    ValidateReadSupported(stream);
    Validate_NotNull(buffer);

    uintsize bytesRead = fread(&buffer[offset], 1, count, stream->File);

    if (ferror(stream->File)) {
        throw_new(IOException, "Failed to read from the stream.");
    }

    return bytesRead;
}

private override intfsize FileStream_Seek(FileStream *stream, intfsize offset, SeekOrigin origin)
{
    ValidateSeekSupported(stream);

    FileSeek(stream->File, offset, origin);

    return FileTell(stream->File);
}

private override void FileStream_Write(FileStream *stream, const byte *buffer, uintsize offset, uintsize count)
{
    ValidateWriteSupported(stream);
    Validate_NotNull(buffer);

    if (count == 0) return;

    fwrite(&buffer[offset], 1, count, stream->File);

    if (ferror(stream->File)) {
        throw_new(IOException, "Failed to write to the stream.");
    }
}

private void ValidateReadSupported(const FileStream *stream)
{
    if (!FileStream_CanRead(stream)) {
        throw_new(NotSupportedException, "The stream does not support reading.");
    }
}

private void ValidateSeekSupported(const FileStream *stream)
{
    if (!FileStream_CanSeek(stream)) {
        throw_new(NotSupportedException, "The stream does not support seeking.");
    }
}

private void ValidateWriteSupported(const FileStream *stream)
{
    if (!FileStream_CanWrite(stream)) {
        throw_new(NotSupportedException, "The stream does not support writing.");
    }
}

private FILE *FileOpen(const char *path, FileMode mode, FileAccess fileAccess)
{
    assert(path != null);
    assert(FileMode_IsValid(mode));
    assert(FileAccess_IsValid(fileAccess));

    ValidateModeAccessCombination(mode, fileAccess);

    if (mode == FileMode_CreateNew) {
        ValidateFileDoesNotExist(path);
    }

    const char *fileMode = GetCFileModeString(mode, fileAccess);

    errno = 0;
    FILE *file = fopen(path, fileMode);

    if (file == null) {
        GenerateFileOpenException(errno, mode);
    }

    return file;
}

private void FileSeek(FILE *file, intfsize offset, SeekOrigin origin)
{
    assert(file != null);
    assert(SeekOrigin_IsValid(origin));

    fseeko(file, offset, GetCSeekOrigin(origin));

    if (ferror(file)) {
        throw_new(IOException, "Failed to seek to the given offset.");
    }
}

private intfsize FileTell(FILE *file)
{
    assert(file != null);

    intfsize pos = ftello(file);

    assert(pos >= 0);

    if (ferror(file)) {
        throw_new(IOException, "Failed to get the current position within the stream.");
    }

    return pos;
}

private void FileTruncate(FILE *file, intfsize length)
{
    assert(file != null);
    assert(length >= 0);

#if defined(POSIX_ftruncate) && defined(POSIX_fileno)
    ftruncate(fileno(file), length);

    if (ferror(file)) {
        throw_new(IOException, "Failed to truncate the stream.");
    }
#else
    throw_new(NotSupportedException, null);
#endif
}

private void ValidateFileDoesNotExist(const char *path)
{
    FILE *file = fopen(path, "r");

    if (file != null) {
        fclose(file);

        throw_new(IOException, "Failed to create new file: File already exists.");
    }
}

private void ValidateModeAccessCombination(FileMode mode, FileAccess fileAccess)
{
    assert(FileMode_IsValid(mode));
    assert(FileAccess_IsValid(fileAccess));

    switch (mode) {
        case FileMode_Append:
            if (fileAccess != FileAccess_Write) {
                throw_new(ArgumentException, "Append mode can only be used in combination with write-only access.");
            }
            break;

        case FileMode_Open:
        case FileMode_OpenOrCreate:
            if (fileAccess == FileAccess_Write) {
                throw_new(
                    ArgumentException,
                    "The specified file mode cannot be used in combination with write-only access.");
            }
            break;

        case FileMode_Create:
        case FileMode_CreateNew:
        case FileMode_Truncate:
            if (fileAccess == FileAccess_Read) {
                throw_new(
                    ArgumentException,
                    "The specified file mode cannot be used in combination with read-only access.");
            }
            break;

        default:
            assert(false);
            break;
    }
}

private const char *GetCFileModeString(FileMode mode, FileAccess fileAccess)
{
    assert(FileMode_IsValid(mode));
    assert(FileAccess_IsValid(fileAccess));

    switch (mode) {
        case FileMode_Append:
            return "ab";

        case FileMode_Open:
        case FileMode_OpenOrCreate:
            if ((fileAccess & FileAccess_Write) == FileAccess_Write) {
                return "r+b";
            }
            else {
                return "rb";
            }

        case FileMode_Create:
        case FileMode_CreateNew:
        case FileMode_Truncate:
            if ((fileAccess & FileAccess_Read) == FileAccess_Read) {
                return "w+b";
            }
            else {
                return "wb";
            }

        default:
            assert(false);
            return null;
    }
}

private int GetCSeekOrigin(SeekOrigin origin)
{
    assert(SeekOrigin_IsValid(origin));

    switch (origin) {
        case SeekOrigin_Begin:
            return SEEK_SET;

        case SeekOrigin_Current:
            return SEEK_CUR;

        case SeekOrigin_End:
            return SEEK_END;

        default:
            assert(false);
            return 0;
    }
}

private void GenerateFileOpenException(int errorCode, FileMode mode)
{
    switch (mode) {
        case FileMode_Create:
        case FileMode_CreateNew:
#ifdef EACCES
            if (errorCode == EACCES) throw_new(IOException, "Failed to create file: Permission denied.");
#endif
#ifdef ENOENT
            if (errorCode == ENOENT) throw_new(IOException, "Failed to create file: No such file or directory.");
#endif
#ifdef EMFILE
            if (errorCode == EMFILE) throw_new(IOException, "Failed to create file: Too many open files.");
#endif
#ifdef ENFILE
            if (errorCode == ENFILE) throw_new(IOException, "Failed to create file: Too many open files.");
#endif
            throw_new(IOException, "Failed to create file.");
            break;

        case FileMode_Append:
        case FileMode_Open:
        case FileMode_OpenOrCreate:
        case FileMode_Truncate:
#ifdef EACCES
            if (errorCode == EACCES) throw_new(IOException, "Failed to open file: Permission denied.");
#endif
#ifdef ENOENT
            if (errorCode == ENOENT) throw_new(IOException, "Failed to open file: No such file or directory.");
#endif
#ifdef EMFILE
            if (errorCode == EMFILE) throw_new(IOException, "Failed to open file: Too many open files.");
#endif
#ifdef ENFILE
            if (errorCode == ENFILE) throw_new(IOException, "Failed to open file: Too many open files.");
#endif
            throw_new(IOException, "Failed to open file.");
            break;

        default:
            assert(false);
            break;
    }
}
