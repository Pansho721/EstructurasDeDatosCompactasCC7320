#include <fstream>
#include <iostream>

#include "graphBitVector.h"

int bitVector::bsrch(int rank){
    int left = 0;
    int right = size - 1;
    int mid;
    while(left <= right){
        mid = (left + right) / 2;
        if(acc[mid] == rank){
            while(mid > 0 && acc[mid - 1] == rank){
                mid--;
            }
            return mid;
        } else if(acc[mid] < rank){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

bitVector::bitVector() : size(0) {}

bitVector::bitVector(int s){
    size = s;
    bits.resize(size, false);
    acc.resize(size, 0);
}

void bitVector::setBit(int index){
    if(index >= size) return;
    if(index < 0) return;
    bits[index] = true;
}

void bitVector::finishSetUp(){
    int count = 0;
    for(int i=0; i<size; i++){
        if(bits[i]){
            count++;
        }
        acc[i] = count;
    }
}

bool bitVector::access(int index){
    if(index < 0 || index >= size){
        return false;
    }
    return bits[index];
}

int bitVector::rank1(int index){
    if(index < 0 || index >= size){
        return 0;
    }
    return acc[index];
}

int bitVector::select1(int rank){
    if(rank < 0) return 0;
    if(rank > acc[size - 1]) return N + 1;
    return bsrch(rank);
}

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
        adjM[i] = bitVector(N);
    }
    std::string sEdge;
    while(std::getline(inputFile, sEdge)){
        int u, v;
        inputFile >> u >> v;
        addEdge(std::make_pair(nodes[u], nodes[v]));
    }
    this->numNodes = N;
    this->numEdges = E;
    inputFile.close();
    for(int i=0; i<N; i++){
        adjM[i].finishSetUp();
    }
}

int GraphBitVector::size(){
    return this->numNodes + this->numNodes;
}

bool GraphBitVector::adj(int n, int m){
    return this->adjM[n].access(m);
}

int GraphBitVector::neigh(int n, int j){
    return adjM[n].rank1(j);
}

int GraphBitVector::outDegree(int n){
    return this->adjM[n].rank1(N - 1);
}