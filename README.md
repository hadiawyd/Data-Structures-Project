# Data-Structures-Project
# Stack.h

A custom stack implemented using a singly linked list, following LIFO (Last In, First Out) order.

## Features
- Push and pop at the top
- Peek at top element without removal
- Deep copy and assignment operator
- Exception handling for underflow and empty access
- Tracks size with O(1) counter

## Time Complexities

| Function | Complexity |
|-----------|------------|
| push() | O(1) |
| pop() | O(1) |
| top() | O(1) |
| empty() | O(1) |
| size() | O(1) |
| Copy Constructor | O(n) |
| Assignment Operator | O(n) |

## Comparison with STL Stack

- Similar behavior to `std::stack`
- Same complexity for all operations
- STL stack uses `std::deque` internally by default
- Custom version uses a singly linked list with explicit node management

# Queue.h

A custom queue implemented using a singly linked list with front and rear pointers, following FIFO (First In, First Out) order.

## Features
- Enqueue at the rear, dequeue from the front
- Peek at both front and rear elements without removal
- Deep copy and assignment operator
- Exception handling for underflow and empty access
- Tracks size with O(1) counter

## Time Complexities

| Function | Complexity |
|-----------|------------|
| enqueue() | O(1) |
| dequeue() | O(1) |
| front() | O(1) |
| rear() | O(1) |
| empty() | O(1) |
| size() | O(1) |
| Copy Constructor | O(n) |
| Assignment Operator | O(n) |

## Comparison with STL Queue

- Similar behavior to `std::queue`
- Same complexity for all operations
- STL queue uses `std::deque` internally by default
- Custom version uses a singly linked list with explicit front and rear node management

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
- Uses Merge Sort 
# LinkedList.h

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
  # Binary Search Tree (BST)

## Overview

This project implements a Binary Search Tree (BST) from scratch in C++. A BST stores data in sorted order, allowing efficient insertion, searching, and deletion of elements.

## Features

* Insert nodes
* Search for values
* Delete nodes
* In-order traversal
* Pre-order traversal
* Post-order traversal
* Automatic memory cleanup using a destructor

## Time Complexities

| Operation | Complexity       |
| --------- | ---------------- |
| Insert    | O(log n) average |
| Search    | O(log n) average |
| Delete    | O(log n) average |
| Traversal | O(n)             |

Worst-case complexity becomes O(n) when the tree becomes skewed.

## Design Decisions

* Recursive helper functions are used for insertion, searching, and deletion.
* Duplicate values are ignored.
* Deletion handles all three BST cases:

  * Leaf node
  * One child
  * Two children (using inorder successor)

## Learning Outcomes

* Recursive tree operations
* Dynamic memory management
* Tree traversals
* Binary Search Tree deletion logic
# Hash Map

## Overview

This project implements a Hash Map from scratch in C++. The Hash Map stores key-value pairs and provides fast average-case insertion, searching, and deletion using hashing.

## Features

* Insert key-value pairs
* Update existing values
* Search by key
* Delete key-value pairs
* Display bucket contents
* Automatic memory cleanup using a destructor

## Collision Handling

Collisions are handled using Separate Chaining, where each bucket stores a linked list of nodes.

## Time Complexities

| Operation | Average Case |
| --------- | ------------ |
| Insert    | O(1)         |
| Search    | O(1)         |
| Delete    | O(1)         |

Worst-case complexity is O(n) when many keys collide into the same bucket.

## Design Decisions

* Uses a simple ASCII-sum hash function.
* Fixed table size of 10 buckets.
* Inserts new nodes at the front of the chain for O(1) insertion.

## Learning Outcomes

* Hash functions
* Collision resolution
* Separate chaining
* Dynamic memory management
* Key-value data structures

