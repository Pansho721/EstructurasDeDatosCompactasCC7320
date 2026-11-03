# EstructurasDeDatosCompactasCC7320
Compact analysis for a Reddit hyperlinks graph.

## Representations

Both graph representations are built entirely from [sdsl-lite](https://github.com/simongog/sdsl-lite) structures.
Edges are read from the edge list, sorted by `(u, v)` and deduplicated.

| Representation | Structure | Operations | Bits per edge* |
|---|---|---|---|
| `GraphBitVector` | One `sd_vector<>` (Elias-Fano) of length N², bit `u*N+v` set iff `(u, v)` is an edge | `adj`, `neigh`, `neighj`, `outDegree` | 17.1 |
| `GraphSequence` | `wm_int<rrr_vector<63>>` over the concatenated adjacency lists + unary degree `sd_vector<>` | all, including `rneigh`, `rneighj`, `inDegree` | 14.7 |
| `GraphK2Tree` | sdsl `k2_tree<2>` over the N×N adjacency matrix | all (degrees and `neighj`/`rneighj` are derived from the full neighbor lists) | 19.6 |

\* On `reddit_numeric.edgelist` (35776 nodes, 137821 edges). The information-theoretic lower bound
log2 C(N², E) / E is 14.6 bits per edge; the benchmark prints it for any input graph.

The `Permutation` class (`appBenchmark/canonicalDS/`) implements the shortcut technique with parameter `t`.
sdsl has no permutation, so it is built on sdsl `int_vector<>`, `bit_vector` and `rank_support_v5<>`.
It is used by the `t`-parameter study (`make testT`).

## Makefile Tutorial

This project is managed through the Makefile. You do not need to compile files manually with g++ commands.

### 1. Requirements

- g++ with C++17 support
- make
- The SDSL library is included as the `external/sdsl-lite` git submodule

### 2. Quick Start

From the repository root:

```bash
git submodule update --init --recursive
make
```

By default, this runs the benchmark.

### 3. Main Targets

Run benchmark (default target):

```bash
make benchmark
```

Run all tests:

```bash
make test
```

Run tests individually:

```bash
make bv   # GraphBitVector vs. plain adjacency lists built from GRAPH_FILE
make sq   # GraphSequence vs. plain adjacency lists built from GRAPH_FILE
make k2   # GraphK2Tree vs. plain adjacency lists built from GRAPH_FILE
make pm   # Permutation access/inverse on random permutations
```

Run analisis for t parameter on sequences

```bash
make testT
```

Clean generated binaries:

```bash
make clean
```

### 4. Change the Input Graph

The benchmark uses `GRAPH_FILE` from the Makefile, which defaults to:

```text
graphs/reddit_numeric.edgelist
```

You can override it at runtime (it also applies to `make bv`, `make sq` and `make k2`):

```bash
make benchmark GRAPH_FILE=graphs/reddit_numeric.edgelist
```

The number of nodes and edges is taken from the file. The benchmark reports the size per edge and
the average time per query (100000 random queries per operation, fixed seed).

### 5. Recommended Workflow

1. Generate or refresh graph files (if needed):

```bash
python preprocess.py
```

2. Run all tests:

```bash
make test
```

3. Run the sequence analysis for parameter t

```bash
make testT
```

4. Generate the graphics for the secuence analysis

```bash
python plot.py appBenchmark/results/permutation_results.csv
```

5. Run benchmark:

```bash
make benchmark
```

### 6. Common Notes

- Use `make` for the default benchmark run.
- If you see stale behavior after code changes, run `make clean` and then re-run your target.