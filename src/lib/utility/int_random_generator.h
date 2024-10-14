#ifndef EVOPTIMIZER_INT_RANDOM_GENERATOR_H_
#define EVOPTIMIZER_INT_RANDOM_GENERATOR_H_

#include <random>

template <typename Integral>
class IntRandomGenerator
{
    static_assert(std::is_integral_v<Integral>,
                  "Integral type must be an integral type");

    std::random_device _rd;
    std::mt19937 _engine;
    std::uniform_int_distribution<Integral> _distribution;

public:
    IntRandomGenerator(Integral min, Integral max);
    double operator()();
};

template <typename Integral>
IntRandomGenerator<Integral>::IntRandomGenerator(Integral min, Integral max)
    : _rd(), _engine(_rd()), _distribution(min, max)
{
}

template <typename Real>
double IntRandomGenerator<Real>::operator()()
{
    return _distribution(_engine);
}

#endif