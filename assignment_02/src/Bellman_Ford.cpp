#include <climits>
#include "Bellman_Ford.hpp"
using namespace std;

void bellmanFord(CSR graph,int source,int *dis,bool &neg_cycle)
{
    int vertex = graph.vertices;
    for(int i = 0; i < vertex; i++) // Initialize distances to max
    {
        dis[i] = INT_MAX;
    }
    dis[source] = 0; //Distance form sorce vertex for itsefl is zero
    // Update shortest distances by checking all edges V-1 times
    for(int i = 0; i < vertex - 1; i++)
    {
        bool changed = false;
        for(int u = 0; u < vertex; u++)
        {
            if(dis[u] == INT_MAX) //check vertex is reachable for other process
                continue;

            for(int j = graph.row_ptr[u];j < graph.row_ptr[u + 1];j++)
            {
                int v = graph.col_idx[j];
                int weight = graph.values[j];
                if(dis[u] + weight < dis[v])
                {
                    dis[v] = dis[u] + weight;
                    changed = true;
                }
            }
        }
        if(!changed)
            break;
    }
    
    neg_cycle = false; // Check for reachable negative cycle
    for(int u = 0; u < vertex; u++) //Checking for reachable negitive cycle
    {
        if(dis[u] == INT_MAX) //Ignoring vertex that are unreachable
            continue;
        for(int j = graph.row_ptr[u]; j < graph.row_ptr[u + 1]; j++)
        {
            int v = graph.col_idx[j];
            int weight = graph.values[j];
            if(dis[u] + weight < dis[v])
            {
                neg_cycle = true;
                return;
            }
        }
    }
}


// g++ -std=c++17 assignment_02\driver\driver_bellman_ford.cpp assignment_02\src\Bellman_Ford.cpp common\csr\src\CSR.cpp -o assignment_02\executables\bellman_ford.exe

// .\assignment_02\executables\bellman_ford.exe