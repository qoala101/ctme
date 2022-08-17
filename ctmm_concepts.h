#ifndef CTMM_CONCEPTS_H_
#define CTMM_CONCEPTS_H_

#include <utility>

namespace ctmm {
/**
 * @brief Container of values accessible by [unsigned][unsigned] syntax.
 */
template <typename T>
concept Container2D = requires(const T &t, unsigned row, unsigned col) {
  t[row][col];
};

/**
 * @brief Object that behaves like a matrix.
 */
template <typename T>
concept MatExpression = requires() {
  { T::kNumRows } -> std::convertible_to<const unsigned>;
  { T::kNumCols } -> std::convertible_to<const unsigned>;
  { T::kNumMats } -> std::convertible_to<const unsigned>;
};
}  // namespace ctmm

#endif  // CTMM_CONCEPTS_H_
