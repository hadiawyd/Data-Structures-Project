# Data-Structures-Project
# Vector.h

A custom dynamic array similar to C++ STL vector.

## Features
- Dynamic resizing
- Random access
- Insert and erase by index
- Reserve and shrink_to_fit
- Deep copy and move semantics
- Merge Sort (O(n log n))
- Iterator support

## Time Complexities

| Function | Complexity |
|-----------|------------|
| push_back() | O(1)* |
| pop_back() | O(1) |
| insert() | O(n) |
| erase() | O(n) |
| find() | O(n) |
| sort() | O(n log n) |
| at(), [] | O(1) |

\* Amortized

## Comparison with STL Vector

- Similar behavior to `std::vector`
- Same complexity for most operations
- Uses Merge Sort instead of Bubble Sort
# MyLinkedList

A custom doubly linked list similar to C++ STL list.

## Features
- Push and pop at both ends
- Insert and erase by index
- Iterator-based insert and erase
- Reverse operation
- Merge Sort (O(n log n))
- Deep copy and move semantics

## Time Complexities

| Function | Complexity |
|-----------|------------|
| push_front() | O(1) |
| push_back() | O(1) |
| pop_front() | O(1) |
| pop_back() | O(1) |
| insert(index) | O(n) |
| erase(index) | O(n) |
| insert(iterator) | O(1) |
| erase(iterator) | O(1) |
| find() | O(n) |
| sort() | O(n log n) |

## Comparison with STL List

- Similar behavior to `std::list`
- Fast insertions and deletions
- Slower random access than vectors
- Uses Merge Sort for efficient sorting
