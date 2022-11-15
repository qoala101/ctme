#ifndef CTME_BENCHMARK_RUNTIME_UTILS_H_
#define CTME_BENCHMARK_RUNTIME_UTILS_H_

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

  for (auto i = 0; i < NumRows; ++i) {
    for (auto j = 0; j < NumCols; ++j) {
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

  for (auto i = 0; i < LeftNumRows; ++i) {
    for (auto j = 0; j < RightNumCols; ++j) {
      auto result_cell = double{};

      for (auto k = 0; k < CommonNum; ++k) {
        result_cell += left_mat[i][k] * right_mat[k][j];
      }

      result[i][j] = result_cell;
    }
  }

  return result;
}
}  // namespace utils

#endif  // CTME_BENCHMARK_RUNTIME_UTILS_H_
