#ifndef PAGERANK_HPP
#define PAGERANK_HPP

#include "../../common/csr/src/CSR.hpp"

void pageRank(
    CSR &graph,
    double damping,
    double tolerance,
    int maxIterations,
    double rank[],
    int &iterations,
    bool &converged
);

#endif