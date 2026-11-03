#include "graphK2Tree.h"

#include <tuple>

GraphK2Tree::GraphK2Tree(const std::vector<Edge>& edges, uint64_t N){
    std::vector<std::tuple<uint64_t, uint64_t>> tuples;
    tuples.reserve(edges.size());
    for(const Edge& edge : edges){
        tuples.emplace_back(edge.first, edge.second);
    }
    T = sdsl::k2_tree<2>(tuples, N);
    n = N;
    e = edges.size();
}

float GraphK2Tree::sizePerEdge(){
    return 8.0f * sdsl::size_in_bytes(T) / e;
}

bool GraphK2Tree::adj(uint64_t u, uint64_t v){
    if(u >= n || v >= n) return false;
    return T.adj(u, v);
}

int64_t GraphK2Tree::neighj(uint64_t u, uint64_t j){
    if(u >= n) return -1;
    std::vector<uint64_t> neighbors = T.neigh(u);
    return j < neighbors.size() ? static_cast<int64_t>(neighbors[j]) : -1;
}

std::vector<uint64_t> GraphK2Tree::neigh(uint64_t u){
    if(u >= n) return {};
    return T.neigh(u);
}

uint64_t GraphK2Tree::outDegree(uint64_t u){
    if(u >= n) return 0;
    return T.neigh(u).size();
}

int64_t GraphK2Tree::rneighj(uint64_t v, uint64_t j){
    if(v >= n) return -1;
    std::vector<uint64_t> neighbors = T.reverse_neigh(v);
    return j < neighbors.size() ? static_cast<int64_t>(neighbors[j]) : -1;
}

std::vector<uint64_t> GraphK2Tree::rneigh(uint64_t v){
    if(v >= n) return {};
    return T.reverse_neigh(v);
}

uint64_t GraphK2Tree::inDegree(uint64_t v){
    if(v >= n) return 0;
    return T.reverse_neigh(v).size();
}
