# CS509 Laboratory - Assignment 03

# Student Details

| Field | Information |
|-------|-------------|
| Student Name | Akash Maurya |
| Entry Number | 2026CSM1024 |
| Programming Language | C++ |
---

## 1. Assignment Overview

This assignment implements and tests two Minimum Spanning Tree (MST) algorithms:

1. **Kruskal's Algorithm**
   - It is a greedy Minimum Spanning Tree algorithm.
   - It processes graph edges in non-decreasing order of weight.
   - It adds an edge only when it does not create a cycle.
   - It uses a Disjoint Set Union (DSU) / Union-Find structure for cycle detection.
   - It uses a CSR (Compressed Sparse Row) graph representation.

2. **Prim's Algorithm**
   - It is also a greedy Minimum Spanning Tree algorithm.
   - It starts from a selected vertex, using vertex `0` for reproducibility.
   - It repeatedly selects the minimum-weight edge connecting the current MST to a vertex outside the MST.
   - It uses the CSR graph representation.
   - It grows one connected tree until all vertices are included.

Both algorithms operate on the same weighted, undirected graph.

The total MST weight produced by Kruskal's and Prim's algorithms must be the same.

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

The Assignment 03 directory follows the required CS509 laboratory organization.

```text
assignment_03/
│
├── src/
│   ├── MST.hpp
│   └── MST.cpp
│
├── driver/
│   └── driver_mst.cpp
│
├── tests/
│   └── mst/
│       ├── mst_5.txt
│       ├── mst_10.txt
│       ├── mst_100.txt
│       └── ...
│
├── outputs/
│   ├── kruskal/
│   │   ├── mst_5.txt
│   │   ├── mst_10.txt
│   │   └── ...
│   │
│   └── prim/
│       ├── mst_5.txt
│       ├── mst_10.txt
│       └── ...
│
├── executables/
│   ├── kruskal.exe
│   └── prim.exe
│
└── README.md
```

---

## 4. Common CSR Component

A reusable CSR implementation is maintained separately under the repository.
It is reusable CSR code implemented separately so it can be used in any assignment, stored in a folder named `common`.

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

Assignment 03 uses this common CSR component.

The original MST input files are first passed to the common CSR generator. The generated CSR files are then used as input by both Kruskal's and Prim's algorithms.

The common CSR implementation itself is not modified for Assignment 03.

---

## 5. Directory and File Responsibilities

### 5.1 `src/`

It contains the implementation of both MST algorithms.

#### `MST.hpp`

It stores the declaration of:

* `MSTEdge` structure.
* Kruskal's algorithm.
* Prim's algorithm.

#### `MST.cpp`

It has the implementation of:

* Disjoint Set Union functions.
* Kruskal's MST algorithm.
* Prim's MST algorithm.

Both algorithms use the common CSR structure.

---

### 5.2 `driver/`

Contains the common driver for both MST algorithms.

#### `driver_mst.cpp`

Used for:

* locating MST input files,
* generating CSR representations using the common CSR component,
* reading generated CSR files,
* creating the CSR graph structure,
* calling Kruskal's algorithm,
* calling Prim's algorithm,
* measuring only algorithm execution time,
* printing results to the terminal,
* creating output files,
* storing Kruskal's output separately from Prim's output,
* releasing dynamically allocated memory.

The same input graph is used for both algorithms.

---

### 5.3 `tests/`

It stores Assignment 03 test cases.

### 5.4 `outputs/`

It contains all output files, separated by algorithm (`kruskal/` and `prim/`). The output file name is kept the same as the corresponding input/CSR file.

### 5.5 `executables/`

Contains the compiled Assignment 03 executables:

* `kruskal.exe`
* `prim.exe`

---

## 6. Assignment Objective

The objectives of this assignment are:

1. Implement Kruskal's Minimum Spanning Tree algorithm.
2. Implement Prim's Minimum Spanning Tree algorithm.
3. Use a weighted undirected graph.
4. Use the common CSR representation.
5. Generate CSR input using the common CSR component.
6. Ensure both algorithms operate on the same input graph.
7. Compute a minimum spanning tree containing V - 1 edges.
8. Calculate the total MST weight.
9. Verify that Kruskal's and Prim's algorithms produce the same minimum total weight.
10. Measure only algorithm execution time.
11. Store the outputs of both algorithms separately.
12. Test the algorithms on graphs of different sizes.

---

## 7. Algorithm Comparison

| Property | Kruskal's Algorithm | Prim's Algorithm |
| -------- | -------------------- | ------------------ |
| Problem | Minimum Spanning Tree | Minimum Spanning Tree |
| Graph | Weighted undirected | Weighted undirected |
| Representation | CSR | CSR |
| Approach | Edge based | Vertex/tree based |
| Starting vertex | Not required | Vertex 0 |
| Cycle detection | DSU / Union-Find | Not required |
| Edge processing | Sorted by weight | Minimum key edge |
| MST edges | V - 1 | V - 1 |
| Greedy algorithm | Yes | Yes |
| Time complexity | O(E log E) | O(V² + E) |
| Auxiliary space | O(V + E) | O(V) |
| Result | Minimum spanning tree | Minimum spanning tree |

---

## 8. Minimum Spanning Tree

A Minimum Spanning Tree is a tree that connects all vertices of a connected, weighted, undirected graph while minimizing the total sum of the selected edge weights.

For a graph containing `V` vertices, an MST contains exactly:

```text
V - 1
```

edges.

An MST must satisfy the following conditions:

