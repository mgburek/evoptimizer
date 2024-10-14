#pragma once

#include <functional>

#include "individual.h"

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
class FitnessEvaluator
{
    using IndividualType = Individual<Integral, Real, genes_num>;
    std::function<Real(IndividualType)> _goal_function;

public:
    FitnessEvaluator(std::function<Real(IndividualType)> goal_function)
        : _goal_function(goal_function)
    {
    }

    Real operator()(IndividualType individual) const
    {
        return _goal_function(individual);
    }

    std::array<Real, population_size> calculate(const std::array<IndividualType, population_size> &population)
    {
        std::array<Real, population_size> fitness;
        int idx = 0;
        std::generate(fitness.begin(), fitness.end(), [&]()
                      { return operator()(population[idx++]); });
        return fitness;
    }
};