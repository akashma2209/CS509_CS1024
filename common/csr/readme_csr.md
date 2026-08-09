# Common CSR Module

## Overview

This folder contains the  **Compressed Sparse Row (CSR)** implementation used by the current and future assignments.

The purpose of this module is to convert graph input given in adjacency-list format into CSR representation.


---

## Directory Structure

```text
common/
└── csr/
    │
    ├── README.md
    ├── test_csr.cpp          ← CSR working/test program
    │
    ├── src/
    │   ├── CSR.hpp
    │   ├── CSR.cpp
    │   ├── driver_csr.hpp
    │   └── driver_csr.cpp
    │
    ├── test_CSR/
    │   ├── test_01.txt
    │   ├── test_02.txt
    │   ├── test_03.txt
    │   ├── test_04.txt
    │   ├── test_05.txt
    │   └── test_06.txt
    │
    └── outputs/
        └── graph/

        
```

---

## CSR Representation

CSR stores a graph using three arrays:

### row_ptr
Stores the starting and ending positions of the edges belonging to each vertex.

### col_idx
Stores the destination vertex of each edge.

### values
Stores the weight of each edge.

For an unweighted graph, a default weight of `1` is assigned internally.

---

## Input

The CSR module accepts graph input in adjacency-list format.

The first line contains:

- `V` = number of vertices
- `E` = number of edges

The following lines contain the adjacency information.

For an unweighted graph:

```text
vertex degree neighbour1 neighbour2 ...
```

For a weighted graph:

```text
vertex degree destination1 weight1 destination2 weight2 ...
```

A source vertex is provided at the end of the input file.

---

## Output

The generated CSR output contains:

```text
Number of Vertices Number of Edges
row_ptr
col_idx
values
source vertex
```

For unweighted graphs, the `values` array is internally assigned a default weight of `1`.

---

## Source Files

### CSR.cpp

Contains the main CSR conversion function:

### CSR.hpp

Contains the CSR structure and function declaration.

### driver_csr.cpp

Reads graph test files, identifies whether the graph is weighted or unweighted, calls the CSR conversion function, and writes the generated CSR representation.

### driver_csr.hpp

Contains declarations related to the CSR driver.

---

## Testing and Verification

The `test_csr.cpp` file is a small verification program used to check whether the common CSR conversion implementation is working correctly.

It is separate from the assignment driver and is only used for basic testing of the CSR module.


## Purpose in the Repository

This module is designed to be reused by multiple assignments.

Instead of maintaining separate CSR implementations in every assignment, future graph assignments can use:

```text
common/csr/
```

as the common CSR component.