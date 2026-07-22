#pragma once

#include <string>
#include <vector>

#include "bitVector.h"

class Alphabet {
    private:
        int size;
        std::vector<char> symbols;
    public:
        Alphabet();
        explicit Alphabet(int s);
        explicit Alphabet(int s, std::vector<char> sym);
};

class Sequence {
    private:
        int size;
        std::vector<bitVector> Alphabet;
    public:
        Sequence();
        explicit Sequence(int s);
        int access(int index);
        int rank(int index,int symbol);
        int select(int rank, int symbol);

};