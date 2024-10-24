#ifndef EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_
#define EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_

#include <algorithm>

#include <generation.h>
#include <generators.h>

namespace Evoptimzer
{
    template <typename I, typename R, size_t genes_num, size_t population_size>
    class SinglePointCrossBreeder
    {
        static Random::IntGenerator<size_t> cross_point_gen;

        const double _crossing_chance;

    public:
        SinglePointCrossBreeder(double crossing_chance)
            : _crossing_chance(crossing_chance) {}

        Generation<I, R, genes_num, population_size> operator()(const Generation<I, R, genes_num, population_size> &generation) const
        {
            Generation crossed_generation(generation);
            std::shuffle(crossed_generation.begin(), crossed_generation.end(), Random::engine);

            for (size_t i = 0; i < crossed_generation.size(); i += 2)
            {
                if (Random::zero_one() < _crossing_chance)
                {
                    size_t cross_point = cross_point_gen();

                    size_t division_gene = cross_point / Evoptimzer::lengthInBits<I, 1>();

                    auto &ind_a = crossed_generation.at(i);
                    auto &ind_b = crossed_generation.at(i + 1);

                    if (division_gene > 0)
                        std::swap_ranges(ind_a.begin(), ind_a.begin() + division_gene, ind_b.begin());

                    I mask = (~0x0) << cross_point;
                    I mask_inv = ~mask;

                    auto division_gene_a = ind_a.at(division_gene).get();
                    auto division_gene_b = ind_b.at(division_gene).get();

                    I ab = (division_gene_a & mask_inv) | (division_gene_b & mask);
                    I ba = (division_gene_a & mask) | (division_gene_b & mask_inv);

                    ind_a.at(division_gene) = ab;
                    ind_b.at(division_gene) = ba;
                }
            }
            return crossed_generation;
        }
    };

    // ============================================================

    template <typename I, typename R, size_t genes_num, size_t population_size>
    Random::IntGenerator<size_t>
        SinglePointCrossBreeder<I, R, genes_num, population_size>::cross_point_gen(1, lengthInBits<I, genes_num>() - 1);
}
#endif