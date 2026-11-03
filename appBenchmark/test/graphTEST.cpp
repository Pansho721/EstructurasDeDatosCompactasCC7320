// Checks a compact graph against plain adjacency lists built from the same edge list.
// Usage: graphTEST <bv|sq|k2> <graph_file>
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "../graph.h"
#include "../graphBitVector.h"
#include "../graphK2Tree.h"
#include "../graphSequence.h"

static int failures = 0;

static void expect(bool ok, const std::string& what){
    if(ok) return;
    if(++failures <= 20) std::cout << "Mismatch: " << what << std::endl;
}

int main(int argc, char* argv[]){
    if(argc < 3){
        std::cerr << "Usage: " << argv[0] << " <bv|sq|k2> <graph_file>" << std::endl;
        return 1;
    }
    const std::string kind = argv[1];
    uint64_t N;
    std::vector<Edge> edges = loadEdges(argv[2], N);

    std::unique_ptr<graph> g;
    if(kind == "bv") g = std::make_unique<GraphBitVector>(edges, N);
    else if(kind == "sq") g = std::make_unique<GraphSequence>(edges, N);
    else if(kind == "k2") g = std::make_unique<GraphK2Tree>(edges, N);
    else { std::cerr << "Unknown graph kind: " << kind << std::endl; return 1; }

    std::cout << "Testing " << g->name() << " (" << N << " nodes, " << edges.size() << " edges)" << std::endl;

    std::vector<std::vector<uint64_t>> out(N), in(N);
    for(const Edge& e : edges){
        out[e.first].push_back(e.second);
        in[e.second].push_back(e.first);  // edges are sorted, so in-lists come out sorted too
    }

    expect(g->numNodes() == N && g->numEdges() == edges.size(), "node/edge count");
    for(uint64_t u = 0; u < N; ++u){
        expect(g->outDegree(u) == out[u].size(), "outDegree(" + std::to_string(u) + ")");
        expect(g->neigh(u) == out[u], "neigh(" + std::to_string(u) + ")");
        for(uint64_t j = 0; j < out[u].size(); ++j){
            expect(g->neighj(u, j) == static_cast<int64_t>(out[u][j]), "neighj(" + std::to_string(u) + ", " + std::to_string(j) + ")");
        }
        expect(g->neighj(u, out[u].size()) == -1, "neighj out of range for " + std::to_string(u));
        if(g->supportsReverse()){
            expect(g->inDegree(u) == in[u].size(), "inDegree(" + std::to_string(u) + ")");
            expect(g->rneigh(u) == in[u], "rneigh(" + std::to_string(u) + ")");
        }
    }

    for(const Edge& e : edges){
        expect(g->adj(e.first, e.second), "adj(" + std::to_string(e.first) + ", " + std::to_string(e.second) + ") should be true");
    }
    std::mt19937_64 rng(7);
    std::uniform_int_distribution<uint64_t> node(0, N - 1);
    for(int i = 0; i < 200000; ++i){
        const uint64_t u = node(rng), v = node(rng);
        const bool expected = std::binary_search(out[u].begin(), out[u].end(), v);
        expect(g->adj(u, v) == expected, "adj(" + std::to_string(u) + ", " + std::to_string(v) + ")");
    }

    if(failures == 0){
        std::cout << "PASS: " << g->name() << " (" << g->sizePerEdge() << " bits per edge)" << std::endl;
        return 0;
    }
    std::cout << "FAIL: " << g->name() << " with " << failures << " mismatches" << std::endl;
    return 1;
}
