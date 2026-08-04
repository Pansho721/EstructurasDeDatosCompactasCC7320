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
    S.reserve(E);
    std::string sEdge;
    std::vector<int> degree(N, 0);
    int u, v;
    while(inputFile >> u >> v){
        if(u < 0 || u >= N || v < 0 || v >= N) continue;
        S.push_back(v);
        degree[u]++;
    }
    const int actualEdges = static_cast<int>(S.size());
    this->N = Sequence(S, N);
    this->B = bitVector(actualEdges + N);

    int index = 0;
    for(int node=0; node < N; node+=1){
        this->B.setBit(index);
        int d = degree[node];
        for(int j=1; j<=d; j++){
            this->B.clearBit(index + j);
        }
        index += d + 1;
    }
    this->B.finishSetUp();
    this->numNodes = N;
    this->numEdges = actualEdges;
}

bool GraphSequence::adj(int v, int u){
    if (v < 0 || v >= this->numNodes || u < 0 || u >= this->numNodes) {
        return false;
    }

    const int start = this->B.select1(v + 1) - v;
    const int end = this->B.select1(v + 2) - (v + 1);
    return (this->N.rank(u, end) - this->N.rank(u, start)) == 1;
}

int GraphSequence::inDegree(int v){
    if (v < 0 || v >= this->numNodes) return -1;
    return this->N.rank(v, this->numEdges);
}

int GraphSequence::outDegree(int v){
    if (v < 0 || v >= this->numNodes) return -1;

    const int start = this->B.select1(v + 1);
    const int next = this->B.select1(v + 2);
    return next - start - 1;
}

int GraphSequence::neigh(int v, int j){
    if (v < 0 || v >= this->numNodes || j < 0) return -1;
    const int deg = this->outDegree(v);
    if (j >= deg) return -1;

    const int start = this->B.select1(v + 1);
    const int p = start - v + j;
    return this->N.access(p);
}

int GraphSequence::rneigh(int v, int j){
    if (v < 0 || v >= this->numNodes || j < 0) return -1;
    const int indeg = this->inDegree(v);
    if (j >= indeg) return -1;

    // Sequence::select uses 1-based rank argument; this API exposes j as 0-based.
    const int p = this->N.select(v, j + 1);
    if (p < 0 || p >= this->numEdges) return -1;

    return this->B.select0(p + 1) - p - 1;
}

int GraphSequence::size(){
    // 2 ints; Sequence, numEdges ints; BitVector: numNodes + numEdges bits.
    return 2 * 32 + this->numEdges * 32 + this->numNodes + this->numEdges;
}