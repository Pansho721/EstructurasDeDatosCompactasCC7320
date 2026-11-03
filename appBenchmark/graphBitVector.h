#pragma once

#include <string>
#include <vector>

#include <sdsl/sd_vector.hpp>

#include "graph.h"

// Adjacency matrix stored as a single Elias-Fano bitvector of length N*N,
// with bit u*N+v set iff the edge (u, v) exists.
class GraphBitVector : public graph {
    private:
        sdsl::sd_vector<> M;
        sdsl::sd_vector<>::rank_1_type rankM;
        sdsl::sd_vector<>::select_1_type selectM;

    public:
        GraphBitVector(const std::vector<Edge>& edges, uint64_t N);

        std::string name() override { return "GraphBitVector"; }
        float sizePerEdge() override;
        bool adj(uint64_t u, uint64_t v) override;
        int64_t neighj(uint64_t u, uint64_t j) override;
        std::vector<uint64_t> neigh(uint64_t u) override;
        uint64_t outDegree(uint64_t u) override;
};
