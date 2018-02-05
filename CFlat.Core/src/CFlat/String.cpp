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

#include "CFlat/String.h"
#include "CFlat/String.Enumerator.h"

#include "CFlat.h"
#include "CFlat/CString.h"
#include "CFlat/Memory.h"
#include "CFlat/StringBuilder.h"
#include "CFlat/Validate.h"

#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/List.h"

#include <utility>

using namespace CFlat;

/* Public constants */
/// <summary>
/// Represents an empty string.
/// </summary>
const String String::Empty = String();

/**************************************/
/* Public function definitions        */
/**************************************/

String::String()
{
}

String::String(shared_ptr<const char[]> value) :
    _length(value ? CString::Length(value.Get()) : 0),
    _value(value)
{
}

String::String(unique_ptr<char[]> &&value) :
    _length(0),
    _value(nullptr)
{
    _length = value ? CString::Length(value.Get()) : 0;
    _value = shared_ptr<const char[]>(std::move(value));
}

String::String(const char *value) :
    _length(value ? CString::Length(value) : 0),
    _value(value ? shared_ptr<const char[]>(CString::Copy(value)) : nullptr)
{
}

String::String(const char *value, uintsize startIndex, uintsize length) :
    _length(length),
    _value(length == 0 ? nullptr : shared_ptr<const char[]>(CString::CSubstring(value, startIndex, length)))
{
}

const char &String::operator[](uintsize index) const
{
    Validate_ArgumentRange(index < _length,
        "Index must be less than the size of the string/array/collection.", "index");

    return _value[index];
}

char String::GetCharAt(uintsize index) const
{
    Validate_ArgumentRange(index < _length,
        "Index must be less than the size of the string/array/collection.", "index");

    return _value[index];
}

const char *String::GetCString() const
{
    return _value.Get();
}

uintsize String::GetLength() const
{
    return _length;
}

int String::Compare(const String &str1, const String &str2)
{
    return String::Compare(str1, str2, false);
}

int String::Compare(const String &str1, const String &str2, bool ignoreCase)
{
    return String::Compare(
        str1, 0,
        str2, 0,
        UIntSize::Max(str1._length, str2._length),
        ignoreCase);
}

int String::Compare(
    const String &str1, uintsize startIndex1,
    const String &str2, uintsize startIndex2,
    uintsize length)
{
    return String::Compare(str1, startIndex1, str2, startIndex2, length, false);
}

