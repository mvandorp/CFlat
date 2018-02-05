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

//! @file Enumerable.h

#ifndef CFLAT_CORE_COLLECTIONS_ENUMERABLE_H
#define CFLAT_CORE_COLLECTIONS_ENUMERABLE_H

#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Integer.h"
#include "CFlat/Language/Pointers.h"

#include "CFlat/Collections/IEnumerable.h"
#include "CFlat/Collections/IEnumerator.h"

namespace CFlat {
    /* Forward declarations */
    template <typename T>
    class IReadOnlyCollection;

    /* Types */
    class Enumerable {
    public:
        /* Types */
        template <typename T>
        class EmptyEnumerable : public IEnumerable<T> {
        private:
            class Enumerator : public IEnumerator<T> {
            public:
                /* Constructors */
                inline Enumerator();

                /* Methods */
                inline const T &GetCurrent() const override;
                inline bool MoveNext() override;
                inline void Reset() override;
            };

        public:
            /* Constructors */
            inline EmptyEnumerable();

            /* Methods */
            inline unique_ptr<IEnumerator<T>> GetEnumerator() const;
        };

        template <typename T>
        class YieldEnumerable : public IEnumerable<T> {
        private:
            /* Fields */
            T _value;

            /* Types */
            class Enumerator : public IEnumerator<T> {
            private:
                int _index;
                T _value;

            public:
                /* Constructors */
                inline Enumerator(T value);

                /* Methods */
                inline const T &GetCurrent() const override;
                inline bool MoveNext() override;
                inline void Reset() override;
            };

        public:
            /* Constructors */
            inline YieldEnumerable(T value);

            /* Methods */
            inline unique_ptr<IEnumerator<T>> GetEnumerator() const;
        };

        template <typename T>
        class ConcatTwoEnumerable : public IEnumerable<T> {
        private:
            /* Fields */
            shared_ptr<IEnumerable<T>> _first;
            shared_ptr<IEnumerable<T>> _second;

            /* Types */
            class Enumerator : public IEnumerator<T> {
            private:
                /* Fields */
                unique_ptr<IEnumerator<T>> _enumerators[2];
                int _index;

                /* Methods */
                inline bool NextEnumerator();

            public:
                /* Constructors */
                inline Enumerator(shared_ptr<IEnumerable<T>> first, shared_ptr<IEnumerable<T>> second);

                /* Methods */
                inline const T &GetCurrent() const override;
                inline bool MoveNext() override;
                inline void Reset() override;
            };

        public:
            /* Constructors */
            inline ConcatTwoEnumerable(shared_ptr<IEnumerable<T>> first, shared_ptr<IEnumerable<T>> second);

            /* Methods */
            inline unique_ptr<IEnumerator<T>> GetEnumerator() const;
        };

    public:
        /* Constructors */
        Enumerable() = delete;

        /* Methods */
        /// <summary>
        /// Determines whether all elements of an <see cref="IEnumerable"/> satisfy a given predicate.
        /// </summary>
        /// <param name="enumerable">Pointer to an <see cref="IEnumerable"/>.</param>
        /// <param name="predicate">A <see cref="Predicate"/> to test each element for a condition.</param>
        /// <returns>
        ///     <see cref="true"/> if all elements of <paramref name="enumerable"/> satisfy <paramref name="predicate"/>;
        ///     otherwise <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="enumerable"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="predicate"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        template <typename T>
        static inline bool All(const IEnumerable<T> &enumerable, typename Functions<T>::Predicate predicate);

        /// <summary>
        /// Determines whether any element of an <see cref="IEnumerable"/> satisfies a given predicate.
        /// </summary>
        /// <param name="enumerable">Pointer to an <see cref="IEnumerable"/>.</param>
        /// <param name="predicate">A <see cref="Predicate"/> to test each element for a condition.</param>
        /// <returns>
        ///     <see cref="true"/> if any element of <paramref name="enumerable"/> satisfies <paramref name="predicate"/>;
        ///     otherwise <see cref="false"/>.
        /// </returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="enumerable"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="predicate"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        template <typename T>
        static inline bool Any(const IEnumerable<T> &enumerable, typename  Functions<T>::Predicate predicate);

        /// <summary>
        /// Determines the number of elements in an <see cref="IEnumerable"/>.
        /// </summary>
        /// <param name="enumerable">Pointer to an <see cref="IEnumerable"/>.</param>
        /// <returns>The number of elements in the <see cref="IEnumerable"/>.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="enumerable"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        template <typename T>
        static inline uintsize Count(const IEnumerable<T> &enumerable);

        /// <summary>
        /// Determines the number of elements in an <see cref="IEnumerable"/>.
        /// </summary>
        /// <param name="enumerable">Pointer to an <see cref="IEnumerable"/>.</param>
        /// <returns>The number of elements in the <see cref="IEnumerable"/>.</returns>
        /// <exception cref="::ArgumentNullException"><paramref name="enumerable"/> is <see cref="null"/>.</exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        template <typename T>
        static inline uintsize Count(const IReadOnlyCollection<T> &collection);

        /// <summary>
        /// Returns an empty <see cref="IEnumerable"/>.
        /// </summary>
        /// <returns>An empty <see cref="IEnumerable"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        template <typename T>
        static inline unique_ptr<IEnumerable<T>> Empty();

        /// <summary>
        /// Returns an <see cref="IEnumerable"/> containing a single <see cref="Object"/>.
        /// </summary>
        /// <param name="item">The <see cref="Object"/> contained in the <see cref="IEnumerable"/>.</param>
        /// <returns>An <see cref="IEnumerable"/> containing a single <see cref="Object"/>.</returns>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        template <typename T>
        static inline unique_ptr<IEnumerable<T>> Yield(T item);

        /// <summary>
        /// Concatenates two sequences.
        /// </summary>
        /// <param name="first">The first sequence to concatenate.</param>
        /// <param name="second">The second sequence to concatenate.</param>
        /// <returns>An <see cref="IEnumerable"/> that contains the concatenated elements of the two input sequences.</returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="first"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="second"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        template <typename T, typename TDeleter>
        static inline unique_ptr<IEnumerable<T>> Concat(unique_ptr<IEnumerable<T>, TDeleter> &&first, unique_ptr<IEnumerable<T>, TDeleter> &&second);

        /// <summary>
        /// Concatenates two sequences.
        /// </summary>
        /// <param name="first">The first sequence to concatenate.</param>
        /// <param name="second">The second sequence to concatenate.</param>
        /// <returns>An <see cref="IEnumerable"/> that contains the concatenated elements of the two input sequences.</returns>
        /// <exception cref="::ArgumentNullException">
        ///     <paramref name="first"/> is <see cref="null"/> <b>-or-</b>
        ///     <paramref name="second"/> is <see cref="null"/>.
        /// </exception>
        /// <exception cref="::OutOfMemoryException">There is insufficient memory available.</exception>
        template <typename T>
        static inline unique_ptr<IEnumerable<T>> Concat(shared_ptr<IEnumerable<T>> first, shared_ptr<IEnumerable<T>> second);

        template <typename TSource, typename TResult>
        static inline unique_ptr<IEnumerable<TResult>> SelectMany(IEnumerable<TSource> &enumerable, unique_ptr<IEnumerable<TResult>>(*selector)(const TSource&));
    };
}

#include "Enumerable.hpp"

#endif
