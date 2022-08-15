#ifndef CTMM_TESTS_H_
#define CTMM_TESTS_H_

#include <iostream>
#include <vector>

#include "ctmm.h"

namespace ctmm::tests {
void Test1() {
  constexpr auto a = Mat<int, 2, 3>{};
  constexpr auto b = Mat<int, 3, 2>{};
  constexpr auto expression = a * b;

  constexpr auto a_values = std::array<std::array<int, 3>, 2>{
      std::array<int, 3>{1, 2, 3}, std::array<int, 3>{4, 5, 6}};
  constexpr auto b_values = std::array<std::array<int, 2>, 3>{
      std::array<int, 2>{1, 2}, std::array<int, 2>{3, 4},
      std::array<int, 2>{5, 6}};

  static_assert(expression.Row<0>().Col<0>()(a_values, b_values) == 22);
  static_assert(expression.Row<0>().Col<1>()(a_values, b_values) == 28);
  static_assert(expression.Row<1>().Col<0>()(a_values, b_values) == 49);
  static_assert(expression.Row<1>().Col<1>()(a_values, b_values) == 64);
}
}  // namespace ctmm::tests

auto main() -> int {
  std::cout << "TEST START\n";
  ctmm::tests::Test1();
  std::cout << "TEST END\n";
  return 0;
}

#endif  // CTMM_TESTS_H_
