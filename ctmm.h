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
// template <typename T, typename... Inputs>
// concept Cell = requires(const T &t, const Inputs &...inputs) {
//   t->EvaluateValue(inputs...);
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

template <int RowIndex, int ColIndex, int NumCols>
class Cell {
  static_assert(ColIndex >= 0);
  static_assert(ColIndex < NumCols);

 public:
  template <int InputIndex, typename... Inputs>
  [[nodiscard]] constexpr auto EvaluateValue(const Inputs &...inputs) const {
    return std::get<InputIndex>(std::tie(inputs...))[RowIndex][ColIndex];
  }

 private:
  template <int, int, int>
  friend class Row;

  explicit Cell() = default;
};

template <int RowIndex, int NumRows, int NumCols>
class Row {
  static_assert(RowIndex >= 0);
  static_assert(RowIndex < NumRows);

 public:
  template <int ColIndex>
  [[nodiscard]] constexpr auto GetCol() const {
    return Cell<RowIndex, ColIndex, NumCols>{};
  }

 private:
  template <int, int>
  friend class Mat;

  explicit Row() = default;
};

template <int NumRows, int NumCols>
class Mat {
  static_assert(NumRows > 0);
  static_assert(NumCols > 0);

 public:
  static constexpr int kNumRows = NumRows;
  static constexpr int kNumCols = NumCols;
  static constexpr int kNumInputs = 1;

  template <int RowIndex>
  [[nodiscard]] constexpr auto GetRow() const {
    return Row<RowIndex, NumRows, NumCols>{};
  }
};

template <int RowIndex, int ColIndex, typename... Inputs>
[[nodiscard]] constexpr auto EvaluateCell(const concepts::Mat auto &mat,
                                          const Inputs &...inputs) {
  return mat.template GetRow<RowIndex>()
      .template GetCol<ColIndex>()
      .template EvaluateValue(inputs...);
}

template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex,
          int ColIndex, int InputIndex, int Index>
class Iterator {
 public:
  template <typename... Inputs>
  [[nodiscard]] static constexpr auto Sum(LeftMat left_mat_,
                                          RightMat right_mat_,
                                          const Inputs &...inputs) {
    return left_mat_.template GetRow<RowIndex>()
                   .template GetCol<Index>()
                   .template EvaluateValue<InputIndex - RightMat::kNumInputs>(
                       inputs...) *
               right_mat_.template GetRow<Index>()
                   .template GetCol<ColIndex>()
                   .template EvaluateValue<InputIndex>(inputs...) +
           Iterator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                    Index - 1>::Sum(left_mat_, right_mat_, inputs...);
  }

 private:
  template <concepts::Mat, concepts::Mat, int, int>
  friend class ExprCell;

  template <concepts::Mat, concepts::Mat, int, int, int, int>
  friend class Iterator;
};

template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex,
          int ColIndex, int InputIndex>
class Iterator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex, -1> {
 public:
  template <typename... Inputs>
  [[nodiscard]] static constexpr auto Sum(LeftMat left_mat_,
                                          RightMat right_mat_,
                                          const Inputs &...inputs) {
    return decltype(left_mat_.template GetRow<0>()
                        .template GetCol<0>()
                        .template EvaluateValue<1>(inputs...) *
                    right_mat_.template GetRow<0>()
                        .template GetCol<0>()
                        .template EvaluateValue<1>(inputs...)){};
  }

 private:
  template <concepts::Mat, concepts::Mat, int, int>
  friend class ExprCell;

  template <concepts::Mat, concepts::Mat, int, int, int, int>
  friend class Iterator;
};

template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex,
          int ColIndex>
class ExprCell {
  static_assert(ColIndex >= 0);
  static_assert(ColIndex < RightMat::kNumCols);

 public:
  template <int InputIndex, typename... Inputs>
  [[nodiscard]] constexpr auto EvaluateValue(const Inputs &...inputs) const {
    return Iterator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                    LeftMat::kNumCols - 1>::Sum(left_mat_, right_mat_,
                                                inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] constexpr auto EvaluateValue(const Inputs &...inputs) const {
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
  static_assert(RowIndex >= 0);
  static_assert(RowIndex < LeftMat::kNumRows);

 public:
  template <int ColIndex>
  [[nodiscard]] constexpr auto GetCol() const {
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

template <typename Expression, typename ResultType, int RowIndex, int ColIndex>
struct Evaluator {
  template <typename... Inputs>
  constexpr explicit Evaluator(
      const Expression &expression,
      std::array<std::array<ResultType, Expression::kNumCols>,
                 Expression::kNumRows> &result,
      const Inputs &...inputs) {
    result[RowIndex][ColIndex] =
        EvaluateCell<RowIndex, ColIndex>(expression, inputs...);
    Evaluator<Expression, ResultType, RowIndex, ColIndex - 1>{
        expression, result, inputs...};
  }
};

template <typename Expression, typename ResultType, int RowIndex>
struct Evaluator<Expression, ResultType, RowIndex, 0> {
  template <typename... Inputs>
  constexpr explicit Evaluator(
      const Expression &expression,
      std::array<std::array<ResultType, Expression::kNumCols>,
                 Expression::kNumRows> &result,
      const Inputs &...inputs) {
    result[RowIndex][0] = EvaluateCell<RowIndex, 0>(expression, inputs...);
    Evaluator<Expression, ResultType, RowIndex - 1, Expression::kNumCols - 1>{
        expression, result, inputs...};
  }
};

template <typename Expression, typename ResultType>
struct Evaluator<Expression, ResultType, 0, 0> {
  template <typename... Inputs>
  constexpr explicit Evaluator(
      const Expression &expression,
      std::array<std::array<ResultType, Expression::kNumCols>,
                 Expression::kNumRows> &result,
      const Inputs &...inputs) {
    result[0][0] = EvaluateCell<0, 0>(expression, inputs...);
  }
};

template <typename Expression, typename... Inputs>
[[nodiscard]] constexpr auto EvaluateMatrix(const Expression &expression,
                                            const Inputs &...inputs) {
  using ResultType = decltype(EvaluateCell<0, 0>(expression, inputs...));

  auto result = std::array<std::array<ResultType, Expression::kNumCols>,
                           Expression::kNumRows>{};

  Evaluator<Expression, ResultType, Expression::kNumRows - 1,
            Expression::kNumCols - 1>{expression, result, inputs...};

  return result;
}
}  // namespace ctmm

#endif  // CTMM_H_
