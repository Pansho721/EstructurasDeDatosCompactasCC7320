#include "../canonicalDS/Sequence.h"
#include <iostream>

int main() {
    // Test the Sequence class
    std::vector<int> data = {0, 1, 2, 3, 4, 4, 4}; // Example sequence over alphabet [0, sigma-1]
    int sigma = 5;
    std::cout << "Starting Sequence test..." << std::endl;
    Sequence seq(data, sigma);
    std::cout << "constructor test completed." << std::endl;

    // Test access
    for (int i = 0; i < data.size(); ++i) {
        std::cout << "seq.access(" << i << ") = " << seq.access(i) << std::endl;
    }

    // Test rank
    for (int symbol = 0; symbol < sigma; ++symbol) {
        for (int index = 0; index < data.size(); ++index) {
            std::cout << "seq.rank(" << symbol << ", " << index << ") = " << seq.rank(symbol, index) << std::endl;
        }
    }

    seq.seeA();
    
    // Test select
    for (int symbol = 0; symbol < sigma; ++symbol) {
        for (int rank = 1; rank < data.size(); ++rank) {
            std::cout << "seq.select(" << symbol << ", " << rank << ") = " << seq.select(symbol, rank) << std::endl;
        }
    }

    

    return 0;
}