# CS509 Laboratory Repository

---

**CS509 - PG Software Lab**

# Repository Overview

## Course

The  objective of this assignment is to implement and analyze efficient  algorithms using C++. Here are the Implementation I have done:

- **General Matrix Multiplication (GEMM)**
  - Simple GEMM implementation using the traditional triple nested loop approach.
  - Blocking GEMM implementation using cache-friendly matrix blocking optimization.

- **CSR (Compressed Sparse Row) Graph Conversion**
  - Conversion of graph adjacency list representation into CSR format.
  - Generation of CSR arrays:
    - `row_ptr`
    - `col_idx`
    - `values`
      

The code are stored in separate files
- Algorithm logic is stored inside the `src`.
- Driver programs are provided for executing and testing.
- Input test cases are stored in `tests`.
- Result and execution time is stored in the `outputs` directory.
- After compilation executable files are stored separately in `executables` directory.

A common wrapper file execute all code at single interface at terminal.

---

# Student Details

| Field | Information |
|-------|-------------|
| Student Name | Akash Maurya |
| Entry Number | 2026CSM1024 |
| Assignment No. | 1|
| Programming Language | C++ |

---

# Language and Environment

The complete repository has been implemented using modern C++ following the laboratory guidelines.

## Programming Language

```
C++
```

## Language Standard

```
C++17
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

# Repository Directory Structure

```
CS509_CS1024
│
├── README.md
│
├── Makefile
│
├── wrapper
│   │
│   ├── wrapper.cpp
│   └── wrapper.exe
│
├── assignment_01
│   │
│   ├── README.md
│   │
│   ├── driver
│   │   │
│   │   ├── driver_matrix.cpp
│   │   └── driver_csr.cpp
│   │
│   ├── src
│   │   │
│   │   ├── GEMM_Simple.cpp
│   │   ├── GEMM_Simple.hpp
│   │   │
│   │   ├── GEMM_Blocking.cpp
│   │   ├── GEMM_Blocking.hpp
│   │   │
│   │   ├── CSR_Graph.cpp
│   │   └── CSR_Graph.hpp
│   │
│   ├── tests
│   │   │
│   │   ├── matrix
│   │   │   ├── gemm_test_01.txt
│   │   │   ├── gemm_test_02.txt
│   │   │   └── ...
│   │   │
│   │   └── csr_graph
│   │       ├── csr_test_01.txt
│   │       ├── csr_test_02.txt
│   │       └── ...
│   │
│   ├── outputs
│   │   │
│   │   ├── matrix
│   │   │   ├── simple
│   │   │   └── blocking
│   │   │
│   │   └── graph
│   │       └── csr
│   │
│   └── executables
│       ├── matrix.exe
│       └── csr.exe
│
├── assignment_02
```

---


# Common Wrapper

The wrapper work as the main interface of the repository.

Instead of manually compiling each assignment, the wrapper allows the user to select and execute assignments from a single menu.

---

# Building the Wrapper

There are two methods for building the wrapper.

## Method 1 – Using Makefile (Recommended)

From the repository root directory, execute:

```bash
make
```

or

```bash
make wrapper
```

The Makefile automatically compiles the wrapper program and generates

```
wrapper.exe
```

---

## Method 2 – Manual Compilation

Compile the wrapper manually using g++:

```bash
g++ -std=c++17 wrapper/wrapper.cpp -o wrapper/wrapper.exe
```

---

# Running the Wrapper

After successful compilation, execute:

```bash
wrapper/wrapper.exe
```

or from Windows Command Prompt:

```cmd
wrapper\wrapper.exe
```

# Assignment 01 
1 - General Matrix Multiplication (GEMM)
---

# Objective

The objective of this assignment is to implement and compare two different approaches for performing matrix multiplication.

The algorithms implemented are:

1. **Simple GEMM (General Matrix Multiplication)**
2. **Blocking GEMM (Cache Optimized Matrix Multiplication)**


---
# Algorithm 1 – Simple GEMM

## Description

The Simple GEMM implementation follows the traditional matrix multiplication algorithm using three nested loops.

The algorithm processes the matrices row by row and column by column.

For every element in the result matrix:

1. Select one row from matrix A.
2. Select one column from matrix B.
3. Multiply corresponding elements.
4. Add the products together.
5. Store the final value in the output matrix.

This implementation is simple and easy to understand but performs a large number of memory accesses.

---

## Working

The computation follows these nested loops:

```
for each row i

    for each column j

        for every element k

            C[i][j] += A[i][k] × B[k][j]
```

---


---

# Algorithm 2 – Blocking GEMM

## Description

Blocking GEMM is an optimized version of matrix multiplication.

Instead of multiplying the entire matrices at once, the matrices are divided into smaller blocks called **tiles**.

The multiplication is performed one block at a time.

This approach allows data loaded into the CPU cache to be reused multiple times before it is replaced, significantly reducing cache misses.

---

## Block Size

The implementation uses

```
64 × 64
```

blocks.

```
Block Size = 64
```

---

## Working

Instead of iterating over complete rows and columns, the algorithm processes the matrices in blocks.

The outer loops iterate over:

```
ii

