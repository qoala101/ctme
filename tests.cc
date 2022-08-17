#ifndef CTMM_TESTS_H_
#define CTMM_TESTS_H_

#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

#include "ctmm.h"

namespace ctmm::tests {
void Test2VectorsInt() {
  const auto a_values = std::vector<std::vector<int>>{
      std::vector<int>{11, 12, 13}, std::vector<int>{14, 15, 16}};
  const auto b_values = std::vector<std::vector<int>>{std::vector<int>{21, 22},
                                                      std::vector<int>{23, 24},
                                                      std::vector<int>{25, 26}};

  using Expression = decltype(Mat<2, 3>{} * Mat<3, 2>{});

  auto value = 0;

  value = Expression::Evaluate<0, 0>(a_values, b_values);
  assert(value == 832);
  value = Expression::Evaluate<0, 1>(a_values, b_values);
  assert(value == 868);
  value = Expression::Evaluate<1, 0>(a_values, b_values);
  assert(value == 1039);
  value = Expression::Evaluate<1, 1>(a_values, b_values);
  assert(value == 1084);
}

// void Test2VectorsFloat() {
//   const auto a_values =
//       std::vector<std::vector<float>>{std::vector<float>{11.1, 12.1, 13.1},
//                                       std::vector<float>{14.1, 15.1, 16.1}};
//   const auto b_values = std::vector<std::vector<float>>{
//       std::vector<float>{21.1, 22.1}, std::vector<float>{23.1, 24.1},
//       std::vector<float>{25.1, 26.1}};

//   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{};

//   assert(expression.GetRow<0>().GetCol<0>().Evaluate(a_values,
//   b_values) >
//          842);
//   assert(expression.GetRow<0>().GetCol<0>().Evaluate(a_values,
//   b_values) <
//          843);
//   assert(expression.GetRow<0>().GetCol<1>().Evaluate(a_values,
//   b_values) >
//          878);
//   assert(expression.GetRow<0>().GetCol<1>().Evaluate(a_values,
//   b_values) <
//          879);
//   assert(expression.GetRow<1>().GetCol<0>().Evaluate(a_values,
//   b_values) >
//          1050);
//   assert(expression.GetRow<1>().GetCol<0>().Evaluate(a_values,
//   b_values) <
//          1051);
//   assert(expression.GetRow<1>().GetCol<1>().Evaluate(a_values,
//   b_values) >
//          1095);
//   assert(expression.GetRow<1>().GetCol<1>().Evaluate(a_values,
//   b_values) <
//          1096);
// }

// void Test3VectorsInt() {
//   const auto a_values = std::vector<std::vector<int>>{
//       std::vector<int>{11, 12, 13}, std::vector<int>{14, 15, 16}};
//   const auto b_values = std::vector<std::vector<int>>{std::vector<int>{21,
//   22},
//                                                       std::vector<int>{23,
//                                                       24},
//                                                       std::vector<int>{25,
//                                                       26}};
//   const auto c_values = std::vector<std::vector<int>>{
//       std::vector<int>{31, 32, 33, 34}, std::vector<int>{35, 36, 37, 38}};

//   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{} * Mat<2, 4>{};

//   assert(expression.GetRow<0>().GetCol<0>().Evaluate(a_values,
//   b_values,
//                                                           c_values) ==
//                                                           56172);
//   assert(expression.GetRow<0>().GetCol<1>().Evaluate(a_values,
//   b_values,
//                                                           c_values) ==
//                                                           57872);
//   assert(expression.GetRow<0>().GetCol<2>().Evaluate(a_values,
//   b_values,
//                                                           c_values) ==
//                                                           59572);
//   assert(expression.GetRow<0>().GetCol<3>().Evaluate(a_values,
//   b_values,
//                                                           c_values) ==
//                                                           61272);
//   assert(expression.GetRow<1>().GetCol<0>().Evaluate(a_values,
//   b_values,
//                                                           c_values) ==
//                                                           70149);
//   assert(expression.GetRow<1>().GetCol<1>().Evaluate(a_values,
//   b_values,
//                                                           c_values) ==
//                                                           72272);
//   assert(expression.GetRow<1>().GetCol<2>().Evaluate(a_values,
//   b_values,
//                                                           c_values) ==
//                                                           74395);
//   assert(expression.GetRow<1>().GetCol<3>().Evaluate(a_values,
//   b_values,
//                                                           c_values) ==
//                                                           76518);
// }

// void Test3VectorsIntFloatDouble() {
//   const auto a_values = std::vector<std::vector<int>>{
//       std::vector<int>{11, 12, 13}, std::vector<int>{14, 15, 16}};
//   const auto b_values = std::vector<std::vector<float>>{
//       std::vector<float>{21.1, 22.1}, std::vector<float>{23.1, 24.1},
//       std::vector<float>{25.1, 26.1}};
//   const auto c_values = std::vector<std::vector<double>>{
//       std::vector<double>{31.1, 32.1, 33.1, 34.1},
//       std::vector<double>{35.1, 36.1, 37.1, 38.1}};

//   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{} * Mat<2, 4>{};

//   assert(expression.GetRow<0>().GetCol<0>().Evaluate(a_values,
//   b_values,
//                                                           c_values) > 56580);
//   assert(expression.GetRow<0>().GetCol<0>().Evaluate(a_values,
//   b_values,
//                                                           c_values) < 56581);
//   assert(expression.GetRow<0>().GetCol<1>().Evaluate(a_values,
//   b_values,
//                                                           c_values) > 58287);
//   assert(expression.GetRow<0>().GetCol<1>().Evaluate(a_values,
//   b_values,
//                                                           c_values) < 58288);
//   assert(expression.GetRow<0>().GetCol<2>().Evaluate(a_values,
//   b_values,
//                                                           c_values) > 59994);
//   assert(expression.GetRow<0>().GetCol<2>().Evaluate(a_values,
//   b_values,
//                                                           c_values) < 59995);
//   assert(expression.GetRow<0>().GetCol<3>().Evaluate(a_values,
//   b_values,
//                                                           c_values) > 61701);
//   assert(expression.GetRow<0>().GetCol<3>().Evaluate(a_values,
//   b_values,
//                                                           c_values) < 61702);
//   assert(expression.GetRow<1>().GetCol<0>().Evaluate(a_values,
//   b_values,
//                                                           c_values) > 70659);
//   assert(expression.GetRow<1>().GetCol<0>().Evaluate(a_values,
//   b_values,
//                                                           c_values) < 70660);
//   assert(expression.GetRow<1>().GetCol<1>().Evaluate(a_values,
//   b_values,
//                                                           c_values) > 72791);
//   assert(expression.GetRow<1>().GetCol<1>().Evaluate(a_values,
//   b_values,
//                                                           c_values) < 72792);
//   assert(expression.GetRow<1>().GetCol<2>().Evaluate(a_values,
//   b_values,
//                                                           c_values) > 74923);
//   assert(expression.GetRow<1>().GetCol<2>().Evaluate(a_values,
//   b_values,
//                                                           c_values) < 74924);
//   assert(expression.GetRow<1>().GetCol<3>().Evaluate(a_values,
//   b_values,
//                                                           c_values) > 77055);
//   assert(expression.GetRow<1>().GetCol<3>().Evaluate(a_values,
//   b_values,
//                                                           c_values) < 77056);
// }

void Test2ArraysInt() {
  constexpr auto a_values = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, std::array<int, 3>{14, 15, 16}};
  constexpr auto b_values = std::array<std::array<int, 2>, 3>{
      std::array<int, 2>{21, 22}, std::array<int, 2>{23, 24},
      std::array<int, 2>{25, 26}};

