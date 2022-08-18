#ifndef CTME_MAT_H_
#define CTME_MAT_H_

#include <tuple>

#include "ctme_concepts.h"  // IWYU pragma: keep

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
  [[nodiscard]] static constexpr auto EvaluateCell(
      const MatValues auto &...input_values) {
    static_assert(RowIndex < kNumRows);
    static_assert(ColIndex < kNumCols);

    return std::get<ValuesIndex>(std::tie(input_values...))[RowIndex][ColIndex];
  }

  static_assert(MatExpression<Mat>);
};
}  // namespace ctme

#endif  // CTME_MAT_H_
