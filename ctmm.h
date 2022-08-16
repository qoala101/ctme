#ifndef CTMM_H_
#define CTMM_H_

#include <array>
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

  constexpr auto GetVal(const ClientMat &t) const {
    return t[RowIndex][ColIndex];
    // return 0;
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

// template <typename T, int RowsLeft, int Common, int ColsRight, int RowIndex,
//           int ColIndex>
// struct ColExpression {
//    auto operator()(const auto& left, const auto& right) const {
//     auto sum = T{};

//     for (auto i = 0; i < Common; ++i) {
//       sum += left[RowIndex][i] * right[i][ColIndex];
//     }

//     return sum;
//   }
// };

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex>
struct ColExpression {
  constexpr explicit ColExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <typename... Args>
  constexpr auto GetVal(const ClientMat &t, const Args&... args) const {
    auto sum = 0;

    for (auto i = 0; i < LeftMat::kCols; ++i) {
      sum +=
          left_mat_.template GetRow<RowIndex>().template GetCol<0>().GetVal(args...) *
          right_mat_.template GetRow<0>().template GetCol<ColIndex>().GetVal(t);
    }

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
