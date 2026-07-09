#include <iostream>
#include <string>


class BenchmarkDoc{
    public:
        std::string name;
        float ConstructionTime;
        float adjTime;
        float rneighTime;
        float outDegreeTime;
        float inDegreeTime;
        BenchmarkDoc(std::string n, float constt, float adjt, float rneight, float outt, float innt){
            name = n;
            ConstructionTime = constt;
            adjTime = adjt;
            rneighTime = rneight;
            outDegreeTime = outt;
            inDegreeTime = innt;
        }
        ~BenchmarkDoc(){}
        void print(){
            std::cout << "/// BENCHMARK RESULTS: " << name << " ///" << std::endl;
            std::cout << "Construction Time: " << ConstructionTime << std::endl;
            std::cout << "Adjacency Time: " << adjTime << std::endl;
            std::cout << "Reverse Neighbors Time: " << rneighTime << std::endl;
            std::cout << "Out Degree Time: " << outDegreeTime << std::endl;
            std::cout << "In Degree Time: " << inDegreeTime << std::endl;
        }
};


BenchmarkDoc GraphBitVector(){
    std::cout << "GraphBitVector Benchmark" << std::endl;
    BenchmarkDoc doc("GraphBitVector", 0.0, 0.0, 0.0, 0.0, 0.0);

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