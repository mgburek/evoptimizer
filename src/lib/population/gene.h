#pragma once

#include <limits>
#include <bitset>

template <typename Integral, typename Real, Real min, Real max>
class Gene
{
    static_assert(std::is_integral_v<Integral> && std::is_unsigned_v<Integral>,
                  "Integral must be an unsigned integral type");
    static_assert(std::is_floating_point_v<Real>,
                  "Real type must be a floating point type");

    static constexpr Real MAX_REAL_VALUE =
        static_cast<Real>(std::numeric_limits<Integral>::max());

    static IntRandomGenerator<Integral> gen;

    Integral _value;

public:
    Gene(Integral init_value = 0);

    static Gene<Integral, Real, min, max> createRandom();

    Real toReal() const;
    std::string toString() const;
    std::string toBinaryString() const;
};

// ============================================================

template <typename Integral, typename Real, Real min, Real max>
IntRandomGenerator<Integral> Gene<Integral, Real, min, max>::gen(0, std::numeric_limits<Integral>::max());

template <typename Integral, typename Real, Real min, Real max>
Gene<Integral, Real, min, max>::Gene(Integral init_value) : _value{init_value}
{
}

/**
 * Creates a random gene
 */
template <typename Integral, typename Real, Real min, Real max>
Gene<Integral, Real, min, max> Gene<Integral, Real, min, max>::createRandom()
{
    return Gene<Integral, Real, min, max>(gen());
}

/**
 * Converts gene's encoded value to real (floating point type) number
 */
template <typename Integral, typename Real, Real min, Real max>
Real Gene<Integral, Real, min, max>::toReal() const
{
    return min + (static_cast<Real>(_value) / MAX_REAL_VALUE) * (max - min);
}

/**
 * Converts gene to std::string representing it's real value
 */
template <typename Integral, typename Real, Real min, Real max>
std::string Gene<Integral, Real, min, max>::toString() const
{
    return std::to_string(toReal());
}

/**
 * Converts gene to std::string representing it's binary value
 */
template <typename Integral, typename Real, Real min, Real max>
std::string Gene<Integral, Real, min, max>::toBinaryString() const
{
    std::bitset<sizeof(Integral) * 8> binary(_value);
    return binary.to_string();
}