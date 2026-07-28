#include "Sequence.h"
#include <algorithm>
#include <stdexcept>

Sequence::Sequence() : n(0), sigma(0) {}

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
    if (index < 0 || index >= n) {
        throw std::out_of_range("Index out of bounds");
    }
    const int k = index / sigma;
    const int p = index - k * sigma; // local position within block k

    // p is a local position; pi[k].inverse(p) recovers the combined occurrence-rank r
    // (0-based, symbols grouped in order) that Dk[k] was built with for that position.
    const int r = this->pi[k].inverse(p);
    const int pos = this->Dk[k].select0(r + 1); // position of the occurrence's own slot
    return this->Dk[k].rank1(pos); // number of completed symbol-groups before pos == symbol
}

int Sequence::rank(int symbol, int index) {
    if (symbol < 0 || symbol >= sigma) return -1; // Invalid symbol
    if (index <= 0) return 0;
    if (index > n) index = n;

    const int idx = index - 1; // last position included in the count
    const int k = idx / sigma;
    const int p = idx - k * sigma;

    int cumulativeBeforeBlock = 0;
    if (k > 0) {
        // select0(k) is the gap right after block (k-1) in Ac[symbol]; everything before it
        // (rank1) is the total count of `symbol` accumulated through block (k-1).
        const int gapPos = this->Ac[symbol].select0(k);
        cumulativeBeforeBlock = this->Ac[symbol].rank1(gapPos - 1);
    }

    int rangeStart = 0;
    if (symbol > 0) {
        const int prevBoundary = this->Dk[k].select1(symbol);
        rangeStart = prevBoundary - this->Dk[k].rank1(prevBoundary - 1); // rank0(prevBoundary - 1)
    }
    const int boundary = this->Dk[k].select1(symbol + 1);
    const int rangeEnd = boundary - this->Dk[k].rank1(boundary - 1); // rank0(boundary - 1), exclusive

    int localCount = 0;
    for (int r = rangeStart; r < rangeEnd; ++r) {
        if (this->pi[k].access(r) <= p) localCount++;
    }

    return cumulativeBeforeBlock + localCount;
}

int Sequence::select(int symbol, int rank) { // select_c(j) <--> select(c, j)
    if (symbol < 0 || symbol >= sigma) return -1; // Invalid symbol
    if (rank < 1) return -1; // Invalid rank

    const int pos = this->Ac[symbol].select1(rank);
    if (pos < 0 || pos >= this->Ac[symbol].length()) return -1; // rank exceeds total occurrences

    const int k = (pos + 1) - this->Ac[symbol].rank1(pos); // rank0(pos): completed blocks before this occurrence's block

    int cumulativeBeforeBlock = 0;
    if (k > 0) {
        const int gapPos = this->Ac[symbol].select0(k);
        cumulativeBeforeBlock = this->Ac[symbol].rank1(gapPos - 1);
    }
    const int localRank1Based = rank - cumulativeBeforeBlock; // rank within block k

    int rangeStart = 0;
    if (symbol > 0) {
        const int prevBoundary = this->Dk[k].select1(symbol);
        rangeStart = prevBoundary - this->Dk[k].rank1(prevBoundary - 1); // rank0(prevBoundary - 1)
    }
    const int combinedRank = rangeStart + (localRank1Based - 1);

    const int p = this->pi[k].access(combinedRank);
    return k * sigma + p;
}