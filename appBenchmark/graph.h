#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

using Edge = std::pair<uint64_t, uint64_t>;

// Reads a "u v [w]" edge list. Returns the edges sorted by (u, v) without duplicates,
// and sets numNodes to max node id + 1.
std::vector<Edge> loadEdges(const std::string& file, uint64_t& numNodes);

class BenchmarkDoc {
    public:
        std::string name;
        float constructionTime;
        float sizePerEdge;
        // Average time per query in nanoseconds; negative means "not supported".
        float adjTime;
        float neighTime;
        float rneighTime;
        float outDegreeTime;
        float inDegreeTime;

        explicit BenchmarkDoc(std::string n);
        void print();
};

class graph {
    public:
        graph() = default;
        // sdsl rank/select supports keep pointers to their bitvectors, so graphs are not copyable.
        graph(const graph&) = delete;
        graph& operator=(const graph&) = delete;
        virtual ~graph() = default;

        virtual std::string name() = 0;
        virtual float sizePerEdge() = 0;
        virtual bool supportsReverse() { return false; }

        virtual bool adj(uint64_t u, uint64_t v) = 0;
        virtual int64_t neighj(uint64_t u, uint64_t j) = 0;
        virtual std::vector<uint64_t> neigh(uint64_t u) = 0;
        virtual uint64_t outDegree(uint64_t u) = 0;

        // Reverse operations; only available when supportsReverse() is true.
        virtual int64_t rneighj(uint64_t, uint64_t) { return -1; }
        virtual std::vector<uint64_t> rneigh(uint64_t) { return {}; }
        virtual uint64_t inDegree(uint64_t) { return 0; }

        uint64_t numNodes() const { return n; }
        uint64_t numEdges() const { return e; }

    protected:
        uint64_t n = 0;
        uint64_t e = 0;
};
