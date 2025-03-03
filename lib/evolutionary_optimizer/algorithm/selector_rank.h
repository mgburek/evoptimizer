#ifndef EVOPTIMIZER_ALGORITHM_RANK_SELECTOR_H
#define EVOPTIMIZER_ALGORITHM_RANK_SELECTOR_H

#include <algorithm>
#include <array>
#include <numeric>

#include <generators.h>

#include "selector.h"

namespace Evo {
template <typename R, size_t genes_num, size_t population_size>
class RankSelector : public Selector<R, genes_num, population_size> {
 public:
  RankSelector() {}

  RealGeneration<R, genes_num, population_size> operator()(
      const RealGeneration<R, genes_num, population_size>& generation,
      const std::array<R, population_size>& fitness) const override {
    std::array<size_t, population_size> indices;
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(), [&fitness](size_t a, size_t b) {
      return fitness[a] > fitness[b];
    });

    // // sum of squares of ranks: 1^2 + 2^2 + ... + N^2
    // constexpr double ranks_sum =
    //     (population_size * (population_size + 1) * (2 * population_size + 1)) /
    //     6.0;

    // std::array<double, population_size> odds;
    // double rank = 0.0;
    // double prev_odd = 0.0;
    // std::generate(odds.begin(), odds.end(), [&rank, &prev_odd, ranks_sum]() {
    //   rank += 1.0;
    //   prev_odd = prev_odd + ((rank * rank) / ranks_sum);
    //   return prev_odd;
    // });

    // (N * (N+1)) / 2
    constexpr double ranks_sum =
        static_cast<double>(population_size * (population_size + 1)) * 0.5;

    std::array<double, population_size> odds;
    double rank = 0.0;
    double prev_odd = 0.0;
    std::generate(odds.begin(), odds.end(), [&rank, &prev_odd, &ranks_sum]() {
      rank += 1.0;
      prev_odd = prev_odd + (rank / ranks_sum);
      return prev_odd;
    });

    auto new_generation_generator = [&]() {
      double selection = Random::zero_one();
      auto it = std::lower_bound(odds.begin(), odds.end(), selection);
      int index = indices[std::distance(odds.begin(), it)];
      return generation[index];
    };

    RealGeneration<R, genes_num, population_size> new_generation;
    std::generate(new_generation.begin(), new_generation.end(),
                  new_generation_generator);

    return new_generation;
  }
};
}  // namespace Evo

#endif  // EVOPTIMIZER_ALGORITHM_RANK_SELECTOR_H