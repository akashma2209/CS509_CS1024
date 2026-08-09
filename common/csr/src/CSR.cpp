#include "CSR.hpp"

CSR convertToCSR(int source[], int destination[], int weight[], int edges, int vertex)
{
    CSR graph;
    graph.vertices = vertex;
    graph.edges = edges;
    graph.row_ptr = new int[vertex + 1];  //row_ptr store V+1 elements.
    graph.col_idx = new int[edges]; //col_idx have E element
    graph.values = new int[edges];  ////value have E element
    
    for(int i = 0; i <= vertex; i++) // Initialize row_ptr to 0
    {
        graph.row_ptr[i] = 0;
    }
    for(int i = 0; i < edges; i++) // Count outgoing edges of every vertex
    {
        graph.row_ptr[source[i] + 1]++;
    }
    for(int i = 1; i <= vertex; i++)
    {
        graph.row_ptr[i] += graph.row_ptr[i - 1];
    }
    
    int *temp = new int[vertex]; 
    for(int i = 0; i < vertex; i++) // Temporary arrey to track next available position of each source index
    {
        temp[i] = graph.row_ptr[i];
    }
    
    for(int i = 0; i < edges; i++) // Fill CSR arrays
    {
        int pos = temp[source[i]];
        graph.col_idx[pos] = destination[i];
        graph.values[pos] = weight[i];
        temp[source[i]]++;
    }
    return graph;
}