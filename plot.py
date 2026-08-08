#!/usr/bin/env python3
"""
Grafica los resultados de permutation_results.csv:
  1) Construction Time y Access Time en función de t
  2) Inverse Time en función de t
  3) Tamaños (size, size per element) en función de t

Uso:
    python plot_permutation_results.py [ruta_al_csv] [--out-dir CARPETA] [--N N]

Si no se especifica ruta, busca "permutation_results.csv" en el directorio actual.
Si se especifica --N, se dibuja una línea vertical en x = log2(N) en cada gráfico.
"""

import argparse
import math
import sys
from pathlib import Path

import pandas as pd
import matplotlib.pyplot as plt


def add_log_line(ax, N: float, y_pos: str = "top"):
    """Dibuja una línea vertical punteada en x = log2(N), con etiqueta."""
    x_val = math.log2(N)
    ax.axvline(x_val, color="black", linestyle="--", linewidth=1.2, alpha=0.7)

    ylim = ax.get_ylim()
    y_text = ylim[1] * 0.97 if y_pos == "top" else ylim[0] + (ylim[1] - ylim[0]) * 0.03
    va = "top" if y_pos == "top" else "bottom"

    ax.text(
        x_val,
        y_text,
        f"  log2(N)={x_val:.2f}",
        rotation=90,
        va=va,
        ha="left",
        fontsize=8,
        color="black",
    )


def load_csv(path: Path) -> pd.DataFrame:
    # El archivo puede traer una primera línea del tipo "log2(E), 17"
    # (impresa por el programa en C++) antes del header real de la tabla.
    # Buscamos la línea que efectivamente empieza con "t," para usarla
    # como inicio real de los datos.
    with open(path, "r") as f:
        lines = f.readlines()

    header_idx = None
    for i, line in enumerate(lines):
        if line.strip().lower().startswith("t,"):
            header_idx = i
            break

    if header_idx is None:
        # No se encontró una línea de header que empiece con "t,";
        # se asume que el archivo ya empieza en el header.
        header_idx = 0

    # El CSV tiene ", " como separador (coma + espacio) y puede traer
    # una columna vacía al final por la coma final de cada línea.
    # index_col=False es crucial: como cada fila termina en coma, se genera
    # un campo extra sin nombre, y sin esto pandas asume que la primera
    # columna ("t") es el índice y desalinea todas las demás columnas.
    df = pd.read_csv(
        path,
        sep=r",\s*",
        engine="python",
        skiprows=header_idx,
        index_col=False,
    )

    # Limpiar nombres de columnas (espacios sobrantes)
    df.columns = [c.strip() for c in df.columns]

    # Eliminar columnas vacías (por la coma final en cada fila)
    df = df.loc[:, ~df.columns.str.match(r"^Unnamed")]

    # Asegurar tipos numéricos
    for col in df.columns:
        df[col] = pd.to_numeric(df[col], errors="coerce")

    df = df.dropna(how="all")
    df = df.dropna(subset=["t"]) if "t" in df.columns else df
    return df


def plot_times(df: pd.DataFrame, out_dir: Path, N: float = None):
    df = df.sort_values("t")
    fig, ax = plt.subplots(figsize=(8, 5))

    ax.plot(df["t"], df["Construction Time"], marker="o", label="Construction Time")
    ax.plot(df["t"], df["Access Time"], marker="o", label="Access Time")

    ax.set_xlabel("t")
    ax.set_ylabel("Tiempo (s)")
    ax.set_title("Tiempos vs t")
    ax.grid(True, linestyle="--", alpha=0.5)
    ax.set_xlim(df["t"].min(), df["t"].max())
    ax.xaxis.set_inverted(False)

    if N is not None and N > 0:
        add_log_line(ax, N)

    ax.legend()
    fig.tight_layout()
    out_path = out_dir / "times_vs_t.png"
    fig.savefig(out_path, dpi=150)
    print(f"Guardado: {out_path}")
    plt.close(fig)


