#ifndef CTMM_H_
#define CTMM_H_

#include <array>
#include <exception>
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

  template <typename... Inputs>
  [[nodiscard]] constexpr auto EvaluateValue(const Inputs &...inputs) const {
    return EvaluateValue<0>(inputs...);
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

template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex,
          int ColIndex, int InputIndex, int ProductIndex>
class CellValueEvaluator {
 public:
  template <typename... Inputs>
  [[nodiscard]] static constexpr auto Evaluate(LeftMat left_mat,
                                               RightMat right_mat,
                                               const Inputs &...inputs) {
    auto result = EvaluateCurrentProduct(left_mat, right_mat, inputs...);

    if constexpr (ProductIndex > 0) {
      result += EvaluateNextProduct(left_mat, right_mat, inputs...);
    }

    return result;
  }

 private:
  template <concepts::Mat, concepts::Mat, int, int>
  friend class ExprCell;

  template <concepts::Mat, concepts::Mat, int, int, int, int>
  friend class CellValueEvaluator;

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto EvaluateValueFromLeftMat(
      const LeftMat &left_mat, const Inputs &...inputs) {
    return left_mat.template GetRow<RowIndex>()
        .template GetCol<ProductIndex>()
        .template EvaluateValue<InputIndex - RightMat::kNumInputs>(inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto EvaluateValueFromRightMat(
      const RightMat &right_mat, const Inputs &...inputs) {
    return right_mat.template GetRow<ProductIndex>()
        .template GetCol<ColIndex>()
        .template EvaluateValue<InputIndex>(inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto EvaluateCurrentProduct(
      const LeftMat &left_mat, const RightMat &right_mat,
      const Inputs &...inputs) {
    return EvaluateValueFromLeftMat(left_mat, inputs...) *
           EvaluateValueFromRightMat(right_mat, inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto EvaluateNextProduct(
      const LeftMat &left_mat, const RightMat &right_mat,
      const Inputs &...inputs) {
    return CellValueEvaluator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                              ProductIndex - 1>::Evaluate(left_mat, right_mat,
                                                          inputs...);
  }
};

template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex,
          int ColIndex>
class ExprCell {
  static_assert(ColIndex >= 0);
  static_assert(ColIndex < RightMat::kNumCols);

 public:
  template <int InputIndex, typename... Inputs>
  [[nodiscard]] constexpr auto EvaluateValue(const Inputs &...inputs) const {
    return CellValueEvaluator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                              LeftMat::kNumCols - 1>::Evaluate(left_mat_,
                                                               right_mat_,
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

template <int RowIndex, int ColIndex, typename... Inputs>
[[nodiscard]] constexpr auto EvaluateCell(const concepts::Mat auto &mat,
                                          const Inputs &...inputs) {
  return mat.template GetRow<RowIndex>()
      .template GetCol<ColIndex>()
      .template EvaluateValue(inputs...);
}

template <typename Expression, typename ResultType, int RowIndex, int ColIndex>
struct Evaluator2 {
  template <typename... Inputs>
  constexpr explicit Evaluator2(
      const Expression &expression,
      std::array<std::array<ResultType, Expression::kNumCols>,
                 Expression::kNumRows> &result,
      const Inputs &...inputs) {
    result[RowIndex][ColIndex] =
        EvaluateCell<RowIndex, ColIndex>(expression, inputs...);
    Evaluator2<Expression, ResultType, RowIndex, ColIndex - 1>{
        expression, result, inputs...};
  }
};

template <typename Expression, typename ResultType, int RowIndex>
struct Evaluator2<Expression, ResultType, RowIndex, 0> {
  template <typename... Inputs>
  constexpr explicit Evaluator2(
      const Expression &expression,
      std::array<std::array<ResultType, Expression::kNumCols>,
                 Expression::kNumRows> &result,
      const Inputs &...inputs) {
    result[RowIndex][0] = EvaluateCell<RowIndex, 0>(expression, inputs...);
    Evaluator2<Expression, ResultType, RowIndex - 1, Expression::kNumCols - 1>{
        expression, result, inputs...};
  }
};

template <typename Expression, typename ResultType>
struct Evaluator2<Expression, ResultType, 0, 0> {
  template <typename... Inputs>
  constexpr explicit Evaluator2(
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

  Evaluator2<Expression, ResultType, Expression::kNumRows - 1,
             Expression::kNumCols - 1>{expression, result, inputs...};

  return result;
}
}  // namespace ctmm

#endif  // CTMM_H_
