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

/**
 * @file List.h
 */

#ifndef CFLAT_CORE_COLLECTIONS_LIST_H
#define CFLAT_CORE_COLLECTIONS_LIST_H

#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Integer.h"

/* Forward declarations */
typedef struct ICollection ICollection;
typedef struct IEnumerable IEnumerable;
typedef struct IEnumerator IEnumerator;

/* Macros */
/// <summary>
/// The maximum number of elements a <see cref="List"/> can hold.
/// </summary>
#define List_MaxCapacity int_MaxValue

/* Types */
/// <summary>
/// Represents a dynamically sized list of objects. Implements <see cref="IList"/>.
/// </summary>
typedef struct List List;

/* Functions */
/// <summary>
/// Allocates and initializes a <see cref="List"/>.
///
/// The lifetime of the <see cref="List"/> should be managed with Object_Aquire() and Object_Release().
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <returns>Pointer to the newly allocated <see cref="List"/>.</returns>
List *List_New(uintsize elementSize);

/// <summary>
/// Allocates and initializes a <see cref="List"/> with the given capacity.
///
/// The lifetime of the <see cref="List"/> should be managed with Object_Aquire() and Object_Release().
/// </summary>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="capacity">The initial capacity of the <see cref="List"/>.</param>
/// <returns>Pointer to the newly allocated <see cref="List"/>.</returns>
List *List_New_WithCapacity(uintsize elementSize, int capacity);

/// <summary>
/// Allocates and initializes a <see cref="List"/> that contains the elements copied from the given collection.
///
/// The lifetime of the <see cref="List"/> should be managed with Object_Aquire() and Object_Release().
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/> whose elements are copied.</param>
/// <returns>Pointer to the newly allocated <see cref="List"/>.</returns>
List *List_New_FromEnumerable(uintsize elementSize, const IEnumerable *enumerable);

/// <summary>
/// Allocates and initializes a <see cref="List"/> that contains the elements copied from the given collection.
///
/// The lifetime of the <see cref="List"/> should be managed with Object_Aquire() and Object_Release().
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="collection">Pointer to an <see cref="ICollection"/> whose elements are copied.</param>
/// <returns>Pointer to the newly allocated <see cref="List"/>.</returns>
List *List_New_FromCollection(uintsize elementSize, const ICollection *collection);

/// <summary>
/// Initializes a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
void List_Constructor(List *list, uintsize elementSize);

/// <summary>
/// Initializes a <see cref="List"/> with the given capacity.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="capacity">The initial capacity of the <see cref="List"/>.</param>
void List_Constructor_WithCapacity(List *list, uintsize elementSize, int capacity);

/// <summary>
/// Initializes a <see cref="List"/> that contains the elements copied from the given collection.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="collection">Pointer to an <see cref="IEnumerable"/> whose elements are copied.</param>
void List_Constructor_FromEnumerable(List *list, uintsize elementSize, const IEnumerable *collection);

/// <summary>
/// Initializes a <see cref="List"/> that contains the elements copied from the given collection.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="collection">Pointer to an <see cref="ICollection"/> whose elements are copied.</param>
void List_Constructor_FromCollection(List *list, uintsize elementSize, const ICollection *collection);

/// <summary>
/// Destroys a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
void List_Destructor(List *list);

/// <summary>
/// Gets the capacity of a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>The capacity of the <see cref="List"/>.</returns>
int List_GetCapacity(const List *list);

/// <summary>
/// Sets the capacity of a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="capacity">The new capacity of the <see cref="List"/>.</param>
void List_SetCapacity(List *list, int capacity);

/// <summary>
/// Gets the size in bytes of each element in a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>Tthe size in bytes of each element in the <see cref="List"/>.</returns>
uintsize List_GetElementSize(const List *list);

/// <summary>
/// Adds the elements of the given collection to the end of a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="enumerable">
/// Pointer to an <see cref="IEnumerable"/> whose elements should be added to the end of the <see cref="List"/>.
/// </param>
void List_AddRange(List *list, const IEnumerable *enumerable);

/// <summary>
/// Inserts the elements of the given collection into a <see cref="List"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The position where the new elements should be inserted.</param>
/// <param name="enumerable">
/// Pointer to an <see cref="IEnumerable"/> whose elements should be inserted into the <see cref="List"/>.
/// </param>
void List_InsertRange(List *list, int index, const IEnumerable *enumerable);

/// <summary>
/// Removes the given range of elements from the a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="startIndex">The position where to start removing elements.</param>
/// <param name="count">The number of elements to remove.</param>
void List_RemoveRange(List *list, int startIndex, int count);

