#ifndef CTME_MAT_SUM_EVALUATOR_H_
#define CTME_MAT_SUM_EVALUATOR_H_

#include "ctme_concepts.h"  // IWYU pragma: keep

namespace ctme::details {
/**
 * @brief Evaluates the value of the single cell in the sum
 * of two matrices.
 *
 * @tparam ValuesIndex Index of the values container to be used
 * for the current matrix.
 */
template <MatExpression LeftMat, MatExpression RightMat, unsigned RowIndex,
          unsigned ColIndex, unsigned ValuesIndex>
class MatSumEvaluator {
 public:
  /**
   * @brief Evaluates the value of the single cell.
   *
   * @param input_values 2D containers with input values.
   */
  static constexpr auto EvaluateCell
      [[nodiscard]] (const MatValues auto &...input_values) {
    return EvaluateLeftMatCellValue(input_values...) +
           EvaluateRightMatCellValue(input_values...);
  }

 private:
  static constexpr auto EvaluateLeftMatCellValue
      [[nodiscard]] (const MatValues auto &...input_values) {
    return LeftMat::template EvaluateCell<RowIndex, ColIndex,
                                          ValuesIndex - RightMat::kNumMats>(
        input_values...);
  }

  static constexpr auto EvaluateRightMatCellValue
      [[nodiscard]] (const MatValues auto &...input_values) {
    return RightMat::template EvaluateCell<RowIndex, ColIndex, ValuesIndex>(
        input_values...);
  }
};
}  // namespace ctme::details

#endif  // CTME_MAT_SUM_EVALUATOR_H_
