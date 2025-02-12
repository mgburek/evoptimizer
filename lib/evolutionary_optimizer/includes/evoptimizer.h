#ifndef EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H
#define EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H

#include <chrono>
#include <memory>

#include "fitness_evaluator.h"

#include "cross_breeder.h"
#include "mutator.h"
#include "selector.h"

namespace Evo {
template <typename R, size_t genes_num, size_t population_size>
class Evoptimizer {
  FitnessEvaluator<R, genes_num, population_size> _evaluator;
  std::unique_ptr<Selector<R, genes_num, population_size>> _selector;
  std::unique_ptr<CrossBreeder<R, genes_num, population_size>> _cross_breeder;
  std::unique_ptr<Mutator<R, genes_num, population_size>> _mutator;

 public:
  Evoptimizer(std::function<R(std::array<R, genes_num>)> fitness_function,
              Selector<R, genes_num, population_size>* selector,
              CrossBreeder<R, genes_num, population_size>* cross_breeder,
              Mutator<R, genes_num, population_size>* mutator)
      : _evaluator{FitnessEvaluator<R, genes_num, population_size>(
            fitness_function)},
        _selector{selector},
        _cross_breeder{cross_breeder},
        _mutator{mutator} {}

  std::array<R, genes_num> operator()(const size_t generations_num) const {
    RealGeneration<R, genes_num, population_size> gen0 =
        createRandomGeneration<R, genes_num, population_size>();

    for (size_t i = 0; i <= generations_num; ++i) {
      auto fitness = _evaluator(gen0);
      auto selected = (*_selector)(gen0, fitness);
      auto crossed = (*_cross_breeder)(selected);
      gen0 = (*_mutator)(crossed);
    }

    auto final_fitness = _evaluator(gen0);
    auto min_it = std::min_element(final_fitness.begin(), final_fitness.end());
    auto min_idx = std::distance(final_fitness.begin(), min_it);
    return toReal(gen0[min_idx]);
  }

  std::array<R, genes_num> operator()(
      const std::chrono::milliseconds timeout) const {
    RealGeneration<R, genes_num, population_size> gen0 =
        createRandomGeneration<R, genes_num, population_size>();

    const auto start = std::chrono::steady_clock::now();

    auto is_timeout = [&start, &timeout]() {
      const auto now = std::chrono::steady_clock::now();
      return (now - start) > timeout;
    };

    auto best = gen0[0];
    auto best_value = _evaluator.evaluate(best);

    int g = 0;
    while (!is_timeout()) {
      g++;
      auto fitness = _evaluator(gen0);
      if (is_timeout())
        break;
      auto selected = (*_selector)(gen0, fitness);
      if (is_timeout())
        break;
      auto crossed = (*_cross_breeder)(selected);
      if (is_timeout())
        break;
      gen0 = (*_mutator)(crossed);

      auto final_fitness = _evaluator(gen0);
      auto min_it =
          std::min_element(final_fitness.begin(), final_fitness.end());
      auto min_idx = std::distance(final_fitness.begin(), min_it);
      if (*min_it < best_value) {
        best = gen0[min_idx];
        best_value = *min_it;
      }
      std::cout << best_value << "\n";
    }
    std::cout << "Generatios prcoessed: " << g << "\n";

    return best;
  }
};
}  // namespace Evo

#endif  // EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H