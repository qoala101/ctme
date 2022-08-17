#ifndef CTMM_H_
#define CTMM_H_

#include "ctmm_evaluate.h"
#include "ctmm_mat.h"
#include "ctmm_mat_product.h"

/**
 * @brief
 * @details
 * 1. Multiplied matrices form an expression:
 * @code
 *   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{} * Mat<4, 2>{};
 * @endcode
 *
 * 2. Expression is a matrix itself, so they can be multiplied as well:
 * @code
 *   constexpr auto expression = expression1 * Mat<4, 2>{} * expression2;
 * @endcode
 *
 * 3. Multiplying matrices of wrong dimensions produces compile-time error:
 * @code
 *   constexpr auto expression1 = Mat<2, 3>{} * Mat<3, 2>{};  // OK
 *   constexpr auto expression2 = expression1 * Mat<4, 2>{};  // OK
 *   constexpr auto expression3 = Mat<2, 3>{} * Mat<3, 1>{};  // Error
 *   constexpr auto expression4 = expression1 * Mat<4, 1>{};  // Error
 * @endcode
 *
 * 4. In order to evaluate an expression, you must provide the inputs for each
 * matrix:
 * @code
 *   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{} * Mat<4, 2>{};
 *   constexpr auto result = decltype(expression)::Evaluate(values1, values2,
 *   values3);
 * @endcode
 *
 * 5. Inputs are anything which supports syntax [unsigned][unsigned] to get the cell
 * value. Values must support operator* for each other:
 * @code
 *   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{} * Mat<4, 2>{};
 *   constexpr auto values1 = std::array<std::array<3, int>>{};
 *   const auto values2 = std::vector<std::vector<float>>({1, 2}, {3, 4}, {5,
 *   6});
 *   constexpr auto values3 = double[4][2];
 *   const auto result = decltype(expression)::Evaluate(values1, values2,
 *   values3);
 * @endcode
 *
 * 6. Providing wrong amount of inputs produces compile-time error:
 * @code
 *   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{};
 *   const auto result1 = decltype(expression)::Evaluate(values1, values2);  //
 *   OK
 *   const auto result2 = decltype(expression)::Evaluate(values1, values2,
 *   values3);  // Error
 *   const auto result3 = decltype(expression)::Evaluate(values1);  // Error
 * @endcode
 *
 * 7. If all inputs are constexpr, evaluation result is also constexpr:
 * @code
 *   const auto values = std::vector<std::vector<int>>{};
 *   const auto result = decltype(expression)::Evaluate(vectors1, vectors1);
 *   constexpr auto result = decltype(expression)::Evaluate(arrays1, arrays1);
 * @endcode
 *
 * 8. Cells can be evaluated one by one:
 * @code
 *   constexpr auto cell_0_0 = decltype(expression)::Evaluate<0, 0>(values1,
 *   values2);
 *   constexpr auto cell_0_1 = decltype(expression)::Evaluate<0, 1>(values1,
 *   values2);
 * @endcode
 *
 * 9. Evaluation logic is the property of the expression type, so you can
 * operate them without creating values:
 * @code
 *   using Expression = decltype(Mat<2, 3>{} * Mat<3, 2>{} * Mat<4, 2>{});
 *   constexpr auto result = Evaluate<Expression>(values1, values2, values3);
 *   constexpr auto cell_0_0 = Evaluate<Expression, 0, 0>(values1, values2,
 *   values3);
 * @endcode
 */

#endif  // CTMM_H_
