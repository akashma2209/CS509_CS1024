#include <iostream>
using namespace std;
#include "CSR_Graph.hpp"

CSR convertToCSR(int source[], int destination[], int weight[], int edges, int vertices)
{
    CSR graph;
    // Storing Graph Information
    graph.vertices = vertices;
    graph.edges = edges;
    //Assingning memory to CSR Array
    graph.row_ptr = new int[vertices + 1];
    graph.col_idx = new int[edges];
    graph.values = new int[edges];

    // Initialize row_ptr
    for(int i = 0; i <= vertices; i++)
    {
        graph.row_ptr[i] = 0;
    }

    // Count edges of every source vertex
    for(int i = 0; i < edges; i++)
    {
        graph.row_ptr[source[i] + 1]++;
    }

    // Create row_ptr
    for(int i = 1; i <= vertices; i++)
    {
        graph.row_ptr[i] += graph.row_ptr[i - 1];
    }

    // Temporary positions
    int *temp = new int[vertices];
    for(int i = 0; i < vertices; i++)
    {
        temp[i] = graph.row_ptr[i];
    }

    // Fill CSR arrays
    for(int i = 0; i < edges; i++)
    {
        int pos = temp[source[i]];

        graph.col_idx[pos] = destination[i];
        graph.values[pos] = weight[i];
        temp[source[i]]++;
    }
    delete[] temp;
    return graph;
}