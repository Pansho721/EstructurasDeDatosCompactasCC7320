#include "graphSequence.h"

#include <cstdio>
#include <filesystem>

#include <sdsl/int_vector_buffer.hpp>

GraphSequence::GraphSequence(const std::vector<Edge>& edges, uint64_t N){
    n = N;
    e = edges.size();

    // Targets in source order. sdsl builds wavelet matrices from an on-disk buffer.
    sdsl::int_vector<> targets(e, 0, sdsl::bits::hi(N) + 1);
    for(uint64_t i = 0; i < e; ++i){
        targets[i] = edges[i].second;
    }
    const std::string tmp = sdsl::tmp_file((std::filesystem::temp_directory_path() / "graphSequence").string(), "_S");
    sdsl::store_to_file(targets, tmp);
    {
        sdsl::int_vector_buffer<> buf(tmp);
        S = sdsl::wm_int<sdsl::rrr_vector<63>>(buf, buf.size());
    }
    std::remove(tmp.c_str());

    sdsl::sd_vector_builder builder(N + e + 1, N + 1);
    uint64_t i = 0;
    for(uint64_t u = 0; u <= N; ++u){
        builder.set(u + i);
        while(i < e && edges[i].first == u) ++i;
    }
    B = sdsl::sd_vector<>(builder);
    sdsl::util::init_support(rankB, &B);
    sdsl::util::init_support(selectB, &B);
    sdsl::util::init_support(select0B, &B);
}

uint64_t GraphSequence::start(uint64_t u){
    return selectB(u + 1) - u;
}

uint64_t GraphSequence::end(uint64_t u){
    return selectB(u + 2) - (u + 1);
}

float GraphSequence::sizePerEdge(){
    const uint64_t bytes = sdsl::size_in_bytes(S) + sdsl::size_in_bytes(B)
        + sdsl::size_in_bytes(rankB) + sdsl::size_in_bytes(selectB) + sdsl::size_in_bytes(select0B);
    return 8.0f * bytes / e;
}

bool GraphSequence::adj(uint64_t u, uint64_t v){
    if(u >= n || v >= n) return false;
    return S.rank(end(u), v) > S.rank(start(u), v);
}

int64_t GraphSequence::neighj(uint64_t u, uint64_t j){
    if(u >= n) return -1;
    const uint64_t s = start(u);
    if(s + j >= end(u)) return -1;
    return S[s + j];
}

std::vector<uint64_t> GraphSequence::neigh(uint64_t u){
    if(u >= n) return {};
    const uint64_t s = start(u);
    const uint64_t t = end(u);
    std::vector<uint64_t> neighbors;
    neighbors.reserve(t - s);
    for(uint64_t p = s; p < t; ++p){
        neighbors.push_back(S[p]);
    }
    return neighbors;
}

uint64_t GraphSequence::outDegree(uint64_t u){
    if(u >= n) return 0;
    return end(u) - start(u);
}

int64_t GraphSequence::rneighj(uint64_t v, uint64_t j){
    if(v >= n || j >= inDegree(v)) return -1;
    const uint64_t p = S.select(j + 1, v);
    // The (p+1)-th zero of B is edge p; the number of ones before it is source + 1.
    return rankB(select0B(p + 1)) - 1;
}

std::vector<uint64_t> GraphSequence::rneigh(uint64_t v){
    if(v >= n) return {};
    const uint64_t deg = inDegree(v);
    std::vector<uint64_t> neighbors(deg);
    for(uint64_t j = 0; j < deg; ++j){
        neighbors[j] = rneighj(v, j);
    }
    return neighbors;
}

uint64_t GraphSequence::inDegree(uint64_t v){
    if(v >= n) return 0;
    return S.rank(e, v);
}
