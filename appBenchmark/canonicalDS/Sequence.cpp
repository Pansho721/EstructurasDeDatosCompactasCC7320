#include "Sequence.h"
#include <cmath>
#include <iostream>

Sequence::Sequence() : n(0), sigma(0) {}

Sequence::Sequence(std::vector<int> S, int sigma, int t) : n(S.size()), sigma(sigma) {
    std::vector<int> F(sigma + 1, 0);//F[0,sigma]
    const int block = std::ceil(static_cast<double>(this->n) / sigma);
    const int n = this->n;
    std::vector<bitVector> Ac;

    for (int i = 0; i < n; ++i) {
        F[S[i] + 1] = F[S[i] + 1] + 1;
    }
    for (int c = 0; c < sigma; ++c) {
        Ac.push_back(bitVector(F[c + 1] + block - 2));
        F[c + 1] = 0;
    }
    for (int k = 0; k < block; ++k) {
        for (int i = k*sigma; i < std::min((k+1)*sigma, n); ++i) {
            F[S[i] + 1] = F[S[i] + 1] + 1;
            Ac[S[i]].setBit(F[S[i] + 1]);
        }
        for (int c = 0; c < sigma; ++c) {
            F[c + 1] = F[c + 1] + 1;
            Ac[c].clearBit(F[c + 1]);
        }
    }
    std::vector<Permutation> pi;
    std::vector<bitVector> Dk;

    for (int k = 0; k < block; ++k) {
        int minkn = std::min((k + 1) * sigma, n);
        int ksigma = k * sigma;

        for (int c = 0; c < sigma + 1; ++c) {
            F[c] = 0;
        }
        int l = minkn - ksigma;
        std::vector<int> pik(l);
        bitVector Dkk(l + sigma);
        for (int i = ksigma; i < minkn; ++i) {
            F[S[i] + 1] = F[S[i] + 1] + 1;
        }
        for (int c = 0; c < sigma; ++c) {
            F[c+1] = F[c+1] + F[c];
            Dkk.setBit(F[c] + c);
        }
        for (int i  = ksigma; i < minkn; ++i) {
            F[S[i]] = F[S[i]] + 1;
            pik[F[S[i]] - 1] = i - ksigma;
            Dkk.clearBit(F[S[i]] + S[i]);
        }
        Dkk.finishSetUp();
        Dk.push_back(Dkk);
        pi.push_back(Permutation(pik, std::ceil(std::log2(sigma))));
    }
    for (int c = 0; c < sigma; ++c) {
        Ac[c].finishSetUp();
        continue;
    }
    this->A = Ac;
    this->D = Dk;
    this->pi = pi;
}

int Sequence::access(int index) {
    if (index < 0 || index >= n) {
        return -1;
    }
    const int k = index / sigma;
    const int ip = index - k * sigma;
    const int j = this->pi[k].inverse(ip);

    return this->D[k].select0(j + 1) - j - 1;
}

int Sequence::rank(int symbol, int index) {
    if (symbol < 0 || symbol >= sigma) return -1; // Invalid symbol
    if (index == 0) return 0;
    if (index > n) return n + 1;

    int count = 0;
    for (int i = 0; i < index; ++i) {
        if (this->access(i) == symbol) {
            count++;
        }
    }
    return count;

}

int Sequence::select(int symbol, int j) { // select_c(j) <--> select(c, j)
    if (symbol < 0 || symbol >= sigma) return -1;
    if (j == 0) return 0;

    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (this->access(i) == symbol) {
            count++;
            if (count == j) {
                return i;
            }
        }
    }
    return n + 1;
}