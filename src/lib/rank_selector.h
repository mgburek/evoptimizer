#ifndef EVOPTIMIZER_RANK_SELECTOR_H_
#define EVOPTIMIZER_RANK_SELECTOR_H_

#include <array>
#include <algorithm>
#include <numeric>

#include <generators.h>

template <typename Integral, typename Real, size_t genes_num, size_t population_size>
class RankSelector
{
    using GenerationType = Generation<Integral, Real, genes_num, population_size>;

public:
    RankSelector() {}

    GenerationType operator()(
        const GenerationType &generation, std::array<Real, population_size> fitness) const
    {
        std::array<size_t, population_size> indices;
        std::iota(indices.begin(), indices.end(), 0); // fills array with incrementing values

        std::sort(indices.begin(), indices.end(), [&fitness](size_t a, size_t b)
                  { return fitness[a] > fitness[b]; });

        // (N * (N+1)) / 2
        constexpr double ranks_sum = static_cast<double>(population_size * (population_size + 1)) * 0.5;

        std::array<double, population_size> odds;
        double rank = 0.0;
        double prev_odd = 0.0;
        std::generate(odds.begin(), odds.end(), [&rank, &prev_odd]()
                      {
            rank += 1.0;
            prev_odd = prev_odd + (rank / ranks_sum);
            return prev_odd; });

        auto new_generation_generator = [&]()
        {
            double selection = Random::zero_one();
            auto it = std::lower_bound(odds.begin(), odds.end(), selection);
            int index = indices[std::distance(odds.begin(), it)];
            return generation.population().at(index);
        };

        GenerationType new_generation;
        std::generate(new_generation.mutablePopulation().begin(),
                      new_generation.mutablePopulation().end(),
                      new_generation_generator);

        return new_generation;
    }
};

#endif