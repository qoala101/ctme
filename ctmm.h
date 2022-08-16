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
//   t->EvaluateCellValue(inputs...);
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

template <int NumRows, int NumCols>
class Mat {
  static_assert(NumRows > 0);
  static_assert(NumCols > 0);

 public:
  static constexpr int kNumRows = NumRows;
  static constexpr int kNumCols = NumCols;
  static constexpr int kNumInputs = 1;

  template <int RowIndex, int ColIndex, int InputIndex, typename... Inputs>
  [[nodiscard]] static constexpr auto SEvaluateCellValue(
      const Inputs &...inputs) {
    return std::get<InputIndex>(std::tie(inputs...))[RowIndex][ColIndex];
  }

  template <int RowIndex, int ColIndex, typename... Inputs>
  [[nodiscard]] static constexpr auto SEvaluateCellValue(
      const Inputs &...inputs) {
    return SEvaluateCellValue<0>(inputs...);
  }
};

template <concepts::Mat LeftMat, concepts::Mat RightMat, int RowIndex,
          int ColIndex, int InputIndex, int ProductIndex>
class CellValueEvaluator {
 public:
  template <typename... Inputs>
  [[nodiscard]] static constexpr auto SEvaluate(const Inputs &...inputs) {
    auto result = SEvaluateCurrentProduct(inputs...);

    if constexpr (ProductIndex > 0) {
      result += SEvaluateNextProduct(inputs...);
    }

    return result;
  }

 private:
  template <concepts::Mat, concepts::Mat, int, int>
  friend class ExprCell;

  template <concepts::Mat, concepts::Mat, int, int, int, int>
  friend class CellValueEvaluator;

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto SEvaluateCellValueFromLeftMat(
      const Inputs &...inputs) {
    return LeftMat::template SEvaluateCellValue<
        RowIndex, ProductIndex, InputIndex - RightMat::kNumInputs>(inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto SEvaluateCellValueFromRightMat(
      const Inputs &...inputs) {
    return RightMat::template SEvaluateCellValue<ProductIndex, ColIndex,
                                                 InputIndex>(inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto SEvaluateCurrentProduct(
      const Inputs &...inputs) {
    return SEvaluateCellValueFromLeftMat(inputs...) *
           SEvaluateCellValueFromRightMat(inputs...);
  }

  template <typename... Inputs>
  [[nodiscard]] static constexpr auto SEvaluateNextProduct(
      const Inputs &...inputs) {
    return CellValueEvaluator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                              ProductIndex - 1>::SEvaluate(inputs...);
  }
};

template <concepts::Mat LeftMat, concepts::Mat RightMat>
class ExprMat {
  static_assert(LeftMat::kNumCols == RightMat::kNumRows);

 public:
  static constexpr int kNumRows = LeftMat::kNumRows;
  static constexpr int kNumCols = RightMat::kNumCols;
  static constexpr int kNumInputs = LeftMat::kNumInputs + RightMat::kNumInputs;

  template <int RowIndex, int ColIndex, int InputIndex, typename... Inputs>
  [[nodiscard]] static constexpr auto SEvaluateCellValue(
      const Inputs &...inputs) {
    return CellValueEvaluator<LeftMat, RightMat, RowIndex, ColIndex, InputIndex,
                              LeftMat::kNumCols - 1>::SEvaluate(inputs...);
  }

  template <int RowIndex, int ColIndex, typename... Inputs>
  [[nodiscard]] static constexpr auto SEvaluateCellValue(
      const Inputs &...inputs) {
    return SEvaluateCellValue<RowIndex, ColIndex, sizeof...(inputs) - 1>(
        inputs...);
  }

 private:
  friend constexpr auto operator*(const concepts::Mat auto &,
                                  const concepts::Mat auto &);

  constexpr explicit ExprMat(LeftMat left_mat, RightMat right_mat) {}
};

[[nodiscard]] constexpr auto operator*(const concepts::Mat auto &left_mat,
                                       const concepts::Mat auto &right_mat) {
  return ExprMat{left_mat, right_mat};
}

// template <typename ResultType, int RowIndex, int ColIndex>
// struct MatrixEvaluator {
//   template <typename... Inputs>
//   constexpr explicit MatrixEvaluator(
//       const concepts::Mat auto &mat,
//       std::array<std::array<ResultType,
//                             std::remove_reference_t<decltype(mat)>::kNumCols>,
//                  std::remove_reference_t<decltype(mat)>::kNumRows> &result,
//       const Inputs &...inputs) {
//     result[RowIndex][ColIndex] =
//         mat.EvaluateCellValue<RowIndex, ColIndex>(inputs...);
//     MatrixEvaluator<ResultType, RowIndex, ColIndex - 1>{mat, result,
//     inputs...};
//   }
// };

// template <typename ResultType, int RowIndex>
// struct MatrixEvaluator<ResultType, RowIndex, 0> {
//   template <typename... Inputs>
//   constexpr explicit MatrixEvaluator(
//       const concepts::Mat auto &mat,
//       std::array<std::array<ResultType,
//                             std::remove_reference_t<decltype(mat)>::kNumCols>,
//                  std::remove_reference_t<decltype(mat)>::kNumRows> &result,
//       const Inputs &...inputs) {
//     result[RowIndex][0] = mat.EvaluateCellValue<RowIndex, 0>(inputs...);
//     MatrixEvaluator<ResultType, RowIndex - 1,
//                     std::remove_reference_t<decltype(mat)>::kNumCols - 1>{
//         mat, result, inputs...};
//   }
// };

// template <typename ResultType>
// struct MatrixEvaluator<ResultType, 0, 0> {
//   template <typename... Inputs>
//   constexpr explicit MatrixEvaluator(
//       const concepts::Mat auto &mat,
//       std::array<std::array<ResultType,
//                             std::remove_reference_t<decltype(mat)>::kNumCols>,
//                  std::remove_reference_t<decltype(mat)>::kNumRows> &result,
//       const Inputs &...inputs) {
//     result[0][0] = mat.EvaluateCellValue<0, 0>(inputs...);
//   }
// };

// template <typename... Inputs>
// [[nodiscard]] constexpr auto EvaluateMatrix(const concepts::Mat auto &mat,
//                                             const Inputs &...inputs) {
//   using MatType = std::remove_reference_t<decltype(mat)>;
//   using ResultType = decltype(mat.EvaluateCellValue<0, 0>(inputs...));

//   auto result = std::array<std::array<ResultType, MatType::kNumCols>,
//                            MatType::kNumRows>{};

//   MatrixEvaluator<ResultType, MatType::kNumRows - 1, MatType::kNumCols - 1>{
//       mat, result, inputs...};

//   return result;
// }
}  // namespace ctmm

#endif  // CTMM_H_
