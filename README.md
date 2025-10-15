# cvec
## Dynamic vector written in C.
The goal of the project is to provide convinient, robust, and highly
performant abstractions for handling dynamic vectors in C.
## Features
### Fast
The library is based on a thread-local static buffer by default which
makes the vector creation, access, modification, and deletion blazing fast.
### Robust
The internal structure is only exposed through const pointers forcing the 
user to make modifications to the vectors via the provided setter functions.
Each function carries out robust thorough safety checks before proceeding with
their task.
### Familiar
The library provides the expected functions that can be found in object
oriented languages, such as push, pop, and append.
## Dependencies
- cmake (for building the library)
- [carena](https://github.com/broskobandi/carena.git)
- [ctest](https://github.com/broskobandi/ctest.git) (for running the tests)
## Installation
```bash
git clone https://github.com/broskobandi/cvec.git &&
cd cvec &&
mkdir build &&
cd build &&
cmake .. &&
make &&
sudo make install
```
## Testing
```bash
cd cvec/build &&
make test &&
./test
```
## Usage
```c
#include <assert.h>
#include <string.h>

/* Include the library. */
#include <cvec.h>

/* Declare the required vector types*/
CVEC_TYPEDEF(int);

int main(void) {
	/* Create a new vector of the desired type. */
	vint_t *vec = vint_new();

	/* Push data at the end. */
	vint_push_back(vec, 2);

	/* Push data at the beginning. */
	vint_push_front(vec, 1);

	/* Remove the last item. */
	vint_pop_back(vec);

	/* Remove the first item. */
	vint_pop_front(vec);

	/* Query info about the vector. */
	assert(vint_len(vec) == 0);
	assert(vint_capacity(vec) == cvec_default_capacity());
	assert(vint_size(vec) == sizeof(int));

	/* Append an array at the end. */
	int arr1[] = {4, 5, 6};
	vint_append(vec, arr1, 3);

	/* Prepend an array at the beginning. */
	int arr2[] = {1, 2, 3};
	vint_prepend(vec, arr2, 3);

	/* Get a const pointer to a specific index in
	 * the array. */
	const int *data = vint_view(vec, 0);
	int exp1[] = {1, 2, 3, 4, 5, 6};
	assert(!memcmp(data, exp1, 6 * sizeof(int)));

	/* Insert a new item. */
	vint_insert(vec, 3, 42);

	/* Remove an item. */
	vint_remove(vec, 3);

	/* Replace an item. */
	vint_replace(vec, 3, 42);

	/* Replace a range of items with an array. */
	int arr3[] = {4, 5, 6, 7, 8, 9};
	vint_replace_range(vec, 3, arr3, 6, 3);

	/* Delete the vector. */
	vint_del(vec);

	return 0;
}
```
## Todo
- Make the default capacity adjustable at compile time.
