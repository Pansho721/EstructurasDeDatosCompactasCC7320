CXX := g++
CXXFLAGS := -std=c++17 -O2 -DNDEBUG -Wno-deprecated-declarations
SDSL_DIR := external/sdsl-lite
SDSL_INC := $(SDSL_DIR)/include
SDSL_LIB := bits util io config ram_fs ram_filebuf sfstream memory_management sd_vector rrr_vector_15

CXXFLAGS += -I$(SDSL_INC)

BIN_DIR := appBenchmark/bin
OBJ_DIR := $(BIN_DIR)/obj
TEST_DIR := appBenchmark/test
DS_DIR := appBenchmark/canonicalDS
APP_DIR := appBenchmark

GRAPH_FILE ?= graphs/reddit_numeric.edgelist

SDSL_OBJ := $(SDSL_LIB:%=$(OBJ_DIR)/sdsl_%.o)
GRAPH_SRC := $(APP_DIR)/graph.cpp $(APP_DIR)/graphBitVector.cpp $(APP_DIR)/graphSequence.cpp $(APP_DIR)/graphK2Tree.cpp
GRAPH_HDR := $(APP_DIR)/graph.h $(APP_DIR)/graphBitVector.h $(APP_DIR)/graphSequence.h $(APP_DIR)/graphK2Tree.h
PERM_SRC := $(DS_DIR)/permutation.cpp
PERM_HDR := $(DS_DIR)/permutation.h

GRAPH_TEST_BIN := $(BIN_DIR)/graphTEST
PM_BIN := $(BIN_DIR)/pmTEST
BENCH_BIN := $(BIN_DIR)/benchmark_bin
TESTT_BIN := $(BIN_DIR)/testT

.PHONY: all benchmark test bv pm sq k2 testT clean

all: benchmark

benchmark: $(BENCH_BIN)
	./$(BENCH_BIN) $(GRAPH_FILE)

test: bv sq k2 pm

testT: $(TESTT_BIN)
	./$(TESTT_BIN)

bv: $(GRAPH_TEST_BIN)
	./$(GRAPH_TEST_BIN) bv $(GRAPH_FILE)

sq: $(GRAPH_TEST_BIN)
	./$(GRAPH_TEST_BIN) sq $(GRAPH_FILE)

k2: $(GRAPH_TEST_BIN)
	./$(GRAPH_TEST_BIN) k2 $(GRAPH_FILE)

pm: $(PM_BIN)
	./$(PM_BIN)

$(OBJ_DIR)/sdsl_%.o: $(SDSL_DIR)/lib/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(BENCH_BIN): $(APP_DIR)/benchmark.cpp $(GRAPH_SRC) $(GRAPH_HDR) $(SDSL_OBJ)
	$(CXX) $(CXXFLAGS) $(filter %.cpp %.o,$^) -o $@

$(GRAPH_TEST_BIN): $(TEST_DIR)/graphTEST.cpp $(GRAPH_SRC) $(GRAPH_HDR) $(SDSL_OBJ)
	$(CXX) $(CXXFLAGS) $(filter %.cpp %.o,$^) -o $@

$(PM_BIN): $(TEST_DIR)/permutationTEST.cpp $(PERM_SRC) $(PERM_HDR) $(SDSL_OBJ)
	$(CXX) $(CXXFLAGS) $(filter %.cpp %.o,$^) -o $@

$(TESTT_BIN): $(APP_DIR)/benchmark-heuristic.cpp $(PERM_SRC) $(PERM_HDR) $(SDSL_OBJ)
	$(CXX) $(CXXFLAGS) $(filter %.cpp %.o,$^) -o $@

clean:
	rm -rf $(GRAPH_TEST_BIN) $(PM_BIN) $(BENCH_BIN) $(TESTT_BIN) $(OBJ_DIR)
