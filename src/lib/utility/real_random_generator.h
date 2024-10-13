#pragma once

#include <random>

template <typename Real>
class RealRandomGenerator
{
    static_assert(std::is_floating_point_v<Real>,
                  "Real type must be a floating point type");

    std::random_device _rd;
    std::mt19937 _engine;
    std::uniform_real_distribution<Real> _distribution;

public:
    RealRandomGenerator(Real min, Real max);
    double operator()();
};

template <typename Real>
RealRandomGenerator<Real>::RealRandomGenerator(Real min, Real max)
    : _rd(), _engine(_rd()), _distribution(min, max)
{
}

template <typename Real>
double RealRandomGenerator<Real>::operator()()
{
    return _distribution(_engine);
}