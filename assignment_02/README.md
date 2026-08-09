# CS509 Laboratory - Assignment 02

# Student Details

| Field | Information |
|-------|-------------|
| Student Name | Akash Maurya |
| Entry Number | 2026CSM1024 |
| Programming Language | C++ |
---

## 1. Assignment Overview

This assignment implements and test two shortest-path algorithms:

1. **Bellman-Ford**
   - It is Single-source shortest path algorithm.
   - it supports graphs containing negative edge weights.
   - It also detects negative-weight cycles reachable from the selected source.
   - It is using a CSR (Compressed Sparse Row) graph .

2. **Floyd-Warshall**
   - It is all-pairs shortest path algorithm.
   - it calculate shortest distances between every pair of vertices.
   - It also supports negative edge weights.
   - It is used a dense distance matrix.

---

## 2. Language and Environment

The complete repository has been implemented using modern C++ following the laboratory guidelines.

## Programming Language

```
C++
```


## Compiler

```
GNU g++ Compiler
```

## Build Tool

```
Makefile
```

## Operating System

```
 Windows 11
```

---

## 3. Repository Structure

The Assignment 02 directory follows the required CS509 laboratory organization.

```text
assignment_02/
│
├── src/
│   ├── Bellman_Ford.hpp
│   ├── Bellman_Ford.cpp
│   ├── Floyd_Warshall.hpp
│   └── Floyd_Warshall.cpp
│
├── driver/
│   ├── driver_bellman_ford.cpp
│   └── driver_floyd_warshall.cpp
│
├── tests/
│   ├── bellman_ford/
│   │   ├── bf_5.txt
│   │   ├── bf_10.txt
│   │   ├── bf_100.txt
│   │   └── ...
│   │
│   └── floyd_warshall/
│       ├── fw_5.txt
│       ├── fw_10.txt
│       ├── fw_100.txt
│       └── ...
│
├── outputs/
│   ├── bellman_ford/
│   │   ├── output_1.txt
│   │   ├── output_2.txt
│   │   └── ...
│   │
│   └── floyd_warshall/
│       ├── output_1.txt
│       ├── output_2.txt
│       └── ...
│
├── executables/
│   ├── bellman_ford.exe
│   └── floyd_warshall.exe
│
└── README.md
```

---

## 4. Common CSR Component

A reusable CSR implementation is maintained separately under the repository
It is reusable CSR code implemented separately so it can be used in any assignment  store in folder name common.

```text
common/
└── csr/
    │
    ├── README.md
    ├── test_csr.cpp
    │
    ├── src/
    │   ├── CSR.hpp
    │   ├── CSR.cpp
    │   ├── driver_csr.hpp
    │   └── driver_csr.cpp
    │
    ├── test_CSR/
    │   ├── csr_test_01.txt
    │   ├── csr_test_02.txt
    │   ├── csr_test_03.txt
    │   └── ...
    │
    └── outputs/
        └── graph/
```

The Bellman-Ford code uses this common CSR in this assignment.

---

## 5. Directory and File Responsibilities

### 5.1 `src/`

it contains the main algorithm implementations.

#### `Bellman_Ford.hpp`

It store the declaration of the Bellman-Ford algorithm.

#### `Bellman_Ford.cpp`

It have implementation of Bellman-Ford using CSR representation.

#### `Floyd_Warshall.hpp`

It store thee declaration of the Floyd-Warshall algorithm.

#### `Floyd_Warshall.cpp`

It have implementation of Floyd-Warshall using a dense distance matrix.

---

### 5.2 `driver/`

Contains one dedicated driver for each assignment algorithm.

#### `driver_bellman_ford.cpp`

Used for:

* locating Bellman-Ford test files,
* generating CSR representations,
* calling Bellman-Ford,
* measuring algorithm execution time,
* printing results,
* creating output files,

#### `driver_floyd_warshall.cpp`

Used for:

* locating Floyd-Warshall test files,
* reading matrix input,
* allocating the distance matrix,
* calling Floyd-Warshall,
* measuring algorithm execution time,
* printing results,
* creating output files,

---

### 5.3 `tests/`

It stores Assignment 02 test cases.

### 5.4 `outputs/`

It contain all Output files

### 5.5 `executables/`

Contains the compiled Assignment 02 executables:

## 6. Assignment Objective

The objectives of this assignment are:

1. Implement Bellman-Ford for single-source shortest paths.
2. Implement Floyd-Warshall for all-pairs shortest paths.
3. Support negative edge weights.
4. Detect negative-weight cycles.
5. Use CSR representation for Bellman-Ford.
6. Use a dense matrix representation for Floyd-Warshall.
7. Measure only algorithm execution time.
8. Test the algorithms on the prescribed graph sizes.

---

## 7. Algorithm Comparison

