#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include "graph.h"
#include "graphBitVector.h"
#include "graphSequence.h"

int MAX = 999999999; // Placeholder for unimplemented functions

static std::string resolveGraphFile(const std::string& file){
    std::ifstream direct(file);
    if(direct.is_open()) return file;

    const std::string parent = "../" + file;
    std::ifstream fromParent(parent);
    if(fromParent.is_open()) return parent;

    return "";
}

void adjTEST(graph& graph){
    bool result = graph.adj(0, 1);
}

void neighTEST(graph& graph){
    int result = graph.neigh(0, 1);
}

void outDegreeTEST(graph& graph){
    int result = graph.outDegree(0);
}

void inDegreeTEST(graph& graph){
    int result = graph.inDegree(0);
}

BenchmarkDoc runGraphBitVectorBenchmark(std::string file){
    std::cout << "GraphBitVector Benchmark" << std::endl;
    BenchmarkDoc doc("GraphBitVector", 0.0, 0.0, 0.0, 0.0, 0.0);


    // =========================
    // Construction of the GraphBitVector
    auto initConstructionTime = std::chrono::high_resolution_clock::now();

    GraphBitVector graphBitVector(file, N, E);
    
    auto endConstructionTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> constructionDuration = endConstructionTime - initConstructionTime;
    doc.ConstructionTime = constructionDuration.count();


    // =========================
    // Benchmark adjacency check
    auto initAdjTime = std::chrono::high_resolution_clock::now();

    adjTEST(graphBitVector);
    //graphBitVector.adj(0, 1);

    auto endAdjTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> adjDuration = endAdjTime - initAdjTime;
    doc.adjTime = adjDuration.count();


    // =========================
    // Benchmark neighbor
    auto initNeighTime = std::chrono::high_resolution_clock::now();

    neighTEST(graphBitVector);
    //graphBitVector.neigh(0, 1);

    auto endNeighTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> neighDuration = endNeighTime - initNeighTime;
    doc.rneighTime = neighDuration.count();


    // =========================
    // Benchmark outDegree
    auto initOutDegreeTime = std::chrono::high_resolution_clock::now();

    outDegreeTEST(graphBitVector);
    //graphBitVector.outDegree(0);

    auto endOutDegreeTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> outDegreeDuration = endOutDegreeTime - initOutDegreeTime;
    doc.outDegreeTime = outDegreeDuration.count();

    
    // =========================
    // Benchmark inDegree and reverse neighbor
    doc.inDegreeTime = MAX; // Not implemented in GraphBitVector
    doc.rneighTime = MAX; // Not implemented in GraphBitVector

    return doc;
}

BenchmarkDoc runGraphSequenceBenchmark(std::string file){
    std::cout << "GraphSequence Benchmark" << std::endl;
    BenchmarkDoc doc("GraphSequence", 0.0, 0.0, 0.0, 0.0, 0.0);


    // =========================
    // Construction of the GraphSequence
    auto initConstructionTime = std::chrono::high_resolution_clock::now();

    GraphSequence graphSequence(file, N, E);

    auto endConstructionTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> constructionDuration = endConstructionTime - initConstructionTime;
    doc.ConstructionTime = constructionDuration.count();

    // =========================
    // Benchmark adjacency check
    auto initAdjTime = std::chrono::high_resolution_clock::now();

    //graphSequence.adj(0, 1);
    adjTEST(graphSequence);

    auto endAdjTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> adjDuration = endAdjTime - initAdjTime;
    doc.adjTime = adjDuration.count();

    // =========================
    // Benchmark neighbor
    auto initNeighTime = std::chrono::high_resolution_clock::now();


    neighTEST(graphSequence);
    //graphSequence.neigh(0, 1);

    auto endNeighTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> neighDuration = endNeighTime - initNeighTime;
    doc.rneighTime = neighDuration.count();

    // =========================
    // Benchmark outDegree
    auto initOutDegreeTime = std::chrono::high_resolution_clock::now();

    outDegreeTEST(graphSequence);
    //graphSequence.outDegree(0);

    auto endOutDegreeTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> outDegreeDuration = endOutDegreeTime - initOutDegreeTime;
    doc.outDegreeTime = outDegreeDuration.count();


    // =========================
    // Benchmark inDegree
    auto initInDegreeTime = std::chrono::high_resolution_clock::now();

    inDegreeTEST(graphSequence);
    //graphSequence.inDegree(0);

    auto endInDegreeTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> inDegreeDuration = endInDegreeTime - initInDegreeTime;
    doc.inDegreeTime = inDegreeDuration.count();

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

    std::cout << "/// BENCHMARK START ///" << std::endl;

    std::cout << "-- Graph Bitvector --" << std::endl;
    BenchmarkDoc gbv = runGraphBitVectorBenchmark(file);

    std::cout << "-- Graph Sequence --" << std::endl;
    BenchmarkDoc gs = runGraphSequenceBenchmark(file);

    std::cout << "/// BENCHMARK END ///" << std::endl;

    std::cout << "\n\n/// BENCHMARK RESULTS ///" << std::endl;

    gbv.print();
    gs.print();

    return 0;
}