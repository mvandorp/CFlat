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

//! @file List.h

#ifndef CFLAT_CORE_COLLECTIONS_LIST_H
#define CFLAT_CORE_COLLECTIONS_LIST_H

#include "CFlat.h"
#include "CFlat/Memory.h"
#include "CFlat/Validate.h"
#include "CFlat/Collections/ICollection.h"
#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"
#include "CFlat/Collections/IList.h"

#include <type_traits>
#include <utility>

namespace CFlat {
    /// <summary>
    /// Represents a dynamically sized list of objects. Implements <see cref="IList"/>.
    /// </summary>
    template <typename T>
    class List : public IList<T> {
    private:
        shared_ptr<T[]> _array;
        uintsize _capacity;
        uintsize _count;
        shared_ptr<uintsize> _version;

        inline void EnsureCapacity(uintsize minCapacity)
        {
            if (_capacity < minCapacity) {
                uintsize capacity;
                capacity = UIntSize::Min(_count * 2, InvalidIndex - 1);
                capacity = UIntSize::Max(capacity, minCapacity);
                capacity = UIntSize::Max(capacity, DefaultCapacity);

                this->SetCapacity(capacity);
            }
        }

        inline void CopyTo(T[], std::false_type) const
        {
            throw NotSupportedException();
        }

        inline void CopyTo(T destination[], std::true_type) const
        {
            Validate_NotNull(destination);

            for (uintsize i = 0; i < _count; i++) {
                destination[i] = _array[i];
            }
        }

        class Enumerator : public IEnumerator<T> {
        private:
            shared_ptr<T[]> _array;
            shared_ptr<uintsize> _listVersion;
            uintsize _count;
            uintsize _index;
            uintsize _version;

        public:
            inline Enumerator(const List<T> *list) :
                _array(list->_array),
                _listVersion(list->_version),
                _count(list->_count),
                _index(0),
                _version(*list->_version)
            {
            }

            inline const T& GetCurrent() const override
            {
                Validate_State(
                    _version == *_listVersion,
                    "Collection was modified; enumeration operation may not execute.");
                Validate_State(
                    _index > 0 &&
                    _index <= _count,
                    "Enumeration has either not started or has already finished.");

                return _array[_index - 1];
            }

            inline bool MoveNext() override
            {
                Validate_State(
                    _version == *_listVersion,
                    "Collection was modified; enumeration operation may not execute.");

                if (_index < _count) {
                    _index++;

                    return true;
                }
                else {
                    _index = UIntSize::CheckedAddition(_count, 1);

                    return false;
                }
            }

            inline void Reset() override
            {
                Validate_State(
                    _version == *_listVersion,
                    "Collection was modified; enumeration operation may not execute.");

                _index = 0;
            }
        };

    public:
        static const uintsize DefaultCapacity = 4;

        /* Constructors */
        /// <summary>
        /// Initializes a <see cref="List"/>.
        /// </summary>
        /// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
        /// <param name="elementSize">The size in bytes of each element.</param>
        /// <param name="equals">
        ///     An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
        /// </param>
        /// <exception cref="::ArgumentOutOfRangeException"><paramref name="elementSize"/> is 0.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline List() : List(4)
        {
        }

        inline List(const List<T> &list) : List(list._capacity)
        {
            for (uintsize i = 0; i < list._count; i++) {
                _array[i] = list._array[i];
            }
        }

        inline List(List<T> &&list) :
            _array(nullptr),
            _capacity(0),
            _count(0),
            _version(new uintsize(0))
        {
            std::swap(_array, list._array);
            std::swap(_capacity, list._capacity);
            std::swap(_count, list._count);
            std::swap(_version, list._version);
        }

