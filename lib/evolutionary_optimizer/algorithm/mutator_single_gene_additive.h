#ifndef EVOPTIMIZER_ALGORITHM_MUTATOR_ADDITIVE_H
#define EVOPTIMIZER_ALGORITHM_MUTATOR_ADDITIVE_H

#include <algorithm>

#include "mutator.h"

namespace Evo {
template <typename R, size_t genes_num, size_t population_size>
class SingleGeneAdditiveMutator
    : public Mutator<R, genes_num, population_size> {
  static Random::IntGenerator<size_t> mutation_point_gen;
  static Random::RealGenerator<R> mutation_value_gen;

 public:
  SingleGeneAdditiveMutator(double mutation_chance)
      : Mutator<R, genes_num, population_size>(mutation_chance) {}

  void mutate(RealIndividual<R, genes_num>& individual) const override {
    mutateAtPoint(individual, mutation_point_gen(), mutation_value_gen());
  }

  static void mutateAtPoint(RealIndividual<R, genes_num>& individual,
                            size_t mutation_point,
                            R mutation) {
    individual[mutation_point] =
        std::fmod(individual[mutation_point] + mutation, 1.0);
  }
};

// ============================================================

template <typename R, size_t genes_num, size_t population_size>
Random::IntGenerator<size_t>
    SingleGeneAdditiveMutator<R, genes_num, population_size>::
        mutation_point_gen(1, genes_num - 1);

template <typename R, size_t genes_num, size_t population_size>
Random::RealGenerator<R>
    SingleGeneAdditiveMutator<R, genes_num, population_size>::
        mutation_value_gen(-1.0, 1.0);

}  // namespace Evo

#endif  // EVOPTIMIZER_ALGORITHM_MUTATOR_ADDITIVE_H