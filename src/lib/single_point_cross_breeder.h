#ifndef EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_
#define EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_

#include <array>
#include <algorithm>
#include <numeric>

#include <generators.h>

template <typename I, typename R, size_t genes_num, size_t population_size>
class SinglePointCrossBreeder
{
    using GenerationType = Generation<I, R, genes_num, population_size>;
    using IndividualType = Individual<I, R, genes_num>;

    static Random::IntGenerator<size_t> cross_point_gen;

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
            if (Random::zero_one() < _crossing_chance)
            {
                size_t cross_point = cross_point_gen();

                size_t division_gene = cross_point / (8 * sizeof(I));

                auto &genes_a = new_population.at(i).mutableGenes();
                auto &genes_b = new_population.at(i + 1).mutableGenes();

                if (division_gene > 0)
                    std::swap_ranges(genes_a.begin(), genes_a.begin() + division_gene, genes_b.begin());

                I mask = (~0x0) << cross_point;
                I mask_inv = ~mask;

                auto division_gene_a = genes_a.at(division_gene).get();
                auto division_gene_b = genes_b.at(division_gene).get();

                I ab = (division_gene_a & mask_inv) | (division_gene_b & mask);
                I ba = (division_gene_a & mask) | (division_gene_b & mask_inv);

                genes_a.at(division_gene) = ab;
                genes_b.at(division_gene) = ba;
            }
        }
        return new_generation;
    }
};

// ============================================================

template <typename I, typename R, size_t genes_num, size_t population_size>
Random::IntGenerator<size_t>
    SinglePointCrossBreeder<I, R, genes_num, population_size>::
        cross_point_gen(1, Individual<I, R, genes_num>::bitsNum() - 1);

#endif