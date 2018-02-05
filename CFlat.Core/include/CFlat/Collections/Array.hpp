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

#ifndef CFLAT_CORE_COLLECTIONS_ARRAY_HPP
#define CFLAT_CORE_COLLECTIONS_ARRAY_HPP

#include "CFlat/Collections/Array.h"

#include "CFlat.h"
#include "CFlat/Validate.h"

#include <type_traits>
#include <utility>

namespace CFlat
{
    template <typename T>
    Array<T>::Array(uintsize length) : _array(new T[length]), _length(length)
    {
    }

    template <typename T>
    Array<T>::Array(unique_ptr<T> &&source, uintsize length) : _array(std::move(source)), _length(length)
    {
    }

    template <typename T>
    Array<T>::Array(shared_ptr<T> source, uintsize length) : _array(source), _length(length)
    {
    }

    template <typename T>
    void Array<T>::CopyTo(T[], std::false_type) const
    {
        throw NotSupportedException();
    }

    template <typename T>
    void Array<T>::CopyTo(T destination[], std::true_type) const
    {
        Validate_NotNull(destination);

        for (uintsize i = 0; i < _length; i++) {
            destination[i] = _array[i];
        }
    }

    template <typename T>
    T &Array<T>::operator[](uintsize index)
    {
        Validate_ArgumentRange(index < _length, "Index must be within the bounds of the array.", "index");

        return _array[index];
    }

    template <typename T>
    T* Array<T>::GetData() const
    {
        return _array.Get();
    }

    template <typename T>
    void Array<T>::SetItem(uintsize index, T item)
    {
        Validate_ArgumentRange(index < _length, "Index must be within the bounds of the array.", "index");

        _array[index] = std::move(item);
    }

    template <typename T>
    Array<T> Array<T>::Wrap(T source[], uintsize length)
    {
        return Array(shared_ptr<T>(source, nullptr), length);
    }

    template <typename T>
    unique_ptr<Array<T>> Array<T>::WrapPointer(T source[], uintsize length)
    {
        if (source == nullptr) { return nullptr; }

        return unique_ptr<Array<T>>(Array(shared_ptr<T>(source, nullptr), length));
    }

    /* IEnumerable */
    template <typename T>
    unique_ptr<IEnumerator<T>> Array<T>::GetEnumerator() const
    {
        return unique_ptr<IEnumerator<T>>(new Enumerator(this));
    }

    /* IReadOnlyCollection */
    template <typename T>
    uintsize Array<T>::GetCount() const
    {
        return _length;
    }

    template <typename T>
    bool Array<T>::Contains(const T &item) const
    {
        return this->IndexOf(item) != InvalidIndex;
    }

    template <typename T>
    void Array<T>::CopyTo(T destination[]) const
    {
        this->CopyTo(destination, std::is_copy_assignable<T>());
    }

    /* IReadOnlyList */
    template <typename T>
    const T &Array<T>::GetItem(uintsize index) const
    {
        Validate_ArgumentRange(index < _length, "Index must be within the bounds of the List.", "index");

        return _array[index];
    }

    template <typename T>
    uintsize Array<T>::IndexOf(const T &item) const
    {
        uintsize count = _length;

        for (uintsize i = 0; i < count; i++) {
            if (_array[i] == item) {
                return i;
            }
        }

        return InvalidIndex;
    }

    /* Array::Enumerator*/
    template <typename T>
    Array<T>::Enumerator::Enumerator(const Array<T> *list) :
        _array(list->_array),
        _length(list->_length),
        _index(0)
    {
    }

    template <typename T>
    const T& Array<T>::Enumerator::GetCurrent() const
    {
        Validate_State(
            _index > 0 &&
            _index <= _length,
            "Enumeration has either not started or has already finished.");

        return _array[_index - 1];
    }

    template <typename T>
    bool Array<T>::Enumerator::MoveNext()
    {
        if (_index < _length) {
            _index++;

            return true;
        }
        else {
            _index = UIntSize::CheckedAddition(_length, 1);

            return false;
        }
    }

    template <typename T>
    void Array<T>::Enumerator::Reset()
    {
        _index = 0;
    }
}

#endif
