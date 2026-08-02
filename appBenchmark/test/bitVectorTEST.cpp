#include "../canonicalDS/bitVector.h"
#include <iostream>

int main() {
    // Test the bitVector class
    int size = 10;
    bitVector bv(size);
    int bits[] = {0, 0, 1, 0, 0, 1, 0, 1, 0, 0}; // Example bit pattern

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
    std::cout << bv.select1(1000) << std::endl; // Test select1 with a rank greater than the number of 1s

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