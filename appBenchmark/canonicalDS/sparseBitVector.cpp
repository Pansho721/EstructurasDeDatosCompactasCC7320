#include "sparseBitVector.h"

namespace {
sdsl::bit_vector makeBitVector(int size) {
    return sdsl::bit_vector(static_cast<std::size_t>(size), 0);
}
} // namespace

sparseBitVector::sparseBitVector() : n(0), finalized(false), pendingBits(), bits() {}

sparseBitVector::sparseBitVector(int s) : n(s), finalized(false), pendingBits(makeBitVector(s)), bits() {}

sparseBitVector::sparseBitVector(std::vector<bool> s) : n(static_cast<int>(s.size())), finalized(true), pendingBits(), bits() {
    sdsl::bit_vector dense(static_cast<std::size_t>(n), 0);
    for (int i = 0; i < n; ++i) {
        dense[i] = s[i];
    }
    bits = sdsl::sd_vector<>(dense);
}

void sparseBitVector::setBit(int index) {
    if (finalized || index < 0 || index >= this->n) {
        return;
    }
    pendingBits[static_cast<std::size_t>(index)] = 1;
}

void sparseBitVector::clearBit(int index) {
    if (finalized || index < 0 || index >= this->n) {
        return;
    }
    pendingBits[static_cast<std::size_t>(index)] = 0;
}

void sparseBitVector::finishSetUp() {
    if (finalized) {
        return;
    }
    bits = sdsl::sd_vector<>(pendingBits);
    finalized = true;
    pendingBits = sdsl::bit_vector();
}

bool sparseBitVector::access(int index) {
    if (index < 0 || index >= this->n) {
        return false;
    }
    if (!finalized) {
        return pendingBits[static_cast<std::size_t>(index)];
    }
    return bits[static_cast<std::size_t>(index)];
}

int sparseBitVector::rank0(int index) {
    if (index < 0 || index >= this->n) {
        return 0;
    }
    if (!finalized) {
        int count = 0;
        for (int i = 0; i <= index; ++i) {
            if (!pendingBits[static_cast<std::size_t>(i)]) {
                ++count;
            }
        }
        return count;
    }
    sdsl::sd_vector<>::rank_0_type rankSupport(&bits);
    return static_cast<int>(rankSupport(static_cast<std::size_t>(index + 1)));
}

int sparseBitVector::rank1(int index) {
    if (index < 0 || index >= this->n) {
        return 0;
    }
    if (!finalized) {
        int count = 0;
        for (int i = 0; i <= index; ++i) {
            if (pendingBits[static_cast<std::size_t>(i)]) {
                ++count;
            }
        }
        return count;
    }
    sdsl::sd_vector<>::rank_1_type rankSupport(&bits);
    return static_cast<int>(rankSupport(static_cast<std::size_t>(index + 1)));
}

int sparseBitVector::select1(int rank) {
    if (rank <= 0) {
        return 0;
    }
    const int totalOnes = (this->n == 0) ? 0 : rank1(this->n - 1);
    if (totalOnes == 0) {
        return 0;
    }
    if (rank > totalOnes) {
        rank = totalOnes;
    }
    if (!finalized) {
        int seen = 0;
        for (int i = 0; i < this->n; ++i) {
            if (pendingBits[static_cast<std::size_t>(i)] && ++seen == rank) {
                return i;
            }
        }
        return 0;
    }
    sdsl::sd_vector<>::select_1_type selectSupport(&bits);
    return static_cast<int>(selectSupport(static_cast<std::size_t>(rank)));
}

int sparseBitVector::select0(int rank) {
    if (rank <= 0) {
        return 0;
    }
    const int totalZeros = this->n - ((this->n == 0) ? 0 : rank1(this->n - 1));
    if (totalZeros == 0) {
        return 0;
    }
    if (rank > totalZeros) {
        return this->n + 1;
    }
    if (!finalized) {
        int seen = 0;
        for (int i = 0; i < this->n; ++i) {
            if (!pendingBits[static_cast<std::size_t>(i)] && ++seen == rank) {
                return i;
            }
        }
        return this->n + 1;
    }
    sdsl::sd_vector<>::select_0_type selectSupport(&bits);
    return static_cast<int>(selectSupport(static_cast<std::size_t>(rank)));
}

int sparseBitVector::length() {
    return this->n;
}

int sparseBitVector::size_in_bytes() {
    uint64_t bits_mem = sdsl::size_in_bytes(this->bits);
    uint64_t pending_mem = sdsl::size_in_bytes(this->pendingBits);
    return 4 + 1 + bits_mem + pending_mem;
}

int sparseBitVector::pred0(int index) {
    if (index < 0 || index >= this->n) {
        return -1;
    }
    return select0(rank0(index));
}

int sparseBitVector::pred1(int index) {
    if (index < 0 || index >= this->n) {
        return -1;
    }
    return select1(rank1(index));
}

int sparseBitVector::succ0(int index) {
    if (index < 0 || index >= this->n) {
        return -1;
    }
    return select0(rank0(index - 1) + 1);
}

int sparseBitVector::succ1(int index) {
    if (index < 0 || index >= this->n) {
        return -1;
    }
    return select1(rank1(index - 1) + 1);
}