| Property                  | Bellman-Ford                | Floyd-Warshall          |
| ------------------------- | --------------------------- | ------------------------ |
| Problem                   | Single-source shortest path | All-pairs shortest path |
| Representation            | CSR                         | Dense matrix            |
| Negative edges            | Supported                   | Supported                |
| Negative-cycle detection  | Reachable from source       | Any negative cycle       |
| Time complexity           | O(VE)                       | O(V³)                    |
| Algorithm auxiliary space | O(V)                        | O(V²)                    |
| Graph/data storage        | O(V + E)                    | O(V²)                    |
| Sources per execution     | One                         | All vertices             |

---



## 8. Bellman-Ford

Bellman-Ford solves the single-source shortest-path problem on a directed weighted graph.

The algorithm computes the shortest distance from a specified source vertex to every reachable vertex.


---

### 8.1. Bellman-Ford Algorithm

For a graph with `V` vertices and `E` edges:

1. Initialize all distances to infinity.
2. Set the source distance to zero.
3. Relax all reachable edges.
4. Repeat the relaxation process up to `V - 1` times.
5. Stop early if a complete pass produces no changes.
6. Perform one additional relaxation pass.
7. If an edge can still be relaxed, report a reachable negative-weight cycle.

---


## 9. Floyd-Warshall

Floyd-Warshall computes the shortest distance between every pair of vertices in a weighted directed graph.

It is an all-pairs shortest-path algorithm.

The algorithm supports negative edge weights, provided the graph does not contain a negative-weight cycle.

---


### 9.1. Floyd-Warshall Algorithm Steps

1. Read the input distance matrix.
2. Convert `INF` entries into an internal infinity value.
3. Start the algorithm timer.
4. Select every vertex `k` as an intermediate vertex.
5. For every source vertex `i`, inspect every destination vertex `j`.
6. Update `distance[i][j]` if the path through `k` is shorter.
7. Stop the timer.
8. Check the diagonal for a negative-weight cycle.
9. Print the resulting matrix if no negative cycle exists.
10. Print the execution time.
11. Release the matrix memory.

---


## 10. Bellman-Ford Result Table

The following table summarizes the measured Bellman-Ford results.

| Test File      | Vertices (V) | Edges (E)  | Source | Algorithm Time   |   Negative Cycle |
| -------------  | -----------: | --------:  | -----: | ---------------- | ---------------- |
| `bf_5.txt`     |          [5] |       [10] |    [0] |      0.001 ms    |      No
| `bf_10.txt`    |         [10] |       [15] |    [0] |      0.0008 ms   |      No
| `bf_100.txt`   |        [100] |      [200] |    [0] |      0.0082 ms   |      No
| `bf_1000.txt`  |       [1000] |     [1500] |    [0] |      0.0917 ms   |      No
| `bf_10000.txt` |      [10000] |    [12000] |    [0] |      726.858 ms  |      Yes
| `bf_20000.txt` |      [20000] |    [20000] |    [0] |      2233.99 ms  |      Yes
| `bf_50000.txt` |      [50000] |    [55000] |    [0] |     3.1342 ms    |      No

---

## 11. Floyd-Warshall Result Summary

The following table summarizes the measured Floyd-Warshall results.

| Test File     | Vertices (V) | Matrix Size  | Algorithm Time   |  Negative Cycle  |
| ------------- | -----------: | ------------ | ---------------- | ---------------- |
| `fw_5.txt`    |          [5] | [5 x 5]      |      0.0023 ms   |      No
| `fw_10.txt`   |         [10] | [10 x 10]    |      0.0065 ms   |      No
| `fw_100.txt`  |        [100] | [100 x 100]  |      3.9498 ms   |      No
| `fw_500.txt`  |        [500] | [500 x 500]  |      522.144 ms  |      Yes
| `fw_1000.txt` |       [1000] | [1000 x 1000]|      3545.04 ms  |      No
| `fw_1500.txt` |       [1500] | [1500 x 1500]|      13782.4 ms  |      No
| `fw_2000.txt` |       [2000] | [2000 x 2000]|      32303.2 ms  |      No
---


# 11 Observations

### 12.1 Bellman-Ford

- The execution time increased as the number of vertices and edges increased.
- The results show the expected increase in computational cost for larger graphs, consistent with the O(VE) time complexity of   Bellman-Ford.
- Negative-weight cycles were correctly detected in the test cases designed to contain them.
- The `bf_50000.txt` result is an exception to the general timing trend, as its measured execution time was lower than the times recorded for some smaller test cases.

### 12.1 Floyd-Warshall

- The execution time increased consistently as the number of vertices and matrix dimensions increased.
- The increase becomes particularly significant for larger matrices, with the `2000 × 2000` test case requiring `32303.2 ms`.
- Overall, the results show that Floyd-Warshall is practical for smaller graph sizes but becomes increasingly expensive as the matrix size grows.