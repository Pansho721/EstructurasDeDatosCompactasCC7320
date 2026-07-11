#pragma once

#include <string>
#include <utility>
#include <vector>

#include "graph.h"

class bitVector {
    private:
        int size;
        std::vector<bool> bits;
        std::vector<int> acc;

        int bsrch(int rank);

    public:
        bitVector();
        explicit bitVector(int s);

        void setBit(int index);
        void finishSetUp();
        bool access(int index);
        int rank1(int index);
        int select1(int rank);
};

class GraphSequence : public graph {
    private:
        std::string name;
        int numNodes;
        int numEdges;
        std::vector<int> nodes;
        std::vector<bitVector> adjM;

        void addEdge(std::pair<int, int> edge);

    public:
        GraphSequence(std::string file, int N, int E);

        int size();
        bool adj(int n, int m) override;
        int neigh(int n, int j) override;
        int outDegree(int n) override;
};