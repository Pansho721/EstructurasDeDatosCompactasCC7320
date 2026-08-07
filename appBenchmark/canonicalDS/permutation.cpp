#include "permutation.h"

Permutation::Permutation(std::vector<int> pi, int t) : n(pi.size()), pi(pi) {
    B = sparseBitVector(this->n);
    sparseBitVector V(this->n);
    for (int i = 0; i < this->n; ++i) {
        B.clearBit(i);
        V.clearBit(i);
    }
    for (int i = 0; i < this->n; ++i) {
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
            B.setBit(i);
        }
    }
    B.finishSetUp();

    std::vector<int> S(B.rank1(this->n - 1) + 1);
    for (int i = 0; i < this->n; ++i) {
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
    if (index < 0 || index >= this->n) return -1;
    return this->pi[index];
}

int Permutation::inverse(int index) {
    if (index < 0 || index >= this->n) return -1;
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

int Permutation::size() {
    return this->B.size() + this->pi.size() * 32 + this->S.size() * 32;
}