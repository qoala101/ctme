#ifndef STONKS_CTMM_CELL_EVALUATOR_H_
#define STONKS_CTMM_CELL_EVALUATOR_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep

namespace ctmm {
template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex,
          int ColIndex, int InputIndex, int ProductIndex>
class CellEvaluator {
 public:
  template <typename... Inputs>
  [[nodiscard]] static constexpr auto Evaluate(const Inputs &...inputs) {
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

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto EvaluateLeftMatCellValue(
      const Inputs &...inputs) {
    return LeftMat::template Evaluate<RowIndex, ProductIndex,
                                      InputIndex - RightMat::kNumInputs>(
        inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto EvaluateRightMatCellValue(
      const Inputs &...inputs) {
    return RightMat::template Evaluate<ProductIndex, ColIndex, InputIndex>(
        inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto EvaluateCurrentProduct(
      const Inputs &...inputs) {
    return EvaluateLeftMatCellValue(inputs...) *
           EvaluateRightMatCellValue(inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto EvaluateNextProduct(
      const Inputs &...inputs) {
    return CellEvaluator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                         ProductIndex - 1>::Evaluate(inputs...);
  }
};

}  // namespace ctmm

#endif  // STONKS_CTMM_CELL_EVALUATOR_H_
