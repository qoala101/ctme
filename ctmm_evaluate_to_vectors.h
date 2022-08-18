#ifndef CTMM_EVALUATE_AS_VECTOR_H_
#define CTMM_EVALUATE_AS_VECTOR_H_

#include <vector>

#include "ctmm_concepts.h"  // IWYU pragma: keep
#include "ctmm_evaluate.h"
#include "ctmm_result_traits.h"

namespace ctmm {
/**
 * @brief Evaluates the matrix expression to vector of vectors.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 *
 * @param input_values 2D containers with values readable
 * by [unsigned][unsigned]. Amount must be equal to the amount of matrices
 * used to define the expression.
 *
 * @return Vector of vectors. Value type is defined by the input values.
 */
template <MatExpression Expression>
[[nodiscard]] constexpr auto EvaluateToVectors(
    const MatValues auto &...input_values) {
  using ResultTraits = decltype(GetResultTraits<Expression>(input_values...));

  auto result_values =
      std::vector<std::vector<typename ResultTraits::ValueType>>(
          ResultTraits::kNumRows);

  for (auto &row : result_values) {
    row.resize(ResultTraits::kNumCols);
  }

  Evaluate<Expression>(result_values, input_values...);
  return result_values;
}

/**
 * @copydoc EvaluateToVectors<Expression>
 * @param expression Defines the type of the evaluated expression.
 */
[[nodiscard]] constexpr auto EvaluateToVectors(
    const MatExpression auto &expression,
    const MatValues auto &...input_values) {
  return EvaluateToVectors<std::decay_t<decltype(expression)>>(input_values...);
}
}  // namespace ctmm

#endif  // CTMM_EVALUATE_AS_VECTOR_H_
