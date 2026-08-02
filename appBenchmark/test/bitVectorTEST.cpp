#include "../canonicalDS/bitVector.h"
#include <iostream>


int main() {
    // Test the bitVector class
    int size = 10;
    bitVector bv(size);
    std::vector<int> bits[size];

    bits = [0, 0, 1, 0, 0, 1, 0, 1, 0, 0]; // Example bit pattern

    // Set some bits
    for (int i = 0; i < size; ++i) {
        if (bits[i] == 1) {
            bv.setBit(i);
        } else {
            bv.clearBit(i);
        }
    }

    bv.finishSetUp();

    // Test rank1
    for (int i = 0; i < size; ++i) {
        std::cout << "rank1(" << i << ") = " << bv.rank1(i) << std::endl;
    }

    // Test select1
    for (int j = 1; j <= 3; ++j) {
        std::cout << "select1(" << j << ") = " << bv.select1(j) << std::endl;
    }

    // Test rank0
    for (int i = 0; i < size; ++i) {
        std::cout << "rank0(" << i << ") = " << bv.rank0(i) << std::endl;
    }

    // Test select0
    for (int j = 1; j <= 7; ++j) {
        std::cout << "select0(" << j << ") = " << bv.select0(j) << std::endl;
    }

    return 0;
}