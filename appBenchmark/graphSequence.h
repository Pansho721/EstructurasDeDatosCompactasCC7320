#pragma once

#include <string>
#include <utility>
#include <vector>

#include "graph.h"
#include "canonicalDS/bitVector.h"
#include "canonicalDS/Sequence.h"

class GraphSequence : public graph {
    private:
        int numNodes;
        int numEdges;
        Sequence N;
        bitVector B;

    public:
        GraphSequence(std::string file, int N, int E);

        int size();
        bool adj(int n, int m) override;
        int neigh(int n, int j) override;
        int rneigh(int n, int j) override;
        int outDegree(int n) override;
        int inDegree(int n) override;
};