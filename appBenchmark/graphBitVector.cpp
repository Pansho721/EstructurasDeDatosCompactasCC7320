#include "graphBitVector.h"
#include <cmath>
#include <omp.h>
#include <sstream>

void GraphBitVector::addEdge(std::pair<int, int> edge){
    if(adjM[edge.first].access(edge.second)) return;
    adjM[edge.first].setBit(edge.second);
}

GraphBitVector::GraphBitVector(std::string file, int N, int E){
    std::ifstream inputFile(file);
    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << file << std::endl;
        return;
    }
    nodes.resize(N);
    adjM.resize(N);
    for(int i=0; i<N; i++){
        nodes[i] = i;
        adjM[i] = sparseBitVector(N);
    }
    std::string sEdge;
    while(std::getline(inputFile, sEdge)){
        if(sEdge.empty()) continue;

        int u, v;
        std::istringstream iss(sEdge);
        if(!(iss >> u >> v)) continue;
        if(u < 0 || u >= N || v < 0 || v >= N) continue;

        addEdge(std::make_pair(nodes[u], nodes[v]));
    }
    this->numNodes = N;
    this->numEdges = E;
    inputFile.close();
    #pragma omp parallel for
    for(int i=0; i<N; i++){
        adjM[i].finishSetUp();
    }
}

int GraphBitVector::size(){
    int const numNodes = this->numNodes;
    return 64 + numNodes + numNodes * std::log(numNodes);
}

bool GraphBitVector::adj(int n, int m){
    return this->adjM[n].access(m);
}

int GraphBitVector::neigh(int n, int j){
    return adjM[n].rank1(j);
}

int GraphBitVector::outDegree(int n){
    return this->adjM[n].rank1(this->numNodes - 1);
}