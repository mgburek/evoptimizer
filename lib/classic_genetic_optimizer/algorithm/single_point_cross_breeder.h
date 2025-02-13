#ifndef EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_
#define EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_

#include <algorithm>

#include <generation.h>
#include <generators.h>

#include "cross_breeder.h"

namespace Evo {
template <typename I, typename R, size_t genes_num, size_t population_size>
class SinglePointCrossBreeder
    : public CrossBreeder<I, R, genes_num, population_size> {
  static Random::IntGenerator<size_t> cross_point_gen;

 public:
  SinglePointCrossBreeder(double crossing_chance)
      : CrossBreeder<I, R, genes_num, population_size>(crossing_chance) {}

  void cross(Individual<I, R, genes_num>& ind1,
             Individual<I, R, genes_num>& ind2) const override {
    crossAtPoint(ind1, ind2, cross_point_gen());
  }

  static void crossAtPoint(Individual<I, R, genes_num>& ind1,
                           Individual<I, R, genes_num>& ind2,
                           size_t cross_point) {
    size_t division_gene = cross_point / lengthInBits<I, 1>();

    if (division_gene < genes_num)
      std::swap_ranges(ind1.rbegin(), ind1.rend() - division_gene,
                       ind2.rbegin());

    I mask =
        (~0x0) << (lengthInBits<I, 1>() - cross_point % lengthInBits<I, 1>());
    I mask_inv = ~mask;

    auto division_gene_a = ind1.at(division_gene).get();
    auto division_gene_b = ind2.at(division_gene).get();

    I ab = (division_gene_a & mask_inv) | (division_gene_b & mask);
    I ba = (division_gene_a & mask) | (division_gene_b & mask_inv);

    ind1.at(division_gene) = ab;
    ind2.at(division_gene) = ba;
  }
};

// ============================================================

template <typename I, typename R, size_t genes_num, size_t population_size>
Random::IntGenerator<size_t>
    SinglePointCrossBreeder<I, R, genes_num, population_size>::cross_point_gen(
        1,
        lengthInBits<I, genes_num>() - 1);
}  // namespace Evo
#endif