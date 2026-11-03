#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "graph.h"
#include "graphBitVector.h"
#include "graphK2Tree.h"
#include "graphSequence.h"

static const int QUERIES = 100000;
static volatile uint64_t sink; // keeps query results from being optimized away

static std::string resolveGraphFile(const std::string& file){
    if(std::ifstream(file).is_open()) return file;
    const std::string parent = "../" + file;
    if(std::ifstream(parent).is_open()) return parent;
    return "";
}

// Average nanoseconds per call of query(i), for i in [0, QUERIES).
static float timeQueries(const std::function<uint64_t(int)>& query){
    auto start = std::chrono::high_resolution_clock::now();
    uint64_t acc = 0;
    for(int i = 0; i < QUERIES; ++i) acc += query(i);
    auto end = std::chrono::high_resolution_clock::now();
    sink = acc;
    return std::chrono::duration<float, std::nano>(end - start).count() / QUERIES;
}

struct Workload {
    std::vector<uint64_t> nodes;               // random nodes
    std::vector<std::pair<uint64_t, uint64_t>> pairs;  // half real edges, half random pairs
    std::vector<Edge> edges;                   // random real edges
};

static Workload makeWorkload(const std::vector<Edge>& edges, uint64_t N){
    std::mt19937_64 rng(42);
    std::uniform_int_distribution<uint64_t> node(0, N - 1);
    std::uniform_int_distribution<size_t> edge(0, edges.size() - 1);
    Workload w;
    for(int i = 0; i < QUERIES; ++i){
        w.nodes.push_back(node(rng));
        w.pairs.push_back(i % 2 ? edges[edge(rng)] : Edge(node(rng), node(rng)));
        w.edges.push_back(edges[edge(rng)]);
    }
    return w;
}

template<class G>
static BenchmarkDoc runBenchmark(const std::vector<Edge>& edges, uint64_t N, const Workload& w){
    auto start = std::chrono::high_resolution_clock::now();
    G g(edges, N);
    auto end = std::chrono::high_resolution_clock::now();

    BenchmarkDoc doc(g.name());
    std::cout << "-- " << doc.name << " --" << std::endl;
    doc.constructionTime = std::chrono::duration<float>(end - start).count();
    doc.sizePerEdge = g.sizePerEdge();

    doc.adjTime = timeQueries([&](int i){ return g.adj(w.pairs[i].first, w.pairs[i].second); });
    doc.outDegreeTime = timeQueries([&](int i){ return g.outDegree(w.nodes[i]); });
    // neighj(u, j) with j < outDegree(u): use the position of a real edge inside its list.
    std::vector<uint64_t> js(QUERIES);
    for(int i = 0; i < QUERIES; ++i) js[i] = w.edges[i].second % g.outDegree(w.edges[i].first);
    doc.neighTime = timeQueries([&](int i){ return g.neighj(w.edges[i].first, js[i]); });

    if(g.supportsReverse()){
        doc.inDegreeTime = timeQueries([&](int i){ return g.inDegree(w.nodes[i]); });
        for(int i = 0; i < QUERIES; ++i) js[i] = w.edges[i].first % g.inDegree(w.edges[i].second);
        doc.rneighTime = timeQueries([&](int i){ return g.rneighj(w.edges[i].second, js[i]); });
    }
    return doc;
}

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <graph_file>" << std::endl;
        return 1;
    }
    std::string file = resolveGraphFile(argv[1]);
    if (file.empty()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    uint64_t N;
    std::vector<Edge> edges = loadEdges(file, N);
    const double E = edges.size();
    const double cells = static_cast<double>(N) * N;
    // Information-theoretic lower bound: log2 C(N^2, E) bits for a graph with N nodes and E edges.
    const double bound = (std::lgamma(cells + 1) - std::lgamma(E + 1) - std::lgamma(cells - E + 1)) / std::log(2.0);

    std::cout << "/// BENCHMARK START ///" << std::endl;
    std::cout << "Nodes: " << N << ", Edges: " << edges.size() << ", Queries per operation: " << QUERIES << std::endl;

    Workload w = makeWorkload(edges, N);
    BenchmarkDoc gbv = runBenchmark<GraphBitVector>(edges, N, w);
    BenchmarkDoc gs = runBenchmark<GraphSequence>(edges, N, w);
    BenchmarkDoc gk2 = runBenchmark<GraphK2Tree>(edges, N, w);

    std::cout << "/// BENCHMARK END ///" << std::endl;

    std::cout << "\n\n/// BENCHMARK RESULTS ///" << std::endl;
    std::cout << "Theoretical lower bound: " << bound / E << " bits per edge" << std::endl;
    gbv.print();
    gs.print();
    gk2.print();

    return 0;
}
