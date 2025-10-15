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

```
## Todo
- Make the default capacity adjustable at compile time.
