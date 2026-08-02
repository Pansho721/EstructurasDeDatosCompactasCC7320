#include "../canonicalDS/Sequence.h"
#include <iostream>

int main() {
    // Test the Sequence class
    std::vector<int> data = {0, 1, 2, 3, 4}; // Example sequence over alphabet [0, sigma-1]
    int sigma = 5;
    int t = 2;
    std::cout << "Starting Sequence test..." << std::endl;
    Sequence seq(data, sigma, t);
    std::cout << "constructor test completed." << std::endl;

    // Test access
    for (int i = 0; i < data.size(); ++i) {
        std::cout << "seq.access(" << i << ") = " << seq.access(i) << std::endl;
    }

    return 0;
}