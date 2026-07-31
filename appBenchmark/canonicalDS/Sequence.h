#pragma once

#include <string>
#include <vector>

#include "bitVector.h"
#include "permutation.h"

class Sequence {
    private:
        int n;
        int sigma;
        std::vector<bitVector> Ac; //Sigma
        std::vector<bitVector> Dk;
        std::vector<Permutation> pi; // permutation
    public:
        Sequence();
        Sequence(std::vector<int> S, int sigma, int t = 4);
        int access(int index);
        int rank(int symbol, int index);
        int select(int symbol, int rank);
};