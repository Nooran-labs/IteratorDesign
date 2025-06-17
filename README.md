# IteratorDesign Project

Author: **Nooran Gnaim** 
Contact: [noorangnaim@gmail.com](mailto:noorangnaim@gmail.com)

---

##  Project Description

This C++ project implements a custom dynamic container named `MyContainer<T>`, supporting various iterator traversal patterns. It demonstrates advanced iterator design, exception safety, and robust unit testing using [doctest](https://github.com/doctest/doctest).

---

##  Features

-  Add/remove elements dynamically (`addElement`, `removeElement`)
-  Multiple custom iterators:
  - `AscendingOrderIterator` – elements in ascending order
  - `DescendingOrderIterator` – elements in descending order
  - `SideCrossOrderIterator` – alternate smallest/largest
  - `ReverseOrderIterator` – traverse in reverse order
  - `OrderIterator` – preserves insertion order
  - `MiddleOutOrderIterator` – starts from middle and fans out
-  Operator overloading for `<<` (printing)
-  Iterator invalidation on modification
-  Exception-safe and version-controlled iteration
-  Fully tested using **doctest**

---

##  Files

| File                          | Description                                      |
|-------------------------------|--------------------------------------------------|
| `MyContainer.hpp`             | Implementation of the dynamic container         |
| `AscendingOrderIterator.hpp`  | Sorted ascending iterator                        |
| `DescendingOrderIterator.hpp` | Sorted descending iterator                       |
| `SideCrossOrderIterator.hpp`  | Alternating smallest/largest traversal           |
| `ReverseOrderIterator.hpp`    | Reversed insertion order                         |
| `OrderIterator.hpp`           | Original insertion order                         |
| `MiddleOutOrderIterator.hpp`  | Traverses from middle outwards                   |
| `main.cpp`                    | Demo program showcasing usage                    |
| `tests.cpp`                   | Unit tests for all iterators using doctest      |
| `Makefile`                    | Build targets for demo, tests, valgrind          |

---

##  Build & Run

###  Requirements

- C++17 or higher
- `g++` compiler
- `valgrind` (optional for memory checking)

###  Makefile Commands

```bash
make main        # Compile and run the demo (main.cpp)
make test        # Compile and run the unit tests (tests.cpp)
make demo        # Alias for 'make main'
make valgrind    # Run valgrind over both ./main and ./test
make clean       # Remove build artifacts
```

###  Example Usage

```bash
make test
./test

make main
./main

make valgrind
```

---

##  Testing

- The tests are written using the `doctest` framework.
- Every iterator is tested for:
  - Correct traversal order
  - Exception on invalid dereferencing
  - Behavior after container modification
- Example:
  ```cpp
  MyContainer<int> c;
  c.addElement(1);
  c.addElement(3);
  c.addElement(2);

  for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
      std::cout << *it << " ";
  }
  ```

---

##  Version Control in Iterators

Each iterator captures the version of the container at creation time. If the container is modified during iteration, the iterator throws a `std::runtime_error` to prevent undefined behavior.


---

##  Contact

For questions or improvements, feel free to email:  
 **noorangnaim@gmail.com**

---
