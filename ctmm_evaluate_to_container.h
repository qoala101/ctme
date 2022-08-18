#ifndef CTMM_EVALUATE_TO_2D_CONTAINER_H_
#define CTMM_EVALUATE_TO_2D_CONTAINER_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep
#include "ctmm_container_evaluator.h"

namespace ctmm {
/**
 * @brief Evaluates the matrix expression and writes results
 * to the provided 2D container. Can be used to fill containers in runtime.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 * @param result_values 2D container with values writable
 * by [unsigned][unsigned]. Size must be greater or equal to the size
 * of the matrix produced by the expression.
 * @remark Value type and size of the resulting matrix can be polled
 * via GetResultTraits in the following way:
 * @code
 *   using ResultTraits = decltype(GetResultTraits<Expression>(a_values,
 *   b_values, c_values));
 *
 *   auto result_values =
 *       std::array<std::array<ResultTraits::Type, ResultTraits::kNumCols>,
 *                  ResultTraits::kNumRows>{};
 *
 *   EvaluateCell<Expression>(result_values, a_values, b_values, c_values);
 * @endcode
 * @param input_values 2D containers with values readable
 * by [unsigned][unsigned]. Amount must be equal to the amount of matrices
 * used to define the expression.
 */
template <MatExpression Expression>
void EvaluateTo(MatValues auto &result_values,
                const MatValues auto &...input_values) {
  return details::ContainerEvaluator<Expression, Expression::kNumRows - 1,
                                     Expression::kNumCols -
                                         1>::EvaluateTo(result_values,
                                                        input_values...);
}

/**
 * @copydoc EvaluateTo<Expression>
 * @param expression Defines the type of the evaluated expression.
 */
void EvaluateTo(const MatExpression auto &expression,
                MatValues auto &result_values,
                const MatValues auto &...input_values) {
  return EvaluateTo<std::decay_t<decltype(expression)>>(result_values,
                                                        input_values...);
}
}  // namespace ctmm

#endif  // STONKS_CTMM_EVALUATE_TO_2D_CONTAINER_H_
