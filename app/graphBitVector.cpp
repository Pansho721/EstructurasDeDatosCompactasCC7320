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
    public:
        bitVector(int s){
            size = s;
            bits.resize(size, false);
            acc.resize(size, 0);
        }
        void setBit(int index){
            if(index < 0 || index >= size){
                return;
            }
            bits[index] = true;
        }
        bool getBit(int index){
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

};

class GraphBitVector : public graph{
    private:
        std::string name;
        int numNodes;
        int numEdges;
        std::vector<node> nodes;
        std::vector<bitVector> adjM;

        void addEdge(std::pair<node, node> edge){
            if(adjM[edge.first.id].getBit(edge.second.id)) return;// Edge already exists
            adjM[edge.first.id].setBit(edge.second.id);
        }

    public:
        GraphBitVector(std::string file){
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
        }

        int size(){
            return 0;
        }


        bool *adj(node n, node m) override{
            return 0;
        }

};