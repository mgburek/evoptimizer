#ifndef EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_
#define EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_

#include <algorithm>

#include <generation.h>
#include <generators.h>

namespace Evoptimizer
{
    template <typename I, typename R, size_t genes_num, size_t population_size>
    class SinglePointCrossBreeder
    {
        static Random::IntGenerator<size_t> cross_point_gen;

        const double _crossing_chance;

    public:
        SinglePointCrossBreeder(double crossing_chance)
            : _crossing_chance(crossing_chance) {}

        static void cross(Individual<I, R, genes_num> &ind1, Individual<I, R, genes_num> &ind2, size_t cross_point)
        {
            size_t division_gene = cross_point / lengthInBits<I, 1>();

            if (division_gene < genes_num)
                std::swap_ranges(ind1.rbegin(), ind1.rend() - division_gene, ind2.rbegin());

            I mask = (~0x0) << (lengthInBits<I, 1>() - cross_point % lengthInBits<I, 1>());
            I mask_inv = ~mask;

            auto division_gene_a = ind1.at(division_gene).get();
            auto division_gene_b = ind2.at(division_gene).get();

            I ab = (division_gene_a & mask_inv) | (division_gene_b & mask);
            I ba = (division_gene_a & mask) | (division_gene_b & mask_inv);

            ind1.at(division_gene) = ab;
            ind2.at(division_gene) = ba;
        }

        Generation<I, R, genes_num, population_size> operator()(const Generation<I, R, genes_num, population_size> &generation) const
        {
            Generation<I, R, genes_num, population_size> crossed_generation(generation);
            std::shuffle(crossed_generation.begin(), crossed_generation.end(), Random::engine);

            for (size_t i = 0; i < crossed_generation.size(); i += 2)
            {
                if (Random::zero_one() < _crossing_chance)
                    cross(crossed_generation.at(i), crossed_generation.at(i + 1), cross_point_gen());
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