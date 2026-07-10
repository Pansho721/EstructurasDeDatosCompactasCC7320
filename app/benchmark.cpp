#include <iostream>
#include <string>
#include <ctime>
#include <graph.h>
#include <graphBitVector.h>




BenchmarkDoc General(graph g){
    BenchmarkDoc doc(g.getName(), 0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}


BenchmarkDoc GraphBitVector(){
    std::cout << "GraphBitVector Benchmark" << std::endl;
    BenchmarkDoc doc("GraphBitVector", 0.0, 0.0, 0.0, 0.0, 0.0);
    auto initConstructionTime = std::chrono::high_resolution_clock::now();

    //Construction of the GraphBitVector object

    auto endConstructionTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> constructionDuration = endConstructionTime - initConstructionTime;
    doc.ConstructionTime = constructionDuration.count();

    

    return doc;
}

BenchmarkDoc GraphSequence(){
    std::cout << "GraphSequence Benchmark" << std::endl;
    BenchmarkDoc doc("GraphSequence", 0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

BenchmarkDoc LabeledGraph(){
    std::cout << "LabeledGraph Benchmark" << std::endl;
    BenchmarkDoc doc("LabeledGraph", 0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

BenchmarkDoc ClusteredK2Tree(){
    std::cout << "ClusteredK2Tree Benchmark" << std::endl;
    BenchmarkDoc doc("ClusteredK2Tree", 0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

int main(int argc, char* argv[]){

    std::cout << "/// BENCHMARK START ///" << std::endl;

    std::cout << "-- Graph Bitvector --" << std::endl;
    BenchmarkDoc gbv = GraphBitVector();

    std::cout << "-- Graph Sequence --" << std::endl;
    BenchmarkDoc gs = GraphSequence();

    std::cout << "-- Labeled Graph --" << std::endl;
    BenchmarkDoc lg = LabeledGraph();

    std::cout << "-- Clustered K2Tree --" << std::endl;
    BenchmarkDoc ck2t = ClusteredK2Tree();

    std::cout << "/// BENCHMARK END ///" << std::endl;

    std::cout << "\n\n/// BENCHMARK RESULTS ///" << std::endl;
    gbv.print();
    gs.print();
    lg.print();
    ck2t.print();

    return 0;
}