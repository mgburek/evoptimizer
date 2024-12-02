#include <iostream>
#include <locale>

#include <evoptimizer.h>
#include <fitness_evaluator.h>
#include <gene.h>
#include <generation.h>
#include <global_engine.h>
#include <individual.h>
#include <rank_selector.h>
#include <single_bit_mutator.h>
#include <single_point_cross_breeder.h>

#include <chrono>
#include <fstream>

#define PI 3.1415926535

int main() {
  using I = uint16_t;
  using R = double;
  constexpr size_t generations_num = 50;
  constexpr size_t gnum = 10;
  constexpr size_t psize = 500;

  Evo::Gene<I, R>::max = 40.0;
  Evo::Gene<I, R>::min = -40.0;

  auto fit_hypersphercial = [](const std::array<R, gnum>& x) {
    R result = 0.0;
    std::for_each(x.begin(), x.end(), [&](const R& v) { result += v * v; });
    return result;
  };

  auto fit_ackley = [](const std::array<R, gnum>& x) {
    constexpr const R a = 20.0;
    constexpr const R b = 0.2;
    const R c = static_cast<R>(2.0 * PI);
    constexpr const R d = 1.0 / static_cast<R>(gnum);

    R squares_sum = 0.0;
    R cosinuses_sum = 0.0;
    std::for_each(x.begin(), x.end(), [&](const R& v) {
      squares_sum += v * v;
      cosinuses_sum += std::cos(c * v);
    });
    return -a * std::exp(-b * std::sqrt(d * squares_sum)) -
           std::exp(d * cosinuses_sum) + a + exp(1);
  };

  auto start = std::chrono::steady_clock::now();

  auto evoptimizer = Evo::Evoptimizer<I, R, gnum, psize>(
      fit_hypersphercial, new Evo::RankSelector<I, R, gnum, psize>(),
      new Evo::SinglePointCrossBreeder<I, R, gnum, psize>(0.9),
      new Evo::SingleBitMutator<I, R, gnum, psize>(0.4));

  auto result = evoptimizer(generations_num);
  std::cout << result.at(0) << std::endl;

  auto finish = std::chrono::steady_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
  std::cout << "Elapsed time: " << duration.count() << "ms" << std::endl;
  return 0;
}
