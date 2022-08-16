#ifndef CTMM_H_
#define CTMM_H_

#include <array>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

namespace ctmm {
template <int RowIndex, int ColIndex>
class Cell {
  static_assert(RowIndex >= 0);
  static_assert(ColIndex >= 0);

 public:
  template <int InputIndex, typename... Inputs>
  [[nodiscard]] constexpr auto EvaluateValue(const Inputs &...inputs) const {
    static_assert(InputIndex >= 0);
    static_assert(InputIndex < sizeof...(inputs));

    return std::get<InputIndex>(std::tie(inputs...))[RowIndex][ColIndex];
  }
};

template <int RowIndex>
class Row {
  static_assert(RowIndex >= 0);

 public:
  template <int ColIndex>
  [[nodiscard]] constexpr auto GetCol() const {
    static_assert(ColIndex >= 0);

    return Cell<RowIndex, ColIndex>{};
  }
};

template <int NumRows, int NumCols>
class Mat {
  static_assert(NumRows > 0);
  static_assert(NumCols > 0);

 public:
  static constexpr auto kNumRows = NumRows;
  static constexpr auto kNumCols = NumCols;
  static constexpr auto kNumInputs = 1;

  template <int RowIndex>
  [[nodiscard]] constexpr auto GetRow() const {
    static_assert(RowIndex >= 0);

    return Row<RowIndex>{};
  }
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex,
          int ContainerIndex, int Index>
struct Iterator {
  template <typename... Args>
  constexpr explicit Iterator(LeftMat left_mat, RightMat right_mat,
                              const Args &...args)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  LeftMat left_mat_{};
  RightMat right_mat_{};

  template <typename... Args>
  [[nodiscard]] constexpr auto Sum(const Args &...args) const {
    return left_mat_.template GetRow<RowIndex>()
                   .template GetCol<Index>()
                   .template EvaluateValue<ContainerIndex -
                                           RightMat::kNumInputs>(args...) *
               right_mat_.template GetRow<Index>()
                   .template GetCol<ColIndex>()
                   .template EvaluateValue<ContainerIndex>(args...) +
           Iterator<LeftMat, RightMat, RowIndex, ColIndex, ContainerIndex,
                    Index - 1>{left_mat_, right_mat_}
               .Sum(args...);
  }
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex,
          int ContainerIndex>
struct Iterator<LeftMat, RightMat, RowIndex, ColIndex, ContainerIndex, -1> {
  template <typename... Args>
  constexpr explicit Iterator(LeftMat left_mat, RightMat right_mat) {}

  template <typename... Args>
  [[nodiscard]] constexpr auto Sum(const Args &...args) const {
    return decltype(std::declval<LeftMat>()
                        .template GetRow<0>()
                        .template GetCol<0>()
                        .template EvaluateValue<1>(args...) *
                    std::declval<RightMat>()
                        .template GetRow<0>()
                        .template GetCol<0>()
                        .template EvaluateValue<1>(args...)){};
  }
};

template <typename LeftMat, typename RightMat, int RowIndex, int ColIndex>
struct ColExpression {
  constexpr explicit ColExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <int ContainerIndex, typename... Args>
  constexpr auto EvaluateValue(const Args &...args) const {
    return Iterator<LeftMat, RightMat, RowIndex, ColIndex, ContainerIndex,
                    LeftMat::kNumCols - 1>{left_mat_, right_mat_}
        .Sum(args...);
  }

  template <typename... Args>
  constexpr auto EvaluateValue(const Args &...args) const {
    return EvaluateValue<sizeof...(args) - 1>(args...);
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
  static_assert(LeftMat::kNumCols == RightMat::kNumRows);

  static constexpr auto kNumRows = LeftMat::kNumRows;
  static constexpr auto kNumCols = RightMat::kNumCols;
  static constexpr auto kNumInputs = LeftMat::kNumInputs + RightMat::kNumInputs;

  constexpr explicit MatExpression(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  template <int RowIndex>
  constexpr auto GetRow() const {
    return RowExpression<LeftMat, RightMat, RowIndex>{left_mat_, right_mat_};
  }

  LeftMat left_mat_{};
  RightMat right_mat_{};
};

[[nodiscard]] constexpr auto operator*(const auto &left_mat,
                                       const auto &right_mat) {
  return MatExpression{left_mat, right_mat};
}

template <int RowIndex, int ColIndex, typename... Args>
[[nodiscard]] constexpr auto EvaluateCell(const auto &expression,
                                          const Args &...args) {
  return expression.template GetRow<RowIndex>()
      .template GetCol<ColIndex>()
      .template EvaluateValue(args...);
}

template <typename Expression, typename ResultType, int RowIndex, int ColIndex>
struct Evaluator {
  template <typename... Args>
  constexpr explicit Evaluator(
      const Expression &expression,
      std::array<std::array<ResultType, Expression::kNumCols>,
                 Expression::kNumRows> &result,
      const Args &...args) {
    result[RowIndex][ColIndex] =
        EvaluateCell<RowIndex, ColIndex>(expression, args...);
    Evaluator<Expression, ResultType, RowIndex, ColIndex - 1>{expression,
                                                              result, args...};
  }
};

template <typename Expression, typename ResultType, int RowIndex>
struct Evaluator<Expression, ResultType, RowIndex, 0> {
  template <typename... Args>
  constexpr explicit Evaluator(
      const Expression &expression,
      std::array<std::array<ResultType, Expression::kNumCols>,
                 Expression::kNumRows> &result,
      const Args &...args) {
    result[RowIndex][0] = EvaluateCell<RowIndex, 0>(expression, args...);
    Evaluator<Expression, ResultType, RowIndex - 1, Expression::kNumCols - 1>{
        expression, result, args...};
  }
};

template <typename Expression, typename ResultType>
struct Evaluator<Expression, ResultType, 0, 0> {
  template <typename... Args>
  constexpr explicit Evaluator(
      const Expression &expression,
      std::array<std::array<ResultType, Expression::kNumCols>,
                 Expression::kNumRows> &result,
      const Args &...args) {
    result[0][0] = EvaluateCell<0, 0>(expression, args...);
  }
};

template <typename Expression, typename... Args>
[[nodiscard]] constexpr auto EvaluateMatrix(const Expression &expression,
                                            const Args &...args) {
  using ResultType = decltype(EvaluateCell<0, 0>(expression, args...));

  auto result = std::array<std::array<ResultType, Expression::kNumCols>,
                           Expression::kNumRows>{};

  Evaluator<Expression, ResultType, Expression::kNumRows - 1,
            Expression::kNumCols - 1>{expression, result, args...};

  return result;
}
}  // namespace ctmm

#endif  // CTMM_H_
