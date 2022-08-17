#ifndef CTMM_MAT_TRAITS_EVALUATE_H_
#define CTMM_MAT_TRAITS_EVALUATE_H_

#include "ctmm_concepts.h"
#include "ctmm_mat_traits_size.h"
#include "ctmm_cell_evaluator.h"
#include "ctmm_matrix_evaluator.h"

namespace ctmm {
template <int, int>
class Mat;

template <concepts::Mat, concepts::Mat>
class MatProduct;

namespace mat_traits {
template <concepts::Mat T>
class Evaluator;

template <int NumRows, int NumCols>
class Evaluator<Mat<NumRows, NumCols>> {
 public:
  template <int RowIndex, int ColIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    return Evaluate<RowIndex, ColIndex, 0>(inputs...);
  }

  template <int RowIndex, int ColIndex, int InputIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    return std::get<InputIndex>(std::tie(inputs...))[RowIndex][ColIndex];
  }

  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    using ResultType = decltype(Evaluate<0, 0>(inputs...));

    auto result = std::array<std::array<ResultType, Traits::kNumCols>, Traits::kNumRows>{};

    MatrixEvaluator<Mat<NumRows, NumCols>, Traits::kNumRows - 1, Traits::kNumCols - 1>::Evaluate(result,
                                                               inputs...);

    return result;
  }

  using Traits = mat_traits::Size<Mat<NumRows, NumCols>>;
};


template <concepts::Mat LeftMat, concepts::Mat RightMat>
class Evaluator<MatProduct<LeftMat, RightMat>> {
 public:
  template <int RowIndex, int ColIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    return Evaluate<RowIndex, ColIndex, sizeof...(inputs) - 1>(inputs...);
  }

  template <int RowIndex, int ColIndex, int InputIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    return SCellEvaluator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                         mat_traits::Size<LeftMat>::kNumCols - 1>::Evaluate(inputs...);
  }

  [[nodiscard]] static constexpr auto Evaluate(
      const concepts::Input auto &...inputs) {
    using ResultType = decltype(Evaluate<0, 0>(inputs...));

    auto result = std::array<std::array<ResultType, Traits::kNumCols>, Traits::kNumRows>{};

    MatrixEvaluator<MatProduct<LeftMat, RightMat>, Traits::kNumRows - 1,
                    Traits::kNumCols - 1>::Evaluate(result, inputs...);

    return result;
  }
  
  using Traits = mat_traits::Size<MatProduct<LeftMat, RightMat>>;
};
}  // namespace mat_traits
}  // namespace ctmm

#endif  // CTMM_MAT_TRAITS_EVALUATE_H_
