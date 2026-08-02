# Para Bit Vectors
Desde root
> g++ -std=c++17 appBenchmark/test/bitVectorTEST.cpp appBenchmark/canonicalDS/bitVector.cpp -o appBenchmark/bin/bvTEST

# Para Permutaciones
Desde root
> g++ -std=c++17 appBenchmark/test/permutationTEST.cpp appBenchmark/canonicalDS/permutation.cpp appBenchmark/canonicalDS/bitVector.cpp -o appBenchmark/bin/pmTEST

# Para Secuencias
Desde root
> g++ -std=c++17 appBenchmark/test/sequenceTEST.cpp appBenchmark/canonicalDS/Sequence.cpp appBenchmark/canonicalDS/permutation.cpp appBenchmark/canonicalDS/bitVector.cpp -o appBenchmark/bin/sqTEST




g++ -std=c++17 appBenchmark/benchmark.cpp appBenchmark/graph.cpp appBenchmark/graphBitVector.cpp appBenchmark/graphSequence.cpp appBenchmark/canonicalDS/bitVector.cpp appBenchmark/canonicalDS/Sequence.cpp appBenchmark/canonicalDS/permutation.cpp -IappBenchmark -IappBenchmark/canonicalDS -o appBenchmark/bin/benchmark_bin