CXX := g++
CXXFLAGS := -std=c++17
OMPFLAGS := -fopenmp

BIN_DIR := appBenchmark/bin
TEST_DIR := appBenchmark/test
DS_DIR := appBenchmark/canonicalDS
APP_DIR := appBenchmark

GRAPH_FILE ?= graphs/reddit_numeric.edgelist

BV_BIN := $(BIN_DIR)/bvTEST
PM_BIN := $(BIN_DIR)/pmTEST
SQ_BIN := $(BIN_DIR)/sqTEST
BENCH_BIN := $(BIN_DIR)/benchmark_bin
BENCH_OMP_BIN := $(BIN_DIR)/benchmark_omp_bin

.PHONY: all benchmark benchmarkomp test bv pm sq clean

all: benchmark

benchmark: $(BENCH_BIN)
	./$(BENCH_BIN) $(GRAPH_FILE)

benchmarkomp: $(BENCH_OMP_BIN)
	./$(BENCH_OMP_BIN) $(GRAPH_FILE)

test: bv pm sq

bv: $(BV_BIN)
	./$(BV_BIN)

pm: $(PM_BIN)
	./$(PM_BIN)

sq: $(SQ_BIN)
	./$(SQ_BIN)

$(BV_BIN): $(TEST_DIR)/bitVectorTEST.cpp $(DS_DIR)/bitVector.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(PM_BIN): $(TEST_DIR)/permutationTEST.cpp $(DS_DIR)/permutation.cpp $(DS_DIR)/bitVector.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(SQ_BIN): $(TEST_DIR)/sequenceTEST.cpp $(DS_DIR)/Sequence.cpp $(DS_DIR)/permutation.cpp $(DS_DIR)/bitVector.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BENCH_BIN): $(APP_DIR)/benchmark.cpp $(APP_DIR)/graph.cpp $(APP_DIR)/graphBitVector.cpp $(APP_DIR)/graphSequence.cpp $(DS_DIR)/Sequence.cpp $(DS_DIR)/permutation.cpp $(DS_DIR)/bitVector.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BENCH_OMP_BIN): $(APP_DIR)/benchmark.cpp $(APP_DIR)/graph.cpp $(APP_DIR)/graphBitVector.cpp $(APP_DIR)/graphSequence.cpp $(DS_DIR)/Sequence.cpp $(DS_DIR)/permutation.cpp $(DS_DIR)/bitVector.cpp
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) $^ -o $@

clean:
	rm -f $(BV_BIN) $(PM_BIN) $(SQ_BIN) $(BENCH_BIN) $(BENCH_OMP_BIN)
