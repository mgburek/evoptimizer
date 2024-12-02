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
  constexpr size_t generations_num = 500;
  constexpr size_t gnum = 30;
  constexpr size_t psize = 5000;

  Evoptimizer::Gene<I, R>::max = 40.0;
  Evoptimizer::Gene<I, R>::min = -40.0;

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

  auto evaluator =
      Evoptimizer::FitnessEvaluator<I, R, gnum, psize>(fit_hypersphercial);
  auto selector = Evoptimizer::RankSelector<I, R, gnum, psize>();
  auto cross = Evoptimizer::SinglePointCrossBreeder<I, R, gnum, psize>(0.9);
  auto mutate = Evoptimizer::SingleBitMutator<I, R, gnum, psize>(0.4);

  auto evoptimizer = Evoptimizer::Evoptimizer<I, R, gnum, psize>(
      evaluator, new Evoptimizer::RankSelector<I, R, gnum, psize>(),
      new Evoptimizer::SinglePointCrossBreeder<I, R, gnum, psize>(0.9),
      new Evoptimizer::SingleBitMutator<I, R, gnum, psize>(0.4));

  auto gen0 = Evoptimizer::createRandom<I, R, gnum, psize>();

  auto start = std::chrono::steady_clock::now();

  for (size_t i = 0; i <= generations_num; ++i) {
    auto fitness = evaluator(gen0);

    if (i % (generations_num / 10) == 0) {
      auto min_v = std::min_element(fitness.begin(), fitness.end());
      std::cout << i << ": " << (min_v != fitness.end() ? *min_v : -1.0)
                << std::endl;
      std::cout << Evoptimizer::toString(gen0[0]) << std::endl;
      std::cout << std::endl;
    }

    auto selected = selector(gen0, fitness);
    auto crossed = cross(selected);
    gen0 = mutate(crossed);
  }

  auto finish = std::chrono::steady_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
  std::cout << "Elapsed time: " << duration.count() << "ms" << std::endl;
  return 0;
}
