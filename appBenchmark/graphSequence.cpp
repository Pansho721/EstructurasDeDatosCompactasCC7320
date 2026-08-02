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
    std::string sEdge;
    std::vector<int> degree(N, 0);
    while(std::getline(inputFile, sEdge)){
        int u, v;
        std::istringstream iss(sEdge);
        iss >> u >> v;
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
    int b = this->B.select1(v);
    int r1 = this->N.rank(u,b-v);
    int r2 = this->N.rank(u,this->B.succ1(b+1)-v-1);
    return r2 - r1 == 1;
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
