#ifndef EVOPTIMIZER_RANDOM_GLOBAL_ENGINE_H_
#define EVOPTIMIZER_RANDOM_GLOBAL_ENGINE_H_

#include <random>

namespace Random
{
    // Default random device, used for providing random seed for primary engine
    static std::random_device rd = std::random_device();

    // Mersenne twister engine
    static std::mt19937 engine;
}

#endif