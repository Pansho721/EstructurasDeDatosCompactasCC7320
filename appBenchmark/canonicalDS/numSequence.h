#pragma once

#include <string>
#include <vector>

#include "bitVector.h"

class Sequence {
    private:
        int Ssize;
        int sigma;
        std::vector<bitVector> S; //Sigma
    public:
        Sequence(int n, int sigma);// naive constructor: seq = [1 .. sigma], length n
        int access(int index);
        int rank(int symbol, int index);
        int select(int symbol, int rank);
};