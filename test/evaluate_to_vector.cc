#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <vector>

#include "ctme_evaluate_to_vector.h"
#include "ctme_mat.h"
#include "ctme_mat_product.h"

namespace {
TEST(EvaluateToVector, MixedInputs) {
  constexpr auto expression = ctme::Mat<2, 3>{} * ctme::Mat<3, 2>{};

  constexpr auto values_2_3 = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, {14, 15, 16}};
  const auto values_3_2 = std::vector<std::vector<int64_t>>{
      std::vector<int64_t>{21, 22}, {23, 24}, {25, 26}};

  const auto result =
      ctme::EvaluateToVector(expression, values_2_3, values_3_2);

  const auto expected_result = std::vector<std::vector<int64_t>>{
      std::vector<int64_t>{832, 868}, {1039, 1084}};

  EXPECT_EQ(result, expected_result);
}
}  // namespace