#pragma once

#include <random>

class RandomGenerator
{
    std::random_device _rd;
    std::mt19937 _engine;
    std::uniform_real_distribution<double> _distribution;

public:
    RandomGenerator(double min, double max);
    double operator()();
};