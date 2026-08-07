#pragma once

#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <string>

#include "graph.h"
#include "canonicalDS/sparseBitVector.h"

class GraphBitVector : public graph {
    private:
        int numNodes;
        int numEdges;
        std::vector<sparseBitVector> adjM;

        void addEdge(std::pair<int, int> edge);

    public:
        GraphBitVector(std::string file, int N, int E);

        float sizePerEdge();
        bool adj(int n, int m) override;
        int neigh(int n, int j) override;
        int outDegree(int n) override;
};