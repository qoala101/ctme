#include <gtest/gtest.h>

#include <array>
#include <type_traits>
#include <vector>

#include "ctme_evaluate_cell.h"
#include "ctme_mat.h"

namespace {
TEST(EvaluateCell, TypeSameAsObject) {
  using Expression = ctme::Mat<1, 1>;
  constexpr auto expression = ctme::Mat<1, 1>{};
  constexpr auto values = std::array<std::array<int, 1>, 1>{{5}};

  constexpr auto type_result = ctme::EvaluateCell<Expression, 0, 0>(values);
  constexpr auto object_result = ctme::EvaluateCell<0, 0>(expression, values);

  EXPECT_TRUE((std::is_same_v<decltype(type_result), decltype(object_result)>));
  EXPECT_EQ(type_result, object_result);
}
}  // namespace