#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include "ctme_evaluate_to_array.h"
#include "ctme_evaluate_to_container.h"
#include "ctme_evaluate_to_vector.h"
#include "ctme_mat.h"
#include "ctme_mat_product.h"

namespace {
TEST(EvaluateToContainer, EvaluateToArray) {
  constexpr auto expression = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};

  constexpr auto values_2_3 = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, {14, 15, 16}};
  const auto values_3_2 = std::vector<std::vector<int64_t>>{
      std::vector<int64_t>{21, 22}, {23, 24}, {25, 26}};

  auto result = std::array<std::array<int64_t, 2>, 2>{};
  ctme::EvaluateTo(expression, result, values_2_3, values_3_2);

  const auto expected_result =
      ctme::EvaluateToArray(expression, values_2_3, values_3_2);

  EXPECT_EQ(result, expected_result);
}

TEST(EvaluateToContainer, EvaluateToVector) {
  constexpr auto expression = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};

  constexpr auto values_2_3 = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, {14, 15, 16}};
  const auto values_3_2 = std::vector<std::vector<int64_t>>{
      std::vector<int64_t>{21, 22}, {23, 24}, {25, 26}};

  auto result = std::vector<std::vector<int64_t>>{std::vector<int64_t>(2),
                                                  std::vector<int64_t>(2)};
  ctme::EvaluateTo(expression, result, values_2_3, values_3_2);

  const auto expected_result =
      ctme::EvaluateToVector(expression, values_2_3, values_3_2);

  EXPECT_EQ(result, expected_result);
}

TEST(EvaluateToContainer, EvaluateToDynamicArray) {
  constexpr auto expression = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};

  constexpr auto values_2_3 = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, {14, 15, 16}};
  const auto values_3_2 = std::vector<std::vector<int64_t>>{
      std::vector<int64_t>{21, 22}, {23, 24}, {25, 26}};

  auto result = std::unique_ptr<int64_t[][2]>{new int64_t[2][2]{}};
  ctme::EvaluateTo(expression, result, values_2_3, values_3_2);

  EXPECT_EQ(result[0][0], 832);
  EXPECT_EQ(result[0][1], 868);
  EXPECT_EQ(result[1][0], 1039);
  EXPECT_EQ(result[1][1], 1084);
}
}  // namespace