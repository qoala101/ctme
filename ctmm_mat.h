#ifndef STONKS_CTMM_MAT_H_
#define STONKS_CTMM_MAT_H_

#include <array>
#include <tuple>

#include "ctmm_concepts.h"  // IWYU pragma: keep
#include "ctmm_matrix_evaluator.h"

namespace ctmm {
/**
 * @brief Plain 2D matrix.
 */
template <unsigned NumRows, unsigned NumCols>
class Mat {
  static_assert(NumRows > 0);
  static_assert(NumCols > 0);

 public:
  static constexpr unsigned kNumRows = NumRows;
  static constexpr unsigned kNumCols = NumCols;
  static constexpr unsigned kNumMats = 1;
  
  template <unsigned RowIndex, unsigned ColIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const Container2D auto &...inputs) {
    return Evaluate<RowIndex, ColIndex, sizeof...(inputs) - 1>(inputs...);
  }

  template <unsigned RowIndex, unsigned ColIndex, unsigned InputIndex>
  [[nodiscard]] static constexpr auto Evaluate(
      const Container2D auto &...inputs) {
    return std::get<InputIndex>(std::tie(inputs...))[RowIndex][ColIndex];
  }

  // [[nodiscard]] static constexpr auto Evaluate(
  //     const Container2D auto &...inputs) {
  //   using ResultType = decltype(Evaluate<0, 0>(inputs...));

  //   auto result = std::array<std::array<ResultType, kNumCols>, kNumRows>{};

  //   MatrixEvaluator<Mat<NumRows, NumCols>, kNumRows - 1,
  //                   kNumCols - 1>::Evaluate(result, inputs...);

  //   return result;
  // }

  static_assert(MatExpression<Mat>);
};
}  // namespace ctmm

#endif  // STONKS_CTMM_MAT_H_
