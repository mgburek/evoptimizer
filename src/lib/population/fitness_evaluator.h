#pragma once

#include <functional>

#include "individual.h"
#include "generation.h"

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
class FitnessEvaluator
{
    using IndividualType = Individual<Integral, Real, genes_num>;
    using GenerationType = Generation<Integral, Real, genes_num, population_size>;
    
    std::function<Real(IndividualType)> _fitness_function;

public:
    FitnessEvaluator(std::function<Real(IndividualType)> fitness_function)
        : _fitness_function(fitness_function)
    {
    }

    /**
     * Invokes fitness function on single indivdual and returns Real fitness value
     */
    Real operator()(IndividualType individual) const
    {
        return _fitness_function(individual);
    }

    /**
     * Calculates fitness for all individuals and returns std::array of Real fitness values
     */
    std::array<Real, population_size> calculate(const GenerationType &population) const
    {
        std::array<Real, population_size> fitness;
        int idx = 0;
        std::generate(fitness.begin(), fitness.end(), [&]()
                      { return operator()(population[idx++]); });
        return fitness;
    }
};