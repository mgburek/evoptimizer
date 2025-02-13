#ifndef EVOPTIMIZER_POPULATION_GENE_H_
#define EVOPTIMIZER_POPULATION_GENE_H_

#include <bitset>
#include <limits>

#include <generators.h>

namespace Evo::Classic {
template <typename I, typename R>
class Gene {
  static_assert(std::is_integral_v<I> && std::is_unsigned_v<I>,
                "I must be an unsigned integral type");
  static_assert(std::is_floating_point_v<R>,
                "R type must be a floating point type");

  static constexpr R UINT_SCALER =
      static_cast<R>(1.0) / static_cast<R>(std::numeric_limits<I>::max());

  I _value;

  static Random::IntGenerator<I> gen;

 public:
  inline static R min = static_cast<R>(-1.0);
  inline static R max = static_cast<R>(1.0);

  Gene(I init_value = 0) : _value{init_value} {}

  /**
   * Creates a random gene
   */
  static Gene<I, R> createRandom() { return Gene<I, R>(gen()); }

  I get() const { return _value; }

  void set(I new_value) { _value = new_value; }

  /**
   * Converts gene's encoded value to real (floating point type) number
   */
  R toReal() const {
    return min + (static_cast<R>(_value) * UINT_SCALER) * (max - min);
  }

  /**
   * Converts gene to std::string representing it's real value
   */
  std::string toString() const { return std::to_string(toReal()); }

  /**
   * Converts gene to std::string representing it's binary value
   */
  std::string toBinaryString() const {
    std::bitset<sizeof(I) * 8> binary(_value);
    return binary.to_string();
  }
};

// ============================================================

template <typename I, typename R>
Random::IntGenerator<I> Gene<I, R>::gen(0, std::numeric_limits<I>::max());
}  // namespace Evo::Classic

#endif