# EstructurasDeDatosCompactasCC7320
Compact analysis for a Reddit hyperlinks graph.

## Architecture

![Architecture](Architecture.png)

## Compile

g++ app/benchmark.cpp app/graph.cpp app/graphBitVector.cpp -o app/benchmark_bin

## Run

./app/benchmark_bin graphs/reddit_weighted_aggregated_numeric.edgelist