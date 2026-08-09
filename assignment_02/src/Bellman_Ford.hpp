#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP
#include "../../common/csr/src/CSR.hpp"

void bellmanFord( CSR graph, int source, int *dis, bool &neg_cycle);
#endif