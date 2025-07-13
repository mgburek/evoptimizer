#ifndef EVOPTIMIZER_EVOLUTIONARY_OPTIMIZER_INDIVIDUAL_H
#define EVOPTIMIZER_EVOLUTIONARY_OPTIMIZER_INDIVIDUAL_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <sstream>
#include <string>

#include <generators.h>

namespace Evo {

template <typename R>
inline static R max = static_cast<R>(1.0);

template <typename R>
inline static R min = static_cast<R>(-1.0);

template <typename R, size_t genes_num>
using RealIndividual = std::array<R, genes_num>;

template <typename R, size_t genes_num>
RealIndividual<R, genes_num> createRandomIndividual() {
  RealIndividual<R, genes_num> ind;
  auto generator = Random::RealGenerator(min<R>, max<R>);
  std::generate(ind.begin(), ind.end(), [&generator]() { return generator(); });
  return ind;
}

template <typename R, size_t genes_num>
std::string toString(const RealIndividual<R, genes_num>& ind) {
  std::ostringstream str_stream;
  for (const R& gene : ind)
    str_stream << gene << " ";

  return str_stream.str();
}
}  // namespace Evo

#endif  // EVOPTIMIZER_EVOLUTIONARY_OPTIMIZER_INDIVIDUAL_H