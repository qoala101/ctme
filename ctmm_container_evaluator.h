#ifndef CTMM_MATRIX_EVALUATOR_H_
#define CTMM_MATRIX_EVALUATOR_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep

namespace ctmm {
template <MatExpression MatType, unsigned RowIndex, unsigned ColIndex>
class ContainerEvaluator {
 public:
  /**
   * @brief
   *
   * @param result_values
   * @param input_values
   */
  static constexpr void EvaluateCell(MatValues auto &result_values,
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
    result_values[RowIndex][ColIndex] = MatType::template EvaluateCell<
        RowIndex, ColIndex, sizeof...(input_values) - 1>(input_values...);
  }

  static constexpr void EvaluateNextCellOfThisRow(
      MatValues auto &result_values, const MatValues auto &...input_values) {
    ContainerEvaluator<MatType, RowIndex, ColIndex - 1>::EvaluateCell(result_values,
                                                               input_values...);
  }

  static constexpr void EvaluateFirstCellOfNextRow(
      MatValues auto &result_values, const MatValues auto &...input_values) {
    ContainerEvaluator<MatType, RowIndex - 1, MatType::kNumCols - 1>::EvaluateCell(
        result_values, input_values...);
  }
};
}  // namespace ctmm

#endif  // CTMM_MATRIX_EVALUATOR_H_
