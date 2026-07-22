#pragma once

#include <vector>

class bitVector {
    private:
        int size;
        std::vector<bool> bits;
        std::vector<int> acc;

        int bsrch(int rank);

    public:
        bitVector();
        explicit bitVector(int s);

        void setBit(int index);
        void finishSetUp();
        bool access(int index);
        int rank1(int index);
        int select1(int rank);
};