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

    if (!graph.adj(0, 1)) std::cout << "Mismatch adjacency 1" << std::endl;
    if (graph.adj(50, 50)) std::cout << "Mismatch adjacency 2" << std::endl;
    if (!graph.adj(90, 91)) std::cout << "Mismatch adjacency 3" << std::endl;
    if (graph.adj(119, 40)) std::cout << "Mismatch adjacency 4" << std::endl;
    if (graph.adj(148, 13)) std::cout << "Mismatch adjacency 5" << std::endl;
    if (!graph.adj(215, 225)) std::cout << "Mismatch adjacency 6" << std::endl;
    if (!graph.adj(363, 408)) std::cout << "Mismatch adjacency 7" << std::endl;
    if (graph.adj(4877, 5090)) std::cout << "Mismatch adjacency 8" << std::endl;
    if (!graph.adj(7056, 1610)) std::cout << "Mismatch adjacency 9" << std::endl;
    if (graph.adj(13200, 7777)) std::cout << "Mismatch adjacency 10" << std::endl;
}

void rneighTEST(graph& graph){
    // Reverse-neighbor checks are only meaningful for GraphSequence right now.
    if (dynamic_cast<GraphSequence*>(&graph) == nullptr) {
        return;
    }

    if (graph.rneigh(1, 0) != 0) std::cout << "Mismatch rneigh 1: " << graph.rneigh(1, 0) << std::endl;
    if (graph.rneigh(1, 1) != 148) std::cout << "Mismatch rneigh 2: " << graph.rneigh(1, 1) << std::endl;
    if (graph.rneigh(1, 2) != 177) std::cout << "Mismatch rneigh 3: " << graph.rneigh(1, 2) << std::endl;
    if (graph.rneigh(3, 10) != 821) std::cout << "Mismatch rneigh 4: " << graph.rneigh(3, 10) << std::endl;
    if (graph.rneigh(5, 0) != 4) std::cout << "Mismatch rneigh 5: " << graph.rneigh(5, 0) << std::endl;
    if (graph.rneigh(350, 20) != 173) std::cout << "Mismatch rneigh 6: " << graph.rneigh(350, 20) << std::endl;
    if (graph.rneigh(3, 0) != 2) std::cout << "Mismatch rneigh 7: " << graph.rneigh(3, 0) << std::endl;
    if (graph.rneigh(4, 0) != 13066) std::cout << "Mismatch rneigh 8: " << graph.rneigh(4, 0) << std::endl;
    if (graph.rneigh(2907, 9) != 1598) std::cout << "Mismatch rneigh 9: " << graph.rneigh(2907, 9) << std::endl;
    if (graph.rneigh(9095, 2) != 5291) std::cout << "Mismatch rneigh 10: " << graph.rneigh(9095, 2) << std::endl;
}

void outDegreeTEST(graph& graph){
    if (graph.outDegree(0) != 1) std::cout << "Mismatch outDegree 1: " << graph.outDegree(0) << std::endl;
    if (graph.outDegree(1) != 1) std::cout << "Mismatch outDegree 2: " << graph.outDegree(1) << std::endl;
    if (graph.outDegree(2) != 1) std::cout << "Mismatch outDegree 3: " << graph.outDegree(2) << std::endl;
    if (graph.outDegree(3) != 65) std::cout << "Mismatch outDegree 4: " << graph.outDegree(3) << std::endl;
    if (graph.outDegree(5) != 0) std::cout << "Mismatch outDegree 5: " << graph.outDegree(5) << std::endl;
    if (graph.outDegree(350) != 40) std::cout << "Mismatch outDegree 6: " << graph.outDegree(350) << std::endl;
    if (graph.outDegree(900) != 11) std::cout << "Mismatch outDegree 7: " << graph.outDegree(900) << std::endl;
    if (graph.outDegree(4877) != 1) std::cout << "Mismatch outDegree 8: " << graph.outDegree(4877) << std::endl;
    if (graph.outDegree(7056) != 26) std::cout << "Mismatch outDegree 9: " << graph.outDegree(7056) << std::endl;
    if (graph.outDegree(13200) != 1) std::cout << "Mismatch outDegree 10: " << graph.outDegree(13200) << std::endl;
}

void inDegreeTEST(graph& graph){
    if (graph.inDegree(0) != 1) std::cout << "Mismatch inDegree 1: " << graph.inDegree(0) << std::endl;
    if (graph.inDegree(1) != 3) std::cout << "Mismatch inDegree 2: " << graph.inDegree(1) << std::endl;
    if (graph.inDegree(2) != 4) std::cout << "Mismatch inDegree 3: " << graph.inDegree(2) << std::endl;
    if (graph.inDegree(3) != 65) std::cout << "Mismatch inDegree 4: " << graph.inDegree(3) << std::endl;
    if (graph.inDegree(5) != 1) std::cout << "Mismatch inDegree 5: " << graph.inDegree(5) << std::endl;
    if (graph.inDegree(5359) != 11) std::cout << "Mismatch inDegree 6: " << graph.inDegree(5359) << std::endl;
    if (graph.inDegree(6576) != 7) std::cout << "Mismatch inDegree 7: " << graph.inDegree(6576) << std::endl;
    if (graph.inDegree(11683) != 10) std::cout << "Mismatch inDegree 8: " << graph.inDegree(11683) << std::endl;
    if (graph.inDegree(15566) != 4) std::cout << "Mismatch inDegree 9: " << graph.inDegree(15566) << std::endl;
    if (graph.inDegree(33666) != 1) std::cout << "Mismatch inDegree 10: " << graph.inDegree(33666) << std::endl;
}

BenchmarkDoc runGraphBitVectorBenchmark(std::string file){
    std::cout << "GraphBitVector Benchmark" << std::endl;
    std::string name;
    name = "GraphBitVector";

    BenchmarkDoc doc(name, 0.0, 0.0, 0.0, 0.0, 0.0, 0);


    // =========================
    // Construction of the GraphBitVector
    auto initConstructionTime = std::chrono::high_resolution_clock::now();

    GraphBitVector graphBitVector(file, N, E);
    
    auto endConstructionTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> constructionDuration = endConstructionTime - initConstructionTime;
    doc.ConstructionTime = constructionDuration.count();

    doc.sizePerEdge = graphBitVector.sizePerEdge();

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

    rneighTEST(graphBitVector);
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
    BenchmarkDoc doc("GraphSequence", 0.0, 0.0, 0.0, 0.0, 0.0, 0);


    // =========================
    // Construction of the GraphSequence
    auto initConstructionTime = std::chrono::high_resolution_clock::now();

    GraphSequence graphSequence(file, N, E);

    auto endConstructionTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> constructionDuration = endConstructionTime - initConstructionTime;
    doc.ConstructionTime = constructionDuration.count();

    doc.sizePerEdge = graphSequence.sizePerEdge();

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


    rneighTEST(graphSequence);
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

    std::cout << "-- Graph BitVector --" << std::endl;
    BenchmarkDoc gbv = runGraphBitVectorBenchmark(file);

    std::cout << "-- Graph Sequence --" << std::endl;
    BenchmarkDoc gs = runGraphSequenceBenchmark(file);

    

    std::cout << "/// BENCHMARK END ///" << std::endl;

    std::cout << "\n\n/// BENCHMARK RESULTS ///" << std::endl;

    gbv.print();
    gs.print();

    return 0;
}