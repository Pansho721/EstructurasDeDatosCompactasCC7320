#include "Sequence.h"
#include <cmath>

Sequence::Sequence() : n(0), sigma(0) {}

Sequence::Sequence(std::vector<int> S, int sigma, int t) : n(S.size()), sigma(sigma) {
    std::vector<int> F(sigma + 1, 0);
    const int block = n / sigma;

    for (int i = 0; i < n; ++i) {
        F[S[i]] = F[S[i]] + 1;
    }
    for (int c = 0; c < sigma; ++c) {
        Ac.push_back(bitVector(F[c] + block - 2));
        F[c] = 0;
    }
    for (int k = 0; k < block; ++k) {
        for (int i = (k-1)*sigma + 1; i < std::min(k*sigma, n); ++i) {
            F[S[i]] = F[S[i]] + 1;
            Ac[S[i]].setBit(F[S[i]]);
        }
        for (int c = 0; c < sigma; ++c) {
            F[c] = F[c] + 1;
            Ac[c].clearBit(F[c]);
        }
    }
    std::vector<Permutation> pi;
    std::vector<bitVector> Dk;
    
    for (int k = 0; k < block; ++k) {
        for (int c = 0; c < sigma; ++c) {
            F[c] = 0;
        }
        int l = std::min(k * sigma, n) - ((k - 1) * sigma);
        std::vector<int> pik(l-1);
        bitVector Dkk(l + sigma - 1);
        for (int i = (k-1)*sigma + 1; i < std::min(k*sigma, n); ++i) {
            F[S[i]] = F[S[i]] + 1;
        }
        for (int c = 0; c < sigma; ++c) {
            F[c] = F[c] + F[c-1];
            Dkk.setBit(F[c] + c);
        }
        for (int i  = (k-1)*sigma + 1; i < std::min(k*sigma, n); ++i) {
            F[S[i - 1]] = F[S[i] - 1] + 1;
            pik[F[S[i]] - 1] = i - ((k - 1) * sigma);
            Dkk.clearBit(F[S[i]-1] + S[i] - 1);
        }
        Dk.push_back(Dkk);
        pi.push_back(Permutation(pik, std::ceil(std::log2(sigma))));
    }
    this->Ac = Ac;
    this->Dk = Dk;
    this->pi = pi;
}

int Sequence::access(int index) {
    if (index < 0 || index >= n) {
        return -1;
    }
    const int k = index / sigma;
    const int ip = ((index - 1) % sigma) + 1;
    const int j = this->pi[k].inverse(ip);

    return this->Dk[k].select0(j) - j + 1;
}

int Sequence::rank(int symbol, int index) {
    if (symbol < 0 || symbol >= sigma) return -1; // Invalid symbol
    if (index == 0) return 0;
    if (index > n) return n + 1;

    const int k = index / sigma;
    const int ip = ((index - 1) % sigma) + 1;
    const int sL = this->Dk[k].select1(symbol - 1) - (symbol - 1);
    const int eL = this->Dk[k].select1(symbol) - symbol;

    int first = sL + 1;
    int last = eL;
    int j = sL;
    while (first <= last) {
        int mid = (first + last) / 2;
        int value = this->pi[k].access(mid);
        if (value <= ip) {
            j = mid;
            first = mid + 1;
        } else {
            last = mid - 1;
        }
    }

    return this->Ac[symbol].select0(k - 1) - (k - 1) - (j - sL);

}

int Sequence::select(int symbol, int j) { // select_c(j) <--> select(c, j)
    if (symbol < 0 || symbol >= sigma) return -1; // Invalid symbol
    if (j < 1) return -1;
    if (j == 0) return 0;

    const int s = this->Ac[symbol].select1(j);
    if (s > this->Ac.size()) return n + 1;

    const int jp = s - this->Ac[symbol].pred0(s);
    const int sL = this->Dk[s-j+1].select1(symbol - 1) - (symbol - 1);

    return (s - j) * sigma + this->pi[s-j+1].access(sL + jp);
}