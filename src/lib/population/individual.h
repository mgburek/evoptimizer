#pragma once

#include <array>
#include <string>
#include <sstream>
#include <algorithm>

#include <int_random_generator.h>

template <unsigned int genes_num, typename GeneType>
class Individual
{
    std::array<GeneType, genes_num> _genes;

public:
    Individual(const std::array<GeneType, genes_num> &genes);

    static Individual<genes_num, GeneType> createRandom();

    std::string toString() const;
};

// ============================================================

template <unsigned int genes_num, typename GeneType>
Individual<genes_num, GeneType>::Individual(const std::array<GeneType, genes_num> &genes)
    : _genes(genes)
{
}

/**
 * Creates an individual with random genes
 */
template <unsigned int genes_num, typename GeneType>
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
template <unsigned int genes_num, typename GeneType>
std::string Individual<genes_num, GeneType>::toString() const
{
    std::ostringstream str_stream;
    for (const GeneType &gene : _genes)
        str_stream << gene.toString() << " ";

    return str_stream.str();
}