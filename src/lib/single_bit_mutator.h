#ifndef EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_
#define EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_

#include <algorithm>

#include <generators.h>

/**
 * Mutates at most one bit of each individual according to mutation chance
 */
template <typename I, typename R, size_t genes_num, size_t population_size>
class SingleBitMutator
{
    using GenerationType = Generation<I, R, genes_num, population_size>;
    using IndividualType = Individual<I, R, genes_num>;
    using GeneType = Gene<I, R>;

    static Random::IntGenerator<size_t> mutation_point_gen;

    const double _mutation_chance;

public:
    SingleBitMutator(double mutation_chance)
        : _mutation_chance(mutation_chance) {}

    GenerationType operator()(const GenerationType &generation) const
    {
        GenerationType new_generation(generation);
        auto &new_population = new_generation.mutablePopulation();

        auto mutate = [this](IndividualType &individual)
        {
            if (Random::zero_one() < _mutation_chance)
            {
                auto &genes = individual.mutableGenes();
                size_t mutation_point = mutation_point_gen();
                auto mutated_gene_num = mutation_point / GeneType::bitsNum();

                auto mask = 0x1 << (mutation_point % GeneType::bitsNum());
                auto gene_v = genes[mutated_gene_num].get();
                genes[mutated_gene_num].set(gene_v ^ mask);
            }
        };

        std::for_each(new_population.begin(), new_population.end(), mutate);

        return new_generation;
    }
};

// ============================================================

template <typename I, typename R, size_t genes_num, size_t population_size>
Random::IntGenerator<size_t>
    SingleBitMutator<I, R, genes_num, population_size>::
        mutation_point_gen(1, Individual<I, R, genes_num>::bitsNum() - 1);

#endif