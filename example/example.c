#include <assert.h>
#include <string.h>

/* Include the library. */
#include <cvec.h>

int main(void) {
	/* Create a new vector of the desired type. */
	vec_t *vec = vec_new(sizeof(int));

	/* Push data at the end. */
	int value = 2;
	vec_push_back(vec, &value, sizeof(int));

	/* Push data at the beginning. */
	value = 1;
	vec_push_front(vec, &value, sizeof(int));

	/* Remove the last item. */
	vec_pop_back(vec);

	/* Remove the first item. */
	vec_pop_front(vec);

	/* Query info about the vector. */
	assert(vec_len(vec) == 0);
	assert(vec_capacity(vec) == vec_default_capacity());
	assert(vec_size(vec) == sizeof(int));

	/* Append an array at the end. */
	int arr1[] = {4, 5, 6};
	vec_append(vec, arr1, 3, sizeof(int));

	/* Prepend an array at the beginning. */
	int arr2[] = {1, 2, 3};
	vec_prepend(vec, arr2, 3, sizeof(int));

	/* Get a const pointer to a specific index in
	 * the array. */
	const int *data = vec_view(vec, 0);
	int exp1[] = {1, 2, 3, 4, 5, 6};
	assert(!memcmp(data, exp1, 6 * sizeof(int)));

	/* Insert a new item. */
	value = 42;
	vec_insert(vec, 3, &value, sizeof(int));

	/* Remove an item. */
	vec_remove(vec, 3);

	/* Replace an item. */
	vec_replace(vec, 3, &value, sizeof(int));

	/* Replace a range of items with an array. */
	int arr3[] = {4, 5, 6, 7, 8, 9};
	vec_replace_range(vec, 3, arr3, 6, 3, sizeof(int));
	int exp2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	data = vec_view(vec, 0);

	assert(!memcmp(data, exp2, 9 * sizeof(int)));

	/* Delete the vector. */
	vec_del(vec);

	return 0;
}
