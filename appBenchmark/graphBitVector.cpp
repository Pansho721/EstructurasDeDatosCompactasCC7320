#include "graphBitVector.h"

GraphBitVector::GraphBitVector(const std::vector<Edge>& edges, uint64_t N){
    // Edges are sorted by (u, v), so the positions u*N+v are strictly increasing.
    sdsl::sd_vector_builder builder(N * N, edges.size());
    for(const Edge& edge : edges){
        builder.set(edge.first * N + edge.second);
    }
    M = sdsl::sd_vector<>(builder);
    sdsl::util::init_support(rankM, &M);
    sdsl::util::init_support(selectM, &M);
    n = N;
    e = edges.size();
}

float GraphBitVector::sizePerEdge(){
    const uint64_t bytes = sdsl::size_in_bytes(M) + sdsl::size_in_bytes(rankM) + sdsl::size_in_bytes(selectM);
    return 8.0f * bytes / e;
}

bool GraphBitVector::adj(uint64_t u, uint64_t v){
    if(u >= n || v >= n) return false;
    return M[u * n + v];
}

int64_t GraphBitVector::neighj(uint64_t u, uint64_t j){
    if(u >= n) return -1;
    const uint64_t before = rankM(u * n);
    if(j >= rankM((u + 1) * n) - before) return -1;
    return selectM(before + j + 1) - u * n;
}

std::vector<uint64_t> GraphBitVector::neigh(uint64_t u){
    if(u >= n) return {};
    const uint64_t before = rankM(u * n);
    const uint64_t deg = rankM((u + 1) * n) - before;
    std::vector<uint64_t> neighbors(deg);
    for(uint64_t j = 0; j < deg; ++j){
        neighbors[j] = selectM(before + j + 1) - u * n;
    }
    return neighbors;
}

uint64_t GraphBitVector::outDegree(uint64_t u){
    if(u >= n) return 0;
    return rankM((u + 1) * n) - rankM(u * n);
}
