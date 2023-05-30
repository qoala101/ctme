/**
 * CTME @link https://github.com/qoala101/ctme @endlink
 * @author Volodymyr Hromakov (4y5t6r@gmail.com)
 * @copyright Copyright (c) 2023, MIT License
 */

#ifndef VH_CTME_BENCHMARK_COMPILE_TIME_UTILS_H_
#define VH_CTME_BENCHMARK_COMPILE_TIME_UTILS_H_

#include <array>

namespace utils {
template <unsigned NumRows, unsigned NumCols>
consteval auto CreateMat [[nodiscard]] () {
  return std::array<std::array<int, NumCols>, NumRows>{2};
}
}  // namespace utils

#endif  // VH_CTME_BENCHMARK_COMPILE_TIME_UTILS_H_
