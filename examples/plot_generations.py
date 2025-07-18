import struct
import math
import sys

import numpy as np
import argparse

import plotly.graph_objects as go
from plotly.subplots import make_subplots

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Plot optimizer data")
    parser.add_argument("--data_file",
                        type=str,
                        help="Path of the file containing optimizer data to plot")
    args = parser.parse_args()

    if args.data_file is None:
        print("No data file provided")
        sys.exit(1)

    file_path = args.data_file

    iterations = dict()

    with open(file_path, "rb") as file:
        while True:

            data = file.read(4)
            if not data:
                break

            iteration_num = struct.unpack("I", data)[0]
            if iteration_num not in iterations:
                iterations[iteration_num] = dict()

            data = file.read(4)
            generation_num = struct.unpack("I", data)[0]

            data = file.read(4)
            population_size = struct.unpack("I", data)[0]

            data = file.read(4)
            genes_num = struct.unpack("I", data)[0]

            individuals = list()

            float_individual_size = struct.calcsize(f"{genes_num}f")
            for i in range(population_size):
                data = file.read(float_individual_size)
                individual_genes = list(struct.unpack(f"{genes_num}f", data))

                individuals.append(individual_genes)

            iterations[iteration_num][generation_num] = individuals



    iteration_to_plot = 1
    genertions_num = len(iterations[iteration_to_plot])

    for generation_to_plot in range(0,genertions_num, genertions_num//3):

        if generation_to_plot not in iterations[iteration_to_plot].keys():
            raise ValueError(f"Generation {generation_to_plot} not found.")

        individuals = iterations[iteration_to_plot][generation_to_plot]
        genes_num = len(individuals[0])
        population_size = len(individuals)

        cols = 3
        rows = math.ceil(genes_num / cols)

        fig = make_subplots(
            rows=rows,
            cols=cols,
            subplot_titles=[f"Gen {i}" for i in range(genes_num)]
        )

        for gene_index in range(genes_num):
            gene_values = [ind[gene_index] for ind in individuals]

            bin_width = 0.025
            bin_edges = np.arange(-1, 1 + bin_width, bin_width)  # statyczny zakres od -1 do 1
            bin_centers = (bin_edges[:-1] + bin_edges[1:]) / 2

            bin_indices = np.digitize(gene_values, bin_edges)
            counts = np.zeros(len(bin_edges) - 1, dtype=int)
            for bidx in bin_indices:
                if 1 <= bidx <= len(counts):
                    counts[bidx - 1] += 1

            row = gene_index // cols + 1
            col = gene_index % cols + 1

            fig.add_trace(
                go.Bar(x=bin_centers, y=counts, name=f"Gen {gene_index}"),
                row=row, col=col
            )
            fig.update_xaxes(range=[-1.1, 1.1], row=row, col=col)

        fig.update_layout(
            title_text=f"Generacja {generation_to_plot}"
        )

        fig.show()
