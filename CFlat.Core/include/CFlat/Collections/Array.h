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

//! @file Array.h

#ifndef CFLAT_CORE_COLLECTIONS_ARRAY_H
#define CFLAT_CORE_COLLECTIONS_ARRAY_H

#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IReadOnlyList.h"
#include "CFlat/Language/Integer.h"

namespace CFlat
{
    template <typename T>
    class Array : public IReadOnlyList<T> {
    private:
        shared_ptr<T> _array;
        uintsize _length;

        inline void CopyTo(T destination[], std::false_type) const;
        inline void CopyTo(T destination[], std::true_type) const;

        class Enumerator : public IEnumerator<T> {
        private:
            shared_ptr<T> _array;
            uintsize _length;
            uintsize _index;

        public:
            inline Enumerator(const Array<T> *list);

            inline const T& GetCurrent() const override;

            inline bool MoveNext() override;

            inline void Reset() override;
        };

    public:
        /// <summary>
        /// Initializes an <see cref="Array"/>.
        /// </summary>
        /// <param name="array">Pointer to an uninitialized <see cref="Array"/>.</param>
        /// <param name="source">The source array.</param>
        /// <param name="length">The number of elements in the array.</param>
        /// <param name="elementSize">The size in bytes of each element.</param>
        /// <param name="equals">
        ///     An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
        /// </param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="source"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::ArgumentOutOfRangeException"><paramref name="elementSize"/> is 0.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline Array(uintsize length);

        /// <summary>
        /// Initializes an <see cref="Array"/>.
        /// </summary>
        /// <param name="array">Pointer to an uninitialized <see cref="Array"/>.</param>
        /// <param name="source">The source array.</param>
        /// <param name="length">The number of elements in the array.</param>
        /// <param name="elementSize">The size in bytes of each element.</param>
        /// <param name="equals">
        ///     An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
        /// </param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="source"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::ArgumentOutOfRangeException"><paramref name="elementSize"/> is 0.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline Array(unique_ptr<T> &&source, uintsize length);

        /// <summary>
        /// Initializes an <see cref="Array"/>.
        /// </summary>
        /// <param name="array">Pointer to an uninitialized <see cref="Array"/>.</param>
        /// <param name="source">The source array.</param>
        /// <param name="length">The number of elements in the array.</param>
        /// <param name="elementSize">The size in bytes of each element.</param>
        /// <param name="equals">
        ///     An <see cref="EqualityPredicate"/> that is used to check elements for equality, or <see cref="null"/>.
        /// </param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="source"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::ArgumentOutOfRangeException"><paramref name="elementSize"/> is 0.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        inline Array(shared_ptr<T> source, uintsize length);

        inline T &operator[](uintsize index);

        inline T* GetData() const;

        /// <summary>
        /// Replaces the item at the given index of an <see cref="Array"/>.
        /// </summary>
        /// <param name="array">Pointer to an <see cref="Array"/>.</param>
        /// <param name="index">The index of the element to replace.</param>
        /// <param name="item">The new value for the element at the given index.</param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="item"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
        /// </exception>
        inline void SetItem(uintsize index, T item);

        inline static Array<T> Wrap(T source[], uintsize length);

        inline static unique_ptr<Array<T>> WrapPointer(T source[], uintsize length);

        /* IEnumerable */
        /// <summary>
        /// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="Array"/>.
        /// </summary>
        /// <param name="array">Pointer to an <see cref="Array"/>.</param>
        /// <returns>An <see cref="IEnumerator"/> that iterates through an <see cref="Array"/>.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
        inline unique_ptr<IEnumerator<T>> GetEnumerator() const override;

        /* IReadOnlyCollection */
        /// <summary>
        /// Gets the number of elements in an <see cref="Array"/>.
        /// </summary>
        /// <param name="array">Pointer to an <see cref="Array"/>.</param>
        /// <returns>The number of elements in the <see cref="Array"/>.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
        inline uintsize GetCount() const override;

        /// <summary>
        /// Determines whether an <see cref="Array"/> contains the given value.
        /// </summary>
        /// <param name="array">Pointer to an <see cref="Array"/>.</param>
        /// <param name="item">The item to find.</param>
        /// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise, <see cref="false"/>.</returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="item"/> is <see cref="null"/>.
        /// </exception>
        inline bool Contains(const T &item) const override;

        /// <summary>
        /// Copies the elements of an <see cref="Array"/> to the given array.
        /// </summary>
        /// <param name="array">Pointer to an <see cref="Array"/>.</param>
        /// <param name="destination">
        ///     The array that is the destination of the elements copied from the <see cref="Array"/>.
        /// </param>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="destination"/> is <see cref="null"/>.
        /// </exception>
        inline void CopyTo(T destination[]) const override;

        /* IReadOnlyList */
        /// <summary>
        /// Gets the item at the given index of an <see cref="Array"/>.
        /// </summary>
        /// <remarks>
        ///     The returned pointer shall no longer be dereferenced after the first call to a function that modifies
        ///     <paramref name="array"/>.
        /// </remarks>
        /// <param name="array">Pointer to an <see cref="Array"/>.</param>
        /// <param name="index">The index of the element to retrieve.</param>
        /// <returns>The item at the given index of the <see cref="Array"/>.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="array"/> is <see cref="null"/>.</exception>
        /// <exception cref="::ArgumentOutOfRangeException">
        ///     <paramref name="index"/> is equal to or greater than the number of elements in <paramref name="array"/>.
        /// </exception>
        inline const T &GetItem(uintsize index) const override;

        /// <summary>
        /// Determines the index of the given item in an <see cref="Array"/>.
        /// </summary>
        /// <param name="array">Pointer to an <see cref="Array"/>.</param>
        /// <param name="item">The item to find.</param>
        /// <returns>The index of <paramref name="item"/> if found; otherwise <see cref="InvalidIndex"/>.</returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="array"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="item"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::InvalidOperationException">
        ///     <paramref name="array"/> does not have an equality predicate set.
        /// </exception>
        inline uintsize IndexOf(const T &item) const override;
    };
}

#include "Array.hpp"

#endif
