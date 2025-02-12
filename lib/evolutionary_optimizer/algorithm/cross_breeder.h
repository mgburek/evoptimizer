#ifndef EVOPTIMIZER_ALGORITHM_CROSS_BREEDER_H
#define EVOPTIMIZER_ALGORITHM_CROSS_BREEDER_H

#include <algorithm>

#include <generation.h>
#include <generators.h>

namespace Evo {
template <typename R, size_t genes_num, size_t population_size>
class CrossBreeder {
  const double _crossing_chance;

 public:
  CrossBreeder(const double crossing_chance)
      : _crossing_chance{crossing_chance} {}

  virtual ~CrossBreeder() = default;

  virtual void cross(RealIndividual<R, genes_num>& ind1,
                     RealIndividual<R, genes_num>& ind2) const = 0;

  RealGeneration<R, genes_num, population_size> operator()(
      const RealGeneration<R, genes_num, population_size>& generation) const {
    RealGeneration<R, genes_num, population_size> crossed_generation(
        generation);
    std::shuffle(crossed_generation.begin(), crossed_generation.end(),
                 Random::engine);

    for (size_t i = 0; i < crossed_generation.size(); i += 2) {
      if (Random::zero_one() < _crossing_chance)
        cross(crossed_generation.at(i), crossed_generation.at(i + 1));
    }
    return crossed_generation;
  }
};
}  // namespace Evo

#endif  // EVOPTIMIZER_ALGORITHM_CROSS_BREEDER_H