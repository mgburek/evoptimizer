#ifndef EVOPTIMIZER_POPULATION_CLASSIC_INDIVIDUAL_H
#define EVOPTIMIZER_POPULATION_CLASSIC_INDIVIDUAL_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <sstream>
#include <string>

#include "classic_gene.h"

namespace Evo::Classic {
template <typename I, typename R, size_t genes_num>
using Individual = std::array<Gene<I, R>, genes_num>;

template <typename I, typename R, size_t genes_num>
Individual<I, R, genes_num> createRandom() {
  Individual<I, R, genes_num> ind;
  std::generate(ind.begin(), ind.end(),
                []() { return Gene<I, R>::createRandom(); });
  return ind;
}

template <typename I, typename R, size_t genes_num>
std::string toString(const Individual<I, R, genes_num>& ind) {
  std::ostringstream str_stream;
  for (const Gene<I, R>& gene : ind)
    str_stream << gene.toString() << " ";

  return str_stream.str();
}

template <typename I, typename R, size_t genes_num>
std::array<R, genes_num> toReal(const Individual<I, R, genes_num>& ind) {
  std::array<R, genes_num> result;
  std::transform(ind.begin(), ind.end(), result.begin(),
                 [](const Gene<I, R>& gene) { return gene.toReal(); });
  return result;
}

template <typename I, size_t genes_num>
static constexpr size_t lengthInBits() {
  return sizeof(I) * 8 * genes_num;
}
}  // namespace Evo::Classic

#endif  // EVOPTIMIZER_POPULATION_CLASSIC_INDIVIDUAL_H