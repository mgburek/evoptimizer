#ifndef EVOPTIMIZER_POPULATION_FITNESS_EVALUATOR_H_
#define EVOPTIMIZER_POPULATION_FITNESS_EVALUATOR_H_

#include <functional>

#include "individual.h"
#include "generation.h"

template <typename I, typename R, size_t genes_num, size_t population_size>
class FitnessEvaluator
{
    using IndividualType = Individual<I, R, genes_num>;
    using GenerationType = Generation<I, R, genes_num, population_size>;

    std::function<R(std::array<R, genes_num>)> _fitness_function;

public:
    FitnessEvaluator(std::function<R(std::array<R, genes_num>)> fitness_function)
        : _fitness_function(fitness_function)
    {
    }

    /**
     * Invokes fitness function on single indivdual and returns R fitness value
     */
    R evaluate(IndividualType individual) const
    {
        return _fitness_function(individual.realGenes());
    }

    /**
     * Invokes fitness function on single indivdual and returns R fitness value
     */
    R operator()(IndividualType individual) const
    {
        return evaluate(individual);
    }

    /**
     * Calculates fitness for all individuals and returns std::array of R fitness values
     */
    std::array<R, population_size> calculate(const GenerationType &generation) const
    {
        std::array<R, population_size> fitness;
        int idx = 0;
        std::generate(fitness.begin(), fitness.end(), [&]()
                      { return evaluate(generation.population().at(idx++)); });
        return fitness;
    }
};

#endif