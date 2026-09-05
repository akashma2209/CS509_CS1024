# CS509 Laboratory - Assignment 04

## Student Details

| Field                | Information  |
| -------------------- | ------------ |
| Student Name         | Akash Maurya |
| Entry Number         | 2026CSM1024  |
| Programming Language | C++          |

---

## 1. Assignment Overview

This assignment implements and tests two graph algorithms:

1. **Vertex Coloring using the Welsh-Powell Greedy Algorithm**

   * It is a greedy graph coloring algorithm.
   * It operates on an undirected graph.
   * It calculates the degree of every vertex.
   * It processes vertices in non-increasing order of degree.
   * It assigns the smallest available color to every vertex.
   * Adjacent vertices must not have the same color.
   * It uses a CSR (Compressed Sparse Row) graph representation.
   * It does not guarantee the minimum possible number of colors because exact graph coloring is an NP-hard problem.

2. **PageRank**

   * It is an iterative graph-ranking algorithm.
   * It operates on a directed graph.
   * It calculates the relative importance of every vertex.
   * It uses a damping factor, normally `0.85`.
   * It initializes every vertex with rank `1/N`.
   * It handles dangling vertices whose outdegree is zero.
   * It repeatedly updates PageRank values until convergence or until the maximum number of iterations is reached.
   * It uses the CSR graph representation.

Both algorithms operate on sparse graph inputs.

The main purpose of this assignment is to study graph algorithms, their implementation using CSR representation, correctness, computational complexity, and performance on graphs of different sizes.

---

## 2. Language and Environment

The complete repository has been implemented using modern C++ following the laboratory guidelines.

### Programming Language

```text
C++
```

### Compiler

```text
GNU g++ Compiler
```

### Build Tool

```text
Makefile
```

### Operating System

```text
Windows 11
```

---

## 3. Repository Structure

The Assignment 04 directory follows the required CS509 laboratory organization.

```text
assignment_04/
│
├── src/
│   ├── Vertex_Coloring.hpp
│   ├── Vertex_Coloring.cpp
│   ├── PageRank.hpp
│   └── PageRank.cpp
│
├── driver/
│   ├── driver_vertex_coloring.cpp
│   └── driver_pagerank.cpp
│
├── tests/
│   ├── vertex_coloring/
│   │   ├── color10.txt
│   │   ├── color100.txt
│   │   ├── color10000.txt
│   │   ├── color50000.txt
│   │   └── color100000.txt
│   │
│   └── pagerank/
│       ├── pr_10.txt
│       ├── pr_100.txt
│       ├── pr_10000.txt
│       ├── pr_50000.txt
│       └── pr_100000.txt
│
├── outputs/
│   ├── vertex_coloring/
│   │   ├── color10.txt
│   │   ├── color100.txt
│   │   └── ...
│   │
│   └── pagerank/
│       ├── pr_10.txt
│       ├── pr_100.txt
│       └── ...
│
├── executables/
│   ├── vertex_coloring.exe
│   └── pagerank.exe
│
└── README.md
```

The assignment also uses the reusable common CSR component:

```text
common/
│
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

---

## 4. Common CSR Component

A reusable CSR implementation is maintained separately under the repository.

It is reusable CSR code implemented separately so it can be used in any assignment, stored in a folder named `common`.

```text
common/
│
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

Assignment 04 uses this common CSR component.

The original graph input files are first passed to the common CSR generator. The generated CSR representation is then used by the Vertex Coloring and PageRank algorithms.

The common CSR implementation itself is not modified for Assignment 04.

The CSR representation stores graph information using arrays such as:

```text
row_ptr
col_idx
values
```

For an unweighted graph, the adjacency information is represented using the row pointer and column index arrays.

The use of CSR provides an efficient representation for the sparse graphs used in this assignment.

---

## 5. Directory and File Responsibilities

### 5.1 `src/`

It contains the implementation of both graph algorithms.

#### `Vertex_Coloring.hpp`

It stores the declarations related to:

* Vertex Coloring algorithm.
* Vertex color information.
* Required function declarations.

#### `Vertex_Coloring.cpp`

It has the implementation of:

* Degree calculation.
* Vertex ordering.
* Welsh-Powell greedy coloring.
* Color assignment.
* Checking the colors of adjacent vertices.
* Calculating the number of colors used.

The algorithm uses the common CSR graph representation.

#### `PageRank.hpp`

It stores the declarations related to:

* PageRank algorithm.
* PageRank function.
* Required parameters such as damping factor, tolerance, and maximum iterations.

#### `PageRank.cpp`

It has the implementation of:

* PageRank initialization.
* PageRank iteration.
* Rank contribution calculation.
* Dangling vertex handling.
* Convergence calculation.
* Maximum iteration handling.
* Final PageRank values.

The algorithm uses the common CSR graph representation.

---

### 5.2 `driver/`

Contains the drivers for both Assignment 04 algorithms.

#### `driver_vertex_coloring.cpp`

