#ifndef CTMM_H_
#define CTMM_H_

#include <array>
#include <exception>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "ctmm_cell_evaluator.h"
#include "ctmm_concepts.h"  // IWYU pragma: keep
#include "ctmm_matrix_evaluator.h"

namespace ctmm {
template <int NumRows, int NumCols>
class Mat {
  static_assert(NumRows > 0);
  static_assert(NumCols > 0);

 public:
  static constexpr int kNumRows = NumRows;
  static constexpr int kNumCols = NumCols;
  static constexpr int kNumInputs = 1;

  template <int RowIndex, int ColIndex, int InputIndex = 0>
  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    return std::get<InputIndex>(std::tie(inputs...))[RowIndex][ColIndex];
  }

  [[nodiscard]] static constexpr auto Evaluate(const concepts::Input auto &...inputs) {
    using ResultType = decltype(Evaluate<0, 0>(inputs...));

    auto result = std::array<std::array<ResultType, kNumCols>, kNumRows>{};

    MatrixEvaluator<Mat, kNumRows - 1, kNumCols - 1>::Evaluate(result,
                                                               inputs...);

    return result;
  }
};

template <concepts::Mat LeftMat, concepts::Mat RightMat>
class ExprMat {
  static_assert(LeftMat::kNumCols == RightMat::kNumRows);

 public:
  static constexpr int kNumRows = LeftMat::kNumRows;
  static constexpr int kNumCols = RightMat::kNumCols;
  static constexpr int kNumInputs = LeftMat::kNumInputs + RightMat::kNumInputs;

  template <int RowIndex, int ColIndex>
  [[nodiscard]] static constexpr auto Evaluate(const concepts::Input auto &...inputs) {
    return Evaluate<RowIndex, ColIndex, sizeof...(inputs) - 1>(inputs...);
  }

  [[nodiscard]] static constexpr auto Evaluate(const concepts::Input auto &...inputs) {
    using ResultType = decltype(Evaluate<0, 0>(inputs...));

    auto result = std::array<std::array<ResultType, kNumCols>, kNumRows>{};

    MatrixEvaluator<ExprMat<LeftMat, RightMat>, kNumRows - 1,
                    kNumCols - 1>::Evaluate(result, inputs...);

    return result;
  }

 private:
  template <concepts::Mat, concepts::Mat, int, int, int, int>
  friend class CellEvaluator;

  friend constexpr auto operator*(const concepts::Mat auto &,
                                  const concepts::Mat auto &);

  constexpr explicit ExprMat() = default;

  template <int RowIndex, int ColIndex, int InputIndex>
  [[nodiscard]] static constexpr auto Evaluate(const concepts::Input auto &...inputs) {
    return CellEvaluator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                         LeftMat::kNumCols - 1>::Evaluate(inputs...);
  }
};

[[nodiscard]] constexpr auto operator*(const concepts::Mat auto &left_mat,
                                       const concepts::Mat auto &right_mat) {
  return ExprMat<std::decay_t<decltype(left_mat)>,
                 std::decay_t<decltype(right_mat)>>{};
}
}  // namespace ctmm

#endif  // CTMM_H_
