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

#include "CFlat/StringBuilder.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/Environment.h"
#include "CFlat/Memory.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

#include <utility>

using namespace CFlat;

/* Private constants */
/// <summary>
/// The default capacity for an empty <see cref="StringBuilder"/>.
/// </summary>
static const uintsize DefaultCapacity = 16;

/**************************************/
/* Public function definitions        */
/**************************************/

/* Constructors */
StringBuilder::StringBuilder() : StringBuilder(String::Empty, DefaultCapacity)
{
}

StringBuilder::StringBuilder(const StringBuilder &sb) :
    _buffer(new char[sb._capacity]),
    _capacity(sb._capacity),
    _length(sb._length)
{
    Memory::Copy(sb._buffer.Get(), _buffer.Get(), _length);
}

StringBuilder::StringBuilder(StringBuilder &&sb) :
    _buffer(),
    _capacity(0),
    _length(0)
{
    std::swap(_buffer, sb._buffer);
    std::swap(_capacity, sb._capacity);
    std::swap(_length, sb._length);
}

StringBuilder::StringBuilder(uintsize capacity) : StringBuilder(String::Empty, capacity)
{
}

StringBuilder::StringBuilder(const char *value) : StringBuilder(String::Wrap(value), DefaultCapacity)
{
}

StringBuilder::StringBuilder(const char *value, uintsize capacity) : StringBuilder(String::Wrap(value), capacity)
{
}

StringBuilder::StringBuilder(const String &value) : StringBuilder(value, DefaultCapacity)
{
}

StringBuilder::StringBuilder(const String &value, uintsize capacity)
{
    uintsize length = value.GetLength();

    // If the capacity is zero, use the default capacity instead.
    if (capacity == 0) {
        capacity = DefaultCapacity;
    }

    // If the capacity is not large enough for the given value, increase the capacity.
    if (capacity < length) {
        capacity = length;
    }

    // Initialize the StringBuilder.
    _length = length;
    _capacity = capacity;
    _buffer = unique_ptr<char[]>(new char[UIntSize::CheckedAddition(capacity, 1)]);

    // Initialize the contents of the StringBuilder to the given string.
    if (length) {
        Memory::Copy(value.GetCString(), _buffer.Get(), length);
    }
}

/* Properties */
char *StringBuilder::GetData() const
{
    this->EnsureBufferIsString();

    return _buffer.Get();
}

uintsize StringBuilder::GetLength() const
{
    return _length;
}

uintsize StringBuilder::GetCapacity() const
{
    return _capacity;
}

void StringBuilder::SetCapacity(uintsize capacity) const
{
    Validate_ArgumentRange(capacity >= _length,
        "Capacity cannot be smaller than the current length.", "capacity");

    if (capacity != _capacity) {
        unique_ptr<char[]> newBuffer = unique_ptr<char[]>(new char[UIntSize::CheckedAddition(capacity, 1)]);

        Memory::Copy(_buffer.Get(), newBuffer.Get(), _length);

        _buffer = std::move(newBuffer);
        _capacity = capacity;
    }
}

/* Operators */
StringBuilder &StringBuilder::operator=(const StringBuilder &sb)
{
    if (this != std::addressof(sb)) {
        this->EnsureCapacity(sb._length);

        Memory::Copy(sb._buffer.Get(), _buffer.Get(), sb._length);

        _length = sb._length;
    }

    return *this;
}

StringBuilder &StringBuilder::operator=(StringBuilder &&sb)
{
    if (this != std::addressof(sb)) {
        std::swap(_buffer, sb._buffer);
        std::swap(_capacity, sb._capacity);
        std::swap(_length, sb._length);
    }

    return *this;
}

String StringBuilder::ToString(const StringBuilder &sb)
{
    return sb.ToString();
}

String StringBuilder::ToString(StringBuilder &&sb)
{
    sb.EnsureBufferIsString();

    return String(shared_ptr<const char[]>(std::move(sb._buffer)));
}

unique_ptr<char[]> StringBuilder::ToCString(const StringBuilder &sb)
{
    return sb.ToCString();
}

unique_ptr<char[]> StringBuilder::ToCString(StringBuilder &&sb)
{
    sb.EnsureBufferIsString();

    return std::move(sb._buffer);
}

/* Methods */
void StringBuilder::Append(char value)
{
    this->EnsureCapacity(UIntSize::CheckedAddition(_length, 1));

    _buffer[_length] = value;
    _length++;
}

void StringBuilder::Append(const char *buffer, uintsize offset, uintsize count)
{
    Validate_NotNull(buffer);

    this->EnsureCapacity(UIntSize::CheckedAddition(_length, count));

    // Copy the string to the end of the buffer.
    Memory::Copy(buffer, offset, _buffer.Get(), _length, count);

    _length += count;
}

void StringBuilder::Append(const char *value)
{
    if (value == nullptr) return;

    this->Append(value, 0, CString::Length(value));
}

void StringBuilder::Append(const String &value)
{
    this->Append(value.GetCString(), 0, value.GetLength());
}

void StringBuilder::Append(int value)
{
    Int::ToString(*this, value, nullptr);
}

void StringBuilder::Append(intmax value)
{
    IntMax::ToString(*this, value, nullptr);
}

/*
#ifdef CFLAT_INTPTR
void StringBuilder::Append(intptr value)
{
    IntPtr::ToString(*this, value, nullptr);
}
#endif

void StringBuilder::Append(intfsize value)
{
    IntFSize::ToString(*this, value, nullptr);
}
*/

void StringBuilder::Append(uint value)
{
    UInt::ToString(*this, value, nullptr);
}

void StringBuilder::Append(uintmax value)
{
    UIntMax::ToString(*this, value, nullptr);
}

