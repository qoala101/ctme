#ifndef CTME_EVALUATE_TO_ARRAY_H_
#define CTME_EVALUATE_TO_ARRAY_H_

#include <array>

#include "ctme_concepts.h"  // IWYU pragma: keep
#include "ctme_evaluate_to_container.h"
#include "ctme_result_traits.h"

namespace ctme {
/**
 * @brief Evaluates the matrix expression to array of arrays.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 * @param input_values 2D containers with values readable
 * by [unsigned][unsigned]. Amount must be equal to the amount of matrices
 * used to define the expression.
 * @return Array of arrays. Value type is defined by the input values.
 */
template <MatExpression Expression>
constexpr auto EvaluateToArray
    [[nodiscard]] (const MatValues auto &...input_values) {
  using ResultTraits = decltype(GetResultTraits<Expression>(input_values...));

  auto result_values = std::array<
      std::array<typename ResultTraits::ValueType, ResultTraits::kNumCols>,
      ResultTraits::kNumRows>{};

  EvaluateTo<Expression>(result_values, input_values...);
  return result_values;
}

/**
 * @copydoc EvaluateToArray<Expression>
 * @param expression Defines the type of the evaluated expression.
 */
constexpr auto EvaluateToArray
    [[nodiscard]] (const MatExpression auto &expression,
                   const MatValues auto &...input_values) {
  return EvaluateToArray<std::decay_t<decltype(expression)>>(input_values...);
}
}  // namespace ctme

#endif  // CTME_EVALUATE_TO_ARRAY_H_
