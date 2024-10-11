#pragma once

#include <array>
#include <string>
#include <sstream>
#include <algorithm>

#include <random_generator.h>

static RandomGenerator gen = RandomGenerator(-1.0, 1.0);

template <unsigned int traits_num>
class Individual
{
    std::array<double, traits_num> _traits;

public:
    Individual();

    std::string toString() const;
};

template <unsigned int traits_num>
Individual<traits_num>::Individual()
{

    std::generate(_traits.begin(), _traits.end(), []()
                  { return gen(); });
}

template <unsigned int traits_num>
std::string Individual<traits_num>::toString() const
{
    std::ostringstream str_stream;
    for (const auto trait : _traits)
        str_stream << trait << " ";

    return str_stream.str();
}