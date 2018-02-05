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

#ifndef CFLAT_CORE_COLLECTIONS_ENUMERABLE_HPP
#define CFLAT_CORE_COLLECTIONS_ENUMERABLE_HPP

#include "CFlat/Collections/Enumerable.h"

#include "CFlat.h"
#include "CFlat/ExceptionType.h"
#include "CFlat/String.h"
#include "CFlat/Validate.h"

#include "CFlat/Collections/Array.h"
#include "CFlat/Collections/IReadOnlyCollection.h"

#include <utility>

namespace CFlat
{
    /* Enumerable */
    template <typename T>
    bool Enumerable::All(const IEnumerable<T> &enumerable, typename Functions<T>::Predicate predicate)
    {
        Validate_NotNull(predicate);

        bool result = true;
        unique_ptr<IEnumerator<T>> enumerator = enumerable.GetEnumerator();

        while (enumerator->MoveNext()) {
            if (!predicate(enumerator->GetCurrent())) {
                result = false;
                break;
            }
        }

        return result;
    }

    template <typename T>
    bool Enumerable::Any(const IEnumerable<T> &enumerable, typename  Functions<T>::Predicate predicate)
    {
        Validate_NotNull(predicate);

        bool result = false;
        unique_ptr<IEnumerator<T>> enumerator = enumerable.GetEnumerator();

        while (enumerator->MoveNext()) {
            if (predicate(enumerator->GetCurrent())) {
                result = true;
                break;
            }
        }

        return result;
    }

    template <typename T>
    uintsize Enumerable::Count(const IEnumerable<T> &enumerable)
    {
        uintsize count = 0;

        unique_ptr<IEnumerator<T>> enumerator = enumerable.GetEnumerator();

        while (enumerator->MoveNext()) {
            count++;
        }

        return count;
    }

    template <typename T>
    uintsize Enumerable::Count(const IReadOnlyCollection<T> &collection)
    {
        return collection.GetCount();
    }

    template <typename T>
    unique_ptr<IEnumerable<T>> Enumerable::Empty()
    {
        return unique_ptr<IEnumerable<T>>(new EmptyEnumerable<T>());
    }

    template <typename T>
    unique_ptr<IEnumerable<T>> Enumerable::Yield(T item)
    {
        return unique_ptr<IEnumerable<T>>(new YieldEnumerable<T>(std::move(item)));
    }

    template <typename T, typename TDeleter>
    unique_ptr<IEnumerable<T>> Enumerable::Concat(unique_ptr<IEnumerable<T>, TDeleter> &&first, unique_ptr<IEnumerable<T>, TDeleter> &&second)
    {
        Validate_NotNull(first);
        Validate_NotNull(second);

        return unique_ptr<IEnumerable<T>>(new ConcatTwoEnumerable<T>(
            shared_ptr<IEnumerable<T>>(std::move(first)),
            shared_ptr<IEnumerable<T>>(std::move(second))));
    }

    template <typename T>
    unique_ptr<IEnumerable<T>> Enumerable::Concat(shared_ptr<IEnumerable<T>> first, shared_ptr<IEnumerable<T>> second)
    {
        Validate_NotNull(first);
        Validate_NotNull(second);

        return unique_ptr<IEnumerable<T>>(new ConcatTwoEnumerable<T>(std::move(first), std::move(second)));
    }

    template <typename TSource, typename TResult>
    unique_ptr<IEnumerable<TResult>> Enumerable::SelectMany(IEnumerable<TSource> &enumerable, unique_ptr<IEnumerable<TResult>>(*selector)(const TSource&))
    {
        Validate_NotNull(selector);

        unique_ptr<List<TResult>> result = unique_ptr<List<TResult>>(new List<TResult>());
        unique_ptr<IEnumerator<TSource>> enumerator = enumerable.GetEnumerator();

        while (enumerator->MoveNext()) {
            unique_ptr<IEnumerable<TResult>> selected = selector(enumerator->GetCurrent());
            
            result->AddRange(*selected.Get());
        }

        return unique_ptr<IEnumerable<TResult>>(std::move(result));
    }

    /* Enumerable::EmptyEnumerable */
    template <typename T>
    Enumerable::EmptyEnumerable<T>::EmptyEnumerable()
    {
    }

    template <typename T>
    unique_ptr<IEnumerator<T>> Enumerable::EmptyEnumerable<T>::GetEnumerator() const
    {
        return unique_ptr<IEnumerator<T>>(new EmptyEnumerable<T>::Enumerator());
    }

