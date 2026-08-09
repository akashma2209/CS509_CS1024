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
├── README.md                  <- you are here
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
└── assignment_02/              <- Shortest path algorithms
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

---

## Common Components

The `common/csr` folder holds a standalone, reusable CSR (Compressed Sparse Row) implementation that is shared across assignments (used by Bellman-Ford in Assignment 02) rather than being reimplemented per assignment.

---

## How Results Are Measured

Across both assignments, only algorithm execution time is measured (I/O, memory allocation, and file handling are excluded from timing). Each algorithm is tested on a range of input sizes, from very small (5–10 elements/vertices) to large (thousands), to observe how execution time scales — matching the theoretical time complexity of each algorithm.