CXX := g++
CXXFLAGS := -std=c++17

BIN_DIR := appBenchmark/bin
TEST_DIR := appBenchmark/test
DS_DIR := appBenchmark/canonicalDS

BV_BIN := $(BIN_DIR)/bvTEST
PM_BIN := $(BIN_DIR)/pmTEST
SQ_BIN := $(BIN_DIR)/sqTEST

.PHONY: all bv pm sq clean

all: bv pm sq

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

clean:
	rm -f $(BV_BIN) $(PM_BIN) $(SQ_BIN)
