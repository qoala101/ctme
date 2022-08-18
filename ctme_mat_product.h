#ifndef CTMM_MAT_PRODUCT_H_
#define CTMM_MAT_PRODUCT_H_

#include "ctme_concepts.h"  // IWYU pragma: keep
#include "ctme_mat_product_evaluator.h"

namespace ctme {
/**
 * @brief Multiplication product of two matrices.
 */
template <MatExpression LeftMat, MatExpression RightMat>
class MatProduct {
  static_assert(LeftMat::kNumCols == RightMat::kNumRows);

 public:
  static constexpr unsigned kNumRows = LeftMat::kNumRows;
  static constexpr unsigned kNumCols = RightMat::kNumCols;
  static constexpr unsigned kNumMats = LeftMat::kNumMats + RightMat::kNumMats;

  template <unsigned RowIndex, unsigned ColIndex, unsigned ValuesIndex>
  [[nodiscard]] static constexpr auto EvaluateCell(
      const MatValues auto &...input_values) {
    return details::MatProductEvaluator<
        LeftMat, RightMat, RowIndex, ColIndex, ValuesIndex,
        LeftMat::kNumCols - 1>::EvaluateCell(input_values...);
  }

  static_assert(MatExpression<MatProduct>);
};

/**
 * @brief Produces an object of matrix product type.
 */
[[nodiscard]] constexpr auto operator*(const MatExpression auto &left_mat,
                                       const MatExpression auto &right_mat)
    -> MatExpression auto{
  return MatProduct<std::decay_t<decltype(left_mat)>,
                    std::decay_t<decltype(right_mat)>>{};
}
}  // namespace ctme

#endif  // CTMM_MAT_PRODUCT_H_