Used for:

* locating Vertex Coloring input files,
* generating CSR representations using the common CSR component,
* reading generated CSR files,
* creating the CSR graph structure,
* calling the Vertex Coloring algorithm,
* measuring only algorithm execution time,
* printing results to the terminal,
* creating output files,
* storing Vertex Coloring results,
* releasing dynamically allocated memory.

The same graph input is used to generate the CSR representation before running the coloring algorithm.

#### `driver_pagerank.cpp`

Used for:

* locating PageRank input files,
* reading PageRank graph parameters,
* generating CSR representations,
* reading the generated CSR graph,
* creating the graph structure,
* calling the PageRank algorithm,
* measuring only algorithm execution time,
* printing PageRank results,
* reporting the sum of ranks,
* reporting the number of iterations,
* reporting convergence status,
* creating output files,
* releasing dynamically allocated memory.

---

### 5.3 `tests/`

It stores Assignment 04 test cases.

The test cases are divided into two directories:

```text
tests/
├── vertex_coloring/
└── pagerank/
```

The Vertex Coloring test cases contain undirected graphs.

The PageRank test cases contain directed graphs.

---

### 5.4 `outputs/`

It contains all output files separated according to the algorithm.

```text
outputs/
├── vertex_coloring/
└── pagerank/
```

The Vertex Coloring output files contain:

* vertex colors,
* number of colors used,
* execution time.

The PageRank output files contain:

* damping factor,
* PageRank values,
* sum of ranks,
* number of iterations,
* convergence status,
* execution time.

---


## 6. Assignment Objective

The objectives of this assignment are:

1. Implement the Vertex Coloring algorithm.
2. Use the Welsh-Powell greedy heuristic for Vertex Coloring.
3. Use an undirected graph for Vertex Coloring.
4. Use the common CSR representation.
5. Generate CSR input using the common CSR component.
6. Calculate the degree of every vertex.
7. Order vertices in non-increasing order of degree.
8. Assign the smallest available color to every vertex.
9. Ensure that adjacent vertices do not receive the same color.
10. Report the number of colors used.
11. Implement the PageRank algorithm.
12. Use a directed graph for PageRank.
13. Initialize every PageRank value to `1/N`.
14. Use a damping factor of `0.85`.
15. Handle dangling vertices with zero outgoing edges.
16. Update PageRank values using the previous iteration values.
17. Check convergence using the total change in PageRank values.
18. Stop when the tolerance is reached or the maximum number of iterations is completed.
19. Verify that the sum of PageRank values remains approximately `1`.
20. Measure only algorithm execution time.
21. Test both algorithms on graphs of different sizes.
22. Record the observed performance and system limitations for large test cases.

---

## 7. Algorithm Comparison

| Property           | Vertex Coloring                         | PageRank                      |
| ------------------ | --------------------------------------- | ------------------------------ |
| Problem            | Graph Coloring                          | Graph Ranking                 |
| Graph              | Undirected                              | Directed                      |
| Representation     | CSR                                     | CSR                            |
| Approach           | Greedy heuristic                        | Iterative                      |
| Main purpose       | Assign valid colors                     | Assign importance scores       |
| Main parameter     | Vertex degree                           | Damping factor                 |
| Starting value     | Uncolored vertices                      | `1/N`                          |
| Iterative          | No                                       | Yes                             |
| Convergence        | Not required                            | Required                       |
| Tolerance          | Not required                            | Required                       |
| Maximum iterations | Not required                            | Required                       |
| Correctness        | Adjacent vertices have different colors | Rank convergence and rank sum  |
| Output             | Vertex colors                           | Vertex PageRank                |
| Typical complexity | Depends on sorting and coloring          | O(I(V + E))                    |
| Space complexity   | O(V + E) including graph                 | O(V + E)                       |
| Graph type         | Sparse undirected                        | Sparse directed                |

---

## 8. Vertex Coloring

Vertex Coloring is a graph problem in which a color is assigned to every vertex of an undirected graph.

The main condition for a valid coloring is:

```text
color[u] != color[v]
```

for every edge:

```text
(u, v)
```

This means that two directly connected vertices cannot have the same color.

The minimum number of colors required to color a graph is known as its chromatic number.

Finding the exact minimum number of colors for a general graph is an NP-hard problem.

Therefore, this assignment uses a greedy heuristic instead of an exact coloring algorithm.

The greedy algorithm attempts to produce a valid coloring using a small number of colors.

---

### 8.1 Welsh-Powell Algorithm

The Vertex Coloring implementation uses the Welsh-Powell greedy approach.

The main idea is to process vertices according to their degree.

Vertices with higher degree are processed first.

The algorithm follows these steps:

1. Calculate the degree of every vertex from CSR.
2. Store all vertices along with their degrees.
3. Sort the vertices in non-increasing order of degree.
4. Initialize all vertices as uncolored.
5. Select the first uncolored vertex in the sorted order.
6. Assign the smallest available color to that vertex.
7. Examine all of its already-colored neighbours.
8. Mark the colors that cannot be used.
9. Select the smallest color that is not used by its neighbours.
10. Continue processing vertices until every vertex has a color.
11. Count the total number of colors used.