  using Expr = decltype(Mat<2, 3>{} * Mat<3, 2>{});

  static_assert(Expr::Evaluate<0, 0>(a_values, b_values) == 832);
  static_assert(Expr::Evaluate<0, 1>(a_values, b_values) == 868);
  static_assert(Expr::Evaluate<1, 0>(a_values, b_values) == 1039);
  static_assert(Expr::Evaluate<1, 1>(a_values, b_values) == 1084);
}

// void Test2ArraysFloat() {
//   constexpr auto a_values = std::array<std::array<float, 3>, 2>{
//       std::array<float, 3>{11.1, 12.1, 13.1},
//       std::array<float, 3>{14.1, 15.1, 16.1}};
//   constexpr auto b_values = std::array<std::array<float, 2>, 3>{
//       std::array<float, 2>{21.1, 22.1}, std::array<float, 2>{23.1, 24.1},
//       std::array<float, 2>{25.1, 26.1}};

//   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{};

//   static_assert(expression.GetRow<0>().GetCol<0>().Evaluate(
//                     a_values, b_values) > 842);
//   static_assert(expression.GetRow<0>().GetCol<0>().Evaluate(
//                     a_values, b_values) < 843);
//   static_assert(expression.GetRow<0>().GetCol<1>().Evaluate(
//                     a_values, b_values) > 878);
//   static_assert(expression.GetRow<0>().GetCol<1>().Evaluate(
//                     a_values, b_values) < 879);
//   static_assert(expression.GetRow<1>().GetCol<0>().Evaluate(
//                     a_values, b_values) > 1050);
//   static_assert(expression.GetRow<1>().GetCol<0>().Evaluate(
//                     a_values, b_values) < 1051);
//   static_assert(expression.GetRow<1>().GetCol<1>().Evaluate(
//                     a_values, b_values) > 1095);
//   static_assert(expression.GetRow<1>().GetCol<1>().Evaluate(
//                     a_values, b_values) < 1096);
// }

