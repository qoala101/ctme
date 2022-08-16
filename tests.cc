#ifndef CTMM_TESTS_H_
#define CTMM_TESTS_H_

#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

#include "ctmm.h"

namespace ctmm::tests {
void Test2Vectors() {
  const auto a_values = std::vector<std::vector<int>>{
      std::vector<int>{11, 12, 13}, std::vector<int>{14, 15, 16}};
  const auto b_values = std::vector<std::vector<int>>{std::vector<int>{21, 22},
                                                      std::vector<int>{23, 24},
                                                      std::vector<int>{25, 26}};

  constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{};

  std::cout << expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values)
            << "\n";

  assert(expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values) == 832);
  assert(expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values) == 868);
  assert(expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values) == 1039);
  assert(expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values) == 1084);
}

void Test3Vectors() {
  const auto a_values = std::vector<std::vector<int>>{
      std::vector<int>{11, 12, 13}, std::vector<int>{14, 15, 16}};
  const auto b_values = std::vector<std::vector<int>>{std::vector<int>{21, 22},
                                                      std::vector<int>{23, 24},
                                                      std::vector<int>{25, 26}};
  const auto c_values = std::vector<std::vector<int>>{
      std::vector<int>{31, 32, 33, 34}, std::vector<int>{35, 36, 37, 38}};

  constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{} * Mat<2, 4>{};

  std::cout << expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<2>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<3>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<2>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<3>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";

  assert(expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values,
                                                   c_values) == 56172);
  assert(expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values,
                                                   c_values) == 57872);
  assert(expression.GetRow<0>().GetCol<2>().GetVal(a_values, b_values,
                                                   c_values) == 59572);
  assert(expression.GetRow<0>().GetCol<3>().GetVal(a_values, b_values,
                                                   c_values) == 61272);
  assert(expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values,
                                                   c_values) == 70149);
  assert(expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values,
                                                   c_values) == 72272);
  assert(expression.GetRow<1>().GetCol<2>().GetVal(a_values, b_values,
                                                   c_values) == 74395);
  assert(expression.GetRow<1>().GetCol<3>().GetVal(a_values, b_values,
                                                   c_values) == 76518);
}

void Test2Arrays() {
  constexpr auto a_values = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, std::array<int, 3>{14, 15, 16}};
  constexpr auto b_values = std::array<std::array<int, 2>, 3>{
      std::array<int, 2>{21, 22}, std::array<int, 2>{23, 24},
      std::array<int, 2>{25, 26}};

  constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{};

  std::cout << expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values)
            << "\n";

  static_assert(expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values) ==
                832);
  static_assert(expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values) ==
                868);
  static_assert(expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values) ==
                1039);
  static_assert(expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values) ==
                1084);
}

void Test3Arrays() {
  const auto a_values = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, std::array<int, 3>{14, 15, 16}};
  const auto b_values = std::array<std::array<int, 2>, 3>{
      std::array<int, 2>{21, 22}, std::array<int, 2>{23, 24},
      std::array<int, 2>{25, 26}};
  const auto c_values = std::array<std::array<int, 4>, 2>{
      std::array<int, 4>{31, 32, 33, 34}, std::array<int, 4>{35, 36, 37, 38}};

  constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{} * Mat<2, 4>{};

  std::cout << expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<2>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<3>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<2>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<3>().GetVal(a_values, b_values,
                                                         c_values)
            << "\n";

  assert(expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values,
                                                   c_values) == 56172);
  assert(expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values,
                                                   c_values) == 57872);
  assert(expression.GetRow<0>().GetCol<2>().GetVal(a_values, b_values,
                                                   c_values) == 59572);
  assert(expression.GetRow<0>().GetCol<3>().GetVal(a_values, b_values,
                                                   c_values) == 61272);
  assert(expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values,
                                                   c_values) == 70149);
  assert(expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values,
                                                   c_values) == 72272);
  assert(expression.GetRow<1>().GetCol<2>().GetVal(a_values, b_values,
                                                   c_values) == 74395);
  assert(expression.GetRow<1>().GetCol<3>().GetVal(a_values, b_values,
                                                   c_values) == 76518);
}

void Test1Vector1Array() {
  const auto a_values = std::vector<std::vector<int>>{
      std::vector<int>{11, 12, 13}, std::vector<int>{14, 15, 16}};
  constexpr auto b_values = std::array<std::array<int, 2>, 3>{
      std::array<int, 2>{21, 22}, std::array<int, 2>{23, 24},
      std::array<int, 2>{25, 26}};

  constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{};

  std::cout << expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values)
            << "\n";

  assert(expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values) == 832);
  assert(expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values) == 868);
  assert(expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values) == 1039);
  assert(expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values) == 1084);
}
}  // namespace ctmm::tests

auto main() -> int {
  std::cout << "TEST START\n";
  ctmm::tests::Test2Vectors();
  ctmm::tests::Test3Vectors();
  ctmm::tests::Test2Arrays();
  ctmm::tests::Test3Arrays();
  ctmm::tests::Test1Vector1Array();
  std::cout << "TEST END\n";
  return 0;
}

#endif  // CTMM_TESTS_H_
