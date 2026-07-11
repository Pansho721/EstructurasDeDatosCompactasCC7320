#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "graph.h"
#include "graphBitVector.h"

int MAX = 999999999; // Placeholder for unimplemented functions


BenchmarkDoc General(graph g){
    BenchmarkDoc doc(g.getName(), 0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}


BenchmarkDoc runGraphBitVectorBenchmark(std::string file){
    std::cout << "GraphBitVector Benchmark" << std::endl;
    BenchmarkDoc doc("GraphBitVector", 0.0, 0.0, 0.0, 0.0, 0.0);

    // Construction of the GraphBitVector
    auto initConstructionTime = std::chrono::high_resolution_clock::now();

    GraphBitVector graphBitVector(file, N, E);
    
    auto endConstructionTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> constructionDuration = endConstructionTime - initConstructionTime;
    doc.ConstructionTime = constructionDuration.count();



    // Benchmark adjacency check
    auto initAdjTime = std::chrono::high_resolution_clock::now();

    graphBitVector.adj(0, 1);

    auto endAdjTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> adjDuration = endAdjTime - initAdjTime;
    doc.adjTime = adjDuration.count();


    // Benchmark neighbor
    auto initNeighTime = std::chrono::high_resolution_clock::now();

    graphBitVector.neigh(0, 1);

    auto endNeighTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> neighDuration = endNeighTime - initNeighTime;
    doc.rneighTime = neighDuration.count();

    // Benchmark outDegree
    auto initOutDegreeTime = std::chrono::high_resolution_clock::now();

    graphBitVector.outDegree(0);

    auto endOutDegreeTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> outDegreeDuration = endOutDegreeTime - initOutDegreeTime;
    doc.outDegreeTime = outDegreeDuration.count();

    // Benchmark inDegree and reverse neighbor
    doc.inDegreeTime = MAX; // Not implemented in GraphBitVector
    doc.rneighTime = MAX; // Not implemented in GraphBitVector

    return doc;
}

BenchmarkDoc runGraphSequenceBenchmark(){
    std::cout << "GraphSequence Benchmark" << std::endl;
    BenchmarkDoc doc("GraphSequence", 0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

BenchmarkDoc runLabeledGraphBenchmark(){
    std::cout << "LabeledGraph Benchmark" << std::endl;
    BenchmarkDoc doc("LabeledGraph", 0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

BenchmarkDoc runClusteredK2TreeBenchmark(){
    std::cout << "ClusteredK2Tree Benchmark" << std::endl;
    BenchmarkDoc doc("ClusteredK2Tree", 0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

int main(int argc, char* argv[]){
    if (argc < 1){
        std::cerr << "Usage: " << argv[0] << " <graph_file>" << std::endl;
        return 1;
    }
    std::string file = argv[1];

    std::cout << "/// BENCHMARK START ///" << std::endl;

    std::cout << "-- Graph Bitvector --" << std::endl;
    BenchmarkDoc gbv = runGraphBitVectorBenchmark(file);

    std::cout << "-- Graph Sequence --" << std::endl;
    BenchmarkDoc gs = runGraphSequenceBenchmark();

    std::cout << "-- Labeled Graph --" << std::endl;
    BenchmarkDoc lg = runLabeledGraphBenchmark();

    std::cout << "-- Clustered K2Tree --" << std::endl;
    BenchmarkDoc ck2t = runClusteredK2TreeBenchmark();

    std::cout << "/// BENCHMARK END ///" << std::endl;

    std::cout << "\n\n/// BENCHMARK RESULTS ///" << std::endl;
    gbv.print();
    gs.print();
    lg.print();
    ck2t.print();

    return 0;
}