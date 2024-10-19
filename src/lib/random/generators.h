#ifndef EVOPTIMIZER_RANDOM_GENERATORS_H_
#define EVOPTIMIZER_RANDOM_GENERATORS_H_

#include "global_engine.h"

namespace Random
{
    template <typename Integral>
    class IntGenerator
    {
        static_assert(std::is_integral_v<Integral>,
                      "Integral type must be an integral type");

        std::uniform_int_distribution<Integral> _distribution;

    public:
        IntGenerator(Integral min, Integral max)
            : _distribution(min, max) {}

        double operator()()
        {
            return _distribution(Random::engine);
        }
    };

    template <typename Real>
    class RealGenerator
    {
        static_assert(std::is_floating_point_v<Real>,
                      "Real type must be a floating point type");

        std::uniform_real_distribution<Real> _distribution;

    public:
        RealGenerator(Real min, Real max)
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