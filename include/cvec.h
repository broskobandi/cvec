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
typedef struct cvec cvec_t;

#ifdef __cplusplus
extern "C" {
#endif


/** Returns the default capacity.
 * \return The default capacity. */
size_t cvec_default_capacity();

/** Creates a new pointer for a specific type.
 * \param sizeof_type The size of the type that's meant to be stored 
 * in the vector.
 * \return A pointer to the allocated vector. */
cvec_t *cvec_new(size_t sizeof_type);

/** Returns the the length of a vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The length of the vector or (size_t)-1 on failure. */
size_t cvec_len(const cvec_t *vec);

/** Returns the the size of a vector's type.
 * \param vec A pointer to the vector to be accessed. 
 * \return The size of the vector's type or (size_t)-1 on failure. */
size_t cvec_size(const cvec_t *vec);

/** Returns the the capacity of a vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The capacity of the vector or (size_t)-1 on failure. */
size_t cvec_capacity(const cvec_t *vec);

/** Deletes a vector instance.
 * \param vec A pointer to the vector to be deleted. */
void cvec_del(cvec_t *vec);

/** Returns a const pointer to a vector item.
 * \param vec A pointer to the vector to be accessed.
 * \param index The index of the element to be accessed. 
 * \return A const pointer to the item. */
const void *cvec_view(const cvec_t *vec, size_t index);

/** Append an item at the end of the vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be appended.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_push_back(cvec_t *vec, void *value, size_t sizeof_type);

/** Removes the last item of a vector.
 * \param vec A pointer to the vector to be modified. */
void cvec_pop_back(cvec_t *vec);

/** Prepends an item at the beginning of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be prepended.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_push_front(cvec_t *vec, void *value, size_t sizeof_type);

/** Removes the first item of a vector.
 * \param vec A pointer to the vector to be modified. */
void cvec_pop_front(cvec_t *vec);

/** Appends an array at the end of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param arr The array to be appended. 
 * \param len The length of the array. 
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_append(cvec_t *vec, void *arr, size_t len, size_t sizeof_type);

/** Prepends an array at the beginning of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param arr The array to be prepended. 
 * \param len The length of the array. 
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_prepend(cvec_t *vec, void *arr, size_t len, size_t sizeof_type);

/** Removes an item of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The item's index. */
void cvec_remove(cvec_t *vec, size_t index);

/** Inserts an item into a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The index where the item is to be inserted.
 * \param value A pointer to the value to be inserted.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_insert(cvec_t *vec, size_t index, void *value, size_t sizeof_type);

/** Replaces an item in a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The index where the item is to be replaced.
 * \param value A pointer to the value to be inserted.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_replace(cvec_t *vec, size_t index, void *value, size_t sizeof_type);

/** Replaces a range of items in a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The index where the new array is to be inserted.
 * \param arr The new array to be inserted.
 * \param len The length of the array.
 * \param range The number of items to be replaced.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_replace_range(
	cvec_t *vec, size_t index, void *arr,
	size_t len, size_t range, size_t sizeof_type);

/** Returns a string containing the latest error information if exists or 
 * NULL if it does not. */
const char *cvec_get_error();

#define CVEC_TYPEDEF(T)\
	typedef struct cvec_##T cvec_##T##_t;\
	static inline cvec_##T##_t *cvec_##T##_new() {\
		return (cvec_##T##_t*)cvec_new(sizeof(T));\
	}\
	static inline size_t cvec_##T##_len(const cvec_##T##_t *vec) {\
		return cvec_len((cvec_t*)vec);\
	}\
	static inline size_t cvec_##T##_size(const cvec_##T##_t *vec) {\
		return cvec_size((cvec_t*)vec);\
	}\
	static inline size_t cvec_##T##_capacity(const cvec_##T##_t *vec) {\
		return cvec_capacity((cvec_t*)vec);\
	}\
	static inline void cvec_##T##_del(cvec_##T##_t *vec) {\
		cvec_del((cvec_t*)vec);\
	}\
	static inline const T *cvec_##T##_view(const cvec_##T##_t *vec, size_t index) {\
		return (T*)cvec_view((cvec_t*)vec, index);\
	}\
	static inline void cvec_##T##_push_back(cvec_##T##_t *vec, T value) {\
		cvec_push_back((cvec_t*)vec, (void*)&value, sizeof(T));\
	}\
	static inline void cvec_##T##_pop_back(cvec_##T##_t *vec) {\
		cvec_pop_back((cvec_t*)vec);\
	}\
	static inline void cvec_##T##_push_front(cvec_##T##_t *vec, T value) {\
		cvec_push_front((cvec_t*)vec, &value, sizeof(T));\
	}\
	static inline void cvec_##T##_pop_front(cvec_##T##_t *vec) {\
		cvec_pop_front((cvec_t*)vec);\
	}\
	static inline void cvec_##T##_append(cvec_##T##_t *vec, T *arr, size_t len) {\
		cvec_append((cvec_t*)vec, (void*)arr, len, sizeof(T));\
	}\
	static inline void cvec_##T##_prepend(cvec_##T##_t *vec, T *arr, size_t len) {\
		cvec_prepend((cvec_t*)vec, (void*)arr, len, sizeof(T));\
	}\
	static inline void cvec_##T##_remove(cvec_##T##_t *vec, size_t index) {\
		cvec_remove((cvec_t*)vec, index);\
	}\
	static inline void cvec_##T##_insert(cvec_##T##_t *vec, T value, size_t index) {\
		cvec_insert((cvec_t*)vec, index, (void*)&value, sizeof(T));\
	}\
	static inline void cvec_##T##_replace(cvec_##T##_t *vec, size_t index, T value) {\
		cvec_replace((cvec_t*)vec, index, (void*)&value, sizeof(T));\
	}\
	static inline void cvec_##T##_replace_range(cvec_##T##_t *vec, size_t index, T *arr, size_t len, size_t range) {\
		cvec_replace_range((cvec_t*)vec, index, (void*)arr, len, range, sizeof(T));\
	}

#ifdef __cplusplus
}
#endif

#endif
