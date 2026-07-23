#pragma once

#include <string>
#include <utility>
#include <vector>

#include "graph.h"
#include "canonicalDS/bitVector.h"

class GraphSequence : public graph {
    private:
        std::string name;
        int numNodes;
        int numEdges;
        std::vector<int> nodes;
        bitVector V;

        void addEdge(std::pair<int, int> edge);

    public:
        GraphSequence(std::string file, int N, int E);

        int size();
        bool adj(int n, int m) override;
        int neigh(int n, int j) override;
        int outDegree(int n) override;
};