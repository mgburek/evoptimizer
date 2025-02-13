#ifndef EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_
#define EVOPTIMIZER_SINGLE_BIT_MUTATOR_H_

#include <algorithm>

#include "mutator.h"

namespace Evo {
/**
 * Mutates at most one bit of each individual according to mutation chance
 */
template <typename I, typename R, size_t genes_num, size_t population_size>
class SingleBitMutator : public Mutator<I, R, genes_num, population_size> {
  static Random::IntGenerator<size_t> mutation_point_gen;

 public:
  SingleBitMutator(double mutation_chance)
      : Mutator<I, R, genes_num, population_size>(mutation_chance) {}

  void mutate(Individual<I, R, genes_num>& individual) const override {
    size_t mutation_point = mutation_point_gen();
    mutateAtPoint(individual, mutation_point);
  }

  static void mutateAtPoint(Individual<I, R, genes_num>& individual,
                            size_t mutation_point) {
    auto mutated_gene_num = mutation_point / lengthInBits<I, 1>();

    auto mask = 0x1 << (lengthInBits<I, 1>() -
                        mutation_point % lengthInBits<I, 1>() - 1);
    auto gene = individual.at(mutated_gene_num).get();
    individual[mutated_gene_num].set(gene ^ mask);
  }
};

// ============================================================

template <typename I, typename R, size_t genes_num, size_t population_size>
Random::IntGenerator<size_t>
    SingleBitMutator<I, R, genes_num, population_size>::mutation_point_gen(
        1,
        lengthInBits<I, genes_num>() - 1);

}  // namespace Evo

#endif