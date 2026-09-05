# CS509 - PG Software Lab

Repository for CS509 (PG Software Lab) assignments. This repo contains implementations and performance analysis of classic algorithms in C++, along with test cases, driver programs, and generated outputs.

Each assignment lives in its own folder with a dedicated README covering full details. This top-level README gives a quick overview of the whole repository so a visitor can understand what's inside without digging through every folder.

---

## Student Details

| Field | Information |
|-------|-------------|
| Student Name | Akash Maurya |
| Entry Number | 2026CSM1024 |

---

## Language and Environment

| Item | Details |
|------|---------|
| Programming Language | C++ |
| Compiler | GNU g++ |
| Build Tool | Makefile |
| Operating System | Windows 11 |

---

## Repository Structure

```
CS509_CS1024
│
├── README.md
├── Makefile
│
├── wrapper/                   <- single entry point to run any assignment
│   ├── wrapper.cpp
│   └── wrapper.exe
│
├── common/                    <- reusable code shared across assignments
│   └── csr/                   <- standalone CSR (Compressed Sparse Row) implementation
│
├── assignment_01/              <- GEMM + CSR conversion
│   ├── README.md
│   ├── driver/
│   ├── src/
│   ├── tests/
│   ├── outputs/
│   └── executables/
│
├── assignment_02/              <- Shortest path algorithms
│   ├── README.md
│   ├── driver/
│   ├── src/
│   ├── tests/
│   ├── outputs/
│   └── executables/
│
├── assignment_03/              <- Minimum Spanning Tree algorithms
│   ├── README.md
│   ├── driver/
│   ├── src/
│   ├── tests/
│   ├── outputs/
│   └── executables/
│
└── assignment_04/              <- Vertex Coloring and PageRank
    ├── README.md
    ├── driver/
    ├── src/
    ├── tests/
    ├── outputs/
    └── executables/
```

Every assignment folder follows the same convention:
- `src/` – algorithm implementations
- `driver/` – programs that read test input, run the algorithm, time it, and write output
- `tests/` – input test cases
- `outputs/` – results and execution times
- `executables/` – compiled binaries
- `README.md` – full write-up: algorithm details, test tables, and observations

---

## Common Wrapper

The `wrapper` acts as the main interface for the whole repository. Instead of compiling and running each assignment separately, it provides a single menu-driven program to build and execute any assignment's algorithms.

## Assignments Overview

### Assignment 01 – GEMM and CSR Graph Conversion

Implements and compares two matrix multiplication strategies, and converts a graph's adjacency list into CSR format.

- **Simple GEMM** – traditional triple nested loop matrix multiplication.
- **Blocking GEMM** – cache-optimized matrix multiplication using 64×64 tiling; performs significantly better than the simple version on larger matrices (e.g. ~2.4x speedup at 2000×2000).
- **CSR Graph Conversion** – converts an adjacency list into the CSR representation (`row_ptr`, `col_idx`, `values` arrays), which is memory-efficient for sparse graphs.

Full details, algorithm walk-throughs, and test result tables: [`assignment_01/README.md`](./assignment_01/README.md)

### Assignment 02 – Shortest Path Algorithms

Implements and tests two classic shortest-path algorithms, both supporting negative edge weights and negative-cycle detection.

- **Bellman-Ford** – single-source shortest path, built on top of the CSR graph representation (see `common/csr`). Time complexity O(VE).
- **Floyd-Warshall** – all-pairs shortest path using a dense distance matrix. Time complexity O(V³).

Full details, algorithm steps, and test result tables: [`assignment_02/README.md`](./assignment_02/README.md)

### Assignment 03 – Minimum Spanning Tree Algorithms

Implements and tests two classic greedy Minimum Spanning Tree (MST) algorithms on the same weighted, undirected graph, built on top of the CSR graph representation (see `common/csr`).

- **Kruskal's Algorithm** – edge-based approach that processes edges in non-decreasing order of weight and uses a Disjoint Set Union (DSU) / Union-Find structure to skip edges that would form a cycle. Time complexity O(E log E).
- **Prim's Algorithm** – vertex/tree-based approach that starts from vertex `0` and repeatedly grows the tree by adding the minimum-weight edge connecting it to an outside vertex. Time complexity O(V² + E).

Both algorithms are verified to produce the same total MST weight on every test graph (7 sizes, from 5 to 100,000 vertices). Kruskal's algorithm is faster on the larger graphs, while Prim's algorithm is faster on the smaller/medium graphs — Kruskal ends up roughly 1.72x faster than Prim on the 100,000-vertex test case.

Full details, algorithm steps, and test result tables: [`assignment_03/README.md`](./assignment_03/README.md)

### Assignment 04 – Vertex Coloring and PageRank

Implements and tests two graph algorithms, both built on top of the CSR graph representation (see `common/csr`).

- **Vertex Coloring (Welsh-Powell)** – greedy heuristic that orders vertices by non-increasing degree and assigns each the smallest color not used by its already-colored neighbours, on an undirected graph. Since exact graph coloring is NP-hard, this does not guarantee the minimum chromatic number.
- **PageRank** – iterative graph-ranking algorithm on a directed graph, using a damping factor of `0.85`, dangling-vertex handling, and convergence based on total rank change. Time complexity O(I(V + E)).

Vertex Coloring successfully scaled up to 100,000 vertices / 500,000 edges (using 3–7 colors depending on graph structure). PageRank converged correctly (rank sum ≈ 1.0) up to 10,000 vertices, but the 50,000- and 100,000-vertex cases could not be completed on the available system due to the cost of repeated iteration over large graphs.

Full details, algorithm steps, and test result tables: [`assignment_04/README.md`](./assignment_04/README.md)

---

## Common Components

The `common/csr` folder holds a standalone, reusable CSR (Compressed Sparse Row) implementation that is shared across assignments — used by Bellman-Ford in Assignment 02, by both Kruskal's and Prim's algorithms in Assignment 03, and by both Vertex Coloring and PageRank in Assignment 04 — rather than being reimplemented per assignment.

---

## How Results Are Measured

Across all assignments, only algorithm execution time is measured (I/O, memory allocation, CSR generation, and file handling are excluded from timing). Each algorithm is tested on a range of input sizes, from very small (5–10 elements/vertices) to large (tens of thousands to 100,000+), to observe how execution time scales — matching the theoretical time complexity of each algorithm. Where a test case could not be completed within practical limits (e.g. the largest PageRank graphs in Assignment 04), this is reported explicitly rather than estimated.
