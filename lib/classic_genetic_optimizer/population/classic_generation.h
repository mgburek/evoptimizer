#ifndef EVOPTIMIZER_POPULATION_CLASSIC_GENERATION_H
#define EVOPTIMIZER_POPULATION_CLASSIC_GENERATION_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <sstream>
#include <string>

#include "classic_individual.h"

namespace Evo::Classic {
template <typename I, typename R, size_t genes_num, size_t population_size>
using Generation = std::array<Individual<I, R, genes_num>, population_size>;

template <typename I, typename R, size_t genes_num, size_t population_size>
Generation<I, R, genes_num, population_size> createRandom() {
  Generation<I, R, genes_num, population_size> generation;
  std::generate(generation.begin(), generation.end(),
                []() { return createRandom<I, R, genes_num>(); });
  return generation;
}

template <typename I, typename R, size_t genes_num, size_t population_size>
std::string toString(
    const Generation<I, R, genes_num, population_size>& generation) {
  std::ostringstream str_stream;
  for (const Individual<I, R, genes_num>& ind : generation)
    str_stream << toString(ind) << std::endl;

  return str_stream.str();
}
}  // namespace Evo::Classic

#endif  // EVOPTIMIZER_POPULATION_CLASSIC_GENERATION_H