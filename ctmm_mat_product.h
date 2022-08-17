#ifndef STONKS_CTMM_EXPRESSION_H_
#define STONKS_CTMM_EXPRESSION_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep
#include "ctmm_matrix_evaluator.h"
#include "ctmm_cell_evaluator.h"

namespace ctmm {
/**
 * @brief
 *
 * @tparam LeftMat Left part of the expression.
 * @tparam RightMat Right part of the expression.
 */
template <concepts::Mat LeftMat, concepts::Mat RightMat>
class MatProduct {
  static_assert(LeftMat::kNumCols == RightMat::kNumRows);

 public:
  static constexpr int kNumRows = LeftMat::kNumRows;
  static constexpr int kNumCols = RightMat::kNumCols;
  static constexpr int kNumInputs = LeftMat::kNumInputs + RightMat::kNumInputs;

  template <int RowIndex, int ColIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    return Evaluate<RowIndex, ColIndex, sizeof...(inputs) - 1>(inputs...);
  }

  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    using ResultType = decltype(Evaluate<0, 0>(inputs...));

    auto result = std::array<std::array<ResultType, kNumCols>, kNumRows>{};

    MatrixEvaluator<MatProduct<LeftMat, RightMat>, kNumRows - 1,
                    kNumCols - 1>::Evaluate(result, inputs...);

    return result;
  }

 private:
  template <concepts::Mat, concepts::Mat, int, int, int, int>
  friend class CellEvaluator;

  friend constexpr auto operator*(const concepts::Mat auto &,
                                  const concepts::Mat auto &) -> concepts::Mat
      auto;

  constexpr explicit MatProduct() = default;

  template <int RowIndex, int ColIndex, int InputIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    return CellEvaluator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                         LeftMat::kNumCols - 1>::Evaluate(inputs...);
  }
};
}

#endif  // STONKS_CTMM_EXPRESSION_H_
