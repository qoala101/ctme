#ifndef STONKS_CTMM_MAT_PRODUCT_EVALUATOR_H_
#define STONKS_CTMM_MAT_PRODUCT_EVALUATOR_H_
#include <array>
#include <tuple>

#include "ctmm_concepts.h"
#include "ctmm_matrix_evaluator.h"

namespace ctmm {
template <MatExpression LeftMat, MatExpression RightMat, unsigned RowIndex,
          unsigned ColIndex, unsigned InputIndex, unsigned ProductIndex>
class MatProductEvaluator {
 public:
  [[nodiscard]] static constexpr auto Evaluate(
      const Container2D auto &...inputs) {
    auto result = EvaluateCurrentProduct(inputs...);

    if constexpr (ProductIndex > 0) {
      result += EvaluateNextProduct(inputs...);
    }

    return result;
  }

 private:
  [[nodiscard]] static constexpr auto EvaluateLeftMatCellValue(
      const Container2D auto &...inputs) {
    return LeftMat::template Evaluate<
        RowIndex, ProductIndex,
        InputIndex - RightMat::kNumMats>(inputs...);
  }

  [[nodiscard]] static constexpr auto EvaluateRightMatCellValue(
      const Container2D auto &...inputs) {
    return RightMat::template Evaluate<
        ProductIndex, ColIndex, InputIndex>(inputs...);
  }

  [[nodiscard]] static constexpr auto EvaluateCurrentProduct(
      const Container2D auto &...inputs) {
    return EvaluateLeftMatCellValue(inputs...) *
           EvaluateRightMatCellValue(inputs...);
  }

  [[nodiscard]] static constexpr auto EvaluateNextProduct(
      const Container2D auto &...inputs) {
    return MatProductEvaluator<LeftMat, RightMat, RowIndex, ColIndex,
                               InputIndex,
                               ProductIndex - 1>::Evaluate(inputs...);
  }
};

}

#endif  // STONKS_CTMM_MAT_PRODUCT_EVALUATOR_H_
