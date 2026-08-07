#pragma once
#include <vector>
#include "sparseBitVector.h"


class Permutation {
    private:
        int n;
        std::vector<int> pi;
        std::vector<int> S;
        sparseBitVector B;

    public:
        Permutation(std::vector<int> pi, int t);
        int access(int index);
        int inverse(int index);
        int size();
};