#ifndef STONKS_CTMM_EVALUATION_H_
#define STONKS_CTMM_EVALUATION_H_

#include "ctmm_concepts.h"
#include "ctmm_mat_traits_evaluator.h"

namespace ctmm {
template <concepts::Mat MatType, int RowIndex, int CellIndex>
[[nodiscard]] constexpr auto Evaluate(const concepts::Input auto &...inputs) {
  return mat_traits::Evaluator<MatType>::template Evaluate<RowIndex, CellIndex>(
      inputs...);
}

template <int RowIndex, int CellIndex>
[[nodiscard]] constexpr auto Evaluate(const concepts::Mat auto &mat,
                                      const concepts::Input auto &...inputs) {
  return Evaluate<std::decay_t<decltype(mat)>, RowIndex, CellIndex>(inputs...);
}

template <concepts::Mat MatType>
[[nodiscard]] constexpr auto Evaluate(const concepts::Input auto &...inputs) {
  return mat_traits::Evaluator<MatType>::Evaluate(inputs...);
}

[[nodiscard]] constexpr auto Evaluate(const concepts::Mat auto &mat,
                                      const concepts::Input auto &...inputs) {
  return Evaluate<std::decay_t<decltype(mat)>>(inputs...);
}
}  // namespace ctmm

#endif  // STONKS_CTMM_EVALUATION_H_
