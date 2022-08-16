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
  explicit Col(const ClientMat& client_mat) : client_mat_{client_mat} {}

  auto GetVal() const { return client_mat_[RowIndex][ColIndex]; }

  const ClientMat& client_mat_;
};

template <int Rows, int Cols, int RowIndex>
struct Row {
  explicit Row(const ClientMat& client_mat) : client_mat_{client_mat} {}

  template <int ColIndex>
  auto GetCol() const {
    return Col<Rows, Cols, RowIndex, ColIndex>{client_mat_};
  }

  const ClientMat& client_mat_;
};

template <int Rows, int Cols>
struct Mat {
  static const constinit auto kRows = Rows;
  static const constinit auto kCols = Cols;

  template <int RowIndex>
  using RowType = Row<Rows, Cols, RowIndex>;

  explicit Mat(const ClientMat& client_mat) : client_mat_{client_mat} {}

  template <int RowIndex>
  auto GetRow() const {
    return Row<Rows, Cols, RowIndex>{client_mat_};
  }

  const ClientMat& client_mat_;
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
  explicit ColExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  auto GetVal() const {
    auto sum = 0;

    for (auto i = 0; i < LeftMat::kCols; ++i) {
      sum +=
          left_mat_.template GetRow<RowIndex>().template GetCol</*i*/0>().GetVal() *
          right_mat_.template GetRow</*i*/0>().template GetCol<ColIndex>().GetVal();
    }

    return sum;
  }

  LeftMat left_mat_{};
  RightMat right_mat_{};
};

template <typename LeftMat, typename RightMat, int RowIndex>
struct RowExpression {
  explicit RowExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <int ColIndex>
  auto GetCol() const {
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

  explicit MatExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <int RowIndex>
  auto GetRow() const {
    return RowExpression<LeftMat, RightMat, RowIndex>{left_mat_, right_mat_};
  }

  LeftMat left_mat_{};
  RightMat right_mat_{};
};

[[nodiscard]] auto operator*(const auto& left_mat, const auto& right_mat) {
  return MatExpression{left_mat, right_mat};
}
}  // namespace ctmm

#endif  // CTMM_H_