kk

jj
```

Each of these represents one block.

Inside each block, normal matrix multiplication is performed.

The overall computation is

```
for every block of rows

    for every block of columns

        for every block of K

            multiply the block
```

---

---


## Matrix Dimensions

The first line contains

```
M K N
```

where

```
M = Number of rows in Matrix A

K = Number of columns in Matrix A
    Number of rows in Matrix B

N = Number of columns in Matrix B
```

---




# GEMM Result Table

| Test File | Input Type / Size | Expected Output | Actual Output | Simple Time | Blocking Time | Block Size | Status |
|-----------|-------------------|-----------------|---------------|-------------|---------------|------------|--------|
| gemm_test_01.txt | 4 × 4 and 4 × 4 | In Output file | In Output file | 0.0013 ms | 0.0013 ms | 64 | Pass |
| gemm_test_02.txt | 10 × 10 and 10 × 10 | In Output file | In Output file | 0.0094 ms | 0.0088 ms | 64 | Pass |
| gemm_test_03.txt | 800 × 800 and 800 × 800 | In Output file | In Output file | 4229.43 ms | 2050.54 ms | 64 | Pass |
| gemm_test_04.txt | 1000 × 1000 and 1000 × 1000 | In Output file | In Output file | 5710.29 ms | 4264.9 ms | 64 | Pass |
| gemm_test_05.txt | 2000 × 2000 and 2000 × 2000 | In Output file | In Output file | 61695 ms | 26226.3 ms | 64 | Pass |
---

# Observations

- Both code produced same output for same input .
- Blocking GEMM is taking more or equal time as Simple GEMM multiplication for smaller matrix.
- For Larger matrix input Blocking GEMM is much faster than Simple GEMM.
- This tells that as the size of matrix get bigger execution time of Blocking GEMM is gets better
- My observation is till 2000 by 2000 matrix as my system supported till that.

---

# 2 – CSR Graph Representation

---

# Introduction to CSR (Compressed Sparse Row)

Compressed Sparse Row (CSR) is one of the most widely used data structures for storing sparse matrices and sparse graphs.

In a sparse graph, most possible edges do not exist. Storing such graphs using an adjacency matrix wastes a significant amount of memory because many entries contain zero values.

CSR stores only the existing edges, making it much more memory efficient.

Instead of storing all possible edges, CSR uses three one-dimensional arrays:

1. **row_ptr**
2. **col_idx**
3. **values**

Together, these arrays completely represent the graph.

---

# CSR Data Structure

## 1. row_ptr

The `row_ptr` array stores the starting index of the adjacency list of every vertex.

Its size is always:

```
Vertices + 1
```

The last element indicates the total number of edges.

Example:

```
row_ptr

0 2 5 6 8
```

This means

- Vertex 0 starts from index 0
- Vertex 1 starts from index 2
- Vertex 2 starts from index 5
- Vertex 3 starts from index 6

---

## 2. col_idx

The `col_idx` array stores the destination vertex of every edge.

Example

```
1 3 0 2 4 1 2 0
```

Each entry represents one neighbouring vertex.

---

## 3. values

The `values` array stores the corresponding edge weights.

Example

```
5 2 7 1 9 4 3 6
```

The index of `values` always matches the index of `col_idx`.

---

# CSR Result Table

| Test File | Input Type | Input Size | Expected Output | Actual Output | Algorithm Time | Status |
|-----------|------------|------------|-----------------|---------------|----------------|--------|
| csr_test_01.txt | Adjacency List → CSR | V = 5, E = 100 | CSR Representation | CSR Representation | 0.004 ms | Pass |
| csr_test_02.txt | Adjacency List → CSR | V = 100, E = 500 | CSR Representation | CSR Representation | 0.0057 ms  | Pass |
| csr_test_03.txt | Adjacency List → CSR | V = 5, E = 100 | CSR Representation | CSR Representation | 0.0021 ms | Pass |
| csr_test_04.txt | Adjacency List → CSR | V = 100, E = 500 | CSR Representation | CSR Representation | 0.0066 ms | Pass |
| csr_test_05.txt | Adjacency List → CSR | V = 1000, E = 3000 | CSR Representation | CSR Representation | 0.0553 ms | Pass |

---

# Observations

- The CSR representation stores only the existing edges, making it significantly more memory efficient than an adjacency matrix for sparse graphs.
- The `row_ptr` array allows direct access to the neighbour list of any vertex.
- The generated CSR structure serves as an efficient input format for graph algorithms such as BFS, DFS, Dijkstra's Algorithm, and other sparse graph operations.
- The implementation follows the laboratory guideline by separating graph preprocessing (CSR conversion) from future graph algorithm execution.
- As size input size increase  time complexity also increse

---
