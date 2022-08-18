#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "ctme_mat.h"
#include "ctme_mat_product.h"
#include "ctme_result_traits.h"

namespace {
TEST(ResultTraits, SizeOfMat) {
  constexpr auto values = std::array<std::array<int, 0>, 0>{};

  using ResultTraits =
      decltype(ctme::GetResultTraits<ctme::Mat<10, 3>>(values));

  EXPECT_EQ(ResultTraits::kNumRows, 10);
  EXPECT_EQ(ResultTraits::kNumCols, 3);
}

TEST(ResultTraits, SizeOfExpression) {
  constexpr auto values_1 = std::array<std::array<int, 0>, 0>{};
  constexpr auto values_2 = std::array<std::array<int, 0>, 0>{};

  constexpr auto expression = ctme::Mat<10, 3>{} * ctme::Mat<3, 20>{};
  using ResultTraits =
      decltype(ctme::GetResultTraits(expression, values_1, values_2));

  EXPECT_EQ(ResultTraits::kNumRows, 10);
  EXPECT_EQ(ResultTraits::kNumCols, 20);
}

TEST(ResultTraits, InfFloatTypesOrder) {
  constexpr auto values_int = std::array<std::array<int, 0>, 0>{};
  constexpr auto values_float = std::array<std::array<float, 0>, 0>{};

  constexpr auto expression = ctme::Mat<10, 3>{} * ctme::Mat<3, 20>{};
  using IntFloatTraits =
      decltype(ctme::GetResultTraits(expression, values_int, values_float));
  using FloatIntTraits =
      decltype(ctme::GetResultTraits(expression, values_float, values_int));

  EXPECT_TRUE((std::is_same_v<IntFloatTraits::ValueType, float>));
  EXPECT_TRUE((std::is_same_v<FloatIntTraits::ValueType, float>));
}

TEST(ResultTraits, InfInt64TypesOrder) {
  constexpr auto values_int = std::array<std::array<int, 0>, 0>{};
  constexpr auto values_int64 = std::array<std::array<int64_t, 0>, 0>{};

  constexpr auto expression = ctme::Mat<10, 3>{} * ctme::Mat<3, 20>{};
  using IntInt64Traits =
      decltype(ctme::GetResultTraits(expression, values_int, values_int64));
  using Int64IntTraits =
      decltype(ctme::GetResultTraits(expression, values_int64, values_int));

  EXPECT_TRUE((std::is_same_v<IntInt64Traits::ValueType, int64_t>));
  EXPECT_TRUE((std::is_same_v<Int64IntTraits::ValueType, int64_t>));
}

TEST(ResultTraits, InfInt64FloatDoubleTypes) {
  constexpr auto values_int = std::array<std::array<int, 0>, 0>{};
  constexpr auto values_int64 = std::array<std::array<int64_t, 0>, 0>{};
  constexpr auto values_float = std::array<std::array<float, 0>, 0>{};
  constexpr auto values_double = std::array<std::array<double, 0>, 0>{};

  constexpr auto expression = ctme::Mat<1, 1>{} * ctme::Mat<1, 1>{} *
                              ctme::Mat<1, 1>{} * ctme::Mat<1, 1>{};
  using OrderedTraits = decltype(ctme::GetResultTraits(
      expression, values_int, values_int64, values_float, values_double));
  using ReversedTraits = decltype(ctme::GetResultTraits(
      expression, values_double, values_float, values_int64, values_int));

  EXPECT_TRUE((std::is_same_v<OrderedTraits::ValueType, double>));
  EXPECT_TRUE((std::is_same_v<ReversedTraits::ValueType, double>));
}
}  // namespace