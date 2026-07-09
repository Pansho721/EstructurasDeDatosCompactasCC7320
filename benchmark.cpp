#include <iostream>

class BenchmarkDoc{
    public:
        float ConstructionTime;
        float adjTime;
        float rneighTime;
        float outDegreeTime;
        float inDegreeTime;
        BenchmarkDoc(float constt, float adjt, float rneight, float outt, float innt){
            ConstructionTime = constt;
            adjTime = adjt;
            rneighTime = rneight;
            outDegreeTime = outt;
            inDegreeTime = innt;
        }
        ~BenchmarkDoc(){}
};


BenchmarkDoc GraphBitVector(){
    std::cout << "GraphBitVector Benchmark" << std::endl;
    BenchmarkDoc doc(0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

BenchmarkDoc GraphSequence(){
    std::cout << "GraphSequence Benchmark" << std::endl;
    BenchmarkDoc doc(0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

BenchmarkDoc LabeledGraph(){
    std::cout << "LabeledGraph Benchmark" << std::endl;
    BenchmarkDoc doc(0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

BenchmarkDoc ClusteredK2Tree(){
    std::cout << "ClusteredK2Tree Benchmark" << std::endl;
    BenchmarkDoc doc(0.0, 0.0, 0.0, 0.0, 0.0);

    return doc;
}

int main(int argc, char* argv[]){
    

    return 0;
}