#include "../canonicalDS/permutation.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>

int main() {
    int failures = 0;

    // Small example, printed for inspection.
    std::vector<int> pi = {2, 0, 1, 4, 3};
    Permutation perm(pi, 2);
    for (int i = 0; i < static_cast<int>(pi.size()); ++i) {
        std::cout << "perm.access(" << i << ") = " << perm.access(i)
                  << ", perm.inverse(" << i << ") = " << perm.inverse(i) << std::endl;
        if (perm.access(i) != pi[i] || pi[perm.inverse(i)] != i) ++failures;
    }

    // Random permutations, several shortcut lengths t.
    std::mt19937 rng(1);
    for (int n : {1, 2, 17, 1000, 35776}) {
        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);
        std::shuffle(p.begin(), p.end(), rng);
        std::vector<int> inv(n);
        for (int i = 0; i < n; ++i) inv[p[i]] = i;
        for (int t : {1, 2, 3, 16, 100}) {
            Permutation q(p, t);
            for (int i = 0; i < n; ++i) {
                if (q.access(i) != p[i] || q.inverse(i) != inv[i]) ++failures;
            }
        }
    }

    std::cout << (failures == 0 ? "PASS" : "FAIL") << ": Permutation (" << failures << " mismatches)" << std::endl;
    return failures == 0 ? 0 : 1;
}
