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
#include "CFlat/String.h"
#include "CFlat/Validate.h"
#include "CFlat/IO/FileAccess.h"
#include "CFlat/IO/FileMode.h"
#include "CFlat/IO/Stream.h"

#include <cerrno>
#include <cstdio>

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

using namespace CFlat;

/**************************************/
/* Private functions                  */
/**************************************/

static std::FILE *FileOpen(const char *path, FileMode::Enum mode, FileAccess::Enum fileAccess);
static void FileSeek(std::FILE *file, intfsize offset, SeekOrigin::Enum origin);
static intfsize FileTell(std::FILE *file);
static void FileTruncate(std::FILE *file, intfsize length);

static void ValidateFileDoesNotExist(const char *path);
static void ValidateModeAccessCombination(FileMode::Enum mode, FileAccess::Enum fileAccess);
static const char *GetCFileModeString(FileMode::Enum mode, FileAccess::Enum fileAccess);
static int GetCSeekOrigin(SeekOrigin::Enum origin);
static void GenerateFileOpenException(int errorCode, FileMode::Enum mode);

/**************************************/
/* Public function definitions        */
/**************************************/

FileStream::FileStream(const String &path, FileMode::Enum mode) :
    FileStream(path, mode, mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite)
{
}

FileStream::FileStream(const char *path, FileMode::Enum mode) :
    FileStream(path, mode, mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite)
{
}

FileStream::FileStream(const String &path, FileMode::Enum mode, FileAccess::Enum fileAccess) :
    _file(nullptr),
    _access(fileAccess),
    _mode(mode)
{
    FileMode::Validate(mode);
    FileAccess::Validate(fileAccess);

    _file = FileOpen(path.GetCString(), mode, fileAccess);
}

FileStream::FileStream(const char *path, FileMode::Enum mode, FileAccess::Enum fileAccess) :
    _file(nullptr),
    _access(fileAccess),
    _mode(mode)
{
    Validate_NotNull(path);
    FileMode::Validate(mode);
    FileAccess::Validate(fileAccess);

    _file = FileOpen(path, mode, fileAccess);
}

FileStream::~FileStream()
{
    if (this->CanWrite()) {
        try {
            this->Flush();
        }
        catch (const Exception &ex) {
            (void)ex;
        }
    }

    std::fclose(_file);
}

bool FileStream::CanRead() const
{
    return FileAccess::HasFlag(_access, FileAccess::Read);
}

bool FileStream::CanSeek() const
{
    return true;
}

bool FileStream::CanWrite() const
{
    return FileAccess::HasFlag(_access, FileAccess::Write);
}

intfsize FileStream::GetLength() const
{
    this->ValidateSeekSupported();

    intfsize length = 0;

    try {
        intfsize cur = FileTell(_file);

        FileSeek(_file, 0, SeekOrigin::End);

        length = FileTell(_file);

        FileSeek(_file, cur, SeekOrigin::Begin);
    }
    catch (const Exception &ex) {
        (void)ex;

        // TODO: Fix innerexception!!!
        throw IOException(String::Wrap("Failed to get the length of the file."), nullptr /* ex */);
    }

    return length;
}

void FileStream::SetLength(intfsize length)
{
    Validate_NotNegative(length);
    this->ValidateSeekSupported();

    FileTruncate(_file, length);
}

intfsize FileStream::GetPosition() const
{
    this->ValidateSeekSupported();

    return FileTell(_file);
}

void FileStream::SetPosition(intfsize position)
{
    FileStream::Seek(position, SeekOrigin::Begin);
}

void FileStream::Flush()
{
    if (this->CanWrite()) {
        std::fflush(_file);

        if (std::ferror(_file)) {
            throw IOException(String::Wrap("Failed to flush the stream."));
        }
    }
}

uintsize FileStream::Read(byte *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(buffer);
    this->ValidateReadSupported();

    uintsize bytesRead = std::fread(&buffer[offset], 1, count, _file);

    if (std::ferror(_file)) {
        throw IOException(String::Wrap("Failed to read from the stream."));
    }

    return bytesRead;
}

intfsize FileStream::Seek(intfsize offset, SeekOrigin::Enum origin)
{
    this->ValidateSeekSupported();

    FileSeek(_file, offset, origin);

    return FileTell(_file);
}

void FileStream::Write(const byte *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(buffer);
    this->ValidateWriteSupported();

    if (count == 0) return;

    std::fwrite(&buffer[offset], 1, count, _file);

    if (std::ferror(_file)) {
        throw IOException(String::Wrap("Failed to write to the stream."));
    }
}

void FileStream::ValidateReadSupported() const
{
    Validate_IsTrue(this->CanRead(), NotSupportedException(String::Wrap("The stream does not support reading.")));
}

void FileStream::ValidateSeekSupported() const
{
    Validate_IsTrue(this->CanSeek(), NotSupportedException(String::Wrap("The stream does not support seeking.")));
}

void FileStream::ValidateWriteSupported() const
{
    Validate_IsTrue(this->CanWrite(), NotSupportedException(String::Wrap("The stream does not support writing.")));
}

/**************************************/
/* Private function definitions       */
/**************************************/

