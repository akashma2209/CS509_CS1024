#ifndef CSR_HPP
#define CSR_HPP


struct CSR
{
    int *row_ptr;
    int *col_idx;
    int *values;

    int vertices;
    int edges;
};


// Convert Edge List to CSR

CSR convertToCSR(
    int source[],
    int destination[],
    int weight[],
    int edges,
    int vertices
);


// Example CSR operation
void printCSR(CSR graph);


#endif