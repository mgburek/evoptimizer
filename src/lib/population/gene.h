#ifndef EVOPTIMIZER_POPULATION_GENE_H_
#define EVOPTIMIZER_POPULATION_GENE_H_

#include <limits>
#include <bitset>

template <typename Integral, typename Real>
class Gene
{
    static_assert(std::is_integral_v<Integral> && std::is_unsigned_v<Integral>,
                  "Integral must be an unsigned integral type");
    static_assert(std::is_floating_point_v<Real>,
                  "Real type must be a floating point type");

    static constexpr Real UINT_SCALER =
        static_cast<Real>(1.0) / static_cast<Real>(std::numeric_limits<Integral>::max());

    static IntRandomGenerator<Integral> gen;

    Integral _value;

public:
    inline static Real min = static_cast<Real>(-1.0);
    inline static Real max = static_cast<Real>(1.0);

    using RealType = Real;

    Gene(Integral init_value = 0) : _value{init_value}
    {
    }

    /**
     * Creates a random gene
     */
    static Gene<Integral, Real> createRandom()
    {
        return Gene<Integral, Real>(gen());
    }

    /**
     * Converts gene's encoded value to real (floating point type) number
     */
    Real toReal() const
    {
        return min + (static_cast<Real>(_value) * UINT_SCALER) * (max - min);
    }

    /**
     * Converts gene to std::string representing it's real value
     */
    std::string toString() const
    {
        return std::to_string(toReal());
    }

    /**
     * Converts gene to std::string representing it's binary value
     */
    std::string toBinaryString() const
    {
        std::bitset<sizeof(Integral) * 8> binary(_value);
        return binary.to_string();
    }
};

// ============================================================

template <typename Integral, typename Real>
IntRandomGenerator<Integral> Gene<Integral, Real>::gen(0, std::numeric_limits<Integral>::max());

#endif