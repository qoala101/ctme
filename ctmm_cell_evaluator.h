#ifndef STONKS_CTMM_CELL_EVALUATOR_H_
#define STONKS_CTMM_CELL_EVALUATOR_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep
#include "ctmm_impl.h"

namespace ctmm {
template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex,
          int ColIndex, int InputIndex, int ProductIndex>
class CellEvaluator {
 public:
  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    auto result = EvaluateCurrentProduct(inputs...);

    if constexpr (ProductIndex > 0) {
      result += EvaluateNextProduct(inputs...);
    }

    return result;
  }

 private:
  template <concepts::Mat, concepts::Mat, int, int>
  friend class ExprCell;

  template <concepts::Mat, concepts::Mat, int, int, int, int>
  friend class CellEvaluator;

  [[nodiscard]] static constexpr auto EvaluateLeftMatCellValue(
      const concepts::Input auto &...inputs) {
    return LeftMat::template Evaluate<RowIndex, ProductIndex,
                                      InputIndex - MatTrait<RightMat>::kNumInputs>(
        inputs...);
  }

  [[nodiscard]] static constexpr auto EvaluateRightMatCellValue(
      const concepts::Input auto &...inputs) {
    return RightMat::template Evaluate<ProductIndex, ColIndex, InputIndex>(
        inputs...);
  }

  [[nodiscard]] static constexpr auto EvaluateCurrentProduct(
      const concepts::Input auto &...inputs) {
    return EvaluateLeftMatCellValue(inputs...) *
           EvaluateRightMatCellValue(inputs...);
  }

  [[nodiscard]] static constexpr auto EvaluateNextProduct(
      const concepts::Input auto &...inputs) {
    return CellEvaluator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                         ProductIndex - 1>::Evaluate(inputs...);
  }
};

}  // namespace ctmm

#endif  // STONKS_CTMM_CELL_EVALUATOR_H_
