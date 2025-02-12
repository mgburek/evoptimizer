#ifndef EVOPTIMIZER_ALGORITHM_SELECTOR_H
#define EVOPTIMIZER_ALGORITHM_SELECTOR_H

#include <algorithm>

#include <generation.h>
#include <generators.h>

namespace Evo {
template <typename R, size_t genes_num, size_t population_size>
class Selector {
 public:
  virtual ~Selector() = default;

  virtual RealGeneration<R, genes_num, population_size> operator()(
      const RealGeneration<R, genes_num, population_size>& generation,
      const std::array<R, population_size>& fitness) const = 0;
};
}  // namespace Evo

#endif  // EVOPTIMIZER_ALGORITHM_SELECTOR_H