// void Test3ArraysInt() {
//   constexpr auto a_values = std::array<std::array<int, 3>, 2>{
//       std::array<int, 3>{11, 12, 13}, std::array<int, 3>{14, 15, 16}};
//   constexpr auto b_values = std::array<std::array<int, 2>, 3>{
//       std::array<int, 2>{21, 22}, std::array<int, 2>{23, 24},
//       std::array<int, 2>{25, 26}};
//   constexpr auto c_values = std::array<std::array<int, 4>, 2>{
//       std::array<int, 4>{31, 32, 33, 34}, std::array<int, 4>{35, 36, 37,
//       38}};

//   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{} * Mat<2, 4>{};

//   static_assert(expression.GetRow<0>().GetCol<0>().Evaluate(
//                     a_values, b_values, c_values) == 56172);
//   static_assert(expression.GetRow<0>().GetCol<1>().Evaluate(
//                     a_values, b_values, c_values) == 57872);
//   static_assert(expression.GetRow<0>().GetCol<2>().Evaluate(
//                     a_values, b_values, c_values) == 59572);
//   static_assert(expression.GetRow<0>().GetCol<3>().Evaluate(
//                     a_values, b_values, c_values) == 61272);
//   static_assert(expression.GetRow<1>().GetCol<0>().Evaluate(
//                     a_values, b_values, c_values) == 70149);
//   static_assert(expression.GetRow<1>().GetCol<1>().Evaluate(
//                     a_values, b_values, c_values) == 72272);
//   static_assert(expression.GetRow<1>().GetCol<2>().Evaluate(
//                     a_values, b_values, c_values) == 74395);
//   static_assert(expression.GetRow<1>().GetCol<3>().Evaluate(
//                     a_values, b_values, c_values) == 76518);
// }

