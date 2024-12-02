#ifndef EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H
#define EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H

#include <memory>

#include "mutator.h"
#include "cross_breeder.h"

namespace Evoptimizer {
template <typename I, typename R, size_t genes_num, size_t population_size>
class Evoptimizer {
  std::unique_ptr<CrossBreeder<I, R, genes_num, population_size>> cross_breeder;
  std::unique_ptr<Mutator<I, R, genes_num, population_size>> mutator;
};
}  // namespace Evoptimizer

#endif  // EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H