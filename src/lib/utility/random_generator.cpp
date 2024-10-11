#include "random_generator.h"

RandomGenerator::RandomGenerator(double min, double max)
    : _rd(), _engine(_rd()), _distribution(min, max)
{
}

double RandomGenerator::operator()()
{
    return _distribution(_engine);
}