/**
 * CTME @link https://github.com/qoala101/ctme @endlink
 * @author Volodymyr Hromakov (4y5t6r@gmail.com)
 * @copyright Copyright (c) 2023, MIT License
 */

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <vector>

#include "ctme_evaluate_to_array.h"
#include "ctme_mat.h"
#include "ctme_mat_product.h"

namespace {
TEST(EvaluateToArray, CompileTime) {
  constexpr auto expression = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};

  constexpr auto values_2_3 = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, {14, 15, 16}};
  constexpr auto values_3_2 = std::array<std::array<int64_t, 2>, 3>{
      std::array<int64_t, 2>{21, 22}, {23, 24}, {25, 26}};

  constexpr auto result =
      ctme::EvaluateToArray(expression, values_2_3, values_3_2);

  constexpr auto expected_result = std::array<std::array<int64_t, 2>, 2>{
      std::array<int64_t, 2>{832, 868}, {1039, 1084}};

  EXPECT_EQ(result, expected_result);
}

TEST(EvaluateToArray, RunTime) {
  constexpr auto expression = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};

  const auto values_2_3 =
      std::vector<std::vector<int>>{std::vector<int>{11, 12, 13}, {14, 15, 16}};
  const auto values_3_2 = std::vector<std::vector<int64_t>>{
      std::vector<int64_t>{21, 22}, {23, 24}, {25, 26}};

  const auto result = ctme::EvaluateToArray(expression, values_2_3, values_3_2);

  constexpr auto expected_result = std::array<std::array<int64_t, 2>, 2>{
      std::array<int64_t, 2>{832, 868}, {1039, 1084}};

  EXPECT_EQ(result, expected_result);
}

TEST(EvaluateToArray, MixedInputs) {
  constexpr auto expression = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};

  constexpr auto values_2_3 = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, {14, 15, 16}};
  const auto values_3_2 = std::vector<std::vector<int64_t>>{
      std::vector<int64_t>{21, 22}, {23, 24}, {25, 26}};

  const auto result = ctme::EvaluateToArray(expression, values_2_3, values_3_2);

  constexpr auto expected_result = std::array<std::array<int64_t, 2>, 2>{
      std::array<int64_t, 2>{832, 868}, {1039, 1084}};

  EXPECT_EQ(result, expected_result);
}
}  // namespace