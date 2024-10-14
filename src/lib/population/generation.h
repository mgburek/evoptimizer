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

    static Generation<Integral, Real, genes_num, population_size> createRandom();

    std::string toString() const;

    /**
     * Returns an Individual at index idx
     */
    constexpr IndividualType operator[](int idx) const
    {
        return _population.at(idx);
    }

    using iterator = std::array<IndividualType, population_size>::iterator;
    using const_iterator = std::array<IndividualType, population_size>::const_iterator;

    iterator begin() { return _population.begin(); }
    // const_iterator cbegin() { return _population.cbegin(); }
    iterator end() { return _population.end(); }
    // const_iterator cend() { return _population.cend(); }
};

// ============================================================

/**
 * Creates a random population
 */
template <typename Integral, typename Real, size_t genes_num, size_t population_size>
Generation<Integral, Real, genes_num, population_size> Generation<Integral, Real, genes_num, population_size>::createRandom()
{
    Generation<Integral, Real, genes_num, population_size> population;
    std::generate(population.begin(), population.end(), []()
                  { return IndividualType::createRandom(); });
    return std::move(population);
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