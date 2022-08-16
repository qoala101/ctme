#ifndef CTMM_H_
#define CTMM_H_

#include <array>
#include <iostream>
#include <utility>
#include <vector>

namespace ctmm {
template <int Rows, int Cols, int RowIndex, int ColIndex>
struct Col {
  // constexpr explicit Col(const ClientMat& client_mat) :
  // client_mat_{client_mat} {}

  template<typename ClientMat>
  constexpr auto GetVal(const ClientMat& t) const {
    // std::cout << "GetClientVal " << RowIndex << " " << ColIndex << " = " << t[RowIndex][ColIndex] << "\n";
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
  template <typename... Args, typename ClientMat>
  constexpr explicit Iterator(LeftMat left_mat, RightMat right_mat,
                              const ClientMat& t, const Args&... args)
      : left_mat_{std::move(left_mat)},
        right_mat_{std::move(right_mat)},

        sum_{TEMP(t, args...) +
             Iterator<LeftMat, RightMat, RowIndex, ColIndex, Index - 1>{
                 left_mat_, right_mat_, t, args...}
                 .sum_} {}

  template <typename... Args, typename ClientMat>
  constexpr auto TEMP(const ClientMat& t, const Args&... args) const -> int {
    // std::cout << "Multiplying " <<
    auto a =
        left_mat_.template GetRow<RowIndex>().template GetCol<Index>().GetVal(
            args...);
    auto b =
        right_mat_.template GetRow<Index>().template GetCol<ColIndex>().GetVal(
            t);
    auto res = a * b;

    // std::cout << a << " * " << b << " = " << res << "\n";
    return res;
  }

  LeftMat left_mat_{};
  RightMat right_mat_{};

  int sum_{};
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex>
struct Iterator<LeftMat, RightMat, RowIndex, ColIndex, -1> {
  template <typename... Args, typename ClientMat>
  constexpr explicit Iterator(LeftMat left_mat, RightMat right_mat,
                              const ClientMat& t, const Args&... args)
      : sum_{0} {}

  int sum_{};
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex>
struct ColExpression {
  constexpr explicit ColExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <typename... Args, typename ClientMat>
  constexpr auto GetVal(const ClientMat& t, const Args&... args) const {
    // std::cout << "GetMatrixVal " << RowIndex << " " << ColIndex << "{\n";
    auto sum = 0;

    sum =
        Iterator<LeftMat, RightMat, RowIndex, ColIndex, LeftMat::kCols - 1>{
            left_mat_, right_mat_, t, args...}
            .sum_;

    // std::cout << "} GetMatrixVal " << RowIndex << " " << ColIndex << " = " << sum << "\n";

    // std::cout << "SUM: " << sum << "\n";

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
