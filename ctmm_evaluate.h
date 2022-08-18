#ifndef CTMM_EVALUATION_H_
#define CTMM_EVALUATION_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep
#include "ctmm_matrix_evaluator.h"

namespace ctmm {
/**
 * @brief Evaluates a single cell of the matrix expression.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 *
 * @param input_values 2D containers with values readable
 * by [unsigned][unsigned]. Amount must be equal to the amount of matrices
 * used to define the expression.
 *
 * @return Cell value of the matrix produced by the evaluation of the expression
 * with the given input values. Type is defined by the values.
 */
template <MatExpression Expression, unsigned RowIndex, unsigned CellIndex>
[[nodiscard]] constexpr auto Evaluate(const MatValues auto &...input_values) {
  return Expression::template Evaluate<RowIndex, CellIndex,
                                       sizeof...(input_values) - 1>(
      input_values...);
}

/**
 * @copydoc Evaluate<Expression, unsigned, unsigned>
 * @param expression Defines the type of the evaluated expression.
 */
template <unsigned RowIndex, unsigned CellIndex>
[[nodiscard]] constexpr auto Evaluate(const MatExpression auto &expression,
                                      const MatValues auto &...input_values) {
  return Evaluate<std::decay_t<decltype(expression)>, RowIndex, CellIndex>(
      input_values...);
}

/**
 * @brief Evaluates the matrix expression and writes results
 * to the provided 2D container. Can be used to fill non-constexpr containers.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 *
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
 *   Evaluate<Expression>(result_values, a_values, b_values, c_values);
 * @endcode
 *
 * @param input_values 2D containers with values readable
 * by [unsigned][unsigned]. Amount must be equal to the amount of matrices
 * used to define the expression.
 */
template <MatExpression Expression>
void Evaluate(MatValues auto &result_values,
              const MatValues auto &...input_values) {
  return MatrixEvaluator<Expression, Expression::kNumRows - 1,
                         Expression::kNumCols - 1>::Evaluate(result_values,
                                                             input_values...);
}

/**
 * @copydoc Evaluate<Expression>
 * @param expression Defines the type of the evaluated expression.
 */
void Evaluate(const MatExpression auto &expression,
              MatValues auto &result_values,
              const MatValues auto &...input_values) {
  return Evaluate<std::decay_t<decltype(expression)>>(result_values,
                                                      input_values...);
}
}  // namespace ctmm

#endif  // STONKS_CTMM_EVALUATION_H_
