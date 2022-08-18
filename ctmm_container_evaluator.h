#ifndef CTMM_CONTAINER_EVALUATOR_H_
#define CTMM_CONTAINER_EVALUATOR_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep

namespace ctmm {
/**
 * @brief Recursively evaluates the value for each expression result cell
 * and writes it to result container.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 * @tparam RowIndex Currently evaluated row index. Goes form the number of rows
 * of the result to 0.
 * @tparam ColIndex Currently evaluated column index. Goes form the number of
 * columns of the result to 0.
 */
template <MatExpression Expression, unsigned RowIndex, unsigned ColIndex>
class ContainerEvaluator {
 public:
  /**
   * @brief Recursively evaluates and writes the value of each cell
   * to the result container.
   *
   * @param result_values 2D container to which result values are being written.
   * @param input_values 2D containers with input values.
   */
  static constexpr void EvaluateTo(MatValues auto &result_values,
                                   const MatValues auto &...input_values) {
    EvaluateCurrentCell(result_values, input_values...);

    if constexpr (ColIndex == 0) {
      if constexpr (RowIndex > 0) {
        EvaluateFirstCellOfNextRow(result_values, input_values...);
      }
    } else {
      EvaluateNextCellOfThisRow(result_values, input_values...);
    }
  }

 private:
  static constexpr void EvaluateCurrentCell(
      MatValues auto &result_values, const MatValues auto &...input_values) {
    result_values[RowIndex][ColIndex] = Expression::template EvaluateCell<
        RowIndex, ColIndex, sizeof...(input_values) - 1>(input_values...);
  }

  static constexpr void EvaluateNextCellOfThisRow(
      MatValues auto &result_values, const MatValues auto &...input_values) {
    ContainerEvaluator<Expression, RowIndex, ColIndex - 1>::EvaluateTo(
        result_values, input_values...);
  }

  static constexpr void EvaluateFirstCellOfNextRow(
      MatValues auto &result_values, const MatValues auto &...input_values) {
    ContainerEvaluator<Expression, RowIndex - 1,
                       Expression::kNumCols - 1>::EvaluateTo(result_values,
                                                             input_values...);
  }
};
}  // namespace ctmm

#endif  // CTMM_CONTAINER_EVALUATOR_H_
