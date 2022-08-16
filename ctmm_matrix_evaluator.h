#ifndef STONKS_CTMM_MATRIX_EVALUATOR_H_
#define STONKS_CTMM_MATRIX_EVALUATOR_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep

namespace ctmm {
template <concepts::Mat MatType, int RowIndex, int ColIndex>
class MatrixEvaluator {
 public:
  template <typename... Inputs>
  static constexpr void Evaluate(auto &result, const Inputs &...inputs) {
    result[RowIndex][ColIndex] =
        MatType::template Evaluate<RowIndex, ColIndex>(inputs...);

    if constexpr (ColIndex == 0) {
      if constexpr (RowIndex > 0) {
        MatrixEvaluator<MatType, RowIndex - 1, MatType::kNumCols - 1>::Evaluate(
            result, inputs...);
      }
    } else {
      MatrixEvaluator<MatType, RowIndex, ColIndex - 1>::Evaluate(result,
                                                                 inputs...);
    }
  }
};
}  // namespace ctmm

#endif  // STONKS_CTMM_MATRIX_EVALUATOR_H_
