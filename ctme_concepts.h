/**
 * CTME @link https://github.com/qoala101/ctme @endlink
 * @author Volodymyr Hromakov (4y5t6r@gmail.com)
 * @copyright Copyright (c) 2023, MIT License
 */

#ifndef VH_CTME_CONCEPTS_H_
#define VH_CTME_CONCEPTS_H_

#include <concepts>
#include <iterator>

namespace ctme {
/**
 * @brief Container of values accessible by [unsigned][unsigned] syntax.
 */
template <typename T>
concept MatValues = requires(const T &t, unsigned index) { t[index][index]; };

/**
 * @brief Object that behaves like a matrix which has a size and could be
 * composed of other matrix expressions.
 *
 * @remark Also must have the following function, which evaluates the value
 * of the specified cell, given the list of input values and index in that
 * list, which tells which inputs should be used to take values from.
 * @code
 *   template <unsigned RowIndex, unsigned ColIndex, unsigned ValuesIndex>
 *   static constexpr auto EvaluateCell(const MatValues auto &...input_values);
 * @endcode
 */
template <typename T>
concept MatExpression = requires() {
  { T::kNumRows } -> std::convertible_to<const unsigned>;
  { T::kNumCols } -> std::convertible_to<const unsigned>;
  { T::kNumMats } -> std::convertible_to<const unsigned>;
};
}  // namespace ctme

#endif  // VH_CTME_CONCEPTS_H_
