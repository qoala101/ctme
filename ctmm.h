#ifndef CTMM_H_
#define CTMM_H_

#include <array>

namespace ctmm {
template <typename T, int Rows, int Cols>
struct Mat {};

template <typename T, int RowsLeft, int Common, int ColsRight, int RowIndex,
          int ColIndex>
struct ColExpression {
  constexpr auto operator()(const auto& left, const auto& right) const {
    auto sum = T{};

    for (auto i = 0; i < Common; ++i) {
      sum += left[RowIndex][i] * right[i][ColIndex];
    }

    return sum;
  }
};

template <typename T, int RowsLeft, int Common, int ColsRight, int RowIndex>
struct RowExpression {
  template <int ColIndex>
  constexpr auto Col() const {
    return ColExpression<T, RowsLeft, Common, ColsRight, RowIndex, ColIndex>{};
  }
};

template <typename T, int RowsLeft, int Common, int ColsRight>
struct MatExpression {
  template <int RowIndex>
  constexpr auto Row() const {
    return RowExpression<T, RowsLeft, Common, ColsRight, RowIndex>{};
  }
};

template <typename T, int RowsLeft, int Common, int ColsRight>
[[nodiscard]] constexpr auto operator*(
    const Mat<T, RowsLeft, Common>& /*unused*/,
    const Mat<T, Common, ColsRight>& /*unused*/) {
  return MatExpression<T, RowsLeft, Common, ColsRight>{};
}
}  // namespace ctmm

#endif  // CTMM_H_