/*
#ifdef CFLAT_UINTPTR
void StringBuilder::Append(uintptr value)
{
    Int::ToString(*this, value, nullptr);
}
#endif

void StringBuilder::Append(uintsize value)
{
    UIntSize::ToString(*this, value, nullptr);
}
*/

void StringBuilder::Append(float value)
{
    Float::ToString(*this, value, nullptr);
}

void StringBuilder::Append(double value)
{
    Double::ToString(*this, value, nullptr);
}

void StringBuilder::AppendFormat(const char *format, ...)
{
    Validate_NotNull(format);

    VarArgsList args;
    VarArgs_Start(args, format);

    this->AppendFormatVA(String::Wrap(format), args);

    VarArgs_End(args);
}

void StringBuilder::AppendFormatVA(const char *format, VarArgsList args)
{
    Validate_NotNull(format);

    this->AppendFormatVA(String::Wrap(format), args);
}

void StringBuilder::AppendFormat(String format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    this->AppendFormatVA(format, args);

    VarArgs_End(args);
}

void StringBuilder::AppendLine()
{
    this->Append(Environment::NewLine);
}

void StringBuilder::AppendLine(const char *value)
{
    this->Append(value);
    this->Append(Environment::NewLine);
}

void StringBuilder::AppendLine(const String &value)
{
    this->Append(value);
    this->Append(Environment::NewLine);
}

void StringBuilder::Clear()
{
    // Reset the length to zero.
    _length = 0;
}

void StringBuilder::Insert(uintsize index, char value)
{
    Validate_ArgumentRange(index <= _length, "Index must be within the bounds of the string.", "index");

    this->EnsureCapacity(UIntSize::CheckedAddition(_length, 1));

    // Copy the contents of the buffer after index forward by 1 byte.
    Memory::Copy(_buffer.Get(), index, _buffer.Get(), index + 1, _length - index);

    // Insert the character.
    _buffer[index] = value;
    _length++;
}

void StringBuilder::Insert(
    uintsize index,
    const char *buffer,
    uintsize offset,
    uintsize count)
{
    Validate_NotNull(buffer);
    Validate_ArgumentRange(index <= _length, "Index must be within the bounds of the string.", "index");

    this->EnsureCapacity(UIntSize::CheckedAddition(_length, count));

    // Copy the contents of the buffer after index forward by length bytes.
    Memory::Copy(_buffer.Get(), index, _buffer.Get(), index + count, _length - index);

    // Copy the string into the buffer.
    Memory::Copy(buffer, offset, _buffer.Get(), index, count);

    _length += count;
}

void StringBuilder::Insert(uintsize index, const char *value)
{
    Validate_ArgumentRange(index <= _length, "Index must be within the bounds of the string.", "index");

    if (value == nullptr) return;

    this->Insert(index, value, 0, CString::Length(value));
}

void StringBuilder::Insert(uintsize index, const String &value)
{
    Validate_ArgumentRange(index <= _length, "Index must be within the bounds of the string.", "index");

    this->Insert(index, value.GetCString(), 0, value.GetLength());
}

void StringBuilder::Remove(uintsize startIndex, uintsize count)
{
    Validate_ArgumentRange(startIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= _length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    // Copy the contents of the buffer backward after index forward by length bytes.
    Memory::Copy(_buffer.Get(), startIndex + count, _buffer.Get(), startIndex, _length - (startIndex + count));

    _length -= count;
}

void StringBuilder::Replace(char oldValue, char newValue)
{
    for (uintsize i = 0; i < _length; i++) {
        if (_buffer[i] == oldValue) _buffer[i] = newValue;
    }
}

void StringBuilder::Replace(const char *oldValue, const char *newValue)
{
    Validate_NotNull(oldValue);
    Validate_Argument(oldValue[0] != '\0', "String cannot be of zero length.", "oldValue");

    uintsize oldValueLength = CString::Length(oldValue);
    uintsize newValueLength = newValue == nullptr ? 0 : CString::Length(newValue);
    uintsize i = 0;

    while (i < _length) {
        if (CString::StartsWith(&_buffer[i], oldValue)) {
            this->Remove(i, oldValueLength);
            this->Insert(i, newValue);

            i += newValueLength;
        }
        else {
            i++;
        }
    }
}

void StringBuilder::Replace(const String &oldValue, const String &newValue)
{
    Validate_Argument(oldValue.GetLength() != 0, "String cannot be of zero length.", "oldValue");

    uintsize oldValueLength = oldValue.GetLength();
    uintsize newValueLength = newValue.GetLength();
    uintsize i = 0;

    while (i < _length) {
        if (CString::StartsWith(&_buffer[i], oldValue)) {
            this->Remove(i, oldValueLength);
            this->Insert(i, newValue);

            i += newValueLength;
        }
        else {
            i++;
        }
    }
}

String StringBuilder::ToString() const
{
    this->EnsureBufferIsString();

    return String(_buffer.Get());
}

unique_ptr<char[]> StringBuilder::ToCString() const
{
    this->EnsureBufferIsString();

    return CString::Copy(_buffer.Get());
}

/**************************************/
/* Internal function definitions      */
/**************************************/

void StringBuilder::EnsureBufferIsString() const
{
    this->EnsureCapacity(1);

    // Ensure that the buffer has a terminating nullptr character.
    _buffer[_length] = '\0';
}

/**************************************/
/* Private function definitions       */
/**************************************/

void StringBuilder::EnsureCapacity(uintsize minCapacity) const
{
    if (_capacity < minCapacity) {
        uintsize capacity;
        capacity = UIntSize::Max(minCapacity, _length * 2);
        capacity = UIntSize::Max(capacity, DefaultCapacity);

        this->SetCapacity(capacity);
    }
}
