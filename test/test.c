#include "cvec.h"
#include <ctest.h>
#include <string.h>

void test_vec_new_size_len_capacity_del() {
	vec_t *vec = vec_new(sizeof(int));
	CTEST(vec_size(vec) == sizeof(int));
	CTEST(vec_len(vec) == 0);
	CTEST(vec_capacity(vec) == vec_default_capacity());
	vec_del(vec);
	CTEST(!vec_get_error());
}

void test_vec_push_and_pop_back() {
	vec_t *vec = vec_new(sizeof(size_t));
	size_t expected_capacity = vec_capacity(vec);
	for (size_t i = 0; i < 128; i++) {
		if (vec_len(vec) + 1 > expected_capacity)
			expected_capacity *= 2;
		vec_push_back(vec, &i, sizeof(size_t));
		CTEST(!vec_get_error());
		CTEST(expected_capacity == vec_capacity(vec));
		CTEST(*(size_t*)vec_view(vec, i) == i);
	}
	expected_capacity = vec_capacity(vec);
	for (size_t i = 128; i > 0; i--) {
		if (
			vec_len(vec) - 1 < expected_capacity / 2 &&
			expected_capacity / 2 >= vec_default_capacity()
		) expected_capacity /= 2;
		vec_pop_back(vec);
		CTEST(!vec_get_error());
		CTEST(expected_capacity == vec_capacity(vec));
	}
	vec_del(vec);
	CTEST(!vec_get_error());
}

void test_vec_push_and_pop_front() {
	vec_t *vec = vec_new(sizeof(size_t));
	size_t expected_capacity = vec_capacity(vec);
	for (size_t i = 0; i < 128; i++) {
		if (vec_len(vec) + 1 > expected_capacity)
			expected_capacity *= 2;
		vec_push_front(vec, &i, sizeof(size_t));
		CTEST(!vec_get_error());
		CTEST(expected_capacity == vec_capacity(vec));
		CTEST(*(size_t*)vec_view(vec, 0) == i);
		CTEST(*(size_t*)vec_view(vec, vec_len(vec) - 1) == 0);
	}
	expected_capacity = vec_capacity(vec);
	for (size_t i = 128; i > 0; i--) {
		if (
			vec_len(vec) - 1 < expected_capacity / 2 &&
			expected_capacity / 2 >= vec_default_capacity()
		) expected_capacity /= 2;
		CTEST(*(size_t*)vec_view(vec, vec_len(vec) - 1) == 0);
		vec_pop_front(vec);
		CTEST(!vec_get_error());
		CTEST(expected_capacity == vec_capacity(vec));
	}
	vec_del(vec);
	CTEST(!vec_get_error());
}

void test_vec_append_prepend() {
	vec_t *vec = vec_new(sizeof(char));
	const char *str1 = "World!";
	const char *str2 = "Hello, ";
	vec_append(vec, (void*)str1, strlen(str1) + 1, sizeof(char));
	CTEST(!strcmp(vec_view(vec, 0), str1));
	vec_prepend(vec, (void*)str2, strlen(str2), sizeof(char));
	CTEST(!strcmp(vec_view(vec, 0), "Hello, World!"));
	CTEST(vec_len(vec) == strlen("Hello, World!") + 1);
	vec_del(vec);
	CTEST(!vec_get_error());
}

void test_vec_remove() {
	vec_t *vec = vec_new(sizeof(int));
	int arr[] = {1, 2, 9, 3};
	vec_append(vec, arr, 4, sizeof(int));
	int exp[] = {1, 2, 3};
	vec_remove(vec, 2);
	CTEST(!memcmp(vec_view(vec, 0), exp, 3 * sizeof(int)));
	CTEST(vec_len(vec) == 3);
	vec_del(vec);
	CTEST(!vec_get_error());
}

void test_vec_insert() {
	vec_t *vec = vec_new(sizeof(int));
	int arr[] = {1, 3};
	vec_append(vec, arr, sizeof(arr), sizeof(int));
	int value = 2;
	vec_insert(vec, 1, &value, sizeof(int));
	int exp[] = {1, 2, 3};
	CTEST(!memcmp(exp, vec_view(vec, 0), 3 * sizeof(int)));
	vec_del(vec);
	CTEST(!vec_get_error());
}

void test_vec_replace() {
	vec_t *vec = vec_new(sizeof(int));
	int arr[] = {1, 2, 9, 4};
	vec_append(vec, arr, sizeof(arr), sizeof(int));
	int value = 3;
	int exp[] = {1, 2, 3, 4};
	vec_replace(vec, 2, &value, sizeof(int));
	CTEST(!memcmp(exp, vec_view(vec, 0), 4 * sizeof(int)));
	vec_del(vec);
	CTEST(!vec_get_error());
}

void test_vec_replace_range_expand() {
	vec_t *vec = vec_new(sizeof(int));
	int arr[] = {1, 2, 9, 5, 6, 7};
	int new_arr[] = {3, 4};
	int exp[] = {1, 2, 3, 4, 5, 6, 7};
	vec_append(vec, arr, 6, sizeof(int));
	vec_replace_range(vec, 2, new_arr, 2, 1, sizeof(int));
	CTEST(vec_len(vec) == 7);
	CTEST(!memcmp(exp, vec_view(vec, 0), 7 * sizeof(int)));
	vec_del(vec);
	CTEST(!vec_get_error());
}

void test_vec_replace_range_shrink() {
	vec_t *vec = vec_new(sizeof(int));
	int arr[] = {1, 2, 9, 10, 11, 5, 6, 7};
	int new_arr[] = {3, 4};
	int exp[] = {1, 2, 3, 4, 5, 6, 7};
	vec_append(vec, arr, 8, sizeof(int));
	vec_replace_range(vec, 2, new_arr, 2, 3, sizeof(int));
	CTEST(vec_len(vec) == 7);
	CTEST(!memcmp(exp, vec_view(vec, 0), 7 * sizeof(int)));
	vec_del(vec);
	CTEST(!vec_get_error());
}

int main(void) {
	test_vec_new_size_len_capacity_del();
	test_vec_push_and_pop_back();
	test_vec_push_and_pop_front();
	test_vec_append_prepend();
	test_vec_remove();
	test_vec_insert();
	test_vec_replace();
	test_vec_replace_range_expand();
	test_vec_replace_range_shrink();

	ctest_print_results();
	return 0;
}
