#pragma once

#include <string>
#include <utility>
#include <unordered_set>
#include <vector>

#include "graph.h"
#include "canonicalDS/sparseBitVector.h"
#include "canonicalDS/Sequence.h"

class GraphSequence : public graph {
    private:
        int numNodes;
        int numEdges;
        Sequence N;
        sparseBitVector B;

    public:
        GraphSequence(std::string file, int N, int E);

        float sizePerEdge();
        bool adj(int n, int m) override;
        int neighj(int n, int j) override;
        std::vector<int> neigh(int n) override;
        int rneighj(int n, int j) override;
        std::vector<int> rneigh(int n) override;
        int outDegree(int n) override;
        int inDegree(int n) override;
};