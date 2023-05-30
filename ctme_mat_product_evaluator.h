/**
 * CTME @link https://github.com/qoala101/ctme @endlink
 * @author Volodymyr Hromakov (4y5t6r@gmail.com)
 * @copyright Copyright (c) 2023, MIT License
 */

#ifndef VH_CTME_MAT_PRODUCT_EVALUATOR_H_
#define VH_CTME_MAT_PRODUCT_EVALUATOR_H_

#include "ctme_concepts.h"      // IWYU pragma: keep
#include "ctme_debug_logger.h"  // IWYU pragma: keep

namespace ctme::details {
/**
 * @brief Recursively evaluates the value of the single cell in the product
 * of two matrices.
 *
 * @tparam ValuesIndex Index of the values container to be used
 * for the current matrix. Goes from size of value containers to zero.
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
   *
   * @param input_values 2D containers with input values.
   */
  static constexpr auto EvaluateCell
      [[nodiscard]] (const MatValues auto &...input_values) {
    if constexpr (ProductIndex > 0) {
      return EvaluateCurrentProduct(input_values...) +
             EvaluateNextProduct(input_values...);
    } else {
      return EvaluateCurrentProduct(input_values...);
    }
  }

 private:
  static constexpr auto EvaluateLeftMatCellValue
      [[nodiscard]] (const MatValues auto &...input_values) {
    return LeftMat::template EvaluateCell<RowIndex, ProductIndex,
                                          ValuesIndex - RightMat::kNumMats>(
        input_values...);
  }

  static constexpr auto EvaluateRightMatCellValue
      [[nodiscard]] (const MatValues auto &...input_values) {
#ifdef CTME_DEBUG
    debug::Logger::Instance().Print() << " * ";
#endif  // CTME_DEBUG
    return RightMat::template EvaluateCell<ProductIndex, ColIndex, ValuesIndex>(
        input_values...);
  }

  static constexpr auto EvaluateCurrentProduct
      [[nodiscard]] (const MatValues auto &...input_values) {
    return EvaluateLeftMatCellValue(input_values...) *
           EvaluateRightMatCellValue(input_values...);
  }

  static constexpr auto EvaluateNextProduct
      [[nodiscard]] (const MatValues auto &...input_values) {
#ifdef CTME_DEBUG
    debug::Logger::Instance().Print() << " +\n";
#endif  // CTME_DEBUG
    return MatProductEvaluator<LeftMat, RightMat, RowIndex, ColIndex,
                               ValuesIndex,
                               ProductIndex - 1>::EvaluateCell(input_values...);
  }
};
}  // namespace ctme::details

#endif  // VH_CTME_MAT_PRODUCT_EVALUATOR_H_
