#ifndef EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H
#define EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H

#include <memory>

#include <fitness_evaluator.h>

#include "cross_breeder.h"
#include "mutator.h"
#include "selector.h"

namespace Evoptimizer {
template <typename I, typename R, size_t genes_num, size_t population_size>
class Evoptimizer {
  FitnessEvaluator<I, R, genes_num, population_size> _evaluator;
  std::unique_ptr<Selector<I, R, genes_num, population_size>> _selector;
  std::unique_ptr<CrossBreeder<I, R, genes_num, population_size>>
      _cross_breeder;
  std::unique_ptr<Mutator<I, R, genes_num, population_size>> _mutator;

 public:
  Evoptimizer(
      const FitnessEvaluator<I, R, genes_num, population_size>& evaluator,
      Selector<I, R, genes_num, population_size>* selector,
      CrossBreeder<I, R, genes_num, population_size>* cross_breeder,
      Mutator<I, R, genes_num, population_size>* mutator)
      : _evaluator{evaluator},
        _selector{selector},
        _cross_breeder{cross_breeder},
        _mutator{mutator} {}

  std::array<R, genes_num> operator()() const { return {}; }
};

}  // namespace Evoptimizer

#endif  // EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H