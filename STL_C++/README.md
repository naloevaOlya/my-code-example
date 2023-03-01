# containers
Implementation of the s21_containers.h. library.

## Contents

## Chapter I

- The program must be developed in C++ language of  C++17 standard
- The program code must be located in the src folder
- Make sure to use iterators
- Classes must be template
- Classes must be implemented within the `s21` namespace
- Prepare full coverage of container classes methods with unit-tests using the GTest library
- Copying of the Standard Template Library (STL) implementation is not allowed
- The logic of the Standard Template Library (STL) must be followed (in terms of checks, memory handling and behaviour in abnormal situations)

### Part 1. Implementation of the s21_containers.h library

You need to implement the `s21_containers.h` library classes (specifications are given in the relevant material sections, see **"Main containers"**). \
List of classes: `list`, `map`, `queue`, `set`, `stack`, `vector`.
- Make it as a header file `s21_containers.h` which includes different header files with implementations of the specified containers (`s21_list.h`, `s21_map.h` and etc.) 
- Provide a Makefile for testing the library (with targets clean, test)

*Tip*: You can move the same implementation of container methods to base classes. For example, for a queue and a stack, or for a list and a vector. There is a UML diagram of the STL library in materials as *one possible example* of hierarchical construction. However, your implementation does not have to be strictly tied to this UML diagram.

### Part 2. Bonus. Implementation of the s21_containersplus.h library.

You need to implement the `s21_containersplus.h` library functions (see **"Additional containers"** for specifications). \
List of classes to be implemented additionally: `array`, `multiset`.
- Make it as a header file `s21_containersplus.h` which includes different header files with implementations of the specified containers (`s21_array.h`, `s21_multiset.h`) 
- Provide a Makefile for testing the library (with targets clean, test)

### Part 3. Bonus. Implementation of the `emplace` methods

You need to complete the classes with the appropriate methods, according to the table:

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator emplace(const_iterator pos, Args&&... args)`          | inserts new elements into the container directly before `pos`  | List, Vector |
| `void emplace_back(Args&&... args)`          | appends new elements to the end of the container  | List, Vector, Queue |
| `void emplace_front(Args&&... args)`          | appends new elements to the top of the container  | List, Stack |
| `vector<std::pair<iterator,bool>> emplace(Args&&... args)`          | inserts new elements into the container  | Map, Set, Multiset |

*Tip 1*: notice that each of these methods uses an Args&&... args - Parameter pack construct. This construct allows a variable number of parameters to be passed to a function or method. So, when calling a method defined as `iterator emplace(const_iterator pos, Args&&... args)`, you can write either `emplace(pos, arg1, arg2)` or `emplace(pos, arg1, arg2, arg3)`.

*Tip 2*: remember to test methods for different cases, including boundary ones.

