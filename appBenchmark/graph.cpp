#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "graph.h"

std::vector<Edge> loadEdges(const std::string& file, uint64_t& numNodes){
    std::ifstream inputFile(file);
    if(!inputFile.is_open()){
        throw std::runtime_error("Error opening file: " + file);
    }
    std::vector<Edge> edges;
    numNodes = 0;
    std::string line;
    while(std::getline(inputFile, line)){
        std::istringstream iss(line);
        uint64_t u, v;
        if(!(iss >> u >> v)) continue;
        edges.emplace_back(u, v);
        numNodes = std::max(numNodes, std::max(u, v) + 1);
    }
    std::sort(edges.begin(), edges.end());
    edges.erase(std::unique(edges.begin(), edges.end()), edges.end());
    return edges;
}

BenchmarkDoc::BenchmarkDoc(std::string n)
    : name(std::move(n)), constructionTime(0), sizePerEdge(0),
      adjTime(-1), neighTime(-1), rneighTime(-1), outDegreeTime(-1), inDegreeTime(-1) {}

static void printTime(const std::string& label, float t){
    std::cout << label;
    if(t < 0) std::cout << "not supported" << std::endl;
    else std::cout << t << " ns/query" << std::endl;
}

void BenchmarkDoc::print(){
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\n===== BENCHMARK RESULTS: " << name << " =====" << std::endl;
    std::cout << "Size per Edge: " << sizePerEdge << " bits" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Construction Time: " << constructionTime << " s" << std::endl;
    printTime("Adjacency Time: ", adjTime);
    printTime("Neighbor (neighj) Time: ", neighTime);
    printTime("Reverse Neighbor (rneighj) Time: ", rneighTime);
    printTime("Out Degree Time: ", outDegreeTime);
    printTime("In Degree Time: ", inDegreeTime);
}
