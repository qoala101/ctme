#ifndef CTMM_TESTS_H_
#define CTMM_TESTS_H_

#include <cassert>
#include <iostream>
#include <vector>

#include "ctmm.h"

namespace ctmm::tests {
void Test1() {
  const auto a_values = std::vector<std::vector<int>>{
      std::vector<int>{1, 2, 3}, std::vector<int>{4, 5, 6}};
  const auto b_values = std::vector<std::vector<int>>{
      std::vector<int>{1, 2}, std::vector<int>{3, 4}, std::vector<int>{5, 6}};

  constexpr auto a = Mat<2, 3>{
      // a_values
  };
  constexpr auto b = Mat<3, 2>{
      // b_values
  };
  constexpr auto expression = a * b;

  std::cout << expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values)
            << "\n";
  std::cout << expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values)
            << "\n";
}

// void Test2() {
//   const auto a_values = std::vector<std::vector<int>>{
//       std::vector<int>{1, 2, 3}, std::vector<int>{4, 5, 6}};
//   const auto b_values = std::vector<std::vector<int>>{
//       std::vector<int>{1, 2}, std::vector<int>{3, 4}, std::vector<int>{5,
//       6}};

//   const auto a = Mat<2, 3>{a_values};
//   const auto b = Mat<3, 2>{b_values};
//   const auto expression = a * b;

//   assert(expression.Row<0>().Col<0>()(a_values, b_values) == 22);
//   assert(expression.Row<0>().Col<1>()(a_values, b_values) == 28);
//   assert(expression.Row<1>().Col<0>()(a_values, b_values) == 49);
//   assert(expression.Row<1>().Col<1>()(a_values, b_values) == 64);
// }

void Test3() {
  // const auto a_values = std::vector<std::vector<int>>{
  //     std::vector<int>{1, 2, 3}, std::vector<int>{4, 5, 6}};
  // const auto b_values = std::vector<std::vector<int>>{
  //     std::vector<int>{1, 2}, std::vector<int>{3, 4}, std::vector<int>{5, 6}};
  // const auto c_values = std::vector<std::vector<int>>{
  //     std::vector<int>{1, 2, 3, 4}, std::vector<int>{5, 6, 7, 8}};

  // constexpr auto a = Mat<2, 3>{
  //     // a_values
  // };
  // constexpr auto b = Mat<3, 2>{
  //     // b_values
  // };
  // constexpr auto c = Mat<2, 4>{
  //     // c_values
  // };
  // constexpr auto expression = a * b * c;

  // std::cout << expression.GetRow<0>().GetCol<0>().GetVal(a_values, b_values,
  //                                                        c_values)
  //           << "\n";
  // std::cout << expression.GetRow<0>().GetCol<1>().GetVal(a_values, b_values,
  //                                                        c_values)
  //           << "\n";
  // std::cout << expression.GetRow<0>().GetCol<2>().GetVal(a_values, b_values,
  //                                                        c_values)
  //           << "\n";
  // std::cout << expression.GetRow<0>().GetCol<3>().GetVal(a_values, b_values,
  //                                                        c_values)
  //           << "\n";
  // std::cout << expression.GetRow<1>().GetCol<0>().GetVal(a_values, b_values,
  //                                                        c_values)
  //           << "\n";
  // std::cout << expression.GetRow<1>().GetCol<1>().GetVal(a_values, b_values,
  //                                                        c_values)
  //           << "\n";
  // std::cout << expression.GetRow<1>().GetCol<2>().GetVal(a_values, b_values,
  //                                                        c_values)
  //           << "\n";
  // std::cout << expression.GetRow<1>().GetCol<3>().GetVal(a_values, b_values,
  //                                                        c_values)
  //           << "\n";

  // assert(expression.GetRow<0>().GetCol<0>().GetVal() == 162);
  // assert(expression.GetRow<0>().GetCol<1>().GetVal() == 212);
  // assert(expression.GetRow<0>().GetCol<2>().GetVal() == 262);
  // assert(expression.GetRow<0>().GetCol<3>().GetVal() == 312);
  // assert(expression.GetRow<1>().GetCol<0>().GetVal() == 369);
  // assert(expression.GetRow<1>().GetCol<1>().GetVal() == 482);
  // assert(expression.GetRow<1>().GetCol<2>().GetVal() == 595);
  // assert(expression.GetRow<1>().GetCol<3>().GetVal() == 708);
}
}  // namespace ctmm::tests

auto main() -> int {
  std::cout << "TEST START\n";
  ctmm::tests::Test1();
  // ctmm::tests::Test2();
  ctmm::tests::Test3();
  std::cout << "TEST END\n";
  return 0;
}

#endif  // CTMM_TESTS_H_
