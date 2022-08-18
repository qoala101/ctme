#ifndef CTME_MAT_SUM_H_
#define CTME_MAT_SUM_H_

#include "ctme_concepts.h"  // IWYU pragma: keep
#include "ctme_mat_sum_evaluator.h"

namespace ctme {
/**
 * @brief Sum of two matrices.
 */
template <MatExpression LeftMat, MatExpression RightMat>
class MatSum {
  static_assert(LeftMat::kNumRows == RightMat::kNumRows);
  static_assert(LeftMat::kNumCols == RightMat::kNumCols);

 public:
  static constexpr unsigned kNumRows = LeftMat::kNumRows;
  static constexpr unsigned kNumCols = LeftMat::kNumCols;
  static constexpr unsigned kNumMats = LeftMat::kNumMats + RightMat::kNumMats;

  template <unsigned RowIndex, unsigned ColIndex, unsigned ValuesIndex>
  [[nodiscard]] static constexpr auto EvaluateCell(
      const MatValues auto &...input_values) {
    return details::MatSumEvaluator<LeftMat, RightMat, RowIndex, ColIndex,
                                    ValuesIndex>::EvaluateCell(input_values...);
  }

  static_assert(MatExpression<MatSum>);
};

/**
 * @brief Produces an object of matrix sum type.
 */
[[nodiscard]] constexpr auto operator+(const MatExpression auto &left_mat,
                                       const MatExpression auto &right_mat) {
  return MatSum<std::decay_t<decltype(left_mat)>,
                std::decay_t<decltype(right_mat)>>{};
}
}  // namespace ctme

#endif  // CTME_MAT_SUM_H_
