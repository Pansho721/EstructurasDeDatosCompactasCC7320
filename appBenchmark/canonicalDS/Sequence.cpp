#include "Sequence.h"

#include <algorithm>

Sequence::Sequence(std::vector<int> S, int sigma, int t) : n(S.size()), sigma(sigma) {
    const int numBlocks = (sigma > 0) ? ((n + sigma - 1) / sigma) : 0;

    // F mirrors the algorithm's F[0, sigma] exactly (sigma+1 slots). Our symbols S[i] are
    // 0-based, so wherever the algorithm reads/writes F[S[i]] we use F[S[i] + 1]; F[0] stays
    // the sentinel used as the base offset for the first symbol group.
    std::vector<int> F(sigma + 1, 0);
    for (int i = 0; i < n; ++i) {
        F[S[i] + 1] = F[S[i] + 1] + 1;
    }

    for (int c = 1; c <= sigma; ++c) {
        // Algorithm (1-based): Ac[1, F[c] + numBlocks - 1] -> 0-based size F[c] + numBlocks - 1
        bitVector temAc(F[c] + numBlocks - 1);
        this->Ac.push_back(temAc);
        F[c] = 0;
    }

    for (int k = 0; k < numBlocks; ++k) {
        const int blockStart = k * sigma;
        const int blockEnd = std::min((k + 1) * sigma, n);

        for (int i = blockStart; i < blockEnd; ++i) {
            const int s = S[i];
            F[s + 1] = F[s + 1] + 1;
            this->Ac[s].setBit(F[s + 1] - 1); // 0-based bit position
        }
        for (int c = 1; c <= sigma; ++c) {
            F[c] = F[c] + 1;
            this->Ac[c - 1].clearBit(F[c] - 1); // 0-based bit position
        }
    }

    for (int k = 0; k < numBlocks; ++k) {
        std::fill(F.begin(), F.end(), 0);

        const int blockStart = k * sigma;
        const int blockEnd = std::min((k + 1) * sigma, n);
        const int l = blockEnd - blockStart;

        std::vector<int> temPi(l, 0);    // pi_k[1, l] -> stores 0-based local offsets [0, l-1]
        bitVector temDk(l + sigma);      // Dk[1, l + sigma] -> 0-based size l + sigma
        this->Dk.push_back(temDk);

        for (int i = blockStart; i < blockEnd; ++i) {
            F[S[i] + 1] = F[S[i] + 1] + 1;
        }
        for (int c = 1; c <= sigma; ++c) {
            F[c] = F[c] + F[c - 1];
            this->Dk[k].setBit(F[c] + c - 1); // 0-based bit position
        }
        for (int i = blockStart; i < blockEnd; ++i) {
            const int s = S[i];
            F[s] = F[s] + 1;
            const int piPos = F[s] - 1; // 0-based pi index
            temPi[piPos] = i - blockStart;
            this->Dk[k].clearBit(F[s] + s - 1); // 0-based bit position
        }

        // Preprocess pi_k for read and inverse queries (Algorithm 6.2, line 32): wrap the
        // raw local permutation in the compact Permutation representation instead of
        // keeping it as a plain vector.
        this->pi.push_back(Permutation(temPi, t));
    }
    for (int c = 0; c < sigma; ++c) {
        this->Ac[c].finishSetUp();
    }
    for (int k = 0; k < numBlocks; ++k) {
        this->Dk[k].finishSetUp();
    }
}

int Sequence::access(int index) {
    int k = index / this->sigma;
    int i = ((index - 1) % this->sigma) + 1;
    int j = inverse()
    if (index < 0 || index >= Ssize) {
        throw std::out_of_range("Index out of bounds");
    }
    return S[index].access(0); // Assuming access returns the symbol at the given index
}

int Sequence::rank(int symbol, int index) {
    if (symbol < 1 || symbol > sigma) return -1; // Invalid symbol
    if (index < 0 || index >= Ssize) return -1; // Invalid index
    if (index == 0) return 0;
    int k = index / this->sigma;
    int l = 

    return S[symbol - 1].rank1(index);
}

int Sequence::select(int symbol, int rank) {// select_c(j) <--> selsect(c,j)
    const auto Ac = this->Ac[symbol];
    if (symbol < 1 || symbol > sigma) return -1; // Invalid symbol
    if (rank < 1) return -1; // Invalid rank
    if (rank == 0) return 0;
    int s = Ac.select1(rank);
    if (s == -1) return -1; // Symbol not found
    if (s > Ac.size) return this->n + 1; // Out of bounds
    int jp = s - k * this->sigma;
    int sL = this->Dk[k].select1(jp);
    return (s-j)* this->sigma + this->pi[k].access(sL+jp);
}