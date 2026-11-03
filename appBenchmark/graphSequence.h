#pragma once

#include <string>
#include <vector>

#include <sdsl/rrr_vector.hpp>
#include <sdsl/sd_vector.hpp>
#include <sdsl/wm_int.hpp>

#include "graph.h"

// Concatenation of all adjacency lists (sorted by source) stored in a wavelet matrix
// over RRR-compressed bitvectors, plus a unary-coded degree bitvector B:
// B has a 1 at position u + start(u) for every u in [0, N], and a 0 for every edge.
class GraphSequence : public graph {
    private:
        sdsl::wm_int<sdsl::rrr_vector<63>> S;
        sdsl::sd_vector<> B;
        sdsl::sd_vector<>::rank_1_type rankB;
        sdsl::sd_vector<>::select_1_type selectB;
        sdsl::sd_vector<>::select_0_type select0B;

        uint64_t start(uint64_t u);  // first position of u's list in S
        uint64_t end(uint64_t u);    // one past the last position of u's list in S

    public:
        GraphSequence(const std::vector<Edge>& edges, uint64_t N);

        std::string name() override { return "GraphSequence"; }
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
