#ifndef EVOPTIMIZER_RANDOM_GENERATORS_H_
#define EVOPTIMIZER_RANDOM_GENERATORS_H_

#include "global_engine.h"

namespace Random
{
    /**
     * Generates whole numbers in range min (inclusive) and max (inclusive)
     */
    template <typename I>
    class IntGenerator
    {
        static_assert(std::is_integral_v<I>,
                      "I type must be an integral type");

        std::uniform_int_distribution<I> _distribution;

    public:
        IntGenerator(I min, I max)
            : _distribution(min, max) {}

        double operator()()
        {
            return _distribution(Random::engine);
        }
    };

    /**
     * Generates real numbers in range min (inclusive) and max (exculsive)
     */
    template <typename R>
    class RealGenerator
    {
        static_assert(std::is_floating_point_v<R>,
                      "R type must be a floating point type");

        std::uniform_real_distribution<R> _distribution;

    public:
        RealGenerator(R min, R max)
            : _distribution(min, max) {}

        double operator()()
        {
            return _distribution(Random::engine);
        }
    };

    /**
     * This generator produces values ranging between 0.0 and 1.0
     */
    static RealGenerator<double> zero_one(0.0, 1.0);
}

#endif