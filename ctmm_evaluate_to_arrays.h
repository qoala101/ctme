#ifndef CTMM_EVALUATE_AS_ARRAY_H_
#define CTMM_EVALUATE_AS_ARRAY_H_

#include <array>

#include "ctmm_concepts.h"  // IWYU pragma: keep
#include "ctmm_evaluate.h"
#include "ctmm_result_traits.h"

namespace ctmm {
/**
 * @brief Evaluates the matrix expression to array of arrays.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 *
 * @param input_values 2D containers with values readable
 * by [unsigned][unsigned]. Amount must be equal to the amount of matrices
 * used to define the expression.
 *
 * @return Array of arrays. Value type is defined by the input values.
 */
template <MatExpression Expression>
[[nodiscard]] constexpr auto EvaluateToArrays(
    const MatValues auto &...input_values) {
  using ResultTraits = decltype(GetResultTraits<Expression>(input_values...));

  auto result_values = std::array<
      std::array<typename ResultTraits::ValueType, ResultTraits::kNumCols>,
      ResultTraits::kNumRows>{};

  Evaluate<Expression>(result_values, input_values...);
  return result_values;
}

/**
 * @copydoc EvaluateToArrays<Expression>
 * @param expression Defines the type of the evaluated expression.
 */
[[nodiscard]] constexpr auto EvaluateToArrays(
    const MatExpression auto &expression,
    const MatValues auto &...input_values) {
  return EvaluateToArrays<std::decay_t<decltype(expression)>>(input_values...);
}
}  // namespace ctmm

#endif  // CTMM_EVALUATE_AS_ARRAY_H_
