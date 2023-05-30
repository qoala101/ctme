/**
 * CTME @link https://github.com/qoala101/ctme @endlink
 * @author Volodymyr Hromakov (4y5t6r@gmail.com)
 * @copyright Copyright (c) 2023, MIT License
 */

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "ctme_evaluate_cell.h"
#include "ctme_evaluate_to_array.h"
#include "ctme_mat.h"
#include "ctme_mat_sum.h"

namespace {
TEST(MatSum, ArrayAndVector) {
  constexpr auto expression = ctme::Mat<1, 1>{} + ctme::Mat<1, 1>{};
  constexpr auto values_array = std::array<std::array<int, 1>, 1>{{5}};
  const auto values_vector = std::vector<std::vector<int64_t>>{{10}};
  const auto result =
      ctme::EvaluateCell<0, 0>(expression, values_array, values_vector);

  EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(result)>, int64_t>));
  EXPECT_EQ(result, 15);
}

TEST(MatSum, ExpressionOfExpressions) {
  constexpr auto left_expression = ctme::Mat<2, 3>{} + ctme::Mat<2, 3>{};
  constexpr auto right_expression = ctme::Mat<2, 3>{} + ctme::Mat<2, 3>{};
  constexpr auto expression_of_expressions = left_expression + right_expression;

  constexpr auto values1 = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, {14, 15, 16}};
  constexpr auto values2 = std::array<std::array<float, 3>, 2>{
      std::array<float, 3>{21.1, 22.1, 23.1}, {24.1, 25.1, 26.1}};
  constexpr auto values3 = std::array<std::array<double, 4>, 2>{
      std::array<double, 4>{31.1, 32.1, 33.1}, {34.1, 35.1, 36.1}};
  constexpr auto values4 = std::array<std::array<int64_t, 4>, 4>{
      std::array<int64_t, 4>{1, 0, 0}, {0, 1, 0}};

  constexpr auto result = ctme::EvaluateToArray(
      expression_of_expressions, values1, values2, values3, values4);

  EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(result[0][0])>, double>));
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result[0].size(), 3);
  EXPECT_NEAR(result[0][0], 64, 1);
  EXPECT_NEAR(result[0][1], 66, 1);
  EXPECT_NEAR(result[0][2], 69, 1);
  EXPECT_NEAR(result[1][0], 72, 1);
  EXPECT_NEAR(result[1][1], 76, 1);
  EXPECT_NEAR(result[1][2], 78, 1);
}
}  // namespace