#ifndef CTME_EVALUATE_TO_VECTOR_H_
#define CTME_EVALUATE_TO_VECTOR_H_

#include <vector>

#include "ctme_concepts.h"  // IWYU pragma: keep
#include "ctme_evaluate_to_container.h"
#include "ctme_result_traits.h"

namespace ctme {
/**
 * @brief Evaluates the matrix expression to vector of vectors.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 * @param input_values 2D containers with values readable
 * by [unsigned][unsigned]. Amount must be equal to the amount of matrices
 * used to define the expression.
 * @return Vector of vectors. Value type is defined by the input values.
 */
template <MatExpression Expression>
constexpr auto EvaluateToVector
    [[nodiscard]] (const MatValues auto &...input_values) {
  using ResultTraits = decltype(GetResultTraits<Expression>(input_values...));
  using ValueType = typename ResultTraits::ValueType;

  auto result_values = std::vector<std::vector<ValueType>>(
      ResultTraits::kNumRows, std::vector<ValueType>(ResultTraits::kNumCols));

  EvaluateTo<Expression>(result_values, input_values...);
  return result_values;
}

/**
 * @copydoc EvaluateToVector<Expression>
 * @param expression Defines the type of the evaluated expression.
 */
constexpr auto EvaluateToVector
    [[nodiscard]] (const MatExpression auto &expression,
                   const MatValues auto &...input_values) {
  return EvaluateToVector<std::decay_t<decltype(expression)>>(input_values...);
}
}  // namespace ctme

#endif  // CTME_EVALUATE_TO_VECTOR_H_
