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

/** \file src/cvec.c
 * \brief Implementation for the cvec library.
 * \details This file contains the definition of the vector object and 
 * the implementations of the public functions for the cvec library. */

#include "cvec.h"
#include <carena.h>
#include <string.h>
#include <stdbool.h>

_Thread_local static const char *g_err;

/** The default capacity of the vector object. */
#define DEFAULT_CAPACITY 8

/** Opaque handle for the vector object. */
struct cvec {
	/** Pointer to the vector data. */
	void *data;

	/** The size of the vector's type. */
	size_t sizeof_type;

	/** The current capacity of the vector. */
	size_t capacity;

	/** The current length of the vector. */
	size_t len;
};

/** Returns the default capacity.
 * \return The default capacity. */
size_t cvec_default_capacity() {
	return DEFAULT_CAPACITY;
}

/** Creates a new pointer for a specific type.
 * \param sizeof_type The size of the type that's meant to be stored 
 * in the vector.
 * \return A pointer to the allocated vector. */
cvec_t *cvec_new(size_t sizeof_type) {
	cvec_t *vec = carena_alloc(sizeof(cvec_t));
	if (!vec) {
		g_err = "Failed to allocate vector.";
		return NULL;
	}
	vec->data = carena_alloc(sizeof_type * DEFAULT_CAPACITY);
	if (!vec->data) {
		g_err = "Failed to allocate vector data.";
		return NULL;
	}
	vec->sizeof_type = sizeof_type;
	vec->capacity = DEFAULT_CAPACITY;
	vec->len = 0;
	return vec;
}

/** Returns the the length of a vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The length of the vector. */
size_t cvec_len(const cvec_t *vec) {
	if (!vec) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	return vec->len;
}

/** Returns the the size of a vector's type.
 * \param vec A pointer to the vector to be accessed. 
 * \return The size of the vector's type. */
size_t cvec_size(const cvec_t *vec) {
	if (!vec) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	return vec->sizeof_type;
}

/** Returns the the capacity of a vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The capacity of the vector. */
size_t cvec_capacity(const cvec_t *vec) {
	if (!vec) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	return vec->capacity;
}

/** Deletes a vector instance.
 * \param vec A pointer to the vector to be deleted. */
void cvec_del(cvec_t *vec) {
	if (!vec || !vec->data) {
		g_err = "Invalid argument.";
		return;
	}
	carena_free(vec->data);
	carena_free(vec);
}

/** Returns a const pointer to a vector item.
 * \param vec A pointer to the vector to be accessed.
 * \param index The index of the element to be accessed. 
 * \return A const pointer to the item. */
const void *cvec_view(const cvec_t *vec, size_t index) {
	if (!vec) {
		g_err = "Invalid argument.";
		return NULL;
	}
	if (index >= vec->len) {
		g_err = "Index is out of bounds.";
		return NULL;
	}
	return (void*)((unsigned char*)vec->data + index * vec->sizeof_type);
}

/** Append an item at the end of the vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be appended.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_push_back(cvec_t *vec, void *value, size_t sizeof_type) {
	if (
		!vec || !vec->data || !value ||
		sizeof_type != vec->sizeof_type
	) {
		g_err = "Invalid argument.";
		return;
	}
	if (vec->len + 1 > vec->capacity) {
		void *tmp = carena_realloc(vec->data, vec->capacity * 2);
		if (!tmp) {
			g_err = "Failed to resize vector.";
			return;
		}
		vec->data = tmp;
		vec->capacity *= 2;
	}
	unsigned char *chardata = (unsigned char*)((vec->data));
	memcpy(&chardata[vec->len * sizeof_type], value, sizeof_type);
	vec->len++;
}	

/** Removes the last item of a vector.
 * \param vec A pointer to the vector to be modified. */
