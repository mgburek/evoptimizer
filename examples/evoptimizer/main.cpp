#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <locale>

#define ENABLE_SAVE_OPTIMIZER_OUTPUT
#define LOGGER_ENABLED
#include "mutator_all_genes_additive.h"

#include <logger.h>

#include <cross_breeder_single_point_mean.h>
#include <evoptimizer.h>
#include <mutator_all_genes_additive.h>
#include <selector_rank.h>

#define PI 3.1415926535

int main() {
  USE_LOGGER(Evo::StdLogger);

  using R = double;
  constexpr size_t generations_num = 150;
  constexpr size_t gnum = 20;
  constexpr size_t psize = 50;

  Evo::max<R> = 40.0;
  Evo::min<R> = -40.0;

  auto fit_hypersphercial = [](const std::array<R, gnum> &x) {
    R result = 0.0;
    std::for_each(x.begin(), x.end(), [&](const R &v) { result += v * v; });
    return result;
  };

  auto fit_ackley = [&gnum](const std::array<R, gnum> &x) {
    constexpr const R a = 20.0;
    constexpr const R b = 0.2;
    const R c = static_cast<R>(2.0 * PI);
    const R d = 1.0 / static_cast<R>(gnum);

    R squares_sum = 0.0;
    R cosinuses_sum = 0.0;
    std::for_each(x.begin(), x.end(), [&](const R &v) {
      squares_sum += v * v;
      cosinuses_sum += std::cos(c * v);
    });
    return -a * std::exp(-b * std::sqrt(d * squares_sum)) -
           std::exp(d * cosinuses_sum) + a + exp(1);
  };

  auto start = std::chrono::steady_clock::now();

  std::unique_ptr<Evo::Optimizer<R, gnum>> evoptimizer =
      std::make_unique<Evo::Evoptimizer<R, gnum, psize>>(
          fit_hypersphercial, new Evo::RankSelector<R, gnum, psize>(),
          new Evo::SinglePointMeanCrossBreeder<R, gnum, psize>(0.5),
          new Evo::AllGeneAdditiveMutator<R, gnum, psize>(0.5, 0.5));

  auto result = (*evoptimizer)(std::chrono::milliseconds(20));
  // auto result = (*evoptimizer)(generations_num);

  LOG_INFO(fit_hypersphercial(result));
  LOG_INFO(Evo::toString(result));

  auto finish = std::chrono::steady_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
  LOG_INFO("Elapsed time: ", duration.count(), "us");
  return 0;
}
