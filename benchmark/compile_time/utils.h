#ifndef CTME_BENCHMARK_COMPILE_TIME_UTILS_H_
#define CTME_BENCHMARK_COMPILE_TIME_UTILS_H_

#include <array>

namespace utils {
template <unsigned NumRows, unsigned NumCols>
consteval auto CreateMat [[nodiscard]] () {
  return std::array<std::array<int, NumCols>, NumRows>{2};
}
}  // namespace utils

#endif  // CTME_BENCHMARK_COMPILE_TIME_UTILS_H_
