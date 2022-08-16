#ifndef CTMM_H_
#define CTMM_H_

#include <array>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

namespace ctmm {
template <int Rows, int Cols, int RowIndex, int ColIndex>
struct Col {
  template <int ContainerIndex, typename... Args>
  constexpr auto GetVal(const Args&... args) const {
    return std::get<ContainerIndex>(std::tie(args...))[RowIndex][ColIndex];
  }
};

template <int Rows, int Cols, int RowIndex>
struct Row {
  template <int ColIndex>
  constexpr auto GetCol() const {
    return Col<Rows, Cols, RowIndex, ColIndex>{};
  }
};

template <int Rows, int Cols>
struct Mat {
  static const constinit auto kRows = Rows;
  static const constinit auto kCols = Cols;
  static const constinit auto kContainers = 1;

  template <int RowIndex>
  using RowType = Row<Rows, Cols, RowIndex>;

  template <int RowIndex>
  constexpr auto GetRow() const {
    return Row<Rows, Cols, RowIndex>{};
  }
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex,
          int ContainerIndex, int Index>
struct Iterator {
  template <typename... Args>
  constexpr explicit Iterator(LeftMat left_mat, RightMat right_mat,
                              const Args&... args)
      : left_mat_{std::move(left_mat)},
        right_mat_{std::move(right_mat)},

        sum_{left_mat_.template GetRow<RowIndex>()
                     .template GetCol<Index>()
                     .template GetVal<ContainerIndex - RightMat::kContainers>(args...) *
                 right_mat_.template GetRow<Index>()
                     .template GetCol<ColIndex>()
                     .template GetVal<ContainerIndex>(args...) +
             Iterator<LeftMat, RightMat, RowIndex, ColIndex, ContainerIndex,
                      Index - 1>{left_mat_, right_mat_, args...}
                 .sum_} {}

  LeftMat left_mat_{};
  RightMat right_mat_{};

  int sum_{};
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex,
          int ContainerIndex>
struct Iterator<LeftMat, RightMat, RowIndex, ColIndex, ContainerIndex, -1> {
  template <typename... Args>
  constexpr explicit Iterator(LeftMat left_mat, RightMat right_mat,
                              const Args&... args) {}

  int sum_{};
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex>
struct ColExpression {
  constexpr explicit ColExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <int ContainerIndex, typename... Args>
  constexpr auto GetVal(const Args&... args) const {
    return Iterator<LeftMat, RightMat, RowIndex, ColIndex, ContainerIndex,
                    LeftMat::kCols - 1>{left_mat_, right_mat_, args...}
        .sum_;
  }

  template <typename... Args>
  constexpr auto GetVal(const Args&... args) const {
    return GetVal<sizeof...(args) - 1>(args...);
  }

  LeftMat left_mat_{};
  RightMat right_mat_{};
};

template <typename LeftMat, typename RightMat, int RowIndex>
struct RowExpression {
  constexpr explicit RowExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <int ColIndex>
  constexpr auto GetCol() const {
    return ColExpression<LeftMat, RightMat, RowIndex, ColIndex>{left_mat_,
                                                                right_mat_};
  }

  LeftMat left_mat_{};
  RightMat right_mat_{};
};

template <typename LeftMat, typename RightMat>
struct MatExpression {
  static_assert(LeftMat::kCols == RightMat::kRows);

  static const constinit auto kRows = LeftMat::kRows;
  static const constinit auto kCols = RightMat::kCols;
  static const constinit auto kContainers = LeftMat::kContainers + RightMat::kContainers;

  template <int RowIndex>
  using RowType = RowExpression<LeftMat, RightMat, RowIndex>;

  constexpr explicit MatExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <int RowIndex>
  constexpr auto GetRow() const {
    return RowExpression<LeftMat, RightMat, RowIndex>{left_mat_, right_mat_};
  }

  LeftMat left_mat_{};
  RightMat right_mat_{};
};

[[nodiscard]] constexpr auto operator*(const auto& left_mat,
                                       const auto& right_mat) {
  return MatExpression{left_mat, right_mat};
}
}  // namespace ctmm

#endif  // CTMM_H_
