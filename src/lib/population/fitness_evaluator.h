#ifndef EVOPTIMIZER_POPULATION_FITNESS_EVALUATOR_H_
#define EVOPTIMIZER_POPULATION_FITNESS_EVALUATOR_H_

#include <functional>

#include "individual.h"
#include "generation.h"

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
class FitnessEvaluator
{
    using IndividualType = Individual<Integral, Real, genes_num>;
    using GenerationType = Generation<Integral, Real, genes_num, population_size>;

    std::function<Real(std::array<Real, genes_num>)> _fitness_function;

public:
    FitnessEvaluator(std::function<Real(std::array<Real, genes_num>)> fitness_function)
        : _fitness_function(fitness_function)
    {
    }

    /**
     * Invokes fitness function on single indivdual and returns Real fitness value
     */
    Real evaluate(IndividualType individual) const
    {
        return _fitness_function(individual.realGenes());
    }

    /**
     * Invokes fitness function on single indivdual and returns Real fitness value
     */
    Real operator()(IndividualType individual) const
    {
        return evaluate(individual);
    }

    /**
     * Calculates fitness for all individuals and returns std::array of Real fitness values
     */
    std::array<Real, population_size> calculate(const GenerationType &generation) const
    {
        std::array<Real, population_size> fitness;
        int idx = 0;
        std::generate(fitness.begin(), fitness.end(), [&]()
                      { return evaluate(generation.population().at(idx++)); });
        return fitness;
    }
};

#endif