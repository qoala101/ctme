#ifndef CTMM_H_
#define CTMM_H_

#include <array>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace ctmm {
namespace concepts {
// template <typename T, typename... Args>
// concept Cell = requires(const T &t, const Args &...args) {
//   t->EvaluateValue(args...);
// };

// template <typename T>
// concept Row = requires() {
//   { T::kNumRows } -> std::convertible_to<int>;
//   { T::kNumCols } -> std::convertible_to<int>;
//   { T::kNumInputs } -> std::convertible_to<int>;
// };

template <typename T>
concept Mat = requires() {
  { T::kNumRows } -> std::convertible_to<int>;
  { T::kNumCols } -> std::convertible_to<int>;
  { T::kNumInputs } -> std::convertible_to<int>;
};
}  // namespace concepts

template <int RowIndex, int ColIndex>
class Cell {
 public:
  template <int InputIndex, typename... Inputs>
  [[nodiscard]] constexpr auto EvaluateValue(const Inputs &...inputs) const {
    static_assert(InputIndex >= 0);
    static_assert(InputIndex < sizeof...(inputs));

    return std::get<InputIndex>(std::tie(inputs...))[RowIndex][ColIndex];
  }

 private:
  template <int, int>
  friend class Row;

  explicit Cell() = default;
};

template <int RowIndex, int NumCols>
class Row {
 public:
  template <int ColIndex>
  [[nodiscard]] constexpr auto GetCol() const {
    static_assert(ColIndex >= 0);
    static_assert(ColIndex < NumCols);

    return Cell<RowIndex, ColIndex>{};
  }

 private:
  template <int, int>
  friend class Mat;

  explicit Row() = default;
};

template <int NumRows, int NumCols>
class Mat {
 public:
  static constexpr int kNumRows = NumRows;
  static constexpr int kNumCols = NumCols;
  static constexpr int kNumInputs = 1;

  template <int RowIndex>
  [[nodiscard]] constexpr auto GetRow() const {
    static_assert(RowIndex >= 0);
    static_assert(RowIndex < kNumRows);

    return Row<RowIndex, NumCols>{};
  }

 private:
  static_assert(NumRows > 0);
  static_assert(NumCols > 0);
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

template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex,
          int ColIndex>
class ExprCell {
 public:
  template <int InputIndex, typename... Inputs>
  [[nodiscard]] constexpr auto EvaluateValue(const Inputs &...inputs) const {
    return Iterator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                    LeftMat::kNumCols - 1>{left_mat_, right_mat_}
        .Sum(inputs...);
  }

  template <typename... Args>
  [[nodiscard]] constexpr auto EvaluateValue(const Args &...inputs) const {
    return EvaluateValue<sizeof...(inputs) - 1>(inputs...);
  }

 private:
  template <concepts::Mat, concepts::Mat, int>
  friend class ExprRow;

  constexpr explicit ExprCell(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  LeftMat left_mat_{};
  RightMat right_mat_{};
};

template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex>
class ExprRow {
 public:
  template <int ColIndex>
  [[nodiscard]] constexpr auto GetCol() const {
    static_assert(ColIndex >= 0);
    static_assert(ColIndex < RightMat::kNumCols);

    return ExprCell<LeftMat, RightMat, RowIndex, ColIndex>{left_mat_,
                                                           right_mat_};
  }

 private:
  template <concepts::Mat, concepts::Mat>
  friend class ExprMat;

  constexpr explicit ExprRow(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  LeftMat left_mat_{};
  RightMat right_mat_{};
};

template <concepts::Mat LeftMat, concepts::Mat RightMat>
class ExprMat {
  static_assert(LeftMat::kNumCols == RightMat::kNumRows);

 public:
  static constexpr int kNumRows = LeftMat::kNumRows;
  static constexpr int kNumCols = RightMat::kNumCols;
  static constexpr int kNumInputs = LeftMat::kNumInputs + RightMat::kNumInputs;

  template <int RowIndex>
  [[nodiscard]] constexpr auto GetRow() const {
    static_assert(RowIndex >= 0);
    static_assert(RowIndex < kNumRows);

    return ExprRow<LeftMat, RightMat, RowIndex>{left_mat_, right_mat_};
  }

 private:
  friend constexpr auto operator*(const concepts::Mat auto &,
                                  const concepts::Mat auto &);

  constexpr explicit ExprMat(LeftMat left_mat, RightMat right_mat)
      : left_mat_{std::move(left_mat)}, right_mat_{std::move(right_mat)} {}

  LeftMat left_mat_{};
  RightMat right_mat_{};
};

[[nodiscard]] constexpr auto operator*(const concepts::Mat auto &left_mat,
                                       const concepts::Mat auto &right_mat) {
  return ExprMat{left_mat, right_mat};
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
