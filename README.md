
# s21_containers

Implementation of the s21_containers.h. library.



## About The Project

Any additional information goes here

This project implements a library that implements the main standard C++ container classes: list, map, queue, set, stack, vector, array, multiset. The tree container is implemented, which is an implementation of the red-black tree, on which the set, map, multiset containers are based. The implementations provide a set of standard methods and attributes for working with elements, checking if the container is full and iterating. 

Each type of container provides the following methods to the user:

- standard constructors (default constructor, copy constructor, move constructor, constructor with initialisation list, see materials);

- methods for accessing container elements (e.g., accessing an element with index i);

- methods of checking whether the container is full (e.g., the number of elements in the container, checking whether the container is empty);

- methods for modifying the container (deleting and adding new elements, cleaning the container);

- methods for working with the container iterator.

Iterators provide access to the elements of a container. For each container, the specific type of iterator will be different. This is due to the different kind of organisation of object sets in container classes, as well as the actual implementation of the container. Iterators are implemented in such a way that they work in a similar way to a pointer to a C array element. It is this approach through the use of iterators that allows any container to be interacted with in the same way. Containers provide iterators through the begin() and end() methods that point to the first and the next-to-last elements of the container, respectively.

## Authors

- [@emmonbea](https://github.com/emmonbear)
- [@kossadda](https://github.com/kossadda)



## Installation

Install project with Makefile

1. Clone [repository](https://github.com/emmonbear/containers)

```bash
  git clone git@github.com:emmonbear/containers.git
```
    
2. Go to the project directory:

```bash
  cd containers/src/
```

3. Build the project using the Makefile:

```bash
  make
```
## Running Tests

To run tests, run the following command

```bash
  make tests
```


## License

[MIT](https://github.com/emmonbear/containers/blob/develop/LICENSE)