* Every vertex must be connected.
* The selected edges must not contain a cycle.
* Exactly V - 1 edges must be selected.
* The total weight of the selected edges must be minimum.

Both Kruskal's and Prim's algorithms are greedy algorithms used to find an MST.

---

### 9. Kruskal's Algorithm

Kruskal's algorithm constructs an MST by considering graph edges in increasing order of their weights.

The algorithm uses a Disjoint Set Union (DSU), also called Union-Find, to detect cycles.

### 9.1. Kruskal's Algorithm Steps

For a graph with `V` vertices and `E` edges:

1. Read the graph in CSR representation.
2. Extract the undirected edges from CSR.
3. Since CSR stores both directions of an undirected edge, keep only edges where `u < v`.
4. Sort all edges in non-decreasing order of weight.
5. Create a separate set for every vertex.
6. Select the smallest remaining edge.
7. Check whether its endpoints belong to different sets.
8. If they belong to different sets, add the edge to the MST and merge the two sets.
9. If they belong to the same set, discard the edge because it would create a cycle.
10. Continue until V - 1 edges have been selected.
11. Calculate the total MST weight.
12. Print the selected MST edges and total weight.
---

## 10. Prim's Algorithm

Prim's algorithm constructs the MST by starting from one vertex and gradually expanding the tree.

In this implementation, vertex 0 is used as the starting vertex for reproducibility.

### 10.1. Prim's Algorithm Steps

1. Read the graph in CSR representation.
2. Initialize the key value of every vertex to infinity.
3. Set the key value of vertex 0 to 0.
4. Mark all vertices as not belonging to the MST.
5. Select the vertex with the smallest key value that is not already in the MST.
6. Add the selected vertex to the MST.
7. Examine all neighbouring vertices using the CSR representation.
8. If an edge has a smaller weight than the current key value of the neighbouring vertex, update the key value and the parent vertex.
9. Repeat until all vertices are included in the MST.
10. Use the parent array to construct the MST edges.
11. Calculate the total MST weight.
12. Print the selected MST edges and total weight.
---

## 11. MST Result Table

The following table summarizes the measured results for both Kruskal's and Prim's algorithms, run on the same input graph for each test file.

| File | V | E | Exp. Wt. | Kruskal Wt. | Prim Wt. | Kruskal Time | Prim Time | Equal? | Status |
| ---- | -: | -: | -: | -: | -: | -: | -: | :-: | :-: |
| `mst_5.txt`     | 5      | 7       | 16      | 16 | 16 | 0.0018 ms | 0.0025 ms | Yes/No | Pass/Fail |
| `mst_10.txt`    | 10     | 15      | 228  | 228 | 228 | 0.0025 ms | 0.0029 ms | Yes | Pass |
| `mst_100.txt`   | 100    | 200     | 2143  | 2143 | 2143 | 0.1114 ms | 0.0405 ms | Yes | Pass |
| `mst_1000.txt`  | 1000   | 1500    | 35633  | 35633 | 35633 | 3.5247 ms | 2.5445 ms | Yes | Pass |
| `mst_10000.txt` | 10000  | 12000   | 432637  | 432637 | 432637 | 149.567 ms | 207.013 ms | Yes | Pass |
| `mst_50000.txt` | 50000  | 55000   | 2320065  | 2320065 | 2320065 | 3188.95 ms | 5094.83 ms | Yes | Pass |
| `mst_100000.txt`| 100000 | 120000  | 4290227  | 4290227 | 4290227 | 14234 ms | 24525.5 ms | Yes | Pass |


## 12. Observations

### 12.1 Execution Time

- The execution time of both algorithms generally increases as the number of vertices and edges increases.
- For the smallest graph, `mst_5.txt`, the execution times are very close, with Kruskal taking `0.0018 ms` and Prim taking `0.0025 ms`.
- For `mst_100.txt` and `mst_1000.txt`, Prim's algorithm is faster than Kruskal's algorithm.
- For the larger graphs, `mst_10000.txt`, `mst_50000.txt`, and `mst_100000.txt`, Kruskal's algorithm is faster than Prim's algorithm.
- The largest test case, `mst_100000.txt`, has `100000` vertices and `120000` edges. Kruskal takes `14234 ms`, while Prim takes `24525.5 ms`.
- The results show that the relative execution performance of the two algorithms changes with graph size.

### 12.2 MST Weight

- For every test case, Kruskal's and Prim's algorithms produce the same MST weight.
- The MST weights obtained are `16`, `228`, `2143`, `35633`, `432637`, `2320065`, and `4290227` respectively for the seven test cases.
- The equality of the MST weights confirms that both implementations produce the same minimum spanning-tree weight for all tested graphs.
- The MST weight increases as the graph size increases, from `16` for the smallest graph to `4290227` for the largest graph.

### 19.3 Overall Performance Comparison

- Prim's algorithm performs better than Kruskal's algorithm for the `100` and `1000` vertex test cases.
- Kruskal's algorithm performs better than Prim's algorithm for the `10000`, `50000`, and `100000` vertex test cases.
- Therefore, Kruskal's algorithm is approximately `1.72` times faster than Prim's algorithm for the largest test case.
- The performance difference becomes more noticeable as the graph size increases.
- Across all test cases, both algorithms produce identical MST weights, so the main observed difference is in their execution performance rather than correctness.
- Overall, the measured results show that Kruskal's algorithm performs better for the larger graphs in this dataset, while Prim's algorithm performs better for some smaller and medium-sized graphs.

---
