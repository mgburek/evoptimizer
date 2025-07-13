#ifndef EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_
#define EVOPTIMIZER_SINGLE_POINT_CROSS_BREEDER_H_

#include <algorithm>

#include <generation.h>
#include <generators.h>

#include "cross_breeder.h"

namespace Evo {
template <typename R, size_t genes_num, size_t population_size>
class SinglePointMeanCrossBreeder
    : public CrossBreeder<R, genes_num, population_size> {
  static Random::IntGenerator<size_t> cross_point_gen;

 public:
  SinglePointMeanCrossBreeder(double crossing_chance)
      : CrossBreeder<R, genes_num, population_size>(crossing_chance) {}

  void cross(RealIndividual<R, genes_num>& ind1,
             RealIndividual<R, genes_num>& ind2) const override {
    crossAtPoint(ind1, ind2, cross_point_gen());
  }

  static void crossAtPoint(RealIndividual<R, genes_num>& ind1,
                         RealIndividual<R, genes_num>& ind2,
                         size_t cross_point) {
    std::swap_ranges(ind1.begin() + cross_point, ind1.end(),
                     ind2.begin() + cross_point);

    auto division_gene_a = ind1.at(cross_point);
    auto division_gene_b = ind2.at(cross_point);

    R mean = (division_gene_a + division_gene_b) * 0.5;

    ind1.at(cross_point) = mean;
    ind2.at(cross_point) = mean;
  }
};

// ============================================================

template <typename R, size_t genes_num, size_t population_size>
Random::IntGenerator<size_t>
    SinglePointMeanCrossBreeder<R, genes_num, population_size>::cross_point_gen(
        1,
        genes_num - 2);

}  // namespace Evo
#endif