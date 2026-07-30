#pragma once

#include <vector>

class bitVector {
    private:
        int size;
        std::vector<bool> bits;
        std::vector<int> acc;

        int bsrch(int rank);
        int bsrch0(int rank);

    public:
        bitVector();
        explicit bitVector(int s);
        ~bitVector() = default;

        void setBit(int index);
        void clearBit(int index);
        void finishSetUp();
        bool access(int index);
        int rank0(int index);
        int rank1(int index);
        int select1(int rank);
        int select0(int rank);
        int length();
        int pred0(int index);
        int pred1(int index);
        int succ0(int index);
        int succ1(int index);
};