void Test3ArraysIntFloatDouble() {
  constexpr auto a_values = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, std::array<int, 3>{14, 15, 16}};
  constexpr auto b_values = std::array<std::array<float, 2>, 3>{
      std::array<float, 2>{21.1, 22.1}, std::array<float, 2>{23.1, 24.1},
      std::array<float, 2>{25.1, 26.1}};
  constexpr auto c_values = std::array<std::array<double, 4>, 2>{
      std::array<double, 4>{31.1, 32.1, 33.1, 34.1},
      std::array<double, 4>{35.1, 36.1, 37.1, 38.1}};

  using Expression = decltype(Mat<2, 3>{} * Mat<3, 2>{} * Mat<2, 4>{});

  static_assert(Expression::Evaluate<0, 0>(a_values, b_values,
                                                    c_values) > 56580);
  static_assert(Expression::Evaluate<0, 0>(a_values, b_values,
                                                    c_values) < 56581);
  static_assert(Expression::Evaluate<0, 1>(a_values, b_values,
                                                    c_values) > 58287);
  static_assert(Expression::Evaluate<0, 1>(a_values, b_values,
                                                    c_values) < 58288);
  static_assert(Expression::Evaluate<0, 2>(a_values, b_values,
                                                    c_values) > 59994);
  static_assert(Expression::Evaluate<0, 2>(a_values, b_values,
                                                    c_values) < 59995);
  static_assert(Expression::Evaluate<0, 3>(a_values, b_values,
                                                    c_values) > 61701);
  static_assert(Expression::Evaluate<0, 3>(a_values, b_values,
                                                    c_values) < 61702);
  static_assert(Expression::Evaluate<1, 0>(a_values, b_values,
                                                    c_values) > 70659);
  static_assert(Expression::Evaluate<1, 0>(a_values, b_values,
                                                    c_values) < 70660);
  static_assert(Expression::Evaluate<1, 1>(a_values, b_values,
                                                    c_values) > 72791);
  static_assert(Expression::Evaluate<1, 1>(a_values, b_values,
                                                    c_values) < 72792);
  static_assert(Expression::Evaluate<1, 2>(a_values, b_values,
                                                    c_values) > 74923);
  static_assert(Expression::Evaluate<1, 2>(a_values, b_values,
                                                    c_values) < 74924);
  static_assert(Expression::Evaluate<1, 3>(a_values, b_values,
                                                    c_values) > 77055);
  static_assert(Expression::Evaluate<1, 3>(a_values, b_values,
                                                    c_values) < 77056);
}

// void Test1Vector1Array() {
//   const auto a_values = std::vector<std::vector<int>>{
//       std::vector<int>{11, 12, 13}, std::vector<int>{14, 15, 16}};
//   constexpr auto b_values = std::array<std::array<int, 2>, 3>{
//       std::array<int, 2>{21, 22}, std::array<int, 2>{23, 24},
//       std::array<int, 2>{25, 26}};

//   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{};

//   assert(expression.GetRow<0>().GetCol<0>().Evaluate(a_values,
//   b_values) ==
//          832);
//   assert(expression.GetRow<0>().GetCol<1>().Evaluate(a_values,
//   b_values) ==
//          868);
//   assert(expression.GetRow<1>().GetCol<0>().Evaluate(a_values,
//   b_values) ==
//          1039);
//   assert(expression.GetRow<1>().GetCol<1>().Evaluate(a_values,
//   b_values) ==
//          1084);
// }

// void Test1Mat1Expression() {
//   constexpr auto d_values =
//       std::array<std::array<int, 2>, 1>{std::array<int, 2>{41, 42}};
//   constexpr auto a_values = std::array<std::array<int, 3>, 2>{
//       std::array<int, 3>{11, 12, 13}, std::array<int, 3>{14, 15, 16}};
//   constexpr auto b_values = std::array<std::array<int, 2>, 3>{
//       std::array<int, 2>{21, 22}, std::array<int, 2>{23, 24},
//       std::array<int, 2>{25, 26}};

//   constexpr auto expression1 = Mat<2, 3>{} * Mat<3, 2>{};
//   constexpr auto expression = Mat<1, 2>{} * expression1;

//   static_assert(expression.GetRow<0>().GetCol<0>().Evaluate(
//                     d_values, a_values, b_values) == 77750);
//   static_assert(expression.GetRow<0>().GetCol<1>().Evaluate(
//                     d_values, a_values, b_values) == 81116);
// }

// void Test2Expressions() {
//   constexpr auto a_values = std::array<std::array<int, 3>, 2>{
//       std::array<int, 3>{11, 12, 13}, std::array<int, 3>{14, 15, 16}};
//   constexpr auto b_values = std::array<std::array<int, 2>, 3>{
//       std::array<int, 2>{21, 22}, std::array<int, 2>{23, 24},
//       std::array<int, 2>{25, 26}};

//   constexpr auto expression1 = Mat<2, 3>{} * Mat<3, 2>{};
//   constexpr auto expression2 = Mat<2, 3>{} * Mat<3, 2>{};
//   constexpr auto expression = expression1 * expression2;

