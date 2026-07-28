#pragma once
#include <vector>
#include "bitVector.h"


class Permutation {
    private:
        int size;
        std::vector<int> pi;
        std::vector<int> S;
        bitVector B;
        bitVector V;

    public:
        Permutation(std::vector<int> pi, int t);
        int access(int index);
        int inverse(int index);
};