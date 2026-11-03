#pragma once
#include <vector>

#include <sdsl/bit_vectors.hpp>
#include <sdsl/int_vector.hpp>

// Permutation with shortcuts every t steps along each cycle (Munro et al.),
// giving inverse() in O(t) time with n*log(n)/t extra bits.
// sdsl has no permutation class, so this is built on sdsl primitives.
class Permutation {
    private:
        uint64_t n;
        sdsl::int_vector<> pi;    // pi[i], log2(n) bits each
        sdsl::int_vector<> S;     // S[rank1(B, j)] = back pointer from shortcut j
        sdsl::bit_vector B;       // B[j] = 1 iff j has a back pointer
        sdsl::rank_support_v5<> rankB;

    public:
        Permutation(const std::vector<int>& pi, int t);
        Permutation(const Permutation&) = delete;
        Permutation& operator=(const Permutation&) = delete;

        int access(int index);
        int inverse(int index);
        int size_in_bytes();
        int inverse_steps(int index);
};
