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

#include "CFlat/Collections/List.h"

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/ICollection.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/IList.h"
//#include "CFlat/Collections/ListEnumerator.h"

#include <utility>

using namespace CFlat;

#ifdef NOPE

/* Private constants */
/// <summary>
/// The default capacity for a list that is not empty.
/// </summary>
template <typename T>
const uintsize List<T>::DefaultCapacity = 4;

/* Constructors */
template <typename T>
List<T>::List() : List(DefaultCapacity)
{
}

template <typename T>
List<T>::List(const List<T> &list) : List(list._capacity)
{
    Memory::Copy(list._array.Get(), _array.Get(), list._count * sizeof(T));
}

template <typename T>
List<T>::List(List<T> &&list) :
    _array(nullptr),
    _capacity(0),
    _count(0),
    _version(0)
{
    std::swap(_array, list._array);
    std::swap(_capacity, list._capacity);
    std::swap(_count, list._count);
    std::swap(_version, list._version);
}

template <typename T>
List<T>::List(uintsize capacity)
{
    Validate_ArgumentRange(elementSize > 0, "Element size cannot be zero.", "elementSize");
    Validate_ArgumentRange(capacity != InvalidIndex,
        "Capacity cannot be equal to the value of InvalidIndex.", "capacity");

    _array = nullptr;
    _capacity = 0;
    _count = 0;
    _version = 0;

    this->SetCapacity(capacity);
}

template <typename T>
List<T>::List(const IEnumerable<T> &collection)
{
    this->AddRange(collection);
}

template <typename T>
List<T>::List(const ICollection<T> &collection) : List(collection.GetCount())
{
    this->AddRange(collection);
}

/* Destructor */
template <typename T>
List<T>::~List()
{
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &list)
{
    if (this != std::addressof(list)) {
        this->EnsureCapacity(list._capacity);

        Memory::Copy(list._array.Get(), _array.Get(), list._length * sizeof(T));

        _count = list._count;
        _version = list._version + 1;
    }

    return *this;
}

template <typename T>
List<T> &List<T>::operator=(List<T> &&list)
{
    if (this != std::addressof(list)) {
        std::swap(_array, list._array);
        std::swap(_capacity, list._capacity);
        std::swap(_count, list._count);
        std::swap(_version, list._version);
    }

    return *this;
}

/* Properties */
template <typename T>
uintsize List<T>::GetCapacity() const
{
    return _capacity;
}

template <typename T>
void List<T>::SetCapacity(uintsize capacity)
{
    Validate_ArgumentRange(capacity >= _count,
        "Capacity cannot be smaller than the current length.", "capacity");
    Validate_ArgumentRange(capacity != InvalidIndex,
        "Capacity cannot be equal to the value of InvalidIndex.", "capacity");

    if (capacity != _capacity) {
        _array = Memory::Reallocate<T>(_array, UIntSize::CheckedMultiplication(capacity, sizeof(T)));
        _capacity = capacity;
    }
}

/* Methods */
template <typename T>
void List<T>::AddRange(const IEnumerable<T> &collection)
{
    Validate_NotNull(collection);

    this->InsertRange(_count, collection);
}

template <typename T>
void List<T>::InsertRange(uintsize index, const IEnumerable<T> &collection)
{
    Validate_NotNull(collection);
    Validate_ArgumentRange(index <= _count,
        "Index must be within the bounds of the List.", "index");

    unique_ptr<IEnumerator<T>> enumerator = collection.GetEnumerator();

    uintsize i = index;

    while (enumerator->MoveNext()) {
        this->Insert(i++, enumerator->GetCurrent());
    }
}

