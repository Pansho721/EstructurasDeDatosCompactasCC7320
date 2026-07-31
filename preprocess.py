import collections
import csv
import sys
import os

def tsv2file(input, output, sep='\t', head=10, cols=None, count=False):
    os.makedirs(os.path.dirname(output), exist_ok=True) if os.path.dirname(output) else None
    with open(input, newline='', encoding='utf-8') as f:
        with open(output, "w", newline="", encoding="utf-8") as out_f:
            writer = csv.writer(out_f, delimiter='\t')
            # try to sniff delimiter if sep is 'auto'
            if sep == 'auto':
                sample = f.read(4096)
                f.seek(0)
                try:
                    dialect = csv.Sniffer().sniff(sample, delimiters='\t,; ')
                    sep_used = dialect.delimiter
                except Exception:
                    sep_used = '\t'
            else:
                sep_used = sep

            reader = csv.reader(f, delimiter=sep_used)
            try:
                header = next(reader)
            except StopIteration:
                print("empty file", file=sys.stderr)
                return

            if cols:
                idxs = []
                for c in cols:
                    try:
                        idxs.append(header.index(c))
                    except ValueError:
                        print(f"column not found: {c}", file=sys.stderr)
                        return
            else:
                idxs = None

            print("Delimiter:", repr(sep_used))
            print("Header:", header if not idxs else [header[i] for i in idxs])

            total = 0
            out_rows = []
            
            # if head==0, process all data rows and count
            for row in reader:
                total += 1
                if idxs:
                    row = [row[i] if i < len(row) else '' for i in idxs]
                if len(row) >= 2:
                        src = row[0].strip()
                        dst = row[1].strip()
                        w = row[2].strip() if len(row) >= 3 else ''
                        if src and dst and w:
                            out_rows.append([src, dst, w])
                        elif src and dst:
                            out_rows.append([src, dst])

            # Sort output rows deterministically by source, target, and optional weight.
            out_rows.sort(key=lambda r: (r[0], r[1], r[2] if len(r) >= 3 else ''))
            writer.writerows(out_rows)

            if count:
                print("Total rows (excluding header):", total)


def directedWeightedGraphFile(input_path, output_path="graphs/graph.edgelist", sep='\t'):
    tsv2file(
        input_path,
        output=output_path,
        sep=sep,
        head=0,
        cols=("SOURCE_SUBREDDIT", "TARGET_SUBREDDIT", "LINK_SENTIMENT"),
        count=True,
    )


def map_reduce_count_edges(input_path, output_path="aggregated.edgelist", sep='\t', use_external_sort=True):
    counter = collections.Counter()
    with open(input_path, 'r', encoding='utf-8') as file:
        for line in file:
            line = line.rstrip('\n')
            if not line:
                continue
            parts = line.split(sep)
            if len(parts) >= 3:
                src, dst, sent = parts[0].strip(), parts[1].strip(), parts[2].strip()
            elif len(parts) == 2:
                src, dst, sent = parts[0].strip(), parts[1].strip(), 0
            else:
                continue
            counter[(src, dst)] += 1

    with open(output_path, 'w', newline='', encoding='utf-8') as outf:
        writer = csv.writer(outf, delimiter=sep)
        for (src, dst), cnt in sorted(counter.items(), key=lambda item: (item[0][0], item[0][1])):
            writer.writerow([src, dst, cnt])

    return output_path


def relabel_edgelist_to_numeric(
    input_path,
    output_path="graphs/reddit_numeric.edgelist",
    mapping_path="graphs/reddit_node_mapping.tsv",
    sep='\t',
):
    node_to_id = {}
    next_id = 0
    output_rows = []

    def get_id(node):
        nonlocal next_id
        if node not in node_to_id:
            node_to_id[node] = next_id
            next_id += 1
        return node_to_id[node]

    with open(input_path, 'r', encoding='utf-8') as infile:
        for line in infile:
            line = line.rstrip('\n')
            if not line:
                continue
            parts = line.split(sep)
            if len(parts) < 2:
                continue

            src = parts[0].strip()
            dst = parts[1].strip()
            if not src or not dst:
                continue

            src_id = get_id(src)
            dst_id = get_id(dst)

            if len(parts) >= 3:
                output_rows.append([src_id, dst_id, parts[2].strip()])
            else:
                output_rows.append([src_id, dst_id])

    output_rows.sort(key=lambda row: (row[0], row[1], row[2] if len(row) >= 3 else ''))

    with open(output_path, 'w', newline='', encoding='utf-8') as outf:
        writer = csv.writer(outf, delimiter=sep)
        writer.writerows(output_rows)

    with open(mapping_path, 'w', newline='', encoding='utf-8') as mapf:
        writer = csv.writer(mapf, delimiter=sep)
        for node, node_id in sorted(node_to_id.items(), key=lambda x: x[1]):
            writer.writerow([node, node_id])

    return output_path, mapping_path

if __name__ == "__main__":
    input_file = "soc-redditHyperlinks-body.tsv"
    weight_file = "graphs/reddit_weighted.edgelist"
    aggregated_file = "graphs/reddit_weighted_aggregated.edgelist"
    numeric_file = "graphs/reddit_numeric.edgelist"
    mapping_file = "graphs/reddit_node_mapping.tsv"

    directedWeightedGraphFile(input_file, weight_file)
    map_reduce_count_edges(weight_file, aggregated_file, sep='\t')
    relabel_edgelist_to_numeric(aggregated_file, numeric_file, mapping_file, sep='\t')