#ifndef EVOPTIMIZER_INCLUDES_MUTATOR_H
#define EVOPTIMIZER_INCLUDES_MUTATOR_H

#include <algorithm>

#include <generation.h>
#include <generators.h>

namespace Evoptimizer {
template <typename I, typename R, size_t genes_num, size_t population_size>
class Mutator {
  const double _mutation_chance;

 public:
  Mutator(const double mutation_chance) : _mutation_chance{mutation_chance} {};
  virtual ~Mutator() = default;

  virtual void mutate(Individual<I, R, genes_num>& individual) const = 0;

  Generation<I, R, genes_num, population_size> operator()(
      const Generation<I, R, genes_num, population_size>& generation) const {
    Generation<I, R, genes_num, population_size> mutated(generation);

    auto mut = [this](Individual<I, R, genes_num>& individual) {
      if (Random::zero_one() < this->_mutation_chance) {
        mutate(individual);
      }
    };

    std::for_each(mutated.begin(), mutated.end(), mut);
    return mutated;
  }
};
}  // namespace Evoptimizer
#endif  // EVOPTIMIZER_INCLUDES_MUTATOR_H