        /// <summary>
        /// Initializes a <see cref="List"/> with the given capacity.
        /// </summary>
        /// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
        /// <param name="elementSize">The size in bytes of each element.</param>
        /// <param name="equals">
        ///     An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
        /// </param>
        /// <param name="capacity">The initial capacity of the <see cref="List"/>.</param>
        /// <exception cref="::ArgumentOutOfRangeException"><paramref name="elementSize"/> is 0.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline List(uintsize capacity) :
            _array(nullptr),
            _capacity(0),
            _count(0),
            _version(new uintsize(0))
        {
            Validate_ArgumentRange(capacity != InvalidIndex,
                "Capacity cannot be equal to the value of InvalidIndex.", "capacity");

            this->SetCapacity(capacity);
        }

        /// <summary>
        /// Initializes a <see cref="List"/> that contains the elements copied from the given collection.
        /// </summary>
        /// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
        /// <param name="elementSize">The size in bytes of each element.</param>
        /// <param name="equals">
        ///     An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
        /// </param>
        /// <param name="collection">Pointer to an <see cref="IEnumerable"/> whose elements are copied.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
        /// <exception cref="::ArgumentOutOfRangeException"><paramref name="elementSize"/> is 0.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline List(const IEnumerable<T> &collection) : List()
        {
            this->AddRange(collection);
        }

        /// <summary>
        /// Initializes a <see cref="List"/> that contains the elements copied from the given collection.
        /// </summary>
        /// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
        /// <param name="elementSize">The size in bytes of each element.</param>
        /// <param name="equals">
        ///     An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
        /// </param>
        /// <param name="collection">Pointer to an <see cref="ICollection"/> whose elements are copied.</param>
        /// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
        /// <exception cref="::ArgumentOutOfRangeException"><paramref name="elementSize"/> is 0.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline List(const ICollection<T> &collection) : List(collection.GetCount())
        {
            this->AddRange(collection);
        }

        /* Destructor */
        /// <summary>
        /// Destroys a <see cref="List"/>.
        /// </summary>
        inline virtual ~List()
        {
        }

        inline List &operator=(const List<T> &list)
        {
            if (this != std::addressof(list)) {
                this->EnsureCapacity(list._capacity);

                for (uintsize i = 0; i < list._count; i++) {
                    _array[i] = list._array[i];
                }

                _count = list._count;
                (*_version)++;
            }

            return *this;
        }

        inline List &operator=(List<T> &&list)
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
        /// <summary>
                /// Gets the capacity of a <see cref="List"/>.
                /// </summary>
                /// <returns>The capacity of the <see cref="List"/>.</returns>
        inline uintsize GetCapacity() const
        {
            return _capacity;
        }

        /// <summary>
        /// Sets the capacity of a <see cref="List"/>.
        /// </summary>
        /// <param name="capacity">The new capacity of the <see cref="List"/>.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="capacity"/> is less than the number of elements in <paramref name="list"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline void SetCapacity(uintsize capacity)
        {
            Validate_ArgumentRange(capacity >= _count,
                "Capacity cannot be smaller than the current length.", "capacity");
            Validate_ArgumentRange(capacity != InvalidIndex,
                "Capacity cannot be equal to the value of InvalidIndex.", "capacity");

            if (capacity != _capacity) {
                shared_ptr<T[]> newArray = shared_ptr<T[]>(new T[capacity]);

                // TODO: Exception safe, what if exception happens
                for (uintsize i = 0; i < _count; i++) {
                    newArray[i] = std::move(_array[i]);
                }

                _array = std::move(newArray);
                _capacity = capacity;
            }
        }

        /* Methods */
        /// <summary>
        /// Determines whether a <see cref="List"/> contains the given value.
        /// </summary>
        /// <param name="list">Pointer to a <see cref="List"/>.</param>
        /// <param name="item">The item to find.</param>
        /// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="item"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::InvalidOperationException">
        ///     <paramref name="list"/> does not have an equality predicate set.
        /// </exception>
        inline bool Contains(const T &item) const override
        {
            return this->IndexOf(item) != InvalidIndex;
        }

