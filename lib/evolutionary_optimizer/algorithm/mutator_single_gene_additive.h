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

  const double _mutation_scale;

 public:
  SingleGeneAdditiveMutator(double mutation_chance, R max_abs_mutation)
      : Mutator<R, genes_num, population_size>(mutation_chance),
        _mutation_scale{max_abs_mutation} {}

  void mutate(RealIndividual<R, genes_num>& individual) const override {
    mutateAtPoint(individual, mutation_point_gen(),
                  _mutation_scale * mutation_value_gen());
  }

  static void mutateAtPoint(RealIndividual<R, genes_num>& individual,
                            size_t mutation_point,
                            R mutation) {
    individual.at(mutation_point) =
        std::fmod(individual[mutation_point] + mutation, max<R>);
  }
};

// ============================================================

template <typename R, size_t genes_num, size_t population_size>
Random::IntGenerator<size_t>
    SingleGeneAdditiveMutator<R, genes_num, population_size>::
        mutation_point_gen(0, genes_num - 1);

template <typename R, size_t genes_num, size_t population_size>
Random::RealGenerator<R>
    SingleGeneAdditiveMutator<R, genes_num, population_size>::
        mutation_value_gen(-1.0, 1.0);

}  // namespace Evo

#endif  // EVOPTIMIZER_ALGORITHM_MUTATOR_ADDITIVE_H