# real-world-algorithms
Personal solutions in C to the exercises from [*Real-World Algorithms* by Panos Louridas](https://louridas.github.io/rwa/) (not me).

Paraphrased assignments and notes on implementation are below.

#### 1.1 Implement an array-based stack.
There are size_t, double, and char versions - used by exercises 1.2, 1.3, and 1.4, respectively. There is also a generic version.

#### 1.2 Implement and benchmark O(n) and O(n^2) algorithms for the Stock Span Problem.
A comment in one of the files details the Stock Span Problem. [libcurl](https://curl.haxx.se/libcurl/) is used to download real stock market data from [Alpha Vantage](https://www.alphavantage.co/), which requires a free API key. A shell script profiles the algorithms with [Callgrind](http://valgrind.org/docs/manual/cl-manual.html/).

#### 1.3 Write an [RPN](https://en.wikipedia.org/wiki/Reverse_Polish_notation) calculator.

#### 1.4 Write a program to determine whether a sequence of open/close delimiters such as `(){[](){}}` is properly matched.

#### 2.1 Implement a singly linked list.
Each node in the list contains a void pointer to data, instead of the data itself, so that the list is generic.

#### 2.2 Implement an array-based queue.

#### 2.3 Implement depth-first search (either recursively or not) and breadth-first search using an adjacency matrix representation.
