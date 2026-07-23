import matplotlib.pyplot as plt
import networkx as nx
import pandas as pd
import numpy as np
import powerlaw
import glob
import sys
import os

LOG = []

def edgelist2graph(edgelist_path):
    # Input format is: source<TAB>target<TAB>weight
    G = nx.read_weighted_edgelist(edgelist_path, delimiter='\t', nodetype=int)
    return G


def plot_centrality_distributions(filepath):



    title = f"Reddit | Distribución de frecuencia: degree centrality"
    outdir = f"Hist/degree"
    os.makedirs(outdir, exist_ok=True)

    print(f"Constructing dot diagram...")
    df = pd.read_csv(filepath, sep='\t', names=['node', 'value'])
    values = df['value']
    counts = values.value_counts().sort_index()
    total = counts.sum()

    plt.figure()
    plt.scatter(counts.index, counts.values / total, s=3, color='black')
    plt.xscale('log')
    plt.yscale('log')
    plt.title(title)
    plt.xlabel("Degree centrality")
    plt.ylabel("Frecuencia")

    values_array = np.array(values)
    fit = powerlaw.Fit(values_array, verbose=False)
    gamma = fit.alpha
    xmin = fit.xmin

    LOG.append({"graph": "Reddit", "gamma": gamma, "xmin": xmin})

    if np.isfinite(gamma) and np.isfinite(xmin):
        x_fit = counts.index[counts.index >= xmin].to_numpy(dtype=float)
        if x_fit.size:
            observed_tail = (counts.loc[x_fit] / total).to_numpy(dtype=float)
            y_fit = observed_tail[0] * np.power(x_fit / x_fit[0], -gamma)
            valid = y_fit >= observed_tail.min()

            if np.count_nonzero(valid) >= 2:
                plt.plot(x_fit[valid], y_fit[valid], 'r--', linewidth=2, label=f'Power law (γ={gamma:.2f})')
                plt.legend()

    plt.savefig(f"{outdir}/reddit-degree.png")
    plt.close()

    for l in LOG:
        print(f"[{l['graph']}] gamma: {l['gamma']:.6f}, xmin: {l['xmin']:.6f}")





if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 centrality.py <path_to_weighted_edgelist>")
        sys.exit(1)

    edgelist_path = sys.argv[1]
    G = edgelist2graph(edgelist_path)
    print(f"Graph has {G.number_of_nodes()} nodes and {G.number_of_edges()} edges.")

    C = nx.average_clustering(G)
    L = nx.average_shortest_path_length(G)
    print(f"Average clustering coefficient: {C}")
    print(f"Average shortest path length: {L}")

    degree_centrality = nx.degree_centrality(G)
    centrality_file = "centrality/degree_centrality.tsv"
    os.makedirs(os.path.dirname(centrality_file), exist_ok=True)
    with open(centrality_file, 'w', newline='', encoding='utf-8') as f:
        for node, centrality in degree_centrality.items():
            f.write(f"{node}\t{centrality}\n")


    plot_centrality_distributions(centrality_file)
