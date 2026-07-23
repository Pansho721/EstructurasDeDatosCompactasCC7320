#include "numSequence.h"

Sequence::Sequence(int n, int sigma) : Ssize(n), sigma(sigma) {
    for (int i = 0; i < sigma; ++i) {
        S.push_back(bitVector(i + 1));
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