#ifndef EVOPTIMIZER_POPULATION_FITNESS_EVALUATOR_H_
#define EVOPTIMIZER_POPULATION_FITNESS_EVALUATOR_H_

#include <functional>

#include "individual.h"
#include "generation.h"

namespace Evo
{
    template <typename I, typename R, size_t genes_num, size_t population_size>
    class FitnessEvaluator
    {
        std::function<R(std::array<R, genes_num>)> _fitness_function;

    public:
        FitnessEvaluator(std::function<R(const std::array<R, genes_num> &)> fitness_function)
            : _fitness_function(fitness_function)
        {
        }

        /**
         * Invokes fitness function on single indivdual and returns R fitness value
         */
        R evaluate(const Individual<I, R, genes_num> &individual) const
        {
            return _fitness_function(toReal(individual));
        }

        /**
         * Invokes fitness function on single indivdual and returns R fitness value
         */
        R operator()(const Individual<I, R, genes_num> &individual) const
        {
            return evaluate(individual);
        }

        /**
         * Calculates fitness for all individuals and returns std::array of R fitness values
         */
        std::array<R, population_size>
        operator()(const Generation<I, R, genes_num, population_size> &generation) const
        {
            std::array<R, population_size> fitness;
            for (size_t i = 0; i < population_size; ++i)
                fitness[i] = evaluate(generation[i]);

            return fitness;
        }
    };
}

#endif