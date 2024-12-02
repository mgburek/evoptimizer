#ifndef EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H
#define EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H

#include <memory>
namespace Evoptimizer {

template <typename I, typename R, size_t genes_num, size_t population_size>
class Mutator;

template <typename I, typename R, size_t genes_num, size_t population_size>
class Evoptimizer {
  std::unique_ptr<Mutator<I, R, genes_num, population_size>> mutator;
};
}  // namespace Evoptimizer

#endif  // EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H