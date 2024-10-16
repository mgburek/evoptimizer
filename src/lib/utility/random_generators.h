#ifndef EVOPTIMIZER_RANDOM_GENERATORS_H_
#define EVOPTIMIZER_RANDOM_GENERATORS_H_

#include "real_random_generator.h"

namespace RandomGenerators
{
    /**
     * This generator produces values ranging between 0.0 and 1.0
     */
    static RealRandomGenerator<double> zero_one(0.0, 1.0);
}

#endif