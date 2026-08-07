#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

#include "canonicalDS/permutation.h"

void permutation_t(int E){
    std::vector<int> S;
    for (int i = 0; i < E; ++i) {
        S.push_back(i % 23451);//random number, just to test
    }


    for (int t = 1; t <= 2; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        Permutation perm(S, t);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> duration = end - start;
        std::cout << "Permutation construction time for t=" << t << ": " << duration.count() << " seconds" << std::endl;
    }
}


int main(){
    
    int E = 100000; // Number of edges (or size of the permutation)

    permutation_t(E);
    return 0;
}