/* IEnumerable */
/// <summary>
/// Returns a pointer to an <see cref="IEnumerator"/> that iterates through the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>An <see cref="IEnumerator"/> that iterates through a <see cref="List"/>.</returns>
IEnumerator *List_GetEnumerator(const List *list);

/* ICollection */
/// <summary>
/// Gets the number of elements in a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>The number of elements in the <see cref="List"/>.</returns>
int List_GetCount(const List *list);

/// <summary>
/// Adds an item to a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="item">The item to add.</param>
#define List_Add(list, item) List_AddRef(list, &item)

/// <summary>
/// Adds an item to a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="item">The item to add.</param>
void List_AddRef(List *list, const void *item);

/// <summary>
/// Removes all elements from a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
void List_Clear(List *list);

/// <summary>
/// Determines whether a <see cref="List"/> contains the given value.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="item">The item to find.</param>
/// <param name="equals">An <see cref="EqualityPredicate"/> that is used to check elements for equality.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise <see cref="false"/>.</returns>
#define List_Contains(list, item, equals) List_ContainsRef(list, &item, equals)

/// <summary>
/// Determines whether a <see cref="List"/> contains the given value.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="item">The item to find.</param>
/// <param name="equals">An <see cref="EqualityPredicate"/> that is used to check elements for equality.</param>
/// <returns><see cref="true"/> if <paramref name="item"/> was found; otherwise <see cref="false"/>.</returns>
bool List_ContainsRef(const List *list, const void *item, EqualityPredicate equals);

/// <summary>
/// Copies the elements of a <see cref="List"/> to the given array.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="destination">
/// The array that is the destination of the elements copied from the <see cref="IList"/>.
/// </param>
/// <param name="destinationSize">The size in bytes of the array.</param>
void List_CopyTo(const List *list, void *destination, uintsize destinationSize);

/// <summary>
/// Removes the first occurance of the given item from a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="item">The item to remove.</param>
/// <param name="equals">An <see cref="EqualityPredicate"/> that is used to check elements for equality.</param>
/// <returns>
/// <see cref="true"/> if <paramref name="item"/> was successfully removed; otherwise <see cref="false"/>.
/// </returns>
#define List_Remove(list, item, equals) List_RemoveRef(list, &item, equals)

/// <summary>
/// Removes the first occurance of the given item from a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="item">The item to remove.</param>
/// <param name="equals">An <see cref="EqualityPredicate"/> that is used to check elements for equality.</param>
/// <returns>
/// <see cref="true"/> if <paramref name="item"/> was successfully removed; otherwise <see cref="false"/>.
/// </returns>
bool List_RemoveRef(List *list, const void *item, EqualityPredicate equals);

/* IList */
/// <summary>
/// Gets the item at the given index of a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="List"/>.</returns>
#define List_GetItem(list, index, type) (*(type*)List_GetItemRef(list, index))

/// <summary>
/// Gets the item at the given index of a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The index of the element to retrieve.</param>
/// <returns>The item at the given index of the <see cref="List"/>.</returns>
void *List_GetItemRef(const List *list, int index);

/// <summary>
/// Replaces the item at the given index of a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index.</param>
#define List_SetItem(list, index, item) List_SetItemRef(list, index, &item)

/// <summary>
/// Replaces the item at the given index of a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The index of the element to replace.</param>
/// <param name="item">The new value for the element at the given index.</param>
void List_SetItemRef(List *list, int index, const void *item);

/// <summary>
/// Determines the index of the given item in a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="item">The item to find.</param>
/// <param name="equals">An <see cref="EqualityPredicate"/> that is used to check elements for equality.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise -1.</returns>
#define List_IndexOf(list, item, equals) List_IndexOfRef(list, &item, equals)

/// <summary>
/// Determines the index of the given item in a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="item">The item to find.</param>
/// <param name="equals">An <see cref="EqualityPredicate"/> that is used to check elements for equality.</param>
/// <returns>The index of <paramref name="item"/> if found; otherwise -1.</returns>
int List_IndexOfRef(const List *list, const void *item, EqualityPredicate equals);

/// <summary>
/// Inserts an item into a <see cref="List"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The index at which <paramref name="item"/> should be inserted.</param>
/// <param name="item">The item to insert.</param>
#define List_Insert(list, index, item) List_InsertRef(list, index, &item)

/// <summary>
/// Inserts an item into a <see cref="List"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The index at which <paramref name="item"/> should be inserted.</param>
/// <param name="item">The item to insert.</param>
void List_InsertRef(List *list, int index, const void *item);

/// <summary>
/// Removes the element at the given index of a <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The index of the element to remove.</param>
void List_RemoveAt(List *list, int index);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/Collections/List.internal.h"
#endif

#endif
