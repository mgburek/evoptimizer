#ifndef EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_
#define EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_

#include <algorithm>

#include <generation.h>
#include <generators.h>

namespace Evoptimizer
{
    /**
     * Mutates at most one bit of each individual according to mutation chance
     */
    template <typename I, typename R, size_t genes_num, size_t population_size>
    class SingleBitMutator
    {
        static Random::IntGenerator<size_t> mutation_point_gen;

        const double _mutation_chance;

    public:
        SingleBitMutator(double mutation_chance)
            : _mutation_chance(mutation_chance) {}

        static void mutate(Individual<I, R, genes_num> &ind, size_t mutation_point)
        {
            auto mutated_gene_num = mutation_point / lengthInBits<I, 1>();

            auto mask = 0x1 << (lengthInBits<I, 1>() - mutation_point % lengthInBits<I, 1>() - 1);
            auto gene = ind.at(mutated_gene_num).get();
            ind[mutated_gene_num].set(gene ^ mask);
        }

        Generation<I, R, genes_num, population_size> operator()(const Generation<I, R, genes_num, population_size> &generation) const
        {
            Generation<I, R, genes_num, population_size> mutated(generation);

            auto mutate_lam = [this](Individual<I, R, genes_num> &individual)
            {
                if (Random::zero_one() < _mutation_chance)
                {
                    size_t mutation_point = mutation_point_gen();
                    mutate(individual, mutation_point);
                }
            };

            std::for_each(mutated.begin(), mutated.end(), mutate_lam);
            return mutated;
        }
    };

    // ============================================================

    template <typename I, typename R, size_t genes_num, size_t population_size>
    Random::IntGenerator<size_t>
        SingleBitMutator<I, R, genes_num, population_size>::mutation_point_gen(1, lengthInBits<I, genes_num>() - 1);

}

#endif