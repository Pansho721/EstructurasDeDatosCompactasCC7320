#pragma once

#include <string>
#include <vector>

#include <sdsl/k2_tree.hpp>

#include "graph.h"

// Adjacency matrix stored as an sdsl k2-tree with k = 2.
// sdsl only answers adj, neigh and reverse_neigh, so degrees and j-th neighbors
// are derived from the full (sorted) neighbor lists.
class GraphK2Tree : public graph {
    private:
        sdsl::k2_tree<2> T;

    public:
        GraphK2Tree(const std::vector<Edge>& edges, uint64_t N);

        std::string name() override { return "GraphK2Tree"; }
        float sizePerEdge() override;
        bool supportsReverse() override { return true; }

        bool adj(uint64_t u, uint64_t v) override;
        int64_t neighj(uint64_t u, uint64_t j) override;
        std::vector<uint64_t> neigh(uint64_t u) override;
        uint64_t outDegree(uint64_t u) override;
        int64_t rneighj(uint64_t v, uint64_t j) override;
        std::vector<uint64_t> rneigh(uint64_t v) override;
        uint64_t inDegree(uint64_t v) override;
};
