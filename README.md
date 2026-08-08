# EstructurasDeDatosCompactasCC7320
Compact analysis for a Reddit hyperlinks graph.

## Architecture

![Architecture](Architecture.png)

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
make bv
make pm
make sq
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

You can override it at runtime:

```bash
make benchmark GRAPH_FILE=graphs/reddit_numeric.edgelist
```

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