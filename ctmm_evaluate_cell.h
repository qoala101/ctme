#ifndef CTMM_EVALUATE_CELL_H_
#define CTMM_EVALUATE_CELL_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep

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
[[nodiscard]] constexpr auto EvaluateCell(
    const MatValues auto &...input_values) {
  return Expression::template EvaluateCell<RowIndex, CellIndex,
                                       sizeof...(input_values) - 1>(
      input_values...);
}

/**
 * @copydoc EvaluateCell<Expression, unsigned, unsigned>
 * @param expression Defines the type of the evaluated expression.
 */
template <unsigned RowIndex, unsigned CellIndex>
[[nodiscard]] constexpr auto EvaluateCell(
    const MatExpression auto &expression,
    const MatValues auto &...input_values) {
  return EvaluateCell<std::decay_t<decltype(expression)>, RowIndex, CellIndex>(
      input_values...);
}
}  // namespace ctmm

#endif  // CTMM_EVALUATE_CELL_H_
