#ifndef MST_HPP
#define MST_HPP

#include "../../common/csr/src/CSR.hpp"

struct MSTEdge
{
    int u;
    int v;
    int weight;
};

void kruskalMST(CSR &graph,MSTEdge mstEdges[],int &edgeCount,int &totalWeight);

void primMST(CSR &graph,MSTEdge mstEdges[],int &edgeCount,int &totalWeight);

#endif