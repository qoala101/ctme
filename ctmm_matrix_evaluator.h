#ifndef CTMM_MATRIX_EVALUATOR_H_
#define CTMM_MATRIX_EVALUATOR_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep
#include "ctmm_mat_traits_size.h"

namespace ctmm {
namespace mat_traits {
template <concepts::Mat T>
class Evaluator;
} // namespace mat_traits

template <concepts::Mat MatType, int RowIndex, int ColIndex>
class MatrixEvaluator {
 public:
  static constexpr void Evaluate(auto &result,
                                 const concepts::Input auto &...inputs) {
    result[RowIndex][ColIndex] =
        mat_traits::Evaluator<MatType>::template Evaluate<RowIndex, ColIndex>(inputs...);

    if constexpr (ColIndex == 0) {
      if constexpr (RowIndex > 0) {
        MatrixEvaluator<MatType, RowIndex - 1, mat_traits::Size<MatType>::kNumCols - 1>::Evaluate(
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