def plot_inverse_time(df: pd.DataFrame, out_dir: Path, N: float = None):
    df = df.sort_values("t")
    fig, ax = plt.subplots(figsize=(8, 5))

    ax.plot(df["t"], df["Inverse Time"], marker="o", label="Inverse Time")

    ax.set_xlabel("t")
    ax.set_ylabel("Tiempo (s)")
    ax.set_title("Tiempos vs t")
    ax.grid(True, linestyle="--", alpha=0.5)
    ax.set_xlim(df["t"].min(), df["t"].max())
    ax.xaxis.set_inverted(False)

    if N is not None and N > 0:
        add_log_line(ax, N)

    ax.legend()
    fig.tight_layout()
    out_path = out_dir / "inverse_time_vs_t.png"
    fig.savefig(out_path, dpi=150)
    print(f"Guardado: {out_path}")
    plt.close(fig)


def plot_sizes(df: pd.DataFrame, out_dir: Path, N: float = None):
    df = df.sort_values("t")
    fig, ax1 = plt.subplots(figsize=(8, 5))

    color1 = "tab:blue"
    ax1.set_xlabel("t")
    ax1.set_ylabel("size (bytes)", color=color1)
    ax1.plot(df["t"], df["size"], marker="o", color=color1, label="size")
    ax1.tick_params(axis="y", labelcolor=color1)
    ax1.grid(True, linestyle="--", alpha=0.5)
    ax1.set_xlim(df["t"].min(), df["t"].max())
    ax1.xaxis.set_inverted(False)

    ax2 = ax1.twinx()
    color2 = "tab:red"
    ax2.set_ylabel("size per element (bytes)", color=color2)
    ax2.plot(df["t"], df["size per element"], marker="s", color=color2, label="size per element")
    ax2.tick_params(axis="y", labelcolor=color2)

    fig.suptitle("Tamaños vs t")

    if N is not None and N > 0:
        add_log_line(ax1, N)

    # Leyenda combinada de ambos ejes
    lines1, labels1 = ax1.get_legend_handles_labels()
    lines2, labels2 = ax2.get_legend_handles_labels()
    ax1.legend(lines1 + lines2, labels1 + labels2, loc="upper right")

    fig.tight_layout()
    out_path = out_dir / "sizes_vs_t.png"
    fig.savefig(out_path, dpi=150)
    print(f"Guardado: {out_path}")
    plt.close(fig)


def main():
    parser = argparse.ArgumentParser(description="Graficar permutation_results.csv")
    parser.add_argument(
        "csv_path",
        nargs="?",
        default="permutation_results.csv",
        help="Ruta al archivo CSV (default: permutation_results.csv)",
    )
    parser.add_argument(
        "--out-dir",
        default=".",
        help="Carpeta donde guardar los gráficos (default: directorio actual)",
    )
    parser.add_argument(
        "--N",
        type=float,
        default=None,
        help="Si se especifica, dibuja una línea vertical en x = log2(N) en cada gráfico",
    )
    args = parser.parse_args()

    csv_path = Path(args.csv_path)
    if not csv_path.exists():
        print(f"Error: no se encontró el archivo '{csv_path}'", file=sys.stderr)
        sys.exit(1)

    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    df = load_csv(csv_path)

    required_cols = {"t", "size", "size per element", "Construction Time", "Access Time", "Inverse Time"}
    missing = required_cols - set(df.columns)
    if missing:
        print(f"Error: faltan columnas en el CSV: {missing}", file=sys.stderr)
        print(f"Columnas encontradas: {list(df.columns)}", file=sys.stderr)
        sys.exit(1)

    plot_times(df, out_dir, N=args.N)
    plot_inverse_time(df, out_dir, N=args.N)
    plot_sizes(df, out_dir, N=args.N)


if __name__ == "__main__":
    main()