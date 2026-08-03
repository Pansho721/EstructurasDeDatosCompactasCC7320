#include "Sequence.h"
#include <cmath>
#include <iostream>

Sequence::Sequence() : n(0), sigma(0) {}

Sequence::Sequence(std::vector<int> S, int sigma) : n(S.size()), sigma(sigma) {
    std::vector<int> F(sigma + 1, 0);//F[0,sigma]
    const int block = std::ceil(static_cast<double>(this->n) / sigma);
    const int n = this->n;
    std::vector<bitVector> Ac;

    for (int i = 0; i < n; ++i) {
        F[S[i]] = F[S[i]] + 1;
    }
    for (int c = 0; c < sigma; c++) {
        Ac.push_back(bitVector(F[c] + block - 1));
        F[c] = 0;
    }
    for (int k = 0; k < block; ++k) {
        for (int i = k*sigma; i < std::min((k+1)*sigma, n); ++i) {
            F[S[i]] = F[S[i]] + 1;
            Ac[S[i]].setBit(F[S[i]] - 1);
        }
        for (int c = 0; c < sigma; ++c) {
            F[c] = F[c] + 1;
            Ac[c].clearBit(F[c] - 1);
        }
    }
    for (int c = 0; c < sigma; ++c) {
        Ac[c].finishSetUp();
        continue;
    }
    this->A = Ac;

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
    if (index <= 0) return 0;
    if (index > n) index = n;

    // Position (0-based) of the last element considered, and the chunk/offset it lives in.
    const int pos0 = index - 1;
    const int k = pos0 / sigma;
    const int ip = pos0 - k * sigma;
    const int chunkLen = std::min((k + 1) * sigma, n) - k * sigma;

    // sL/eL bound (0-based, half-open on the right via eL-1) the slice of pi[k] that
    // corresponds to `symbol`'s list of positions within this chunk. D[k] is laid out as
    // 1 0^|L0| 1 0^|L1| ... 1 0^|L_{sigma-1}| (a separator right before each list).
    const int sL = this->D[k].select1(symbol + 1) - symbol;
    const int eL = (symbol == sigma - 1) ? chunkLen : (this->D[k].select1(symbol + 2) - (symbol + 1));

    int lo = sL, hi = eL - 1;
    int countInChunk = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (this->pi[k].access(mid) <= ip) {
            countInChunk = mid - sL + 1;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    const int base = (k == 0) ? 0 : (this->A[symbol].select0(k) - k + 1);
    return base + countInChunk;
}

int Sequence::select(int symbol, int j) { // select_c(j) <--> select(c, j)
    if (symbol < 0 || symbol >= sigma) return -1;
    if (j <= 0) return 0;

    bitVector &Ac = this->A[symbol];
    const int totalCount = (Ac.length() > 0) ? Ac.rank1(Ac.length() - 1) : 0;
    if (j > totalCount) return n + 1;

    const int s = Ac.select1(j);
    // Local (1-based) occurrence number of `symbol` within its chunk, and that chunk's index.
    const int jp = (Ac.rank0(s) == 0) ? (s + 1) : (s - Ac.pred0(s));
    const int chunkIdx = s - j + 1;

    const int sL = this->D[chunkIdx].select1(symbol + 1) - symbol;
    const int offset = this->pi[chunkIdx].access(sL + jp - 1);

    return chunkIdx * sigma + offset;
}

void Sequence::seeA() {
    std::cout << "sigma: " << this->sigma << std::endl;
    for (int c=0;c<this->sigma;c++){
        for (int i=0; i<this->A[c].length() ; i++){
            std::cout << "c: " << c << " | i: " << i << " | access_c(i):" << this->A[c].access(i) << std::endl;
        }
        std::cout << "________________________" << std::endl;
    }
}