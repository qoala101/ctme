/**
 * CTME @link https://github.com/qoala101/ctme @endlink
 * @author Volodymyr Hromakov (4y5t6r@gmail.com)
 * @copyright Copyright (c) 2023, MIT License
 */

#ifndef VH_CTME_EVALUATE_CELL_H_
#define VH_CTME_EVALUATE_CELL_H_

#include "ctme_concepts.h"      // IWYU pragma: keep
#include "ctme_debug_logger.h"  // IWYU pragma: keep

namespace ctme {
/**
 * @brief Evaluates a single cell of the matrix expression.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 * @param input_values 2D containers with values readable
 * by [unsigned][unsigned]. Amount must be equal to the amount of matrices
 * used to define the expression.
 * @return Cell value of the matrix produced by the evaluation of the expression
 * with the given input values. Type is defined by the values.
 */
template <MatExpression Expression, unsigned RowIndex, unsigned ColIndex>
constexpr auto EvaluateCell
    [[nodiscard]] (const MatValues auto &...input_values) {
#ifdef CTME_DEBUG
  debug::Logger::Instance().PrintEvaluatingCell(RowIndex, ColIndex);
#endif  // CTME_DEBUG
  return Expression::template EvaluateCell<RowIndex, ColIndex,
                                           sizeof...(input_values) - 1>(
      input_values...);
}

/**
 * @copydoc EvaluateCell<Expression, unsigned, unsigned>
 * @param expression Defines the type of the evaluated expression.
 */
template <unsigned RowIndex, unsigned ColIndex>
constexpr auto EvaluateCell
    [[nodiscard]] (const MatExpression auto &expression,
                   const MatValues auto &...input_values) {
  return EvaluateCell<std::decay_t<decltype(expression)>, RowIndex, ColIndex>(
      input_values...);
}
}  // namespace ctme

#endif  // VH_CTME_EVALUATE_CELL_H_
