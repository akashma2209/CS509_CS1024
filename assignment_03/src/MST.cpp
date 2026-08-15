#include "MST.hpp"
#include <algorithm>
#include <climits>

int fparent(int parent[], int vertex) // Find the parent of a vertex in the Disjoint Set
{
    while(parent[vertex] != vertex)
    {
        vertex = parent[vertex];
    }
    return vertex;
}

void unionSet(int parent[], int rank[], int u, int v) // Join two sets together
{
    int par_u = fparent(parent, u);
    int par_v = fparent(parent, v);
    if(par_u == par_v)  //Checking both have same parents or not
    {
        return;
    }
    if(rank[par_u] < rank[par_v]) //Add smaller rank tree to larger tank tree
    {
        parent[par_u] = par_v;
    }
    else if(rank[par_u] > rank[par_v])
    {
        parent[par_v] = par_u;
    }
    else
    {
        parent[par_v] = par_u; // If both ranks are same make par_u the parent
        rank[par_u]++;
    }
}

// KRUSKAL
void kruskalMST(CSR &graph,MSTEdge mstEdges[],int &count,int &weight)
{
    count = 0;
    weight = 0;
    // CSR contains both directions of every undirected edge, so keep only u < v.
    int maxEdges = graph.edges;
    MSTEdge *allEdges = new MSTEdge[maxEdges];
    int c = 0;

    for(int u = 0; u < graph.vertices; u++)
    {
        for(int i = graph.row_ptr[u];i < graph.row_ptr[u + 1];i++)
        {
            int v = graph.col_idx[i];
            if(u < v)
            {
                allEdges[c].u = u;
                allEdges[c].v = v;
                allEdges[c].weight = graph.values[i];
                c++;
            }
        }
    }

    for(int i = 0; i < c - 1; i++) // Sort edges by weight
    {
        for(int j = i + 1; j < c; j++)
        {
            if(allEdges[j].weight < allEdges[i].weight)
            {
                MSTEdge temp = allEdges[i];
                allEdges[i] = allEdges[j];
                allEdges[j] = temp;
            }
        }
    }

    int *parent = new int[graph.vertices];
    int *rank = new int[graph.vertices];

    for(int i = 0; i < graph.vertices; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
    for(int i = 0; i < c; i++)
    {
        int u = allEdges[i].u;
        int v = allEdges[i].v;
        int par_u = fparent(parent, u);
        int par_v = fparent(parent, v);
        if(par_u != par_v)
        {
            mstEdges[count] = allEdges[i];
            weight += allEdges[i].weight;
            count++;
            unionSet(parent, rank, u, v);
            if(count == graph.vertices - 1)
            {
                break;
            }
        }
    }
}

// PRIM
void primMST(CSR &graph,MSTEdge mstEdges[],int &count,int &weight)
{
    count = 0;
    weight = 0;
    int vertices = graph.vertices;
    int *key = new int[vertices];
    int *parent = new int[vertices];
    bool *inMST = new bool[vertices];

    for(int i = 0; i < vertices; i++)
    {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = false;
    }
    
    key[0] = 0; // Start from vertex 0
    for(int c = 0; c < vertices; c++)
    {
        int u = -1;
        int minKey = INT_MAX;
        for(int i = 0; i < vertices; i++) // Find minimum key vertex
        {
            if(!inMST[i] && key[i] < minKey)
            {
                minKey = key[i];
                u = i;
            }
        }
        if(u == -1)
        {
            break;
        }
        inMST[u] = true;

        if(parent[u] != -1) // Add selected edge
        {
            mstEdges[count].u = parent[u];
            mstEdges[count].v = u;
            mstEdges[count].weight = key[u];
            weight += key[u];
            count++;
        }

        for(int i = graph.row_ptr[u]; i < graph.row_ptr[u + 1]; i++) // Update neighbouring vertices
        {
            int v = graph.col_idx[i];
            int weight = graph.values[i];
            if(!inMST[v] && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

}