void cvec_pop_back(cvec_t *vec) {
	if (!vec || !vec->data) {
		g_err = "Invalid argument.";
		return;
	}
	if (!vec->len) {
		g_err = "Cannot pop empty vector.";
		return;
	}
	if (vec->len - 1 < vec->capacity / 2 && vec->capacity / 2 >= DEFAULT_CAPACITY) {
		void *tmp = carena_realloc(vec->data, vec->capacity / 2);
		if (!tmp) {
			g_err = "Failed to resize vector.";
			return;
		}
		vec->data = tmp;
		vec->capacity /= 2;
	}
	vec->len--;
}

/** Prepends an item at the beginning of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be prepended.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_push_front(cvec_t *vec, void *value, size_t sizeof_type) {
	if (
		!vec || !vec->data || !value ||
		sizeof_type != vec->sizeof_type
	) {
		g_err = "Invalid argument.";
		return;
	}
	if (vec->len + 1 > vec->capacity) {
		void *tmp = carena_realloc(vec->data, vec->capacity * 2);
		if (!tmp) {
			g_err = "Failed to resize vector.";
			return;
		}
		vec->data = tmp;
		vec->capacity *= 2;
	}
	unsigned char *chardata = (unsigned char*)((vec->data));
	memmove(&chardata[sizeof_type], chardata, sizeof_type * vec->len);
	memcpy(chardata, value, sizeof_type);
	vec->len++;
}

/** Removes the first item of a vector.
 * \param vec A pointer to the vector to be modified. */
void cvec_pop_front(cvec_t *vec) {
	if (!vec || !vec->data) {
		g_err = "Invalid argument.";
		return;
	}
	if (!vec->len) {
		g_err = "Cannot pop empty vector.";
		return;
	}
	unsigned char *chardata = (unsigned char*)((vec->data));
	memmove(chardata, &chardata[vec->sizeof_type], vec->sizeof_type * vec->len - 1);
	if (vec->len - 1 < vec->capacity / 2 && vec->capacity / 2 >= DEFAULT_CAPACITY) {
		void *tmp = carena_realloc(vec->data, vec->capacity / 2);
		if (!tmp) {
			g_err = "Failed to resize vector.";
			return;
		}
		vec->data = tmp;
		vec->capacity /= 2;
	}
	vec->len--;
}

/** Appends an array at the end of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param arr The array to be appended. 
 * \param len The length of the array. 
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_append(cvec_t *vec, void *arr, size_t len, size_t sizeof_type) {
	if (
		!vec || !vec->data || !arr ||
		sizeof_type != vec->sizeof_type
	) {
		g_err = "Invalid argument.";
		return;
	}
	while (vec->len + len > vec->capacity) {
		void *tmp = carena_realloc(vec->data, vec->capacity * 2);
		if (!tmp) {
			g_err = "Failed to resize vector.";
			return;
		}
		vec->data = tmp;
		vec->capacity *= 2;
	}
	unsigned char *chardata = (unsigned char*)((vec->data));
	memcpy(&chardata[vec->len * sizeof_type], arr, len * sizeof_type);
	vec->len += len;
}

/** Prepends an array at the beginning of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param arr The array to be prepended. 
 * \param len The length of the array. 
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_prepend(cvec_t *vec, void *arr, size_t len, size_t sizeof_type) {
	if (
		!vec || !vec->data || !arr ||
		sizeof_type != vec->sizeof_type
	) {
		g_err = "Invalid argument.";
		return;
	}
	while (vec->len + len > vec->capacity) {
		void *tmp = carena_realloc(vec->data, vec->capacity * 2);
		if (!tmp) {
			g_err = "Failed to resize vector.";
			return;
		}
		vec->data = tmp;
		vec->capacity *= 2;
	}
	unsigned char *chardata = (unsigned char*)((vec->data));
	memmove(&chardata[len * sizeof_type], chardata, vec->len * sizeof_type);
	memcpy(chardata, arr, len * sizeof_type);
	vec->len += len;
}

/** Removes an item of a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The item's index. */
void cvec_remove(cvec_t *vec, size_t index) {
	if (!vec || !vec->data) {
		g_err = "Invalid argument.";
		return;
	}
	if (!vec->len) {
		g_err = "Cannot remove from empty vector.";
		return;
	}
	if (index >= vec->len) {
		g_err = "index is out of bounds.";
		return;
	}
	unsigned char *chardata = (unsigned char*)((vec->data));
	size_t len_to_move = vec->len - index + 1;
	memmove(
		&chardata[index * vec->sizeof_type],
		&chardata[(index + 1) * vec->sizeof_type],
		len_to_move * vec->sizeof_type);
	if (vec->len - 1 < vec->capacity / 2 && vec->capacity / 2 >= DEFAULT_CAPACITY) {
		void *tmp = carena_realloc(vec->data, vec->capacity / 2);
		if (!tmp) {
			g_err = "Failed to resize vector.";
			return;
		}
		vec->data = tmp;
		vec->capacity /= 2;
	}
	vec->len--;
}

