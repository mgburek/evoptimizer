#ifndef EVOPTIMIZER_EVOLUTIONARY_OPTIMIZER_GENERATION_H
#define EVOPTIMIZER_EVOLUTIONARY_OPTIMIZER_GENERATION_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <sstream>
#include <string>

#include "individual.h"

namespace Evo {
template <typename R, size_t genes_num, size_t population_size>
using RealGeneration = std::array<RealIndividual<R, genes_num>, population_size>;

template <typename R, size_t genes_num, size_t population_size>
RealGeneration<R, genes_num, population_size> createRandomGeneration() {
  RealGeneration<R, genes_num, population_size> generation;
  std::generate(generation.begin(), generation.end(),
                []() { return createRandomIndividual<R, genes_num>(); });
  return generation;
}

template <typename R, size_t genes_num, size_t population_size>
std::string toString(
    const RealGeneration<R, genes_num, population_size>& generation) {
  std::ostringstream str_stream;
  for (const RealIndividual<R, genes_num>& ind : generation)
    str_stream << toString(ind) << std::endl;

  return str_stream.str();
}
}  // namespace Evo

#endif  // EVOPTIMIZER_EVOLUTIONARY_OPTIMIZER_GENERATION_H