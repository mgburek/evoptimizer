#ifndef EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_
#define EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_

#include <array>
#include <algorithm>
#include <numeric>

#include <int_random_generator.h>
#include <random_generators.h>

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
class SinglePointCrossBreeder
{
    using GenerationType = Generation<Integral, Real, genes_num, population_size>;
    using IndividualType = Individual<Integral, Real, genes_num>;

    static IntRandomGenerator<size_t> cross_point_gen;

    const double _crossing_chance;

public:
    SinglePointCrossBreeder(double crossing_chance)
        : _crossing_chance(crossing_chance) {}

    GenerationType operator()(const GenerationType &generation) const
    {
        GenerationType new_generation(generation);

        // TODO: Rethink random generators
        static std::random_device rd;
        static std::mt19937 g(rd());

        auto &new_population = new_generation.mutablePopulation();

        std::shuffle(new_population.begin(), new_population.end(), g);

        for (size_t i = 0; i < new_generation.population().size(); i += 2)
        {
            if (RandomGenerators::zero_one() < _crossing_chance)
            {
                size_t cross_point = cross_point_gen();

                size_t division_gene = cross_point / (8 * sizeof(Integral));

                auto &genes_a = new_population.at(i).mutableGenes();
                auto &genes_b = new_population.at(i + 1).mutableGenes();

                if (division_gene > 0)
                    std::swap_ranges(genes_a.begin(), genes_a.begin() + division_gene, genes_b.begin());

                Integral mask = (~0x0) << cross_point;
                Integral mask_inv = ~mask;

                auto division_gene_a = genes_a.at(division_gene).get();
                auto division_gene_b = genes_b.at(division_gene).get();

                Integral ab = (division_gene_a & mask_inv) | (division_gene_b & mask);
                Integral ba = (division_gene_a & mask) | (division_gene_b & mask_inv);

                genes_a.at(division_gene) = ab;
                genes_b.at(division_gene) = ba;
            }
        }
        return new_generation;
    }
};

// ============================================================

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
IntRandomGenerator<size_t>
    SinglePointCrossBreeder<Integral, Real, genes_num, population_size>::cross_point_gen(1, sizeof(Integral) * 8 * genes_num - 1);

#endif