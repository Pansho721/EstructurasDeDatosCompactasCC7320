#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "graph.h"
#include "graphBitVector.h"


BenchmarkDoc General(graph g){
    BenchmarkDoc doc(g.getName(), 0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}


BenchmarkDoc runGraphBitVectorBenchmark(){
    std::cout << "GraphBitVector Benchmark" << std::endl;
    BenchmarkDoc doc("GraphBitVector", 0.0, 0.0, 0.0, 0.0, 0.0);
    auto initConstructionTime = std::chrono::high_resolution_clock::now();

    GraphBitVector graphBitVector("reddit_hyperlinks_body.txt", N, E);

    auto endConstructionTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> constructionDuration = endConstructionTime - initConstructionTime;
    doc.ConstructionTime = constructionDuration.count();

    

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

    std::cout << "/// BENCHMARK START ///" << std::endl;

    std::cout << "-- Graph Bitvector --" << std::endl;
    BenchmarkDoc gbv = runGraphBitVectorBenchmark();

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