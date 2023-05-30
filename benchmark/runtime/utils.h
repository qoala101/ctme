/**
 * CTME @link https://github.com/qoala101/ctme @endlink
 * @author Volodymyr Hromakov (4y5t6r@gmail.com)
 * @copyright Copyright (c) 2023, MIT License
 */

#ifndef VH_CTME_BENCHMARK_RUNTIME_UTILS_H_
#define VH_CTME_BENCHMARK_RUNTIME_UTILS_H_

#include <array>
#include <random>
#include <vector>

#include "ctme_concepts.h"  // IWYU pragma: keep

namespace utils {
struct AsArray {
  template <unsigned NumRows, unsigned NumCols>
  static auto Create [[nodiscard]] () {
    return std::array<std::array<double, NumRows>, NumCols>{};
  }
};

struct AsVector {
  template <unsigned NumRows, unsigned NumCols>
  static auto Create [[nodiscard]] () {
    return std::vector<std::vector<double>>(NumRows,
                                            std::vector<double>(NumCols, 0));
  }
};

template <typename ContainerCreator, unsigned NumRows, unsigned NumCols>
auto GenerateRandomValues [[nodiscard]] () {
  auto values = ContainerCreator::template Create<NumRows, NumCols>();

  auto random_engine = std::default_random_engine{};
  auto distribution = std::uniform_real_distribution<double>{0, 10};

  for (auto i = 0U; i < NumRows; ++i) {
    for (auto j = 0U; j < NumCols; ++j) {
      values[i][j] = distribution(random_engine);
    }
  }

  return values;
}

template <typename ContainerCreator, unsigned LeftNumRows, unsigned CommonNum,
          unsigned RightNumCols>
auto MultiplyWithLoops [[nodiscard]] (const ctme::MatValues auto& left_mat,
                                      const ctme::MatValues auto& right_mat) {
  auto result = ContainerCreator::template Create<CommonNum, CommonNum>();

  for (auto i = 0U; i < LeftNumRows; ++i) {
    for (auto j = 0U; j < RightNumCols; ++j) {
      auto result_cell = double{};

      for (auto k = 0U; k < CommonNum; ++k) {
        result_cell += left_mat[i][k] * right_mat[k][j];
      }

      result[i][j] = result_cell;
    }
  }

  return result;
}
}  // namespace utils

#endif  // VH_CTME_BENCHMARK_RUNTIME_UTILS_H_
