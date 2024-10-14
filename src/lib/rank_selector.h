#ifndef EVOPTIMIZER_SELECTOR_H_
#define EVOPTIMIZER_SELECTOR_H_

#include <array>
#include <algorithm>
#include <numeric>

#include <real_random_generator.h>

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
class RankSelector
{
    using GenerationType = Generation<Integral, Real, genes_num, population_size>;

    static RealRandomGenerator<double> rdg;

public:
    RankSelector() {}

    GenerationType operator()(
        GenerationType generation, std::array<Real, population_size> fitness) const
    {
        std::array<size_t, population_size> indices;
        std::iota(indices.begin(), indices.end(), 0); // fills array with incrementing values

        std::sort(indices.begin(), indices.end(), [&fitness](size_t a, size_t b)
                  { return fitness[a] > fitness[b]; });

        // (N * (N+1)) / 2
        constexpr double ranks_sum = static_cast<double>(population_size * (population_size + 1)) * 0.5;

        std::array<double, population_size> odds;
        double x = 0.0;
        double prev_odd = 0.0;
        std::generate(odds.begin(), odds.end(), [&x, &prev_odd]()
                      {
            x += 1.0;
            prev_odd = prev_odd + (x / ranks_sum);
            return prev_odd; });

        GenerationType new_generation;
        std::generate(new_generation.begin(), new_generation.end(), [&]()
                      {
                            double selection = rdg();
                            auto it = std::find_if(odds.begin(), odds.end(), [&](double odd)
                            { return odd > selection; }); 
                            int index = indices[std::distance(odds.begin(), it)];
                            return generation[index]; });

        return new_generation;
    }
};

// ============================================================

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
RealRandomGenerator<double> RankSelector<Integral, Real, genes_num, population_size>::rdg(0.0, 1.0);

#endif