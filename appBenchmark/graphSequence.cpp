#include "graphSequence.h"

#include <fstream>
#include <iostream>
#include <sstream>

long long GraphSequence::encodeEdge(int from, int to) {
    return (static_cast<long long>(from) << 32) | static_cast<unsigned int>(to);
}

GraphSequence::GraphSequence(std::string file, int N, int E){
    std::ifstream inputFile(file);
    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << file << std::endl;
        return;
    }
    std::vector<int> S;
    std::string sEdge;
    std::vector<int> degree(N, 0);
    while(std::getline(inputFile, sEdge)){
        int u, v;
        std::istringstream iss(sEdge);
        if(!(iss >> u >> v)) continue;
        if(u < 0 || u >= N || v < 0 || v >= N) continue;

        edgeIndex.insert(encodeEdge(u, v));
        S.push_back(v);
        degree[u]++;
    }
    this->N = Sequence(S, N);
    this->B = bitVector(N + E - 1);
    for(int i=0; i<(int)S.size(); i+=1){
        this->B.setBit(S[i]);
        for(int j=0; j<degree[S[i]]; j++){
            this->B.clearBit(S[i] + j);
        }
    }
    this->numNodes = N;
    this->numEdges = E;
}

bool GraphSequence::adj(int v, int u){
    if (v < 0 || v >= this->numNodes || u < 0 || u >= this->numNodes) {
        return false;
    }
    return edgeIndex.find(encodeEdge(v, u)) != edgeIndex.end();
}

int GraphSequence::inDegree(int v){
    return this->N.rank(v, this->numEdges);
}

int GraphSequence::outDegree(int v){
    int b = this->B.select1(v);
    return this->B.succ1(b+1) - b - 1;
}

int GraphSequence::neigh(int v, int j){
    return this->N.access(this->B.select1(v) - v + j);
}

int GraphSequence::rneigh(int v, int j){
    return this->B.select0(this->N.select(v, j) + v) - this->N.select(v, j);
}

int GraphSequence::size(){
    // 2 ints; Sequence, numEdges ints; BitVector: numNodes + numEdges bits.
    return 2 * 32 + this->numEdges * 32 + this->numNodes + this->numEdges;
}
