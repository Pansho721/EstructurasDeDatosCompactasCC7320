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
        std::unordered_set<long long> edgeIndex;

        static long long encodeEdge(int from, int to);

    public:
        GraphSequence(std::string file, int N, int E);

        int size();
        bool adj(int n, int m) override;
        int neigh(int n, int j) override;
        int rneigh(int n, int j) override;
        int outDegree(int n) override;
        int inDegree(int n) override;
};