        /// <summary>
        /// Adds the elements of the given collection to the end of a <see cref="List"/>.
        /// </summary>
        /// <param name="collection">
        ///     Pointer to an <see cref="IEnumerable"/> whose elements should be added to the end of the <see cref="List"/>.
        /// </param>
        /// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline void AddRange(const IEnumerable<T> &collection)
        {
            this->InsertRange(_count, collection);
        }

        /// <summary>
        /// Inserts the elements of the given collection into a <see cref="List"/> at the given index.
        /// </summary>
        /// <param name="index">The position where the new elements should be inserted.</param>
        /// <param name="collection">
        ///     Pointer to an <see cref="IEnumerable"/> whose elements should be inserted into the <see cref="List"/>.
        /// </param>
        /// <exception cref="::ArgumentNullException"><paramref name="collection"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline void InsertRange(uintsize index, const IEnumerable<T> &collection)
        {
            Validate_ArgumentRange(index <= _count,
                "Index must be within the bounds of the List.", "index");

            unique_ptr<IEnumerator<T>> enumerator = collection.GetEnumerator();

            uintsize i = index;

            while (enumerator->MoveNext()) {
                this->Insert(i++, enumerator->GetCurrent());
            }
        }

        /// <summary>
        /// Removes the given range of elements from the a <see cref="List"/>.
        /// </summary>
        /// <param name="index">The position where to start removing elements.</param>
        /// <param name="count">The number of elements to remove.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> and <paramref name="count"/> do not denote a valid range of elements in
        ///     <paramref name="list"/>.
        /// </exception>
        inline void RemoveRange(uintsize index, uintsize count)
        {
            Validate_ArgumentRange(index <= _count,
                "Index cannot be greater than the size of the string/array/collection.", "index");
            Validate_ArgumentRange(count <= _count - index,
                "Count must refer to a location within the string/array/collection.", "count");

            // Move the contents of the array after 'index + count' down by 'count' places.
            for (uintsize i = index + count; i < _count; i++) {
                _array[i - index] = std::move(_array[i]);
            }

            _count -= count;
            (*_version)++;
        }

        /// <summary>
        /// Copies the elements of a <see cref="List"/> to the given array.
        /// </summary>
        /// <param name="destination">
        ///     The array that is the destination of the elements copied from the <see cref="List"/>.
        /// </param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="destination"/> is <see cref="null"/>.
        /// </exception>
        inline void CopyTo(T destination[]) const override
        {
            this->CopyTo(destination, std::is_copy_assignable<T>());
        }

        /// <summary>
        /// Copies the elements of a <see cref="List"/> to a new array.
        /// </summary>
        /// <returns>An array containing copies of the elements of <paramref name="list"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline shared_ptr<T[]> ToArray() const
        {
            shared_ptr<T[]> copy = shared_ptr<T[]>(new T[_count]);

            for (uintsize i = 0; i < _count; i++) {
                copy[i] = _array[i];
            }

            return copy;
        }

        /// <summary>
        /// Sets the capacity to the actual number of elements in the <see cref="List"/>, if that number is less than a treshold
        /// value.
        /// </summary>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline void TrimExcess()
        {
            if (_count < (_capacity * 9) / 10) {
                this->SetCapacity(_count);
            }
        }

        /* IEnumerable */
        /// <summary>
        /// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="List"/>.
        /// </summary>
        /// <returns>An <see cref="IEnumerator"/> that iterates through a <see cref="List"/>.</returns>
        inline unique_ptr<IEnumerator<T>> GetEnumerator() const override
        {
            return unique_ptr<IEnumerator<T>>(new List<T>::Enumerator(this));
        }

        /* ICollection */
        /// <summary>
                /// Gets the number of elements in a <see cref="List"/>.
                /// </summary>
                /// <returns>The number of elements in the <see cref="List"/>.</returns>
        inline uintsize GetCount() const override
        {
            return _count;
        }

        /// <summary>
        /// Adds an item to a <see cref="List"/>.
        /// </summary>
        /// <param name="list">Pointer to a <see cref="List"/>.</param>
        /// <param name="item">The item to add.</param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="item"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline void Add(T item) override
        {
            this->Insert(_count, std::move(item));
        }

