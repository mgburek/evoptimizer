#ifndef EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_
#define EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_

#include <algorithm>

#include <int_random_generator.h>
#include <random_generators.h>

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
class SingleBitMutator
{
    using GenerationType = Generation<Integral, Real, genes_num, population_size>;
    using IndividualType = Individual<Integral, Real, genes_num>;
    using GeneType = Gene<Integral, Real>;

    static IntRandomGenerator<size_t> mutation_point_gen;

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
            if (RandomGenerators::zero_one() < _mutation_chance)
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

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
IntRandomGenerator<size_t>
    SingleBitMutator<Integral, Real, genes_num, population_size>::
        mutation_point_gen(1, Individual<Integral, Real, genes_num>::bitsNum() - 1);

#endif