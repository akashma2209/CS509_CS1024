#include "Floyd_Warshall.hpp"
using namespace std;


void floydWarshall(int **dis,int vertex,bool &neg_cycle)
{
    // Floyd-Warshall algorithm
    for(int k = 0; k < vertex; k++)
    {
        for(int i = 0; i < vertex; i++)  //Selecting Source Vertex
        {
            for(int j = 0; j < vertex; j++) //Selecting Destination vetrex
            {
                if(dis[i][k] != 1000000000 &&
                   dis[k][j] != 1000000000)
                {
                    if(dis[i][k] + dis[k][j] < dis[i][j])
                    {
                        dis[i][j] =dis[i][k] + dis[k][j]; //Update shortest distance
                    }
                }
            }
        }
    }

    // Check negative cycle
    neg_cycle = false;
    for(int i = 0; i < vertex; i++)
    {
        if(dis[i][i] < 0)
        {
            neg_cycle = true;
            return;
        }
    }

}