#pragma once

#include <vector>

#include <sdsl/bit_vectors.hpp>
#include <sdsl/sd_vector.hpp>

class sparseBitVector {
    private:
        int size;
        bool finalized;
        sdsl::bit_vector pendingBits;
        sdsl::sd_vector<> bits;

    public:
        sparseBitVector();
        explicit sparseBitVector(int s);
        explicit sparseBitVector(std::vector<bool> s);
        ~sparseBitVector() = default;

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