#ifndef CTMM_CONCEPTS_H_
#define CTMM_CONCEPTS_H_

#include <concepts>
#include <iterator>

namespace ctmm {
/**
 * @brief Container of values accessible by [unsigned][unsigned] syntax.
 */
template <typename T>
concept MatValues = requires(const T &t, unsigned row) {
  requires std::ranges::random_access_range<T>;
  requires std::ranges::random_access_range<decltype(t[row])>;
};

/**
 * @brief Object that behaves like a matrix which has a size and could be
 * composed of other matrix expressions.
 *
 * @remark Also must have the following function, which evaluates the value
 * of the specified cell, given the list of input values and index in that
 * list, which tells which inputs should be used to take values from.
 * @code
 *   template <unsigned RowIndex, unsigned ColIndex, unsigned ValuesIndex>
 *   static constexpr auto Evaluate(const MatValues auto &...input_values);
 * @endcode
 */
template <typename T>
concept MatExpression = requires() {
  { T::kNumRows } -> std::convertible_to<const unsigned>;
  { T::kNumCols } -> std::convertible_to<const unsigned>;
  { T::kNumMats } -> std::convertible_to<const unsigned>;
};
}  // namespace ctmm

#endif  // CTMM_CONCEPTS_H_
