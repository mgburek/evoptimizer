#ifndef EVOPTIMIZER_INCLUDES_OPTIMIZER_H
#define EVOPTIMIZER_INCLUDES_OPTIMIZER_H

namespace Evo {
template <typename R, size_t arg_num>
class Optimizer {
 public:
  virtual std::array<R, arg_num> operator()(
      const size_t generations_num) const = 0;

  virtual std::array<R, arg_num> operator()(
      const std::chrono::milliseconds timeout) const = 0;
};
}  // namespace Evo

#endif  // EVOPTIMIZER_INCLUDES_OPTIMIZER_H