#include <iostream>
#include <iomanip>

#include "graph.h"

// These numbers are exclusive for the reddit hyperlinks body graph
// Number of nodes in the graph
// Number of edges in the graph
int N = 35777;
int E = 367662;

BenchmarkDoc::BenchmarkDoc(std::string n, float constt, float adjt, float rneight, float outt, float innt){
    name = n;
    ConstructionTime = constt;
    adjTime = adjt;
    rneighTime = rneight;
    outDegreeTime = outt;
    inDegreeTime = innt;
}

BenchmarkDoc::~BenchmarkDoc(){}

void BenchmarkDoc::print(){
    std::cout << std::fixed << std::setprecision(9);
    std::cout << "===== BENCHMARK RESULTS: " << name << " =====" << std::endl;
    std::cout << "Construction Time: " << ConstructionTime << std::endl;
    std::cout << "Adjacency Time: " << adjTime << std::endl;
    std::cout << "Reverse Neighbors Time: " << rneighTime << std::endl;
    std::cout << "Out Degree Time: " << outDegreeTime << std::endl;
    std::cout << "In Degree Time: " << inDegreeTime << std::endl;
}

graph::graph(){}

graph::~graph(){}

bool graph::adj(int n, int m){
    return false;
}

int graph::neigh(int n, int j){
    return 0;
}

int graph::rneigh(int n, int j){
    return 0;
}

int graph::outDegree(int n){
    return 0;
}

int graph::inDegree(int n){
    return 0;
}

std::string graph::getName(){
    return name;
}