template <typename T>
void List<T>::RemoveRange(uintsize index, uintsize count)
{
    Validate_ArgumentRange(index <= _count,
        "Index cannot be greater than the size of the string/array/collection.", "index");
    Validate_ArgumentRange(count <= _count - index,
        "Count must refer to a location within the string/array/collection.", "count");

    uintsize size = sizeof(T);

    // Copy the contents of the buffer backward after index forward by length bytes.
    Memory::Copy(
        _array.Get(), (index + count) * sizeof(T),
        _array.Get(), count * sizeof(T),
        (_count - (index + count)) * sizeof(T));

    _count -= count;
    _version++;
}

template <typename T>
unique_ptr<T> List<T>::ToArray() const
{
    unique_ptr<T> copy = unique_ptr<T>(new T[_count]);

    Memory::Copy(_array.Get(), copy, _count * sizeof(T));

    return copy;
}

template <typename T>
void List<T>::TrimExcess()
{
    if (_count < (_capacity * 9) / 10) {
        this->SetCapacity(_count);
    }
}

/* IEnumerable */
template <typename T>
unique_ptr<IEnumerator<T>> List<T>::GetEnumerator() const
{
    return nullptr;
    //return ListEnumerator_New((const IReadOnlyList*)list, (ListEnumerator_GetVersionFunc)List<T>::GetVersion);
}

/* ICollection */
template <typename T>
uintsize List<T>::GetCount() const
{
    return _count;
}

template <typename T>
void List<T>::Add(const T &item)
{
    Validate_NotNull(item);

    this->Insert(_count, item);
}

template <typename T>
void List<T>::Clear()
{
    _count = 0;
    _version++;
}

template <typename T>
bool List<T>::Contains(const T &item) const
{
    return this->IndexOf(item) != InvalidIndex;
}

template <typename T>
void List<T>::CopyTo(T destination[]) const
{
    Validate_NotNull(destination);

    Memory_Copy(_array, destination, _count * sizeof(T));
}

template <typename T>
bool List<T>::Remove(const T &item)
{
    uintsize index = this->IndexOf(item);

    if (index != InvalidIndex) {
        this->RemoveAt(index);
    }

    return index != InvalidIndex;
}

/* IList */
template <typename T>
T &List<T>::operator[](uintsize index)
{
    Validate_ArgumentRange(index < _count, "Index must be within the bounds of the List.", "index");

    return _array[index];
}

template <typename T>
uintsize List<T>::IndexOf(const T &item) const
{
    uintsize count = _count;

    for (uintsize i = 0; i < count; i++) {
        if (_array[i] == item) {
            return i;
        }
    }

    return InvalidIndex;
}

template <typename T>
void List<T>::Insert(uintsize index, const T &item)
{
    Validate_NotNull(item);
    Validate_ArgumentRange(index <= _count,
        "Index must be within the bounds of the List.", "index");

    this->EnsureCapacity(list, UIntSize::CheckedAddition(_count, 1));

    byte *arr = _array;
    uintsize size = sizeof(T);
    uintsize i = index;
    uintsize length = _count;

    if (i < length) {
        // Move the contents of the array after index forward by 1 index.
        Memory::Copy(
            &arr[i * size],
            &arr[(i + 1) * size],
            (length - i) * size);
    }

    // Insert the item.
    Memory::Copy(item, &arr[i * size], size);

    _count++;
    _version++;
}

template <typename T>
void List<T>::RemoveAt(uintsize index)
{
    this->RemoveRange(index, 1);
}

/**************************************/
/* Internal function definitions      */
/**************************************/

template <typename T>
uintsize List<T>::GetVersion() const
{
    return _version;
}

/**************************************/
/* Private function definitions       */
/**************************************/

template <typename T>
void List<T>::EnsureCapacity(uintsize minCapacity)
{
    if (_capacity < minCapacity) {
        uintsize capacity;
        capacity = UIntSize::Min(_count * 2, InvalidIndex - 1);
        capacity = UIntSize::Max(capacity, minCapacity);
        capacity = UIntSize::Max(capacity, DefaultCapacity);

        this->SetCapacity(capacity);
    }
}

#endif