static std::FILE *FileOpen(const char *path, FileMode::Enum mode, FileAccess::Enum fileAccess)
{
    assert(path != nullptr);
    assert(FileMode::IsValid(mode));
    assert(FileAccess::IsValid(fileAccess));

    ValidateModeAccessCombination(mode, fileAccess);

    if (mode == FileMode::CreateNew) {
        ValidateFileDoesNotExist(path);
    }

    const char *fileMode = GetCFileModeString(mode, fileAccess);

    errno = 0;
    std::FILE *file = std::fopen(path, fileMode);

    if (file == nullptr) {
        GenerateFileOpenException(errno, mode);
    }

    return file;
}

static void FileSeek(std::FILE *file, intfsize offset, SeekOrigin::Enum origin)
{
    assert(file != nullptr);
    assert(SeekOrigin::IsValid(origin));

    fseeko(file, offset, GetCSeekOrigin(origin));

    if (std::ferror(file)) {
        throw IOException(String::Wrap("Failed to seek to the given offset."));
    }
}

static intfsize FileTell(std::FILE *file)
{
    assert(file != nullptr);

    intfsize pos = ftell/*o*/(file);

    assert(pos >= 0);

    if (std::ferror(file)) {
        throw IOException(String::Wrap("Failed to get the current position within the stream."));
    }

    return pos;
}

static void FileTruncate(std::FILE *file, intfsize length)
{
    assert(file != nullptr);
    assert(length >= 0);

#if defined(POSIX_ftruncate) && defined(POSIX_fileno)
    ftruncate(fileno(file), length);

    if (std::ferror(file)) {
        throw IOException(String::Wrap("Failed to truncate the stream."));
    }
#else
    throw_new(NotSupportedException, null);
#endif
}

static void ValidateFileDoesNotExist(const char *path)
{
    std::FILE *file = std::fopen(path, "r");

    if (file != nullptr) {
        std::fclose(file);

        throw IOException(String::Wrap("Failed to create new file: File already exists."));
    }
}

static void ValidateModeAccessCombination(FileMode::Enum mode, FileAccess::Enum fileAccess)
{
    assert(FileMode::IsValid(mode));
    assert(FileAccess::IsValid(fileAccess));

    switch (mode) {
        case FileMode::Append:
            if (fileAccess != FileAccess::Write) {
                throw ArgumentException(String::Wrap("Append mode can only be used in combination with write-only access."));
            }
            break;

        case FileMode::Open:
        case FileMode::OpenOrCreate:
            if (fileAccess == FileAccess::Write) {
                throw ArgumentException(String::Wrap("The specified file mode cannot be used in combination with write-only access."));
            }
            break;

        case FileMode::Create:
        case FileMode::CreateNew:
        case FileMode::Truncate:
            if (fileAccess == FileAccess::Read) {
                throw ArgumentException(String::Wrap("The specified file mode cannot be used in combination with read-only access."));
            }
            break;

        default:
            assert(false);
            break;
    }
}

static const char *GetCFileModeString(FileMode::Enum mode, FileAccess::Enum fileAccess)
{
    assert(FileMode::IsValid(mode));
    assert(FileAccess::IsValid(fileAccess));

    switch (mode) {
        case FileMode::Append:
            return "ab";

        case FileMode::Open:
        case FileMode::OpenOrCreate:
            if ((fileAccess & FileAccess::Write) == FileAccess::Write) {
                return "r+b";
            }
            else {
                return "rb";
            }

        case FileMode::Create:
        case FileMode::CreateNew:
        case FileMode::Truncate:
            if ((fileAccess & FileAccess::Read) == FileAccess::Read) {
                return "w+b";
            }
            else {
                return "wb";
            }

        default:
            assert(false);
            return nullptr;
    }
}

static int GetCSeekOrigin(SeekOrigin::Enum origin)
{
    assert(SeekOrigin::IsValid(origin));

    switch (origin) {
        case SeekOrigin::Begin:
            return SEEK_SET;

        case SeekOrigin::Current:
            return SEEK_CUR;

        case SeekOrigin::End:
            return SEEK_END;

        default:
            assert(false);
            return 0;
    }
}

static void GenerateFileOpenException(int errorCode, FileMode::Enum mode)
{
    switch (mode) {
        case FileMode::Create:
        case FileMode::CreateNew:
#ifdef EACCES
            if (errorCode == EACCES) throw IOException(String::Wrap("Failed to create file: Permission denied."));
#endif
#ifdef ENOENT
            if (errorCode == ENOENT) throw IOException(String::Wrap("Failed to create file: No such file or directory."));
#endif
#ifdef EMFILE
            if (errorCode == EMFILE) throw IOException(String::Wrap("Failed to create file: Too many open files."));
#endif
#ifdef ENFILE
            if (errorCode == ENFILE) throw IOException(String::Wrap("Failed to create file: Too many open files."));
#endif
            throw IOException(String::Wrap("Failed to create file."));
            break;

        case FileMode::Append:
        case FileMode::Open:
        case FileMode::OpenOrCreate:
        case FileMode::Truncate:
#ifdef EACCES
            if (errorCode == EACCES) throw IOException(String::Wrap("Failed to open file: Permission denied."));
#endif
#ifdef ENOENT
            if (errorCode == ENOENT) throw IOException(String::Wrap("Failed to open file: No such file or directory."));
#endif
#ifdef EMFILE
            if (errorCode == EMFILE) throw IOException(String::Wrap("Failed to open file: Too many open files."));
#endif
#ifdef ENFILE
            if (errorCode == ENFILE) throw IOException(String::Wrap("Failed to open file: Too many open files."));
#endif
            throw IOException(String::Wrap("Failed to open file."));
            break;

        default:
            assert(false);
            break;
    }
}
