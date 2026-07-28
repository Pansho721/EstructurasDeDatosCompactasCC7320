#include "graphSequence.h"

#include <fstream>
#include <iostream>
#include <sstream>

GraphSequence::GraphSequence(std::string file, int N, int E){
    std::ifstream inputFile(file);
    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << file << std::endl;
        return;
    }
    std::vector<int> S;
    int maxNode = -1;
    std::string sEdge;
    std::vector<int> degree(N, 0);
    while(std::getline(inputFile, sEdge)){
        int u, v;
        std::istringstream iss(sEdge);
        iss >> u >> v;
        S.push_back(u);
        S.push_back(v);
        degree[u]++;
        if(u > maxNode) maxNode = u;
        if(v > maxNode) maxNode = v;
    }
    this->N = Sequence(S, maxNode + 1);
    this->B = bitVector(N + E - 1);
    for(int i=0; i<N; i+=1){
        this->B.setBit(S[i]);
        for(int j=0; j<degree[S[i]]; j++){
            this->B.clearBit(S[i] + j);
        }
    }
    this->numNodes = N;
    this->numEdges = E;
}

bool GraphSequence::adj(int v, int u){
    int a = this->N.rank(u, (this->B.select1(v + 1) - (v + 1)));
    int b = this->N.rank(u, (this->B.select1(v) -v));
    return  a - b;
}

int GraphSequence::outDegree(int v){
    return this->B.select1(v+1) - this->B.select1(v) - 1;
}

int GraphSequence::neigh(int v, int j){
    return this->N.access(this->B.select1(v) - v + j);
}

int GraphSequence::size(){
    return this->numNodes + this->numEdges;
}
