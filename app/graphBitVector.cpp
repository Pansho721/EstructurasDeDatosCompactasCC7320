#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "graph.h"

class bitVector{
    private:
        int size;
        std::vector<bool> bits;
        std::vector<int> acc;
        int bsrch(int rank){
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
    public:
        bitVector(int s){
            size = s;
            bits.resize(size, false);
            acc.resize(size, 0);
        }
        void setBit(int index){
            if(index >= size) return;
            if(index < 0) return;
            bits[index] = true;
        }
        void finishSetUp(){
            int count = 0;
            for(int i=0; i<size; i++){
                if(bits[i]){
                    count++;
                }
                acc[i] = count;
            }
        }
        bool access(int index){
            if(index < 0 || index >= size){
                return false;
            }
            return bits[index];
        }
        int rank1(int index){
            if(index < 0 || index >= size){
                return 0;
            }
            return acc[index];
        }
        int select1(int rank){
            if(rank < 0) return 0;
            if(rank > acc[size - 1]) return N + 1;
            return bsrch(rank);
        }

};

class GraphBitVector : public graph{
    private:
        std::string name;
        int numNodes;
        int numEdges;
        std::vector<int> nodes;
        std::vector<bitVector> adjM;

        void addEdge(std::pair<node, node> edge){
            if(adjM[edge.first.id].access(edge.second.id)) return;// Edge already exists
            adjM[edge.first.id].setBit(edge.second.id);
        }

    public:
        GraphBitVector(std::string file, int N, int E){
            std::ifstream inputFile(file);
            if(!inputFile.is_open()){
                std::cerr << "Error opening file: " << file << std::endl;
                return;
            }
            nodes.resize(N);
            adjM.resize(N);
            for(int i=0; i<N; i++){
                nodes[i] = node();
                nodes[i].id = i;
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
        
        int size(){
            return 0;
        }

        bool adj(int n, int m) override{
            return this->adjM[n].access(m);
        }

        int neigh(int n, int j) override{
            return adjM[n].rank1(j);
        }

        int outDegree(int n) override{
            return this->adjM[n].rank1(N - 1);
        }
};