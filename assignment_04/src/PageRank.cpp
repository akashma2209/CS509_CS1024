#include "PageRank.hpp"
#include <cmath>
using namespace std;

void pageRank( CSR &graph, double damping, double tolerance, int maxIterations, double rank[], int &iterations, bool &converged)
{
    int vertex = graph.vertices;

    // Allocate array for ranks of previous iteration
    double *oldRank = new double[vertex];

    double initialRank = 1.0 / vertex;
    for(int i = 0; i < vertex; i++) // Initialize every vertex with 1 / N
    {
        rank[i] = initialRank;
    }
    converged = false;
    iterations = 0;
    
    for(int iteration = 1; iteration <= maxIterations; iteration++) // PageRank iterations
    {
        
        for(int i = 0; i < vertex; i++)  // Copy current ranks into oldRank.
        {
            oldRank[i] = rank[i];
        }

        double danglingRank = 0.0;
        for(int u = 0; u < vertex; u++) // Calculate total rank of dangling vertices.
        {
            int outdegree = graph.row_ptr[u + 1] - graph.row_ptr[u];
            if(outdegree == 0)
            {
                danglingRank += oldRank[u];
            }
        }

        double totalChange = 0.0;
        for(int v = 0; v < vertex; v++) // Calculate new PageRank for every vertex
        {
            double newRank = (1.0 - damping) / vertex; // Base contribution
            newRank += damping * danglingRank / vertex;

            double incomingContribution = 0.0;
            for(int u = 0; u < vertex; u++) // Contribution from normal incoming vertices
            {
                int start = graph.row_ptr[u];
                int end = graph.row_ptr[u + 1];
                int outdegree = end - start;
                if(outdegree == 0)
                {
                    continue;
                }
                for(int j = start; j < end; j++)
                {
                    int destination = graph.col_idx[j];
                    if(destination == v)
                    {
                        incomingContribution += oldRank[u] / outdegree;
                    }
                }
            }
            newRank += damping * incomingContribution;
            rank[v] = newRank;
            totalChange += fabs(rank[v] - oldRank[v]);  // Calculate total change
        }
        iterations = iteration;
        if(totalChange <= tolerance) // Check convergence
        {
            converged = true;
            break;
        }
    }

    delete[] oldRank;
}