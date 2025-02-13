#ifndef EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H
#define EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H

#include <chrono>
#include <memory>

#include <optimizer.h>

#include "cross_breeder.h"
#include "fitness_evaluator.h"
#include "mutator.h"
#include "selector.h"

namespace Evo {
template <typename I, typename R, size_t genes_num, size_t population_size>
class Evoptimizer : public Optimizer<R, genes_num> {
  FitnessEvaluator<I, R, genes_num, population_size> _evaluator;
  std::unique_ptr<Selector<I, R, genes_num, population_size>> _selector;
  std::unique_ptr<CrossBreeder<I, R, genes_num, population_size>>
      _cross_breeder;
  std::unique_ptr<Mutator<I, R, genes_num, population_size>> _mutator;

 public:
  Evoptimizer(std::function<R(std::array<R, genes_num>)> fitness_function,
              Selector<I, R, genes_num, population_size>* selector,
              CrossBreeder<I, R, genes_num, population_size>* cross_breeder,
              Mutator<I, R, genes_num, population_size>* mutator)
      : _evaluator{FitnessEvaluator<I, R, genes_num, population_size>(
            fitness_function)},
        _selector{selector},
        _cross_breeder{cross_breeder},
        _mutator{mutator} {}

  std::array<R, genes_num> operator()(
      const size_t generations_num) const override {
    Generation<I, R, genes_num, population_size> gen0 =
        createRandom<I, R, genes_num, population_size>();

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
      const std::chrono::milliseconds timeout) const override {
    Generation<I, R, genes_num, population_size> gen0 =
        createRandom<I, R, genes_num, population_size>();

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
      if (!is_timeout())
        gen0 = (*_selector)(gen0, fitness);
      if (!is_timeout())
        gen0 = (*_cross_breeder)(gen0);
      if (!is_timeout())
        gen0 = (*_mutator)(gen0);

      auto final_fitness = _evaluator(gen0);
      auto min_it =
          std::min_element(final_fitness.begin(), final_fitness.end());
      auto min_idx = std::distance(final_fitness.begin(), min_it);
      if (*min_it < best_value) {
        best = gen0[min_idx];
        best_value = *min_it;
      }
    }
    std::cout << "Generatios prcoessed: " << g << "\n";

    return toReal(best);
  }
};
}  // namespace Evo

#endif  // EVOPTIMIZER_INCLUDES_EVOPTIMIZER_H