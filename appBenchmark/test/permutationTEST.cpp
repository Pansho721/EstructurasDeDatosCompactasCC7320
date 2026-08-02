#include "../canonicalDS/permutation.h"
#include <iostream>

int main() {
    // Test the Permutation class
    std::vector<int> pi = {2, 0, 1, 4, 3}; // Example permutation
    int t = 2; // Example parameter for the Permutation constructor

    Permutation perm(pi, t);

    // Test access
    for (int i = 0; i < pi.size(); ++i) {
        std::cout << "perm.access(" << i << ") = " << perm.access(i) << std::endl;
    }

    // Test inverse
    for (int i = 0; i < pi.size(); ++i) {
        std::cout << "perm.inverse(" << i << ") = " << perm.inverse(i) << std::endl;
    }

    return 0;
}