The algorithm does not hard-code the number of colors.

The required number of colors depends on the graph structure.

---


## 9. PageRank

PageRank is an iterative graph-ranking algorithm used to estimate the relative importance of vertices in a directed graph.

In the original web interpretation:

```text
Vertex = Web page
Edge = Link between pages
```

A page receives importance from pages that point towards it.

The PageRank algorithm repeatedly distributes rank through the graph until the values converge.

The PageRank formula used in this assignment is:

```text
PR(v) =
(1 - d) / N
+
d * Σ(PR(u) / outdegree(u))
```

where:

```text
PR(v)        = PageRank of vertex v
d            = damping factor
N            = total number of vertices
u -> v       = directed edge from u to v
outdegree(u) = number of outgoing edges from u
```

The damping factor used in the test cases is:

```text
d = 0.85
```

---



## 10. Vertex Coloring Result Table

The following table summarizes the measured results for the Vertex Coloring test cases.

| File               |       V |       E | Colors Used | Valid? | Execution Time | Status |
| ------------------ | ------: | ------: | ----------: | :----: | --------------: | :----: |
| `color10.txt`      |      10 |      20 |           3 |   Yes  |       0.0035 ms |  Pass  |
| `color100.txt`     |     100 |     300 |           4 |   Yes  |       0.0036 ms |  Pass  |
| `color10000.txt`   |  10,000 |  50,000 |           4 |   Yes  |       0.0323 ms |  Pass  |
| `color50000.txt`   |  50,000 | 250,000 |           7 |   Yes  |      200.711 ms |  Pass  |
| `color100000.txt`  | 100,000 | 500,000 |           7 |   Yes  |      5919.13 ms |  Pass  |

---

## 11. PageRank Result Table

The following table summarizes the successfully completed PageRank tests.

| File             |       V |       E | Damping |  Sum of Ranks | Iterations | Converged |  Execution Time |            Status            |
| ---------------- | ------: | ------: | ------: | -------------: | ---------: | :-------: | ---------------: | :---------------------------: |
| `pr_10.txt`      |      10 |      20 |    0.85 |       1.000000 |         33 |    Yes    |      0.047200 ms |             Pass              |
| `pr_100.txt`     |     100 |     300 |    0.85 |       1.000000 |         15 |    Yes    |      1.822900 ms |             Pass              |
| `pr_10000.txt`   |  10,000 |  50,000 |    0.85 |       1.000000 |         11 |    Yes    |  27923.717000 ms |             Pass              |
| `pr_50000.txt`   |  50,000 | 250,000 |    0.85 |  Not completed |          - |     -     |    Not completed |       System limitation       |
| `pr_100000.txt`  | 100,000 | 500,000 |    0.85 |  Not completed |          - |     -     |    Not completed | Optional / System limitation |

---
## 12. Observations

### 16.1 Vertex Coloring

* The Vertex Coloring algorithm successfully processed graphs ranging from small graphs to graphs containing `100,000` vertices and `500,000` edges.

* The execution time generally increases as the number of vertices and edges increases because the algorithm has to calculate vertex degrees, order the vertices, and examine their neighbouring vertices during color assignment.

* The algorithm produced valid colorings for the tested graphs, with no adjacent vertices assigned the same color.

* The number of colors used depends mainly on the structure of the graph and the degree ordering rather than only on the number of vertices.

* The tested graphs required between `3` and `7` colors.

* The number of colors does not necessarily increase with graph size. Larger graphs can use the same number of colors as smaller graphs if their structures allow it.

* Since Welsh-Powell is a greedy heuristic, the number of colors obtained is not guaranteed to be the minimum possible number of colors.

* Overall, Vertex Coloring showed good scalability for the tested graph sizes and successfully completed the largest graph used in the assignment.


### 16.2 PageRank

* The PageRank algorithm successfully processed the smaller and medium-sized graphs and converged within the specified tolerance using a damping factor of `0.85`.

* The execution time increases significantly as the graph size increases because PageRank is an iterative algorithm that repeatedly processes the graph until convergence.

* All successfully completed test cases converged, and the sum of the PageRank values remained `1.000000`, confirming the expected normalization of the calculated ranks.

* The number of iterations required for convergence depends on the graph structure, damping factor, tolerance, and initial rank distribution, and therefore does not necessarily increase directly with the number of vertices.

* PageRank required substantially more computation for larger graphs compared with Vertex Coloring because the graph must be traversed repeatedly across multiple iterations.

* The larger PageRank test cases containing `50,000` and `100,000` vertices could not be completed on the available system due to practical execution limitations.

* Overall, PageRank is computationally more expensive for large graphs because of its iterative nature, while Vertex Coloring completed the largest tested graph successfully.