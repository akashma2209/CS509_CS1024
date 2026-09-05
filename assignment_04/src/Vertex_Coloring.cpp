#include "Vertex_Coloring.hpp"
using namespace std;

void vertexColoring( CSR &graph, int color[], int &colorsUsed, bool &valid)
{
    int vertex = graph.vertices;
    for(int i = 0; i < vertex; i++)  // Initialize all colors to -1
    {
        color[i] = -1;
    }

    colorsUsed = 0;
    int *degree = new int[vertex]; // Calculate degree of every vertex
    int maxDegree = 0;
    for(int i = 0; i < vertex; i++)
    {
        degree[i] = graph.row_ptr[i + 1] - graph.row_ptr[i];
        if(degree[i] > maxDegree)
        {
            maxDegree = degree[i];
        }
    }

    int *count = new int[maxDegree + 1];
    for(int i = 0; i <= maxDegree; i++)  // Counting sort vertices by decreasing degree
    {
        count[i] = 0;
    }

    for(int i = 0; i < vertex; i++) // Count how many vertices have each degree
    {
        count[degree[i]]++;
    }

    int position = 0;
    for(int d = maxDegree; d >= 0; d--) // Convert counts into starting positions
    {
        int numberOfVertices = count[d];
        count[d] = position;
        position += numberOfVertices;
    }

    int *order = new int[vertex];  // Create vertex ordering
    for(int i = 0; i < vertex; i++) // Place vertices according to degree
    {
        int d = degree[i];
        order[count[d]] = i;
        count[d]++;
    }

    
    bool *usedColor = new bool[vertex + 1]; // Welsh-Powell coloring
    for(int position = 0; position < vertex; position++)
    {
        int u = order[position];
        for(int c = 0; c <= vertex; c++) // Reset used colors
        {
            usedColor[c] = false;
        }
        // Get neighbours of vertex u
        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];
        
        for(int i = start; i < end; i++) // Check colors of already-colored neighbours
        {
            int v = graph.col_idx[i];
            if(color[v] != -1)
            {
                usedColor[color[v]] = true;
            }
        }
        // Find smallest available color
        int currentColor = 0;
        while(usedColor[currentColor])
        {
            currentColor++;
        }
        // Assign color
        color[u] = currentColor;
        // Update number of colors used
        if(currentColor + 1 > colorsUsed)
        {
            colorsUsed = currentColor + 1;
        }
    }

    // Verify coloring
    valid = true;
    for(int u = 0; u < vertex; u++)
    {
        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];
        for(int i = start; i < end; i++)
        {
            int v = graph.col_idx[i];
            if(color[u] == color[v]) // Adjacent vertices must have  different colors
            {
                valid = false;
                break;
            }
        }
        if(!valid)
        {
            break;
        }
    }

    // Free temporary arrays
    delete[] degree;
    delete[] count;
    delete[] order;
    delete[] usedColor;
}