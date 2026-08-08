#include <filesystem>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>
#include <cmath>
namespace fs = std::filesystem;

#include "canonicalDS/permutation.h"

void permutation_t(int N){
    std::vector<int> S;
    S.resize(N);
    std::iota(S.begin(), S.end(), 0);

    // 2. Initialize a high-quality random number engine
    std::random_device rd; 
    std::mt19937 g(rd()); // Mersenne Twister engine

    // 3. Permute the elements randomly
    std::shuffle(S.begin(), S.end(), g);

    fs::create_directories("appBenchmark/results");
    std::ofstream csvFile("appBenchmark/results/permutation_results.csv");
    if (!csvFile.is_open()) {
        std::cerr << "Error: could not open CSV file for writing." << std::endl;
        return;
    }

    int opt = std::ceil(std::log2(N));
    std::cout << "N: " << N << ", opt: " << opt << std::endl;

    std::string header = "t, size, size per element, Construction Time, Access Time, Inverse Time";
    csvFile << header << "\n";
    std::cout << " [*t*], [*size*], [*size per element*], [*Construction Time*], [*Access Time*], [*Inverse Time*], [*Inverse Steps*]," << std::endl;

    //for (int t = 1; t <= 1000; t+=1) {// Second round
    for (int t = 1; t<=opt*2; t+=1) {// First round
        auto start = std::chrono::high_resolution_clock::now();
        Permutation perm(S, t);
        auto end = std::chrono::high_resolution_clock::now();
        float constructionTime = std::chrono::duration<float>(end - start).count();

        // Test access
        auto accessStart = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            perm.access(i);
        }
        auto accessEnd = std::chrono::high_resolution_clock::now();
        float accessTime = std::chrono::duration<float>(accessEnd - accessStart).count();

        // Test inverse
        auto inverseStart = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            perm.inverse(i);
        }
        auto inverseEnd = std::chrono::high_resolution_clock::now();
        float inverseTime = std::chrono::duration<float>(inverseEnd - inverseStart).count();

        int sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += perm.inverse_steps(i);
        }
        sum = sum / N;


        int sizeInBytes = perm.size_in_bytes();
        int sizePerElement = sizeInBytes / N;

        std::cout << '[' << t << "], " << '[' << sizeInBytes << "], " << '[' << sizePerElement << "], " << '[' << constructionTime << "], "<< '[' << accessTime << "], "<< '[' << inverseTime << "], " << '[' << sum << "], " << std::endl;
        csvFile << t << ", "
                 << sizeInBytes << ", "
                 << sizePerElement << ", "
                 << constructionTime << ", "
                 << accessTime << ", "
                 << inverseTime << ", "
                 << "\n";
        //if (t > 9) t += 9; // For second round, skip some t values to reduce the number of iterations
    }
    csvFile.close();
    std::cout << "Results saved to permutation_results.csv" << std::endl;

}


int main(){
    
    int N = 35776; // Number of nodes (or size of the permutation)

    permutation_t(N);
    return 0;
}