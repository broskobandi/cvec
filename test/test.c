#include "cvec.h"
#include <ctest.h>
#include <string.h>

void test_cvec_new_size_len_capacity_del() {
	cvec_t *vec = cvec_new(sizeof(int));
	CTEST(cvec_size(vec) == sizeof(int));
	CTEST(cvec_len(vec) == 0);
	CTEST(cvec_capacity(vec) == cvec_default_capacity());
	cvec_del(vec);
	CTEST(!cvec_get_error());
}

void test_cvec_push_and_pop_back() {
	cvec_t *vec = cvec_new(sizeof(size_t));
	size_t expected_capacity = cvec_capacity(vec);
	for (size_t i = 0; i < 128; i++) {
		if (cvec_len(vec) + 1 > expected_capacity)
			expected_capacity *= 2;
		cvec_push_back(vec, &i, sizeof(size_t));
		CTEST(!cvec_get_error());
		CTEST(expected_capacity == cvec_capacity(vec));
		CTEST(*(size_t*)cvec_view(vec, i) == i);
	}
	expected_capacity = cvec_capacity(vec);
	for (size_t i = 128; i > 0; i--) {
		if (
			cvec_len(vec) - 1 < expected_capacity / 2 &&
			expected_capacity / 2 >= cvec_default_capacity()
		) expected_capacity /= 2;
		cvec_pop_back(vec);
		CTEST(!cvec_get_error());
		CTEST(expected_capacity == cvec_capacity(vec));
	}
	cvec_del(vec);
	CTEST(!cvec_get_error());
}

void test_cvec_push_and_pop_front() {
	cvec_t *vec = cvec_new(sizeof(size_t));
	size_t expected_capacity = cvec_capacity(vec);
	for (size_t i = 0; i < 128; i++) {
		if (cvec_len(vec) + 1 > expected_capacity)
			expected_capacity *= 2;
		cvec_push_front(vec, &i, sizeof(size_t));
		CTEST(!cvec_get_error());
		CTEST(expected_capacity == cvec_capacity(vec));
		CTEST(*(size_t*)cvec_view(vec, 0) == i);
		CTEST(*(size_t*)cvec_view(vec, cvec_len(vec) - 1) == 0);
	}
	expected_capacity = cvec_capacity(vec);
	for (size_t i = 128; i > 0; i--) {
		if (
			cvec_len(vec) - 1 < expected_capacity / 2 &&
			expected_capacity / 2 >= cvec_default_capacity()
		) expected_capacity /= 2;
		CTEST(*(size_t*)cvec_view(vec, cvec_len(vec) - 1) == 0);
		cvec_pop_front(vec);
		CTEST(!cvec_get_error());
		CTEST(expected_capacity == cvec_capacity(vec));
	}
	cvec_del(vec);
	CTEST(!cvec_get_error());
}

void test_cvec_append_prepend() {
	cvec_t *vec = cvec_new(sizeof(char));
	const char *str1 = "World!";
	const char *str2 = "Hello, ";
	cvec_append(vec, (void*)str1, strlen(str1) + 1, sizeof(char));
	CTEST(!strcmp(cvec_view(vec, 0), str1));
	cvec_prepend(vec, (void*)str2, strlen(str2), sizeof(char));
	CTEST(!strcmp(cvec_view(vec, 0), "Hello, World!"));
	CTEST(cvec_len(vec) == strlen("Hello, World!") + 1);
	cvec_del(vec);
	CTEST(!cvec_get_error());
}

void test_cvec_remove() {
	cvec_t *vec = cvec_new(sizeof(int));
	int arr[] = {1, 2, 9, 3};
	cvec_append(vec, arr, 4, sizeof(int));
	int exp[] = {1, 2, 3};
	cvec_remove(vec, 2);
	CTEST(!memcmp(cvec_view(vec, 0), exp, 3 * sizeof(int)));
	CTEST(cvec_len(vec) == 3);
	cvec_del(vec);
	CTEST(!cvec_get_error());
}

void test_cvec_insert() {
	cvec_t *vec = cvec_new(sizeof(int));
	int arr[] = {1, 3};
	cvec_append(vec, arr, sizeof(arr), sizeof(int));
	int value = 2;
	cvec_insert(vec, 1, &value, sizeof(int));
	int exp[] = {1, 2, 3};
	CTEST(!memcmp(exp, cvec_view(vec, 0), 3 * sizeof(int)));
	cvec_del(vec);
	CTEST(!cvec_get_error());
}

void test_cvec_replace() {
	cvec_t *vec = cvec_new(sizeof(int));
	int arr[] = {1, 2, 9, 4};
	cvec_append(vec, arr, sizeof(arr), sizeof(int));
	int value = 3;
	int exp[] = {1, 2, 3, 4};
	cvec_replace(vec, 2, &value, sizeof(int));
	CTEST(!memcmp(exp, cvec_view(vec, 0), 4 * sizeof(int)));
	cvec_del(vec);
	CTEST(!cvec_get_error());
}

void test_cvec_replace_range_expand() {
	cvec_t *vec = cvec_new(sizeof(int));
	int arr[] = {1, 2, 9, 5, 6, 7};
	int new_arr[] = {3, 4};
	int exp[] = {1, 2, 3, 4, 5, 6, 7};
	cvec_append(vec, arr, 6, sizeof(int));
	cvec_replace_range(vec, 2, new_arr, 2, 1, sizeof(int));
	CTEST(cvec_len(vec) == 7);
	CTEST(!memcmp(exp, cvec_view(vec, 0), 7 * sizeof(int)));
	cvec_del(vec);
	CTEST(!cvec_get_error());
}

void test_cvec_replace_range_shrink() {
	cvec_t *vec = cvec_new(sizeof(int));
	int arr[] = {1, 2, 9, 10, 11, 5, 6, 7};
	int new_arr[] = {3, 4};
	int exp[] = {1, 2, 3, 4, 5, 6, 7};
	cvec_append(vec, arr, 8, sizeof(int));
	cvec_replace_range(vec, 2, new_arr, 2, 3, sizeof(int));
	CTEST(cvec_len(vec) == 7);
	CTEST(!memcmp(exp, cvec_view(vec, 0), 7 * sizeof(int)));
	cvec_del(vec);
	CTEST(!cvec_get_error());
}

int main(void) {
	test_cvec_new_size_len_capacity_del();
	test_cvec_push_and_pop_back();
	test_cvec_push_and_pop_front();
	test_cvec_append_prepend();
	test_cvec_remove();
	test_cvec_insert();
	test_cvec_replace();
	test_cvec_replace_range_expand();
	test_cvec_replace_range_shrink();

	ctest_print_results();
	return 0;
}