        /// <summary>
        /// Removes all elements from a <see cref="List"/>.
        /// </summary>
        inline void Clear() override
        {
            _count = 0;
            (*_version)++;
        }

        /// <summary>
        /// Removes the first occurance of the given item from a <see cref="List"/>.
        /// </summary>
        /// <param name="list">Pointer to a <see cref="List"/>.</param>
        /// <param name="item">The item to remove.</param>
        /// <returns>
        ///     <see cref="true"/> if <paramref name="item"/> was successfully removed; otherwise, <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="item"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::InvalidOperationException">
        ///     <paramref name="list"/> does not have an equality predicate set.
        /// </exception>
        inline bool Remove(const T &item) override
        {
            uintsize index = this->IndexOf(item);

            if (index != InvalidIndex) {
                this->RemoveAt(index);
            }

            return index != InvalidIndex;
        }

        /* IList */
        /// <summary>
        /// Gets the item at the given index of a <see cref="List"/>.
        /// </summary>
        /// <remarks>
        ///     The returned pointer shall no longer be dereferenced after the first call to a function that modifies
        ///     <paramref name="list"/>.
        /// </remarks>
        /// <param name="list">Pointer to a <see cref="List"/>.</param>
        /// <param name="index">The index of the element to retrieve.</param>
        /// <returns>The item at the given index of the <see cref="List"/>.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="list"/> is <see cref="null"/>.</exception>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
        /// </exception>
        inline T& operator[](uintsize index) override
        {
            Validate_ArgumentRange(index < _count, "Index must be within the bounds of the List.", "index");

            return _array[index];
        }

        inline const T &GetItem(uintsize index) const override
        {
            Validate_ArgumentRange(index < _count, "Index must be within the bounds of the List.", "index");

            return _array[index];
        }

        inline void SetItem(uintsize index, T item) override
        {
            Validate_ArgumentRange(index < _count, "Index must be within the bounds of the List.", "index");

            _array[index] = std::move(item);
        }

        /// <summary>
        /// Determines the index of the given item in a <see cref="List"/>.
        /// </summary>
        /// <param name="list">Pointer to a <see cref="List"/>.</param>
        /// <param name="item">The item to find.</param>
        /// <returns>The index of <paramref name="item"/> if found; otherwise <see cref="InvalidIndex"/>.</returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="item"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::InvalidOperationException">
        ///     <paramref name="list"/> does not have an equality predicate set.
        /// </exception>
        inline uintsize IndexOf(const T &item) const override
        {
            uintsize count = _count;

            for (uintsize i = 0; i < count; i++) {
                if (_array[i] == item) {
                    return i;
                }
            }

            return InvalidIndex;
        }

        /// <summary>
        /// Inserts an item into a <see cref="List"/> at the given index.
        /// </summary>
        /// <param name="list">Pointer to a <see cref="List"/>.</param>
        /// <param name="index">The index at which <paramref name="item"/> should be inserted.</param>
        /// <param name="item">The item to insert.</param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="list"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="item"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is greater than the number of elements in <paramref name="list"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline void Insert(uintsize index, T item) override
        {
            Validate_ArgumentRange(index <= _count,
                "Index must be within the bounds of the List.", "index");

            this->EnsureCapacity(UIntSize::CheckedAddition(_count, 1));

            if (index < _count) {
                // Move the contents of the array after index up by 1 index.
                for (uintsize i = _count; i-- > index; ) {
                    _array[i] = std::move(_array[i - 1]);
                }
            }

            // Insert the item.
            _array[index] = std::move(item);

            _count++;
            (*_version)++;
        }

        /// <summary>
        /// Removes the element at the given index of a <see cref="List"/>.
        /// </summary>
        /// <param name="index">The index of the element to remove.</param>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="list"/>.
        /// </exception>
        inline void RemoveAt(uintsize index) override
        {
            this->RemoveRange(index, 1);
        }
    };
}

#endif
