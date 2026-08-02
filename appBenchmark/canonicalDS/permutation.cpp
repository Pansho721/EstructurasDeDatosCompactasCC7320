#include "permutation.h"

Permutation::Permutation(std::vector<int> pi, int t) : size(pi.size()), pi(pi) {
    B = bitVector(size);
    V = bitVector(size);
    for (int i = 0; i < size; ++i) {
        B.clearBit(i);
        V.clearBit(i);
    }
    for (int i = 0; i < size; ++i) {
        if (not V.access(i)) {
            V.setBit(i);
            int j = pi[i];
            int k = 1;
            while (j != i) {
                if (k % t == 0) {
                    B.setBit(j);
                }
                V.setBit(j);
                j = pi[j];
                k++;
            }
            // Every cycle needs at least one marked anchor, otherwise access()/inverse()
            // would loop forever on cycles shorter than t (no k % t == 0 hit occurs).
            B.setBit(i);
        }
    }
    B.finishSetUp();

    std::vector<int> S(B.rank1(size - 1) + 1);
    for (int i = 0; i < size; ++i) {
        if (B.access(i)) {
            V.clearBit(i);
            int j = pi[i];
            while (V.access(j)) {
                if (B.access(j)) {
                    S[B.rank1(j)] = i;
                }
                V.clearBit(j);
                j = pi[j];
            }
            if (B.access(j)) {
                S[B.rank1(j)] = i;
            }
        }
    }
    this->S = S;
}

int Permutation::access(int index) {
    if (index < 0 || index >= size) return -1;
    return this->pi[index];
}

int Permutation::inverse(int index) {
    if (index < 0 || index >= size) return -1;
    int j = index;
    bool s = true;
    while (this->pi[j] != index) {
        if (s && B.access(j)){
            j = S[B.rank1(j)];
            s = false;
        } else {
            j = this->pi[j];
        }
    }
    return j;
}