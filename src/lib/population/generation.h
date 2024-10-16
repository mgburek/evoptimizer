#ifndef EVOPTIMIZER_POPULATION_GENERATION_H_
#define EVOPTIMIZER_POPULATION_GENERATION_H_

#include <cstdlib>
#include <string>

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
class Generation
{
    using IndividualType = Individual<Integral, Real, genes_num>;
    std::array<IndividualType, population_size> _population;

public:
    Generation(const std::array<IndividualType, population_size> &population)
        : _population(population) {}

    Generation()
        : _population() {}

    Generation(const Generation<Integral, Real, genes_num, population_size> &other)
        : _population(other._population) {}

    static Generation<Integral, Real, genes_num, population_size> createRandom();

    std::string toString() const;

    std::array<IndividualType, population_size> &mutablePopulation()
    {
        return _population;
    }

    const std::array<IndividualType, population_size> &population() const
    {
        return _population;
    }
};

// ============================================================

/**
 * Creates a random population
 */
template <typename Integral, typename Real, size_t genes_num, size_t population_size>
Generation<Integral, Real, genes_num, population_size> Generation<Integral, Real, genes_num, population_size>::createRandom()
{
    Generation<Integral, Real, genes_num, population_size> generation;
    std::generate(generation.mutablePopulation().begin(), generation.mutablePopulation().end(), []()
                  { return IndividualType::createRandom(); });
    return std::move(generation);
}

/**
 * Converts an indivdual to space separated std::string
 */
template <typename Integral, typename Real, size_t genes_num, size_t population_size>
std::string Generation<Integral, Real, genes_num, population_size>::toString() const
{
    std::ostringstream str_stream;
    for (const IndividualType &individual : _population)
        str_stream << individual.toString() << std::endl;

    return str_stream.str();
}

#endif