#ifndef EVOPTIMIZER_POPULATION_GENE_H_
#define EVOPTIMIZER_POPULATION_GENE_H_

#include <limits>
#include <bitset>

#include <generators.h>

template <typename Integral, typename Real>
class Gene
{
    static_assert(std::is_integral_v<Integral> && std::is_unsigned_v<Integral>,
                  "Integral must be an unsigned integral type");
    static_assert(std::is_floating_point_v<Real>,
                  "Real type must be a floating point type");

    static constexpr Real UINT_SCALER =
        static_cast<Real>(1.0) / static_cast<Real>(std::numeric_limits<Integral>::max());

    Integral _value;

public:
    static Random::IntGenerator<Integral> gen;

    static constexpr Real min = static_cast<Real>(-1.0);
    static constexpr Real max = static_cast<Real>(1.0);

    Gene(Integral init_value = 0) : _value{init_value} {}

    /**
     * Creates a random gene
     */
    static Gene<Integral, Real> createRandom()
    {
        return Gene<Integral, Real>(gen());
    }

    Integral get() const
    {
        return _value;
    }

    void set(Integral new_value)
    {
        _value = new_value;
    }

    static constexpr size_t bitsNum()
    {
        return sizeof(Integral) * 8;
    }

    /**
     * Converts gene's encoded value to real (floating point type) number
     */
    Real getReal() const
    {
        return min + (static_cast<Real>(_value) * UINT_SCALER) * (max - min);
    }

    /**
     * Converts gene to std::string representing it's real value
     */
    std::string toString() const
    {
        return std::to_string(getReal());
    }

    /**
     * Converts gene to std::string representing it's binary value
     */
    std::string toBinaryString() const
    {
        std::bitset<bitsNum()> binary(_value);
        return binary.to_string();
    }
};

// ============================================================

template <typename Integral, typename Real>
Random::IntGenerator<Integral> Gene<Integral, Real>::gen(0, std::numeric_limits<Integral>::max());

#endif