int String::Compare(
    const String &str1, uintsize startIndex1,
    const String &str2, uintsize startIndex2,
    uintsize length,
    bool ignoreCase)
{
    Validate_ArgumentRange(startIndex1 <= str1._length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex1");
    Validate_ArgumentRange(startIndex2 <= str2._length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex2");

    if (length == 0) return 0;

    const char *cstr1 = str1._value.Get();
    const char *cstr2 = str2._value.Get();

    for (uintsize i = 0; i < length; i++) {
        int c1 = ignoreCase ? Char::ToLower(cstr1[i]) : cstr1[i];
        int c2 = ignoreCase ? Char::ToLower(cstr2[i]) : cstr2[i];
        int diff = c1 - c2;

        if (diff) return diff;

        if (c1 == '\0') break;
    }

    return 0;
}

String String::Concat(const String &str1, const String &str2)
{
    StringBuilder sb = StringBuilder(str1.GetLength() + str2.GetLength());
    sb.Append(str1);
    sb.Append(str2);

    return StringBuilder::ToString(std::move(sb));
}

String String::Concat(const String &str1, const String &str2, const String &str3)
{
    StringBuilder sb = StringBuilder(str1.GetLength() + str2.GetLength() + str3.GetLength());
    sb.Append(str1);
    sb.Append(str2);
    sb.Append(str3);

    return StringBuilder::ToString(std::move(sb));
}

String String::Concat(const String &str1, const String &str2, const String &str3, const String &str4)
{
    StringBuilder sb = StringBuilder(str1.GetLength() + str2.GetLength() + str3.GetLength() + str4.GetLength());
    sb.Append(str1);
    sb.Append(str2);
    sb.Append(str3);
    sb.Append(str4);

    return StringBuilder::ToString(std::move(sb));
}

String String::Concat(const String strings[], uintsize count)
{
    Validate_NotNull(strings);

    uintsize capacity = 0;

    // Calculate the total length of the resulting string.
    for (uintsize i = 0; i < count; i++) {
        capacity += strings[i]._length;
    }

    StringBuilder sb = StringBuilder(capacity);

    // Concatenate the strings.
    for (uintsize i = 0; i < count; i++) {
        sb.Append(strings[i]);
    }

    return StringBuilder::ToString(std::move(sb));
}

String String::Concat(const IEnumerable<String> &strings)
{
    unique_ptr<IEnumerator<String>> enumerator(strings.GetEnumerator());
    StringBuilder sb = StringBuilder();

    while (enumerator->MoveNext()) {
        sb.Append(enumerator->GetCurrent());
    }

    return StringBuilder::ToString(std::move(sb));
}

bool String::Contains(char value) const
{
    return this->IndexOf(value) != InvalidIndex;
}

bool String::Contains(const char *value) const
{
    return this->IndexOf(value) != InvalidIndex;
}

bool String::Contains(const String &value) const
{
    return this->IndexOf(value) != InvalidIndex;
}

String String::Copy() const
{
    return String(_value);
}

void String::CopyTo(
    uintsize sourceIndex,
    char *destination,
    uintsize destinationIndex,
    uintsize count) const
{
    Validate_NotNull(destination);
    Validate_ArgumentRange(sourceIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "sourceIndex");
    Validate_ArgumentRange(count <= _length - sourceIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    Memory::Copy(&_value[sourceIndex], &destination[destinationIndex], count);
}

bool String::EndsWith(char value) const
{
    return _length > 0 && _value[_length - 1] == value;
}

bool String::EndsWith(const char *value) const
{
    return this->EndsWith(value, false);
}

bool String::EndsWith(const char *value, bool ignoreCase) const
{
    Validate_NotNull(value);

    return this->EndsWith(String::Wrap(value), ignoreCase);
}

bool String::EndsWith(const String &value) const
{
    return this->EndsWith(value, false);
}

bool String::EndsWith(const String &value, bool ignoreCase) const
{
    if (value._length == 0) return true;
    if (value._length > _length) return false;

    // Indices are within bounds because of the early-out above.
    const char *cstr1 = &_value[_length - 1];
    const char *cstr2 = &value._value[value._length - 1];

    // Iterate through all of the search string's characters, or until we find two inequal characters.
    for (uintsize length = value._length; length-- > 0; cstr1--, cstr2--) {
        if ((!ignoreCase && *cstr1 != *cstr2) || (ignoreCase && Char::ToLower(*cstr1) != Char::ToLower(*cstr2))) {
            return false;
        }
    }

    // Reached the end of the search string, all the characters must've matched.
    return true;
}

bool String::Equals(const String &str1, const String &str2)
{
    return String::Equals(str1, str2, false);
}

bool String::Equals(const String &str1, const String &str2, bool ignoreCase)
{
    return
        std::addressof(str1) == std::addressof(str2) || (
            str1._length == str2._length &&
            CString::Equals(str1._value.Get(), str2._value.Get(), ignoreCase));
}

bool String::Equals(const String &str1, const char *str2)
{
    return String::Equals(str1, str2, false);
}

bool String::Equals(const String &str1, const char *str2, bool ignoreCase)
{
    return str2 != nullptr && CString::Equals(str1._value.Get(), str2, ignoreCase);
}

String String::Format(const char *format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    String result = String::FormatVA(format, args);

    VarArgs_End(args);

    return result;
}

String String::FormatVA(const char *format, VarArgsList args)
{
    Validate_NotNull(format);

    return String::FormatVA(String::Wrap(format), args);
}

String String::Format(String format, ...)
{
    VarArgsList args;
    VarArgs_Start(args, format);

    String result = String::FormatVA(format, args);

    VarArgs_End(args);

    return result;
}

String String::FormatVA(const String &format, VarArgsList args)
{
    StringBuilder sb = StringBuilder();
    sb.AppendFormatVA(format, args);

    return StringBuilder::ToString(std::move(sb));
}

int String::GetHashCode() const
{
    return CString::GetHashCode(_value.Get());
}

uintsize String::IndexOf(char value) const
{
    return this->IndexOf(value, 0, _length);
}

uintsize String::IndexOf(char value, uintsize startIndex) const
{
    return this->IndexOf(value, startIndex, _length - startIndex);
}

uintsize String::IndexOf(char value, uintsize startIndex, uintsize count) const
{
    Validate_ArgumentRange(startIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= _length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize end = startIndex + count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex; i < end; i++) {
        if (_value[i] == value) {
            return i;
        }
    }

    return InvalidIndex;
}

uintsize String::IndexOf(const char *value) const
{
    return this->IndexOf(value, 0, _length);
}

uintsize String::IndexOf(const char *value, uintsize startIndex) const
{
    return this->IndexOf(value, startIndex, _length - startIndex);
}

uintsize String::IndexOf(
    const char *value,
    uintsize startIndex,
    uintsize count) const
{
    Validate_NotNull(value);
    Validate_ArgumentRange(startIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= _length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    // If we are searching for an empty string, report it at the starting index.
    if (*value == '\0') {
        return startIndex;
    }

    uintsize end = startIndex + count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex; i < end; i++) {
        if (CString::StartsWith(&_value[i], value)) {
            return i;
        }
    }

    return InvalidIndex;
}

uintsize String::IndexOf(const String &value) const
{
    return this->IndexOf(value, 0, _length);
}

uintsize String::IndexOf(const String &value, uintsize startIndex) const
{
    return this->IndexOf(value, startIndex, _length - startIndex);
}

uintsize String::IndexOf(
    const String &value,
    uintsize startIndex,
    uintsize count) const
{
    Validate_ArgumentRange(startIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= _length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    // If we are searching for an empty string, report it at the starting index.
    if (value._value[0] == '\0') {
        return startIndex;
    }

    // If we are searching for a string that does not fit in the span we are searching for, report it not found.
    if (value._length > count) {
        return InvalidIndex;
    }

    uintsize end = startIndex + count - value._length;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex; i < end; i++) {
        if (CString::StartsWith(&_value[i], value)) {
            return i;
        }
    }

    return InvalidIndex;
}

uintsize String::IndexOfAny(const char *anyOf) const
{
    return this->IndexOfAny(anyOf, 0, _length);
}

uintsize String::IndexOfAny(const char *anyOf, uintsize startIndex) const
{
    return this->IndexOfAny(anyOf, startIndex, _length - startIndex);
}

uintsize String::IndexOfAny(const char *anyOf, uintsize startIndex, uintsize count) const
{
    Validate_NotNull(anyOf);
    Validate_ArgumentRange(startIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= _length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize end = startIndex + count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex; i < end; i++) {
        if (CString::IndexOf(anyOf, _value[i]) != InvalidIndex) {
            return i;
        }
    }

    return InvalidIndex;
}

String String::Insert(uintsize startIndex, const String &value) const
{
    Validate_ArgumentRange(startIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");

    if (value._length == 0) return *this;

    uintsize capacity = UIntSize::CheckedAddition(_length, value._length);

    StringBuilder sb = StringBuilder(capacity);
    sb.Append(*this);
    sb.Insert(startIndex, value);

    return StringBuilder::ToString(std::move(sb));
}

bool String::IsEmpty() const
{
    return _length == 0;
}

bool String::IsEmptyOrWhiteSpace() const
{
    for (uintsize i = 0; i < _length; i++) {
        if (!Char::IsWhiteSpace(_value[i])) return false;
    }

    return true;
}

String String::Join(const String &separator, const String strings[], uintsize count)
{
    Validate_NotNull(strings);

    if (count == 0) return String::Empty;
    if (count == 1) return strings[0];

    uintsize capacity = 0;

    // Calculate the total length of the resulting string.
    capacity = UIntSize::CheckedMultiplication(count - 1, separator._length);

    for (uintsize i = 0; i < count; i++) {
        capacity = UIntSize::CheckedAddition(capacity, strings[i]._length);
    }

    StringBuilder sb = StringBuilder(capacity);

    // Join the strings.
    for (uintsize i = 0; i < count - 1; i++) {
        sb.Append(strings[i]);
        sb.Append(separator);
    }

    sb.Append(strings[count - 1]);

    return StringBuilder::ToString(std::move(sb));
}

String String::Join(const String &separator, const IEnumerable<String> &strings)
{
    unique_ptr<IEnumerator<String>> enumerator(strings.GetEnumerator());
    StringBuilder sb = StringBuilder();

    bool first = true;

    while (enumerator->MoveNext()) {
        if (!first) sb.Append(separator);

        sb.Append(enumerator->GetCurrent());

        if (first) first = false;
    }

    return StringBuilder::ToString(std::move(sb));
}

uintsize String::LastIndexOf(char value) const
{
    return LastIndexOf(value, _length - 1, _length);
}

uintsize String::LastIndexOf(char value, uintsize startIndex) const
{
    return LastIndexOf(value, startIndex, UIntSize::CheckedAddition(startIndex, 1));
}

uintsize String::LastIndexOf(char value, uintsize startIndex, uintsize count) const
{
    Validate_ArgumentRange(startIndex < _length || _length == 0,
        "Index must be less than the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(startIndex + 1 >= count || _length == 0,
        "Count must refer to a location within the string/array/collection.", "count");

    // If the string is empty, return InvalidIndex.
    if (_length == 0) {
        return InvalidIndex;
    }

    uintsize end = startIndex + 1 - count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex + 1; i-- > end; ) {
        if (_value[i] == value) {
            return i;
        }
    }

    return InvalidIndex;
}

uintsize String::LastIndexOf(const char *value) const
{
    Validate_NotNull(value);

    return LastIndexOf(String::Wrap(value));
}

uintsize String::LastIndexOf(const char *value, uintsize startIndex) const
{
    Validate_NotNull(value);

    return LastIndexOf(String::Wrap(value), startIndex);
}

uintsize String::LastIndexOf(
    const char *value,
    uintsize startIndex,
    uintsize count) const
{
    Validate_NotNull(value);

    return LastIndexOf(String::Wrap(value), startIndex, count);
}

uintsize String::LastIndexOf(const String &value) const
{
    if (_length == 0) {
        if (value._length == 0) {
            return 0;
        }
        else {
            return InvalidIndex;
        }
    }
    else {
        return LastIndexOf(value, _length - 1, _length);
    }
}

uintsize String::LastIndexOf(const String &value, uintsize startIndex) const
{
    return LastIndexOf(value, startIndex, UIntSize::CheckedAddition(startIndex, 1));
}

uintsize String::LastIndexOf(
    const String &value,
    uintsize startIndex,
    uintsize count) const
{
    Validate_ArgumentRange(startIndex < _length || _length == 0,
        "Index must be less than the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(startIndex + 1 >= count || _length == 0,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize length = value._length;
    uintsize end = startIndex + 1 - count;

    // If we are searching for an empty string, report it at the starting index.
    if (length == 0) {
        return startIndex;
    }

    // If there aren't enough characters in front of start index, return InvalidIndex.
    if (startIndex + 1 < length) {
        return InvalidIndex;
    }

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex + 1 - length; i-- > end; ) {
        if (CString::StartsWith(&_value[i], value._value.Get())) {
            return i;
        }
    }

    return InvalidIndex;
}

uintsize String::LastIndexOfAny(const char *anyOf) const
{
    if (_length == 0) {
        Validate_NotNull(anyOf);

        return InvalidIndex;
    }
    else {
        return LastIndexOfAny(anyOf, _length - 1, _length);
    }
}

uintsize String::LastIndexOfAny(const char *anyOf, uintsize startIndex) const
{
    return LastIndexOfAny(anyOf, startIndex, UIntSize::CheckedAddition(startIndex, 1));
}

uintsize String::LastIndexOfAny(
    const char *anyOf,
    uintsize startIndex,
    uintsize count) const
{
    Validate_NotNull(anyOf);
    Validate_ArgumentRange(startIndex < _length || _length == 0,
        "Index must be less than the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(startIndex + 1 >= count || _length == 0,
        "Count must refer to a location within the string/array/collection.", "count");

    // If the string is empty, return InvalidIndex.
    if (_length == 0) {
        return InvalidIndex;
    }

    uintsize end = startIndex + 1 - count;

    // Iterate through all of the string's specified characters.
    for (uintsize i = startIndex + 1; i-- > end; ) {
        if (CString::IndexOf(anyOf, _value[i]) != InvalidIndex) {
            return i;
        }
    }

    return InvalidIndex;
}

String String::PadLeft(uintsize totalWidth, char paddingChar) const
{
    if (totalWidth <= _length) return *this;

    StringBuilder sb = StringBuilder(totalWidth);

    for (uintsize i = _length; i < totalWidth; i++) {
        sb.Append(paddingChar);
    }

    sb.Append(*this);

    return StringBuilder::ToString(std::move(sb));
}

String String::PadRight(uintsize totalWidth, char paddingChar) const
{
    if (totalWidth <= _length) return *this;

    StringBuilder sb = StringBuilder(*this, totalWidth);

    for (uintsize i = _length; i < totalWidth; i++) {
        sb.Append(paddingChar);
    }

    return StringBuilder::ToString(std::move(sb));
}

String String::Remove(uintsize startIndex) const
{
    return this->Substring(0, startIndex);
}

String String::Remove(uintsize startIndex, uintsize count) const
{
    Validate_ArgumentRange(startIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(count <= _length - startIndex,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize endIndex = startIndex + count;

    StringBuilder sb = StringBuilder(_length - count);
    sb.Append(_value.Get(), 0, startIndex);
    sb.Append(_value.Get(), endIndex, _length - endIndex);

    return StringBuilder::ToString(std::move(sb));
}

String String::Replace(char oldValue, char newValue) const
{
    StringBuilder sb = StringBuilder(*this);
    sb.Replace(oldValue, newValue);

    return StringBuilder::ToString(std::move(sb));
}

String String::Replace(const char *oldValue, const char *newValue) const
{
    StringBuilder sb = StringBuilder(*this);
    sb.Replace(oldValue, newValue);

    return StringBuilder::ToString(std::move(sb));
}

String String::Replace(const String &oldValue, const String &newValue) const
{
    StringBuilder sb = StringBuilder(*this);
    sb.Replace(oldValue, newValue);

    return StringBuilder::ToString(std::move(sb));
}

unique_ptr<IList<String>> String::Split(const char *separators) const
{
    return this->Split(separators, UIntSize::MaxValue, StringSplitOptions_None);
}

unique_ptr<IList<String>> String::Split(const char *separators, uintsize count) const
{
    return this->Split(separators, count, StringSplitOptions_None);
}

unique_ptr<IList<String>> String::Split(
    const char *separators,
    StringSplitOptions options) const
{
    return this->Split(separators, UIntSize::MaxValue, options);
}

unique_ptr<IList<String>> String::Split(
    const char *separators,
    uintsize count,
    StringSplitOptions options) const
{
    Validate_NotNull(separators);

    auto list = unique_ptr<IList<String>>(new List<String>());

    uintsize i;
    uintsize offset = 0;

    for (i = 1; i <= count; i++) {
        uintsize separatorIndex;

        if (i == count) {
            separatorIndex = _length;
        }
        else {
            separatorIndex = this->IndexOfAny(separators, offset);

            if (separatorIndex == InvalidIndex) {
                break;
            }
        }

        if (separatorIndex == offset) {
            if ((options & StringSplitOptions_RemoveEmptyEntries) == 0) {
                list->Add(String::Empty);
            }
        }
        else {
            list->Add(this->Substring(offset, separatorIndex - offset));
        }

        offset = separatorIndex + 1;
    }

    if (i <= count) {
        if (offset == _length) {
            if ((options & StringSplitOptions_RemoveEmptyEntries) == 0) {
                list->Add(String::Empty);
            }
        }
        else if (offset < _length) {
            list->Add(this->Substring(offset, _length - offset));
        }
    }

    return list;
}

bool String::StartsWith(char value) const
{
    return CString::StartsWith(_value.Get(), value);
}

bool String::StartsWith(const char *value) const
{
    return CString::StartsWith(_value.Get(), value);
}

bool String::StartsWith(const char *value, bool ignoreCase) const
{
    return CString::StartsWith(_value.Get(), value, ignoreCase);
}

bool String::StartsWith(const String &value) const
{
    return this->StartsWith(value, false);
}

bool String::StartsWith(const String &value, bool ignoreCase) const
{
    if (value._length == 0) return true;
    if (value._length > _length) return false;

    return CString::StartsWith(_value.Get(), value._value.Get(), ignoreCase);
}

String String::Substring(uintsize startIndex) const
{
    Validate_ArgumentRange(startIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");

    return this->Substring(startIndex, _length - startIndex);
}

String String::Substring(uintsize startIndex, uintsize length) const
{
    Validate_ArgumentRange(startIndex <= _length,
        "Index cannot be greater than the the size of the string/array/collection.", "startIndex");
    Validate_ArgumentRange(length <= _length - startIndex,
        "StartIndex and length must refer to a location within the string.", "length");

    if (length == 0) return String::Empty;
    if (startIndex == 0 && length == _length) return *this;

    StringBuilder sb = StringBuilder(length);
    sb.Append(_value.Get(), startIndex, length);

    return StringBuilder::ToString(std::move(sb));
}

unique_ptr<char[]> String::ToCString() const
{
    return CString::Copy(_value.Get());
}

String String::ToLower() const
{
    StringBuilder sb = StringBuilder(_length);

    for (uintsize i = 0; i < _length; i++) {
        sb.Append((char)Char::ToLower(_value[i]));
    }

    return StringBuilder::ToString(std::move(sb));
}

String String::ToUpper() const
{
    StringBuilder sb = StringBuilder(_length);

    for (uintsize i = 0; i < _length; i++) {
        sb.Append((char)Char::ToUpper(_value[i]));
    }

    return StringBuilder::ToString(std::move(sb));
}

String String::Trim(const char *trimChars) const
{
    if (CString::IsNullOrEmpty(trimChars)) {
        return this->TrimWhiteSpace(2);
    }

    return this->Trim(trimChars, 2);
}

String String::TrimEnd(const char *trimChars) const
{
    if (CString::IsNullOrEmpty(trimChars)) {
        return this->TrimWhiteSpace(1);
    }

    return this->Trim(trimChars, 1);
}

String String::TrimStart(const char *trimChars) const
{
    if (CString::IsNullOrEmpty(trimChars)) {
        return this->TrimWhiteSpace(0);
    }

    return this->Trim(trimChars, 0);
}

String String::Wrap(const char *str)
{
    return String(shared_ptr<const char[]>(str, NoOpDeleter<const char[]>()));
}

unique_ptr<String> String::WrapPointer(const char *str)
{
    if (str == nullptr) { return nullptr; }

    return unique_ptr<String>(new String(shared_ptr<const char[]>(str, NoOpDeleter<const char[]>())));
}

/* IEnumerable */
unique_ptr<IEnumerator<char>> String::GetEnumerator() const
{
    return unique_ptr<IEnumerator<char>>(new Enumerator(*this));
}

/**************************************/
/* Private function definitions       */
/**************************************/

String String::Trim(const char *trimChars, int mode) const
{
    assert(trimChars != nullptr);

    uintsize length = _length;
    uintsize start = 0;
    uintsize end = length;

    if (mode != 1) {
        while (start < length && CString::Contains(trimChars, _value[start])) {
            start++;
        }
    }

    if (mode != 0) {
        while (end > start && CString::Contains(trimChars, _value[end - 1])) {
            end--;
        }
    }

    return this->Substring(start, end - start);
}

String String::TrimWhiteSpace(int mode) const
{
    uintsize length = _length;
    uintsize start = 0;
    uintsize end = length;

    if (mode != 1) {
        while (start < length && Char::IsWhiteSpace(_value[start])) {
            start++;
        }
    }

    if (mode != 0) {
        while (end > start && Char::IsWhiteSpace(_value[end - 1])) {
            end--;
        }
    }

    return this->Substring(start, end - start);
}
