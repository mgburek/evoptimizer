#pragma once

#include <functional>

#include "individual.h"

template <unsigned int genes_num, typename GeneType>
class FitnessEvaluator
{
    using Real = GeneType::RealType;
    using IndividualType = Individual<genes_num, GeneType>;

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
};