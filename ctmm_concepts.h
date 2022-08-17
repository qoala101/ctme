#ifndef STONKS_CTMM_CONCEPTS_H_
#define STONKS_CTMM_CONCEPTS_H_

#include <array>
#include <exception>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace ctmm::concepts {
template <typename T>
concept Input = requires(const T &t) {
  t[0][0];
};

template <typename T>
concept Mat = requires() {
  { T::kNumRows } -> std::convertible_to<int>;
  { T::kNumCols } -> std::convertible_to<int>;
  { T::kNumInputs } -> std::convertible_to<int>;

  // T::template Evaluate<0, 0>(std::vector<int>{}, std::vector<int>{});
  // T::Evaluate(std::vector<int>{}, std::vector<int>{});
};
}  // namespace ctmm::concepts

#endif  // STONKS_CTMM_CONCEPTS_H_
