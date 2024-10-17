#ifndef EVOPTIMIZER_POPULATION_INDIVIDUAL_H_
#define EVOPTIMIZER_POPULATION_INDIVIDUAL_H_

#include <cstddef>
#include <array>
#include <string>
#include <sstream>
#include <algorithm>

#include <int_random_generator.h>

#include "gene.h"

template <typename Integral, typename Real, size_t genes_num>
class Individual
{
    using GeneType = Gene<Integral, Real>;
    std::array<GeneType, genes_num> _genes;

public:
    Individual(const std::array<GeneType, genes_num> &genes)
        : _genes(genes) {}

    Individual()
        : _genes() {}

    static Individual<Integral, Real, genes_num> createRandom();

    std::string toString() const;

    std::array<GeneType, genes_num> &mutableGenes()
    {
        return _genes;
    }

    const std::array<GeneType, genes_num> &genes() const
    {
        return _genes;
    }

    const std::array<Real, genes_num> realGenes() const
    {
        std::array<Real, genes_num> real_values;
        for (size_t i = 0; i < genes_num; i++)
            real_values[i] = _genes[i].getReal();
        return real_values;
    }

    static constexpr size_t bitsNum()
    {
        return sizeof(Integral) * 8 * genes_num;
    }
};

// ============================================================

/**
 * Creates an individual with random genes
 */
template <typename Integral, typename Real, size_t genes_num>
Individual<Integral, Real, genes_num> Individual<Integral, Real, genes_num>::createRandom()
{
    std::array<GeneType, genes_num> genes;
    std::generate(genes.begin(), genes.end(), []()
                  { return GeneType::createRandom(); });
    return Individual<Integral, Real, genes_num>(std::move(genes));
}

/**
 * Converts an indivdual to space separated std::string
 */
template <typename Integral, typename Real, size_t genes_num>
std::string Individual<Integral, Real, genes_num>::toString() const
{
    std::ostringstream str_stream;
    for (const GeneType &gene : _genes)
        str_stream << gene.toString() << " ";

    return str_stream.str();
}

#endif