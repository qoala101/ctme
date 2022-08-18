#ifndef CTMM_MAT_PRODUCT_EVALUATOR_H_
#define CTMM_MAT_PRODUCT_EVALUATOR_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep

namespace ctmm {
/**
 * @brief Recursively evaluates the value of the single cell in the product
 * of two matrices.
 *
 * @tparam ValuesIndex Index of the values container to be used
 * for the current matrix. Goes from size of value containers to zero.
 *
 * @tparam ProductIndex Index of the product of each left matrix row cell
 * and each right matrix column cell, sum of which gives the result value.
 * Goes from the number of columns in the first matrix to zero.
 */
template <MatExpression LeftMat, MatExpression RightMat, unsigned RowIndex,
          unsigned ColIndex, unsigned ValuesIndex, unsigned ProductIndex>
class MatProductEvaluator {
 public:
  /**
   * @brief Recursively evaluates the value of the single cell.
   */
  [[nodiscard]] static constexpr auto EvaluateCell(
      const MatValues auto &...input_values) {
    auto result = EvaluateCurrentProduct(input_values...);

    if constexpr (ProductIndex > 0) {
      result += EvaluateNextProduct(input_values...);
    }

    return result;
  }

 private:
  [[nodiscard]] static constexpr auto EvaluateLeftMatCellValue(
      const MatValues auto &...input_values) {
    return LeftMat::template EvaluateCell<RowIndex, ProductIndex,
                                      ValuesIndex - RightMat::kNumMats>(
        input_values...);
  }

  [[nodiscard]] static constexpr auto EvaluateRightMatCellValue(
      const MatValues auto &...input_values) {
    return RightMat::template EvaluateCell<ProductIndex, ColIndex, ValuesIndex>(
        input_values...);
  }

  [[nodiscard]] static constexpr auto EvaluateCurrentProduct(
      const MatValues auto &...input_values) {
    return EvaluateLeftMatCellValue(input_values...) *
           EvaluateRightMatCellValue(input_values...);
  }

  [[nodiscard]] static constexpr auto EvaluateNextProduct(
      const MatValues auto &...input_values) {
    return MatProductEvaluator<LeftMat, RightMat, RowIndex, ColIndex,
                               ValuesIndex,
                               ProductIndex - 1>::EvaluateCell(input_values...);
  }
};
}  // namespace ctmm

#endif  // CTMM_MAT_PRODUCT_EVALUATOR_H_
