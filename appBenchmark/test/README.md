# Para Bit Vectors
Desde la carpeta test
> g++ -std=c++17 bitVectorTEST.cpp ../canonicalDS/bitVector.cpp -o ../bin/bvTEST

Desde root
> g++ -std=c++17 appBenchmark/test/bitVectorTEST.cpp appBenchmark/canonicalDS/bitVector.cpp -o appBenchmark/bin/bvTEST

# Para Permutaciones
> g++ -std=c++17 bitVectorTEST.cpp ../canonicalDS/bitVector.cpp -o ../bin/bvTEST

Desde root
> g++ -std=c++17 appBenchmark/test/bitVectorTEST.cpp appBenchmark/canonicalDS/bitVector.cpp appBenchmark/canonicalDS/permutation.cpp -o appBenchmark/bin/bvTEST




g++ -std=c++17 appBenchmark/benchmark.cpp appBenchmark/graph.cpp appBenchmark/graphBitVector.cpp appBenchmark/graphSequence.cpp appBenchmark/canonicalDS/bitVector.cpp appBenchmark/canonicalDS/Sequence.cpp appBenchmark/canonicalDS/permutation.cpp -IappBenchmark -IappBenchmark/canonicalDS -o appBenchmark/bin/benchmark_bin