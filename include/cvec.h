/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/** \file include/cvec.h
 * \brief Public header file for the cvec library.
 * \details This file contains the typedef and the public function declarations
 * for the cvec library. */

#ifndef CVEC_H
#define CVEC_H

#include <stddef.h> /* for size_t */

/** Opaque handle for the vector object. */
typedef struct vec vec_t;

#ifdef __cplusplus
extern "C" {
#endif

/** Returns the default capacity.
 * \return The default capacity. */
size_t vec_default_capacity();

/** Creates a new pointer for a specific type.
 * \param sizeof_type The size of the type that's meant to be stored 
 * in the vector.
 * \return A pointer to the allocated vector. */
vec_t *vec_new(size_t sizeof_type);

/** Returns the the length of a vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The length of the vector or (size_t)-1 on failure. */
size_t vec_len(const vec_t *vec);

/** Returns the the size of a vector's type.
 * \param vec A pointer to the vector to be accessed. 
 * \return The size of the vector's type or (size_t)-1 on failure. */
size_t vec_size(const vec_t *vec);

/** Returns the the capacity of a vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The capacity of the vector or (size_t)-1 on failure. */
size_t vec_capacity(const vec_t *vec);

/** Deletes a vector instance.
 * \param vec A pointer to the vector to be deleted. */
void vec_del(vec_t *vec);

/** Returns a const pointer to a vector item.
 * \param vec A pointer to the vector to be accessed.
 * \param index The index of the element to be accessed. 
 * \return A const pointer to the item. */
const void *vec_view(const vec_t *vec, size_t index);

/** Append an item at the end of the vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be appended.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void vec_push_back(vec_t *vec, void *value, size_t sizeof_type);

/** Removes the last item of a vector.
 * \param vec A pointer to the vector to be modified. */
void vec_pop_back(vec_t *vec);

/** Prepends an item at the beginning of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be prepended.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void vec_push_front(vec_t *vec, void *value, size_t sizeof_type);

/** Removes the first item of a vector.
 * \param vec A pointer to the vector to be modified. */
void vec_pop_front(vec_t *vec);

/** Appends an array at the end of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param arr The array to be appended. 
 * \param len The length of the array. 
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void vec_append(vec_t *vec, void *arr, size_t len, size_t sizeof_type);

/** Prepends an array at the beginning of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param arr The array to be prepended. 
 * \param len The length of the array. 
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void vec_prepend(vec_t *vec, void *arr, size_t len, size_t sizeof_type);

/** Removes an item of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The item's index. */
void vec_remove(vec_t *vec, size_t index);

/** Inserts an item into a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The index where the item is to be inserted.
 * \param value A pointer to the value to be inserted.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void vec_insert(vec_t *vec, size_t index, void *value, size_t sizeof_type);

/** Replaces an item in a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The index where the item is to be replaced.
 * \param value A pointer to the value to be inserted.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void vec_replace(vec_t *vec, size_t index, void *value, size_t sizeof_type);

/** Replaces a range of items in a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The index where the new array is to be inserted.
 * \param arr The new array to be inserted.
 * \param len The length of the array.
 * \param range The number of items to be replaced.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void vec_replace_range(
	vec_t *vec, size_t index, void *arr,
	size_t len, size_t range, size_t sizeof_type);

/** Returns a string containing the latest error information if exists or 
 * NULL if it does not. */
const char *vec_get_error();

#ifdef __cplusplus
}
#endif

#endif