/** Inserts an item into a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The index where the item is to be inserted.
 * \param value A pointer to the value to be inserted.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_insert(cvec_t *vec, size_t index, void *value, size_t sizeof_type) {
	if (
		!vec || !vec->data || !value ||
		sizeof_type != vec->sizeof_type
	) {
		g_err = "Invalid argument.";
		return;
	}
	if (index >= vec->len) {
		g_err = "index is out of bounds.";
		return;
	}
	unsigned char *chardata = (unsigned char*)((vec->data));
	size_t len_to_move = vec->len - index + 1;
	memmove(
		&chardata[(index + 1) * sizeof_type],
		&chardata[index * sizeof_type],
		len_to_move * sizeof_type);
	memcpy(&chardata[index * sizeof_type], value, sizeof_type);
	if (vec->len + 1 > vec->capacity) {
		void *tmp = carena_realloc(vec->data, vec->capacity * 2);
		if (!tmp) {
			g_err = "Failed to resize vector.";
			return;
		}
		vec->data = tmp;
		vec->capacity *= 2;
	}
	vec->len++;
}

/** Replaces an item in a vector.
 * \param vec A pointer to the vector to be modified.
 * \param index The index where the item is to be replaced.
 * \param value A pointer to the value to be inserted.
 * \param sizeof_type The size of the vector's type 
 * (must be the same as the value's). */
void cvec_replace(cvec_t *vec, size_t index, void *value, size_t sizeof_type) {
	if (
		!vec || !vec->data || !value ||
		sizeof_type != vec->sizeof_type
	) {
		g_err = "Invalid argument.";
		return;
	}
	if (index >= vec->len) {
		g_err = "index is out of bounds.";
		return;
	}
	unsigned char *chardata = (unsigned char*)((vec->data));
	memcpy(&chardata[index * sizeof_type], value, sizeof_type);
}

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
	size_t len, size_t range, size_t sizeof_type)
{
	if (
		!vec || !vec->data || !arr ||
		sizeof_type != vec->sizeof_type
	) {
		g_err = "Invalid argument.";
		return;
	}
	if (index >= vec->len) {
		g_err = "index is out of bounds.";
		return;
	}
	if (index + range > vec->len) {
		g_err = "range is too big.";
		return;
	}
	while (vec->len - range + len > vec->capacity) {
		void *tmp = carena_realloc(vec->data, vec->capacity * 2);
		if (!tmp) {
			g_err = "Failed to resize vector.";
			return;
		}
		vec->data = tmp;
		vec->capacity *= 2;
	}
	unsigned char *chardata = (unsigned char*)((vec->data));
	size_t move_by = len - range;
	memmove(
		&chardata[(index + range + move_by) * sizeof_type],
		&chardata[(index + range) * sizeof_type],
		(vec->len - index - range) * sizeof_type);
	memcpy(&chardata[index * sizeof_type], arr, len * sizeof_type);
	vec->len = vec->len - range + len;
}

/** Returns a string containing the latest error information if exists or 
 * NULL if it does not. */
const char *cvec_get_error() {
	return g_err;
}
