#include <chrono>
#include <fstream>
#include <iostream>
#include <locale>

#include <classic_evoptimizer.h>
#include <classic_rank_selector.h>
#include <classic_single_bit_mutator.h>
#include <classic_single_point_cross_breeder.h>
#include <global_engine.h>

#define PI 3.1415926535

int main() {
  using I = uint32_t;
  using R = double;
  constexpr size_t generations_num = 150;
  constexpr size_t gnum = 20;
  constexpr size_t psize = 50;

  Evo::Classic::Gene<I, R>::max = 40.0;
  Evo::Classic::Gene<I, R>::min = -40.0;

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

  std::unique_ptr<Evo::Optimizer<R, gnum>> evoptimizer =
      std::make_unique<Evo::Classic::Evoptimizer<I, R, gnum, psize>>(
          fit_hypersphercial,
          new Evo::Classic::RankSelector<I, R, gnum, psize>(),
          new Evo::Classic::SinglePointCrossBreeder<I, R, gnum, psize>(0.5),
          new Evo::Classic::SingleBitMutator<I, R, gnum, psize>(0.5));

  auto result = (*evoptimizer)(std::chrono::milliseconds(20));
  // auto result = (*evoptimizer)(generations_num);

  std::cout << fit_hypersphercial(result) << std::endl;

  auto finish = std::chrono::steady_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
  std::cout << "Elapsed time: " << duration.count() << "us" << std::endl;
  return 0;
}
