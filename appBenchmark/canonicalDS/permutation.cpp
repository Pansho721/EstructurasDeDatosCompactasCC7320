#include "permutation.h"

Permutation::Permutation(const std::vector<int>& p, int t) : n(p.size()) {
    const uint8_t width = sdsl::bits::hi(n > 1 ? n - 1 : 1) + 1;
    pi = sdsl::int_vector<>(n, 0, width);
    for (uint64_t i = 0; i < n; ++i) pi[i] = p[i];

    // Mark the start of every cycle and every t-th element along it.
    B = sdsl::bit_vector(n, 0);
    sdsl::bit_vector visited(n, 0);
    std::vector<std::vector<uint64_t>> marksPerCycle;
    for (uint64_t i = 0; i < n; ++i) {
        if (visited[i]) continue;
        std::vector<uint64_t> marks;
        uint64_t j = i;
        uint64_t k = 0;
        do {
            visited[j] = 1;
            if (k % t == 0) {
                B[j] = 1;
                marks.push_back(j);
            }
            j = pi[j];
            ++k;
        } while (j != i);
        marksPerCycle.push_back(std::move(marks));
    }
    sdsl::util::init_support(rankB, &B);

    // Each mark points back to the previous mark of its cycle (the first one to the last).
    S = sdsl::int_vector<>(rankB(n), 0, width);
    for (const std::vector<uint64_t>& marks : marksPerCycle) {
        for (uint64_t l = 0; l < marks.size(); ++l) {
            const uint64_t prev = marks[(l + marks.size() - 1) % marks.size()];
            S[rankB(marks[l])] = prev;
        }
    }
}

int Permutation::access(int index) {
    if (index < 0 || static_cast<uint64_t>(index) >= n) return -1;
    return pi[index];
}

int Permutation::inverse(int index) {
    if (index < 0 || static_cast<uint64_t>(index) >= n) return -1;
    uint64_t j = index;
    bool jumped = false;
    while (pi[j] != static_cast<uint64_t>(index)) {
        if (!jumped && B[j]) {
            j = S[rankB(j)];
            jumped = true;
        } else {
            j = pi[j];
        }
    }
    return j;
}

int Permutation::size_in_bytes() {
    return sdsl::size_in_bytes(pi) + sdsl::size_in_bytes(S) + sdsl::size_in_bytes(B) + sdsl::size_in_bytes(rankB);
}

int Permutation::inverse_steps(int index) {  // debug version of inverse()
    uint64_t j = index;
    int steps = 0;
    bool jumped = false;
    while (pi[j] != static_cast<uint64_t>(index)) {
        if (!jumped && B[j]) {
            j = S[rankB(j)];
            jumped = true;
        } else {
            j = pi[j];
        }
        steps++;
    }
    return steps;
}
