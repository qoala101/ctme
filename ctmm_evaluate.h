#ifndef CTMM_EVALUATION_H_
#define CTMM_EVALUATION_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep

namespace ctmm {
/**
 * @brief Evaluates a single cell value of the matrix expression.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 * Produced by combination of operations applied to the @link Mats @endlink.
 *
 * @param inputs 2D containers with values accessible by [unsigned][unsigned].
 * Amount should be equal to the amount of @link Mats @endlink used
 * to define the expression.
 *
 * @return Cell value of the matrix produced by the evaluation of the expression
 * with the given inputs. Value type is defined by the inputs.
 */
// template <MatExpression Expression, unsigned RowIndex, unsigned CellIndex>
// [[nodiscard]] constexpr auto Evaluate(const Container2D auto &...inputs) {
//   return Expression::template Evaluate<RowIndex, CellIndex>(inputs...);
// }

/**
 * @copydoc Evaluate<MatExpression, unsigned, unsigned>
 */
template <unsigned RowIndex, unsigned CellIndex>
[[nodiscard]] constexpr auto Evaluate(const MatExpression auto &expression,
                                      const Container2D auto &...inputs) {
  return std::decay_t<decltype(expression)>::template Evaluate<RowIndex,
                                                               CellIndex>(
      inputs...);
}

/**
 * @brief Evaluates the matrix expression.
 *
 * @tparam Expression Type of the matrix expression to be evaluated.
 * Produced by combination of operations applied to the @link Mats @endlink.
 *
 * @param inputs 2D containers with values accessible by [unsigned][unsigned].
 * Amount should be equal to the amount of @link Mats @endlink used
 * to define the expression.
 *
 * @return Matrix produced by the evaluation of the expression
 * with the given inputs. Value type is defined by the inputs.
 */
// template <MatExpression Expression>
// [[nodiscard]] constexpr auto Evaluate(const Container2D auto &...inputs) {
//   return Expression::Evaluate(inputs...);
// }

/**
 * @copydoc Evaluate<MatExpression>
 */
// [[nodiscard]] constexpr auto Evaluate(const MatExpression auto &expression,
//                                       const Container2D auto &...inputs) {
//   return Evaluate<std::decay_t<decltype(expression)>>(inputs...);
// }
}  // namespace ctmm

#endif  // STONKS_CTMM_EVALUATION_H_
