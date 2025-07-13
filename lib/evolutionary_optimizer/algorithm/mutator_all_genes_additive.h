//
// Created by mateusz on 7/13/25.
//

#ifndef MUTATOR_ALL_GENES_ADDITIVE_H
#define MUTATOR_ALL_GENES_ADDITIVE_H

#include <algorithm>

#include "mutator.h"

namespace Evo {
    template<typename R, size_t genes_num, size_t population_size>
    class AllGeneAdditiveMutator final
            : public Mutator<R, genes_num, population_size> {
        static Random::RealGenerator<R> mutation_value_gen;

        const double _mutation_scale;

    public:
        AllGeneAdditiveMutator(double mutation_chance, R max_abs_mutation)
            : Mutator<R, genes_num, population_size>(mutation_chance),
              _mutation_scale{max_abs_mutation} {
        }

        void mutate(RealIndividual<R, genes_num> &individual) const override {
            for (size_t g = 0; g < genes_num; g++) {
                mutateAtPoint(individual, g,
                              _mutation_scale * mutation_value_gen());
            }
        }

        static void mutateAtPoint(RealIndividual<R, genes_num> &individual,
                                  size_t mutation_point, R mutation) {
            R range = max<R> - min<R>;
            R val = individual[mutation_point] + mutation - min<R>;
            val = std::fmod(val, range);
            if (val < 0)
                val += range;
            individual.at(mutation_point) = val + min<R>;
        }
    };

    // ============================================================

    template<typename R, size_t genes_num, size_t population_size>
    Random::RealGenerator<R>
    AllGeneAdditiveMutator<R, genes_num,
        population_size>::mutation_value_gen(-1.0, 1.0);
} // namespace Evo


#endif //MUTATOR_ALL_GENES_ADDITIVE_H
