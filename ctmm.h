#ifndef CTMM_H_
#define CTMM_H_

#include <array>
#include <iostream>
#include <utility>
#include <vector>

namespace ctmm {
using ClientVal = int;
using ClientVec = std::vector<ClientVal>;
using ClientMat = std::vector<ClientVec>;

template <int Rows, int Cols, int RowIndex, int ColIndex>
struct Col {
  // constexpr explicit Col(const ClientMat& client_mat) :
  // client_mat_{client_mat} {}

  constexpr auto GetVal(const ClientMat& t) const {
    return t[RowIndex][ColIndex];
  }

  // const ClientMat& client_mat_;
};

template <int Rows, int Cols, int RowIndex>
struct Row {
  // constexpr explicit Row(const ClientMat& client_mat) :
  // client_mat_{client_mat} {}

  template <int ColIndex>
  constexpr auto GetCol() const {
    return Col<Rows, Cols, RowIndex, ColIndex>{
        // client_mat_
    };
  }

  // const ClientMat& client_mat_;
};

template <int Rows, int Cols>
struct Mat {
  static const constinit auto kRows = Rows;
  static const constinit auto kCols = Cols;

  template <int RowIndex>
  using RowType = Row<Rows, Cols, RowIndex>;

  // constexpr explicit Mat(const ClientMat& client_mat) :
  // client_mat_{client_mat} {}

  template <int RowIndex>
  constexpr auto GetRow() const {
    return Row<Rows, Cols, RowIndex>{
        // client_mat_
    };
  }

  // const ClientMat& client_mat_;
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex,
          int Index>
struct Iterator {
  template <typename... Args>
  constexpr explicit Iterator(LeftMat left_mat, RightMat right_mat,
                              const ClientMat& t, const Args&... args)
      : left_mat_{std::move(left_mat)},
        right_mat_{std::move(right_mat)},

        sum_{left_mat_.template GetRow<RowIndex>()
                     .template GetCol<Index>()
                     .GetVal(args...) *
                 right_mat_.template GetRow<Index>()
                     .template GetCol<ColIndex>()
                     .GetVal(t) +
             Iterator<LeftMat, RightMat, RowIndex, ColIndex, Index - 1>{
                 left_mat_, right_mat_, t, args...}
                 .sum_} {}

  LeftMat left_mat_{};
  RightMat right_mat_{};

  int sum_{};
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex>
struct Iterator<LeftMat, RightMat, RowIndex, ColIndex, -1> {
  template <typename... Args>
  constexpr explicit Iterator(LeftMat left_mat, RightMat right_mat,
                              const ClientMat& t, const Args&... args)
      : sum_{0} {}

  int sum_{};
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex>
struct ColExpression {
  constexpr explicit ColExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <typename... Args>
  constexpr auto GetVal(const ClientMat& t, const Args&... args) const {
    auto sum = 0;

    sum =
        Iterator<LeftMat, RightMat, RowIndex, ColIndex, LeftMat::kRows - 1>{
            left_mat_, right_mat_, t, args...}
            .sum_;

    return sum;
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
  static const constinit auto kRows = LeftMat::kRows;
  static const constinit auto kCols = RightMat::kCols;
  static_assert(LeftMat::kCols == RightMat::kRows);

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
