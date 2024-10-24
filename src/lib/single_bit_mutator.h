#ifndef EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_
#define EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_

#include <algorithm>

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

        Generation<I, R, genes_num, population_size> operator()(const Generation<I, R, genes_num, population_size> &generation) const
        {
            Generation<I, R, genes_num, population_size> mutated(generation);

            auto mutate = [this](Individual<I, R, genes_num> &individual)
            {
                if (Random::zero_one() < _mutation_chance)
                {
                    size_t mutation_point = mutation_point_gen();
                    auto mutated_gene_num = mutation_point / lengthInBits<I, 1>();

                    auto mask = 0x1 << (mutation_point % lengthInBits<I, 1>());
                    auto gene = individual[mutated_gene_num].get();
                    individual[mutated_gene_num].set(gene ^ mask);
                }
            };

            std::for_each(mutated.begin(), mutated.end(), mutate);
            return mutated;
        }
    };

    // ============================================================

    template <typename I, typename R, size_t genes_num, size_t population_size>
    Random::IntGenerator<size_t>
        SingleBitMutator<I, R, genes_num, population_size>::mutation_point_gen(1, lengthInBits<I, genes_num>() - 1);

}

#endif