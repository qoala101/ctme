/**
 * CTME @link https://github.com/qoala101/ctme @endlink
 * @author Volodymyr Hromakov (4y5t6r@gmail.com)
 * @copyright Copyright (c) 2023, MIT License
 */

#include <gtest/gtest.h>

#include <array>
#include <type_traits>
#include <vector>

#include "ctme_evaluate_cell.h"
#include "ctme_mat.h"

namespace {
TEST(Mat, EvaluateCell) {
  constexpr auto expression = ctme::Mat<1, 1>{};
  constexpr auto values = std::array<std::array<int, 1>, 1>{{5}};
  constexpr auto result = ctme::EvaluateCell<0, 0>(expression, values);

  EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(result)>, int>));
  EXPECT_EQ(result, 5);
}
}  // namespace