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

#include "CFlat/Language/Integer.h"

/* Forward declarations */
typedef struct IEnumerable IEnumerable;
typedef struct IEnumerator IEnumerator;

/* Macros */
/// <summary>
/// The maximum number of elements a <see cref="List"/> can hold.
/// </summary>
#define List_MaxCapacity int_MaxValue

/* Types */
/// <summary>
/// Represents a dynamically sized list of objects. Implements <see cref="IEnumerable"/>.
/// </summary>
typedef struct List List;

/* Functions */
/// <summary>
/// Allocates and initializes a new <see cref="List"/>.
///
/// The lifetime of the <see cref="List"/> should be managed with Object_Aquire() and Object_Release().
/// </summary>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <returns>Pointer to the newly allocated <see cref="List"/>.</returns>
List *List_New(uintsize elementSize);

/// <summary>
/// Allocates and initializes a new <see cref="List"/> using the given capacity.
///
/// The lifetime of the <see cref="List"/> should be managed with Object_Aquire() and Object_Release().
/// </summary>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="capacity">The initial capacity of the <see cref="List"/>.</param>
/// <returns>Pointer to the newly allocated <see cref="List"/>.</returns>
List *List_New_WithCapacity(uintsize elementSize, int capacity);

/// <summary>
/// Initializes the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
void List_Constructor(List *list, uintsize elementSize);

/// <summary>
/// Initializes the given <see cref="List"/> using the given capacity.
/// </summary>
/// <param name="list">Pointer to an uninitialized <see cref="List"/>.</param>
/// <param name="elementSize">The size in bytes of each element.</param>
/// <param name="capacity">The initial capacity of the <see cref="List"/>.</param>
void List_Constructor_WithCapacity(List *list, uintsize elementSize, int capacity);

/// <summary>
/// Destroys the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
void List_Destructor(List *list);

/// <summary>
/// Gets the capacity of the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>The capacity of the <see cref="List"/>.</returns>
int List_GetCapacity(const List *list);

/// <summary>
/// Sets the capacity of the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="capacity">The new capacity of the <see cref="List"/>.</param>
void List_SetCapacity(List *list, int capacity);

/// <summary>
/// Gets the number of elements in the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>The number of elements in the <see cref="List"/>.</returns>
int List_GetCount(const List *list);

/// <summary>
/// Gets the size in bytes of each element in the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>Tthe size in bytes of each element in the given <see cref="List"/>.</returns>
uintsize List_GetElementSize(const List *list);

/// <summary>
/// Adds the given element to the end of the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="lvalue">The value to append, must be an lvalue.</param>
#define List_Add(list, lvalue) List_AddRef(list, &lvalue)

/// <summary>
/// Adds the given element to the end of the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="value">Pointer to the value to append.</param>
void List_AddRef(List *list, const void *value);

/// <summary>
/// Adds the elements of the given collection to the end of the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="enumerable">
/// Pointer to an <see cref="IEnumerable"/> whose elements should be added to the end of the <see cref="List"/>.
/// </param>
void List_AddRange(List *list, IEnumerable *enumerable);

/// <summary>
/// Removes all elements from the specified <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
void List_Clear(List *list);

/// <summary>
/// Returns a <see cref="ListEnumerator"/> that iterates through the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <returns>A <see cref="ListEnumerator"/> that iterates through the given <see cref="List"/>.</returns>
IEnumerator *List_GetEnumerator(const List *list);

/// <summary>
/// Returns the element at the given index of the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The index of the element to return.</param>
/// <param name="type">The type of the element.</param>
#define List_Index(list, index, type) (*(type*)List_IndexRef(list, index))

/// <summary>
/// Returns a pointer to the element at the given index of the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The index of the element to return.</param>
void *List_IndexRef(const List *list, int index);

/// <summary>
/// Inserts the given element into the given <see cref="List"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The position where to insert <paramref name="value"/>.</param>
/// <param name="value">The value to append, must be an lvalue.</param>
#define List_Insert(list, index, value) List_InsertRef(list, index, &value)

/// <summary>
/// Inserts the given element into the given <see cref="List"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The position where to insert <paramref name="value"/>.</param>
/// <param name="value">Pointer to the value to append.</param>
void List_InsertRef(List *list, int index, const void *value);

/// <summary>
/// Inserts the elements of the given collection into the given <see cref="List"/> at the given index.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">The position where the new elements should be inserted.</param>
/// <param name="enumerable">
/// Pointer to an <see cref="IEnumerable"/> whose elements should be added to the end of the <see cref="List"/>.
/// </param>
void List_InsertRange(List *list, int index, IEnumerable *enumerable);

/// <summary>
/// Removes the element at the given index of the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="index">Index of the element to remove.</param>
void List_RemoveAt(List *list, int index);

/// <summary>
/// Removes the given range of elements from the given <see cref="List"/>.
/// </summary>
/// <param name="list">Pointer to a <see cref="List"/>.</param>
/// <param name="startIndex">The position where to start removing elements.</param>
/// <param name="count">The number of elements to remove.</param>
void List_RemoveRange(List *list, int startIndex, int count);

#ifdef CFLAT_CORE_INTERNAL
 #include "CFlat/Collections/List.internal.h"
#endif

#endif
