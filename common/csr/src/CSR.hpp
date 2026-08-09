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

CSR convertToCSR(int source[], int destination[], int weight[], int edges, int vertices);
#endif