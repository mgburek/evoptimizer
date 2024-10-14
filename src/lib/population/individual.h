#ifndef EVOPTIMIZER_POPULATION_INDIVIDUAL_H_
#define EVOPTIMIZER_POPULATION_INDIVIDUAL_H_

#include <cstddef>
#include <array>
#include <string>
#include <sstream>
#include <algorithm>

#include <int_random_generator.h>

template <size_t genes_num, typename GeneType>
class Individual
{
    std::array<GeneType, genes_num> _genes;

public:
    using RealType = GeneType::RealType;

    Individual(const std::array<GeneType, genes_num> &genes)
        : _genes(genes) {}

    Individual()
        : _genes() {}

    static Individual<genes_num, GeneType> createRandom();

    std::string toString() const;

    /**
     * Returns a RealType value of a gene at index idx
     */
    constexpr RealType operator[](int idx)
    {
        return _genes.at(idx).toReal();
    }
};

// ============================================================

/**
 * Creates an individual with random genes
 */
template <size_t genes_num, typename GeneType>
Individual<genes_num, GeneType> Individual<genes_num, GeneType>::createRandom()
{
    std::array<GeneType, genes_num> genes;
    std::generate(genes.begin(), genes.end(), []()
                  { return GeneType::createRandom(); });
    return Individual<genes_num, GeneType>(std::move(genes));
}

/**
 * Converts an indivdual to space separated std::string
 */
template <size_t genes_num, typename GeneType>
std::string Individual<genes_num, GeneType>::toString() const
{
    std::ostringstream str_stream;
    for (const GeneType &gene : _genes)
        str_stream << gene.toString() << " ";

    return str_stream.str();
}

#endif