---
title: "Link-time merging of arrays"
document: D0xxxR0
date: today
audience: Language Evolution Group
author:
  - name: Lauri Vasama
    email: <lauri@vasama.org>
toc: true
---

# Introduction

This paper proposes a new method of defining arrays in namespace scope by merging one or more variables or arrays of the same type together from all translation units.

# Motivation

It is often desirable to statically define sets of things in a distributed manner without explicitly and manually maintaining the full list of elements in a single location. In C++20 the only way to achieve this is by building the set at runtime using static initialisers. This approach however presents multiple problems:

* Accessing specific elements adds additional complexity. For example storing indices in global variables during static initialisation.
* Is subject to the static initialisation order fiasco if other static initialisers should access the list, even when the actual data is known statically and could in theory be constant initialised.
* Use in certain domains such as embedded firmware poses challenges: data must either be stored in a linked list or some form of dynamic allocation is required.
* Adds unnecessary runtime overhead in both time and memory.
* It is made fragile due to the fact that static initialisers - even when they have side effects - are not always executed if the objects they initialise are never used. Ironically this also works the other way around: static initialisers with side effects cannot be elided because their effects, i.e. the set they build at runtime, are not being used.

Existing use cases:
* Test case registration in all major C++ unit test frameworks.
* Optimisation pass registration in LLVM.
* Type information registration in Unreal Engine 4.

Collation of type information may become a particularly important use case if static reflection is added to the language. A reflection library may register descriptions of user types and other entities in link arrays for runtime use.

::: tonytable

### Before
```cpp
std::vector<int>& get_array_as_vector() {
  static std::vector<T> vector;
  return vector;
}

std::span<const int> get_array() {
  return get_array_as_vector();
}


static char elements_pusher = (
  get_array_as_vector().push_back(value_0),
  get_array_as_vector().push_back(value_1), 0);
```

### After
```cpp
extern const int array[];

std::span<const int> get_array() {
  return std::span(array, std::link_array_size(array));
}


register(array)
static const int elements[] = { value_0, value_1 };
```
:::

# Design

## Defining elements of link arrays



## Link array element ordering

* All elements of a link array defined within a single translation unit are ordered in the resulting array according to their definitions.
* The relative ordering of elements from different translation units is unspecified, but same for all link arrays. This facilitates the definition of parallel link arrays.

## Size of the merged array

There are at least two alternative approaches for exposing the size of the merged array with different pros and cons:

::: tonytable

### Library function

Usage:
```cpp
std::link_array_size(array)
```

* Illegal usage has undefined behaviour at runtime.
* Reference to the array is a first-class object.
* Lesser implementation flexibility.

Possible implementation:
```cpp
template<typename T>
size_t link_array_size(const T* array) noexcept {
  // the size of the array might be stored before the array in memory:
  return reinterpret_cast<const size_t*>(array)[-1];
}
```

### Function-like operator

Usage:
```cpp
__link_array_size(array)
```

* Illegal usage may produce an error at link time.
* Reference to the array is not a first-class object.
* Greater implementation flexibility.

Possible implementation:
```cpp
// The compiler may calculate the size using two symbols:
static_cast<size_t>(
  reinterpret_cast<T*>(&array__end) -
  reinterpret_cast<T*>(&array__begin)
)
```
:::

# Implementation

Existing linkers already support merging symbols into arrays from multiple translation units in order to implement static initialisers, thread local storage and exception handling.

# Examples

## Unit test framework

Framework header:
```cpp
using test_case_callback = void();

// array of test case callbacks
extern test_case_callback* const test_cases[];
```

User test code:
```cpp
register(test_cases)
test_case_callback* const my_test_case = my_test_case_function_1;

register(test_cases)
test_case_callback* const my_test_case_array[] = {
  my_test_case_function_2,
  my_test_case_function_3
};
```

Framework source:
```cpp
void run_unit_tests()
{
  test_case_callback* const* tests = test_cases;
  size_t test_count = std::link_array_size(tests);

  for (test_case_callback* test : std::span(tests, test_count))
  {
      test();
  }
}
```