    /* Enumerable::EmptyEnumerable::Enumerator */
    template <typename T>
    Enumerable::EmptyEnumerable<T>::Enumerator::Enumerator()
    {
    }

    template <typename T>
    const T &Enumerable::EmptyEnumerable<T>::Enumerator::GetCurrent() const
    {
        throw InvalidOperationException(String::Wrap("Enumeration has either not started or has already finished."));
    }

    template <typename T>
    bool Enumerable::EmptyEnumerable<T>::Enumerator::MoveNext()
    {
        return false;
    }

    template <typename T>
    void Enumerable::EmptyEnumerable<T>::Enumerator::Reset()
    {
    }

    /* Enumerable::YieldEnumerable */
    template <typename T>
    Enumerable::YieldEnumerable<T>::YieldEnumerable(T value) : _value(value)
    {
    }

    template <typename T>
    unique_ptr<IEnumerator<T>> Enumerable::YieldEnumerable<T>::GetEnumerator() const
    {
        return unique_ptr<IEnumerator<T>>(new YieldEnumerable<T>::Enumerator(std::move(_value)));
    }

    /* Enumerable::YieldEnumerable::Enumerator */
    template <typename T>
    Enumerable::YieldEnumerable<T>::Enumerator::Enumerator(T value) :_index(0), _value(value)
    {
    }

    template <typename T>
    const T &Enumerable::YieldEnumerable<T>::Enumerator::GetCurrent() const
    {
        Validate_State(_index > 0 && _index <= 1, "Enumeration has either not started or has already finished.");

        return _value;
    }

    template <typename T>
    bool Enumerable::YieldEnumerable<T>::Enumerator::MoveNext()
    {
        if (_index < 1) {
            _index++;

            return true;
        }
        else {
            _index = 2;

            return false;
        }
    }

    template <typename T>
    void Enumerable::YieldEnumerable<T>::Enumerator::Reset()
    {
        _index = 0;
    }

    /* Enumerable::ConcatTwoEnumerable */
    template <typename T>
    Enumerable::ConcatTwoEnumerable<T>::ConcatTwoEnumerable(shared_ptr<IEnumerable<T>> first, shared_ptr<IEnumerable<T>> second) :
        _first(std::move(first)),
        _second(std::move(second))
    {
        assert(_first);
        assert(_second);
    }

    template <typename T>
    unique_ptr<IEnumerator<T>> Enumerable::ConcatTwoEnumerable<T>::GetEnumerator() const
    {
        return unique_ptr<IEnumerator<T>>(new ConcatTwoEnumerable<T>::Enumerator(_first, _second));
    }

    /* Enumerable::ConcatTwoEnumerable::Enumerator */
    template <typename T>
    Enumerable::ConcatTwoEnumerable<T>::Enumerator::Enumerator(shared_ptr<IEnumerable<T>> first, shared_ptr<IEnumerable<T>> second) :
        _enumerators{ nullptr, nullptr },
        _index(0)
    {
        assert(first);
        assert(second);

        _enumerators[0] = first->GetEnumerator();
        _enumerators[1] = second->GetEnumerator();
    }

    template <typename T>
    bool Enumerable::ConcatTwoEnumerable<T>::Enumerator::NextEnumerator()
    {
        if (_index < 2) {
            _index++;

            return true;
        }
        else {
            _index = 3;

            return false;
        }
    }

    template <typename T>
    const T &Enumerable::ConcatTwoEnumerable<T>::Enumerator::GetCurrent() const
    {
        Validate_State(_index > 0 && _index <= 2, "Enumeration has either not started or has already finished.");

        // Return the current element of the current enumerator.
        return _enumerators[_index - 1]->GetCurrent();
    }

    template <typename T>
    bool Enumerable::ConcatTwoEnumerable<T>::Enumerator::MoveNext()
    {
        // If there is no current enumerator, move to the first one, or return false if we reached past the last enumerator.
        if (_index <= 0 || _index > 2) {
            if (!this->NextEnumerator()) return false;
        }

        // Move to the next element of the current enumerator, or move to the next enumerator if we reached past the end of
        // the current one.
        return _enumerators[_index - 1]->MoveNext() || (this->NextEnumerator(), this->MoveNext());
    }

    template <typename T>
    void Enumerable::ConcatTwoEnumerable<T>::Enumerator::Reset()
    {
        // Reset all enumerators.
        _enumerators[0]->Reset();
        _enumerators[1]->Reset();

        // Move to the first enumerator.
        _index = 0;
    }
}

#endif
