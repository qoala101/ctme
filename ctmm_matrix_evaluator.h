#ifndef CTMM_MATRIX_EVALUATOR_H_
#define CTMM_MATRIX_EVALUATOR_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep

namespace ctmm {
template <MatExpression MatType, unsigned RowIndex, unsigned ColIndex>
class MatrixEvaluator {
 public:
  static constexpr void Evaluate(auto &result,
                                 const Container2D auto &...inputs) {
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

#endif  // CTMM_MATRIX_EVALUATOR_H_