//   static_assert(expression.GetRow<0>().GetCol<0>().Evaluate(
//                     a_values, b_values, a_values, b_values) == 1594076);
//   static_assert(expression.GetRow<0>().GetCol<1>().Evaluate(
//                     a_values, b_values, a_values, b_values) == 1663088);
//   static_assert(expression.GetRow<1>().GetCol<0>().Evaluate(
//                     a_values, b_values, a_values, b_values) == 1990724);
//   static_assert(expression.GetRow<1>().GetCol<1>().Evaluate(
//                     a_values, b_values, a_values, b_values) == 2076908);
// }

void TestFacadeInt() {
  constexpr auto a_values = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{11, 12, 13}, std::array<int, 3>{14, 15, 16}};
  constexpr auto b_values = std::array<std::array<int, 2>, 3>{
      std::array<int, 2>{21, 22}, std::array<int, 2>{23, 24},
      std::array<int, 2>{25, 26}};
  constexpr auto c_values = std::array<std::array<int, 4>, 2>{
      std::array<int, 4>{31, 32, 33, 34}, std::array<int, 4>{35, 36, 37, 38}};

  using Expression = decltype(Mat<2, 3>{} * Mat<3, 2>{} * Mat<2, 4>{});

  constexpr auto result = Expression::Evaluate(a_values, b_values, c_values);

  static_assert(result[0][0] == 56172);
  static_assert(result[0][1] == 57872);
  static_assert(result[0][2] == 59572);
  static_assert(result[0][3] == 61272);
  static_assert(result[1][0] == 70149);
  static_assert(result[1][1] == 72272);
  static_assert(result[1][2] == 74395);
  static_assert(result[1][3] == 76518);
}

// void TestFacadeIntFloatDouble() {
//   constexpr auto a_values = std::array<std::array<int, 3>, 2>{
//       std::array<int, 3>{11, 12, 13}, std::array<int, 3>{14, 15, 16}};
//   constexpr auto b_values = std::array<std::array<float, 2>, 3>{
//       std::array<float, 2>{21.1, 22.1}, std::array<float, 2>{23.1, 24.1},
//       std::array<float, 2>{25.1, 26.1}};
//   constexpr auto c_values = std::array<std::array<double, 4>, 2>{
//       std::array<double, 4>{31.1, 32.1, 33.1, 34.1},
//       std::array<double, 4>{35.1, 36.1, 37.1, 38.1}};

//   constexpr auto expression = Mat<2, 3>{} * Mat<3, 2>{} * Mat<2, 4>{};

//   constexpr auto result = EvaluateMatrix(expression, a_values, b_values,
//   c_values);

//   static_assert(result[0][0] > 56580);
//   static_assert(result[0][0] < 56581);
//   static_assert(result[0][1] > 58287);
//   static_assert(result[0][1] < 58288);
//   static_assert(result[0][2] > 59994);
//   static_assert(result[0][2] < 59995);
//   static_assert(result[0][3] > 61701);
//   static_assert(result[0][3] < 61702);
//   static_assert(result[1][0] > 70659);
//   static_assert(result[1][0] < 70660);
//   static_assert(result[1][1] > 72791);
//   static_assert(result[1][1] < 72792);
//   static_assert(result[1][2] > 74923);
//   static_assert(result[1][2] < 74924);
//   static_assert(result[1][3] > 77055);
//   static_assert(result[1][3] < 77056);
// }
}  // namespace ctmm::tests

auto main() -> int {
  std::cout << "TEST START\n";
  // ctmm::tests::Test2VectorsInt();
  // ctmm::tests::Test2VectorsFloat();
  // ctmm::tests::Test3VectorsInt();
  // ctmm::tests::Test3VectorsIntFloatDouble();
  ctmm::tests::Test2ArraysInt();
  // ctmm::tests::Test2ArraysFloat();
  // ctmm::tests::Test3ArraysInt();
  // ctmm::tests::Test3ArraysIntFloatDouble();
  // ctmm::tests::Test1Vector1Array();
  // ctmm::tests::Test1Mat1Expression();
  // ctmm::tests::Test2Expressions();
  ctmm::tests::TestFacadeInt();
  // ctmm::tests::TestFacadeIntFloatDouble();
  std::cout << "TEST END\n";
  return 0;
}

#endif  // CTMM_TESTS_H_
