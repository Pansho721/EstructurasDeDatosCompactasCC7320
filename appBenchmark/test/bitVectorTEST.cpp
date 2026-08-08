#include "../canonicalDS/sparseBitVector.h"
#include <iostream>

int main() {
    // Test the bitVector class
    std::vector<bool> bits = {false, false, true, false, false, true, false, true, false, false}; // Example bit pattern
    sparseBitVector bv(bits);
    int size = bv.length(); // Get the length of the bit vector

    // Test rank1
    for (int i = 0; i < size; ++i) {
        std::cout << "rank1(" << i << ") = " << bv.rank1(i) << std::endl;
    }

    // Test select1
    for (int j = 1; j <= 3; ++j) {
        std::cout << "select1(" << j << ") = " << bv.select1(j) << std::endl;
    }
    std::cout << "select1(1000) = " << bv.select1(1000) << std::endl; // Test select1 with a rank greater than the number of 1s

    // Test rank0
    for (int i = 0; i < size; ++i) {
        std::cout << "rank0(" << i << ") = " << bv.rank0(i) << std::endl;
    }

    // Test select0
    for (int j = 1; j <= 7; ++j) {
        std::cout << "select0(" << j << ") = " << bv.select0(j) << std::endl;
    }

    // Test access
    for (int i = 0; i < size; ++i) {
        std::cout << "access(" << i << ") = " << bv.access(i) << std::endl;
    }

    // Test pred1 and pred0
    for (int i = 0; i < size; ++i) {
        std::cout << "pred1(" << i << ") = " << bv.pred1(i) << std::endl;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << "pred0(" << i << ") = " << bv.pred0(i) << std::endl;
    }

    return 0;
}