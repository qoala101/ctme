#ifndef STONKS_CTMM_MAT_PRODUCT_H_
#define STONKS_CTMM_MAT_PRODUCT_H_

#include <array>
#include <tuple>

#include "ctmm_concepts.h"
#include "ctmm_mat_product_evaluator.h"
#include "ctmm_matrix_evaluator.h"

namespace ctmm {
/**
 * @brief Multiplication product of two 2D matrices.
 */
template <MatExpression LeftMat, MatExpression RightMat>
class MatProduct {
  static_assert(LeftMat::kNumCols == RightMat::kNumRows);

 public:
  static constexpr unsigned kNumRows = LeftMat::kNumRows;
  static constexpr unsigned kNumCols = RightMat::kNumCols;
  static constexpr unsigned kNumMats = LeftMat::kNumMats + RightMat::kNumMats;

  template <unsigned RowIndex, unsigned ColIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const Container2D auto &...inputs) {
    return Evaluate<RowIndex, ColIndex, sizeof...(inputs) - 1>(inputs...);
  }

  template <unsigned RowIndex, unsigned ColIndex, unsigned InputIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const Container2D auto &...inputs) {
    return MatProductEvaluator<LeftMat, RightMat, RowIndex, ColIndex,
                               InputIndex,
                               LeftMat::kNumCols - 1>::Evaluate(inputs...);
  }

  // [[nodiscard]] static constexpr auto Evaluate(
  //     const Container2D auto &...inputs) {
  //   using ResultType = decltype(Evaluate<0, 0>(inputs...));

  //   auto result = std::array<std::array<ResultType, kNumCols>, kNumRows>{};

  //   MatrixEvaluator<MatProduct<LeftMat, RightMat>, kNumRows - 1,
  //                   kNumCols - 1>::Evaluate(result, inputs...);

  //   return result;
  // }

  static_assert(MatExpression<MatProduct>);
};

/**
 * @brief Produces an object of type representing the matrix product.
 */
[[nodiscard]] constexpr auto operator*(const MatExpression auto &left_mat,
                                       const MatExpression auto &right_mat)
    -> MatExpression auto{
  return MatProduct<std::decay_t<decltype(left_mat)>,
                    std::decay_t<decltype(right_mat)>>{};
}
}  // namespace ctmm

#endif  // STONKS_CTMM_MAT_PRODUCT_H_
