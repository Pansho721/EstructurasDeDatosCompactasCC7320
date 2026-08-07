#pragma once

#include <string>
#include <vector>

#include "permutation.h"
#include "sparseBitVector.h"

class Sequence {
    private:
        int n;
        int sigma;
        std::vector<sparseBitVector> A; //Sigma
        std::vector<sparseBitVector> D; //k
        std::vector<Permutation> pi; //k
    public:
        Sequence();
        Sequence(std::vector<int> S, int sigma);
        int access(int index);
        int rank(int symbol, int index);
        int select(int symbol, int rank);
        int size_in_bytes();
};