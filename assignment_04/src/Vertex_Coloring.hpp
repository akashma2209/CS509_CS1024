#ifndef VERTEX_COLORING_HPP
#define VERTEX_COLORING_HPP

#include "../../common/csr/src/CSR.hpp"

void vertexColoring(
    CSR &graph,
    int color[],
    int &colorsUsed,
    bool &valid
);

#endif