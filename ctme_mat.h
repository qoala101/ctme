/**
 * CTME @link https://github.com/qoala101/ctme @endlink
 * @author Volodymyr Hromakov (4y5t6r@gmail.com)
 * @copyright Copyright (c) 2023, MIT License
 */

#ifndef VH_CTME_MAT_H_
#define VH_CTME_MAT_H_

#include <tuple>

#include "ctme_concepts.h"      // IWYU pragma: keep
#include "ctme_debug_logger.h"  // IWYU pragma: keep

namespace ctme {
/**
 * @brief Plain matrix.
 */
template <unsigned NumRows, unsigned NumCols>
class Mat {
  static_assert(NumRows > 0);
  static_assert(NumCols > 0);

 public:
  static constexpr unsigned kNumRows = NumRows;
  static constexpr unsigned kNumCols = NumCols;
  static constexpr unsigned kNumMats = 1;

  template <unsigned RowIndex, unsigned ColIndex, unsigned ValuesIndex>
  static constexpr auto EvaluateCell
      [[nodiscard]] (const MatValues auto &...input_values) {
    static_assert(RowIndex < kNumRows);
    static_assert(ColIndex < kNumCols);
#ifdef CTME_DEBUG
    debug::Logger::Instance().PrintCell(
        std::get<ValuesIndex>(std::tie(input_values...)), RowIndex, ColIndex);
#endif
    return std::get<ValuesIndex>(std::tie(input_values...))[RowIndex][ColIndex];
  }

  static_assert(MatExpression<Mat>);
};
}  // namespace ctme

#endif  // VH_CTME_MAT_H_
