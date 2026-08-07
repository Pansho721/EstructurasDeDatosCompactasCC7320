CXX := g++
CXXFLAGS := -std=c++17 -Wno-deprecated-declarations
SDSL_DIR := external/sdsl-lite
SDSL_INC := $(SDSL_DIR)/include
SDSL_SRC := $(SDSL_DIR)/lib/bits.cpp $(SDSL_DIR)/lib/util.cpp $(SDSL_DIR)/lib/ram_fs.cpp $(SDSL_DIR)/lib/memory_management.cpp

CXXFLAGS += -I$(SDSL_INC)

BIN_DIR := appBenchmark/bin
TEST_DIR := appBenchmark/test
DS_DIR := appBenchmark/canonicalDS
APP_DIR := appBenchmark

GRAPH_FILE ?= graphs/reddit_numeric.edgelist

BV_BIN := $(BIN_DIR)/bvTEST
PM_BIN := $(BIN_DIR)/pmTEST
SQ_BIN := $(BIN_DIR)/sqTEST
BENCH_BIN := $(BIN_DIR)/benchmark_bin
TESTT_BIN := $(BIN_DIR)/testT

.PHONY: all benchmark test bv pm sq testT clean

all: benchmark

benchmark: $(BENCH_BIN)
	./$(BENCH_BIN) $(GRAPH_FILE)

test: bv pm sq

testT: $(TESTT_BIN)
	./$(TESTT_BIN)

bv: $(BV_BIN)
	./$(BV_BIN)

pm: $(PM_BIN)
	./$(PM_BIN)

sq: $(SQ_BIN)
	./$(SQ_BIN)

$(BV_BIN): $(TEST_DIR)/bitVectorTEST.cpp $(DS_DIR)/bitVector.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(PM_BIN): $(TEST_DIR)/permutationTEST.cpp $(DS_DIR)/permutation.cpp $(DS_DIR)/bitVector.cpp $(DS_DIR)/sparseBitVector.cpp $(SDSL_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(SQ_BIN): $(TEST_DIR)/sequenceTEST.cpp $(DS_DIR)/Sequence.cpp $(DS_DIR)/permutation.cpp $(DS_DIR)/bitVector.cpp $(DS_DIR)/sparseBitVector.cpp $(SDSL_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BENCH_BIN): $(APP_DIR)/benchmark.cpp $(APP_DIR)/graph.cpp $(APP_DIR)/graphBitVector.cpp $(APP_DIR)/graphSequence.cpp $(DS_DIR)/Sequence.cpp $(DS_DIR)/permutation.cpp $(DS_DIR)/bitVector.cpp $(DS_DIR)/sparseBitVector.cpp $(SDSL_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TESTT_BIN): $(APP_DIR)/benchmark-heuristic.cpp $(DS_DIR)/permutation.cpp $(DS_DIR)/bitVector.cpp $(DS_DIR)/sparseBitVector.cpp $(SDSL_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(BV_BIN) $(PM_BIN) $(SQ_BIN) $(BENCH_BIN) $(TESTT_BIN)
