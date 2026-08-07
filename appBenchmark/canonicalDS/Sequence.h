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
        std::vector<sparseBitVector> D;
        std::vector<Permutation> pi; // permutation
    public:
        Sequence();
        Sequence(std::vector<int> S, int sigma);
        int access(int index);
        int rank(int symbol, int index);
        int select(int symbol, int rank);
        int size();
};